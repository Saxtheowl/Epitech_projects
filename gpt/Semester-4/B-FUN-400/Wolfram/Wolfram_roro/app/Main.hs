{-
** EPITECH PROJECT, 2025
** Wolfram_roro
** File description:
** Main (Haskell)
-}

module Main (main) where

import System.Environment (getArgs)
import System.Exit (exitWith, ExitCode(..))
import System.IO (hPutStrLn, stderr)
import Data.Set (Set)
import qualified Data.Set as S
import Data.Bits (testBit)

data Cfg = Cfg
  { cfgRule   :: Int
  , cfgStart  :: Int
  , cfgLines  :: Maybe Int
  , cfgWindow :: Int
  , cfgMove   :: Int
  } deriving (Show)

usage :: String -> String
usage bin =
  "Usage: " ++ bin ++ " --rule N [--start N] [--lines N] [--window N] [--move N]"

die84 :: String -> IO a
die84 msg = do
  hPutStrLn stderr msg
  exitWith (ExitFailure 84)

parseInt :: String -> Maybe Int
parseInt s = if not (null s) && all (`elem` ['0'..'9']) s
             then Just (read s)
             else Nothing

parseArgs :: [String] -> IO Cfg
parseArgs as = go as (Cfg { cfgRule = -1, cfgStart = 0, cfgLines = Nothing
                          , cfgWindow = 80, cfgMove = 0 })
  where
    go [] cfg
      | cfgRule cfg `elem` [30,90,110] = pure cfg
      | otherwise = die84 (usage "wolfram")
    go ("--help":_) _ = do
      putStrLn (usage "wolfram")
      exitWith ExitSuccess
    go ("--rule":n:xs) cfg = case parseInt n of
      Just v -> go xs cfg { cfgRule = v }
      _      -> die84 (usage "wolfram")
    go ("--start":n:xs) cfg = case parseInt n of
      Just v | v >= 0 -> go xs cfg { cfgStart = v }
      _               -> die84 (usage "wolfram")
    go ("--lines":n:xs) cfg = case parseInt n of
      Just v | v >= 0 -> go xs cfg { cfgLines = Just v }
      _               -> die84 (usage "wolfram")
    go ("--window":n:xs) cfg = case parseInt n of
      Just v | v > 0 -> go xs cfg { cfgWindow = v }
      _              -> die84 (usage "wolfram")
    go ("--move":n:xs) cfg = case parseInt n of
      Just v -> go xs cfg { cfgMove = v }
      _      -> die84 (usage "wolfram")
    go _ _ = die84 (usage "wolfram")

ruleBit :: Int -> Bool -> Bool -> Bool -> Bool
ruleBit rule a b c = testBit rule idx
  where idx = (if a then 4 else 0) + (if b then 2 else 0) + (if c then 1 else 0)

step :: Int -> Set Int -> Set Int
step rule cur
  | S.null cur = S.empty
  | otherwise  = S.fromList [i | i <- [mn-1 .. mx+1]
                               , let a = S.member (i-1) cur
                                     b = S.member i cur
                                     c = S.member (i+1) cur
                               , ruleBit rule a b c]
  where
    mn = S.findMin cur
    mx = S.findMax cur

advance :: Int -> Int -> Set Int -> Set Int
advance _ 0 s = s
advance rule n s = advance rule (n-1) (step rule s)

printWindow :: Int -> Int -> Set Int -> IO ()
printWindow win move cur = do
  let left = move - (win `div` 2)
      line = [ if S.member i cur then '*' else ' '
             | i <- [left .. left + win - 1] ]
  putStrLn line

loopPrint :: Int -> Int -> Int -> Set Int -> IO ()
loopPrint _ _ 0 _ = pure ()
loopPrint rule win n cur = do
  printWindow win 0 cur
  loopPrint rule win (n-1) (step rule cur)

loopPrintInf :: Int -> Int -> Set Int -> IO ()
loopPrintInf rule win cur = do
  printWindow win 0 cur
  loopPrintInf rule win (step rule cur)

main :: IO ()
main = do
  args <- getArgs
  cfg <- parseArgs args
  let s0 = S.singleton 0
      s1 = advance (cfgRule cfg) (cfgStart cfg) s0
      moveCur = if cfgMove cfg == 0 then s1 else S.mapMonotonic (+ cfgMove cfg) s1
  case cfgLines cfg of
    Just n  -> loopPrint (cfgRule cfg) (cfgWindow cfg) n moveCur
    Nothing -> loopPrintInf (cfgRule cfg) (cfgWindow cfg) moveCur

