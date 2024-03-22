/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package places;

import java.awt.Color;
import java.awt.Point;

/**
 * Class FoodSource is a representation of a place where preys can eat.
 * @author weraz
 */
public class FoodSource extends Source {
    /**
     * Constructor
     * @param location coordinated on a (x,y) board
     * @param capacity maximum number of preys that can simultaneously use the resource
     * @param replenishingSpeed how fast are goods being refilled
     * @param name name of this resource
     * @param goods number of goods (food) that preys can eat
     * @param path 
     */
    public FoodSource(Point location, int capacity, int replenishingSpeed, String name, int goods, String path){
        super(location, Color.YELLOW, "food", capacity, replenishingSpeed, name, goods, path);
    }

}
