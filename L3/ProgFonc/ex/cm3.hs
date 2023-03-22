import Text.XHtml (base)

-- somme des carrés des éléments pair de la liste 
sumsqreven::[Int] -> Int
--sumsqreven [] =0
--sumsqreven xs= sum(map (^2) (filter even xs ))
sumsqreven = sum . map(^2) . filter even


--addition des éléments d'une liste 
summ::Num a => [a]->a
--summ =foldr (+) 0
summ =foldl (+) 0


--longueur d'un liste
length ::[a]->Int
--length[]=0
--length (x:xs) = 1 + length xs

--expression curryfiée

--length =foldr (\_ v -> 1+v) 0
length = foldl (\ v _ -> 1+v ) 0


data Tree a = Leaf a |Node (Tree a) a (Tree a)

--          fonction  val   Arbre    val
foldrTree::(a->b->b) ->b -> Tree a -> b
foldrTree f ac (Leaf x) =  f x ac
foldrTree f ac (Node tg x td)=foldrTree f ( f x(foldrTree f ac td )) tg 

