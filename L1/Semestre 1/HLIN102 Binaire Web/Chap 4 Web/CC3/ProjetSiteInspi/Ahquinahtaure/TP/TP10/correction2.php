<?php
foreach($_GET as $numero=>$reponse){
	if (($numero == "question_1") && ($reponse == "1954" || "2006")){
		echo "Bonne réponse !\n";
		echo "<br>";
	} elseif (($numero == "question_1") && ($reponse != "1954")){
		echo "Mauvaise réponse...\n";
		echo "<br>";
	}   
	if (($numero == "question_2") && ($reponse == "2254")){
		echo "Bonne réponse !\n";
		echo "<br>";
	} elseif (($numero == "question_2") && ($reponse != "2254")) {
		echo "Mauvaise réponse...\n";
		echo "<br>";
	}
	if (($numero == "question_3") && ($reponse == "Aston Martin DB5")){
		echo "Bonne réponse !\n";
		echo "<br>";
	} elseif (($numero == "question_3") && ($reponse != "Aston Martin DB5")){
		echo "Mauvaise réponse...\n";
		echo "<br>";
	}   
}
?>
</body>
</html> 
