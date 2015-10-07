//
//  Threading.cpp
//  CSC240 project
//  
//  
//
//
//  Created by Kelvin Rodriguez on 10/30/14.
//  Copyright (c) 2014 Kelvin.rodriguez. All rights reserved.
//

#include "Sorting.h"

// Sorting Functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// simple off-the-shelf bubble sort algorithm, returns the number of iterations
int bubble_sort(std::vector<int>& vector){
    int num_interations = 0;
    
    for (std::vector<int>::iterator  i = vector.begin(); i != vector.end(); ++i, ++num_interations)
        for(std::vector<int>::iterator  j = vector.begin(); j != vector.end(); ++j, ++num_interations)
            if (*i < *j)
                std::swap(*i, *j);
    
    return num_interations;
}

// simple off-the-shelf selection sort algorithm, returns the number of iterations
int selection_sort(std::vector<int>& vector){
    std::vector<int>::iterator j;
    std::vector<int>::iterator min_ptr;
    int num_iterations = 0;
    
    for (std::vector<int>::iterator i = vector.begin(); i != vector.end(); ++i, num_iterations++){
        
        min_ptr = i;
        for (j = i; j != vector.end(); ++j, num_iterations++)
            if (*j < *min_ptr)
                min_ptr = j;
  
        if(min_ptr != i)
            std::swap(*i, *min_ptr);
    }
    
    return num_iterations;
}

// simple off-the-shelf insertion sort algorithm, returns the number of iterations
int insertion_sort(std::vector<int>& vector) {
    std::vector<int>::iterator j;
    int num_iterations = 0;
    
    for (std::vector<int>::iterator i = vector.begin() + 1; i != vector.end(); ++i, ++num_iterations)
        for (j = i; (j >= vector.begin()) && *(j-1) > *j; --j, ++num_iterations)
            std::swap(*j, *(j - 1));
    
    return num_iterations;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Utility Functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


// gets the run time of a function, passes the function as a parameter
void print_function_timing(Vector_Smart_Ptr& vector, int (*funtion)(std::vector<int>&)){
    // get start time
    double start_time = clock();
    
    // call the function
    int iterations = funtion(*vector);
    
    // print sorted vector, number of iterations and total time
    std::cout << "Sorted vector: " << std::endl << vector_to_string(*vector);
    std::cout << "Number of iterations: " << iterations << std::endl;
    std::cout << "Sorting time: " << (clock() - start_time)/(CLOCKS_PER_SEC/1000)
              << " Milliseconds"  << std::endl << std::endl;
}

// simple function to print an vector
std::string vector_to_string(std::vector<int>& vector){
    std::string return_string = "";
    
    return_string += "\n--------- BEGIN ---------\n";
    for(std::vector<int>::const_iterator i = vector.begin(); i != vector.end(); ++i)
        return_string += "    " + std::to_string(i - vector.begin()) + ":" + std::to_string(*i) + "\n";
    return_string +=   "---------- END ----------\n";
    
    return return_string;
}

// returns a unique pointer to a 1000 size vector of random numbers
std::unique_ptr<std::vector<int>> get_random_vector(){
    // create a new vector
    std::unique_ptr<std::vector<int>> return_vector (new std::vector<int>(1000));
    
    // radmonly generate numbers between -1000 and 1000
    for(std::vector<int>::iterator  i = return_vector->begin(); i != return_vector->end(); ++i)
        *i = (rand() % 2000 ) - 1000;
    
    return return_vector;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


