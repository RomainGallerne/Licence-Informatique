public class Main {
    public static void main(String[] args) {
        Lettre cartePostal = new Lettre("Paris", "Marseille", 12345, 3, 1, Taux.zero, false);
        Colis amazon = new Colis("Chine", "Strasbourg", 54321, 18, 1, Taux.un, "Un colis un peu important", 600);
        ColisExpress amazonPrime = new ColisExpress("Chine", "Bordeau", 24680, 28, 3, Taux.deux, "Un colis très important", 5000, true);

        //ColisExpress amazonSuperPrime = new ColisExpress("Chine", "Bordeau", 24680, 38, 3, Taux.deux, "Un colis très très important", 50000, true);
        //Ce code renvoie l'erreur : "Erreur : le poid ne peut être supérieur à 30kg"

        cartePostal.affichage();
        amazon.affichage();
        amazonPrime.affichage();
        //amazonSuperPrime.affichage();
        System.out.println("Date d'envoi du ColisExpress amazonPrime : "+amazonPrime.getDate());
    }
}
