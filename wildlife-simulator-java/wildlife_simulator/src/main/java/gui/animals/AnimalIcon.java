/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package gui.animals;

import animals.Animal;
import animals.Predator;
import animals.Prey;
import static gui.BoardPanel.squareSize;
import static gui.BoardPanel.xOrg;
import static gui.BoardPanel.yOrg;
import static gui.Window.getKillButtonListener;
import static gui.Window.getRouteButtonListener;
import static gui.Window.setKillButtonListener;
import static gui.Window.setRouteButtonListener;
import gui.buttons.KillButtonListener;
import gui.buttons.RouteChangerListener;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JPanel;
import static wildlifesimulator.Main.jFrame;

/**
 * AnimalIcon icon that represents an animal on the GUI board.
 * @author weraz
 */
public class AnimalIcon extends JPanel implements MouseListener {
    private int x;
    private int y;
    private ImageIcon icon;
    private final String id;
    private final Animal animal;
    private boolean clickable = true;
    
    
    /**
     * Constructor of AnimalIcon.
     * @param a Animal (prey or predator) to put in GUI board
     * @param sizeMultiplier multiplier of size of an icon
     * @throws IOException 
     */
    public AnimalIcon(Animal a, float sizeMultiplier) throws IOException{
        this.animal = a;
        this.x = xOrg + a.getLocation().x*squareSize;
        this.y = yOrg + a.getLocation().y*squareSize;
        this.id = a.getId();
        BufferedImage img = ImageIO.read(new File(a.getPath()));
        Image dimg = img.getScaledInstance(((int)(squareSize*sizeMultiplier)), ((int)(squareSize*sizeMultiplier)), Image.SCALE_SMOOTH);
        icon = new ImageIcon(dimg, null);
    }
    
    /**
     * Changes coordinates of an animal at the GUI board. Repaints it.
     * @param location 
     */
    public void changeCoordinates(Point location){
        this.setX(xOrg + location.x*squareSize);
        this.setY(yOrg + location.y*squareSize);
        repaint();
    }
    
    /**
     * Paint the component - an animal icon. Attaches mouse listener to it if applicable.
     * @param g 
     */
    @Override
    public void paintComponent(Graphics g)
    {
        super.paintComponent(g);
        getIcon().paintIcon(this, g, 0,0);
        if (isClickable()){
            addMouseListener(this);
        }
    }

    /**
     * Shows information about an animal if its icon is clicked.
     * @param e
     */
    @Override
    public void mouseClicked(MouseEvent e) {
        jFrame.InfoPhotoLabel.setIcon(null);
        jFrame.infoNameLabel.setText(this.getAnimal().getSpecies());

        jFrame.getKillButton().removeActionListener(getKillButtonListener());
        setKillButtonListener(new KillButtonListener(this.getAnimal()));
        jFrame.getKillButton().addActionListener(getKillButtonListener());
        jFrame.getKillButton().setVisible(true);

        
        if (this.getAnimal() instanceof Prey){
            jFrame.InfoText.setText(this.getAnimal().toString());
            jFrame.getRouteButton().removeActionListener(getRouteButtonListener());
            setRouteButtonListener(new RouteChangerListener((Prey) this.getAnimal()));
            jFrame.getRouteButton().addActionListener(getRouteButtonListener());
            jFrame.getRouteButton().setVisible(true);
        } else {
            jFrame.InfoText.setText(this.getAnimal().toString());
            if (((Predator)this.getAnimal()).isRelaxMode()){
                jFrame.InfoText.append("\n\n       relaxing...");
            } else {
                jFrame.InfoText.append("\n\n       hunting...");
            }
        }
    }

    @Override
    public void mousePressed(MouseEvent e) {
        //throw new UnsupportedOperationException("Not supported yet."); // Generated from nbfs://nbhost/SystemFileSystem/Templates/Classes/Code/GeneratedMethodBody
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        //throw new UnsupportedOperationException("Not supported yet."); // Generated from nbfs://nbhost/SystemFileSystem/Templates/Classes/Code/GeneratedMethodBody
    }

    @Override
    public void mouseEntered(MouseEvent e) {
        //throw new UnsupportedOperationException("Not supported yet."); // Generated from nbfs://nbhost/SystemFileSystem/Templates/Classes/Code/GeneratedMethodBody
    }

    @Override
    public void mouseExited(MouseEvent e) {
        //throw new UnsupportedOperationException("Not supported yet."); // Generated from nbfs://nbhost/SystemFileSystem/Templates/Classes/Code/GeneratedMethodBody
    }

    /**
     * Gets x coordinate in GUI board.
     * @return the x
     */
    public int getX() {
        return x;
    }

    /**
     * Sets x coordinate in GUI board.
     * @param x the x to set
     */
    public void setX(int x) {
        this.x = x;
    }

    /**
     * Gets y coordinate in GUI board.
     * @return the y
     */
    public int getY() {
        return y;
    }

    /**
     * Sets y coordinate in GUI board.
     * @param y the y to set
     */
    public void setY(int y) {
        this.y = y;
    }

    /**
     * @return the icon
     */
    public ImageIcon getIcon() {
        return icon;
    }

    /**
     * @param icon the icon to set
     */
    public void setIcon(ImageIcon icon) {
        this.icon = icon;
    }

    /**
     * @return the id
     */
    public String getId() {
        return id;
    }


    /**
     * @return the animal
     */
    public Animal getAnimal() {
        return animal;
    }


    /**
     * @return the clickable
     */
    public boolean isClickable() {
        return clickable;
    }

    /**
     * @param clickable the clickable to set
     */
    public void setClickable(boolean clickable) {
        this.clickable = clickable;
    }
}
