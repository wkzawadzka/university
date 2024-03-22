/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package wildlifesimulator;

import gui.BoardPanel;
import static gui.BoardPanel.columns;
import static gui.BoardPanel.rows;
import gui.Map;
import java.awt.Color;
import java.awt.Point;
import javax.swing.BorderFactory;
import static wildlifesimulator.Main.jFrame;

/**
 * Board is a representation of region when animals can move.
 * @author weraz
 */
public class Board {
    
    // main board 2D array
    // 2D array
    public int[][] board = new int[columns][rows]; // initialized with 0 
    
    
    /**
     * Creates initial board with custom map and displays it.
     */
    public void createBoard(){
        // grid
        BoardPanel boardGrid = new BoardPanel();
        boardGrid.setBounds(0,0, 800, 800);    
        boardGrid.setBorder(BorderFactory.createEtchedBorder()); 
        boardGrid.setBackground(new Color(1.0f,1.0f,1.0f,0.0f));
        jFrame.add(boardGrid, 0);
        
        
        // add map on top
       Map map = new Map();
       map.createCustomMap();
    }
    
    
    /**
     * Checks if it is possible to add new spot in a given place.
     * @param coords
     * @param isObstacle
     * @return 
     */
    public boolean addToBoard(Point coords, boolean isObstacle){
        if (board[coords.x][coords.y] == 0){
            if (isObstacle){
                board[coords.x][coords.y] = 1;
            }
            return true;
        }
        return false;
    }
}
