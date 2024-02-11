--Le nombre de joueur sponsorisé dans chaque match dans chaque compétition
select match.NUM_COMPETITION,match.NUM_MATCH,count(joueur.NUM_SPONSOR) as NbJoueursSponso from match 
	join equipe on (match.NUM_E1=equipe.NUM_EQUIPE or match.NUM_E2=equipe.NUM_EQUIPE) 
    join joue on (equipe.NUM_EQUIPE=joue.NUM_EQUIPE)
    join joueur on (joue.NUM_JOUEUR=joueur.NUM_JOUEUR)
    group by match.NUM_COMPETITION,match.NUM_MATCH
    order by match.NUM_COMPETITION,match.NUM_MATCH;
    
--Les arbitres ayant arbitré au moins un match de chaque compétitions
select arbitre.num_arbitre,personne.prenom,personne.nom,personne.nationalite from arbitre
	join personne on (arbitre.num_arbitre=personne.num_personne)
    where not exists(
      select * from competition where not exists(
        select * from match where (
          	match.NUM_ARBITRE = arbitre.NUM_ARBITRE
      		and match.NUM_COMPETITION = competition.NUM_COMPETITION
    	)
      )
    );
    
--Pour chaque compétition, les Equipes ayant gagné au moins 2 matchs
select match.NUM_COMPETITION,e.NUM_EQUIPE,e.NOM_EQUIPE from equipe e 
	join match on (NUM_E1=e.NUM_EQUIPE or NUM_E2=e.NUM_EQUIPE)
	where ((NUM_E1=e.NUM_EQUIPE and SCORE_E1 > SCORE_E2) 
    or (NUM_E2=e.NUM_EQUIPE and SCORE_E2 > SCORE_E1))
    group by match.NUM_COMPETITION,e.NUM_EQUIPE,e.NOM_EQUIPE
    having (
      2 <= (
        select count(*) from match where 
        (NUM_E1=e.NUM_EQUIPE and SCORE_E1 > SCORE_E2) 
        or (NUM_E2=e.NUM_EQUIPE and SCORE_E2 > SCORE_E1))
    );
    

--Pour chaque compétition, l'équipe vainqueur
select c.NUM_COMPETITION,c.NOM_COMPETITION,c.SAISON,e.NUM_EQUIPE,e.NOM_EQUIPE from competition c
	join match m on m.NUM_COMPETITION=c.NUM_COMPETITION
    join equipe e on (e.NUM_EQUIPE=m.NUM_E1 or e.NUM_EQUIPE=m.NUM_E2)
    where (
      (select count(*) from match where(
        ((NUM_E1=e.NUM_EQUIPE and SCORE_E1 > SCORE_E2) or (NUM_E2=e.NUM_EQUIPE and SCORE_E2 > SCORE_E1))
        and match.NUM_COMPETITION = m.NUM_COMPETITION
      ))
      >=
      (select max(NbVictoire) from(
  		select e2.NUM_EQUIPE,count(*) NbVictoire from equipe e2
			join match on (NUM_E1=e2.NUM_EQUIPE or NUM_E2=e2.NUM_EQUIPE)
    		where(
        		((NUM_E1=e2.NUM_EQUIPE and SCORE_E1 > SCORE_E2) or (NUM_E2=e2.NUM_EQUIPE and SCORE_E2 > SCORE_E1))
            and match.NUM_COMPETITION = m.NUM_COMPETITION
    		)
    		group by e2.NUM_EQUIPE)
      )
    )
    group by c.NUM_COMPETITION,c.NOM_COMPETITION,c.SAISON,e.NUM_EQUIPE,e.NOM_EQUIPE;
    
--Les sponsors qui ne sponsorient que des joueurs français
select sponsor.NUM_SPONSOR,sponsor.NOM,p.NATIONALITE from sponsor
	join joueur j on sponsor.NUM_SPONSOR=j.NUM_SPONSOR
    join personne p on p.NUM_PERSONNE=j.NUM_JOUEUR
 	where (p.NATIONALITE = 'FRANCAIS')
    group by sponsor.NUM_SPONSOR,sponsor.NOM;