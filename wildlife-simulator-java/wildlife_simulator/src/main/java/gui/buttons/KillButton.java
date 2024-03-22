/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package gui.buttons;

import java.awt.Color;
import java.awt.Point;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;

/**
 * KillButton is Swing button used to kill animals.
 * @author weraz
 */
public class KillButton extends JButton {
    private final Icon deafultIcon = new ImageIcon(".\\src\\main\\images\\animals\\death.png");
    private final Icon clickedIcon = new ImageIcon(".\\src\\main\\images\\animals\\death_clicked.png");
        
/**
 * Constructor of KillButton.
 * @param loc: GUI coordinates od the kill button
 */
public KillButton(Point loc){
        setIcon(deafultIcon);
        setBounds(loc.x,loc.y, 50,50);
        setBackground(new Color(1.0f,1.0f,1.0f,0.0f));
        setBorder(null);
        
        addMouseListener(new MouseAdapter(){
        
            @Override
            public void mouseEntered(MouseEvent e){
                setIcon(clickedIcon);
            }
            
            
            @Override
            public void mouseExited(MouseEvent e){
                setIcon(deafultIcon);
            }
            
        });
}}
