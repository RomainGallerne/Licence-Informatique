package Exo1;

public class Note {
    private UE UE;
    private float Notation;

    public Note(UE UE, float Notation){
        this.UE = UE;
        this.Notation = Notation;
    }

    public void setNotation(float notation) {
        this.Notation = notation;
    }

    public void setUE(UE ue) {
        this.UE = ue;
    }
}
