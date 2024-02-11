package Exo1;

public class Etudiant {
	private String nom;
	private String prenom;
	private final int dateNaissance;
	private Source origine;
    private Note[] notes = new Note[3];

    public enum Source{
        locale,
        eCandidat,
        France;
    }

    public enum Mentions{
        AssezBien,
        Bien,
        TrèsBien;
    }

    public Etudiant(String nom, String prenom, Int dateNaissance, Source origine) {
		this.nom = nom;
		this.prenom = prenom;
		this.dateNaissance = dateNaissance;
		this.origine = origine;
	}

    public float Moyenne(){
        return ((notes[0].Notation + notes[1].Notation + notes[2].Notation)/3);
    }

}