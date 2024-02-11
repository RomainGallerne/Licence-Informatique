Parameter A : Prop.
Parameter E : Set.
Parameters x y : E.
Parameters P Q : E -> Prop.

Goal forall x : E, (P x) -> exists y : E, (P y) \/ (Q y).
Proof.
  intros.
  exists x0.
  left.
  assumption.
Qed.

Goal (exists x : E, (P x) \/ (Q x)) -> (exists y : E, P y) \/ (exists z : E, Q z).
Proof.
  intro.
  elim H.
  intros.

  elim H0.
  intros.
  left.
  exists x0.
  assumption.

  intro.
  right.
  exists x0.
  assumption.
Qed.

Require Import Classical.

Goal ~(forall x : E, P x) -> (exists y : E, ~(P y)).
Proof.
  intro.
  apply NNPP.
  intro.
  elim H.
  intro.
  apply NNPP.
  intro.
  elim H0.
  exists x0.
  assumption.
Qed.