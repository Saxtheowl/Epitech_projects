{-
EPITECH PROJECT, 2025
Wolfram
File description:
Main entry point
-}

module Main where

import System.Environment (getArgs)
import System.Exit (exitWith, ExitCode(..))
import Control.Exception (catch, SomeException)
import Args (parseArgs)
import Wolfram (runAutomaton)

main :: IO ()
main = do
    args <- getArgs
    config <- parseArgs args
    catch (runAutomaton config) handleException
  where
    handleException :: SomeException -> IO ()
    handleException _ = exitWith (ExitFailure 84)