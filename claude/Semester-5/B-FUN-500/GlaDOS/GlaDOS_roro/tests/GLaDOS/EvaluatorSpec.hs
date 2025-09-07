{-
** EPITECH PROJECT, 2025
** GLaDOS
** File description:
** Tests for GLaDOS evaluator
-}

module GLaDOS.EvaluatorSpec (spec) where

import Test.Hspec
import GLaDOS.Types (SExpr(..), Value(..), GLaDOSError(..))
import GLaDOS.Evaluator (eval, evalProgram, initialEnv)
import qualified Data.Map as Map

spec :: Spec
spec = do
  describe "eval" $ do
    it "evaluates integers" $ do
      eval initialEnv (SInt 42) `shouldBe` Right (VInt 42)
      
    it "evaluates booleans" $ do
      eval initialEnv (SAtom "#t") `shouldBe` Right (VBool True)
      eval initialEnv (SAtom "#f") `shouldBe` Right (VBool False)
      
    it "evaluates arithmetic operations" $ do
      eval initialEnv (SList [SAtom "+", SInt 1, SInt 2]) `shouldBe` Right (VInt 3)
      eval initialEnv (SList [SAtom "-", SInt 5, SInt 3]) `shouldBe` Right (VInt 2)
      eval initialEnv (SList [SAtom "*", SInt 4, SInt 3]) `shouldBe` Right (VInt 12)
      eval initialEnv (SList [SAtom "div", SInt 10, SInt 2]) `shouldBe` Right (VInt 5)
      eval initialEnv (SList [SAtom "mod", SInt 10, SInt 3]) `shouldBe` Right (VInt 1)
      
    it "evaluates comparison operations" $ do
      eval initialEnv (SList [SAtom "<", SInt 1, SInt 2]) `shouldBe` Right (VBool True)
      eval initialEnv (SList [SAtom "<", SInt 2, SInt 1]) `shouldBe` Right (VBool False)
      eval initialEnv (SList [SAtom "eq?", SInt 1, SInt 1]) `shouldBe` Right (VBool True)
      eval initialEnv (SList [SAtom "eq?", SInt 1, SInt 2]) `shouldBe` Right (VBool False)
      
    it "evaluates if expressions" $ do
      eval initialEnv (SList [SAtom "if", SAtom "#t", SInt 1, SInt 2]) `shouldBe` Right (VInt 1)
      eval initialEnv (SList [SAtom "if", SAtom "#f", SInt 1, SInt 2]) `shouldBe` Right (VInt 2)
      
    it "evaluates lambda expressions" $ do
      case eval initialEnv (SList [SAtom "lambda", SList [SAtom "x"], SAtom "x"]) of
        Right (VProc _ _ _) -> True `shouldBe` True
        _ -> expectationFailure "Expected procedure"
        
    it "fails on unbound variables" $ do
      eval initialEnv (SAtom "foo") `shouldSatisfy` isUnboundVariable
      
    it "fails on division by zero" $ do
      eval initialEnv (SList [SAtom "div", SInt 1, SInt 0]) `shouldBe` Left DivisionByZero
      
  describe "evalProgram" $ do
    it "evaluates simple programs" $ do
      evalProgram initialEnv [SInt 42] `shouldBe` Right (VInt 42)
      
    it "evaluates programs with definitions" $ do
      let program = [ SList [SAtom "define", SAtom "x", SInt 42]
                    , SAtom "x"
                    ]
      evalProgram initialEnv program `shouldBe` Right (VInt 42)

isUnboundVariable :: Either GLaDOSError Value -> Bool
isUnboundVariable (Left (UnboundVariable _)) = True
isUnboundVariable _ = False