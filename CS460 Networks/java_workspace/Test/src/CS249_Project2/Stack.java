package CS249_Project2;

/**
 * @author Kelvin Rodriguez (KR788)
 * @date 3/1/2015
 * 
 * Stack class that works with a singly linked circular list. There are very little
 * comments because it's really more of a wrapper for the circular list than 
 * anything. So the code is pretty self documenting-ish.
 * @param <E> type of element to store
 */
public class Stack<E> {

	SLinkedCircularList<E> list;
	
	public Stack(){
		list = new SLinkedCircularList<E>();
	}
	
	public void push(E element){
		list.insert(element);
	}
	
	public E pop() throws Exception{
		E data = list.getHead().getData();
		list.delete();
		return data;
	}

	public E peek(){
		return list.getHead().getData();
	}
	
	public int size(){
		return list.getSize();
	}
	
	public String toString(){
		return list.toString();
	}
	
	// Test method, there is no reason to put this into another class for the purpose of
	// this assignment
	public static void main(String[] args) throws Exception{
		
		{ // Integer stack test
			System.out.println("------------------ Integer Stack -------------------");
			Stack<Integer> intStack = new Stack<Integer>();
			System.out.println("Print of empty stack: " + intStack);
			
			intStack.push(234);
			intStack.push(12);
			intStack.push(141);
			intStack.push(414);
			
			System.out.println("Print after pushing some ints: " + intStack);
			
	
			System.out.println("Popping From stack returns: " + intStack.pop());
			System.out.println("Popping From stack returns: " + intStack.pop());
			System.out.println("Popping From stack returns: " + intStack.pop());
			
			System.out.println("Final stack print: " + intStack);
			System.out.println("----------------------------------------------------\n");
		}
		
		{ // String stack test
			System.out.println("------------------ String Stack --------------------");
			Stack<String> stringStack = new Stack<String>();
			
			System.out.println("Print of empty stack: " + stringStack + "\n");
	
			stringStack.push("String 1");
			stringStack.push("String 2");
			stringStack.push("String 3");
			stringStack.push("String 4");
			
			System.out.println("Print after pushing some Strings \n" + stringStack + "\n");
		
			System.out.println("Popping From stack returns: " + stringStack.pop());
			System.out.println("Popping From stack returns: " + stringStack.pop());
			System.out.println("Popping From stack returns: " + stringStack.pop());
			System.out.println("Final stack print: " + stringStack);
			System.out.println("----------------------------------------------------\n");
		}
		
		
		
		
	}
	
	
}
