/**
 * @author Kelvin Rodriguez (KR788)
 * @date   3/1/15
 * 
 * 
 * Simple elimination game for project 2. Uses and singly linked list
 * to hold players. 
 * 
 */


package CS249_Project2;

import java.util.Random;
import java.util.Scanner;

public class ElimGame {

	SLinkedCircularList<String> players; 
	SLinkedCircularList.Node<String> startingPlayer; // player to start the count from
	Random rand; // a random number generator to get the eliminated player from

	boolean complete;
	
	/**
	 * Parameterized constructor, populates the players list 
	 * of size passed in and names players player1 to player(n)
	 * @param numPlayers
	 */
	public ElimGame(int numPlayers){
		rand = new Random();
		players = new SLinkedCircularList<String>();
		
		for(int i = 0; i < numPlayers; i++)
			players.insert("Player" + (i+1));
	
		startingPlayer = players.getHead(); //ha!
	}
	
	/**
	 * Update, this is where all the magic happens. Every call 
	 * simulates one step of the game. pass in the update rate in ms.
	 * 
	 * @return the eliminated player's name
	 * @throws Exception generic exception if the game removes from 
	 * 					 an empty player list
	 */
	public String update(long rate) throws Exception{
		
		// get random int from  range (1,numPlayers*2)
		int elimNum = rand.nextInt(players.getSize()*2) + 1;
		System.out.println("\nGoing to start couting to " + elimNum + 
				" starting with " + startingPlayer);
		
		// iterate through players until at the eliminated player spot
		for(int i = 0; i < elimNum; i++)
			startingPlayer = startingPlayer.next;
		
		Thread.sleep(rate); // pause for dramatic effect
		
		// delete the player from the game
		String eliminatedPlayer = startingPlayer.getData();
		players.delete(startingPlayer);
		
		// if one player left, end game
		if(players.getSize() == 1){
			complete = true;
			System.out.println("The winner is " + players.getHead() + "\n");
		}
		
		// else print the player eliminated
		else
			System.out.println(eliminatedPlayer + "  was eliminated");
		
		Thread.sleep(rate);
		
		// get the new player to start the count from
		startingPlayer = startingPlayer.next;
		
		// return the name of the elinimated player
		return eliminatedPlayer;
	}

	// Test method, there is no reason to put this into another class for the purpose of
	// this assignment
	public static void main(String[] args) throws Exception{

		Scanner keyboard = new Scanner(System.in);
		System.out.print("Enter the number of players:");
		ElimGame game = new ElimGame(keyboard.nextInt());
		
		System.out.println("The game will update every second");
		do{
			game.update(0);
			
		}while(!game.complete);
		keyboard.close();
		
	}
	
	
	
}
