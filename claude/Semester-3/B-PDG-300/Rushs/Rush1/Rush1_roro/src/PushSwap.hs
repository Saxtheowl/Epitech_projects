{-
** EPITECH PROJECT, 2025
** pushswap_checker
** File description:
** Main logic for pushswap checker
-}

module PushSwap where

import Operations
import Parser
import System.Exit (exitWith, ExitCode(..))

-- Main logic for the pushswap checker
checkPushSwap :: [String] -> String -> IO ()
checkPushSwap args operationsLine = do
    case parseArgs args of
        Nothing -> exitWith (ExitFailure 84)
        Just numbers -> do
            let operations = parseOperations operationsLine
            let initialStacks = Stacks numbers []
            case applyOperations operations initialStacks of
                Nothing -> exitWith (ExitFailure 84)
                Just finalStacks -> 
                    if isSorted finalStacks
                    then putStrLn "OK"
                    else putStrLn $ "KO: " ++ show finalStacks

-- Format the final stacks for display (matching the expected output format)
formatStacks :: Stacks -> String
formatStacks (Stacks la lb) = "(" ++ show la ++ "," ++ show lb ++ ")"