-- EPITECH PROJECT, 2025
-- Rush 1
-- File description:
-- Pushswap checker implementation in Haskell

module Main where

import System.Environment (getArgs)
import System.Exit (exitWith, ExitCode(..))
import System.IO (hPutStrLn, stderr)

-- Data structure to represent the two stacks
data PushSwapState = PushSwapState
    { stackA :: [Int]
    , stackB :: [Int]
    } deriving (Show, Eq)

-- Initialize state with list A and empty list B
initState :: [Int] -> PushSwapState
initState nums = PushSwapState nums []

-- Check if list A is sorted and list B is empty
isSorted :: PushSwapState -> Bool
isSorted (PushSwapState a b) = null b && isSortedList a
  where
    isSortedList [] = True
    isSortedList [_] = True
    isSortedList (x:y:xs) = x <= y && isSortedList (y:xs)

-- Apply a single operation to the state
applyOperation :: String -> PushSwapState -> PushSwapState
applyOperation "sa" state = swapA state
applyOperation "sb" state = swapB state
applyOperation "sc" state = swapB (swapA state)
applyOperation "pa" state = pushA state
applyOperation "pb" state = pushB state
applyOperation "ra" state = rotateA state
applyOperation "rb" state = rotateB state
applyOperation "rr" state = rotateB (rotateA state)
applyOperation "rra" state = reverseRotateA state
applyOperation "rrb" state = reverseRotateB state
applyOperation "rrr" state = reverseRotateB (reverseRotateA state)
applyOperation _ state = state -- Invalid operation, do nothing

-- Individual operations
swapA :: PushSwapState -> PushSwapState
swapA (PushSwapState (x:y:xs) b) = PushSwapState (y:x:xs) b
swapA state = state

swapB :: PushSwapState -> PushSwapState
swapB (PushSwapState a (x:y:xs)) = PushSwapState a (y:x:xs)
swapB state = state

pushA :: PushSwapState -> PushSwapState
pushA (PushSwapState a (x:xs)) = PushSwapState (x:a) xs
pushA state = state

pushB :: PushSwapState -> PushSwapState
pushB (PushSwapState (x:xs) b) = PushSwapState xs (x:b)
pushB state = state

rotateA :: PushSwapState -> PushSwapState
rotateA (PushSwapState (x:xs) b) = PushSwapState (xs ++ [x]) b
rotateA state = state

rotateB :: PushSwapState -> PushSwapState
rotateB (PushSwapState a (x:xs)) = PushSwapState a (xs ++ [x])
rotateB state = state

reverseRotateA :: PushSwapState -> PushSwapState
reverseRotateA (PushSwapState a b) =
    case reverse a of
        [] -> PushSwapState a b
        (x:xs) -> PushSwapState (x : reverse xs) b

reverseRotateB :: PushSwapState -> PushSwapState
reverseRotateB (PushSwapState a b) =
    case reverse b of
        [] -> PushSwapState a b
        (x:xs) -> PushSwapState a (x : reverse xs)

-- Apply a sequence of operations
applyOperations :: [String] -> PushSwapState -> PushSwapState
applyOperations ops state = foldl (flip applyOperation) state ops

-- Parse command line arguments to integers
parseArgs :: [String] -> Either String [Int]
parseArgs args =
    case traverse readMaybe args of
        Just nums -> Right nums
        Nothing -> Left "Invalid integer arguments"
  where
    readMaybe s = case reads s of
        [(x, "")] -> Just x
        _ -> Nothing

-- Main function
main :: IO ()
main = do
    args <- getArgs
    case parseArgs args of
        Left err -> do
            hPutStrLn stderr err
            exitWith (ExitFailure 84)
        Right nums -> do
            operations <- getLine
            let ops = words operations
                initialState = initState nums
                finalState = applyOperations ops initialState

            if isSorted finalState
                then putStrLn "OK"
                else do
                    putStrLn $ "KO: (" ++ show (stackA finalState) ++ "," ++ show (stackB finalState) ++ ")"

            exitWith ExitSuccess