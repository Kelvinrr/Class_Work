package server;

import java.util.Scanner;

public class ServerMenu implements Runnable {
	private MultiThreadedServer server; 
	
	public ServerMenu(MultiThreadedServer server) {
		this.server = server;
	}
	
	@Override
	public void run() {
		Scanner keyboard = new Scanner(System.in);
		String input;
		do{
			System.out.println("Type \"Stop\" at anytime to stop the server");
			input = keyboard.nextLine();
		}while(!input.equalsIgnoreCase("Stop"));
		
		server.shutdown();
		keyboard.close();
		
		System.out.println("Server has shutdown.");
		System.exit(0);
	} 
}