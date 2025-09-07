{-
** EPITECH PROJECT, 2025
** GLaDOS
** File description:
** Tests for GLaDOS parser
-}

module GLaDOS.ParserSpec (spec) where

import Test.Hspec
import Test.QuickCheck
import GLaDOS.Parser (parseSExpr, parseProgram)
import GLaDOS.Types (SExpr(..), GLaDOSError(..))

spec :: Spec
spec = do
  describe "parseSExpr" $ do
    it "parses integers" $ do
      parseSExpr "42" `shouldBe` Right (SInt 42)
      parseSExpr "-15" `shouldBe` Right (SInt (-15))
      
    it "parses atoms" $ do
      parseSExpr "foo" `shouldBe` Right (SAtom "foo")
      parseSExpr "#t" `shouldBe` Right (SAtom "#t")
      parseSExpr "#f" `shouldBe` Right (SAtom "#f")
      
    it "parses empty lists" $ do
      parseSExpr "()" `shouldBe` Right (SList [])
      
    it "parses simple lists" $ do
      parseSExpr "(1 2 3)" `shouldBe` Right (SList [SInt 1, SInt 2, SInt 3])
      parseSExpr "(+ 1 2)" `shouldBe` Right (SList [SAtom "+", SInt 1, SInt 2])
      
    it "parses nested lists" $ do
      parseSExpr "((foo bar) (1 2))" `shouldBe` 
        Right (SList [SList [SAtom "foo", SAtom "bar"], SList [SInt 1, SInt 2]])
        
    it "handles whitespace" $ do
      parseSExpr "  (  +   1    2  )  " `shouldBe` Right (SList [SAtom "+", SInt 1, SInt 2])
      
    it "fails on invalid input" $ do
      parseSExpr "(" `shouldSatisfy` isLeft
      parseSExpr ")" `shouldSatisfy` isLeft
      parseSExpr "(1 2" `shouldSatisfy` isLeft

  describe "parseProgram" $ do
    it "parses multiple expressions" $ do
      parseProgram "(+ 1 2) (* 3 4)" `shouldBe` 
        Right [SList [SAtom "+", SInt 1, SInt 2], SList [SAtom "*", SInt 3, SInt 4]]
        
    it "parses single expression" $ do
      parseProgram "42" `shouldBe` Right [SInt 42]

isLeft :: Either a b -> Bool
isLeft (Left _) = True
isLeft (Right _) = False