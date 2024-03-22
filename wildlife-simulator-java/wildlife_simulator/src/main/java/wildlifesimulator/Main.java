/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Project/Maven2/JavaApp/src/main/java/${packagePath}/${mainClassName}.java to edit this template
 */

package wildlifesimulator;

import gui.MapAdjuster;
import gui.Window;

/**
 * Main class.
 * @author weraz
 */
public class Main {
    public static Window jFrame;
    public static Board board;
    public static Spawner spawner;
    public static MapAdjuster mapAdjuster;
    public static AStarPathFinder pathFinder;
    
    public static void main(String[] args) {
        jFrame = new Window();
        board = new Board();
        board.createBoard();
        mapAdjuster = new MapAdjuster();
        jFrame.setVisible(true);
        pathFinder = new AStarPathFinder();
        spawner = new Spawner();
}
}
