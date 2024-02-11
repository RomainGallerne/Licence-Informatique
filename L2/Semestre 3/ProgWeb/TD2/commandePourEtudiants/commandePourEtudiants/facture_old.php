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
            if(($_GET['lenovo'])!=0){
                $nb = $_GET['lenovo'];
                $tva = (20/100)*499.99;
                $prix = $_GET['lenovo']*499.99;
                $total += $prix;
                echo("  <tr>
                        <td>$nb</td>
                        <td>PC Lenovo</td>
                        <td>499.99</td>
                        <td>$tva</td>
                        <td>$prix</td>
                        </tr>
                    ");
            }
            if(($_GET['asus'])!=0){
                $nb = $_GET['asus'];
                $tva = (20/100)*579.99;
                $prix = $_GET['asus']*579.99;
                $total += $prix;
                echo("  <tr>
                        <td>$nb</td>
                        <td>PC Asus</td>
                        <td>579.99</td>
                        <td>$tva</td>
                        <td>$prix</td>
                        </tr>
                    ");
            }
            if(($_GET['samsung'])!=0){
                $nb = $_GET['samsung'];
                $tva = (20/100)*215.19;
                $prix = $_GET['samsung']*215.19;
                $total += $prix;
                echo("  <tr>
                        <td>$nb</td>
                        <td>Tablette Samsung</td>
                        <td>215,19</td>
                        <td>$tva</td>
                        <td>$prix</td>
                        </tr>
                    ");
            }
            if(($_GET['archos'])!=0){
                $nb = $_GET['archos'];
                $tva = (20/100)*99.99;
                $prix = $_GET['archos']*99.99;
                $total += $prix;
                echo("  <tr>
                        <td>$nb</td>
                        <td>Tablette Archos</td>
                        <td>99.99</td>
                        <td>$tva</td>
                        <td>$prix</td>
                        </tr>
                    ");
            }
            if(($_GET['maxcom'])!=0){
                $nb = $_GET['maxcom'];
                $tva = (20/100)*2015.19;
                $prix = $_GET['maxcom']*2015.19;
                $total += $prix;
                echo("  <tr>
                        <td>$nb</td>
                        <td>Téléphone Maxcom</td>
                        <td>2015.19</td>
                        <td>$tva</td>
                        <td>$prix</td>
                        </tr>
                    ");
            }
            if(($_GET['iphone'])!=0){
                $nb = $_GET['iphone'];
                $tva = (20/100)*9.99;
                $prix = $_GET['iphone']*9.99;
                $total += $prix;
                echo("  <tr>
                        <td>$nb</td>
                        <td>Téléphone Iphone</td>
                        <td>9.99</td>
                        <td>$tva</td>
                        <td>$prix</td>
                        </tr>
                    ");
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