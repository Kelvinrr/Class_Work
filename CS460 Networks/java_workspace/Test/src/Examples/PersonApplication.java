package Examples;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author mlh395
 */
import java.util.Scanner;

public class PersonApplication {
    
     public static void main(String[] args) {
        Person a = new Person("Maggie");
        Person b = new Person("Mary", 18);

        int i = Integer.parseInt(args[0]);
        Person [] people_array = new Person[i];
        System.out.println("Length of people array is: " + people_array.length);

        Scanner in = new Scanner(System.in);
        String name;
        int age;

        System.out.println("Enter a person's name to add to the array: ");
        name = in.next();
        people_array[0]=new Person(name);
        
        try{
            System.out.println("Enter the person's age: ");
            String oneLine = in.next();
            age = Integer.parseInt(oneLine);
            people_array[0].setAge(age);
        } catch (NumberFormatException e){
            System.out.println("Error: " + e);
            System.out.println("Age must be a number. Please re-enter the age:");
            String oneLine = in.next();
            age = Integer.parseInt(oneLine);
            System.out.println("You entered the age: " + age);
            people_array[0].setAge(age);
        }
        
        int ag = people_array[0].getAge();
        System.out.println("Age is: "+ag);

        Student s = new Student("Mike",19,"123 Main St.", "919-602-2323",3.5);
        people_array[1]=s;
        System.out.print("Last person created has name of length: " + people_array[1].getNameLength() + " and ");
        s.printAge();
        
        people_array[0]=a;
        people_array[1]=new Person("Suzy", 21);

        Student x = new Student("Joe", 15, "123 Main", "919-212-5005", 3.9);
        System.out.println("The student is:" + x.toString());

        a = x;   //set Person a to point to student object x

        Employee e = new Employee("Jill", 50, "13 1st Ave", "212-604-4505", 2000.00);

        StudentEmployee se = new StudentEmployee("John", 22, "100 2nd Ave", "312-334-0003", 3.5, 3000.00);
        System.out.println(se.toString());

        people_array[3]=se;

        System.out.println("Creating pairs....");
        Pair<Person, String> p1 = new Pair<Person,String>(a,"president");
        Pair<Student, Integer> p2 = new Pair<>(s,1);

        System.out.println("Printing pairs: " +p1.toString() +" "+ p2.toString());
    }



}
