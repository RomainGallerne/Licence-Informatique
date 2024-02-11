--2

CREATE TABLE genre (idG INT, description VARCHAR(50) NOT NULL, PRIMARY KEY(idG));

CREATE TABLE film (idF INT, titre VARCHAR(255) NOT NULL, annee INT NOT NULL, nbSpectateurs INT NOT NULL, idRealisateur INT REFERENCES realisteur(idR), idGenre INT REFERENCES genre(idG), PRIMARY KEY(idF));

CREATE TABLE jouer (idActeur INT,idFilm INT REFERENCES film(idF),salaire INT NOT NULL,PRIMARY KEY (idActeur,idFilm));

--3

INSERT INTO genre VALUES(2,'Science fiction');
INSERT INTO realisateur VALUES(12,'Michel','Paul','Français');
INSERT INTO film VALUES(14,'Mieux vaut être riche et bien portant que pauvre et fauche',1980,10023,12,2);

INSERT INTO realisateur VALUES(1,'Hooper','Tom','Americain');

INSERT INTO film VALUES(11,'La mome',2007,3456743,NULL,2);

INSERT INTO film VALUES(27,'Enfermés Dehors',2006,132890,16,2);

--4

