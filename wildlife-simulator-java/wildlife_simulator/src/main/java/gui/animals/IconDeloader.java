/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package gui.animals;

import animals.Animal;
import javax.swing.SwingWorker;
import static wildlifesimulator.Main.jFrame;

/**
 * Handles unloading an animal icon from the board temporarily or absolutely.
 * @author weraz
 */
public class IconDeloader extends SwingWorker<Void, Object> {
    private final Animal animal; 
    private final boolean isFinal;
    private final boolean clickable;
    
    
    /**
     * Constructor for IconDeloader.
     * @param a: an Animal object which icon will be unloaded
     * @param isFinal: unload temporarily or absolutely
     * @param clickable: after unloading, should an animal still be clickable?
     */
    public IconDeloader(Animal a, boolean isFinal, boolean clickable){
        this.animal = a;
        this.isFinal = isFinal;
        this.clickable = clickable;
    }
    
    /**
     * Does nothing as the thread logic is in animal run() method.
     * @return
     * @throws Exception 
     */
    @Override
    protected Void doInBackground() throws Exception {
        return null;
    }
    
    /**
     * Accesses GUI and makes changes.
     */
   @Override
   protected void done() {
        this.animal.getIcon().setBounds(0, 0, 1, 1);
        this.animal.getIcon().setClickable(this.clickable);
        this.animal.getIcon().repaint();
        if (isFinal == true){
            jFrame.remove(this.animal.getIcon());
        }
} 
}
