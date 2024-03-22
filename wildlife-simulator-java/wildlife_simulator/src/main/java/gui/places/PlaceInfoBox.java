/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package gui.places;

import static gui.BoardPanel.squareSize;
import static gui.BoardPanel.xOrg;
import static gui.BoardPanel.yOrg;
import java.awt.Image;
import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import places.Hideout;
import places.Source;
import places.Spot;
import static wildlifesimulator.Main.jFrame;

/**
 * PlaceInfoBox is handler for displaying information about spots.
 * @author weraz
 */
public class PlaceInfoBox implements MouseListener {
    private final int xLeft;
    private final int xRight;
    private final int yUpper;
    private final int yLower;
    private final Spot spot;
    
    /**
     * Constructor of PlaceInfoBox.
     * @param spot Spot object that the information is about
     */
    public PlaceInfoBox(Spot spot) {
        this.spot = spot;
        int x = spot.location.x;
        int y = spot.location.y;
        this.xLeft = xOrg + x*squareSize;
        this.xRight = this.xLeft + squareSize;
        this.yUpper = yOrg + y*squareSize;
        this.yLower = this.yUpper + squareSize;
    }
    
    /**
     * Displays information about the spot.
     * @param e 
     */
    @Override
    public void mouseClicked(MouseEvent e) {
        jFrame.getKillButton().setVisible(false);
        jFrame.getRouteButton().setVisible(false);
        Point pos = e.getPoint();
        if ((this.getxLeft() <= pos.x) && (pos.x <= this.getxRight()) && (this.getyUpper() <= pos.y) && (pos.y <= this.getyLower())){
            jFrame.InfoText.setText(this.getSpot().showInfo());
            //jFrame.InfoText.setVisible(true);
            BufferedImage img = null;
            if(getSpot() instanceof Source source){
                try {
                    img = ImageIO.read(new File(source.getPath()) );
                    jFrame.infoNameLabel.setText(source.name);
                } catch (IOException ex) {
     
                    Logger.getLogger(PlaceInfoBox.class.getName()).log(Level.SEVERE, null, ex);
                }
            } else {
                try {
                    img = ImageIO.read(new File(((Hideout)getSpot()).getPath()) );
                    jFrame.infoNameLabel.setText(((Hideout)getSpot()).name);
                } catch (IOException ex) {
                    Logger.getLogger(PlaceInfoBox.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
            jFrame.InfoPhotoLabel.setVisible(true);
            Image dimg = img.getScaledInstance(jFrame.InfoPhotoLabel.getWidth(), jFrame.InfoPhotoLabel.getHeight(), Image.SCALE_SMOOTH);
            ImageIcon imageIcon = new ImageIcon(dimg);
            jFrame.InfoPhotoLabel.setIcon(imageIcon);

    }
    }

    @Override
    public void mousePressed(MouseEvent e) {
        
    }

    @Override
    public void mouseReleased(MouseEvent e) {
       
    }

    @Override
    public void mouseEntered(MouseEvent e) {
      
    }

    @Override
    public void mouseExited(MouseEvent e) {

    }

    /**
     * @return the xLeft
     */
    public int getxLeft() {
        return xLeft;
    }

    /**
     * @return the xRight
     */
    public int getxRight() {
        return xRight;
    }

    /**
     * @return the yUpper
     */
    public int getyUpper() {
        return yUpper;
    }

    /**
     * @return the yLower
     */
    public int getyLower() {
        return yLower;
    }

    /**
     * @return the spot
     */
    public Spot getSpot() {
        return spot;
    }
    
}
