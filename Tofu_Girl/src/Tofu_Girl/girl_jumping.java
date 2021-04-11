package Tofu_Girl;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

@SuppressWarnings("serial")
class girl_jumping  extends JPanel implements Runnable, KeyListener{
	
	//private static final int KeyEvent = 0;
	private int frameWidth =800, frameHeight =700;
	static int x, y, x_temp ;
	private int yy=0, temp=0;
		
	//each position image
	private ImageIcon Jump;
	private Image jumping;
	
	private ImageIcon Stand ;
	private Image stand;
	
	private ImageIcon Down ;
	private  Image down;
	
	//check level
	static int level=1;
	

	private boolean jump = false;
	private Thread thread;
	private int u=60, t=1, g=13, position;

	static boolean bump = false; 
	static boolean girl_arrive = false; 

	
	public girl_jumping() {
		
		//jumping with space bar 
		addKeyListener(this);		
		thread= new Thread(this);
		thread.setDaemon(true);
		thread.start();		
	}
	
	
	
	@Override
	public void run() {
				
		//initial x position
		  x= 380; 
		 		
			while(true) {
				//jumping and stand 
				if(jump) {					
					t++;												
					yy=u*t-(g/2)*t*t;																								
					girl_arrive=false;					
					y=yy;	//return height value to moving_tofu														
				}
				if(t>1 && yy<=50) {
					
					jump=false;
					t=1;						
					yy=50;
					girl_arrive=true;
					y=yy;  //return height value to moving_tofu
				}
					
				repaint();
					
				try {
					Thread.sleep(50);					
				}catch(InterruptedException e) {
					e.printStackTrace();
				}
				
			}

		}
		
	
	public void paintComponent(Graphics g) {
		
		
		ImageIcon Jump = new ImageIcon(moving_tofu.class.getResource("/characters/girl"+level+"_jumping.png"));
		Image jumping=Jump.getImage();
		
		ImageIcon Stand = new ImageIcon(moving_tofu.class.getResource("/characters/girl"+level+"_stand.png"));
		Image stand=Stand.getImage();
		
		ImageIcon Down = new ImageIcon(moving_tofu.class.getResource("/characters/girl"+level+"_down.png"));
		Image down=Down.getImage();
					
		if(jump) {
		
			g.drawImage(jumping, x, frameHeight-yy-250, null); 
		}
	
		else if(bump) {
			g.drawImage(down, x+100,  frameHeight-230, null);
						
		}
		
		else if (!bump && !jump) {			
			g.drawImage(stand, x,  frameHeight-250, null);				
		}

		setOpaque(false);
		
	}
	
	@Override
	public void keyPressed(KeyEvent e) {

		int key= e.getKeyCode();
		if(key == e.VK_SPACE) {
			jump=true; 
			
			String jump = tofu_girl.class.getResource("/Music/jump.wav").getPath();
			tofu_girl.Sound(jump, false);
		
		}
		
	}

	@Override
	public void keyTyped(KeyEvent e) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void keyReleased(java.awt.event.KeyEvent e) {
		// TODO Auto-generated method stub
		
	}
	
}
