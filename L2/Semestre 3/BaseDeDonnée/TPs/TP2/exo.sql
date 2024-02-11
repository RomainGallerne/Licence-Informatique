--1
SELECT titre FROM film, genre
    WHERE (
        film.idGenre=genre.idG AND
        genre.description = 'horreur'
    ) 
    ORDER BY annee;
-- SELECT titre FROM film, genre WHERE (film.idGenre=genre.idG AND genre.description = 'horreur')ORDER BY annee;

--2
SELECT nom, prenom FROM acteur, film, genre, jouer
    WHERE (
        acteur.nationalite = 'France' AND
        acteur.idA = jouer.idActeur AND
        jouer.idFilm = film.idF AND
        film.idGenre = genre.idG AND
        genre.description = 'drame'
    )
    GROUP BY idA, nom, prenom
    ORDER BY nom, prenom;
-- SELECT nom, prenom FROM acteur, film, genre, jouer WHERE (acteur.nationalite = 'France' AND acteur.idA = jouer.idActeur AND jouer.idFilm = film.idF AND film.idGenre = genre.idG AND genre.description = 'drame') GROUP BY idA, nom, prenom ORDER BY nom, prenom;

--3
SELECT realisateur.nom, realisateur.prenom FROM acteur, film, jouer, realisateur
    WHERE (
        acteur.nom = 'Cotillard' AND
        acteur.prenom = 'Marion' AND
        jouer.idActeur = acteur.idA AND
        jouer.idFilm = film.idF AND
        film.idRealisateur = realisateur.idR
    )
    GROUP BY idR, R.nom, R.prenom;
-- SELECT realisateur.nom, realisateur.prenom FROM acteur, film, jouer, realisateur WHERE (acteur.nom = 'Cotillard' AND acteur.prenom = 'Marion' AND jouer.idActeur = acteur.idA AND jouer.idFilm = film.idF AND film.idRealisateur = realisateur.idR) GROUP BY idR, realisateur.nom, realisateur.prenom;

--4
SELECT MAX(nbspectateurs) AS max,MIN(nbspectateurs) AS min,AVG(nbspectateurs) AS moy FROM film, genre
    WHERE (
        film.idGenre = genre.idG AND
        genre.description = 'policier'
    );
-- SELECT MAX(nbspectateurs) AS max,MIN(nbspectateurs) AS min,AVG(nbspectateurs) AS moy FROM film, genre WHERE (film.idGenre = genre.idG AND genre.description = 'policier');

--5
SELECT SUM(nbspectateurs) AS total FROM film, realisateur
    WHERE (
        film.idRealisateur = realisateur.idR AND
        realisateur.nom = 'Scorcesse' AND
        realisateur.prenom = 'Martin'
    );
--SELECT SUM(nbspectateurs) AS total FROM film, realisateur WHERE (film.idRealisateur = realisateur.idR AND realisateur.nom = 'Scorcesse' AND realisateur.prenom = 'Martin');

--6
SELECT SUM(nbspectateurs)*6 AS recette2000 FROM film, realisateur
    WHERE (
        film.idRealisateur = realisateur.idR AND
        realisateur.nationalite = 'France' AND
        film.annee = 2000
    );
--SELECT SUM(nbspectateurs)*6 AS recette2000 FROM film, realisateur WHERE (film.idRealisateur = realisateur.idR AND realisateur.nationalite = 'France' AND film.annee = 2000);

--7
SELECT nationalite,COUNT(*) AS nombreDActeurs FROM acteur GROUP BY nationalite;

--8
SELECT COUNT(*) AS nombreDeFilm FROM film;

--9
SELECT description, COUNT(*) AS nombreDeFilm FROM film, genre 
    WHERE (film.idGenre = genre.idG)
    GROUP BY description;
--SELECT description, COUNT(*) AS nombreDeFilm FROM film, genre WHERE (film.idGenre = genre.idG) GROUP BY description;

--10
SELECT idGenre, COUNT(*) AS nombreDeFilm FROM film GROUP BY idGenre;

--11
SELECT nom, prenom, AVG(nbspectateurs) AS moy, MAX(nbspectateurs) AS max, MIN(nbspectateurs) AS min FROM film, realisateur
    WHERE (film.idRealisateur = realisateur.idR)
    GROUP BY idR, nom, prenom;
--SELECT nom, prenom, AVG(nbspectateurs) AS moy, MAX(nbspectateurs) AS max, MIN(nbspectateurs) AS min FROM film, realisateur WHERE (film.idRealisateur = realisateur.idR) GROUP BY idR, nom, prenom;

--12
SELECT nom, prenom FROM acteur, jouer
    WHERE (acteur.idA = jouer.idActeur)
    GROUP BY nom,prenom
    HAVING (SUM(salaire) > 1000000);
--SELECT nom, prenom FROM acteur, jouer WHERE (acteur.idA = jouer.idActeur) GROUP BY nom,prenom HAVING (SUM(salaire) > 1000000);

--13
SELECT annee FROM film WHERE (annee <= ALL(SELECT annee FROM film));

--14
SELECT annee, MAX(nbspectateurs) FROM film GROUP BY annee;

--15
SELECT annee, COUNT(*) AS nombreDeFilm FROM film WHERE (annee >= 1990) GROUP BY annee ORDER BY annee;

--16
SELECT F1.annee, COUNT(*) AS nombreDeFilm FROM film F1, film F2
    WHERE (1000000 <= ALL(SELECT annee FROM F2) AND F1.annee=F2.annee)
    GROUP BY F1.annee 
    ORDER BY F1.annee;
--SELECT F1.annee, COUNT(*) AS nombreDeFilm FROM film F1, film F2 WHERE (F1.annee=F2.annee AND 1000000 <= ALL(SELECT annee FROM film)) GROUP BY F1.annee ORDER BY F1.annee;