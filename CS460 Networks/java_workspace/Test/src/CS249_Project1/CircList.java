package CS249_Project1;

public class CircList{
	
	private Node current;        // ref to current node
	private Node tail;			 // Node at end of circList (i.e the node right before current)
	private int count;           // # of nodes on list


    public CircList() {             // constructor
		count = 0;                  // no nodes in the list yet
		current = null;
		tail = null;
    }


    public void insert(long id) {   // insert  node before current
    	Node newNode = new Node(id);
    	
    	if(count > 0){
    		tail.next = newNode;
    		newNode.next = current;
    		current = newNode;
    	}
    	else{
    		current = newNode;
    		current.next = newNode;
    		tail = newNode;
    	}

    	count++;
    }

    public Node delete() {         // delete current node

    	Node returnNode = current;
    	current = current.next;
    	tail.next = current;
    	return returnNode;
    }

    public Node find(long key) {     // find first node starting at  current with given key
    	Node iterator = current;
    	if(count > 0){
	    	do{
	    		if(iterator.iData == key)
	    			return iterator;
	    		
	    		iterator = iterator.next;
	    	}while(iterator != current);
    	}
    	
    	System.out.println("Error: element not found");
    	return null;
    }

    public Node delete(long key){    // delete node with given key

    	boolean found = false;
    	Node iterator = current;
    	
    	// if only one element
    	if(count == 1 && iterator.iData == key){
    		found = true;
    		current = null;
    	}
    	
    	//if first element needs to be removed with count > 1
    	else if(iterator.iData == key){
    		found = true;
    		current = current.next;
    		tail.next = current;
    	}
   
    	else{
	    	do{
	    		if(iterator.next.iData == key){
	    			found = true;
	    			break;
	    		}
	    		iterator = iterator.next;
	    	}while(iterator.next != current);
	    
	    	// if item to be removed is the tail
	    	if(iterator.next == tail)
	    		tail = iterator;
	    	
	    	iterator.next = iterator.next.next;
    	}
    	
    	// only return and decrement count if found a matching node
    	if (found){
    		count--;
    		return iterator;
    	}
    	
    	System.out.println("Error: Item to be removed not found");
    	return null; // would be better to throw exception, but screw it.

    }
 
  
	public class Node{

	   public long iData;              // data item (key)
	   public Node next;              // next node in the list

	   // -------------------------------------------------------------
	   public Node(long id) {           // constructor
	          iData = id;		// (next automatically null)
	    }             

	   // -------------------------------------------------------------
	   public void displayNode() {     // display yourself
	         System.out.print(iData + " ");
	    }
	  
	 }  // end class Node


}  // end class CircList



