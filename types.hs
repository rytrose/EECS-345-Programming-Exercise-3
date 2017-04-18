data NestedList a = Element a | SubList [NestedList a] deriving (Show)

flatten :: [NestedList a] -> [NestedList a]
flatten l =
  if (null l)
    then
      []
  else if (isElement (head l))
    then
      (head l) : (flatten (tail l))
  else
    if (null (getList (head l)))
      then
        (flatten (tail l))
    else
      (merge (flatten (getList (head l))) (flatten (tail l)))

myreverse :: [NestedList a] -> [NestedList a]
myreverse l =
  if (null l)
    then
      []
    else
      if (isSubList (last l))
        then
          (SubList (myreverse (getList (last l)))) : (myreverse (init l))
        else
          (last l) : (myreverse (init l))

getSlHead (SubList sl) = (head sl)
getSlTail (SubList sl) = (tail sl)
getSlInit (SubList sl) = (init sl)
getSlLast (SubList sl) = (last sl)

isElement (Element _) = True
isElement _ = False
isSubList (SubList _) = True
isSubList _ = False

getList :: NestedList a -> [NestedList a]
getList (SubList a) = a

merge :: [NestedList a] -> [NestedList a] -> [NestedList a]
merge nl1 nl2 =
  if (null nl1)
    then
      nl2
  else
    (head nl1) : (merge (tail nl1) nl2)
