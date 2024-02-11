<?php
foreach($_GET as $numero=>$reponse){
	if (($numero == "question_1") && ($reponse == "1954" || "2006")){
		echo "Bravo c'est la bonne réponse !!\n";
		echo "<br>";
	} elseif (($numero == "question_1") && ($reponse != "1954")){
		echo "Ce n'est pas bonne réponse\n";
		echo "<br>";
	}   
	if (($numero == "question_2") && ($reponse == "2254")){
		echo "Bravo c'est la bonne réponse !!\n";
		echo "<br>";
	} elseif (($numero == "question_2") && ($reponse != "2254")) {
		echo "Ce n'est pas bonne réponse \n";
		echo "<br>";
	}
	if (($numero == "question_3") && ($reponse == "Aston Martin DB5")){
		echo "Bravo c'est la bonne réponse !!\n";
		echo "<br>";
	} elseif (($numero == "question_3") && ($reponse != "Aston Martin DB5")){
		echo "Ce n'est pas bonne réponse\n";
		echo "<br>";
	}   
}
?>
</body>
</html> 
