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
public class Student extends Person {
    double gpa;

    public Student(String n, int ag, String ad, String p, double g){
        super(n, ag, ad, p);   //use constructor of the super class
        gpa=g;
        System.out.println("This person is a student.");

    }

    //override toString method
    @Override
    public String toString(){
        String thePerson = super.toString() + " GPA: " +gpa;
        return thePerson;
    }

}
