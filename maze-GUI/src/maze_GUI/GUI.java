package maze_GUI;

import javax.swing.*;

/**
 * Created by Nicolò Tagliaferro on 03/04/2017.
 */
public class GUI extends JFrame{
    private JComboBox piano;
    private JPanel mainPane;

    public GUI(BTLayer frs, BTLayer scnd){
        super("Rappresentazione grafica maze");
        piano.addItem(frs);
        piano.addItem(scnd);
        setVisible(true);
        setContentPane(mainPane);
        pack();
    }
}
