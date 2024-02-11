package comptes;

public class CompteRemunere extends CompteBanquaire {
    private float plafond;
    protected static float interet = 3.0;

    public CompteRemunere(int numeroCompte,float solde, float plafond){
            super(numeroCompte, solde);
            this.plafond = plafond;
    }

    public void Depot(float montant){
        if ((this.solde+montant) <= this.plafond){
            super.Depot(montant);
        }
    }

    public void Remuneration(){
        this.solde += this.solde*interet;
    }

    public float getPlafond(){
        return this.plafond;
    }

    public void setPlafond(float plafond){
        this.plafond = plafond;
    }

    public float getInteret(){
        return interet;
    }

    public void setInteret(float newInteret){
        interet = newInteret;
    }
}
