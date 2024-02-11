Require Import Arith.
Require Import Lia.
Require Export List.
Open Scope list_scope.
Import ListNotations.

(* Exercice 1 *)
Inductive is_perm : list nat -> list nat -> Prop :=
|cons : forall a : nat, forall l1 l2 : list nat,(is_perm l1 l2) -> (is_perm (a::l1) (a::l2))
|append : forall a : nat, forall l : list nat, (is_perm (a::l) (l++[a]))
|refl : forall l : list nat, (is_perm l l)
|trans : forall l1 l2 l3: list nat, (is_perm l1 l2) -> (is_perm l2 l3)->(is_perm l1 l3)
|sym : forall l1 l2 : list nat,(is_perm l1 l2) -> (is_perm l2 l1).

Goal (is_perm [1;2;3] [3;2;1]).
Proof.
apply (trans [1;2;3] ([2;3]++[1]) [3;2;1]).

apply (append 1 [2;3]).
apply (trans ([2;3;1]) ([3;1]++[2]) [3;2;1]).

apply (append 2 [3;1]).
apply cons.
apply append.
Qed.

Inductive est_trie : list nat -> Prop:=
|lvide : (est_trie nil)
|singl : forall a : nat, (est_trie (a::nil))
|bcp : forall a b : nat,forall l : list nat, (a<=b)->(est_trie (b::l))->(est_trie (a::(b::l))).

Goal (est_trie [1;2;3]).
Proof.
apply bcp.

auto with arith.
apply bcp.

auto with arith.
apply singl.
Qed.

(* Exercice 2 *)

Check le_dec.
Print sumbool.

Definition le_10 (n:nat):bool:=
  match (le_dec n 10) with
  | left _ => true
  | right _ => false
  end.

Eval compute in le_10 5.
Eval compute in le_10 15.

Fixpoint insert (x:nat)(l:list nat){struct l}:list nat:=
match l with
|nil => [x]
|t::q => match (le_dec x t) with
         |left _ => x::l
         |right _ => t::(insert x q)
         end
end.

Eval compute in (insert 3 (insert 3 [1;2;4;5])).

Fixpoint isort (l:list nat):list nat:=
match l with
|nil => nil
|t::q => insert t (isort q)
end.

Eval compute in (isort [2;1;5;3;4]).

Lemma head_is_perm : forall (x1 x2 : nat) (l : list nat),
is_perm (x1 :: x2 :: l) (x2 :: x1 :: l).
Proof.
intros.
apply (trans (x1::x2::l)((x2::l)++[x1])(x2::x1::l)).
apply append.
simpl.
apply cons.
apply sym.
apply append.
Qed.

Lemma insert_is_perm : forall (x:nat)(l:list nat),is_perm(x::l)(insert x l).
Proof.
induction l.
simpl.
apply refl.
simpl.
elim (le_dec x a).
intro.
apply refl.
intro.
apply (trans (x::a::l)(a::x::l)(a::(insert x l))).
apply head_is_perm.
apply cons.
assumption.
Qed.

Lemma insert_is_sorted : forall (x:nat)(l:list nat),
est_trie l -> est_trie (insert x l).
Proof.
intros.
elim H.
simpl.
apply singl.
intros.
simpl.
elim (le_dec x a).
intro.
apply bcp.
assumption.
apply singl.
intro.
apply bcp.
lia.
apply singl.
simpl.
intro.
intro.
intro.
intro.
intro.
elim (le_dec x b).
intro.
intro.
elim (le_dec x a).
intro.
apply bcp.
assumption.
apply bcp.
assumption.
assumption.
intro.
apply bcp.
lia.
assumption.
intro.
intro.
elim (le_dec x a).
intro.
apply bcp.
assumption.
apply bcp.
assumption.
assumption.
intro.
apply bcp.
assumption.
assumption.
Qed.

Lemma isort_correct : forall (l l' : list nat),
l'=isort l -> is_perm l l' /\ est_trie l'.
Proof.
induction l.
intros.
split.
rewrite H.
simpl.
apply refl.
rewrite H.
simpl.
apply lvide.
intros.
rewrite H.
simpl.
elim (IHl (isort l)).
intros.
split.
apply (trans (a::l)(a::(isort l))(insert a (isort l))).
apply cons.
assumption.
apply insert_is_perm.
apply insert_is_sorted.
assumption.
reflexivity.
Qed.


Lemma insert_is_sorted2 : forall (x:nat)(l:list nat),
est_trie l -> est_trie (insert x l).
Proof.
    intros.
    elim H.
    simpl.
    apply singl.
    intros.
    simpl.
    elim (le_dec x a).
    intro.
    apply bcp.
    assumption.
    apply singl.
    intro.
    apply bcp.
    lia.
    apply singl.
    intro.
    intro.
    intro.
    intro.
    simpl.
    elim (le_dec x b).
    elim (le_dec x a).
    intros.
    apply bcp.
    assumption.
    apply bcp.
    assumption.
    assumption.
    intros.
    apply bcp.
    lia.
    apply bcp.
    assumption.
    assumption.
    intro.
    elim (le_dec x a).
    intros.
    apply bcp.
    assumption.
    apply bcp.
    assumption.
    assumption.
    intros.
    apply bcp.
    assumption.
    assumption.