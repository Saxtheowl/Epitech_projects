data Tree a = Empty | Node (Tree a) a (Tree a) deriving (Show)

addInTree :: Ord a => a -> Tree a -> Tree a
addInTree x Empty = Node Empty x Empty
addInTree x (Node left val right)
  | x < val = Node (addInTree x left) val right
  | otherwise = Node left val (addInTree x right)

instance Functor Tree where
  fmap _ Empty = Empty
  fmap f (Node left val right) = Node (fmap f left) (f val) (fmap f right)

listToTree :: Ord a => [a] -> Tree a
listToTree = foldr addInTree Empty

treeToList :: Tree a -> [a]
treeToList Empty = []
treeToList (Node left val right) = treeToList left ++ [val] ++ treeToList right

treeSort :: Ord a => [a] -> [a]
treeSort = treeToList . listToTree

instance Foldable Tree where
  foldr _ acc Empty = acc
  foldr f acc (Node left val right) = foldr f (f val (foldr f acc right)) left