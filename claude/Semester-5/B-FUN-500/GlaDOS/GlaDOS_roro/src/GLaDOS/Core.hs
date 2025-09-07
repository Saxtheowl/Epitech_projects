{-
** EPITECH PROJECT, 2025
** GLaDOS
** File description:
** Core module for GLaDOS interpreter
-}

module GLaDOS.Core
    ( runGLaDOS
    ) where

import GLaDOS.Types (GLaDOSError(..))
import GLaDOS.Parser (parseProgram)
import GLaDOS.Evaluator (evalProgram, initialEnv)

-- | Main function to run GLaDOS interpreter
runGLaDOS :: String -> IO (Either String String)
runGLaDOS input = do
    case parseProgram input of
        Left (ParseError msg) -> return $ Left $ "*** ERROR : " ++ msg
        Left (UnboundVariable msg) -> return $ Left $ "*** ERROR : " ++ msg
        Left (TypeError msg) -> return $ Left $ "*** ERROR : " ++ msg
        Left (ArityError msg) -> return $ Left $ "*** ERROR : " ++ msg
        Left DivisionByZero -> return $ Left $ "*** ERROR : division by zero"
        Left (RuntimeError msg) -> return $ Left $ "*** ERROR : " ++ msg
        Right exprs -> do
            case evalProgram initialEnv exprs of
                Left (ParseError msg) -> return $ Left $ "*** ERROR : " ++ msg
                Left (UnboundVariable msg) -> return $ Left $ "*** ERROR : " ++ msg
                Left (TypeError msg) -> return $ Left $ "*** ERROR : " ++ msg
                Left (ArityError msg) -> return $ Left $ "*** ERROR : " ++ msg
                Left DivisionByZero -> return $ Left $ "*** ERROR : division by zero"
                Left (RuntimeError msg) -> return $ Left $ "*** ERROR : " ++ msg
                Right result -> return $ Right $ show result