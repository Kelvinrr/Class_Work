package CS249_Project2;

/**
 * <H1>Recrusive Grouping</H1>
 * <p>
 * Models n Choose k combinatorics.
 * <p>
 * Executes under a main method and thus can be called and tested directly.
 *
 * @author      First Last fll23@nau.edu
 * @version     1.0
 * @since       00-00-2015
 */
public class recursiveGrouping {

    private static String players="";
    private static int groupsize;

    /**
     * Main method, takes number of players and group size as arguments
     * @param args [0]= int players>0, [1] = int group size>0
     */
    public static void main(String[] args){
       
    	players = "ABCDEFG";
    	int size = 2;
    	
    	System.out.println(showTeams(size, 0));
    	
    }

    /**
     * Static method to recursively display desired team groupings.
     * @param 
     * @param 
     * @return 
     */
    private static String showTeams(int size, int current){
    
    	if(current == players.length()-1)
    		return "\n";
    	
    	String returnString = "";
    	for(int i = current+1; i < players.length(); i++){
    		returnString += players.charAt(current);
    	
    		if((current + i + size) < players.length())
    			returnString += players.substring(i, i+size);
    			
    		returnString += "\n";
    	}
    
    	return returnString + showTeams(size, current+1);
    }
   
    
    
    private static boolean knapSack(){
		
    	// base cases: if target weight = 0
    	// and if start > weight.length -2 || target weight < 0
    	
    	//else 
    	// result = knapsack(weights, start+1, targetweight - weights[start])
    	
    	//if(result == true)
    		// syso(weights);
    		//return true;
    	
    	//else
    	// 	return knapsack(weights, start+1.targets)
    	
    	
    	
    	return false;
    	
    	
    	
    }
    
    
    
    
    
}
