(*Question 1*)

Fixpoint mult(n m : nat) {struct n} : nat :=
match n with
| 0 => 0
| (S p) => plus (mult p m) m
end .
(*Question 2*)

Lemma p0 : forall n, mult 2 n = plus n n.
Proof.
  intro.
  simpl.
  reflexivity.
Qed.

(*Question 3*) 

Lemma aux0 : forall n, (plus n 2) = S (S n).
Proof.
  induction n.
  simpl.
  reflexivity.
  simpl.
  rewrite IHn.
  reflexivity.
Qed.

Lemma aux1 : forall n m, (S (plus n (S m))) = S (S (plus n m)).
Proof.
  intro.
  elim n.
  intros.
  simpl.
  reflexivity.
  intros.
  simpl.
  rewrite (H m).
  reflexivity.
Qed.

Lemma p1 : forall n, mult n 2 = plus n n.
Proof.
  intro.
  elim n.
  simpl.
  reflexivity.
  intros.
  simpl.
  rewrite aux0.
  rewrite aux1.
  rewrite H.
  reflexivity.
Qed.

(*Question 4*)

Require Export List.
Open Scope list_scope.
Import ListNotations.

Parameter E : Type.

Fixpoint rev(l : list E) {struct l} : list E :=
match l with
| nil => nil
| e::q => (rev q) ++ [e]
end .

Lemma l1 : forall l e, rev(l ++ [e]) = e::rev(l).
Proof.
  intro.
  elim l.
  intros.
  simpl.
  reflexivity.
  intros.
  simpl.
  rewrite H.
  reflexivity.
Qed.

Lemma l2 : forall l, rev(rev(l)) = l.
Proof.
  induction l.
  simpl;reflexivity.
  simpl.
  rewrite l1.
  rewrite IHl.
  reflexivity.
Qed.
  
