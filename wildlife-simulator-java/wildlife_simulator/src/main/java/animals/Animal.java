/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package animals;

import gui.animals.AnimalIcon;
import gui.animals.IconDeloader;
import java.awt.Point;
import java.util.List;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * An animal class. Can be either prey or predator.
 * @author weraz
 */
public class Animal implements Runnable{
    private final String id;
    private int health;
    private final int speed;
    private final int strength;
    private final String species;
    private Point location;
    private String objective;
    private String path;
    protected final AtomicBoolean running = new AtomicBoolean(false);
    private AnimalIcon icon;
    protected List<Point> plan;

    
    /**
     * Constructor of Animal
     * @param name      id-string unique for each animal
     * @param speed     number of seconds animal will be sleeping after each move
     *                  (the higher speed value the slower animal moves)
     * @param strength  how strong an animal is in 0-8 range
     * @param species   string name of species: either penguin (prey) or seal (predator)
     * @param location  point that is location in 2D grid board
     */
    protected Animal(String name, int speed, int strength, String species, Point location){
        this.id = name;
        this.health =  10; // at the beggining, Animal has 10/10 health
        this.speed = speed;
        this.strength = strength;
        this.species = species;
        this.location = location;
    }  
 
    /**
     * Kills an animal by setting running atomic Boolean to false and unloading its icon from GUI.
     */
    public void die(){
        running.set(false);
        (new IconDeloader(this, true, false)).execute();
    }
    
    /**
     * Combines stats of strength and health of an animal.
     * @return string - strength and health data
     */
    @Override
    public String toString(){
        return ("\nstrength: " + this.getStrength()
                + "\nhealth: " + this.getHealth() + " / 10")
                + "\nlocation: (" + this.getLocation().x + ", " + this.getLocation().y + ")";
    }

    /**
     * Gets integer value of health level.
     * @return the health
     */
    public int getHealth() {
        return health;
    }

    /**
     * Sets integer value of health level.
     * @param health the health to set
     */
    protected void setHealth(int health) {
        this.health = health;
    }

    /**
     * Gets integer value of speed.
     * @return the speed
     */
    public int getSpeed() {
        return speed;
    }


    /**
     * Gets integer value of strength level.
     * @return the strength
     */
    public int getStrength() {
        return strength;
    }

    /**
     * Gets the current Point(x,y) location of an animal.
     * @return the location
     */
    public Point getLocation() {
        return location;
    }

    /**
     * Sets the current Point(x,y) location of an animal.
     * @param location the location to set
     */
    public void setLocation(Point location) {
        this.location = location;
    }

     /**
     * Starts running animal's thread routine.
     */
    @Override
    public void run() {
        running.set(true);
    }

    /**
     * Gets the path to the animal's icon.
     * @return the path
     */
    public String getPath() {
        return path;
    }

    /**
     * Sets the path to the animal's icon.
     * @param path the path to set
     */
    public void setPath(String path) {
        this.path = path;
    }

    /**
     * Gets the animal icon of type AnimalIcon (JPanel).
     * @return the icon
     */
    public AnimalIcon getIcon() {
        return icon;
    }

    /**
     * Sets the animal icon of type AnimalIcon (JPanel).
     * @param icon the icon to set
     */
    public void setIcon(AnimalIcon icon) {
        this.icon = icon;
    }

    /**
     * Gets the list of points - an A* algorithm produced plan of moves.
     * @return the plan
     */
    public List<Point> getPlan() {
        return plan;
    }

    /**
     * Sets the list of points - an A* algorithm produced plan of moves.
     * @param plan the plan to set
     */
    public void setPlan(List<Point> plan) {
        if (this.plan != null){
            this.plan.clear();
        }
        this.plan = plan;
    }

    /**
     * Gets current string objective (want animal want to do or where it wants to go).
     * @return the objective
     */
    public String getObjective() {
        return objective;
    }

    /**
     * Sets current string objective (want animal want to do or where it wants to go).
     * @param objective the objective to set
     */
    public void setObjective(String objective) {
        this.objective = objective;
    }

    /**
     * Gets id unique string of an animal.
     * @return the id
     */
    public String getId() {
        return id;
    }

    /**
     * Gets the species type of an animal - either penguin or seal.
     * @return the species
     */
    public String getSpecies() {
        return species;
    }
    
}
