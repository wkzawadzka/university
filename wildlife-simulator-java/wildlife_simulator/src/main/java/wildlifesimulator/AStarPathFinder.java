/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package wildlifesimulator;


import java.awt.Point;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.PriorityQueue;
import static wildlifesimulator.Main.board;

/**
 * AStarPathFinder uses A* algorithm to find a path from Point A to Point B.
 * @author weraz
 */
public class AStarPathFinder {
    private static final List<Point> moves = new ArrayList<>();
    
    /**
     * Constructor
     */
    public AStarPathFinder(){
        moves.add(new Point(0,1)); 
        moves.add(new Point(0, -1)); 
        moves.add(new Point(1, 0));
        moves.add(new Point(-1, 0));
    }
    
    /**
     * Finds path between source and destination.
     * @param isPrey is an animal that path will be calculated of prey type
     * @param source source Point
     * @param dest destination Point
     * @return 
     */
    public static List<Point> findPath(boolean isPrey, Point source, Point dest){
        Node[][] cell = new Node[board.board.length][board.board[0].length];
        cell = calculateHeuristics(cell, isPrey, dest);
        return generatePath(cell, source, dest);
        
    }
    
    /**
     * Calculates euclidean distance between two points.
     * @param source source Point
     * @param dest destination Point
     * @return 
     */
    public static double euclideanDistance(Point source, Point dest){
        double deltaX = dest.y - source.y;
        double deltaY = dest.x - source.x;
        return Math.sqrt(deltaX*deltaX + deltaY*deltaY);
    }

    /**
     * Calculates heuristics to destination for all the points on the 2D board array.
     * @param cell collection of all the cells on a board
     * @param isPrey is it prey or not
     * @param dest destination Point
     * @return 
     */
    public static Node[][] calculateHeuristics(Node[][] cell, boolean isPrey, Point dest) {

        for (int x = 0; x < board.board.length; x++) {
            for (int y = 0; y < board.board[0].length; y++) {
                cell[x][y] = new Node(x, y);
                if (board.board[x][y] == 0 || isPrey == false) {
                    cell[x][y].sethValue(euclideanDistance(new Point(x, y), dest));
                } else {
                    cell[x][y].sethValue(-1);
                }
            }
        }
        return cell;
    }
    
    /**
     * Generates path - a list of moves from point A to B.
     * @param cell collection of all the cells on a board
     * @param source source Point
     * @param dest destination Point
     * @return 
     */
    public static List<Point> generatePath(Node[][] cell, Point source, Point dest){
        List<Point> path = new ArrayList<>();
        List<Node> tempPath = new ArrayList<>();
        
        PriorityQueue<Node> q = new PriorityQueue<>(1, new Comparator<Node>() {
            @Override
            public int compare(Node o1, Node o2) {
                if (o1.getfValue() < o2.getfValue()){
                    return -1;
                }
                if (o1.getfValue() > o2.getfValue()){
                    return 1;
                }
                return 0;
        }
        });
        q.add(cell[source.x][source.y]); // add source as starting point to the queue
        
        
        while (!q.isEmpty()) {
            Node node = q.poll(); // let the node equal the node with the least f value
            tempPath.add(node);
            if (node == cell[dest.x][dest.y]) { // arrived at destination
                break;
            }

            for (Point move : moves){
            try {
                if (tempPath.contains(cell[node.getX() + move.x][node.getY() + move.y]) || cell[node.getX() + move.x][node.getY() + move.y].gethValue() == -1){
                    continue;
                }
                double gValue = node.getgValue() + 1;
                double fValue = gValue + cell[node.getX() + move.x][node.getY() + move.y].gethValue();
                if (q.contains(cell[node.getX() + move.x][node.getY() + move.y]) && (fValue > cell[node.getX() + move.x][node.getY() + move.y].getfValue())) {
                    continue;
                }
                
                cell[node.getX() + move.x][node.getY() + move.y].setParent(node);
                cell[node.getX() + move.x][node.getY() + move.y].setgValue(gValue);
                cell[node.getX() + move.x][node.getY() + move.y].setfValue(fValue);
                q.add(cell[node.getX() + move.x][node.getY() + move.y]);
            } catch (IndexOutOfBoundsException e) {
            }}}

        Node n = tempPath.get(tempPath.size() - 1);
        while(n.getParent() != null){
             Node curr = n;
             path.add(new Point(curr.getX(), curr.getY()));
             n = n.getParent();
         }
        Collections.reverse(path);
        
//    System.out.println("To get from (" + source.x + ", " + source.y + ")"
//                        +" to (" + dest.x + ", " + dest.y +"):\n");
//    for (Point node : path){
//        System.out.println("(" + node.x +", " + node.y + ") -> ");
//    }
                        
    return path; 
        
}}
