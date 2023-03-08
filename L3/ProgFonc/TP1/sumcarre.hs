-- res = 338350
sumcarre :: Int
sumcarre = sum[ x^2 | x <-[1..100] ]


replic :: Int -> a -> [a]
replic a b = [b | x<-[1..a]]

pyths :: Int -> [(Int,Int,Int)]
pyths n = [(a,b,c)| a<-[1..n],b<-[1..n],c<-[1..n],n==c|| n==b|| n==a ,a^2 + b^2 == c^2 || c^2 + b^2 == a^2 ||c^2 + a^2 == b^2]