package server;

/* package whatever; // don't place package name! */


import java.net.*;

/* Name of the class has to be "Main" only if the class is public. */
public class UDPServiceServer
{
	
	public static void main (String[] args) throws java.lang.Exception
	{
		/*
		if(args.length != 1)
		{
			System.out.println("Needs port number only");
			System.exit(0);
		}*/

			int port = 9998;
			DatagramSocket serverSocket = new DatagramSocket(port);
		    byte[] receiveData = new byte[1024];             
		    byte[] sendData = new byte[1024];       
		    
		    while(true)                
		    {                   
		        DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
		        serverSocket.receive(receivePacket);
		        String sentence = new String( receivePacket.getData());
		       	System.out.println("RECEIVED: " + sentence);
		       	InetAddress IPAddress = receivePacket.getAddress();
		       	int ClientPort = receivePacket.getPort();
		       	String capitalizedSentence = sentence.toUpperCase();
              	sendData = capitalizedSentence.getBytes();
              	DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, ClientPort);
		       	serverSocket.send(sendPacket);
		       	
		    }	
	
		}
		         
		   
}