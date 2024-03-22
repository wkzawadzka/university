/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package places;

import java.awt.Color;
import java.awt.Point;
import static java.lang.Math.min;
import java.util.concurrent.Semaphore;

/**
 * Source is a type of spot where prey can eat or drink.
 * @author weraz
 */
public class Source extends Spot {
    public final String name;
    private final int replenishingSpeed;
    private final int goods;
    private int currentGoods;
    public final String path;
    private final Semaphore goodsHandler;

    /**
     * Constructor
     * @param location coordinated on a (x,y) board
     * @param capacity maximum number of preys that can simultaneously use the resource
     * @param color color of the square in GUI board
     * @param type water, food, hideout or obstacle
     * @param replenishingSpeed how fast are goods being refilled
     * @param name name of this resource
     * @param goods number of goods (water) that preys can drink
     * @param path path to icon representing this spot in information window
     */
    public Source(Point location, Color color, String type, int capacity, int replenishingSpeed, String name, int goods, String path){
        super(location, color, type, capacity);
        this.replenishingSpeed = replenishingSpeed;
        this.name = name;
        this.goods = goods;
        this.currentGoods = goods;
        this.path = path;
        this.goodsHandler = new Semaphore(1);
    }

    /**
     * Creates string of information about given source.
     * @return 
     */
    @Override
    public String showInfo(){
        String info1 = super.showInfo();
        String info2 = String.format("\nGOODS %2d /%2d\nREPLENISHING SPEED %2d\n",currentGoods,goods, replenishingSpeed);
        return info1 + info2;
};
       
    /**
     * Replenishes resource.
     * @throws InterruptedException 
     */
    public void replenish() throws InterruptedException{
        goodsHandler.acquire();
        if (currentGoods < goods){
            currentGoods = min(currentGoods + replenishingSpeed, goods);
        }
        goodsHandler.release();
    };
    
    /**
     * Uses resource's goods.
     * @return
     * @throws InterruptedException 
     */
    public boolean useGood() throws InterruptedException{
        goodsHandler.acquire();
        if (this.currentGoods >= 1){
            this.currentGoods--;
            goodsHandler.release();
            return true;
        }
        
        goodsHandler.release();
        return false;
    }
    

    /**
     * @return the name
     */
    public String getName() {
        return name;
    }


    /**
     * @return the replenishingSpeed
     */
    public int getReplenishingSpeed() {
        return replenishingSpeed;
    }


    /**
     * @return the goods
     */
    public int getGoods() {
        return goods;
    }


    /**
     * @return the currentGoods
     */
    public int getCurrentGoods() {
        return currentGoods;
    }

    /**
     * @param currentGoods the currentGoods to set
     */
    private void setCurrentGoods(int currentGoods) {
        this.currentGoods = currentGoods;
    }

    /**
     * @return the path
     */
    public String getPath() {
        return path;
    }

}
