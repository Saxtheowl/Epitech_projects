{-
EPITECH PROJECT, 2025
Wolfram
File description:
Test specification
-}

import Test.Hspec
import Wolfram

main :: IO ()
main = hspec $ do
    describe "Wolfram Cellular Automaton" $ do
        it "should generate initial state correctly" $ do
            let initial = generateInitialState 5
            length initial `shouldBe` 5
            filter (== Alive) initial `shouldSatisfy` (not . null)
        
        it "should display generation correctly" $ do
            let gen = [Dead, Alive, Dead, Alive, Dead]
            let display = displayGeneration gen 5 0
            display `shouldBe` " * * "
        
        it "should apply rule correctly" $ do
            let rule30 = ruleTable 30
            let gen = [Dead, Alive, Dead]
            let next = nextGeneration rule30 gen
            length next `shouldBe` 3