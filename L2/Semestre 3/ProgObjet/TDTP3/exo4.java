public class A{
    public A(){} 
    //On rajoute un constructeur par défault,
    //sinon B et C ne peuvent hériter du super constructeur.
    //B et C n'ont pas d'attributs supplémentaires à passer.
    public A(int i){}
    public A m0(A a){System.out.println("m0 de A");return a;}
    public void m1(A a){System.out.println("m1 de A");}
}

public class B extends A {
    public void m1(A a){System.out.println("je masque m1 de A");} 
    //Masquage -> Redéfinition total du code à exécuter
    //Invariant -> même type de retour et même paramètres
    public B m0(A a){
        System.out.println("je masque m0 de A");
        super.m0(a);
        return (b = new B());}
    //Spécialisation -> appelle de la même méthode dans la super classe
    //Covariante -> même paramètres mais spécialisation du type de retour (B est un A)
}

public class C extends A {
    public A m0(C c){
        System.out.println("Surchage de m0 dans C");
        return (a = new A());
    //Surcharge -> même nom mais paramètres différents, 
    //(en type ou en nombre et pas en relation de sous-typage), 
    //ou type de retour différent.
    }
}