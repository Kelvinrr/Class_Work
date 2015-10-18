package client;

import java.net.Socket;
import java.util.Random;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

/**
 * @Description
 *		plays game with the MultiThreadedServer
 *		He doesn't like server very much but he doesn't want
 *		to feel lonely, either...*/
public class NumberGuessingClient {
	private final int    BUFFER_SIZE = 255;
	private 	  String host_name;
	private 	  int 	 port_number;
	private 	  Socket server_socket;

	public void play_game() throws IOException{
		try{
			server_socket = new Socket("localhost", 23657);
		}
		catch (Exception e){
			System.out.println("The server is not responding... exiting");
			System.exit(0);
		}
		/////// Declare all the things ///////
		Random rnd = new Random(System.currentTimeMillis());
        int number_to_guess  = rnd.nextInt(1025) + 1;
        int current_fence    = 0;  // The current number the server is guessing
        int guess_count      = 0;  // The number of times the server has guessed
		int last_space_index = 0;  // Index of last space (' ') in the server message
		int last_punct_index = 0;  // Index of punctuation (e.g. '?') in the server message

		// buffer to store the message coming from server
        byte[] buffer = new byte[BUFFER_SIZE];
        String buffer_string;

        // Streams to read and write things to and from server
        InputStream input_stream = this.server_socket.getInputStream();
        OutputStream output_stream = this.server_socket.getOutputStream();

        /////// Client Loop ///////
        while(input_stream.read(buffer) >= 0) {
        	buffer_string = new String(buffer);
        	System.out.println(buffer_string);

        	for(int i = 0; i < buffer_string.length(); i++)
        		if(buffer_string.charAt(i) == ' ')
        			last_space_index = i;
        		else if(buffer_string.charAt(i) == '?')
        			last_punct_index = i;

        	buffer_string = buffer_string.substring(last_space_index+1, last_punct_index);
        	current_fence = Integer.parseInt(buffer_string);

        	if(number_to_guess > current_fence) {
        		output_stream.write('y');
        		System.out.println("Client - y\n");
        	}

        	else if(guess_count < Math.log(1024)/Math.log(2)){
        	    output_stream.write('n');
        	    System.out.println("Client - n\n");
        	}

        	guess_count++;
        	buffer = new byte[BUFFER_SIZE];
        }  // end of  while(input_stream.read(buffer) >= 0)

    	System.out.println("\nServer's guess: " + current_fence + "\n");
    	System.out.println("Client's number: " + number_to_guess + "\n");

        if(number_to_guess == current_fence)
        	System.out.println("\nServer is correct");
        else
        	System.err.println("The guess is wrong...");

        if(!server_socket.isClosed())
			server_socket.close();
	}

	public static void main(String[] args) {
            NumberGuessingClient client = new NumberGuessingClient();
            try {
				client.play_game();
			} catch (IOException e) {
				System.out.println("Game crashed... "
						+ "send complaints to Kelvin Rodriguez and Franklin Berry");
			}
	}


}
