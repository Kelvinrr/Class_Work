package server;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

/**
 * 	@Description
 *		Class for the number guessing game. Only has a single method for
 *		running the game.
 *  @Author
 *		Franklin Berry and Kelvin Rodriugez.
 *		Mostly Franklin though, that guys cool. */
public class NumberGuessingGame implements Runnable {
	private Socket client_socket;

	/**
	 * basic parameterized constructor, it's very basic. */
	public NumberGuessingGame(Socket client_socket) {
		this.client_socket = client_socket;
	}

	/**
	 * @Desciption
	 *		The run() method, where all the logic happens.
	 *		It's much larger than the default constructor, but don't
	 *		mention it around him, he's very insecure about it. */
	public void run() {
	    int fence 		= 1024/2;
	    int increment 	= 1024/2;
	    int number 		= 0;
	    InputStream input_stream = null;
	    OutputStream output_stream = null;

		// Try and catch blocks that nobody likes...
		try {
			input_stream = this.client_socket.getInputStream();
			output_stream = this.client_socket.getOutputStream();
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		byte response[] = new byte[3];
	    while(increment >  0) {
	    	try {
				output_stream.write(
				    ("Is your number higher than " + fence + "?\n").getBytes());
		    	
		    	input_stream.read(response);

		    	if ((char)response[0] == 'q')
		    		break; // quit

		    	if ((char)response[0] == 'y') {
		    	    number += increment;
		    	    increment /= 2;
		    	    fence  += increment;
		    	} else {
		    		increment /= 2;
		    		fence -= increment;
		    	}

	    	}catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
	    }  // End of while(increment > 0) loop

	    number++;
	    try {
	    	if((char)response[0] != 'q')
				output_stream.write(("Is your number " + number + "?\n").getBytes());

		    input_stream.close();
		    output_stream.close();
		    if(!client_socket.isClosed())
		    	client_socket.close();
    		System.out.println("Closed Client:\n" + client_socket);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
