package CS249_Project2;

import java.util.InputMismatchException;
import java.util.Random;
import java.util.Scanner;

import CS249_Project1.Queue;

public class MarketCheckout {

	private int maxLineLen;
	private int numLines;
	
	private Queue POSLine[];   // array of the market's POSLines
	
	private int currentCustOfLine[]; // The current customer being checked out
	private int magnitudeOfLine[];   // The total amount of items in a POSLine
	                                 // this include the current customer being 
								     // being processed
	
	/**
	 * Parameterized constructor, sets the max line length and number of lines
	 * @throws Exception
	 */
	MarketCheckout(int initPOSLineLen, int initnumLines) throws Exception{
		maxLineLen = initPOSLineLen;
		numLines = initnumLines;
		
		POSLine = new Queue[numLines];
		currentCustOfLine = new int[numLines];
		magnitudeOfLine = new int[numLines];
		
		// construct all the queues
		for(int i = 0; i < numLines; i++)
			POSLine[i] = new Queue(maxLineLen);
	}
	
	/**
	 * @throws Exception 
	 * Simulates a single step in time
	 */
	public void tick() throws Exception{
		// iterates and updates each line
		for(int i = 0; i < numLines; i++){
			if(currentCustOfLine[i] > 0)
				currentCustOfLine[i]--;
			if(currentCustOfLine[i] == 0 && !POSLine[i].isEmpty()){
				currentCustOfLine[i] = POSLine[i].remove();
			}
		}
	}
	
	/**
	 * 
	 * @param newElement
	 * @throws Exception
	 */
	public void insertNew(int newElement) throws Exception{
		// find the shortest line ////////////////////////////////////
		// gets index to the first shortest line found ///////////////
		int shortestPOSLineIdx = 0;
		for(int i = 1; i < numLines; i++)
			if(magnitudeOfLine[i] < magnitudeOfLine[shortestPOSLineIdx])
				shortestPOSLineIdx = i;
		//////////////////////////////////////////////////////////////////
		// add new element to the shortest POSLine and increase magnitude
		if(currentCustOfLine[shortestPOSLineIdx] == 0)
			currentCustOfLine[shortestPOSLineIdx] = newElement;
		else
			POSLine[shortestPOSLineIdx].add(newElement);
		
		magnitudeOfLine[shortestPOSLineIdx] += newElement;
		//////////////////////////////////////////////////////////////////\
	}
	
	/**
	 * simple to String. returns the lines as strings.
	 */
	public String toString(){
		
		String returnString = "";
		
		for(int i = 0; i < numLines; i++){
			returnString += "Line " +  (i+1) + ":";
			if(currentCustOfLine[i] == 0)
				returnString += "This line is Empty\n";
			else
				returnString += "[" + currentCustOfLine[i] + "]" + POSLine[i];
		}
		return returnString ;
	}
	
	//************* Setters and Getters **************//
	public int getmaxLineLen() {
		return maxLineLen;
	}
	public void setmaxLineLen(int maxLineLen) {
		this.maxLineLen = maxLineLen;
	}

	public int getnumLines() {
		return numLines;
	}
	public void setnumLines(int numLines) {
		this.numLines = numLines;
	}
	//*************************************************//
	
	public static void main(String[] args){
		
		try {
			Scanner keyboard = new Scanner(System.in);
			System.out.print("Enter the number of lines: ");
			int numLines = keyboard.nextInt();
			System.out.print("Enter the max line length: ");
			int maxLen = keyboard.nextInt();
			
			MarketCheckout checkout = new MarketCheckout(maxLen, numLines);
			
			Random rand = new Random();
			int menuChoice;
			int tempInput;
			
			{// populate lines with random customers to make it easier to test
				int numCustomers = rand.nextInt(13) + 5; 
				for(int i = 0; i < numCustomers; i++)
					checkout.insertNew(rand.nextInt(10) + 1);
			}
			
			do{
				System.out.println("\n"
								 + "1 -- Show the lines\n"
								 + "2 -- Enter a new customer\n"
								 + "3 -- Simulates one time step\n"
								 + "4 -- Simulates 5 time steps\n"
								 + "5 -- Quit the program");
				
				menuChoice = keyboard.nextInt();
				
				switch(menuChoice){
				case 1: System.out.println("\n\n" + checkout); 
						break;
				case 2: System.out.print("\nNew Customer's number of items: ");
						tempInput = keyboard.nextInt();
						checkout.insertNew(tempInput);
						break;
				case 3: checkout.tick(); 
					    break;
				case 4: for(int i = 0; i < 5; i++) checkout.tick(); 
						break;
				case 5: break;
				
				default: 
					System.out.println("Incorrect input, try again");
				}
			}while(menuChoice != 5);
			
			keyboard.close();
			
		} catch(InputMismatchException e) {
			e.printStackTrace();
		}catch (Exception e) {
			e.printStackTrace();
		} 
		
		
	}
	
}
