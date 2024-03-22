/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package wildlifesimulator;

/**
 * Node used for backtracking in path finding.
 * @author weraz
 */
public class Node {
    private final int x;
    private final int y;
    private double hValue;
    private double fValue;
    private double gValue;
    private Node parent;

    /**
     * Constructor
     * @param x x coordinate
     * @param y y coordinate
     */
    public Node(int x, int y) {    
        this.x = x;
        this.y = y;
        this.parent = null;
        this.gValue = 0;
        
    }    

    /**
     * @return the x
     */
    public int getX() {
        return x;
    }

    /**
     * @return the y
     */
    public int getY() {
        return y;
    }

    /**
     * @return the hValue
     */
    public double gethValue() {
        return hValue;
    }

    /**
     * @param hValue the hValue to set
     */
    public void sethValue(double hValue) {
        this.hValue = hValue;
    }

    /**
     * @return the fValue
     */
    public double getfValue() {
        return fValue;
    }

    /**
     * @param fValue the fValue to set
     */
    public void setfValue(double fValue) {
        this.fValue = fValue;
    }

    /**
     * @return the gValue
     */
    public double getgValue() {
        return gValue;
    }

    /**
     * @param gValue the gValue to set
     */
    public void setgValue(double gValue) {
        this.gValue = gValue;
    }

    /**
     * @return the parent
     */
    public Node getParent() {
        return parent;
    }

    /**
     * @param parent the parent to set
     */
    public void setParent(Node parent) {
        this.parent = parent;
    }
}
