<?php 
    include "MasterMind.php";
    session_start();
?>
<!DOCTYPE html>
<html lang="fr">

    <head>
        <meta charset="utf-8" />
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
        <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
        <title>Master Mind</title>
    </head>

    <body>
        <h1>MasterMind</h1><br />
        <?php
            if (isset($_SESSION["MasterMind"])){
                echo $_SESSION["Secret"];
                //echo var_dump($_SESSION["MasterMind"]->getEssais());
                //echo var_dump($_SESSION["MasterMind"]->getResultat());
                echo "<h5>Liste des essais précédents</h5>";
                echo "<table>";
                echo "<tr><th>Essais </th> <th>Bon </th> <th>Mauvais </th> </tr> <tr>";
                $compteur=0;
                if (isset($_GET['x'])){
                    $_SESSION["MasterMind"]->test($_GET['x']);
                    if ($_GET['x'] == $_SESSION["Secret"]){
                        echo "<h2>Victoire !</h2>";
                    }
                    $previous = $_GET['x'];
                }
                else {$previous = "XXXX";}
                foreach ($_SESSION["MasterMind"]->getEssais() as $e){
                    $r = ($_SESSION["MasterMind"]->getResultat())[$compteur];
                    $compteur++;
                    $r1 = $r[0];
                    $r2 = $r[1];
                    echo "<td>$e</td> <td>$r1</td> <td>$r2</td> </tr> <tr>";
                }
                echo "</tr></table>";
            }
            else {
                $_SESSION["MasterMind"] = new MasterMind(4);
                $_SESSION["Secret"] = $_SESSION["MasterMind"]->getSecret();
                $previous = "XXXX";
            }
        ?>
        <form method="get">
            <label for="x">Code Secret</label><br>
            <?php echo ("<input type='text' placeholder=$previous id='x' name='x'><br>"); ?>
            <input type="submit" value="Essayer !">
        </form> 
    </body>
</html>