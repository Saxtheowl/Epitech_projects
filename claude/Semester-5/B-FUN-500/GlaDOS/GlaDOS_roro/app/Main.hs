{-
** EPITECH PROJECT, 2025
** GLaDOS
** File description:
** Main entry point for GLaDOS interpreter
-}

module Main (main) where

import System.Exit (exitWith, ExitCode(ExitFailure, ExitSuccess))
import System.IO (hGetContents, stdin, hPutStrLn, stderr)
import Control.Exception (catch, SomeException)
import GLaDOS.Core (runGLaDOS)

main :: IO ()
main = do
    input <- hGetContents stdin
    result <- catch (runGLaDOS input) handleException
    case result of
        Right output -> putStrLn output >> exitWith ExitSuccess
        Left err -> hPutStrLn stderr err >> exitWith (ExitFailure 84)
  where
    handleException :: SomeException -> IO (Either String String)
    handleException e = return $ Left $ "Error: " ++ show e