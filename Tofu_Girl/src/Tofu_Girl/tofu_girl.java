//main
package Tofu_Girl;


import java.awt.*;
import java.awt.event.*;
import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.URL;
import java.util.Vector;

import javax.imageio.ImageIO;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.swing.*;
import javax.swing.border.EmptyBorder;


@SuppressWarnings({ "unused", "serial" })
public class tofu_girl extends JFrame  {

	private static final Object CNETER = null;
	protected static final BufferedInputStream Sound = null;
	private JPanel contentPane;	
		
	 private JPanel pnInput;
	 private JButton[] btn = new JButton[5];   
	 private int button_number;
	
	JLabel imageLabel;
	ImageIcon icon_start_button = new ImageIcon(moving_tofu.class.getResource("/characters/start_button.png"));
    ImageIcon icon_reset_button = new ImageIcon(moving_tofu.class.getResource("/characters/reset_button.png"));
    ImageIcon icon_help_button = new ImageIcon(moving_tofu.class.getResource("/characters/help.png"));
    ImageIcon icon_dress_button = new ImageIcon(moving_tofu.class.getResource("/characters/dress.png"));
        
   ImageIcon back= new ImageIcon(moving_tofu.class.getResource("/characters/background.png"));
   Image img=back.getImage();
			
  
  
   
    public tofu_girl(){
					
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 901, 900);
		setTitle("2020 Java programing Mini Project");	
		contentPane = new JPanel(){
		
			//background	
		   public void paintComponent(Graphics g) {
	    	g.drawImage(img, 0, 0,900,900,null);	
		    	
		    }
		};
				 
		setContentPane(contentPane);
	
		contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.X_AXIS));
	
		//tofu moving		
		moving_tofu moving_tofu_ = new moving_tofu();
		contentPane.add(moving_tofu_);			
		moving_tofu_.setLayout(new BorderLayout(0, 0));
	
	
	   //girl_jumping
		girl_jumping girl_jumping_ = new girl_jumping();
		moving_tofu_.add(girl_jumping_);
		
			
			GridBagLayout gbl_girl_jumping_ = new GridBagLayout();
			gbl_girl_jumping_.columnWidths = new int[]{481, 141, 0};
			gbl_girl_jumping_.rowHeights = new int[]{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			gbl_girl_jumping_.columnWeights = new double[]{0.0, 0.0, Double.MIN_VALUE};
			gbl_girl_jumping_.rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, Double.MIN_VALUE};
			girl_jumping_.setLayout(gbl_girl_jumping_);
					
  
		
		JButton btn= new JButton();    //start button
		btn.setVerticalAlignment(SwingConstants.BOTTOM); 
		btn.setBorderPainted(false);	
		btn.setFocusPainted(false);
		btn.setContentAreaFilled(false);
													
		btn.setIcon(icon_start_button);
		girl_jumping_.add(btn);
																	
							
		JButton btn2= new JButton();  //reset button
		btn2.setVerticalAlignment(SwingConstants.BOTTOM); 
		btn2.setBorderPainted(false);	
		btn2.setFocusPainted(false);
		btn2.setContentAreaFilled(false);
														
		btn2.setIcon(icon_reset_button);							
		girl_jumping_.add(btn2);
																
		btn2.setVisible(false);
		
		
		JButton btn3= new JButton();  //help button
		btn3.setVerticalAlignment(SwingConstants.BOTTOM); 
		btn3.setBorderPainted(false);	
		btn3.setFocusPainted(false);
		btn3.setContentAreaFilled(false);
																						
		btn3.setIcon(icon_help_button);											
		girl_jumping_.add(btn3);
		
		
		JButton btn4= new JButton();  //dress button
		btn4.setVerticalAlignment(SwingConstants.BOTTOM); 
		btn4.setBorderPainted(false);	
		btn4.setFocusPainted(false);
		btn4.setContentAreaFilled(false);
																						
		btn4.setIcon(icon_dress_button);											
		girl_jumping_.add(btn4);
				
		//start 
		btn.addActionListener (new ActionListener() {

			@SuppressWarnings("static-access")
			@Override
			public void actionPerformed(ActionEvent e) {
			
				moving_tofu_.move=1;		 // tofu moves from left side to right	side				
				girl_jumping_.requestFocus();								
				girl_jumping_.setFocusable(true);	
				btn.setVisible(false);									
				btn3.setVisible(false);
				btn4.setVisible(false);
				
				btn2.setVisible(true);   //after start only can see reset button
							
			}
			
		});					
		
		//reset 
		btn2.addActionListener (new ActionListener() {

			@SuppressWarnings({ "static-access", "rawtypes" })
			@Override
			public void actionPerformed(ActionEvent e) {

				
				moving_tofu_.score=0;      // reset score value
				moving_tofu_.x=0;          //initial x coordinate of the tofu
				moving_tofu_.girl_jumping_.bump=false;   //initial value for checking bump
				moving_tofu_.arrive=false;				 //initial value for checking that the tofu arrive
				moving_tofu_.girl_jumping_.girl_arrive=false;  //initial value for checking that girl step on the tofu
				moving_tofu_.tofu_list= new JList();      // list for building the tofu
				moving_tofu_.tofu_building=new Vector();
				moving_tofu_.temp_building=0;             //value for checking until the tofu is less than 3 
														
				dispose();  //close a previous window
			
				//restart 
		        tofu_girl frame = new tofu_girl();										
				frame.setVisible(true);
				frame.setResizable(false);
				moving_tofu_.move=0;	//if reset the tofu dose not move until click start button									
			
			}
			
		});
		
		//help 
		btn3.addActionListener (new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
												
				new helpwindow();   //Open new help window																
			}
											
	   });			
		
		//dress_choise
		btn4.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				new dress_choise();  //Open new dress window	
				
			}
			
		});
		
		
    }
    
 
	//sound
    public static void Sound(String file, boolean Loop){

    	Clip clip;
    	try {
   		
    		AudioInputStream ais = AudioSystem.getAudioInputStream(new BufferedInputStream(new FileInputStream(file)));

    		clip = AudioSystem.getClip();
    		clip.open(ais);
    		clip.start();
    		
    	if ( Loop) clip.loop(-1);

    	//if Loop is true, base music repeat infinitely
    	//if false repeat only one time

    	} catch (Exception e) {
    		e.printStackTrace();
    	}
    }
    
   
        
    		
   

  
	public static void main(String[] args) {
		
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
										
					tofu_girl frame = new tofu_girl();										
					frame.setVisible(true);
					frame.setResizable(false);
				    // base sound
					String base_music = tofu_girl.class.getResource("/Music/bensound-clearday.wav").getPath();
					Sound(base_music, true);
										 
				} catch (Exception e) {
				
					e.printStackTrace();
				}
			}
		});
	}
	 
}

//help window 
@SuppressWarnings("serial")
class helpwindow extends JFrame{
	
	ImageIcon rule= new ImageIcon(helpwindow.class.getResource("/characters/game_rule.png"));
    Image img=rule.getImage();
    
    
	helpwindow(){
		setTitle("Help");	
        setVisible(true);
        
        addWindowListener(new WindowAdapter() {   //when click x button, close only this window
			public void windowClosing(WindowEvent e) {
				setVisible(false);
				dispose();
			}
		});
        setSize(835,380);
        setResizable(false);
		setLocationRelativeTo(null);

       JPanel helpwindow=new JPanel() {
    	 //paint background		
    	   public void paint(Graphics g) {  
    			g.drawImage(img, 0, 0, null); 		
    	   }
    	};
    	   
    	add(helpwindow); 
    	   
    }
	
	public static void main(String[] args){
		new helpwindow();
	}
}


//dress window
class dress_choise extends JFrame{
	
    private JPanel pnInput;
    private JButton[] btn = new JButton[5];   
    private int button_number;
       
	dress_choise(){
				
		setTitle("Dress Choise");	
        setVisible(true);
	
		addWindowListener(new WindowAdapter() {  //when click x button, close only this window
			public void windowClosing(WindowEvent e) {
				setVisible(false);
				dispose();
			}
		});
		
		setSize(835,380);
	    setResizable(false);
	    setLocationRelativeTo(null);
	    
	    //add button and each function 	   
	    girl_jumping girl_jumping_ = new girl_jumping();
	  
		button_number=4;
		
		 for(int i=1; i<=button_number; i++){
			   btn[i] = new JButton();
			 }
			
		JPanel contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(new BorderLayout(0, 0));
		setContentPane(contentPane);
		
		pnInput = new JPanel();
		add(pnInput, BorderLayout.CENTER);
		pnInput.setLayout(new GridLayout(4, 5, 5, 5));
		
		
		btn[1] = new JButton("Pink");
		btn[1].setBackground(Color.PINK);
		btn[1].setFont(new Font("±¼¸²", Font.BOLD, 14));					
		
		btn[2] = new JButton("Blue");
		btn[2].setBackground(new Color(0, 102, 204));
		btn[2].setFont(new Font("±¼¸²", Font.BOLD, 14));		

		btn[3] = new JButton("Beige");
		btn[3].setBackground(new Color(210, 180, 140));
		btn[3].setFont(new Font("±¼¸²", Font.BOLD, 14));

		btn[4] = new JButton("Purple");
		btn[4].setBackground(new Color(72, 61, 139));
		btn[4].setFont(new Font("±¼¸²", Font.BOLD, 14));
	
		//add dresses
		for( int i=1; i<=girl_jumping_.level; i++) {
			
			final int temp=i;
			//add button
			pnInput.add(btn[i]);
			//each button action
			btn[i].addActionListener (new ActionListener() {

				@SuppressWarnings("static-access")
				@Override
				public void actionPerformed(ActionEvent e) {					 
					girl_jumping_.level=temp;								
				}
				
			});		
		}

    }
		
	public static void main(String[] args){
		new dress_choise();
	}
}
