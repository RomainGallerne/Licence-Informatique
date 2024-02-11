public class Document {
    protected String titre;
    protected String texte;

    public Document(String titre, String texte){
        this.titre = titre;
        this.texte = texte;
    }

    public int nbCars(){
        return (String.length(this.titre) + String.length(this.texte));
    }

    public String export(){
        return (this.titre + this.texte);
    }

    public String getTitre(){
        return this.titre;
    }

    protected String getTexte(){
        return this.texte;
    }

    public void setTitre(String newTitre){
        this.titre = newTitre;
    }

    public void setTexte(String newTexte){
        this.texte = newTexte;
    }
}
