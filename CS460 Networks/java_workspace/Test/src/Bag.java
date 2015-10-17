import java.awt.Color;
import java.util.Arrays;


public class Bag {

	
	private Apple apple[];
	private int numApples;
	
	Bag(int capacity){
		apple = new Apple[capacity];
	}
	
	void addApple(Apple newApple){
		
		if(numApples == apple.length)
			System.out.println("There is no room in the bag for more apples!!!");
		
		for(int i = 0; i < apple.length; i++)
			if(apple[i] == null)
			{
				apple[i] = newApple;
				numApples++;
				return;
			}
	}
	
	public Apple removeApple(int index){
		
		Apple removedApple = null;
		
		if(apple[index] != null){
			removedApple = apple[index];
			apple[index] = null;
			numApples--;
		}
		
		return removedApple;
	}
	
	public String toString() {
		return "Bag [apple=" + Arrays.toString(apple) + ", numApples="
				+ numApples + "]";
	}
	
	public Apple[] getApple() {
		return apple;
	}

	public void setApple(Apple[] apple) {
		this.apple = apple;
	}

	public int getNumApples() {
		return numApples;
	}
	
	public static void main(String[] args) {
		
		Bag bag = new Bag(5);
		
		System.out.println(bag);
		
		bag.addApple(bag.new Apple("green"));
		System.out.println(bag);
		
		bag.removeApple(3);
		bag.removeApple(0);
		System.out.println(bag);
	}
	
	
	//inner class for Apple
	private class Apple{

		public String type;
		public Color color;
		
		Apple(String name){
			type = name;
			color = Color.RED;
		}
		
		public String toString() {
			return "Apple [type=" + type + ", color=" + color + "]";
		}
	}

}