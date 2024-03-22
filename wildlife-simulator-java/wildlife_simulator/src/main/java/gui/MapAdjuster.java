/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package gui;

import static gui.Map.getFoodSources;
import static gui.Map.getHideouts;
import static gui.Map.getWaterSources;
import static gui.Map.paint;
import static gui.Map.unpaint;
import places.FoodSource;
import places.Hideout;
import places.WaterSource;
import static wildlifesimulator.Spawner.preyCount;
import static wildlifesimulator.Spawner.preyCountAccess;

/**
 * Adds/removes resources available to preys if criterion of preyCount is met.
 * @author weraz
 */
public class MapAdjuster {
    private static String currentMap = "deafult";
    
    
    /**
     * Constructor of MapAdjuster.
     */
    public MapAdjuster(){
        startMap();
    }
   
    /**
     * Changes the number of sources on a map if applicable.
     * @throws InterruptedException 
     */
    public static void adjustMap() throws InterruptedException{
        preyCountAccess.acquire();
        int preysNumber = preyCount;
        preyCountAccess.release();
        
        if (0 <= preysNumber && preysNumber <= 15){
            if (!getCurrentMap().equals("deafult")){
                defaultMap();
            }
        } else if (15 < preysNumber && preysNumber <= 30 ){
            if (!getCurrentMap().equals("en1")){
                changeMap("en1");
            }
        } else {
            if (!getCurrentMap().equals("en2")){
                changeMap("en2");
            }   
        }
    }
    
    /**
     * Changes the map to default map with 5 hideouts and 5 sources type spots.
     */
    private static void defaultMap(){
        if (currentMap.equals("deafult")){
            return;
        }
        
        for (int i=5; i<getHideouts().size(); ++i){
            Hideout hideout = getHideouts().get(i);
            if (hideout.isPresent == true){
                unpaint(hideout, hideout.getLocation());
                hideout.isPresent = false;
            } else {
                break;
            }
        }
        
        for (int i=5; i<getWaterSources().size(); ++i){
            WaterSource ws = getWaterSources().get(i);
            if (ws.isPresent == true){
                unpaint(ws, ws.getLocation());
                ws.isPresent = false;
            } else {
                break;
            }
        }
        
        for (int i=5; i<getFoodSources().size(); ++i){
            FoodSource es = getFoodSources().get(i);
            if (es.isPresent == true){
                unpaint(es,es.getLocation());
                es.isPresent = false;
            } else {
                break;
            }
        }
        currentMap = "deafult";
        
} 
    
    /**
     * Changes the map to adjust number od hideouts and sources.
     * @param type either en1 (7 spots each type) or en2 (9 spots each type)
     */
    private static void changeMap(String type){
        int numSpots;
        if (type.equals("en1")){
            if (currentMap.equals("en1")){
                return;
            }
            numSpots = 7;
            currentMap = "en1";
        } else {
            if (currentMap.equals("en2")){
                return;
            }
            numSpots = 9;
            currentMap = "en2";
        }
       
        for (int i=5; i<getHideouts().size(); ++i){
            Hideout hideout = getHideouts().get(i);
            if (i < numSpots && hideout.isPresent == false){
                paint(hideout, hideout.getColor(), hideout.getLocation());
                hideout.isPresent = true;
            } else if ( i >= numSpots && hideout.isPresent == true) {
                unpaint(hideout, hideout.getLocation());
                hideout.isPresent = false;
            }
        }
        
        for (int i=5; i<getWaterSources().size(); ++i){
            WaterSource ws = getWaterSources().get(i);
            if (i < numSpots && ws.isPresent == false){
                paint(ws, ws.getColor(), ws.getLocation());
                ws.isPresent = true;
            } else if (i >= numSpots && ws.isPresent == true){
                unpaint(ws, ws.getLocation());
                ws.isPresent = false;
            }
        }
        
        for (int i=5; i<getFoodSources().size(); ++i){
            FoodSource es = getFoodSources().get(i);
            if (i < numSpots && es.isPresent == false){
                paint(es, es.getColor(), es.getLocation());
                es.isPresent = true;
            } else if (i >= numSpots && es.isPresent == true) {
                unpaint(es,es.getLocation());
                es.isPresent = false;
            }
        } 
        
    }
    
    /**
     * Creates map at the start of the game.
     */
    private void startMap() {
        for (int i=0; i<5; ++i){
            Hideout hideout = getHideouts().get(i);
            hideout.isPresent = true;
            paint(hideout, hideout.getColor(), hideout.getLocation());
        }
        
        for (int i=0; i<5; ++i){
            WaterSource ws = getWaterSources().get(i);
            ws.isPresent = true;
            paint(ws, ws.getColor(), ws.getLocation());
        }
        
        for (int i=0; i<5; ++i){
            FoodSource es = getFoodSources().get(i);
            es.isPresent = true;
            paint(es, es.getColor(), es.getLocation());
        } 
    }

    /**
     * @return the currentMap
     */
    public static String getCurrentMap() {
        return currentMap;
    }

    /**
     * @param aCurrentMap the currentMap to set
     */
    public static void setCurrentMap(String aCurrentMap) {
        currentMap = aCurrentMap;
    }
}
