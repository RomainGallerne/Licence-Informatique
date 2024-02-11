public class Colis extends ObjetPostal {
    private String declaration;
    private int valeur;

    public Colis(){}

    public Colis(String origine, String destination, int codePostal, int poids, int volume, Taux un, String declaration, int valeur){
        super(origine, destination, codePostal, poids, volume, un);
        this.declaration = declaration;
        this.valeur = valeur;
    }    

    public int getValeur(){
        return this.valeur;
    }

    public double tarifAffranchissement(){
        int tarif = 2;
        if (tarif == 1){
            tarif+=0.5;
        }
        else if (tarif == 2){
                tarif+=1.5;
            }
        if (super.getPoids() > 1/8){
            tarif += 3;
        }
        return tarif;
    }

    public double tarifRemboursement(){
        Taux taux = super.getTaux();
        if (taux == Taux.un){
            return 0.1*this.valeur;
        }
        else if (taux == Taux.deux){
                return 0.5*this.valeur;
            }
            else return 0;
    }

    public void affichage(){
        System.out.println("Colis : "+String.valueOf(super.getCodePostal())+"/"+super.getDestination()+"/"+String.valueOf(super.getTaux())+"/"+String.valueOf(super.getVolume())+"/"+String.valueOf(this.valeur));
    }
}
