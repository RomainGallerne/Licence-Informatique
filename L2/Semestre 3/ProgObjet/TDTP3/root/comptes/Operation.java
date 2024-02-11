package comptes;

public class Operation {
    public static void main(String args[]){
        CompteBanquaire Robert = new CompteBanquaire(01, 2000.0);
        CompteRemunere Michel = new CompteRemunere(02, 8500.0, 9000.0);
        CompteRemunere.interet = 3.5;

        System.out.println(Robert.getSolde());
        Robert.Prelevement(1500.0);
        System.out.println(Robert.getSolde());

        System.out.println(Michel.getSolde());
        Michel.Depot(600.0);
        System.out.println(Michel.getSolde());

    }
}