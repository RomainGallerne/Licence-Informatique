<!DOCTYPE html>
<html lang="fr">
	<head>
		<meta charset="UTF-8" />
	</head>
	<body>
		Votre réponse est donc:
		<?php
			foreach($_GET as $name=>$value){
				echo "<li>" , $name, " : ", $value, "</li>";
			}
		?>
	</body>
</html>