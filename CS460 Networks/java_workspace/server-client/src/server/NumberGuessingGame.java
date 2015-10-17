package server;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

public class NumberGuessingGame implements Runnable{
	private Socket client_socket;
	
	public NumberGuessingGame(Socket client_socket){
		this.client_socket = client_socket;
	}
	
	public void run(){
	    int fence 		= 1024/2;
	    int increment 	= 1024/2;
	    int number 		= 0;
	    InputStream input_stream = null;
	    OutputStream output_stream = null;
		try {
			input_stream = this.client_socket.getInputStream();
			output_stream = this.client_socket.getOutputStream();
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

	    while(increment >  0) {
	    	try {
				output_stream.write(
				    ("Is your number higher than " + fence + "?\n").getBytes());

		    	byte response[] = new byte[3];
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
			output_stream.write(("Is your number " + number + "?\n").getBytes());
		    input_stream.close();
		    output_stream.close();
		    client_socket.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	    
	}
	

}