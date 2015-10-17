package CS249_Project1;

public class DLinkedList {
	
	private Node head;
	private Node tail;
	
	DLinkedList(){
		head = tail = null;
	}
	
	public void insertLast(int i, String s){
		Node newNode = new Node(i,s);
		
		if(tail == null){
			head = tail = newNode;
			
		}
		else{
			tail.next = newNode;
			newNode.prev = tail;
			tail = newNode;
		}
	}

	 public Node getHead() {
		return head;
	}

	public Node getTail() {
		return tail;
	}

	public void insertFirst(int i, String s){
		 Node newNode = new Node(i,s);
		 
		 if(head == null)
			 head = tail = newNode;
		 else{
		 head.prev = newNode;
		 newNode.next = head;
		 head = newNode;
		 }
	 }

	 public String toString(){
		 String returnString = "";
		 Node iterator = head;
		 
		 do{
			 returnString += iterator.iData + " "; 
			 iterator = iterator.next;
		 }while(iterator != null);
		 
		 return returnString;
	 }
	 
	 public static void main (String [] args){
		 
		 DLinkedList list = new DLinkedList();
		 
		 list.insertLast(10, "Hello");
		 list.insertLast(11, "Hello");
		 list.insertLast(12, "Hello");
		 list.insertLast(13, "Hello");
		
		 System.out.println(list);
		
		 list.insertFirst(1, "Hello");
		 
		 System.out.println(list);
	 }
	 
	 
	public static class Node{
		
		public int iData;
		public String sData;
		Node next;
		Node prev;
		
		Node(int i, String s){
			iData = i;
			sData = s;
		}
		
		public String toString(){
			return iData + ", " + sData;
		}
	}

}
