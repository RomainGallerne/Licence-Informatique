public class DocumentCrypte extends Document {
    private int clé = 1234;

    public DocumentCrypte(String titre, String texte){
        super(titre, texte);
    }

    public String export(int testClé){
        if (testClé == this.clé){
            return (this.titre + this.texte);
        }
        return ("Clé incorrect");
    }

    public String crypte(){
        return (this.text + "cryptage");
    }
}