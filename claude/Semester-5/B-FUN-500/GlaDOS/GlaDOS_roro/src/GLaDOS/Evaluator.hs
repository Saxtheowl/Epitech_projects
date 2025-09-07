{-
** EPITECH PROJECT, 2025
** GLaDOS
** File description:
** Evaluator for GLaDOS LISP expressions
-}

module GLaDOS.Evaluator
    ( eval
    , evalProgram
    , initialEnv
    ) where

import GLaDOS.Types (SExpr(..), Value(..), Environment, GLaDOSError(..))
import qualified Data.Map as Map

-- | Evaluate a single expression
eval :: Environment -> SExpr -> Either GLaDOSError Value
eval env (SInt n) = Right $ VInt n
eval env (SAtom "#t") = Right $ VBool True
eval env (SAtom "#f") = Right $ VBool False
eval env (SAtom symbol) = 
    case Map.lookup symbol env of
        Just value -> Right value
        Nothing -> Left $ UnboundVariable $ "variable " ++ symbol ++ " is not bound"

eval env (SList []) = Left $ RuntimeError "Cannot evaluate empty list"

eval env (SList (SAtom "define" : args)) = evalDefine env args

eval env (SList (SAtom "lambda" : args)) = evalLambda env args

eval env (SList (SAtom "if" : args)) = evalIf env args

eval env (SList (func : args)) = do
    funcValue <- eval env func
    argValues <- mapM (eval env) args
    applyFunction funcValue argValues

-- | Evaluate define special form
evalDefine :: Environment -> [SExpr] -> Either GLaDOSError Value
evalDefine env [SAtom symbol, expr] = eval env expr
evalDefine env (SList (SAtom name : params) : body : []) = 
    case mapM extractSymbol params of
        Right paramNames -> Right $ VProc paramNames body env
        Left err -> Left err
evalDefine _ _ = Left $ RuntimeError "Invalid define syntax"

-- | Evaluate lambda special form  
evalLambda :: Environment -> [SExpr] -> Either GLaDOSError Value
evalLambda env [SList params, body] = 
    case mapM extractSymbol params of
        Right paramNames -> Right $ VProc paramNames body env
        Left err -> Left err
evalLambda _ _ = Left $ RuntimeError "Invalid lambda syntax"

-- | Evaluate if special form
evalIf :: Environment -> [SExpr] -> Either GLaDOSError Value
evalIf env [cond, thenExpr, elseExpr] = do
    condValue <- eval env cond
    case condValue of
        VBool False -> eval env elseExpr
        _ -> eval env thenExpr
evalIf _ _ = Left $ RuntimeError "Invalid if syntax"

-- | Apply function to arguments
applyFunction :: Value -> [Value] -> Either GLaDOSError Value
applyFunction (VBuiltin _ func) args = func args
applyFunction (VProc params body closure) args 
    | length params == length args = do
        let newEnv = foldr (uncurry Map.insert) closure (zip params args)
        eval newEnv body
    | otherwise = Left $ ArityError $ "Expected " ++ show (length params) ++ " arguments, got " ++ show (length args)
applyFunction _ _ = Left $ TypeError "Not a function"

-- | Extract symbol from S-expression
extractSymbol :: SExpr -> Either GLaDOSError String
extractSymbol (SAtom s) = Right s
extractSymbol _ = Left $ RuntimeError "Expected symbol"

-- | Evaluate program (multiple expressions)
evalProgram :: Environment -> [SExpr] -> Either GLaDOSError Value
evalProgram _ [] = Left $ RuntimeError "Empty program"
evalProgram env [expr] = eval env expr
evalProgram env (SList (SAtom "define" : args) : rest) = do
    case args of
        [SAtom symbol, expr] -> do
            value <- eval env expr
            let newEnv = Map.insert symbol value env
            evalProgram newEnv rest
        (SList (SAtom name : params) : body : []) -> do
            case mapM extractSymbol params of
                Right paramNames -> do
                    let func = VProc paramNames body env
                    let newEnv = Map.insert name func env
                    evalProgram newEnv rest
                Left err -> Left err
        _ -> Left $ RuntimeError "Invalid define syntax"
evalProgram env (expr : rest) = do
    _ <- eval env expr
    evalProgram env rest

-- | Initial environment with built-in functions
initialEnv :: Environment
initialEnv = Map.fromList
    [ ("+", VBuiltin "+" addBuiltin)
    , ("-", VBuiltin "-" subBuiltin)
    , ("*", VBuiltin "*" mulBuiltin)
    , ("div", VBuiltin "div" divBuiltin)
    , ("mod", VBuiltin "mod" modBuiltin)
    , ("<", VBuiltin "<" ltBuiltin)
    , ("eq?", VBuiltin "eq?" eqBuiltin)
    ]

-- | Built-in arithmetic functions
addBuiltin :: [Value] -> Either GLaDOSError Value
addBuiltin [VInt a, VInt b] = Right $ VInt (a + b)
addBuiltin _ = Left $ TypeError "Addition requires two integers"

subBuiltin :: [Value] -> Either GLaDOSError Value
subBuiltin [VInt a, VInt b] = Right $ VInt (a - b)
subBuiltin _ = Left $ TypeError "Subtraction requires two integers"

mulBuiltin :: [Value] -> Either GLaDOSError Value
mulBuiltin [VInt a, VInt b] = Right $ VInt (a * b)
mulBuiltin _ = Left $ TypeError "Multiplication requires two integers"

divBuiltin :: [Value] -> Either GLaDOSError Value
divBuiltin [VInt a, VInt 0] = Left DivisionByZero
divBuiltin [VInt a, VInt b] = Right $ VInt (a `div` b)
divBuiltin _ = Left $ TypeError "Division requires two integers"

modBuiltin :: [Value] -> Either GLaDOSError Value
modBuiltin [VInt a, VInt 0] = Left DivisionByZero
modBuiltin [VInt a, VInt b] = Right $ VInt (a `mod` b)
modBuiltin _ = Left $ TypeError "Modulo requires two integers"

ltBuiltin :: [Value] -> Either GLaDOSError Value
ltBuiltin [VInt a, VInt b] = Right $ VBool (a < b)
ltBuiltin _ = Left $ TypeError "Less-than requires two integers"

eqBuiltin :: [Value] -> Either GLaDOSError Value
eqBuiltin [a, b] = Right $ VBool (a == b)
eqBuiltin _ = Left $ TypeError "Equality requires two arguments"