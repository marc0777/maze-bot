package maze_GUI;

/**
 * @author Nicolò Tagliaferro
 * @date 03/04/2017
 */

public class Main {

    public static void main(String[] args) {
        BTLayer primo = new BTLayer(0, "Primo piano");
        BTLayer secondo = new BTLayer(1, "Secondo piano");
        GUI interfaccia = new GUI(primo, secondo);
    }
}