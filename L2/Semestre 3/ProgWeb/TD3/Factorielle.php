<?php session_start(); ?>
<!doctype html>
<html lang="fr">

<head>
    <meta charset="utf-8" />
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
  <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
  <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
  <title>Factorielle</title>
</head>

<body>
    <h1>Factorielle</h1><br />
    <?php
        $previous = 0;
        function factorielle(int $x) {
            $resultat = 1;
            if ($x > 0) {
                for($x;$x>0;$x--){
                    $resultat *= $x;
                }
            }
            return $resultat;
          } 
    ?>
    <?php
        if (isset($_GET['x'])){
            echo "<h3>Résultat : ",factorielle($_GET['x']),"</h3>";
            $previous = $_GET['x'];
        }
    ?>
     <form method="get">
        <label for="x">Valeur de X:</label><br>
        <?php echo ("<input type='number' value=$previous id='x' name='x'><br>"); ?>
        <input type="submit" value="Submit">
    </form> 