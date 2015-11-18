package client;

import java.io.*;
import java.net.*;
import java.util.Arrays;

class UDPServiceClient {
	public static final int DEFAULT_PORT = 9890;
	
	public static final char CMD_ECHO 	= 'e';
	public static final char CMD_DNS 	= 'd';
	public static final char CMD_TIME   = 't';
		
	public static void main (String[] args){
		if(args.length < 1){
			System.out.println("Usage: [service] [Parameter] [port]");
			System.exit(0);
		}
		
		byte[] buffer = new byte[255];
		DatagramPacket receivePacket = null;
		DatagramSocket clientSocket  = null;
		
		if(args[0].equals("-d"))
			buffer[0] = 'd';
		else if (args[0].equals("-e")) 
			buffer[0] = 'e';
		else if (args[0].equals("-t")) 
			buffer[0] = 't';
		else {
			System.out.println("Unknown Service value: " + args[0]);
			System.exit(0);
		}
		
		buffer[1] = ' ';
		
		if (args.length > 1)
			for(int i = 0; i < args[1].length(); i++)
				buffer[i+2] = (byte) args[1].charAt(i);
		
		System.out.println("Sending: " + new String(buffer));
		try {
			
			// create UDP socket
			clientSocket = new DatagramSocket();
			InetAddress IPAddress = InetAddress.getByName("134.114.9.128");
			
			// send the data
			DatagramPacket sendPacket = new DatagramPacket(buffer, buffer.length, IPAddress, DEFAULT_PORT);
			clientSocket.send(sendPacket);
			
			// wait for server response
			receivePacket = new DatagramPacket(buffer, buffer.length);
			clientSocket.receive(receivePacket);
		} catch (Exception e) {
			System.out.println("Shit Happens....");
			System.exit(-1);
		}
		
		String modifiedSentence = new String(receivePacket.getData());
		System.out.println("FROM SERVER:" + modifiedSentence);
		clientSocket.close();
	}
}