//
//  Threading.h
//  CSC240 project
//
//  Created by Kelvin Rodriguez on 10/30/14.
//  Copyright (c) 2014 Kelvin.rodriguez. All rights reserved.
//

#ifndef __CSC240_project__Threading__
#define __CSC240_project__Threading__

// include all the things
#include <iostream>
#include <time.h>
#include <vector>

// typedef a thing
typedef std::unique_ptr<std::vector<int>> Vector_Smart_Ptr;

// the sorts of all sorts
int bubble_sort    (std::vector<int>&);
int selection_sort (std::vector<int>&);
int insertion_sort (std::vector<int>&);

// other stuff
std::string vector_to_string(std::vector<int>&);
void print_function_timing(Vector_Smart_Ptr&, int (*function)(std::vector<int>&));
Vector_Smart_Ptr get_random_vector(void);

#endif /* defined(__CSC240_project__Threading__) */
