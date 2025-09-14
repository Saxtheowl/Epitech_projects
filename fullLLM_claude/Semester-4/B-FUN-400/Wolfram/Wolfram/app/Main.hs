module Main where

import Wolfram
import System.Environment (getArgs)
import System.Exit (exitWith, ExitCode(ExitFailure))
import System.IO (hPutStrLn, stderr, hFlush, stdout)

main :: IO ()
main = do
    args <- getArgs
    case parseArgs args of
        Left errMsg -> do
            hPutStrLn stderr errMsg
            hPutStrLn stderr showUsage
            exitWith (ExitFailure 84)
        Right opts -> runSimulation opts

runSimulation :: Options -> IO ()
runSimulation opts = do
    let rule = optRule opts
        startGen = optStart opts
        generations = generateSequence rule
        startingGen = drop startGen generations
    
    case optLines opts of
        Nothing -> displayInfinite opts startingGen
        Just numLines -> displayFinite opts startingGen numLines

displayInfinite :: Options -> [Generation] -> IO ()
displayInfinite opts gens = do
    mapM_ (\gen -> do
        putStrLn (displayGeneration opts gen)
        hFlush stdout
    ) gens

displayFinite :: Options -> [Generation] -> Int -> IO ()
displayFinite opts gens numLines = do
    let limitedGens = take numLines gens
    mapM_ (putStrLn . displayGeneration opts) limitedGens