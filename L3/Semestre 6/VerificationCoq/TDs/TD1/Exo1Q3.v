Parameter A B : Prop.
Goal A/\B->B.
intro.
elim H.
intros.
assumption.