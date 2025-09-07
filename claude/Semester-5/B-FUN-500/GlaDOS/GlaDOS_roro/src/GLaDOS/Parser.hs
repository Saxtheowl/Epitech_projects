{-
** EPITECH PROJECT, 2025
** GLaDOS
** File description:
** S-Expression parser for GLaDOS (no external parsing library)
-}

module GLaDOS.Parser
    ( parseSExpr
    , parseProgram
    ) where

import GLaDOS.Types (SExpr(..), GLaDOSError(..))
import Data.Char (isDigit, isSpace, isAlpha, isAlphaNum)

-- | Parse a single S-expression from string
parseSExpr :: String -> Either GLaDOSError SExpr
parseSExpr input = 
    case parseExpr (skipWhitespace input) of
        Right (expr, "") -> Right expr
        Right (_, rest) -> Left $ ParseError $ "Unexpected input: " ++ rest
        Left err -> Left err

-- | Parse multiple S-expressions (program)
parseProgram :: String -> Either GLaDOSError [SExpr]
parseProgram input = parseExprs (skipWhitespace input)

-- | Skip whitespace characters
skipWhitespace :: String -> String
skipWhitespace = dropWhile isSpace

-- | Parse multiple expressions
parseExprs :: String -> Either GLaDOSError [SExpr]
parseExprs "" = Right []
parseExprs input = do
    (expr, rest) <- parseExpr input
    let rest' = skipWhitespace rest
    if null rest'
        then Right [expr]
        else do
            exprs <- parseExprs rest'
            Right (expr : exprs)

-- | Parse a single expression
parseExpr :: String -> Either GLaDOSError (SExpr, String)
parseExpr "" = Left $ ParseError "Unexpected end of input"
parseExpr ('(' : rest) = parseList (skipWhitespace rest)
parseExpr input@(c : _)
    | isDigit c || c == '-' = parseNumber input
    | isValidSymbolStart c = parseSymbol input
    | otherwise = Left $ ParseError $ "Invalid character: " ++ [c]

-- | Parse a list (started with '(')
parseList :: String -> Either GLaDOSError (SExpr, String)
parseList "" = Left $ ParseError "Unclosed list"
parseList (')' : rest) = Right (SList [], rest)
parseList input = do
    (exprs, rest) <- parseListElements input
    case skipWhitespace rest of
        (')' : rest') -> Right (SList exprs, rest')
        _ -> Left $ ParseError "Expected closing parenthesis"

-- | Parse elements of a list
parseListElements :: String -> Either GLaDOSError ([SExpr], String)
parseListElements input = 
    case skipWhitespace input of
        "" -> Left $ ParseError "Unclosed list"
        (')' : _) -> Right ([], input)
        _ -> do
            (expr, rest) <- parseExpr input
            let rest' = skipWhitespace rest
            case rest' of
                (')' : _) -> Right ([expr], rest')
                _ -> do
                    (exprs, rest'') <- parseListElements rest'
                    Right (expr : exprs, rest'')

-- | Parse a number (integer)
parseNumber :: String -> Either GLaDOSError (SExpr, String)
parseNumber input = 
    let (numStr, rest) = span (\c -> isDigit c || c == '-') input
    in case numStr of
        "" -> Left $ ParseError "Invalid number"
        "-" -> Left $ ParseError "Invalid number: lone dash"
        _ -> case reads numStr of
            [(n, "")] -> Right (SInt n, rest)
            _ -> Left $ ParseError $ "Invalid number: " ++ numStr

-- | Parse a symbol/atom
parseSymbol :: String -> Either GLaDOSError (SExpr, String)
parseSymbol input =
    let (symbol, rest) = span isValidSymbolChar input
    in case symbol of
        "" -> Left $ ParseError "Empty symbol"
        "#t" -> Right (SAtom "#t", rest)
        "#f" -> Right (SAtom "#f", rest)
        _ -> Right (SAtom symbol, rest)

-- | Check if character can start a symbol
isValidSymbolStart :: Char -> Bool
isValidSymbolStart c = isAlpha c || c `elem` "+-*/<>=?!#"

-- | Check if character can be part of a symbol
isValidSymbolChar :: Char -> Bool
isValidSymbolChar c = isAlphaNum c || c `elem` "+-*/<>=?!#"