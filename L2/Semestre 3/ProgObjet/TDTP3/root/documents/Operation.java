public class Operation {
    public static void main(String args[]){
        Document dissert = new Document("Pourquoi?","parce que!");
        DocumentAvecMentionsLegales passport = new DocumentAvecMentionsLegales("Robert","Français, 38ans","République Française");
        DocumentCrypte topSecret = new DocumentCrypte("Top secret", "T'avais pas le droit d'ouvrir !");
        System.out.println(dissert.export());
        System.out.println(passport.export());
    }
}