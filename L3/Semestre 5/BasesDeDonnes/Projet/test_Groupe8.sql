/*
Groupe 8
22010415 - Lisa SAVY
21809267 - Eric GILLES
22009176 - Morgan NAVEL
22010416 - Romain GALLERNE
*/

--test trigger Joueur_Autre_Equipe
INSERT INTO JOUE VALUES (000002,000001);

--test trigger arbitre_dispo
INSERT INTO MATCH VALUES (000012,0,3,000008,000005,000003,010101,'30-01-2019');

--test trigger diff_equipes
INSERT INTO MATCH VALUES (000011,1,3,000001,000001,000012,010101,'25-09-2040');

--test de la fonction
prompt SELECT nb_victoire_equipe(000002) FROM DUAL;
SELECT nb_victoire_equipe(000002) FROM DUAL;

--appel de la procédure
prompt EXEC equipe_max_victoire;
EXEC equipe_max_victoire;