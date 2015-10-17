/**
 * MultiThreadedServer.java
 * @author Kelvin Rodriguez & Franklin Berry
 *
 */
package server;
import java.net.ServerSocket;
import java.net.Socket;
import java.io.IOException;
/**
 * @description
 * 		A multi-threaded server that plays a number guessing game
 * 		with a client
 * @author Kelvin Rodriguez, Franklin Berry
 */
public class MultiThreadedServer implements Runnable {
    //////////////////////// Instance Variables ////////////////////////
    private final int SERVER_PORT = 23666;
    private ServerSocket server_socket;
    private Socket client_socket;
    private Thread user_thread;

    ///////////////////////////// Methods //////////////////////////////
    public MultiThreadedServer(){
    }
    
    public MultiThreadedServer(Socket client_socket){
    	this.client_socket = client_socket;
    }
    
    @Override
    /** Runs the server */
    public void run() {
    	System.out.println("Starting Server");
    	synchronized(this) {
    		this.user_thread = Thread.currentThread();
    	}
    	
    	try {
    		this.server_socket = new ServerSocket(this.SERVER_PORT);
    	} catch (IOException e) {
    		System.out.println("Failed to open server at port " + this.SERVER_PORT);
    	}
    	
    	while(true) {
    		/*Scanner in = new Scanner(System.in);
    		String std_in = in.nextLine();
    		if(std_in.equals("q")){
    			try {
    				System.out.println("Closing socket");
					server_socket.close();
				} catch (IOException e) {
					System.out.println("Couldn't close socket");
				}
    		    System.exit(0);
    		}*/
    	   
    		try {
				client_socket = server_socket.accept();
				
			} catch (IOException e) {
				System.out.println("Failed to accept client socket");
			}
    	
    		new Thread(new NumberGuessingGame(client_socket)).start();
    	}
	}
    
	public void shutdown(){
    	try{
    		this.server_socket.close();
    		this.client_socket.close();
    	}catch(Exception e){
    		
    	}
    }
    
	///////////////////////// Setters and Getters ///////////////////////// 
    public ServerSocket getServer_socket() {
		return server_socket;
	}

	public void setServer_socket(ServerSocket server_socket) {
		this.server_socket = server_socket;
	}

	public Socket getClient_socket() {
		return client_socket;
	}

	public void setClient_socket(Socket client_socket) {
		this.client_socket = client_socket;
	}

	public Thread getUser_thread() {
		return user_thread;
	}

	public void setUser_thread(Thread user_thread) {
		this.user_thread = user_thread;
	}
	///////////////////////////////////////////////////////////////////////
	
	public static void main(String[] args) {
		MultiThreadedServer server = new MultiThreadedServer();
		new Thread(new MultiThreadedServer()).start();
		server.shutdown();
	}
	

}  // end of MultiThreadedServer class