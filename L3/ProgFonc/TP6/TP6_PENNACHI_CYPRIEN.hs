import Text.XHtml (base, background)
data Op = Add | Sub | Mul | Div

instance Show Op where
    show :: Op -> String  
    show Add = " + "
    show Sub = " - "
    show Mul = " * "
    show Div = " / "

valid :: Op -> Int -> Int -> Bool
valid Add x y = x <= y
valid Sub x y = x > y
valid Mul x y = x /= 1 && y /= 1 && x <= y
valid Div x y = y /= 1 && x `mod` y == 0

apply :: Op -> Int -> Int -> Int
apply Add a b =a + b
apply Sub a b = a - b
apply Mul a b = a * b
apply Div a b = a`div`b

{-
Partie II
-}


data Expr = Val Int | App Op Expr Expr


instance Show Expr where
    show :: Expr -> String  
    show (Val a)= show a 
    show (App v a b)  =  voir a ++ show v ++ voir b
        where
      voir (Val a) = show a
      voir b = "(" ++ show b ++ ")"


values:: Expr -> [Int]
values (Val a)=[a]
values (App v a b) = values a ++ values b


eval :: Expr -> [Int] 
eval (Val x) = [x | x>0]
eval (App op e1 e2) = [ apply op x y | x <- eval e1, y <- eval e2, valid op x y]

{-
Partie 3
-}

interleave :: a -> [a] -> [[a]]
interleave x [] = [[x]]
interleave x (y:ys) = (x : y : ys) : map (y :) (interleave x ys)

perms :: [a] -> [[a]]
perms [] = [[]]
perms (x:xs) = concat [ interleave x ys | ys <- perms xs ]



subs :: [a] -> [[a]]
subs [] = [[]]
subs (x:xs) = map (x:) (subs xs) ++ subs xs
{-
La fonction subs prend un tableau en parametre 

renvoie toutes les listes possibles à partir des éléments de liste
-}

choices :: [a] -> [[a]]
choices  = concat.map perms.subs

{-
Partie IV
-}



solution :: Expr -> [Int] -> Int -> Bool
solution op as b = elem (values op) (choices as) && eval op == [b]

e = App Mul (App Add (Val 1) (Val 50)) (App Sub (Val 25) (Val 10))

{-
Partie V
-}



split::[a]->[([a],[a])]
split [] = []
split [_] = []
split (x:xs) = ([x], xs) : [(x : ls, rs) | (ls, rs) <- split xs]

exprs :: [Int] -> [Expr]
exprs [] = []
exprs [n] = [Val n]
exprs ns =
  [e | (ls, rs) <- split ns, l <- exprs ls, r <- exprs rs, e <- combine l r]

combine :: Expr -> Expr -> [Expr]
combine l r = [App o l r | o <- ops]

ops :: [Op]
ops = [Add, Sub, Mul, Div]

solutions :: [Int] -> Int -> [Expr]
solutions ns n = [e | ns' <- choices ns, e <- exprs ns', eval e == [n]]


main :: IO ()
main = print (solutions [1, 3, 7, 10, 25, 50] 765)