{-
** EPITECH PROJECT, 2025
** pushswap_checker
** File description:
** Push_swap operations implementation
-}

module Operations where

-- Data type for two stacks
data Stacks = Stacks [Int] [Int] deriving (Show, Eq)

-- sa: swap the first two elements of l_a
sa :: Stacks -> Stacks
sa (Stacks [] lb) = Stacks [] lb
sa (Stacks [x] lb) = Stacks [x] lb
sa (Stacks (x:y:xs) lb) = Stacks (y:x:xs) lb

-- sb: swap the first two elements of l_b
sb :: Stacks -> Stacks
sb (Stacks la []) = Stacks la []
sb (Stacks la [x]) = Stacks la [x]
sb (Stacks la (x:y:xs)) = Stacks la (y:x:xs)

-- sc: sa and sb at the same time
sc :: Stacks -> Stacks
sc stacks = sb (sa stacks)

-- pa: take the first element from l_b and move it to the first position on l_a
pa :: Stacks -> Stacks
pa (Stacks la []) = Stacks la []
pa (Stacks la (x:xs)) = Stacks (x:la) xs

-- pb: take the first element from l_a and move it to the first position on l_b
pb :: Stacks -> Stacks
pb (Stacks [] lb) = Stacks [] lb
pb (Stacks (x:xs) lb) = Stacks xs (x:lb)

-- ra: rotate l_a toward the beginning, the first element becomes the last
ra :: Stacks -> Stacks
ra (Stacks [] lb) = Stacks [] lb
ra (Stacks (x:xs) lb) = Stacks (xs ++ [x]) lb

-- rb: rotate l_b toward the beginning, the first element becomes the last
rb :: Stacks -> Stacks
rb (Stacks la []) = Stacks la []
rb (Stacks la (x:xs)) = Stacks la (xs ++ [x])

-- rr: ra and rb at the same time
rr :: Stacks -> Stacks
rr stacks = rb (ra stacks)

-- rra: rotate l_a toward the end, the last element becomes the first
rra :: Stacks -> Stacks
rra (Stacks [] lb) = Stacks [] lb
rra (Stacks la lb) = case reverse la of
    [] -> Stacks [] lb
    (x:xs) -> Stacks (x:reverse xs) lb

-- rrb: rotate l_b toward the end, the last element becomes the first
rrb :: Stacks -> Stacks
rrb (Stacks la []) = Stacks la []
rrb (Stacks la lb) = case reverse lb of
    [] -> Stacks la []
    (x:xs) -> Stacks la (x:reverse xs)

-- rrr: rra and rrb at the same time
rrr :: Stacks -> Stacks
rrr stacks = rrb (rra stacks)

-- Apply operation by name
applyOperation :: String -> Stacks -> Maybe Stacks
applyOperation "sa"  stacks = Just (sa stacks)
applyOperation "sb"  stacks = Just (sb stacks)
applyOperation "sc"  stacks = Just (sc stacks)
applyOperation "pa"  stacks = Just (pa stacks)
applyOperation "pb"  stacks = Just (pb stacks)
applyOperation "ra"  stacks = Just (ra stacks)
applyOperation "rb"  stacks = Just (rb stacks)
applyOperation "rr"  stacks = Just (rr stacks)
applyOperation "rra" stacks = Just (rra stacks)
applyOperation "rrb" stacks = Just (rrb stacks)
applyOperation "rrr" stacks = Just (rrr stacks)
applyOperation _     _      = Nothing

-- Apply a sequence of operations
applyOperations :: [String] -> Stacks -> Maybe Stacks
applyOperations [] stacks = Just stacks
applyOperations (op:ops) stacks = do
    newStacks <- applyOperation op stacks
    applyOperations ops newStacks

-- Check if the result is sorted (l_a sorted, l_b empty)
isSorted :: Stacks -> Bool
isSorted (Stacks la []) = isSortedList la
isSorted _ = False

-- Check if a list is sorted in ascending order
isSortedList :: [Int] -> Bool
isSortedList [] = True
isSortedList [_] = True
isSortedList (x:y:xs) = x <= y && isSortedList (y:xs)