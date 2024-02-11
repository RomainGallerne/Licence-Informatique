type prop =
  | Symb of string
  | Top
  | Bot
  | Not of prop
  | And of prop * prop
  | Or of prop * prop
  | Imp of prop * prop
  | Equ of prop * prop;;

(*Question 1*)

(*a∧b ↔ ¬a∨b*)
let f1 = Equ(And(Symb "a", Symb "b"),Or(Not(Symb "a"), Symb "b"))

(*¬(a ∧ ¬b) ∨ ¬(a → b)*)
let f2 = Or (Not(And(Symb "a", Not(Symb "b"))),Not(Imp(Symb "a", Symb "b")))

(*¬(a → a ∨ b) ∧ ¬¬(a ∧ (b ∨ ¬c))*)
let f3 = And (Not(Imp(Symb "a", Or(Symb "a", Symb "b"))),Not(Not(And(Symb "a",Or(Symb "b", Not(Symb "c"))))))

(*(¬a ∨ b ∨ d) ∧ (¬d ∨ c) ∧ (c ∨ a) ∧ (¬c ∨ b) ∧ (¬c ∨ ¬b) ∧ (¬b ∨ d)*)
let f4 = 
  And(
    And(
      And(
        And(
          And(
            Or(
              Or(
                Not(Symb "a"),
                Symb "b"
              ),
              Symb "d"
            ),
            Or(
              Not(Symb "d"),
              Symb "c"
            )
          ),
          Or(
            Symb "c", 
            Symb "a"
          )
        ),
        Or(
          Not(Symb "c"),
          Symb "b"
        )
      ),
      Or(
        Not(Symb "c"),
        Not(Symb "b")
      )
    ),
    Or(
      Not(Symb "b"),
      Symb "d"
    )
  )

(*Question 2*)
let rec nbc : prop -> int = function
  | Symb s -> 0
  | Top -> 0
  | Bot -> 0
  | Not(g) -> 1+nbc(g)
  | And(g,h) -> 1+nbc(g)+nbc(h)
  | Or(g,h) -> 1+nbc(g)+nbc(h)
  | Imp(g,h) -> 1+nbc(g)+nbc(h)
  | Equ (g,h) -> 1+nbc(g)+nbc(h);;

(*Question 3*)
let max (a,b) =
  if(a>b) then a else b;;

let rec prof : prop -> int = function
  | Symb s -> 0
  | Top -> 0
  | Bot -> 0
  | Not(g) -> 1+prof(g)
  | And(g,h) -> 1+max(prof(g),prof(h))
  | Or(g,h) -> 1+max(prof(g),prof(h))
  | Imp(g,h) -> 1+max(prof(g),prof(h))
  | Equ (g,h) -> 1+max(prof(g),prof(h));;

(*Question 4*)
let rec ajoutSiAbsent e l =
  match l with
  | [] -> [e]
  | hd::tl when hd=e -> l
  | hd::tl -> hd::(ajoutSiAbsent e tl);;

let rec union l1 l2 =
  match l1 with
  | [] -> l2
  | hd::tl -> union tl (ajoutSiAbsent hd l2);;

let rec sp f =
  let list = [] in
  match f with
  | Symb s -> (ajoutSiAbsent s list)
  | Top -> list
  | Bot -> list
  | Not(g) -> (sp g)
  | And(g,h) -> (union (sp g) (sp h))
  | Or(g,h) -> (union (sp g) (sp h))
  | Imp(g,h) -> (union (sp g) (sp h))
  | Equ (g,h) -> (union (sp g) (sp h));;

(*Question 5*)
let rec affiche f =
  match f with
  | Symb s -> s
  | Top -> "T"
  | Bot -> "⊥"
  | Not(g) -> "¬"^(affiche g)
  | And(g,h) -> "("^(affiche g)^"∧"^(affiche h)^")"
  | Or(g,h) -> "("^(affiche g)^"∨"^(affiche h)^")"
  | Imp(g,h) -> "("^(affiche g)^"→"^(affiche h)^")"
  | Equ (g,h) -> "("^(affiche g)^"↔"^(affiche h)^")";; 
  
type valVerite = Zero | Un ;;
type interpretation = (string * valVerite) list;;
  
  (*Question 7*)
let i1 = [("a",Un); ("b",Zero); ("c",Un)];;
let i2 = [("a",Zero); ("b",Zero); ("c",Zero)];;
let i3 = [("a",Un); ("b",Un); ("c",Un)];;
  
  (*Question 8*)
let rec intSymb sym inter =
  if (inter = []) then Zero else (*On choisit de mettre à Zero si l'interprétation est vide*)
  if (fst(List.hd inter) = sym) then snd(List.hd inter)
  else intSymb sym (List.tl inter);;
  
  (*Question 9*)
let intNeg valeur =
  match valeur with
  |Zero -> Un
  |Un -> Zero;;
  
let intAnd valeur1 valeur2 =
  if (valeur1 = Un) then 
    if (valeur2 = Un) then Un
    else Zero
  else Zero;;
  
let intOr valeur1 valeur2 =
  if (valeur1 = Un) then Un
  else  if (valeur2 = Un) then Un
  else Zero;;
  
let intImp valeur1 valeur2 =
  if (valeur1 = Zero) then Un
  else if (valeur2 = Un) then Un
  else Zero;;
  
let intEqu valeur1 valeur2 =
  if (valeur1 = valeur2) then Un else Zero;;
  
let intTop = Un;;
let intBot = Zero;;
  
  (*Question 10*)
let rec valV f inter =
  match f with
  |Top -> intTop
  |Bot -> intBot
  |Symb s -> intSymb s inter
  |Not (prop) -> intNeg(valV prop inter)
  |And (prop1,prop2) -> intAnd (valV prop1 inter) (valV prop2 inter)
  |Or (prop1,prop2) -> intOr (valV prop1 inter) (valV prop2 inter)
  |Imp (prop1,prop2) -> intImp (valV prop1 inter) (valV prop2 inter)
  |Equ (prop1,prop2) -> intEqu (valV prop1 inter) (valV prop2 inter);;
  
  (*Question 11*)
let modele f inter = (Un = valV f inter);;
  
  (*Question 12*)
let toutesInterPQ =  
  [
    [("p",Zero);("q",Zero)];
    [("p",Zero);("q",Un)];
    [("p",Un);("q",Zero)];
    [("p",Un);("q",Un)]
  ];;
  
  (*Question 13*) 
let rec consTous e list =
  match list with
  | [] -> []
  | [[]] -> [[e]]
  | hd::tl -> (e::hd)::(consTous e tl);;
            
let rec ensInt list =
  match list with
  | [] -> [[]]
  | hd::tl -> (consTous (hd,Zero) (ensInt tl))@(consTous (hd,Un) (ensInt tl));;
  
(*Question 14*)
let satisfiable f =
  let listeInter = (ensInt (sp f)) in
  let rec test f li =
    match li with
    | [] -> false
    | [[]] -> false
    | hd::tl when modele f hd -> true
    | hd::tl -> test f tl
  in test f listeInter;; 

(*Question 15*)
let valide f =
  let listeInter = (ensInt (sp f)) in
  let rec test f li =
    match li with
    | [] -> true
    | [[]] -> true
    | hd::tl when not(modele f hd) -> false
    | hd::tl -> test f tl
  in test f listeInter;; 

(*Question 16*)
let insatisfiable f =
  let listeInter = (ensInt (sp f)) in
  let rec test f li =
    match li with
    | [] -> true
    | [[]] -> true
    | hd::tl when modele f hd -> false
    | hd::tl -> test f tl
  in test f listeInter;; 

(*Question 17*)
let equivalent1 f1 f2 =
  let listeInterf1 = (ensInt (sp f1)) and listeInterf2 = (ensInt (sp f2)) in
  let rec test f1 li1 f2 li2 =
    match li1 with
    | []  -> true
    | [[]]  -> true
    | hd::tl when not(modele f1 hd = modele f2 (List.hd li2)) -> false
    | hd::tl -> test f1 tl f2 (List.tl li2)
  in test f1 listeInterf1 f2 listeInterf2;; 

let equivalent2 f1 f2 =
  valide (Equ(f1,f2));;

(*Question 18*)
let consequence2 f1 f2 = 
  valide(Imp(f1,f2));;

(*Question 19*)
let rec tousSP fList =
  match fList with
  | [] -> []
  | hd::tl -> union (sp hd) (tousSP tl);;

(*Question 20*)
let rec modeleCommun fList inter =
  match fList with
  | [] -> true
  | hd::tl -> modele hd inter && modeleCommun tl inter;;

(*Question 21*)
let contradictoire fList =
  let ttInt = ensInt (tousSP fList) in
  let rec eachInter fList intList =
    match intList with
    | [] -> true
    | hd::tl -> not(modeleCommun fList hd) && eachInter fList tl
  in eachInter fList ttInt;;

(*Question 22*)
let modeleHypothese fList =
  let ttInt = ensInt (tousSP fList) in
  let rec eachInter fList intList =
    match intList with
    | [] -> []
    | hd::tl when modeleCommun fList hd -> hd::(eachInter fList tl)
    | hd::tl -> eachInter fList tl
  in eachInter fList ttInt;;

let consequence fList f =
  let listModHyp = modeleHypothese fList in
    let rec eachInterVerif f listMod =
      match listMod with
      | [] -> true
      | hd::tl -> (modele f hd) && (eachInterVerif f tl)
    in eachInterVerif f listModHyp;;

(*Question 23*)
let rec conjonction fList =
  match fList with
  |[] -> Bot
  |[f] -> f
  |hd::tl -> And(hd,(conjonction tl));;

let consequenceV fList f = 
  valide (Imp((conjonction fList),f));;

(*Question 24*)
let consequenceI fList f = 
  insatisfiable (And((conjonction fList),Not(f)));;