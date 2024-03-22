/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package places;

import java.awt.Color;
import java.awt.Point;


/**
 * Class WaterSource is a representation of a place where preys can drink water
 * @author weraz
 */
public class WaterSource extends Source {
    /**
     * Constructor
     * @param location coordinated on a (x,y) board
     * @param capacity maximum number of preys that can simultaneously use the resource
     * @param replenishingSpeed how fast are goods being refilled
     * @param name name of this resource
     * @param goods number of goods (water) that preys can drink
     * @param path
     */
    public WaterSource(Point location, int capacity, int replenishingSpeed, String name, int goods, String path){
        super(location, Color.BLUE, "water", capacity, replenishingSpeed, name, goods, path);
    }


}
