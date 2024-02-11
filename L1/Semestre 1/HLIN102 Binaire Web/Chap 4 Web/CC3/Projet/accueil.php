<html lang="fr">
	<head>
		<?php include("php/head.html"); ?>
		<title>Accueil Lotr & Animés</title>
	</head>
	
	<body>
		<div id="menu">
  	  <a href="accueil.php" class="button link" title="Retourner à        l'accueil">Accueil</a>
    	<a href="CV/CVRomain/CVRomain.php" class="link" id="RG">CV G. Romain</a>
    	<a href="CV/CVPatrick/CVPatrick.php" class="link" id="PM">CV M. Patrick</a>
	    <a href="CV/CVIlies/CVIlies.php" class="link" id="IS">CV S. Ilies</a>
    </div>
		
		<h1>Bienvenue!</h1>
		<h2>Sélectionnez votre thème favoris :</h2>
		<div id="mainbox">
			<a id="boxLotR" href="quizLotR.php">
				<p><div class="theme">Thème</div></p>
				<img id="LotR_photo" src="accueil.images/LotR_logo.png" alt="LotR">
			</a>
			<a id="boxJVAnime" href="quizJVA.php">
				<p><div class="theme">Thème</div></p>
				<img id="JVA_photo" src="accueil.images/JVAnime_logo.png" alt="LotR">
			</a>
		</div> <br>
	</body>