
public class Chat {
	private String nom;
	private String pelage;
	private boolean poilLong;
	private int anneeNaissance;
	private boolean puce;
	
	public Chat(String nom, String pelage, boolean poilLong, int anneeNaissance, boolean puce) {
		this.nom = nom;
		this.pelage = pelage;
		this.poilLong = poilLong;
		this.anneeNaissance = anneeNaissance;
		this.puce = puce;
	}

	Chat Azrael=new Chat("Azrael", "roux et blanc", false, 2017, false);
	Chat Grosminet=new Chat("Grosminet", "noir", false, 2005, true);

	

	public String toString() {
		return "Chat [nom=" + nom + ", pelage=" + pelage + ", poilLong=" + poilLong + ", anneeNaissance="
				+ anneeNaissance + ", pucé=" + puce + "]";
	}

}
