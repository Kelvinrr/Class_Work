/**
 * MultiThreadedServer.java
 * @author Kelvin Rodriguez & Franklin Berry */
package server;

import java.net.ServerSocket;
import java.net.Socket;
import java.io.IOException;

/**
 * @description
 * 		A multi-threaded server that plays a number guessing game
 * 		with a client.
 * @author
 *      Kelvin Rodriguez and Franklin Berry.
 *      Fun fact: Kelvin is very handsom. */
public class MultiThreadedServer implements Runnable {
    //////////////////////// Instance Variables ////////////////////////
    private final int SERVER_PORT = 23659;
    private ServerSocket server_socket;
    private Socket client_socket;
    private Thread user_thread;
    private boolean server_is_stopped;
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////// Methods //////////////////////////////
    /**
     * @Description
     *      default constructor, it is very default-y */
    public MultiThreadedServer() {
    	server_is_stopped = false;
    }

    /**
     * @Description
     *      Parameterized constructor. It's parameterized, it's a
     *      a constructor, it's a parameterized constructor!*/
    public MultiThreadedServer(Socket client_socket) {
    	this.client_socket = client_socket;
    }

    @Override
    /**
     * @Description
     *      Runs the server */
    public synchronized void run() {
    	System.out.println("Starting Server");

    	try {
    		this.server_socket = new ServerSocket(this.SERVER_PORT);
    	} catch (IOException e) {
    		System.out.println("Failed to open server at port "
                + this.SERVER_PORT+ " exiting...");
    		System.exit(0);
    	}

        ///////////// Server loop /////////////
    	while(!server_is_stopped) {
    		try {
				client_socket = server_socket.accept();
	    		System.out.println("\nAccepted Client:");
	    		System.out.println(client_socket + "\n");

			} catch (IOException e) {
				if(!server_is_stopped)
					System.out.println("Error accepting a client...");
			}
    		new Thread(new NumberGuessingGame(client_socket)).start();
    	}
        ////////////////////////////////////////
	}

    /**
     *
     *
     */
	public void shutdown(){
    	try{
    		this.server_is_stopped = true;
    		if(this.server_socket != null && !server_socket.isClosed())
    			this.server_socket.close();
    		if(this.client_socket != null && !client_socket.isClosed())
    			this.client_socket.close();
    	}catch(Exception e){

    	}
    }
    ///////////////////////////////////////////////////////////////////////

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

    ///////////////////////////// Main Method /////////////////////////////
    /**
     * @Description
     *      The main method, it has a smug sense of self-importance...
     *      It creates the initial thread. */
	public static void main(String[] args) {
		MultiThreadedServer server = new MultiThreadedServer();
	  	ServerMenu menu = new ServerMenu(server);

		new Thread(server).start();
		new Thread(menu).start();
	}
}  // end of MultiThreadedServer class
