/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package places;

import java.awt.Color;
import java.awt.Point;

/**
 * Obstacle is a spot on a board where prey cannot step onto.
 * @author weraz
 */
public class Obstacle{
    private final Point location;
    private final Color color;
    
    /**
     * Constructor
     * @param location coordinates on a (x,y) board
     */
    public Obstacle(Point location){
        this.location = location;
        this.color = Color.DARK_GRAY;
    }

    /**
     * @return the location
     */
    public Point getLocation() {
        return location;
    }


    /**
     * @return the color
     */
    public Color getColor() {
        return color;
    }

}
