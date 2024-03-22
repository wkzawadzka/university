/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package places;

import java.awt.Color;
import java.awt.Point;

/**
 * Class Hideout represents a spot where preys can go and are protected
 * from the predators attacks.
 * @author weraz
 */
public class Hideout extends Spot{
    public final String name;
    public final String path;
    
    /**
     * Constructor
     * @param location coordinated on a (x,y) board
     * @param capacity maximum number of preys that can simultaneously use the hideout
     * @param name name of this hideout
     * @param path path to icon representing this spot in information window
     */
    public Hideout(Point location, int capacity, String name, String path){
        super(location, Color.BLACK, "hideout", capacity);
        this.name = name;
        this.path = path;
    }

    /**
     * @return the name
     */
    public String getName() {
        return name;
    }


    /**
     * @return the path
     */
    public String getPath() {
        return path;
    }

}
