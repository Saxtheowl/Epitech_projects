{-
** EPITECH PROJECT, 2025
** pushswap_checker
** File description:
** Main entry point for pushswap checker
-}

module Main where

import System.Environment (getArgs)
import System.Exit (exitWith, ExitCode(..))
import PushSwap

main :: IO ()
main = do
    args <- getArgs
    if null args
        then exitWith (ExitFailure 84)
        else do
            operationsLine <- getLine
            checkPushSwap args operationsLine