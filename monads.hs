import Data.Maybe

appendIf :: a -> Maybe [a] -> (a -> Bool) -> Maybe [a]
appendIf x Nothing check = Nothing
appendIf x ml check =
  if (check x) then
    Just (x : (fromJust ml))
  else
    Nothing

check :: Integer -> Bool
check x =
  if (x `mod` 2) == 0 then
    True
  else
    False

checklist :: [a] -> (a -> Bool) -> Maybe [a]
checklist x check =
  if (null x) then
    Just ([])
  else
    appendIf (head x) (checklist (tail x) check) check
