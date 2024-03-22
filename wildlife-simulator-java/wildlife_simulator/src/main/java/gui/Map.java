/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package gui;

import static gui.BoardPanel.columns;
import static gui.BoardPanel.rows;
import gui.places.PlaceInfoBox;
import gui.places.Rectangle;
import java.awt.Color;
import java.awt.Point;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;
import places.FoodSource;
import places.Hideout;
import places.Intersection;
import places.Obstacle;
import places.Spot;
import places.WaterSource;
import wildlifesimulator.Board;
import static wildlifesimulator.Main.board;
import static wildlifesimulator.Main.jFrame;

/**
 * This class creates a custom map structure.
 * @author weraz
 */
public class Map {
    private static final List<Hideout> hideouts = new ArrayList<>();
    private static final List<WaterSource> waterSources = new ArrayList<>();
    private static final List<FoodSource> foodSources = new ArrayList<>();
    private static Intersection[][] intersectionBoard;

    /**
     * Adds created spots onto GUI.
     */
    public void createCustomMap(){
        setIntersectionBoard(new Intersection[columns][rows]);
        this.createWaterSpots(board);
        this.createFoodSpots(board);
        this.createHideouts(board);
        this.createLanes(board);
        
        for (int i=0; i<getHideouts().size(); ++i){
            Hideout hideout = getHideouts().get(i);
            this.createGUISpot(hideout, hideout.getColor(), hideout.getLocation());
        }
        
        for (int i=0; i<getWaterSources().size(); ++i){
            WaterSource ws = getWaterSources().get(i);
            this.createGUISpot(ws, ws.getColor(), ws.getLocation());
        }
      
        for (int i=0; i<getFoodSources().size(); ++i){
            FoodSource fs = getFoodSources().get(i);
            this.createGUISpot(fs, fs.getColor(), fs.getLocation());
        }
    }
    
    /**
     * Creates all water sources.
     * @param board 
     */
     public void createWaterSpots(Board board){
        List<Point> tempCoords = new ArrayList<>();
        Collections.addAll(tempCoords, new Point(0,0),
                                         new Point(5,1) ,
                                         new Point(29,12),
                                         new Point(8,15),
                                         new Point(0,23),
                                         new Point(27, 3),
                                         new Point(21, 25),
                                         new Point(23,25),
                                         new Point(9,2)
        );
        
        List<String> tempNames = new ArrayList<>();
        Collections.addAll(tempNames,   "Chilling spot", 
                                        "Under bridge", 
                                        "By the pool",
                                        "At the zoo",
                                        "Sunny pool",
                                        "Touch grass",
                                        "Abandoned water bottles",
                                        "Campfire by a lake",
                                        "On a beach");
           
        List<String> tempPaths = new ArrayList<>();
        Collections.addAll(tempPaths,   ".\\src\\main\\images\\waterSource\\water0.jpg", 
                                        ".\\src\\main\\images\\waterSource\\water1.jpg", 
                                        ".\\src\\main\\images\\waterSource\\water2.jpg",
                                        ".\\src\\main\\images\\waterSource\\water3.jpg",
                                        ".\\src\\main\\images\\waterSource\\water4.jpg",
                                        ".\\src\\main\\images\\waterSource\\water5.jpg",
                                        ".\\src\\main\\images\\waterSource\\water6.jpg",
                                        ".\\src\\main\\images\\waterSource\\water7.jpg",
                                        ".\\src\\main\\images\\waterSource\\water8.jpg");
        for (int i = 0; i<tempCoords.size(); ++i){
            int goods = ThreadLocalRandom.current().nextInt(1, 7 + 1);
            int replenishing_speed = ThreadLocalRandom.current().nextInt(1, goods + 1);
            WaterSource ws = new WaterSource(tempCoords.get(i), 3, replenishing_speed, tempNames.get(i), goods, tempPaths.get(i));
            if (board.addToBoard(ws.getLocation(), false)== true){
                this.getWaterSources().add(ws);
            }
        }
    }  
     
    /**
     * Creates all the hideouts.
     * @param board 
     */
    public void createHideouts(Board board){
        List<Point> tempCoords = new ArrayList<>();
        Collections.addAll(tempCoords, new Point(10,25),
                                         new Point(2,7),
                                         new Point(0,18),
                                         new Point(28,9),
                                         new Point(23,0),
                                         new Point(25,25),
                                         new Point(15,15),
                                         new Point(3, 24),
                                         new Point(10, 9)
        );
        
        List<String> tempNames = new ArrayList<>();
        Collections.addAll(tempNames,   "In the bushes", 
                                        "Desert", 
                                        "By the pool",
                                        "In absolute concentration",
                                        "Above all",
                                        "Shady place",
                                        "Dreamy place",
                                        "On a tree",
                                        "Party time");
           
        List<String> tempPaths = new ArrayList<>();
        Collections.addAll(tempPaths,   ".\\src\\main\\images\\hideout\\hideout0.jpg", 
                                        ".\\src\\main\\images\\hideout\\hideout1.jpg", 
                                        ".\\src\\main\\images\\hideout\\hideout2.jpg", 
                                        ".\\src\\main\\images\\hideout\\hideout3.jpg", 
                                        ".\\src\\main\\images\\hideout\\hideout4.jpg", 
                                        ".\\src\\main\\images\\hideout\\hideout5.jpg", 
                                        ".\\src\\main\\images\\hideout\\hideout6.jpg", 
                                        ".\\src\\main\\images\\hideout\\hideout7.jpg", 
                                        ".\\src\\main\\images\\hideout\\hideout8.jpg");
        for (int i = 0; i<tempCoords.size(); ++i){
            int capacity = ThreadLocalRandom.current().nextInt(1, 7 + 1);
            Hideout hideout = new Hideout(tempCoords.get(i), capacity, tempNames.get(i), tempPaths.get(i));
            if (board.addToBoard(hideout.getLocation(), false)== true){
                this.getHideouts().add(hideout);
            } 
        }
    }
 
    /**
     * Creates all the obstacles and paints them.
     * @param board 
     */
    public void createLanes(Board board){
        List<Point> tempCoords = new ArrayList<>();
        Collections.addAll(tempCoords, new Point(1,0),
                                         new Point(2,0),
                                         new Point(1, 4),
                                         new Point(1, 3),
                                         new Point(3, 1),
                                         new Point (3,2),
                                         new Point (1,2),
                                         new Point(2,6),
                                         new Point(4,1),
                                         new Point(4,2),
                                         new Point(0,11),
                                         new Point(0,12),
                                         new Point(0, 14),
                                         new Point(0, 15),
                                         new Point(1, 14),
                                         new Point(1, 15),
                                         new Point(29,0),
                                         new Point(2,12),
                                         new Point(3,16),
                                         new Point(4, 18),
                                         new Point(5,18),
                                         new Point(0, 21),
                                         new Point(0,22),
                                         new Point(11, 23),
                                         new Point(11, 22),
                                         new Point(7,22),
                                         new Point(18,14),
                                         new Point(18, 16),
                                         new Point(18, 18),
                                         new Point(16, 18),
                                         new Point(12, 18),
                                         new Point(15,13),
                                         new Point(6,10),
                                         new Point(9,3),
                                         new Point(12, 3),
                                         new Point(12,11),
                                         new Point(28,0),
                                         new Point(27, 4),
                                         new Point(26, 11),
                                         new Point(27, 11),
                                         new Point(15, 13),
                                         new Point(15,14),
                                         new Point(24, 12),
                                         new Point(24, 13),
                                         new Point(23, 15),
                                         new Point(23,16),
                                         new Point(24,16),
                                         new Point(24, 15),
                                         new Point(28,24),
                                         new Point(23, 17),
                                         new Point(23, 19)
      

        ); 
        for (int i=0; i<10; ++i){
            tempCoords.add(new Point(i, 17));
            tempCoords.add(new Point(i, 25));
            tempCoords.add(new Point(i+11, 25));
            tempCoords.add(new Point(i+4, 13));
            tempCoords.add(new Point(i+7, 0));
            tempCoords.add(new Point(i+7, 1));
            tempCoords.add(new Point(8, i));
            tempCoords.add(new Point(20, i+8));
             tempCoords.add(new Point(22, i+8));
            tempCoords.add(new Point(29, i+2));
            tempCoords.add(new Point(29, i+13));
            tempCoords.add(new Point(18+i, 22));
            tempCoords.add(new Point(12+i, 20));
        }
        for (int i=0; i<6; ++i){
            tempCoords.add(new Point(17+i, 6));
        }
        for (int i=0; i<5; ++i){
            tempCoords.add(new Point(5, i+2));
            tempCoords.add(new Point(3, i+4));
            tempCoords.add(new Point(i+2, 8));
            tempCoords.add(new Point(16, 13+i));
            tempCoords.add(new Point(18, 8+i));
            tempCoords.add(new Point(12+i, 4));
            tempCoords.add(new Point(15, 5+i));
            tempCoords.add(new Point(24+i, 10));
            tempCoords.add(new Point(12+i, 22));
            tempCoords.add(new Point(12+i, 23));
        }
        for (int i=0; i<4; ++i){
            tempCoords.add(new Point(7, i+3));
            tempCoords.add(new Point(i+2, 10));
            tempCoords.add(new Point(i+4, 24));
            tempCoords.add(new Point(11, 17+i));
            tempCoords.add(new Point(0, 2+i));
            tempCoords.add(new Point(0, 6+i));
            tempCoords.add(new Point(17, 8+i));
            tempCoords.add(new Point(13, 6+i));
            tempCoords.add(new Point(18, 1+i));
            tempCoords.add(new Point(20, 1+i));
            tempCoords.add(new Point(22, 1+i));
            tempCoords.add(new Point(24, 1+i));
            tempCoords.add(new Point(26, 1+i));
            tempCoords.add(new Point(26, 17+i));
            tempCoords.add(new Point(27, 17+i));
            tempCoords.add(new Point(14, 15+i));
        }
        
        for (int i=0; i<3; ++i){
            tempCoords.add(new Point(3, 12+i));
            tempCoords.add(new Point(5+i, 15));
            tempCoords.add(new Point(10+i, 15));
            tempCoords.add(new Point(5+i, 11));
            tempCoords.add(new Point(9, 9+i));
            tempCoords.add(new Point(0+i, 19));
            tempCoords.add(new Point(2, 20+i));
            tempCoords.add(new Point(0+i, 24));
            tempCoords.add(new Point(4, 20+i));
            tempCoords.add(new Point(5, 20+i));
            tempCoords.add(new Point(7+i, 18));
            tempCoords.add(new Point(7+i, 20));
            tempCoords.add(new Point(9, 22+i));
            tempCoords.add(new Point(14+i, 11));
            tempCoords.add(new Point(9+i, 8));
            tempCoords.add(new Point(11, 9+i));
            tempCoords.add(new Point(10+i, 6));
            tempCoords.add(new Point(10, 3+i));
            tempCoords.add(new Point(14+i, 2));
            tempCoords.add(new Point(24, 6+i));
            tempCoords.add(new Point(28, 2+i));
            tempCoords.add(new Point(26, 6+i));
            tempCoords.add(new Point(27, 6+i));
            tempCoords.add(new Point(28, 6+i));
            tempCoords.add(new Point(28, 13+i));
            tempCoords.add(new Point(26, 13+i));
            tempCoords.add(new Point(18+i, 23));
        }
        for (int i=0; i<2; ++i){
            tempCoords.add(new Point(25, 18+i));
            tempCoords.add(new Point(23+i, 21));
            tempCoords.add(new Point(20+i, 19));
            tempCoords.add(new Point(22, 24+i));
            tempCoords.add(new Point(24, 24+i));
            tempCoords.add(new Point(26, 24+i));
    }
   
        
        for (int i = 0; i<tempCoords.size(); ++i){
            Obstacle o = new Obstacle(tempCoords.get(i));
            if (board.addToBoard(o.getLocation(), true)== true){
                this.paintObstacle(o);
                
            }
        }
    }
    
    /**
     * Creates all the food spots.
     * @param board 
     */
    public void createFoodSpots(Board board){
        List<Point> tempCoords = new ArrayList<>();
        Collections.addAll(tempCoords, new Point(0,10) ,
                                         new Point(29,1),
                                         new Point(28,25),
                                         new Point(8,24),
                                         new Point(18, 17),
                                         new Point(9,4),
                                         new Point(3,0),
                                         new Point(21, 12),
                                         new Point(9, 15)
                                         
                                        
        );
        
        List<String> tempNames = new ArrayList<>();
        Collections.addAll(tempNames,   "Cheesy Dibbles heaven",
                                        "Sushi place",
                                        "Birthday party",
                                        "Never too much",
                                        "Hole in ice",
                                        "Best fish in town",
                                        "Fishhh!",
                                        "Peaceful fishing spot",
                                        "Family gathering"
        );
        List<String> tempPaths = new ArrayList<>();
        Collections.addAll(tempPaths,   ".\\src\\main\\images\\foodSource\\food0.jpg", 
                                        ".\\src\\main\\images\\foodSource\\food1.jpg",  
                                        ".\\src\\main\\images\\foodSource\\food2.jpg", 
                                        ".\\src\\main\\images\\foodSource\\food3.jpg", 
                                        ".\\src\\main\\images\\foodSource\\food4.jpg", 
                                        ".\\src\\main\\images\\foodSource\\food5.jpg", 
                                        ".\\src\\main\\images\\foodSource\\food6.jpg", 
                                        ".\\src\\main\\images\\foodSource\\food7.jpg", 
                                        ".\\src\\main\\images\\foodSource\\food8.jpg",
                                        ".\\src\\main\\images\\foodSource\\food9.jpg");
        
        for (int i = 0; i<tempCoords.size(); ++i){
            int goods = ThreadLocalRandom.current().nextInt(1, 5 + 1);
            int replenishing_speed = ThreadLocalRandom.current().nextInt(1, goods + 1);
            FoodSource fs = new FoodSource(tempCoords.get(i), 3, replenishing_speed, tempNames.get(i), goods, tempPaths.get(i));
            if (board.addToBoard(fs.getLocation(), false)== true){
                this.getFoodSources().add(fs);
            }
        }
    }
    
    /**
     * Creates Rectangle object for given spot.
     * @param spot
     * @param c color
     * @param p point in 2D array
     */
    public void createGUISpot(Spot spot, Color c, Point p){
        Rectangle rec = new Rectangle(c, p, new PlaceInfoBox(spot));
        spot.setRectangle(rec); 
        spot.getRectangle().setBounds(0,0, 1, 1);
        jFrame.add(rec, 0);
    }
    
    /**
     * Paints spot onto GUI board.
     * @param spot
     * @param c
     * @param p 
     */
    public static void paint(Spot spot, Color c, Point p){
        Rectangle rec = spot.getRectangle();
        rec.setBounds(0,0, 800, 800);
        rec.setBackground(new Color(1.0f,1.0f,1.0f,0.0f));
        rec.repaint();
        jFrame.addMouseListener(rec.getRectangleListener());

    }
    
    /**
     * Removes spot from GUI board.
     * @param spot
     * @param p 
     */
    public static void unpaint(Spot spot, Point p){
        Rectangle rec = spot.getRectangle();
        rec.setBounds(0,0, 1, 1);
        rec.repaint();
        rec.setBounds(0,0, 1, 1);
        jFrame.removeMouseListener(rec.getRectangleListener());
    }
    
    /**
     * Paints obstacle.
     * @param o 
     */
    public void paintObstacle(Obstacle o){
        Rectangle rec = new Rectangle(o.getColor(), o.getLocation(), null);
        rec.setBounds(0,0, 800, 800);
        rec.setBackground(new Color(1.0f,1.0f,1.0f,0.0f));
        jFrame.add(rec, 0);
        rec.repaint();
    }
    
    /**
     * Creates lanes intersections.
     */
    public void addIntersections(){
        int[][] m ={{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
                    { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                    { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        };
        
        for (int x=0; x<board.board.length; x++){
            for (int y=0; y<board.board[0].length; y++){
                if (m[x][y] == 1){
                    getIntersectionBoard()[x][y] = new Intersection();
                }
            }
        }

    }

    /**
     * @return the hideouts
     */
    public static List<Hideout> getHideouts() {
        return hideouts;
    }

    /**
     * @return the waterSources
     */
    public static List<WaterSource> getWaterSources() {
        return waterSources;
    }

    /**
     * @return the foodSources
     */
    public static List<FoodSource> getFoodSources() {
        return foodSources;
    }

    /**
     * @return the intersectionBoard
     */
    public static Intersection[][] getIntersectionBoard() {
        return intersectionBoard;
    }

    /**
     * @param aIntersectionBoard the intersectionBoard to set
     */
    public static void setIntersectionBoard(Intersection[][] aIntersectionBoard) {
        intersectionBoard = aIntersectionBoard;
    }
}
