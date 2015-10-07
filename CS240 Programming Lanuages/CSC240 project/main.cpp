//
//  main.cpp
//  CSC240 project
//
//  Created by Kelvin Rodriguez on 10/23/14.
//  Copyright (c) 2014 Kelvin.rodriguez. All rights reserved.
//

#include <iostream>
#include "Sorting.h"

int main() {
    // lambda function for printing the menu.
    auto print_menu = [](int& input, Vector_Smart_Ptr& array){
        array = get_random_vector();
        std::cout << "What do you want to run?" << std::endl
                  << "------------------------" << std::endl
                  << "1. Bubble Sort"           << std::endl
                  << "2. Selection Sort"        << std::endl
                  << "3. Insertion Sort"        << std::endl
                  << "4. quit"                  << std::endl
                  << "------------------------" << std::endl;
        std::cout << "-->";
        std::cin  >> input;

        switch (input) {
            case 1:
                print_function_timing(array, bubble_sort);
                break;
            case 2:
                print_function_timing(array, selection_sort);
                break;
            case 3:
                print_function_timing(array, insertion_sort);
                break;
            case 4:
                 std::cout << "Ok, I'll miss you..." << std::endl;
                break;
            default:
                std::cout << "Incorrect input, try again" << std::endl;
                break;
        }
    };

    int input;
    Vector_Smart_Ptr array;

    do {
    print_menu(input, array);
    } while (input != 4);
}
