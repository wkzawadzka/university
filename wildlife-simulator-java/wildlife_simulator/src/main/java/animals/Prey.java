/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package animals;

import static gui.Map.getFoodSources;
import static gui.Map.getHideouts;
import static gui.Map.getIntersectionBoard;
import static gui.Map.getWaterSources;
import static gui.MapAdjuster.adjustMap;
import gui.animals.AnimalIcon;
import gui.animals.IconDeloader;
import gui.animals.IconLoader;
import java.awt.Point;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.TimeUnit;
import java.util.logging.Level;
import java.util.logging.Logger;
import places.Source;
import places.Spot;
import static wildlifesimulator.AStarPathFinder.euclideanDistance;
import static wildlifesimulator.AStarPathFinder.findPath;
import static wildlifesimulator.Main.spawner;
import static wildlifesimulator.Spawner.preyCount;
import static wildlifesimulator.Spawner.preyCountAccess;
import static wildlifesimulator.Spawner.preys;
import static wildlifesimulator.Spawner.preysListAccess;
/**
 * Prey is an animal that eats, drinks, hides and reproduces. 
 * @author weraz
 */
public class Prey extends Animal{
    private int waterLevel;
    private int energyLevel;
    private boolean atSpot = false;
    private boolean atHideout = false;
    private Spot target = null;
    public final int index;
    private boolean shouldChangeRoute = false;
    private boolean changedRoute = false;

     /**
     * Constructor of Prey
     * @param name      id-string unique for each animal
     * @param speed     number of seconds animal will be sleeping after each move
     *                  (the higher speed value the slower animal moves)
     * @param strength  how strong an animal is in 0-8 range
     * @param location  point that is location in 2D grid board
     * @param index     unique index of each prey used to access it in preys list
     * @throws java.io.IOException
     */
    public Prey(String name, int speed, int strength, Point location, int index) throws IOException{
        super(name, speed, strength, "penguin", location);
        this.setWaterLevel(10);
        this.setEnergyLevel(10);
        this.setPath(".\\src\\main\\images\\animals\\peng.png");
        super.setIcon(new AnimalIcon(this, 1));
        this.index = index;
    }
    
    
    /**
     * Combines stats of strength, health, water and food level, target location of an prey.
     * @return string - data about the prey
     */
    @Override
    public String toString(){
        String parent = super.toString();
        String newInfo = ("\nfood: " + getEnergyLevel() + " / 10"
                + "\nwater: " + getWaterLevel() + " / 10"
                + "\n\n         going to " 
                + getTarget().type
                + " at (" + getTarget().location.x + ", " 
                + getTarget().location.y + ") ...");
        return parent +  newInfo;
    }
    
    /**
     * Finds the closest objective (Spot) that it will be heading to.
     * @param objective string either hideout, food or water
     * @return 
     */
    public Spot findClosestObjective(String objective){
        List<? extends Spot> spots;
        spots = switch (objective) {
            case "water" -> getWaterSources();
            case "food" -> getFoodSources();
            default -> getHideouts();
        };
        List<Double> list = new ArrayList();
        for (Spot element : spots) {
            if (element.isPresent == false){
                list.add((double)1000);
                continue;
            }
            list.add(euclideanDistance(getLocation(), element.location));
        }
        return spots.get(list.indexOf(Collections.min(list)));
    }
    
    
    /**
     * Finds which spot is most needed out of hideout, food source and water source to go to.
     * @return String: hideout, food or water
     */
    public String findObjective () {
        int minimum;
        List<Integer> list=Arrays.asList(energyLevel, waterLevel, this.getHealth());
        Collections.sort(list);
        minimum = list.get(0);

        if (this.getHealth() == minimum){
            return "hideout";
        }
        if (this.getEnergyLevel() == minimum){
            return "food";
        } else {
            return "water";
        } 
    }
    
    
    /**
     * Checks the level of given parameter.
     * @param objective: string hideout, food or water
     * @return int: level of given parameter
     */
    public int checkLevel(String objective){
        if (objective.equals("water")){
            return getWaterLevel();
        }
        if (objective.equals("food")){
            return getEnergyLevel();
        } else {
            return getHealth();
        }
        
    }
    
    /**
     * Changes the level of given parameter by given difference.
     * @param objective: string hideout, food or water
     * @param diff: int the difference (negative or positive)
     */
    public void changeLevel(String objective, int diff){
        if (objective.equals("health")){
            int newHealth = this.getHealth() + diff;
            if (newHealth >= 0 && newHealth <=10 ){
                this.setHealth(this.getHealth() + diff);
            }
        }
        if (objective.equals("food")){
            int newEnergyLevel = this.energyLevel + diff;
            if (newEnergyLevel >= 0 && newEnergyLevel <=10){
                this.energyLevel = newEnergyLevel;
            }
        } else {
            int newWaterLevel = this.waterLevel + diff;
            if (newWaterLevel >= 0 && newWaterLevel <=10){
                this.waterLevel = newWaterLevel;
            }
        }
    }
    
    /**
     * Handles routine to perform if the prey is at source.
     */
    public void handleSourceRoutine(){
        // eat/drink
        try {if(((Source)getTarget()).useGood()){
            this.changeLevel(getTarget().type, 1);
        }
        } catch (InterruptedException ex) {
            Logger.getLogger(Prey.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        // replenish
        try {
            ((Source)getTarget()).replenish();
        } catch (InterruptedException ex) {
            Logger.getLogger(Prey.class.getName()).log(Level.SEVERE, null, ex);
        }   
    }
    
    
    /**
     * Handles routine to perform if the prey is at hideout.
     */
    public void handleHideoutRoutine(){
        this.changeLevel("hideout", 1);
        setAtHideout(true);
        
        try {
            // reproduce with probability 0.3
            Random rand = new Random();
            float f = rand.nextFloat();
            if (f > (float)0.7){
                spawner.spawnPrey();
            }
        } catch (IOException ex) {
            Logger.getLogger(Prey.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    
    /**
     * Handles any spot routine.
     */
    public void handleSpotRoutine(){
        (new IconDeloader(this, false, false)).execute();
        if (!atSpot){
            atSpot = true;
        }
        
        if (getTarget() instanceof Source){
            this.handleSourceRoutine();
        } else {
            this.handleHideoutRoutine();
        } 
    }
    
    /**
     * Handles finding new target. Finds closest spot and calculates list of Points (moves) to get to it.
     * @param newObjective: string hideout, food or water
     */
    public void handleNewTarget(String newObjective){
           if (atSpot){
               try {
                   target.leave(this);
                   atSpot = false;
                   if ((target.type).equals("hideout")){
                       setAtHideout(false);
                   }
               } catch (InterruptedException ex) {
                   Logger.getLogger(Prey.class.getName()).log(Level.SEVERE, null, ex);
               }
           }
           target = findClosestObjective(newObjective);
           plan = findPath(true, getLocation(), target.location);   
    }
    
    /**
     * Handles death of prey. Decreases prey count and sets itself to null in preys list. 
     */
    public void handleDeath(){
    //(new IconDeloader(this, true)).execute();
    die();
    try {
        preysListAccess.acquire();
        preyCountAccess.acquire();
        preyCount--;
        preys.set(this.index, null);
        preyCountAccess.release();
        preysListAccess.release();
        adjustMap();
    } catch (InterruptedException ex) {
        Logger.getLogger(Prey.class.getName()).log(Level.SEVERE, null, ex);
    }}
    
    /**
     * Handles entering spot if the next move is a spot place. Checks if capacity of given spot allows this prey
     * to enter it.
     */
    public void handleEnteringSpotIfApplicable(){
        if (!atSpot && plan.size() == 1){
            if (plan.get(0).equals(target.location)){
                try {
                    target.enter(this);
                } catch (InterruptedException ex) {
                    Logger.getLogger(Prey.class.getName()).log(Level.SEVERE, null, ex);
                }
    }}}
    
    /**
     * Handles changing route if button was clicked.
     * @param newObjective 
     */
    public void changeRouteObjective(String newObjective){
        List<String> list = new ArrayList<>();
        list.addAll(Arrays.asList("food", "water", "hideout"));
        list.remove(newObjective);
        int randomNum = ThreadLocalRandom.current().nextInt(0, 1 + 1);
        handleNewTarget(list.get(randomNum));
    }
    
     /**
     * Starts running prey's thread routine.
     */
    @Override
    public void run() {
        super.run();
        target = findClosestObjective("hiedout");
        plan = findPath(true, getLocation(), target.location);
        
        int step = 0;
        while (super.running.get()) {
            try {
                // CASE 0: Prey is at destination and stays there
                if (getLocation().equals(target.location) && checkLevel(target.type) != 10){
                    handleSpotRoutine(); // use the resource
                    setChangedRoute(false);
                } else if (getLocation().equals(target.location) && getHealth() == 10 && waterLevel == 10 && energyLevel == 10) {
                    handleSpotRoutine(); // if all parameters high, just chill at some spot
                    setChangedRoute(false);
                } else {
 
                // CASE 1: Find new target if needed
                String newObjective = findObjective();
                if (!target.type.equals(newObjective) && !isChangedRoute()|| (plan.isEmpty() && atSpot == false) || !isChangedRoute() && (getLocation().equals(target.location))){
                    handleNewTarget(newObjective);
                    plan = findPath(true, getLocation(), target.location);
                }
                else if (isShouldChangeRoute()){
                    setShouldChangeRoute(false);
                    changeRouteObjective(newObjective);
                    plan = findPath(true, getLocation(), target.location);
                    setChangedRoute(true);
                }
                
                // handler for when predator would interrupt prey at some source by attacking it
                if (plan.isEmpty() && getLocation().equals(target.location)){
                    plan.add(getLocation());
                    setChangedRoute(false);
                }
                                
                // CASE 2: Completing the route
                Point newLocation = plan.get(0);
                if (getIntersectionBoard()[newLocation.x][newLocation.y] != null){
                    getIntersectionBoard()[newLocation.x][newLocation.y].enter(this);
                }
                setLocation(newLocation);
                plan.remove(0);
                (new IconLoader(this)).execute(); // repaint
                }

                // advance time depedning on speed of prey
                TimeUnit.SECONDS.sleep(this.getSpeed());
                step++;
                
                
                if (getIntersectionBoard()[getLocation().x][getLocation().y] != null){
                    getIntersectionBoard()[getLocation().x][getLocation().y].leave();
                }
                
                // decrease food and water each 5 steps
                if (step % 5 == 0){
                    changeLevel("water", -1);
                    changeLevel("food", -1);
                }
                
                if ((waterLevel == 0) || energyLevel == 0 || getHealth() == 0){
                    handleDeath();
                }
                handleEnteringSpotIfApplicable();
                
            } catch (InterruptedException ex) {
                Logger.getLogger(Prey.class.getName()).log(Level.SEVERE, null, ex);
            }
            
        }
    }
    
    
    /** 
     * Gets current integer water level.
     * @return the waterLevel
     */
    public int getWaterLevel() {
        return waterLevel;
    }

    /**
     * Sets current integer water level.
     * @param waterLevel the waterLevel to set
     */
    private void setWaterLevel(int waterLevel) {
        this.waterLevel = waterLevel;
    }

    /**
     * Gets current integer energy (food) level.
     * @return the energyLevel
     */
    public int getEnergyLevel() {
        return energyLevel;
    }

    /**
     * Sets current integer energy (food) level.
     * @param energyLevel the energyLevel to set
     */
    private void setEnergyLevel(int energyLevel) {
        this.energyLevel = energyLevel;
    }

    /**
     * Checks if this prey is currently at some spot.
     * @return the atSpot
     */
    public boolean isAtSpot() {
        return atSpot;
    }

    /**
     * Sets if this prey is currently at some spot.
     * @param atSpot the atSpot to set
     */
    public void setAtSpot(boolean atSpot) {
        this.atSpot = atSpot;
    }
    /**
     * Gets the current Spot the prey is heading to.
     * @return the target
     */
    public Spot getTarget() {
        return target;
    }

    /**
     * Sets new Spot the prey will be heading to.
     * @param target the target to set
     */
    public void setTarget(Spot target) {
        this.target = target;
    }

    /**
     * @return the atHideout
     */
    public boolean isAtHideout() {
        return atHideout;
    }

    /**
     * @param atHideout the atHideout to set
     */
    public void setAtHideout(boolean atHideout) {
        this.atHideout = atHideout;
    }

    /**
     * @return the shouldChangeRoute
     */
    public boolean isShouldChangeRoute() {
        return shouldChangeRoute;
    }

    /**
     * @param shouldChangeRoute the shouldChangeRoute to set
     */
    public void setShouldChangeRoute(boolean shouldChangeRoute) {
        this.shouldChangeRoute = shouldChangeRoute;
    }

    /**
     * @return the changedRoute
     */
    public boolean isChangedRoute() {
        return changedRoute;
    }

    /**
     * @param changedRoute the changedRoute to set
     */
    public void setChangedRoute(boolean changedRoute) {
        this.changedRoute = changedRoute;
    }
    
}
