/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package places;

import animals.Prey;
import java.util.concurrent.Semaphore;

/**
 * Intersection is a place on the map which only 1 prey at a time can occupy.
 * @author weraz
 */
public class Intersection {
    private final Semaphore o;
    private boolean occupied;
    
    /**
     * Constructor of Intersection.
     */
    public Intersection () {
        this.occupied = false;
        this.o = new Semaphore(1);
    }
    
    /**
     * Handles prey entering the intersection.
     * @param prey
     * @throws InterruptedException 
     */
    public synchronized void enter(Prey prey) throws InterruptedException {
      int count = 0;
      while (true)
      {     o.acquire();
            if (isOccupied() == false){
                setOccupied(true);
               o.release();
               break;
           }
           o.release();
           count++;
           
           try { wait(1000); }
           catch (InterruptedException e) { } 
           finally {} 
           
           if (count > 10 ){
               prey.handleDeath();
           }
      } 
    }
    
    /**
     * Handles prey leaving the intersection.
     * @throws InterruptedException 
     */
    public void leave() throws InterruptedException {
        o.acquire();
        setOccupied(false);
        o.release();
    }

    /**
     * @return the occupied
     */
    public boolean isOccupied() {
        return occupied;
    }

    /**
     * @param occupied the occupied to set
     */
    public void setOccupied(boolean occupied) {
        this.occupied = occupied;
    }
    
}
