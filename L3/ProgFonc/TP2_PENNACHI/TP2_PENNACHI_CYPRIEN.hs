import Distribution.Simple.Utils (xargs)
import Language.Haskell.TH (safe)
import Data.Time.Format.ISO8601 (yearFormat)

-- exercice 1

-- Paire
paire:: Int-> Bool
paire 0= True
paire a= impaire (a-1)


--Impaire
impaire:: Int-> Bool
impaire 0=False
impaire n =paire (n-1)

--insert 
insert:: Ord a=> a-> [a] -> [a]
insert a []=[a]
insert a (n:ns) | a>n = n : insert a ns -- [n] ++ insert a ns 
                | otherwise = [a,n] ++ ns

-- isort
isort:: Ord a=> [a] -> [a]
isort []=[]
isort (n:ns) = insert n (isort ns)


-- exercice 2

--halve 
halve::[a]->([a],[a])
halve []=([],[])
halve n = (take l n,drop l n) where l=length n `div` 2 

--merge 

merge::Ord a => [a] -> [a] -> [a]
merge [][]=[]
merge [a][]=[a]
merge[][a]=[a]
merge (x:xs) (y:ys) |x<y = [x] ++ merge xs (y:ys) 
                    | otherwise =[y]++ merge (x:xs) ys

--msort
msort::Ord a => [a] -> [a] 
msort []=[]
msort a = merge(msort x) (msort y) where (x,y) =halve a 


--exercice 3

data Prop = Const Bool
            | Var Char
            | Not Prop
            | And Prop Prop
            | Imply Prop Prop

p1 :: Prop
p1 = And (Var 'A') (Not (Var 'A'))

p2 :: Prop
p2 = Imply (And (Var 'A') (Var 'B')) (Var 'A') 

p3 :: Prop
p3 = Imply (Var 'A') (And (Var 'A') (Var 'B'))

p4 :: Prop
p4 = Imply (And (Var 'A') (Imply (Var 'A') (Var 'B'))) (Var 'B')


type Assoc k v = [(k, v)] 
type Subst = Assoc Char Bool 

find :: Eq k => k-> Assoc k v -> v
find k xs = head [b | (a,b)<-xs, a==k]

--eval
eval :: Subst ->Prop ->Bool
eval _ (Const x)=x
eval v (Var c) =find c v
eval v (Not c) =not (eval v c)
eval p(And v c) = eval p v && eval p c
eval p(Imply v c)= not (eval p v) || eval p c

--rmdups
rmdups :: Eq a => [a] -> [a]
rmdups [] = []
rmdups (x:xs) = x : filter (/= x) (rmdups xs)

--vars

vars :: Prop -> [Char]
vars p = rmdups (vars2 p)

--vars2 
vars2 ::Prop ->[Char]
vars2 (Var x)=[x]
vars2 (Not x)=vars2 x
vars2 (And x y)= vars2 x ++ vars2 y
vars2 (Imply x y)= vars2 x ++ vars2 y

--bools

bools::Int -> [[Bool]]
bools 0=[[]]
bools n = map (False :) bss ++ map (True :) bss where bss = bools (n-1)

--substs
substs :: Prop -> [Subst]
substs p = map (zip vs) (bools (length vs))where vs = vars p

--isTaut

isTaut::Prop->Bool
isTaut p=and( [eval b p |b <- substs p ])