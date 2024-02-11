import java.text.SimpleDateFormat;
import java.util.Date;

public class ColisExpress extends Colis {
    private Date dateEnvoi;
    private boolean emballage;
    private int numeroSuivi;
    private static int nombreColisExpress = 0;

    public ColisExpress(){}

    public ColisExpress(String origine, String destination, int codePostal, int poids, int volume, Taux tauxDeRecommandation, String declaration, int valeur, boolean emballage){
        super(origine, destination, codePostal, poids, volume, tauxDeRecommandation, declaration, valeur);
        if (poids < 30) {
            this.emballage = emballage;
            this.dateEnvoi = new Date();
            nombreColisExpress++;
            this.numeroSuivi = nombreColisExpress;
        }
        else {throw new RuntimeException("Erreur : le poid ne peut être supérieur à 30kg");}
    }
    public double tarifAffranchissement(){
        int tarif = 30;
        if (this.emballage) {
            tarif+=3;
        }
        return tarif;
    }

    public double tarifRemboursement(){
        return super.tarifRemboursement();
    }

    public void affichage(){
        System.out.println("ColisExpress : "+String.valueOf(super.getCodePostal())+"/"+super.getDestination()+"/"+String.valueOf(super.getTaux())+"/"+String.valueOf(super.getVolume())+"/"+String.valueOf(super.getValeur())+"/"+String.valueOf(super.getPoids())+"/"+String.valueOf(nombreColisExpress));
    }

    public String getDate(){
        SimpleDateFormat s = new SimpleDateFormat("dd/MM/yyyy");
        return (s.format(this.dateEnvoi));
    }

}
