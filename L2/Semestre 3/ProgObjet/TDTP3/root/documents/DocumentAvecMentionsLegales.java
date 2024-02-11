public class DocumentAvecMentionsLegales extends Document {
    private String mentionsLegales;

    public DocumentAvecMentionsLegales(String titre, String texte, String mentionsLegales){
            super(titre, texte);
            this.mentionsLegales = mentionsLegales;
    }

    public String export(){
        return (this.titre + this.texte + this.mentionsLegales);
    }

    public float getMentions(){
        return this.mentionsLegales;
    }

    public void setMentions(String Mentions){
        this.mentionsLegales = Mentions;
    }
}
