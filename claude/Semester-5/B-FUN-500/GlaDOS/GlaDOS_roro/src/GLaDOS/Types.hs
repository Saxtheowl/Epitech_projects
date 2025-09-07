{-
** EPITECH PROJECT, 2025
** GLaDOS
** File description:
** Data types for GLaDOS language
-}

module GLaDOS.Types
    ( Value(..)
    , SExpr(..)
    , Environment
    , GLaDOSError(..)
    ) where

import qualified Data.Map as Map

-- | Values that can be computed in GLaDOS
data Value
    = VInt Integer
    | VBool Bool
    | VProc [String] SExpr Environment  -- parameters, body, closure
    | VBuiltin String ([Value] -> Either GLaDOSError Value)

instance Show Value where
    show (VInt n) = show n
    show (VBool True) = "#t"
    show (VBool False) = "#f"
    show (VProc _ _ _) = "#<procedure>"
    show (VBuiltin name _) = "#<builtin:" ++ name ++ ">"

instance Eq Value where
    (VInt a) == (VInt b) = a == b
    (VBool a) == (VBool b) = a == b
    _ == _ = False

-- | S-Expressions for LISP syntax
data SExpr
    = SAtom String
    | SInt Integer
    | SList [SExpr]
    deriving (Show, Eq)

-- | Environment for variable bindings
type Environment = Map.Map String Value

-- | Error types for GLaDOS
data GLaDOSError
    = ParseError String
    | UnboundVariable String
    | TypeError String
    | ArityError String
    | DivisionByZero
    | RuntimeError String
    deriving (Show, Eq)