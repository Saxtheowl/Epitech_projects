{-
** EPITECH PROJECT, 2025
** GLaDOS
** File description:
** Integration tests for GLaDOS
-}

module GLaDOS.IntegrationSpec (spec) where

import Test.Hspec
import GLaDOS.Core (runGLaDOS)

spec :: Spec
spec = do
  describe "runGLaDOS integration tests" $ do
    it "evaluates simple arithmetic" $ do
      result <- runGLaDOS "(+ 1 2)"
      result `shouldBe` Right "3"
      
    it "evaluates factorial function" $ do
      let factorial = unlines
            [ "(define (fact x)"
            , "  (if (eq? x 1)"
            , "      1"
            , "      (* x (fact (- x 1)))))"
            , "(fact 5)"
            ]
      result <- runGLaDOS factorial
      result `shouldBe` Right "120"
      
    it "evaluates lambda expressions" $ do
      result <- runGLaDOS "((lambda (x y) (+ x y)) 3 4)"
      result `shouldBe` Right "7"
      
    it "handles errors gracefully" $ do
      result <- runGLaDOS "(+ foo 2)"
      case result of
        Left msg -> msg `shouldContain` "foo is not bound"
        Right _ -> expectationFailure "Expected error"
        
    it "handles division by zero" $ do
      result <- runGLaDOS "(div 1 0)"
      case result of
        Left msg -> msg `shouldContain` "division by zero"
        Right _ -> expectationFailure "Expected error"
        
    it "evaluates boolean expressions" $ do
      result <- runGLaDOS "(< 1 2)"
      result `shouldBe` Right "#t"
      
    it "evaluates nested expressions" $ do
      result <- runGLaDOS "(+ (* 2 3) (div 10 2))"
      result `shouldBe` Right "11"