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
public class Person {
    private String name;
    private int age;
    private String address;
    private String phone_number;

    public Person(String name){
        this.name=name;
        System.out.println("A person with the name " + name + " has just been created.");
    }

    public Person(String name, int age){
        this.name=name;
        this.age=age;
        System.out.println("A "+age+ " year old person with the name " + name + " has just been created.");
    }

    public Person(String n, int ag, String ad, String p){
        name=n;
        age=ag;
        address=ad;
        phone_number=p;
        System.out.println("A "+age+ " year old person with the name " + name + " has just been created. Address and phone were initialized too.");
    }
    @Override
    public String toString(){
        String thePerson = "Name: " + name + ", Age: " + age + ", Address: " + address + ", Phone # " + phone_number;
        return thePerson;
    }

    public int getNameLength(){
        return name.length();
    }

    public void setAge(int i){
        age=i;
    }

    public int getAge(){
        return age;
    }
    public void printAge(){
        switch(age){
            case 18:case 19:case 20:
                System.out.println("Age is between 18 and 20.");
                break;
            case 21:case 22:case 23:case 24:case 25:case 26:case 27:case 28:case 29:
                System.out.println("Age is between 21 and 29");
                break;
            default:
                System.out.println("Age is less than 18 or creater than 29.");
        }

    }

}
