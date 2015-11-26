import java.util.Arrays;
public class MyRecursiveKnapsack implements RecursiveKnapsack {


    @Override
    public int[] getKnapsackSolution(int[] weights, int targetweight) {
      
      //Base Case
      //No Soln if there is too much weight in the bad
      if(targetweight < 0) return new int[]{-1};
      
      //only 1 weight left to try
      if(weights.length == 1){
         if(weights[0] == targetweight) return weights;
         else return new int[]{-1};
      }
      
      //Recursive Work---//
      int[] posSoln = getKnapsackSolution(Arrays.copyOfRange(weights, 1, weights.length), targetweight - weights[0]);
      
      //seeing if the weights[0] is in solution 
      if(posSoln.length > 1 || (posSoln.length == 1 && posSoln[0] != -1)){
         int[] soln = getKnapsackSolution(Arrays.copyOfRange(posSoln, 0, posSoln.length + 1), targetweight);
         
         soln[soln.length - 1] = weights[0];
         return soln;
      } else {
         return getKnapsackSolution(Arrays.copyOfRange(weights, 1, weights.length), targetweight);
      }
      
    }   
}