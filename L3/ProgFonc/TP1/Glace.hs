data Parfum =Chocolat | Vanille | Framboise

prixParfum:: Parfum  -> Float 
prixParfum Chocolat =1.5
prixParfum Vanille =1.2
prixParfum Framboise =1.4

data Glace = UneBoule Parfum |DeuxBoules Parfum Parfum | TroisBoules Parfum Parfum Parfum

prixGlace :: Glace -> Float

prixGlace (UneBoule p) = 1.1 + prixParfum p
prixGlace (DeuxBoules p1 p2) = 1.15 + sum (map prixParfum [p1, p2])
prixGlace (TroisBoules p1 p2 p3) = 1.2 + sum (map prixParfum [p1, p2, p3])