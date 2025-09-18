import System.Environment
import System.Exit

myElem :: Eq a => a -> [a] -> Bool
myElem _ [] = False
myElem x (y:ys) = x == y || myElem x ys

safeDiv :: Int -> Int -> Maybe Int
safeDiv _ 0 = Nothing
safeDiv x y = Just (x `div` y)

safeNth :: [a] -> Int -> Maybe a
safeNth [] _ = Nothing
safeNth (x:_) 0 = Just x
safeNth (_:xs) n
  | n < 0 = Nothing
  | otherwise = safeNth xs (n - 1)

safeSucc :: Maybe Int -> Maybe Int
safeSucc Nothing = Nothing
safeSucc (Just x) = Just (x + 1)

myLookup :: Eq a => a -> [(a,b)] -> Maybe b
myLookup _ [] = Nothing
myLookup key ((k,v):xs)
  | key == k = Just v
  | otherwise = myLookup key xs

maybeDo :: (a -> b -> c) -> Maybe a -> Maybe b -> Maybe c
maybeDo _ Nothing _ = Nothing
maybeDo _ _ Nothing = Nothing
maybeDo f (Just x) (Just y) = Just (f x y)

readInt :: [Char] -> Maybe Int
readInt str = case reads str of
  [(x, "")] -> Just x
  _ -> Nothing

getLineLength :: IO Int
getLineLength = do
  line <- getLine
  return (length line)

printAndGetLength :: String -> IO Int
printAndGetLength str = do
  putStrLn str
  return (length str)

printBox :: Int -> IO ()
printBox n
  | n <= 0 = return ()
  | otherwise = do
      putStrLn (replicate (n * 2) '+')
      mapM_ (\_ -> putStrLn ("|" ++ replicate (n * 2 - 2) ' ' ++ "|")) [1..(n-2)]
      putStrLn (replicate (n * 2) '+')

concatLines :: Int -> IO String
concatLines n
  | n <= 0 = return ""
  | otherwise = do
      lines <- mapM (\_ -> getLine) [1..n]
      return (concat lines)

getInt :: IO (Maybe Int)
getInt = do
  line <- getLine
  return (readInt line)

parseArgs :: [String] -> Maybe (Int, String, Int)
parseArgs [a, op, b] = do
  x <- readInt a
  y <- readInt b
  return (x, op, y)
parseArgs _ = Nothing

performOp :: Int -> String -> Int -> Maybe Int
performOp x "+" y = Just (x + y)
performOp x "-" y = Just (x - y)
performOp x "*" y = Just (x * y)
performOp x "/" y = safeDiv x y
performOp x "%" y = if y == 0 then Nothing else Just (x `mod` y)
performOp _ _ _ = Nothing

main :: IO ()
main = do
  args <- getArgs
  case parseArgs args of
    Nothing -> exitWith (ExitFailure 84)
    Just (x, op, y) -> case performOp x op y of
      Nothing -> exitWith (ExitFailure 84)
      Just result -> print result