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
public class Pair <T,S> {
    private T first;
    private S second;

    //Constructor
    public Pair(T firstElement, S secondElement){
        first=firstElement;
        second=secondElement;
    }

    //Return first object
    public T getFirst(){
        return first;
    }

    //Return second object
    public S getSecond(){
        return second;
    }

    //Return objects as a pair such as (X,Y)
    public String toString(){
        return "(" + first + "," + second + ")";
    }
}

