package gui;

import java.awt.Color;
import java.awt.Graphics;
import javax.swing.JPanel;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 * Class BoardPanel creates board grid in GUI frame.
 * @author weraz
 */
public class BoardPanel extends JPanel {
    static final public int columns = 30;
    static final public int rows = 26;
    static final public int squareSize = 21;
    static final public int xOrg = 43;
    static final public int yOrg = 62;
            
           
    /**
     * Paints the board.
     * @param g 
     */
    @Override
    protected void paintComponent(Graphics g){
        super.paintComponent(g);
        g.setColor(Color.ORANGE);
        
        for (int i = 0; i <= rows; i++){
            g.drawLine(xOrg, yOrg + i * squareSize, xOrg + columns *squareSize, yOrg + i*squareSize);
        }
        
        for (int i = 0; i <= columns; i++){
            g.drawLine(xOrg + i*squareSize, yOrg , xOrg + i *squareSize, yOrg + rows*squareSize);
        }
    };
    
}
