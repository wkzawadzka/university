/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package animals;

import gui.animals.AnimalIcon;
import gui.animals.IconDeloader;
import gui.animals.IconLoader;
import java.awt.Point;
import java.io.IOException;
import static java.lang.Integer.max;
import static java.lang.Thread.sleep;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.TimeUnit;
import java.util.logging.Level;
import java.util.logging.Logger;
import static wildlifesimulator.AStarPathFinder.euclideanDistance;
import static wildlifesimulator.AStarPathFinder.findPath;
import static wildlifesimulator.Spawner.preys;
import static wildlifesimulator.Spawner.preysListAccess;

/**
 * Predator, a type of an animal.
 * @author weraz
 */
public class Predator extends Animal {
    private Prey target;
    private AnimalIcon normalIcon;
    private AnimalIcon relaxedIcon;
    private boolean relaxMode = false;
    
     /**
     * Constructor of Predator
     * @param name      id-string unique for each animal
     * @param speed     number of seconds animal will be sleeping after each move
     *                  (the higher speed value the slower animal moves)
     * @param strength  how strong an animal is in 0-8 range
     * @param location  point that is location in 2D grid board
     * @throws java.io.IOException
     */
    public Predator(String name, int speed, int strength, Point location) throws IOException{
        super(name, speed, strength, "seal", location);
        this.setPath(".\\src\\main\\images\\animals\\relaxed-seal.png");
        this.relaxedIcon = new AnimalIcon(this, (float) 1.3);
        this.setPath(".\\src\\main\\images\\animals\\seal-pro.png");
        this.normalIcon = new AnimalIcon(this, (float) 1.3);
        super.setIcon(normalIcon);
    }
    
     /**
     * Finds closest Animal that is instance of Prey class.
     * @return object Prey - closest prey animal
     * @throws java.lang.InterruptedException 
     */
    public Prey findClosestPrey() throws InterruptedException{
        preysListAccess.acquire();
        if (preys.isEmpty()){
            // there are no preys 
            preysListAccess.release();
            return null; 
        }
        
        List<Double> list = new ArrayList();
        for (int i = 0; i<preys.size(); i++) {
            if (preys.get(i) == null){
                list.add((double)1000);
            } else {
                list.add(euclideanDistance(getLocation(), preys.get(i).getLocation()));
            }
        }
        double mini = Collections.min(list);
        if (mini > 13){
            // all preys are dead or too far away
            preysListAccess.release();
            return null;
        }
        Prey p = preys.get(list.indexOf(mini));
        preysListAccess.release();
        return p;
    }
    
     /**
     * Checks if prey is in the same location and if it is, returns this prey object.
     * @return object Prey if there is prey in same location null otherwise
     * @throws java.lang.InterruptedException 
     */
    public Prey isPreyHere() throws InterruptedException{
        preysListAccess.acquire();
        for (int i = 0; i<preys.size(); i++) {
            if (preys.get(i) == null){
                continue;
            }
            if (preys.get(i).getLocation().equals(getLocation())){
                Prey p = preys.get(i);
                preysListAccess.release();
                return p;
            }
        }
        preysListAccess.release();
        return null;
    }
    
    
    /**
     * Kills an animal by setting running atomic boolean to false and unloading its icon from GUI.
     */
    @Override
    public void die(){
        super.die();
        if (!isRelaxMode()){
            setIcon(this.getRelaxedIcon());
        } else {
            setIcon(this.getNormalIcon());
        }
        (new IconDeloader(this, true, false)).execute();
    }
        
    
    /**
     * Puts the predator in relax mode. Changes its color on the map, sets the current target to null.
     */
    public void relax(){
        if (!isRelaxMode()){
            (new IconDeloader(this, false, true)).execute();
            try {
                sleep(100);
            } catch (InterruptedException ex) {
                Logger.getLogger(Predator.class.getName()).log(Level.SEVERE, null, ex);
            }
            setRelaxMode(true);
            setTarget(null);
            plan = null;
            setIcon(this.getRelaxedIcon());
            (new IconLoader(this)).execute(); // repaint
            
            // relax & sleep
            try {
                TimeUnit.SECONDS.sleep(6);
            } catch (InterruptedException ex) {
                Logger.getLogger(Predator.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
    
    
    /**
     * Puts the predator in hunt mode. Changes its icon to normal mode. 
     */
    public void hunt(){
        if (isRelaxMode()){
            (new IconDeloader(this, false, true)).execute();
            try {
                sleep(100);
            } catch (InterruptedException ex) {
                Logger.getLogger(Predator.class.getName()).log(Level.SEVERE, null, ex);
            }
            setIcon(this.getNormalIcon());
            setRelaxMode(false);
            (new IconLoader(this)).execute(); // repaint
        }
    }
    
    
    /**
     * Attacks given prey. Results in change to either Predator's health or Prey's health according 
     * to the difference in strengths between these two.
     * @param p Prey object to attack
     */
    public void attack(Prey p){
        int preyStrength = p.getStrength();
        int difference = getStrength() - preyStrength;
        
        if (difference > 0){
           p.setHealth(max(0, p.getHealth()-difference));
        } 
        else if (difference < 0){
            setHealth(max(0, getHealth()+difference));
        }
        
        if (getHealth() == 0){
            die();
            return;
        }
        relax();
    }
    
    
    
    /**
     * Starts running predator's thread routine.
     */
    @Override
    public void run() {
        super.run();
        int step = 0;
        
        try {
            setTarget(findClosestPrey());
        } catch (InterruptedException ex) {
            Logger.getLogger(Predator.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        if (getTarget()!= null){
            plan = findPath(false, getLocation(), getTarget().getLocation());
        } else { 
            relax();
        }
        
        while (super.running.get()) {
            try {
        
                if (!isRelaxMode() && !plan.isEmpty()){
                    Point newLocation = plan.get(0);
                    setLocation(newLocation);
                    plan.remove(0);
                    (new IconLoader(this)).execute(); // repaint
                }
                //(new IconLoader(this)).execute(); // repaint
                                
                // attack if hunting mode && prey is in the same location
                Prey possibleTarget = isPreyHere();
                if (!isRelaxMode() && possibleTarget != null && possibleTarget.isAtHideout() == false){
                    attack(isPreyHere());
                }
                
                // every 5 steps, check for closest prey
                // if prey is dead, find new target 
                if (step % 5 == 0 || (!isRelaxMode() && (getTarget() != null && !getTarget().running.get()))){
                    setTarget(findClosestPrey());
                    if (target == null){
                        relax();
                    } else {
                        plan = findPath(false, getLocation(), getTarget().getLocation());
                        hunt();
                    }
                }
                   
                    
                // advance time depedning on speed of predator
                TimeUnit.SECONDS.sleep(this.getSpeed());
                step++;
                
                

                
            } catch (InterruptedException ex) {
                Logger.getLogger(Predator.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }

    
    /**
     * Gets the current target - concrete prey object.
     * @return the target
     */
    public Prey getTarget() {
        return target;
    }

    /**
     * Sets the current target - concrete prey object.
     * @param target the target to set
     */
    public void setTarget(Prey target) {
        this.target = target;
    }

    /**
     * Checks if predator is in relax mode.
     * @return the relaxMode
     */
    public boolean isRelaxMode() {
        return relaxMode;
    }

    /**
     * Sets if predator is in relax mode.
     * @param relaxMode the relaxMode to set
     */
    public void setRelaxMode(boolean relaxMode) {
        this.relaxMode = relaxMode;
    }

    /**
     * Gets the AnimalIcon icon which represents an animal not in relax mode.
     * @return the normalIcon
     */
    public AnimalIcon getNormalIcon() {
        return normalIcon;
    }

    /**
     * Sets the AnimalIcon icon which represents an animal not in relax mode.
     * @param normalIcon the normalIcon to set
     */
    public void setNormalIcon(AnimalIcon normalIcon) {
        this.normalIcon = normalIcon;
    }

    /**
     * Gets the AnimalIcon icon which represents an animal in relax mode.
     * @return the relaxedIcon
     */
    public AnimalIcon getRelaxedIcon() {
        return relaxedIcon;
    }

    /**
     * Sets the AnimalIcon icon which represents an animal in relax mode.
     * @param relaxedIcon the relaxedIcon to set
     */
    public void setRelaxedIcon(AnimalIcon relaxedIcon) {
        this.relaxedIcon = relaxedIcon;
    }
}
