Parameter A B : Prop.
Goal (A<->B)->A->B.
intros.
elim H.
intros.
apply(H1,H0).
assumption.