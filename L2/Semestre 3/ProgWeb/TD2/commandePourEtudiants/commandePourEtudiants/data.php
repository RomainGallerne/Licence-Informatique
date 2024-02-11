<?php
function getCatalogue(){
$json=<<<FIN
{
"portables":
[
  {"id":"lenovo", "prix":499.99, "nom":"PC portable Lenovo","desc":"Processeur : AMD Athlon Silver 3050U / 2.3 GHz   RAM : 8 Go (1 x 4 Go + 4 Go (soudé)) Résolution : 1600 x 900 (HD+)"},
  {"id":"asus", "prix":579.99, "nom":"PC portable ASUS","desc":"Processeur : AMD Ryzen 3 3200U / 2.6 GHz   RAM : 8 Go (1 x 4 Go + 4 Go (soudé)) Résolution : 1600 x 900 (HD+)"}
],
"tablettes":
[  
  {"id":"samsung", "prix":215.19, "nom":"Tablette Samsung", "desc": "10.1p TFT - rétroéclairage par LED - 1920 x 1200   (224 ppi) Système d'exploitation : Android 9.0 (Pie) RAM : 2 Go - LPDDR4 SDRAM Stockage : 32 Go"},
  {"id":"archos", "prix":99.99, "nom":"Tablette Archos", "desc":"10.1p IPS TFT - 1280 x 800 3G Système d'exploitation :    Android 8.1 (Oreo) Go Edition RAM : 1 Go - LPDDR3 SDRAM  Stockage : 32 Go"}
],
"téléphones":
[
  {"id":"maxcom", "prix":2015.19, "nom":"Maxcom", "desc":"Taille de la diagonale : 6.3, Résolution du capteur : 48 mégapixels, Capacité : 4000 mAh, Capacité de la mémoire interne : 128 Go, 8 coeurs, RAM : 4 Go, Génération à haut débit mobile : 4G" },
  {"id":"iphone", "prix":9.99, "nom":"iphone", "desc":"Taille de la diagonale : 6.3, Résolution du capteur : 48 mégapixels, Capacité : 4000 mAh, Capacité de la mémoire interne : 128 Go, 8 coeurs, RAM : 4 Go, Génération à haut débit mobile : 4G" }
]
}
FIN;
// pas de retour à la ligne ni tab ni char de ctrl dans une chaine json à décoder ! que des guillemets !

//echo $json;
$rayons=json_decode($json,true);
if ($rayons==null) {
  echo json_last_error_msg();
  die("Impossible d'accéder aux données !<br>");
}
/* var_dump($rayons);
foreach($rayons as $rayon => $articles){
  foreach($articles as $article){
    foreach($article as $cle => $valeur){
      echo "$clé : $valeur <br>";
    }
  }
}  */
return $rayons;
}

function getArticle($catalogue, $id){
  foreach ($catalogue as $rayon => $articles){
    foreach($articles as $article){
      if ($article['id']==$id){
        return $article;
      }
    }
  }
  return null;
}
?>