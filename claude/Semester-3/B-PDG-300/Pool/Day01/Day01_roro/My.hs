-- EPITECH PROJECT, 2025
-- Day01 - A Gentle Introduction to Functional Programming
-- File description:
-- My.hs - Implementation of basic Haskell functions

-- Step 1 - Basic functions

-- Task 01: mySucc - returns the successor of an Int
mySucc :: Int -> Int
mySucc x = x + 1

-- Task 02: myIsNeg - returns True if Int is negative, False otherwise
myIsNeg :: Int -> Bool
myIsNeg x = x < 0

-- Task 03: myAbs - returns the absolute value of an Int
myAbs :: Int -> Int
myAbs x
    | x < 0     = -x
    | otherwise = x

-- Task 04: myMin - returns the minimum of two Ints
myMin :: Int -> Int -> Int
myMin x y
    | x <= y    = x
    | otherwise = y

-- Task 05: myMax - returns the maximum of two Ints
myMax :: Int -> Int -> Int
myMax x y
    | x >= y    = x
    | otherwise = y

-- Step 2 - Tuples

-- Task 06: myTuple - creates a tuple from two arguments
myTuple :: a -> b -> (a, b)
myTuple x y = (x, y)

-- Task 07: myTruple - creates a tuple from three arguments
myTruple :: a -> b -> c -> (a, b, c)
myTruple x y z = (x, y, z)

-- Task 08: myFst - returns the first element of a tuple
myFst :: (a, b) -> a
myFst (x, _) = x

-- Task 09: mySnd - returns the second element of a tuple
mySnd :: (a, b) -> b
mySnd (_, y) = y

-- Task 10: mySwap - swaps the elements of a tuple
mySwap :: (a, b) -> (b, a)
mySwap (x, y) = (y, x)

-- Step 3 - Simple lists

-- Task 11: myHead - returns the first element of a list
myHead :: [a] -> a
myHead []     = error "Empty list"
myHead (x:_)  = x

-- Task 12: myTail - returns the list without its first element
myTail :: [a] -> [a]
myTail []     = error "Empty list"
myTail (_:xs) = xs

-- Task 13: myLength - returns the number of elements in a list
myLength :: [a] -> Int
myLength []     = 0
myLength (_:xs) = 1 + myLength xs

-- Task 14: myNth - returns the element at index N in the list
myNth :: [a] -> Int -> a
myNth [] _         = error "Index too large"
myNth (x:_) 0      = x
myNth (_:xs) n
    | n < 0        = error "Negative index"
    | otherwise    = myNth xs (n - 1)

-- Task 15: myTake - returns a list with the Nth first elements
myTake :: Int -> [a] -> [a]
myTake _ []         = []
myTake n (x:xs)
    | n <= 0       = []
    | otherwise    = x : myTake (n - 1) xs

-- Task 16: myDrop - returns a list without the N first elements
myDrop :: Int -> [a] -> [a]
myDrop _ []         = []
myDrop n xs
    | n <= 0       = xs
myDrop n (_:xs)    = myDrop (n - 1) xs

-- Task 17: myAppend - appends the second list to the first one
myAppend :: [a] -> [a] -> [a]
myAppend [] ys     = ys
myAppend (x:xs) ys = x : myAppend xs ys

-- Task 18: myReverse - reverses a list
myReverse :: [a] -> [a]
myReverse []     = []
myReverse (x:xs) = myAppend (myReverse xs) [x]

-- Task 19: myInit - returns all elements except the last one
myInit :: [a] -> [a]
myInit []     = error "Empty list"
myInit [_]    = []
myInit (x:xs) = x : myInit xs

-- Task 20: myLast - returns the last element of a list
myLast :: [a] -> a
myLast []     = error "Empty list"
myLast [x]    = x
myLast (_:xs) = myLast xs

-- Task 21: myZip - creates a list of tuples from two lists
myZip :: [a] -> [b] -> [(a, b)]
myZip [] _          = []
myZip _ []          = []
myZip (x:xs) (y:ys) = (x, y) : myZip xs ys

-- Task 22: myUnzip - creates a tuple of lists from a list of tuples
myUnzip :: [(a,b)] -> ([a], [b])
myUnzip []         = ([], [])
myUnzip ((x,y):zs) = (x:xs, y:ys)
    where (xs, ys) = myUnzip zs

-- Step 4 - Advanced lists

-- Task 23: myMap - applies a function to every element of a list
myMap :: (a -> b) -> [a] -> [b]
myMap _ []     = []
myMap f (x:xs) = f x : myMap f xs

-- Task 24: myFilter - filters a list based on a predicate
myFilter :: (a -> Bool) -> [a] -> [a]
myFilter _ []     = []
myFilter p (x:xs)
    | p x        = x : myFilter p xs
    | otherwise  = myFilter p xs

-- Task 25: myFoldl - left fold (reduce from left to right)
myFoldl :: (b -> a -> b) -> b -> [a] -> b
myFoldl _ acc []     = acc
myFoldl f acc (x:xs) = myFoldl f (f acc x) xs

-- Task 26: myFoldr - right fold (reduce from right to left)
myFoldr :: (a -> b -> b) -> b -> [a] -> b
myFoldr _ acc []     = acc
myFoldr f acc (x:xs) = f x (myFoldr f acc xs)

-- Task 27: myPartition - splits a list based on a predicate
myPartition :: (a -> Bool) -> [a] -> ([a], [a])
myPartition _ []     = ([], [])
myPartition p (x:xs)
    | p x           = (x:trues, falses)
    | otherwise     = (trues, x:falses)
    where (trues, falses) = myPartition p xs

-- Task 28: myQuickSort - sorts a list using quicksort algorithm
myQuickSort :: (a -> a -> Bool) -> [a] -> [a]
myQuickSort _ []     = []
myQuickSort p (x:xs) = myAppend (myAppend smaller [x]) larger
    where
        smaller = myQuickSort p (myFilter (p x) xs)
        larger  = myQuickSort p (myFilter (not . p x) xs)