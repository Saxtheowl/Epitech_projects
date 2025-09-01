{-
EPITECH PROJECT, 2025
Wolfram
File description:
Main Wolfram module for cellular automata
-}

module Wolfram
    ( CellState(..)
    , Generation
    , Rule
    , Config(..)
    , applyRule
    , nextGeneration
    , generateInitialState
    , displayGeneration
    , runAutomaton
    ) where

import System.IO (hFlush, stdout)

data CellState = Dead | Alive
    deriving (Eq, Show)

type Generation = [CellState]
type Rule = (CellState, CellState, CellState) -> CellState

data Config = Config
    { configRule    :: Int
    , configStart   :: Int
    , configLines   :: Maybe Int
    , configWindow  :: Int
    , configMove    :: Int
    } deriving (Show)

-- Rule definitions for cellular automata
ruleTable :: Int -> Rule
ruleTable n = \(left, center, right) -> 
    let index = cellToInt left * 4 + cellToInt center * 2 + cellToInt right
        bit = (n `div` (2 ^ index)) `mod` 2
    in if bit == 1 then Alive else Dead
  where
    cellToInt Dead = 0
    cellToInt Alive = 1

-- Apply rule to generate next cell state
applyRule :: Rule -> Generation -> Int -> CellState
applyRule rule gen pos = rule (getCell (pos - 1), getCell pos, getCell (pos + 1))
  where
    getCell i
        | i < 0 || i >= length gen = Dead
        | otherwise = gen !! i

-- Generate next generation from current one
nextGeneration :: Rule -> Generation -> Generation
nextGeneration rule gen = 
    let len = length gen
        extended = replicate 100 Dead ++ gen ++ replicate 100 Dead
        newGen = map (applyRule rule extended) [100..len + 99]
    in newGen

-- Generate initial state with single alive cell in center
generateInitialState :: Int -> Generation
generateInitialState width = 
    let center = width `div` 2
    in replicate center Dead ++ [Alive] ++ replicate (width - center - 1) Dead

-- Display a generation as a string
displayGeneration :: Generation -> Int -> Int -> String
displayGeneration gen window move =
    let startPos = max 0 (length gen `div` 2 - window `div` 2 + move)
        endPos = min (length gen) (startPos + window)
        visibleCells = take (endPos - startPos) $ drop startPos gen
        cellToChar Dead = ' '
        cellToChar Alive = '*'
    in map cellToChar visibleCells

-- Run the automaton simulation
runAutomaton :: Config -> IO ()
runAutomaton config = do
    let rule = ruleTable (configRule config)
        initial = generateInitialState 200
        generations = iterate (nextGeneration rule) initial
        startGen = configStart config
        linesToShow = maybe maxBound id (configLines config)
    
    mapM_ (\(i, gen) -> do
        putStrLn $ displayGeneration gen (configWindow config) (configMove config)
        hFlush stdout
        ) $ take linesToShow $ zip [startGen..] $ drop startGen generations