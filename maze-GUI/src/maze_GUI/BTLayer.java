package maze_GUI;

/**
 * Created by Nicolò Tagliaferro on 03/04/2017.
 */
public class BTLayer {
    private int piano;
    private String nome;

    public BTLayer(int piano, String nome) {
        this.nome = nome;
        this.piano = piano;
    }

    public String toString() {
        return nome;
    }

    public int getPiano() {
        return piano;
    }
}
