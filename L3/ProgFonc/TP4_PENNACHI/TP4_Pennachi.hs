import Data.Char
import Data.List
import System.IO


data Player= O|X|B deriving(Eq,Ord)

instance Show Player where
    show :: Player -> String  
    show X = "X"
    show O = "O"
    show B = " "

type Grid = (Int,[[Player]])


next :: Player-> Player
next X = O
next O = X
next B = B

-- Partie 2

empty::Int-> Grid
empty x = (x, replicate x (replicate x B))

full::Grid -> Bool
full (_,xs) =all (/=B) (concat xs) 


diag::Grid->[Player]
diag (v,xs) = [(xs !! x) !! x| x<- [0..v-1]]
 

wins::Player-> Grid->Bool
wins x (i,g) | all (==x) (diag (i,g)) =True
             | all (==x) (diag (i,reverse g)) =True 
             | any (==True) [all (==x) v|v<-g]  =True
             | any (==True) [all (==x) v|v<-transpose g] =True
             | otherwise =False


won:: Grid->Bool
won g= wins X g || wins O g


-- Partie 3

insVert::[String]->[String]
insVert[]=[]
insVert[x]=[x]
insVert (x:xs)= [x,"|"] ++ insVert xs

showRow::[Player]->[String]
showRow []=[]
showRow xs= insVert[show x| x<-xs]



insHoriz::Int->[String]
insHoriz i=replicate i"---" ++ replicate (i-1) "-"


showGrid::Grid->IO()
showGrid (i,g)= [showRow (g !! 0) ++insHoriz i ++showRow (g !! 1) ++ insHoriz i ++ showRow(g !! 2)]