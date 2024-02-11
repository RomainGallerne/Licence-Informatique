<?php
class Mastermind{
    private int $taille;
    private String $secret;
    private array $tentatives;
    private array $resultats;
    private int $nbTentatives=0;

    public function __construct(int $taille){
        $this->taille = $taille;
        $this->tentatives = [];
        $this->resultats = [];
        $this->secret = "";

        $caracteres = "0123456789";
        for ($i = 0; $i < $taille; $i++) {
            $this->secret .= $caracteres[rand(0, 9)];
        }
    }

    public function getSecret(){
        return $this->secret;
    }

    public function getEssais(){
        return $this->tentatives;
    }

    public function getResultat(){
        return $this->resultats;
    }

    public function getTaille(){
        return $this->taille;
    }

    public function test(string $newTentative){
        $nbBon = 0;
        $nbMalPlace = 0;
        $thisSecret = $this->secret;
        if (strlen($newTentative)==$this->taille){
            $this->tentatives[$this->nbTentatives] = $newTentative;
            for ($i = 0; $i < $this->taille; $i++) {
                if ($newTentative[$i]==$thisSecret[$i]){
                    $nbBon++;
                    $newTentative[$i]='Y';
                    $thisSecret[$i]='Y';
                }
                else {
                    if (false != array_search($newTentative[$i], $thisSecret,false)) {
                        $nbMalPlace++;
                    }
                }
            }
        $this->resultats[$this->nbTentatives] = [$nbBon,$nbMalPlace];
        $this->nbTentatives++;
        return [$nbBon,$nbMalPlace];
        }
        else {return false;}
    }
}
?>