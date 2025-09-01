{-
EPITECH PROJECT, 2025
Wolfram
File description:
Command line argument parsing
-}

module Args
    ( parseArgs
    , showUsage
    ) where

import Wolfram (Config(..))
import System.Exit (exitWith, ExitCode(..))
import System.IO (hPutStrLn, stderr)

showUsage :: IO ()
showUsage = do
    hPutStrLn stderr "USAGE: wolfram --rule R [--start N] [--lines N] [--window N] [--move N]"
    hPutStrLn stderr ""
    hPutStrLn stderr "    --rule      the ruleset to use (mandatory)"
    hPutStrLn stderr "    --start     the generation number at which to start the display (default: 0)"
    hPutStrLn stderr "    --lines     the number of lines to display (default: infinite)"
    hPutStrLn stderr "    --window    the number of cells to display on each line (default: 80)"
    hPutStrLn stderr "    --move      translation to apply on the window (default: 0)"

parseArgs :: [String] -> IO Config
parseArgs [] = showUsage >> exitWith (ExitFailure 84)
parseArgs args = do
    config <- parseArgs' args defaultConfig
    case configRule config of
        (-1) -> showUsage >> exitWith (ExitFailure 84)
        _    -> return config
  where
    defaultConfig = Config (-1) 0 Nothing 80 0

parseArgs' :: [String] -> Config -> IO Config
parseArgs' [] config = return config
parseArgs' ("--rule":r:rest) config = 
    case reads r of
        [(rule, "")] | rule >= 0 && rule <= 255 -> parseArgs' rest config { configRule = rule }
        _ -> showUsage >> exitWith (ExitFailure 84)
parseArgs' ("--start":s:rest) config =
    case reads s of
        [(start, "")] | start >= 0 -> parseArgs' rest config { configStart = start }
        _ -> showUsage >> exitWith (ExitFailure 84)
parseArgs' ("--lines":l:rest) config =
    case reads l of
        [(lines', "")] | lines' > 0 -> parseArgs' rest config { configLines = Just lines' }
        _ -> showUsage >> exitWith (ExitFailure 84)
parseArgs' ("--window":w:rest) config =
    case reads w of
        [(window, "")] | window > 0 -> parseArgs' rest config { configWindow = window }
        _ -> showUsage >> exitWith (ExitFailure 84)
parseArgs' ("--move":m:rest) config =
    case reads m of
        [(move, "")] -> parseArgs' rest config { configMove = move }
        _ -> showUsage >> exitWith (ExitFailure 84)
parseArgs' _ _ = showUsage >> exitWith (ExitFailure 84)