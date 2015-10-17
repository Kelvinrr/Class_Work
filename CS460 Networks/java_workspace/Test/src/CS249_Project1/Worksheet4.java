package CS249_Project1;

public class Worksheet4 {

	
	/*
	 * Write a count() function the counts the number of times a given int occurs in 
	 * a list. The first node in the list (e.g., Node n) and the int to search for 
	 * (e.g, int key) should be the parameters for your method. The method should 
	 * return the number of times the key appears in the list. 
	 */
	static int count(DLinkedList list){
		int count = 0;
		DLinkedList.Node iter = list.getHead();
		
		while(iter != null){
			count++;
			iter = iter.next;
		}
		
		return count;
	}

	
	/*
	 *  Write a getNth() function that takes in a node and an integer, and returns 
	 *  the node at the integer. In other words, if you call getNth(first, 4).
	 *  It should return the 4th node in the list that is pointed to by first. 
	 *  Be sure to check that the nth index is within the current size of the list. 
	 *  You can assume you have access to a variable called size that contains 
	 *  the number of nodes in the list
	 */
	static DLinkedList.Node getNth(DLinkedList.Node first, int idx){
		DLinkedList.Node returnNode = first;
		
		for(int i = 0; i < idx && returnNode != null; i++, 
				returnNode = returnNode.next);
			
		return returnNode;
	}
	
	/*
	 * Write a insertNth() function that takes the first node to a list, the nth 
	 * index (int), and the int to insert at the nth index. Thus, if you call 
	 * insertNth(first, 5, 10). A node containing the value 10 should be inserted 
	 * as the 5th node in the list that is pointed to by first. Be sure to check 
	 * that the nth index is within the current size of the list. You can assume
	 * you have access to a variable called size that contains the number of nodes
	 * in the list. 
	 
	static void insertNth(DLinkedList.Node first, DLinkedList.Node newNode, int idx){
		DLinkedList.Node returnNode = first;
		
		for(int i = 0; i < idx-1 && returnNode != null; i++, 
				returnNode = returnNode.next);
		
		DLinkedList.Node temp = returnNode.next;
		returnNode.next = newNode;
		newNode.next = temp;
	}
	
	public Node recursiveReverse(Node p){
	    return helperReverse(p, null);
	} 

	private Node helperReverse(Node p, Node previous){
	    if (p == null)
	        return p;
	    
	    else if (p.next == null){
	        p.next == previous;
	        return p;
	    }
	
	    else{
	        Node next = p.next;
	        p.next = previous;
	        return helperReverse(next, p);
	    }
	}
	
	public static void main(String [] args){
		
		DLinkedList list = new DLinkedList();
		
		list.insertLast(3, "Hello");
		list.insertLast(10, "Hello");
		list.insertLast(1, "Hello");
		list.insertLast(20, "Hello");
		
		System.out.println(count(list));
		
		System.out.println(getNth(list.getHead(), 2));
		System.out.println(getNth(list.getHead(), 3));
		
		DLinkedList.Node node = new DLinkedList.Node(1231, "sda");
		
		insertNth(list.getHead(), node, 2);
		System.out.println(list);
		
		
		
		
	}
	*/
}
