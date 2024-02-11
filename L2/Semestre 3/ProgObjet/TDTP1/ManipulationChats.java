
public class ManipulationChats {
	public static void main (String[] args) {
		PelageChat PelageAzrael=new PelageChat("Roux et Blanc", true, false, "Roux avec des taches blanchs");
		PelageChat PelageAzibis=new PelageChat("Noir", false, false, "Un chat tout noir");
		Chat Azrael=new Chat("Azrael", PelageAzrael, 2017, false);
		Chat Azibis=new Chat("Azibis", PelageAzibis, 2005, true);
		System.out.println(Azrael.toString());
		System.out.println(Azibis.toString());
	}
}