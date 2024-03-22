/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package gui.places;

import static gui.BoardPanel.squareSize;
import static gui.BoardPanel.xOrg;
import static gui.BoardPanel.yOrg;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import javax.swing.JPanel;

/**
 * Rectangle is GUI representation of the spot.
 * @author weraz
 */
public class Rectangle extends JPanel {
    private final Color c;
    private final Point p; 
    private final PlaceInfoBox rectangleListener;
    
    
    /**
     * Constructor of Rectangle.
     * @param c color
     * @param p point in 2D array
     * @param rectangleListener 
     */
    public Rectangle(Color c, Point p, PlaceInfoBox rectangleListener){
        this.c = c;
        this.p = p;
        this.rectangleListener = rectangleListener;
    }
    
    /**
     * Paints the rectangle.
     * @param g 
     */
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.setColor(getC());
        g.fillRect(xOrg + getP().x*squareSize,yOrg + getP().y*squareSize,squareSize,squareSize);
    }

    /**
     * @return the rectangleListener
     */
    public PlaceInfoBox getRectangleListener() {
        return rectangleListener;
    }

    /**
     * @return the c
     */
    public Color getC() {
        return c;
    }

    /**
     * @return the p
     */
    public Point getP() {
        return p;
    }
}
