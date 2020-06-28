-- Implementations of common functions using folds

max' :: (Ord a) => [a] -> a
max' = foldr1 (\x acc -> if x > acc then x else acc) 

reverse' :: [a] -> [a]
reverse' = foldl (flip (:)) []

elem' :: (Eq a) => a -> [a] -> Bool
elem' item = foldr (\x acc -> acc || x == item) False

product' :: (Num a) => [a] -> a
product' = foldr (*) 1

filter' :: (a -> Bool) -> [a] -> [a]
filter' p = foldr (\x acc -> if p x then x : acc else acc) []

mapFoldr :: (a -> b) -> [a] -> [b]
-- mapFoldr f = foldr (\x acc -> f x : acc) []
mapFoldr f = foldr ((:) . f) []

mapFoldl :: (a -> b) -> [a] -> [b]
mapFoldl f = foldl (\acc x -> acc ++ [f x]) []
