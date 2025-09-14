module Wolfram
    ( Rule(..)
    , Cell(..)
    , Generation
    , Options(..)
    , parseArgs
    , applyRule
    , nextGeneration
    , generateSequence
    , displayGeneration
    , showUsage
    ) where

import System.Environment (getArgs)
import System.Exit (exitWith, ExitCode(ExitFailure))
import Data.List (isPrefixOf)

-- | Cell state: alive (*) or dead (space)
data Cell = Alive | Dead
    deriving (Eq)

instance Show Cell where
    show Alive = "*"
    show Dead = " "

-- | A generation is an infinite list of cells (conceptually)
-- We represent it as a finite list with implicit dead cells at boundaries
type Generation = [Cell]

-- | Cellular automaton rules
data Rule = Rule30 | Rule90 | Rule110
    deriving (Eq, Show)

-- | Command line options
data Options = Options
    { optRule :: Rule
    , optStart :: Int
    , optLines :: Maybe Int
    , optWindow :: Int
    , optMove :: Int
    } deriving (Show)

-- | Default options
defaultOptions :: Options
defaultOptions = Options
    { optRule = Rule30  -- Will be overridden by mandatory --rule
    , optStart = 0
    , optLines = Nothing  -- Infinite by default
    , optWindow = 80
    , optMove = 0
    }

-- | Parse command line arguments
parseArgs :: [String] -> Either String Options
parseArgs args = 
    if not (hasRule args)
    then Left "Missing mandatory --rule argument"
    else parseArgs' args defaultOptions
  where
    parseArgs' [] opts = Right opts
    parseArgs' ("--rule":ruleStr:rest) opts = 
        case parseRule ruleStr of
            Just rule -> parseArgs' rest (opts { optRule = rule })
            Nothing -> Left $ "Invalid rule: " ++ ruleStr
    parseArgs' ["--rule"] _ = Left "--rule requires a value"
    parseArgs' ("--start":startStr:rest) opts =
        case reads startStr of
            [(start, "")] | start >= 0 -> parseArgs' rest (opts { optStart = start })
            _ -> Left $ "Invalid start value: " ++ startStr
    parseArgs' ["--start"] _ = Left "--start requires a value"
    parseArgs' ("--lines":linesStr:rest) opts =
        case reads linesStr of
            [(lines', "")] | lines' > 0 -> parseArgs' rest (opts { optLines = Just lines' })
            _ -> Left $ "Invalid lines value: " ++ linesStr
    parseArgs' ["--lines"] _ = Left "--lines requires a value"
    parseArgs' ("--window":windowStr:rest) opts =
        case reads windowStr of
            [(window, "")] | window > 0 -> parseArgs' rest (opts { optWindow = window })
            _ -> Left $ "Invalid window value: " ++ windowStr
    parseArgs' ["--window"] _ = Left "--window requires a value"
    parseArgs' ("--move":moveStr:rest) opts =
        case reads moveStr of
            [(move, "")] -> parseArgs' rest (opts { optMove = move })
            _ -> Left $ "Invalid move value: " ++ moveStr
    parseArgs' ["--move"] _ = Left "--move requires a value"
    parseArgs' (arg:_) _ = Left $ "Unknown argument: " ++ arg

    hasRule = any ("--rule" `isPrefixOf`)

-- | Parse rule string to Rule type
parseRule :: String -> Maybe Rule
parseRule "30" = Just Rule30
parseRule "90" = Just Rule90
parseRule "110" = Just Rule110
parseRule _ = Nothing

-- | Apply cellular automaton rule to three cells
applyRule :: Rule -> (Cell, Cell, Cell) -> Cell
applyRule Rule30 (Dead, Dead, Dead) = Dead
applyRule Rule30 (Dead, Dead, Alive) = Alive
applyRule Rule30 (Dead, Alive, Dead) = Alive
applyRule Rule30 (Dead, Alive, Alive) = Alive
applyRule Rule30 (Alive, Dead, Dead) = Alive
applyRule Rule30 (Alive, Dead, Alive) = Dead
applyRule Rule30 (Alive, Alive, Dead) = Dead
applyRule Rule30 (Alive, Alive, Alive) = Dead

applyRule Rule90 (Dead, Dead, Dead) = Dead
applyRule Rule90 (Dead, Dead, Alive) = Alive
applyRule Rule90 (Dead, Alive, Dead) = Dead
applyRule Rule90 (Dead, Alive, Alive) = Alive
applyRule Rule90 (Alive, Dead, Dead) = Alive
applyRule Rule90 (Alive, Dead, Alive) = Dead
applyRule Rule90 (Alive, Alive, Dead) = Alive
applyRule Rule90 (Alive, Alive, Alive) = Dead

applyRule Rule110 (Dead, Dead, Dead) = Dead
applyRule Rule110 (Dead, Dead, Alive) = Alive
applyRule Rule110 (Dead, Alive, Dead) = Alive
applyRule Rule110 (Dead, Alive, Alive) = Alive
applyRule Rule110 (Alive, Dead, Dead) = Dead
applyRule Rule110 (Alive, Dead, Alive) = Alive
applyRule Rule110 (Alive, Alive, Dead) = Alive
applyRule Rule110 (Alive, Alive, Alive) = Dead

-- | Get cell at position with default Dead for out-of-bounds
getCell :: Generation -> Int -> Cell
getCell gen pos
    | pos < 0 || pos >= length gen = Dead
    | otherwise = gen !! pos

-- | Generate next generation from current one
nextGeneration :: Rule -> Generation -> Generation
nextGeneration rule gen = 
    let size = max (length gen + 2) 3  -- Expand by 2 to handle growth
        indices = [-1 .. size]
        newCells = map (\i -> 
            let left = getCell gen (i - 1)
                center = getCell gen i
                right = getCell gen (i + 1)
            in applyRule rule (left, center, right)
        ) indices
    in trim newCells
  where
    -- Trim leading and trailing dead cells, but keep at least some context
    trim cells = 
        let trimmed = dropWhile (== Dead) $ reverse $ dropWhile (== Dead) $ reverse cells
        in if null trimmed then [Dead] else trimmed

-- | Generate infinite sequence of generations
generateSequence :: Rule -> [Generation]
generateSequence rule = iterate (nextGeneration rule) initialGeneration
  where
    initialGeneration = [Alive]  -- Single alive cell in center

-- | Display a generation with windowing
displayGeneration :: Options -> Generation -> String
displayGeneration opts gen = 
    let windowSize = optWindow opts
        move = optMove opts
        centerPos = length gen `div` 2
        startPos = centerPos - (windowSize `div` 2) + move
        window = [getCell gen (startPos + i) | i <- [0 .. windowSize - 1]]
    in concatMap show window

-- | Show usage message
showUsage :: String
showUsage = unlines
    [ "USAGE:"
    , "    ./wolfram --rule R [--start S] [--lines L] [--window W] [--move M]"
    , ""
    , "DESCRIPTION:"
    , "    Elementary cellular automaton simulation"
    , ""
    , "    --rule R       Ruleset to use (30, 90, 110) [MANDATORY]"
    , "    --start S      Generation number to start display (default: 0)"
    , "    --lines L      Number of lines to display (default: infinite)"
    , "    --window W     Number of cells per line (default: 80)"
    , "    --move M       Window translation (default: 0)"
    ]