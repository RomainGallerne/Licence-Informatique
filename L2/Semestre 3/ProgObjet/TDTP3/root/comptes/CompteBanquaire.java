package comptes;

public class CompteBanquaire {
    private final int numeroCompte;
    protected float solde;

    public CompteBanquaire(int numeroCompte, float solde){
        this.numeroCompte = numeroCompte;
        this.solde = solde;
    }

    public void Depot(float montant){
        this.solde += montant;
    }

    public void Prelevement(float montant){
        if (this.solde >= montant){
            this.solde -= montant;
        }

    }

    public void getNumero(){
        return this.numeroCompte;
    }

    protected void getSolde(){
        return this.solde;
    }

    public void setSolde(float montant){
        this.solde = montant;
    }

    }
}
