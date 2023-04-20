
import Data.Char


let2int::Char->Int
let2int a= ord a - ord 'A'


int2let:: Int->Char
int2let x = chr(x +ord 'A')

shift:: Int ->Char ->Char
shift a b = int2let(mod (let2int b + a) 26)


cypher::Int->String->String
cypher a xs= [ shift a (toUpper v) | v<-xs, isLetter v]


--Partie 2
-- pouventage entre deux nombres
percent::Int->Int->Float
percent a b= (fromIntegral a/ fromIntegral b)*100


count::Char->String->Int
count a xs = sum[i |let i=1 ,xs<-xs,a==xs ]


freqs::String->[Float]
freqs a = [percent (count v a)  (length a)|v<-['A'..'Z']] 

--PArtie 3

table :: [Float]
table = [9.42,1.02,2.64,3.39,15.87,0.95,1.04,0.77,8.41,0.89,0.001,5.34,3.24,7.15,5.14,2.86,1.06,6.46,7.90,7.26,6.24,2.15,0.001,0.30,0.24,0.32]

chisqr::[Float]->[Float]->Float
chisqr os es = sum[ (o-e)^2/e | (o,e)<-zip os es]

rotate::Int ->[a]->[a]
rotate a xs = drop a xs ++ take a xs


positions::Eq a=> a -> [a] ->[Int]
positions a b= [x | (x,y)<-zip [0..] b,a==y ]


crack :: String -> String 
crack xs = cypher (-factor) xs 
    where factor = head (positions (minimum chitab) chitab) 
          chitab = [chisqr (rotate n table' ) table | n <- [0..25]]
          table' = freqs xs