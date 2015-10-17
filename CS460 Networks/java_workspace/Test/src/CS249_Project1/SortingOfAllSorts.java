/**
 * @author Kelvin Rodriguez (KR788)
 * @date   1/31/15
 *
 *  This file contains the three required sorting algorithms
 *  Bubble sort, selection sort, and insertion sort
 */

package CS249_Project1;

import java.util.Arrays;
import java.util.function.Consumer;
import java.util.function.Function;

/**
 * Class that contains the required sorting algorithms,
 * the name may not be very practical, but it's cute.
 * @author KR788
 */
public class SortingOfAllSorts {

	// arrays to use for testing
	private final static int INVERSE_SORTED_ARRAY[] = {9,8,7,6,5,4,3,2,1,0};
	private final static int PARTIAL_SORTED_ARRAY[] = {0,1,2,3,4,5,7,8,9,6};

	// store the array lengths, assumption is made that they both will always be the same size
	private final static int ARRAY_LENS = INVERSE_SORTED_ARRAY.length;

	/**
	 * A simple class holding sorting metrics, the number of
	 * comparison and the copy instructions executed during sorting
	 */
	public static class SortData{
		public int comparisonCount;
		public int copyCount;

		@Override
		public String toString() {
			return "comparisonCount = " + comparisonCount
			    +", copyCount = " + copyCount;
		}
	}

	/**
	 * Simple off-the-shelf bubble sort algorithm
	 * (i.e no optimization using flags and what-not)
	 * @param array the array to be sorted
	 * @return a SortData object containing sorting metrics
	 */
	public static SortData bubbleSort(int[] array){
		SortData results = new SortData();
		int temp;
		for(int i = 0; i < array.length-1; i++)
			for(int j = 0; j < array.length-1; j++, results.comparisonCount++)
				if(array[j] > array[j+1]){
					results.copyCount += 3;
					//swap ////////////////
					temp = array[j];
					array[j] = array[j+1];
					array[j+1] = temp;
					////////////////////////
				}
		return results;
	}

	/**
	 * Simple off-the-shelf selection sort algorithm
	 * (i.e no optimization using flags and what-not)
	 * @param array the array to be sorted
	 * @return a SortData object holding the metric data
	 */
	public static SortData selectionSort(int[] array){
		SortData results = new SortData();
		int temp;
		int minValIndex;

		for(int i = 0; i < array.length; i++){
			minValIndex = i;
			for(int j = i; j < array.length; j++, results.comparisonCount++)
				if(array[j] < array[minValIndex])
					minValIndex = j;

			if(minValIndex != i){
				results.copyCount+=3;
				//Swapity-Swap/////////////////
				temp = array[i];
				array[i] = array[minValIndex];
				array[minValIndex] = temp;
				///////////////////////////////
			}
		}

		return results;
	}

	/**
	 * Simple off-the-shelf insertion sort algorithm
	 * (i.e no optimization using flags and what-not)
	 * @param array the array to be sorted
	 * @return a SortData object holding the metric data
	 */
	public static SortData insertionSort(int[] array){
		SortData results = new SortData();
		int temp;

		for(int i = 0; i < array.length;i++, results.comparisonCount++)
			for(int j = i; (j > 0) && (array[j-1] > array[j]);j--,results.comparisonCount++) {
				results.copyCount+=3;
				//Swapity-do/////////////
				temp = array[j];
				array[j] = array[j-1];
				array[j-1] = temp;
				/////////////////////////
			}
		return results;
	}

	/**
	 * Prints out simple metrics for determining efficiency for both
	 * a partially sorted and inversely sorted array
	 * @param sortMethod the sort method to test out
	 */
	public static void testSortMethod(Function<int[], SortData> sortMethod){

		// local lambda function for printing the metric data for one array
		Consumer<int[]> printMetrics = (array) -> {
			System.out.println(sortMethod.apply(array));
			System.out.println("Sorted: " + Arrays.toString(array));
		};

		// print the data out using a copy of the two test arrays to avoid reseting the arrays
		System.out.println("Inversely Sorted Array:");
		printMetrics.accept(Arrays.copyOf(INVERSE_SORTED_ARRAY, ARRAY_LENS));
		System.out.println(); // blank line for prettiness
		System.out.println("Partially Sorted Array:");
		printMetrics.accept(Arrays.copyOf(PARTIAL_SORTED_ARRAY, ARRAY_LENS));
	}

	// An Obligatory comment about this being the main method
	public static void main(String[] args) {
		System.out.println("-----Original Inverse Sorted Array-----");
		System.out.println("    " + Arrays.toString(INVERSE_SORTED_ARRAY));
		System.out.println("---------------------------------------\n");
		System.out.println("-----Original Partial Sorted Array-----");
		System.out.println("    " + Arrays.toString(PARTIAL_SORTED_ARRAY));
		System.out.println("---------------------------------------\n");
		
		// test everything out one algorithm at a time
		System.out.println("--------------Bubble Sort--------------");
		testSortMethod(SortingOfAllSorts::bubbleSort);
		System.out.println("---------------------------------------\n");

		System.out.println("-------------Selection Sort------------");
		testSortMethod(SortingOfAllSorts::selectionSort);
		System.out.println("---------------------------------------\n");

		System.out.println("-------------Insertion Sort------------");
		testSortMethod(SortingOfAllSorts::insertionSort);
		System.out.println("---------------------------------------\n");
	}
}
