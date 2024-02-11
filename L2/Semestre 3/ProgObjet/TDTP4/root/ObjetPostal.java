public abstract class ObjetPostal {
    private String origine;
    private String destination;
    private int codePostal;
    private int poids;
    private int volume;
    private Taux tauxDeRecommandation;

    public ObjetPostal(){}

    public ObjetPostal(String origine, String destination, int codePostal, int poids, int volume, Taux tauxDeRecommandation){
        this.origine = origine;
        this.destination = destination;
        this.codePostal = codePostal;
        this.poids = poids;
        this.volume = volume;
        this.tauxDeRecommandation = tauxDeRecommandation;
    }

    public abstract double tarifAffranchissement();
    public abstract double tarifRemboursement();
    public abstract void affichage();

    public void setPoids(int nouveauPoid){
        this.poids = nouveauPoid;
    }

    public int getPoids(){
        return this.poids;
    }

    public Taux getTaux(){
        return this.tauxDeRecommandation;
    }

    public int getVolume(){
        return this.volume;
    }

    public String getDestination(){
        return this.destination;
    }

    public int getCodePostal(){
        return this.codePostal;
    }
}