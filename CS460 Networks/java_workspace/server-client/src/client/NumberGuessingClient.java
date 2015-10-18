package client;

import java.net.Socket;
import java.util.Random;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class NumberGuessingClient {
	private final int BUFFER_SIZE = 255;
	private String host_name;
	private int port_number;
	private Socket server_socket;


	public void play_game() throws IOException{
		try{
			server_socket = new Socket("localhost", 23657);
		}
		catch (Exception e){

		}
		// Server Loop ///////
		Random rnd = new Random(System.currentTimeMillis());
        int number_to_guess  = rnd.nextInt(1025) + 1;
        int current_fence    = 0;
        int guess_count      = 0;
		int last_space_index = 0;
		int last_punct_index = 0;

        byte[] buffer = new byte[BUFFER_SIZE];
        String buffer_string;

        InputStream input_stream = this.server_socket.getInputStream();
        OutputStream output_stream = this.server_socket.getOutputStream();

        while(input_stream.read(buffer) >= 0){
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
        }
        if(number_to_guess == current_fence){
        	System.out.println("\nServer's guess: " + current_fence + "\n");
        	System.out.println("Client's number: " + number_to_guess + "\n");
        	System.out.println("\nServer is correct");
        } else
        	System.err.println("The guess is wrong...");

		server_socket.close();
	}

	public static void main(String[] args) {
            NumberGuessingClient client = new NumberGuessingClient();
            try {
				client.play_game();
			} catch (IOException e) {

			}
	}


}
