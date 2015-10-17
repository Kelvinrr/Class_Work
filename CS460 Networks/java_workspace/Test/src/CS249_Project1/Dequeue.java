/**
 * @author Kelvin Rodriguez (KR788)
 * @date   2/03/15
 * 
 * This file contains the class for part three of the project: a dequeue
 */

package CS249_Project1;

import java.util.Arrays;
import java.util.function.Consumer;

/**
 * class representing a dequeue aka a double ended queue
 * @author kr788
 */
public class Dequeue {

	private int[] array;
	private int leftPtr;
	private int rightPtr;
	private int numItems;

	/**
	 * Defualt constructor, sets the size to 10
	 */
	public Dequeue() {
		array = new int[10];
		rightPtr = 0;
		leftPtr = 0;
		numItems = 0;
	}

	/**
	 * Parameterized contructor that sets the size of the queue
	 * 
	 * @param size
	 *            The size of the queue
	 * @throws Exception
	 *             generic exception if the queue size is less than 1
	 */
	public Dequeue(int size) throws Exception {
		if (size < 1)
			throw new Exception("Error: the queue size is out of bounds: " 
									+ "[size = " + size + "]");

		array = new int[size];
		rightPtr = 0;
		leftPtr = 1;
		numItems = 0;
	}

	/**
	 * insert element into the right side of the dequeue
	 * 
	 * @param newElement
	 *            element to insert
	 * @return boolean on weather or not the insert was successful
	 */
	public boolean insertRight(int newElement) {
		if (isFull())
			return false;

		rightPtr = (rightPtr < array.length - 1) ? rightPtr+1 : 0;
		numItems++;
		array[rightPtr] = newElement;
		return true;
	}

	/**
	 * insert element into the left side of the dequeue
	 * 
	 * @param newElement
	 *            element to insert
	 * @return boolean on weather or not the insert was successful
	 */
	public boolean insertLeft(int newElement) {
		if (isFull())
			return false;

		leftPtr = (leftPtr > 0) ? leftPtr - 1 : array.length-1;
		numItems++;
		array[leftPtr] = newElement;
		return true;
	}

	/**
	 * remove element from the right of the dequeue
	 * 
	 * @return the element removed
	 * @throws Exception
	 *             generic expception if the queue us empty
	 */
	public int removeRight() throws Exception {
		if (isEmpty())
			throw new Exception("Error: Dequeue is Empty.");

		int temp = array[rightPtr];
		rightPtr = (rightPtr > 0) ? rightPtr - 1 : array.length-1;
		return temp;
	}

	/*
	 * remove element from the left of the dequeue*
	 * 
	 * @return the element removed
	 * @throws Exception generic exception if the queue is empty
	 */
	public int removeLeft() throws Exception {
		if (isEmpty())
			throw new Exception("Error: Dequeue is Empty.");

		int temp = array[rightPtr];
		leftPtr = (leftPtr < array.length - 1) ? leftPtr+1 : 0;
		return temp;
	}

	/**
	 * @return boolean depending if the queue is empty
	 */
	public boolean isEmpty() {
		return (numItems == 0);
	}

	/**
	 * @return boolean depending if the queue is full
	 */
	public boolean isFull() {
		return (numItems == array.length);
	}

	/**
	 * Prints Dequeue from left pointer to right pointer to standard output
	 */
	public void display() {
		if (numItems == 0) {
			System.out.println("This Dequeue is empty.");
			return;
		}

		for (int i = leftPtr; i != rightPtr; i = (i < array.length - 1) ? i+1 : 0)
			System.out.print(array[i] + ",");
		System.out.println(array[rightPtr]);
	}

	/**
	 * @param args
	 *            default arguments for main
	 * @throws Exception
	 *             throws exception because I can't be bothered with try catch
	 *             block
	 */
	public static void main(String[] args) throws Exception {

		// local lambda for printing dequeue info
		Consumer<Dequeue> printAttributes = (q) -> {
			System.out.print("Queue Print: ");
			q.display();
			System.out.println("Array Print: " + Arrays.toString(q.array));
			System.out.println("Right Pointer = " + q.rightPtr);
			System.out.println("Left Pointer = " + q.leftPtr);
			System.out.println("Element Count = " + q.numItems);
		};

		Dequeue q = new Dequeue(4);
		
		System.out.println("------------------------------------");
		System.out.println("      Test on Queue of size " + q.array.length + "     ");
		System.out.println("------------------------------------\n");
		
		System.out.println("------------------------------------");
		System.out.println("Everything printed from left pointer\n"
				         + "         to right pointer");
		System.out.println("------------------------------------\n");
		
		System.out.println("------------Empty Queue-------------");
		printAttributes.accept(q);
		System.out.println("------------------------------------\n");
		
		System.out.println("-------After Adding One Item--------");
		q.insertRight(10);
		printAttributes.accept(q);
		System.out.println("------------------------------------\n");
		
		System.out.println("----------No Wrap Around------------");
		q.insertRight(3);
		printAttributes.accept(q);
		System.out.println("------------------------------------\n");
		
		System.out.println("------------Wrap Around-------------");
		q.insertLeft(3234);
		q.insertLeft(300);
		printAttributes.accept(q);
		System.out.println("------------------------------------\n");
		
		
		
		
		
		
		
	}
}