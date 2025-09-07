{-
** EPITECH PROJECT, 2025
** GLaDOS
** File description:
** Main test specification
-}

import Test.Hspec
import qualified GLaDOS.ParserSpec as Parser
import qualified GLaDOS.EvaluatorSpec as Evaluator
import qualified GLaDOS.IntegrationSpec as Integration

main :: IO ()
main = hspec $ do
  describe "GLaDOS Parser" Parser.spec
  describe "GLaDOS Evaluator" Evaluator.spec
  describe "GLaDOS Integration" Integration.spec