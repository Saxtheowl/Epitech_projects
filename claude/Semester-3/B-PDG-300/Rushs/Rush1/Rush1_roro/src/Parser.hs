{-
** EPITECH PROJECT, 2025
** pushswap_checker
** File description:
** Command line arguments and operations parser
-}

module Parser where

import Text.Read (readMaybe)

-- Parse command line arguments to integers
parseArgs :: [String] -> Maybe [Int]
parseArgs args = mapM readMaybe args

-- Parse operations from input line
parseOperations :: String -> [String]
parseOperations input = words (filter (/= '\n') input)

-- Validate that all arguments are integers
validateArgs :: [String] -> Bool
validateArgs = all isValidInt
  where
    isValidInt :: String -> Bool
    isValidInt arg = case readMaybe arg :: Maybe Int of
        Just _  -> True
        Nothing -> False