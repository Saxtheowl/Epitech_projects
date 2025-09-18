-- EPITECH PROJECT, 2024
-- Day01 PDG - Haskell Introduction
-- File description:
-- My.hs - Complete implementation of 28 tasks

-- Step 1: Basic Functions (Tasks 1-5)

-- Task 01: Successor
mySucc :: Int -> Int
mySucc x = x + 1

-- Task 02: Is Negative
myIsNeg :: Int -> Bool
myIsNeg x = x < 0

-- Task 03: Absolute Value
myAbs :: Int -> Int
myAbs x
    | x < 0     = -x
    | otherwise = x

-- Task 04: Minimum
myMin :: Int -> Int -> Int
myMin x y
    | x <= y    = x
    | otherwise = y

-- Task 05: Maximum
myMax :: Int -> Int -> Int
myMax x y
    | x >= y    = x
    | otherwise = y

-- Step 2: Tuples (Tasks 6-10)

-- Task 06: Create Tuple
myTuple :: a -> b -> (a, b)
myTuple x y = (x, y)

-- Task 07: Create Triple
myTruple :: a -> b -> c -> (a, b, c)
myTruple x y z = (x, y, z)

-- Task 08: First element of tuple
myFst :: (a, b) -> a
myFst (x, _) = x

-- Task 09: Second element of tuple
mySnd :: (a, b) -> b
mySnd (_, y) = y

-- Task 10: Swap tuple elements
mySwap :: (a, b) -> (b, a)
mySwap (x, y) = (y, x)

-- Step 3: Simple Lists (Tasks 11-22)

-- Task 11: Head of list
myHead :: [a] -> a
myHead []     = error "Empty list"
myHead (x:_)  = x

-- Task 12: Tail of list
myTail :: [a] -> [a]
myTail []     = error "Empty list"
myTail (_:xs) = xs

-- Task 13: Length of list
myLength :: [a] -> Int
myLength []     = 0
myLength (_:xs) = 1 + myLength xs

-- Task 14: Nth element of list
myNth :: [a] -> Int -> a
myNth [] _       = error "Index out of bounds"
myNth (x:_) 0    = x
myNth (_:xs) n
    | n < 0      = error "Negative index"
    | otherwise  = myNth xs (n - 1)

-- Task 15: Take first n elements
myTake :: Int -> [a] -> [a]
myTake 0 _       = []
myTake _ []      = []
myTake n (x:xs)
    | n < 0      = []
    | otherwise  = x : myTake (n - 1) xs

-- Task 16: Drop first n elements
myDrop :: Int -> [a] -> [a]
myDrop 0 xs      = xs
myDrop _ []      = []
myDrop n (_:xs)
    | n < 0      = []
    | otherwise  = myDrop (n - 1) xs

-- Task 17: Append two lists
myAppend :: [a] -> [a] -> [a]
myAppend [] ys     = ys
myAppend (x:xs) ys = x : myAppend xs ys

-- Task 18: Reverse a list
myReverse :: [a] -> [a]
myReverse []     = []
myReverse (x:xs) = myAppend (myReverse xs) [x]

-- Task 19: Init - all elements except last
myInit :: [a] -> [a]
myInit []     = error "Empty list"
myInit [_]    = []
myInit (x:xs) = x : myInit xs

-- Task 20: Last element of list
myLast :: [a] -> a
myLast []     = error "Empty list"
myLast [x]    = x
myLast (_:xs) = myLast xs

-- Task 21: Zip two lists
myZip :: [a] -> [b] -> [(a, b)]
myZip [] _          = []
myZip _ []          = []
myZip (x:xs) (y:ys) = (x, y) : myZip xs ys

-- Task 22: Unzip list of tuples
myUnzip :: [(a,b)] -> ([a], [b])
myUnzip []         = ([], [])
myUnzip ((x,y):xs) = (x : fst rest, y : snd rest)
  where rest = myUnzip xs

-- Step 4: Advanced Lists (Tasks 23-28)

-- Task 23: Map function over list
myMap :: (a -> b) -> [a] -> [b]
myMap _ []     = []
myMap f (x:xs) = f x : myMap f xs

-- Task 24: Filter elements by predicate
myFilter :: (a -> Bool) -> [a] -> [a]
myFilter _ []     = []
myFilter p (x:xs)
    | p x         = x : myFilter p xs
    | otherwise   = myFilter p xs

-- Task 25: Fold left
myFoldl :: (b -> a -> b) -> b -> [a] -> b
myFoldl _ acc []     = acc
myFoldl f acc (x:xs) = myFoldl f (f acc x) xs

-- Task 26: Fold right
myFoldr :: (a -> b -> b) -> b -> [a] -> b
myFoldr _ acc []     = acc
myFoldr f acc (x:xs) = f x (myFoldr f acc xs)

-- Task 27: Partition list by predicate
myPartition :: (a -> Bool) -> [a] -> ([a], [a])
myPartition _ []     = ([], [])
myPartition p (x:xs)
    | p x           = (x : fst rest, snd rest)
    | otherwise     = (fst rest, x : snd rest)
  where rest = myPartition p xs

-- Task 28: Quick sort with custom comparator
myQuickSort :: (a -> a -> Bool) -> [a] -> [a]
myQuickSort _ []     = []
myQuickSort cmp (x:xs) = 
    myAppend (myAppend (myQuickSort cmp smaller) [x]) (myQuickSort cmp larger)
  where
    smaller = myFilter (\y -> cmp y x) xs
    larger = myFilter (\y -> not (cmp y x)) xs