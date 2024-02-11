<?php session_start(); ?>
<!doctype html>
<html lang="fr">
<head>
    <meta charset="utf-8" />
    <title>Multiplication et session</title>
</head>

<body>
    <h1>Multiplication et session</h1>
    <?php
        if(isset($_SESSION['historique'])){ // var_dump($_SESSION);?> 
        <h2>Historique des multiplications</h2>
    <?php 
        foreach($_SESSION['historique'] as $tab){
        echo "{$tab['x']} * {$tab['y']} = {$tab['r']}<br/>\n";
        }
        echo "<hr/>\n";
        } else {
            $_SESSION['historique']=array(); // init tableau de tableau
        if (isset($_GET['mult'])){
        // nouvelle mult
    ?> 
    <h2>Multiplication courante</h2>
    <?php
        echo " {$_GET['x']} * {$_GET['y']} = ".$_GET['x']*$_GET['y'].
        " !<br/>";
        $tab=array('x'=>$_GET['x'], 'y'=>$_GET['y'],'r'=>$_GET['x']*$_GET['y']);
        $_SESSION['historique'][]=$tab;
        echo "<hr/>";
        }
    ?>
    <h2>Nouvelle Multiplication</h2>
    <form action="<?php echo"{$_SERVER['PHP_SELF']}".(strlen(SID)?'?'.SID:''); ?> "method="get">
        X<input type="number" name="x" size="10"><br>
        Y<input type="number" name="y" size="10"><br>
        <input type="submit" value="Multiplier !" name="mult">
    </form>
</body>
</html>