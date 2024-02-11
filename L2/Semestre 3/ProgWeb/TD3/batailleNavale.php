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
  <title>Commande</title>
  <style>
            th {
                font-weight: bold;
                text-align: center;
            }
            td {
                text-align: center;
            }
            table, th, td {
                border: 2px solid black;
                border-collapse: collapse;
                font-size: 1em;
            }
        </style>
</head>

<body>
    <h1>Bataille navale</h1><br />
    <table class="col-md-5 col-12">
        <tr>
            <th class="col-2"></th>
            <th class="col-2">A</th>
            <th class="col-2">B</th>
            <th class="col-2">C</th>
            <th class="col-2">D</th>
            <th class="col-2">E</th>
        </tr>
        <form>
        <?php
            $numCase = 0;
            for ($numLigne=1; $numLigne<=5; $numLigne++){
                echo ("<tr> <td class='col-2'>$numLigne</td>");
                for ($j=0; $j<=4; $j++){
                    $numCase++;
                    if (!empty($_SESSION[$numCase])) {
                        if ($numCase%3 == 0){
                            echo ("<td class='col-2'>BOOM</td>");
                        }
                        else {
                            echo ("<td class='col-2'>~</td>");
                        }
                    }
                    else {
                        echo ("
                        <td class='col-2'>
                            <input type='submit' name='$numCase' class='col-12' value='?'>
                        </td>
                        ");
                    }
                }
                echo ("</tr>");
            }
        ?>
        </form>
    </table>
</body>
</html>