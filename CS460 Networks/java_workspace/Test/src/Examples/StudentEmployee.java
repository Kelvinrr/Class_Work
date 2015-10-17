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
public class StudentEmployee extends Student implements Pay {
    double rate;
    public StudentEmployee(String n, int ag, String ad, String p, double g, double r) {
        super(n,ag,ad,p,g);
        rate=r;
        System.out.println("This person is also a student employee.");
    }
    @Override
    public void pay(double rate){
        this.rate=rate;
    }

    @Override
    public String toString(){
        return super.toString()+" Pay rate is: " + rate;

    }
}
