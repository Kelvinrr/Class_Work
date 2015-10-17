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
public class Employee extends Person implements Pay{
    double salary;

    public Employee(String n, int ag, String ad, String ph, double sal){
        super(n, ag, ad, ph);   //use constructor of the super class
        salary=sal;
        System.out.println("This person is an employee.");

    }

    @Override
    public void pay (double rate){
        salary+= rate;
    }
}
