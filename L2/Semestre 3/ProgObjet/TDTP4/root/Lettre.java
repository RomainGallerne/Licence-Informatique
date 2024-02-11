public class Lettre extends ObjetPostal {
    private boolean urgence;

    public Lettre(){}

    public Lettre(String origine, String destination, int codePostal, int poids, int volume, Taux tauxDeRecommandation, boolean urgence){
        super(origine, destination, codePostal, poids, volume, tauxDeRecommandation);
        this.urgence = urgence;
    }

    public double tarifAffranchissement(){
        Taux taux =  super.getTaux();
        if (taux == Taux.un){
            return 0.5;
        }
        else if (taux == Taux.deux){
                return 1.5;
            }
            else return 0;
    }

    public double tarifRemboursement(){
        Taux taux = super.getTaux();
        if (taux == Taux.un){
            return 1.5;
        }
        else if (taux == Taux.deux){
                return 15;
            }
            else return 0;
    }

    public void affichage(){
        String urgent;
        if (urgence) {urgent = "urgent";}
        else {urgent = "ordinaire";}
        System.out.println("Lettre : "+String.valueOf(super.getCodePostal())+"/"+super.getDestination()+"/"+String.valueOf(super.getTaux())+"/"+urgent);
    }
}
