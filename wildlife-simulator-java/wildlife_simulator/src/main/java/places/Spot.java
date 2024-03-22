/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package places;

import animals.Animal;
import animals.Prey;
import gui.places.Rectangle;
import java.awt.Color;
import java.awt.Point;
import java.util.concurrent.Semaphore;

/**
 * Class Spot represent place on the (x,y) board with certain capacity and
 * corresponding GUI board color.
 * @author weraz
 */
public class Spot {
    public Point location;
    private Color color;
    public String type;
    int capacity;
    private int currentCapacity;
    Semaphore door;
    private Rectangle rectangle;
    public boolean isPresent = false;
    
    /**
     * Constructor
     * @param location coordinated on a (x,y) board
     * @param color color of the square in GUI board
     * @param type water, food, hideout
     * @param capacity maximum number of preys that can simultaneously use the resource
     */
    
    protected Spot(Point location, Color color, String type, int capacity){
        this.setColor(color);
        this.setLocation(location);
        this.setType(type);
        this.setCapacity(capacity);
        this.setCurrentCapacity(0);
        door = new Semaphore(1);
    }
    
    /**
     * Shows information about type and capacity of the spot.
     * @return 
     */
    public String showInfo(){
        return(String.format("\nTYPE %s\nCAPACITY %2d /%2d", type, currentCapacity, capacity));
};

    /**
     * @return the location
     */
    public Point getLocation() {
        return location;
    }

    /**
     * @param location the location to set
     */
    private void setLocation(Point location) {
        this.location = location;
    }

    /**
     * @return the color
     */
    public Color getColor() {
        return color;
    }

    /**
     * @param color the color to set
     */
    private void setColor(Color color) {
        this.color = color;
    }

    /**
     * @return the type
     */
    public String getType() {
        return type;
    }

    /**
     * @param type the type to set
     */
    private void setType(String type) {
        this.type = type;
    }

    /**
     * @return the capacity
     */
    public int getCapacity() {
        return capacity;
    }

    /**
     * @param capacity the capacity to set
     */
    private void setCapacity(int capacity) {
        this.capacity = capacity;
    }

    /**
     * @return the currentCapacity
     */
    public int getCurrentCapacity() {
        return currentCapacity;
    }

    /**
     * @param currentCapacity the currentCapacity to set
     */
    private void setCurrentCapacity(int currentCapacity) {
        this.currentCapacity = currentCapacity;
    }
   
    
    public synchronized void enter(Prey p) throws InterruptedException {
      int count = 0;
      while(getCurrentCapacity() == getCapacity()) 
      {
           //System.out.println("count: " + count);
           try { wait(1000); }
           catch (InterruptedException e) { } 
           finally {} 
           count++;
           if (count == 10){
               p.handleDeath();
               return;
           }
           
      } 
      door.acquire();
      this.currentCapacity++;
      door.release();
    }
    
    public void leave(Animal a) throws InterruptedException{
        door.acquire();
        this.currentCapacity--;
        door.release();
    }

    /**
     * @return the rectangle
     */
    public Rectangle getRectangle() {
        return rectangle;
    }

    /**
     * @param rectangle the rectangle to set
     */
    public void setRectangle(Rectangle rectangle) {
        this.rectangle = rectangle;
    }
  
};
    
