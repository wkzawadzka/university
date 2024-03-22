/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package gui.animals;

import animals.Animal;
import static gui.BoardPanel.squareSize;
import static gui.BoardPanel.xOrg;
import static gui.BoardPanel.yOrg;
import java.awt.Point;
import javax.swing.SwingWorker;

/**
 * Handles loading an animal icon onto GUI board.
 * @author weraz
 */
public class IconLoader  extends SwingWorker<Void, Object> {
    private final AnimalIcon icon;
    private final Point location;
    
    /**
     * Constructor for IconLoader.
     * @param a: an Animal object which icon will be loaded
     */
    public IconLoader(Animal a){
        this.icon = a.getIcon();
        this.icon.setClickable(true);
        this.location = a.getLocation();
    }

    /**
     * Accesses GUI and makes changes.
     */
   @Override
   protected void done() {
       this.icon.setBounds(xOrg + location.x*squareSize,yOrg + location.y*squareSize, 20, 20);
       this.icon.changeCoordinates(location);
   }

     /**
     * Does nothing as the thread logic is in animal run() method.
     */
    @Override
    protected Void doInBackground() throws Exception {
        return null;
    }

}
