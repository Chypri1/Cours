inverse :: [a]-> [a]
inverse []=[]
inverse(x:xs) =(inverse xs) ++ [x] 


isPalindrome:: Eq a => [a] -> Bool
isPalindrome a = a == (inverse a)

doPalimdrome:: [a] -> [a]
doPalimdrome[]=[]
doPalimdrome [a]=[a]
doPalimdrome a = a ++ inverse(init a) 