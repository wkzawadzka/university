/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package gui.buttons;

import gui.Window;
import java.awt.Color;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JButton;
import static wildlifesimulator.Main.spawner;

/**
 * SpawnButton is Swing button used for adding new animals.
 * @author weraz
 */
public class SpawnButton extends JButton {
    private final Color clickColor = new Color(154, 179, 219);
    private final Color deafultColor = Color.LIGHT_GRAY;
    
    /**
     * Constructor of SpawnButton
     * @param text: string to display as button's name
     */
    public SpawnButton(String text){
        setText(text);
        setBackground(deafultColor);
        setBorder(null);
        
        addMouseListener(new MouseAdapter(){
        
            @Override
            public void mouseEntered(MouseEvent e){
                setBackground(clickColor);
            }
            
            
            @Override
            public void mouseExited(MouseEvent e){
                setBackground(deafultColor);
            }
            
            @Override
            public void mouseClicked(MouseEvent e){
                if (text.equals("PREY")){
                    try {
                        spawner.spawnPrey();
                    } catch (IOException ex) {
                        Logger.getLogger(Window.class.getName()).log(Level.SEVERE, null, ex);
                    }
                } else {
                    try {
                        spawner.spawnPredator();
                    } catch (IOException ex) {
                        Logger.getLogger(SpawnButton.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }
        });
    
    }
}

