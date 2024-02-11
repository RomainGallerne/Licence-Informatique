<!doctype html>
<html lang="fr">
    <head>
        <meta charset="utf-8" />
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
        <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
        <title>Facture</title>
        <style>
            th {
                font-weight: bold;
                text-align: left;
            }
            td {
                text-align: right;
            }
            table, th, td {
                border: 2px solid black;
                border-collapse: collapse;
                font-size: 1em;
            }
        </style>
    </head>

    <body> 
        <h1>Facture</h1><br />
        <table class="col-md-8 col-12">
            <tr>
                <th class="col-2">Quantité</th>
                <th class="col-3">Article</th>
                <th class="col-3">Prix Unitaire HT</th>
                <th class="col-2">T.V.A.</th>
                <th class="col-2">T.T.C.</th>
            </tr>
            <?php
            include 'data.php';
            $total = 0;

            foreach($_GET as $id=>$art){
                if(!empty($art)){
                    $nb = $art['id'];
                    $nom = $art['nom'];
                    $tva = (20/100)*$art['prix'];
                    $prix = $art['prix'];
                    $prixXnb = $prix * $id;
                    $total += $prix;
                    echo("  <tr>
                        <td>$id</td>
                        <td>$nom</td>
                        <td>$prixXnb</td>
                        <td>$tva</td>
                        <td>$prix</td>
                        </tr>
                    ");
                }
            }
            echo("
                <tr>
                <td></td>
                <td>TOTAL</td>
                <td></td>
                <td></td>
                <td>$total</td>
            ")
            ?>
        </table> 
    </body>
</html>