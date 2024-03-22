/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package wildlifesimulator;

import animals.Animal;
import animals.Predator;
import animals.Prey;
import static gui.BoardPanel.columns;
import static gui.BoardPanel.rows;
import static gui.BoardPanel.squareSize;
import static gui.BoardPanel.xOrg;
import static gui.BoardPanel.yOrg;
import static gui.MapAdjuster.adjustMap;
import gui.animals.AnimalIcon;
import java.awt.Color;
import java.awt.Point;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;
import java.util.concurrent.Semaphore;
import java.util.concurrent.ThreadLocalRandom;
import java.util.logging.Level;
import java.util.logging.Logger;
import static wildlifesimulator.Main.board;
import static wildlifesimulator.Main.jFrame;

/**
 * Spawner is used to add new animals.
 * @author weraz
 */
public class Spawner {
    private int index = 0;
    public static int preyCount = 0;
    public static Semaphore preyCountAccess = new Semaphore(1);
    public static List<Prey> preys = new ArrayList<>(0);
    public static Semaphore preysListAccess = new Semaphore(1);

    /**
     * Spawns new prey.
     * @throws IOException 
     */
    public void spawnPrey() throws IOException{
        int randomRow = ThreadLocalRandom.current().nextInt(0, rows);
        int randomCol = ThreadLocalRandom.current().nextInt(0, columns);
        while (board.board[randomCol][randomRow] == 1){
            randomRow = ThreadLocalRandom.current().nextInt(0, rows);
            randomCol = ThreadLocalRandom.current().nextInt(0, columns);  
        }
        
        String id = UUID.randomUUID().toString().substring(0, 8);
        int speed = ThreadLocalRandom.current().nextInt(2, 3 + 1);
        int strength = ThreadLocalRandom.current().nextInt(0, 4 + 1);
        Animal newPrey = new Prey(id, speed, strength, new Point(randomCol, randomRow), index);
        index++;
        AnimalIcon ai = newPrey.getIcon();
        ai.setBackground(new Color(1.0f,1.0f,1.0f,0.0f));
        ai.setBounds(xOrg + randomCol*squareSize,yOrg + randomRow*squareSize, 20, 20);
        jFrame.add(ai, 0);
        Thread p = new Thread(newPrey);  
        p.start();  
        
        try {
            preysListAccess.acquire();
            preyCountAccess.acquire();
            preys.add((Prey) newPrey);
            preyCount++;
            preyCountAccess.release();   
            preysListAccess.release();
            adjustMap();
        } catch (InterruptedException ex) {
            Logger.getLogger(Spawner.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }
    
    /**
     * Spawns new predator.
     * @throws IOException 
     */
    public void spawnPredator() throws IOException{
        int randomRow = ThreadLocalRandom.current().nextInt(0, rows);
        int randomCol = ThreadLocalRandom.current().nextInt(0, columns);
        String id = UUID.randomUUID().toString().substring(0, 8);
        int speed = ThreadLocalRandom.current().nextInt(1, 2 + 1);
        int strength = ThreadLocalRandom.current().nextInt(3, 8 + 1);
        Predator newPredator = new Predator(id, speed, strength, new Point(randomCol, randomRow));
       
        AnimalIcon ai0 = newPredator.getRelaxedIcon();
        ai0.setBackground(new Color(1.0f,1.0f,1.0f,0.0f));
        ai0.setBounds(0, 0, 1, 1);
        jFrame.add(ai0, 0);
        
        AnimalIcon ai1 = newPredator.getNormalIcon();
        ai1.setBackground(new Color(1.0f,1.0f,1.0f,0.0f));
        ai1.setBounds(0, 0, 1, 1);
        jFrame.add(ai1, 0);
        
        Thread p = new Thread(newPredator);  
        p.start();  
  
}}
