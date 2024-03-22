/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package gui.buttons;

import animals.Animal;
import animals.Prey;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import static wildlifesimulator.Main.jFrame;

/**
 * KillButtonListener is an action listener for KillButton.
 * @author weraz
 */
public class KillButtonListener implements ActionListener {
    private final Animal animal;
    
    /**
     * Constructor of KillButtonListener.
     * @param a: Animal object that will be killed if action performed
     */
    public KillButtonListener(Animal a){
        this.animal = a;
    }
    
    /**
     * Kills the animal.
     * @param e 
     */
    @Override
    public void actionPerformed(ActionEvent e) {
            this.animal.getIcon().setBounds(0, 0, 800, 800);
            jFrame.remove(this.animal.getIcon());
            this.animal.die();
            if (this.animal instanceof Prey prey){
                prey.handleDeath();
            }
            jFrame.InfoText.setText(null);
            jFrame.infoNameLabel.setText(null);
            jFrame.getKillButton().setVisible(false);
            jFrame.getRouteButton().setVisible(false);
    }
    
}
