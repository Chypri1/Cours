--PENNACHI Cyprien
import System.IO

-- Partie 1

getCh:: IO Char
getCh = do
    hSetEcho stdin False 
    c <- getChar 
    hSetEcho stdin True 
    return c

sgetLine:: IO String
sgetLine = do
    c <- getCh 
    case c of 
        '\n' -> return ""
        _ -> do 
            putChar '-'
            fmap(c:)  sgetLine


match::String -> String ->String 
match [_] [] = []
match [] [_] = []
match xs ys = [if elem x ys then x else '-' | x <- xs]


play :: String -> IO ()
play word = 
   do putStr "? "
      guess <- getLine
      if guess == word then
         putStrLn "You got it!"
      else
         do putStrLn (match word guess)
            play word

hangman :: IO ()
hangman = do putStrLn "Think of a word: "
             word <- sgetLine
             putStrLn "Try to guess it:"
             play word



-- Partie 2
    
type Matf = Int -> Int ->(Bool,Int)

exemple :: Matf 
exemple i j | i<=6 && i>=1 && j<= 5 && j>= 1 =(True,2*i +j)
            |otherwise = (False,0)

identite4x4 :: Matf
identite4x4 i j| i==j && i<=4 && i>=1 && j<=4 && j>=1 =(True,1)
               | i<=4 && i>=1 && j<=4 && j>=1 =(True,0)
               |otherwise = (False,0)




nbLines :: Matf -> Int
nbLines mat = length $ takeWhile (\i -> fst(mat 1 i)) [1..]

nbCols :: Matf -> Int
nbCols mat = length $ takeWhile (\i -> fst(mat 1 i)) [1..]

dims :: Matf -> (Int, Int)
dims mat = (nbLines mat, nbCols mat)

cmpDims::Matf ->Matf -> Bool
cmpDims a b = dims a == dims b 


add :: Matf -> Matf -> Matf
add mat1 mat2 |not (cmpDims mat1 mat2)  = error "Les matrices ne sont pas de même dimension !"
              | otherwise = \i j -> let (b1, x1) = mat1 i j 
                                        (b2, x2) = mat2 i j
                                    in (b1 || b2, x1 + x2)


identite6x5 :: Matf
identite6x5 i j | i == j && i >= 1 && i <= 6 && j >= 1 && j <= 5 = (True, 1)
                | i >= 1 && i <= 6 && j >= 1 && j <= 5 =(True, 0)
                | otherwise = (False,0)


{-

ligne 3:
on veut ajouter deux matrices et mettre le résultat dans mat mais ca ne fonctionne pas car les matrices ne sont pas de mêmes tailles

-}

