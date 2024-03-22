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
 * Button that lets the prey to change its route.
 * @author weraz
 */
public class RouteChanger extends JButton{
    private final Icon deafultIcon = new ImageIcon(".\\src\\main\\images\\change_route.png");
    private final Icon clickedIcon = new ImageIcon(".\\src\\main\\images\\change_route_clicked.png");
    
    /**
     * Constructor
     * @param loc location on GUI Frame
     */
    public RouteChanger(Point loc){
        setIcon(deafultIcon);
        setBounds(loc.x,loc.y, 90,90);
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
}
}
