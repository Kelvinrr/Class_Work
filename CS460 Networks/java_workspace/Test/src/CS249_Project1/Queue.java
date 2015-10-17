
/**
 * @author Kelvin Rodriguez (KR788)
 * @date   1/31/15
 * 
 * File with Queue class. Does queue stuff and has a thing to test the queue stuff 
 */

package CS249_Project1;

import java.util.Arrays;
import java.util.function.Consumer;

/**
 * Queue class, this class was named Queue because Queue was already taken.
 * 
 * @author kr788
 *
 */
public class Queue {

	private int[] array;
	private int front;
	private int rear;
	private int numItems;

	/**
	 * Default Constructor
	 */
	Queue() {
		array = new int[10];
		front = 0;
		rear = -1;
	}

	/**
	 * Parameterized constructor that sets the size of the Queue
	 * 
	 * @param size
	 *            the size of the queue
	 * @throws Exception
	 *             generic exception if the size is less than 1
	 */
	public Queue(int size) throws Exception {
		if (size < 1)
			throw new Exception("Error: the queue size is out of bounds: " 
					+ "[size = " + size + "]");


		array = new int[size];
		front = 0;
		rear = -1;
	}

	/**
	 * Add an Element to the front of the Queue
	 * 
	 * @param newElement
	 *            element to add to the Queue
	 * @throws Exception
	 *             Generic exception if the Queue is full
	 */
	public void add(int newElement) throws Exception {
		if (numItems == array.length)
			throw new Exception("Error: can't add to a full array");

		numItems++;
		rear = (rear < array.length - 1) ? rear+1 : 0;
		array[rear] = newElement;
	}

	/**
	 * Removes the first item from the Queue
	 * 
	 * @return Element in front of the Queue
	 * @throws Exception
	 *             Generic exception if the Queue is Empty
	 */
	public int remove() throws Exception {
		if (numItems < 1)
			throw new Exception("Error: can't remove from empty queue");

		int temp = array[front];
		front = (front < array.length-1) ? front+1 : 0;
		numItems--;
		return temp;
	}

	/**
	 * Prints out the the queue in proper order (first to last)
	 */
	public void display() {
		if (numItems == 0) {
			System.out.println("This Queue is empty.");
			return;
		}

		for (int i = front; i != rear; i = (i < array.length-1) ? i+1 : 0)
			System.out.print(array[i] + ",");
		System.out.println(array[rear]);
	}

	/**
	 * 
	 * @return
	 */
	public String toString(){
		if (numItems == 0) {
			return "\n";
		}

		String returnString = ""; 
		
		for (int i = front; i != rear; i = (i < array.length-1) ? i+1 : 0)
			returnString += "[" + array[i] + "]";
		returnString += "[" + array[rear] + "]\n";
		
		return returnString;
	}
	
	/**
	 * @return whether or not the queue is empty
	 */
	public boolean isEmpty(){
		return numItems < 1;
	}
	
	/**
	 * @return whether or not the line is full
	 */
	public boolean isFull(){
		return numItems == array.length;
	}
	
	public static void main(String[] args) throws Exception {

		// local lambda for printing queue info
		Consumer<Queue> printAttributes = (q) -> {
			System.out.print("Queue Print: ");
			q.display();
			System.out.println("Array Print: " + Arrays.toString(q.array));
			System.out.println("Front Pointer = " + q.front);
			System.out.println("Rear Pointer = " + q.rear);
			System.out.println("Element Count = " + q.numItems);
		};

		Queue q = new Queue(4);
		System.out.println("-----------------------------------");
		System.out.println("      Test on Queue of size " + q.array.length + "     ");
		System.out.println("     Prints from left to right     ");
		System.out.println("-----------------------------------\n");
		
		System.out.println("------------Empty Queue------------");
		printAttributes.accept(q);
		System.out.println("-----------------------------------\n");

		System.out.println("-------After Adding One Item-------");
		q.add(2);
		printAttributes.accept(q);
		System.out.println("-----------------------------------\n");

		System.out.println("----------No Wrap Around-----------");
		q.add(5);
		q.add(10);
		q.add(12);
		printAttributes.accept(q);
		System.out.println("-----------------------------------\n");

		System.out.println("------------Wrap Around------------");
		q.remove();
		q.remove();
		q.add(100);
		q.add(1123);
		printAttributes.accept(q);
		System.out.println("-----------------------------------\n");

	}

}
