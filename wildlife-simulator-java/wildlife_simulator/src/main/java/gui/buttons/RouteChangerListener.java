/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package gui.buttons;

import animals.Prey;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Listener for RouteChanger button.
 * @author weraz
 */
public class RouteChangerListener implements ActionListener {
    private final Prey prey;
    
    /**
     * Constructor
     * @param a Prey object
     */
    public RouteChangerListener(Prey a){
        this.prey = a;
    }
    
    /**
     * Signals prey to change its route.
     * @param e 
     */
    @Override
    public void actionPerformed(ActionEvent e) {
        this.prey.setShouldChangeRoute(true);
    }
    
}
