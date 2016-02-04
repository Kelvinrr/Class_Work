//
//  strcat.c
//  Operating Systems
//
//  Created by Kelvin Rodriguez on 2/3/16.
//  Copyright © 2016 Kelvin.rodriguez. All rights reserved. I have lawyers.
//

#include <stdio.h>
#include <stdlib.h>

/**
 * @Description
 *      My personal version of strlen, usees pointer arithmatic. Using
 *      a char pointer as an iterator, keep iterating until you hit '/0' AKA
 *      the end of the string. Then subtract str_iter from str (i.e. the
 *      begin address from the end address) to get the length.
 *
 *
 * @input char* str_start c-string which you want the length of.
 * @output length of input string
 */
size_t str_len(const char* str_start) {
    const char* char_iter;
    for(char_iter = str_start; *char_iter; char_iter++);
    return (char_iter - str_start);
}

/**
 * @Description
 *      The concatination function, basic algorithm:
 *          - Sum the string lengths of the input array
 *          - Allocate the space
 *          - Iterate through original array copying the chars into
 *            new linear array delimited by spaces
 *
 * @input char** str_arr Input to be concatenated into a linear array
 * @output char* pointer to newly created array.
 */
char* str_cat(const char** str_arr) {
    size_t new_str_size = 0;
    size_t num_strs = 0;
    
    // get the size of new char array
    for (const char** str_iter = str_arr; *str_iter; str_iter++, num_strs++)
        new_str_size += str_len(*str_iter);
    
    // Allocate the space
    char* return_str = (char*)malloc(new_str_size+num_strs+1);
    if(!return_str)
        printf("Error allocating return_str in str_cat.");
    
    // Copy over he strings into the new array
    char* return_str_iter = return_str;
    for (const char** arr_iter = str_arr; *arr_iter; arr_iter++) {
        for(const char* str_iter = *arr_iter; *str_iter; return_str_iter++)
            *return_str_iter = *(str_iter++);
        
        // add a space between string concats
        *return_str_iter = ' ';
        return_str_iter++;
    }
    
    return_str_iter--;
    return_str_iter = '\0';
    return return_str;
}

/**
 * The main method. It is very important.
 */
int main(int argc, const char * argv[]) {
    
    printf("Original input array--------\n\n");
    for(int i = 1; i < argc; i++)
        printf("%i. %s\n", i, argv[i]);
    printf("\nNumber of elements: %i\n\n", argc-1);
    
    char* str = str_cat(argv+1);
    
    printf("Concatenated string---------\n\n%s\n", str);
    return 0;
}
