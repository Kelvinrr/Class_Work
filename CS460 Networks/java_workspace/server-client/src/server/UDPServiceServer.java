package server;

/* package whatever; // don't place package name! */


import java.net.*;
import java.util.*;
import java.net.InetAddress.*;



/* Name of the class has to be "Main" only if the class is public. */
public class UDPServiceServer
{
	public final static int DEFAULT_PORT = 9865;
	
	public static void main (String[] args) throws java.lang.Exception
	{
		/*
		if(args.length != 1)
		{
			System.out.println("Needs port number only");
			System.exit(0);
		}*/
			int port = DEFAULT_PORT;
			DatagramSocket serverSocket = new DatagramSocket(port);
		    byte[] receiveData = new byte[1024];             
		    byte[] sendData = new byte[1024];       
		    
		    while(true)                
		    {                   
		    	System.out.println("Server is running...");
		    	DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
		    	serverSocket.receive(receivePacket);		    	
		    	String sentence = new String(receivePacket.getData());
		       	System.out.println("RECEIVED: " + sentence); // HH:MM
		       	
		       			       	
		       	switch (sentence.charAt(0)) {
		       	case 't':   Date date = new Date();   // given date
		       				Calendar calendar = GregorianCalendar.getInstance(); // creates a new calendar instance
		       				calendar.setTime(date);   // assigns calendar to given date 
		       				int hour = calendar.get(Calendar.HOUR_OF_DAY); // gets hour in 24h format
		       				int minutes = calendar.get(Calendar.MINUTE); // gets minutes in some format
		       				
		       				System.out.println("Server time is " + hour + ":" + minutes + " in HH:MM format");
		       				sendData = ("Server time is " + hour + ":" + minutes + " in HH:MM format").getBytes();
		       			    break;
		       			    
		       	case 'd':   String HostName = sentence.substring(2, sentence.length());
		       				System.out.println(HostName);
		       			    InetAddress HostAddress = InetAddress.getByName(HostName); 
		       				System.out.println("Requested Host IP address is " + HostAddress.getHostAddress()); 
		       				sendData = null;
		       				sendData = HostAddress.getHostAddress().getBytes();
		       				break;
		       				
		       	case 'e':   String message = sentence.substring(2, sentence.length());
		       	            System.out.println("Message to be sent is: " + message);
		       	            sendData = null;
		       	            sendData = message.getBytes();
		       	            break;
		       	            
		       	
		       	}
		       	
		       	
		       	
		       	
		       	int ClientPort = receivePacket.getPort();              	
		       	InetAddress IPAddress = receivePacket.getAddress();
              	DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, ClientPort);
		       	serverSocket.send(sendPacket);
		    }	
		    

	
		}
		         
		   
}
