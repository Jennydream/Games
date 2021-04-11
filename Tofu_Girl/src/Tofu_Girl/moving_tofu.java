package Tofu_Girl;

import java.awt.Component;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Image;
import java.util.Random;
import java.util.Vector;

import javax.swing.ImageIcon;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.Timer;

import Tofu_Girl.girl_jumping;


public class moving_tofu extends JPanel implements Runnable {
	
		
	
	 static int x, y;     //tofu coordinates
	 static int move;     //moving  
	 private int x_x=1;   //location when tofu meet girl before arrive completely
	 static int score=0;  //number of building tofus
	 
	Font myfont= new Font ("Courier New",  Font.BOLD, 50);  //score font size
	 
	 //moving stick image 
	private ImageIcon icon = new ImageIcon(moving_tofu.class.getResource("/characters/tofu_stick_left.png"));
	private Image img=icon.getImage();
	
	//successful image
	private ImageIcon icon2 = new ImageIcon(moving_tofu.class.getResource("/characters/complete_level.png"));
	private Image img_complete=icon2.getImage();
	
	private Thread thread;	

	girl_jumping  girl_jumping_  = new girl_jumping();  //import girl_jumping
	
	// building_tofu
	private ImageIcon icon3 = new ImageIcon(moving_tofu.class.getResource("/characters/tofu_plate.png"));
	private Image img_plate=icon3.getImage();

	private ImageIcon icon4 = new ImageIcon(moving_tofu.class.getResource("/characters/tofu.png"));
	private Image img_tofu=icon4.getImage();
	
	private ImageIcon icon5 = new ImageIcon(moving_tofu.class.getResource("/characters/table.png"));
	private Image img_table=icon5.getImage();

	private ImageIcon icon6 = new ImageIcon(moving_tofu.class.getResource("/characters/water_drop.png"));
	private Image img_water=icon6.getImage();
	
    //stack tofu list
	JList tofu_list= new JList();
	Vector tofu_building= new Vector();
	boolean arrive = false;
	int temp_building=0;

	
	public moving_tofu() {
			

		thread= new Thread(this);
		thread.setDaemon(true);
		thread.start();
		
	}
		
	public void run(){
				y=505;  //tofu height
			
				int threadspeed=0;// initial  speed
				while(true){
					
					x+=move;  //move to right side
					if(x>=170 && x<=220 ) {
						 
						  //bump check
						 if( Crash(girl_jumping_.x, girl_jumping_.y, x, y)) {													
							 break;
							}
					  }
					 else if( x>=240 ) {	

						 for(int j=x; j<=280;j++){	
							 
							 //check tofu met girl 
							 if((500-girl_jumping_.y)==(y-55)) {
								x_x=j;							
								break;							 						
							 }
							 if(((500-girl_jumping_.y)!=(y-55))&& j==270){
								 x_x=j;							 
								 break;					 
							 }
						 }
					 
					add(girl_jumping_);
					girl_jumping_.x_temp = x_x;   //return x value to girl_jumping
								
					//if girl arrive  add score
					arrive =true;
					score+=1; 	
						
					//stack tofus 
					if(temp_building==0) {
						for(int i=0; i<2; i++) {
																
							tofu_building.addElement(x_x+100);																											
					//	}
							y=y;
							temp_building+=1;																
						}
										
					}
					else {
									
						tofu_building.addElement(x_x+100);								
							
						y=y;																	
					}
	
					x=0; // initialization x value when tofu arrive completely.
				}							 
						
				else if (x<170) {
					arrive =false;	
						
				}	
					
				if(score==5) {
					girl_jumping_.level+=1;	
					if(girl_jumping_.level==5) {
						girl_jumping_.level=1;
					}
					String compleate = tofu_girl.class.getResource("/Music/complete.wav").getPath();
					tofu_girl.Sound(compleate, false);
					
					break;
				}
								   					
				repaint();

				try {

					//tofu_moving speed 
					Random rd= new Random();
		
					if(tofu_building.size()<3) {
						threadspeed=rd.nextInt(3)+3;
					}
					else {
						threadspeed=rd.nextInt(3)+2;
					}		
					
					Thread.sleep(threadspeed);
					
					

				} catch (InterruptedException e) {
					e.printStackTrace();					

				}
				
					
				
		}
			
}
		
	public void paintComponent(Graphics g) {
		

	
		g.setFont(myfont);
				
		if(score>=1 && score<5 ) {
			
			g.drawString("Score : "+ score, 400, 100);
			
		}
		else if (score==5) {
			g.drawString("Score : "+ score, 400, 100);
			g.drawImage(img_complete,230,350,null);
			
		}
		
		
		//tofu_building
		if(tofu_building.size()<2) {
			
			
			g.drawImage(img_table, 250,540, this);
			g.drawImage(img_plate, 320, 570, this);  
			g.drawImage(img_tofu, 370, 560, this);   
	    }
		
		else {
			for(int j=1; j<tofu_building.size();j++) {
				
				
				//moving plage, table and first tofu
				if(j==tofu_building.size()-1) {
					
					g.drawImage(img_table, 250,540+(j*50), this);
					g.drawImage(img_plate, 320, 570+(j*50), this);
					g.drawImage(img_tofu, 370, 560+(j*50), this);
				}
				else continue;								
			
				//stack tofu
				if(girl_jumping.girl_arrive) {
					for( int i=1; i< tofu_building.size(); i++) {  
				
						g.drawImage(img_tofu, (int) tofu_building.elementAt(i),((560+(j*50))-(i*49)), null);		
					}
				}
				
				else if(!girl_jumping.girl_arrive ){
					if(arrive) {
						
						for( int i=0; i< tofu_building.size(); i++) {  
							g.drawImage(img_tofu, (int) tofu_building.elementAt(i),((560+(j*50))-(i*49)), null);	
													
						}
					}
					else if(!arrive) {
						for( int i=1; i< tofu_building.size(); i++) {  					
							
							g.drawImage(img_tofu, (int) tofu_building.elementAt(i),((560+(j*50))-(i*49)), null);								
							
						}
				
					}
				}		
			}
			
		}
		
		
		g.drawImage(img,x, y, 220,73, this);
		setOpaque(false);
			
	}

	
	//check bump
	public boolean Crash(int x1, int y1, int x2, int y2){ 
		
			
		if( x2>170 && (500-y1) <y2 && (500-y1+55)>(y2-40) ) {
		
			add(new girl_jumping());
			girl_jumping_.bump = true;
			
			//sound for each function
			String punch = tofu_girl.class.getResource("/Music/punch.wav").getPath();
			String crying = tofu_girl.class.getResource("/Music/crying.wav").getPath();
			String ah = tofu_girl.class.getResource("/Music/ah.wav").getPath();
			
			tofu_girl.Sound(punch, false);
						
			if(score<3)
				tofu_girl.Sound(crying, false);
			else
				tofu_girl.Sound(ah, false);
			
		}
		else {
			add(new girl_jumping());
			girl_jumping_.bump = false;
			
		}

		return girl_jumping_.bump; 

    }
	  

}
