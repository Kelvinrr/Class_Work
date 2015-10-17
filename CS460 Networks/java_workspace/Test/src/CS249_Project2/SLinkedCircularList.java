/**
 * @author Kelvin Rodriguez (KR788)
 * @date 3/1/2015
 * 
 * file containing a simple implementation of circular linked list.
 * 
 */


package CS249_Project2;

public class SLinkedCircularList<T> {
	
	private Node<T> head;
	private int size;
	
	
	public Node<T> insert(T newElement){
		Node<T> node = new Node<T>(newElement);	
		
		if(head == null)
			node.next = head = node;
		else{
			node.next = head.next;
			head.next = node;
		}
		
		size++;
		return node;
	}
	
	public Node<T> delete() throws Exception{
		
		if(head == null)
			throw new Exception("Can't remove from an empty list");
		
		Node<T> node = head.next;
		
		if(size == 1)
			head = null;
		
		else
			head.next = head.next.next;
		
	
		size--;
		return node;
	}
	
	public Node<T> delete(Node<T> node) throws Exception{
		if(head == null)
			throw new Exception("Can't remove from an empty list");
		if(size == 1 && node == head)
			head = null;
		
		else{
			boolean found = false;
			Node<T> iterator = head;
			
			do{
				found = iterator.next == node;
				if(!found)
					iterator = iterator.next;
			}while(!found && iterator != head);
			
			if(found)
				iterator.next = iterator.next.next;
			else
				System.out.println("The Node was not found in the list!");
		}
		
		
		size--;
		return node;
	}
	
	public boolean contains(Node<T> node){
		
		if(size <= 1)
			return head != null && head.equals(node);
		
		Node<T> iterator = head.next;
		boolean found = false;
		
		do{
			found = iterator.equals(node);
			iterator = iterator.next;
		}while(!found && iterator != head.next);
		
		return found;
	}
	
	public String toString(){
		
		if(isEmpty())
			return "Empty";
			
		String returnString = "";
		Node<T> iterator = head.next;
		
		do{
			returnString += "[" + iterator.data + "]";
			iterator = iterator.next;
		}while(iterator != head.next);
		
		return returnString;
	}
	
	public boolean isEmpty(){
		return size == 0;
	}
	
	public Node<T> getHead(){
		return head.next;
	}
	
	public int getSize(){
		return size;
	}
	
	/**
	 * @author kelvinrodriguez
	 *
	 * Inner Node class, used by the outer list. Also uses generics.
	 * @param <T> type of data to store
	 */
	static class Node<T>{
		
		private T data;
		Node<T> next; //set to package private for simplicity 
		
		/**
		 * Parameterized constructor, creates a new node 
		 * with the passed in data
		 * @param data
		 */
		Node(T data){
			this.data = data;
			next = null;
		}
		
		public String toString(){
			
			String returnString = "";
			returnString += data;
			return returnString;
			
		}
		
		/**
		 * simple equals method
		 * @returns whether or not this and the passed in node 
		 * have equal date.
		 */
		public boolean equals(Object node){
			if(node == null)
				return false;
			
			if(!(node instanceof Node))
				return false;
			
			@SuppressWarnings("unchecked")
			Node<T> temp = (Node<T>)node;
			
			if(temp.getData().equals(this.getData()))
				return true;
			
			return false;
		}
		
		public T getData(){
			return data;
		}
	}
	
	
}
