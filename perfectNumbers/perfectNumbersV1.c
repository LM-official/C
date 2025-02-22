/* :::::::::::::::::::::::::::::::::::::::::::::: MATH SOURCES :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
perfect numbers definition:       https://en.wikipedia.org/wiki/Perfect_number
every even perfect number:
    - is a triangular number:     https://en.wikipedia.org/wiki/Triangular_number
    - is an hexagonal number:     https://en.wikipedia.org/wiki/Hexagonal_number#:~:text=1%2C%206%2C%2015%2C%2028,.)%20is%20a%20hexagonal%20number.
    - is a practical number:      https://en.wikipedia.org/wiki/Practical_number
    - has a binary expression with p lenght ​​equal to one followed by p-1 zeros (p prime)
        # examples:
        # 6 base 10 = 110 base 2
        # 28 base 10 = 11100 base 2
    
Mersenne's theory:                https://en.wikipedia.org/wiki/Mersenne_prime
list of perfect numbers:          https://en.wikipedia.org/wiki/List_of_Mersenne_primes_and_perfect_numbers
    # first 12 perfect numbers:
    # 6
    # 28
    # 496
    # 8 128
    # 33 550 336 (8 digits)
    # 8 589 869 056 (10 digits)
    # 137 438 691 328 (12 digits)
    # 2 305 843 008 139 952 128 (19 digits)
    # 2 658 455 991 569 831 744 654 692 615 953 842 176 (37 digits)
    # 191 561 942 608 236 107 294 793 378 084 303 638 130 997 321 548 169 216 (54 digits)
    # 13 164 036 458 569 648 337 239 753 460 458 722 910 223 472 318 386 943 117 783 728 128 (65 digits)
    # 14 474 011 154 664 524 427 946 373 126 085 988 481 573 677 491 474 835 889 066 354 349 131 199 152 128 (77 digits) */



/* :::::::::::::::::::::::::::::::::::::::::::::::: C SOURCES ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
struct:
    https://www.w3schools.com/c/c_structs.php

time: 
    https://www.geeksforgeeks.org/time_taken-h-header-file-in-c-with-examples
    https://www.geeksforgeeks.org/how-to-measure-time_taken-taken-by-a-program-in-c

linked list:
    https://www.geeksforgeeks.org/linked-list-in-c
    https://www.geeksforgeeks.org/insertion-in-linked-list
    https://learn.microsoft.com/it-it/cpp/c-runtime-library/reference/malloc?view=msvc-170
    https://learn.microsoft.com/it-it/cpp/c-runtime-library/reference/free?view=msvc-170
    https://www.geeksforgeeks.org/understanding-time-complexity-simple-examples

bitwise shifting:
    https://www.geeksforgeeks.org/left-shift-right-shift-operators-c-cpp

data types:
    https://en.wikipedia.org/wiki/C_data_types */



// ::::::::::::::::::::::::::::::::::::::::::::::::: LIBRARIES :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/**
 * @file perfectNumbersV1.c
 * @author Lorenzo Mercuri
 * @version 1.0
 * @brief Computes perfect numbers
 * @details Look at the sources at the begging of the file
 */
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h> // for dynamic memory allocation



// ::::::::::::::::::::::::::::::::::::::::::::::::::::: NODE ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/**
 * @struct node
 * @brief Represent a node of a linked list
 * @details It has unsigned integer value (~ 4*10^9),
 * an unsigned long long integer value (~ 18*10^18) 
 * and a pointer to the next node in the list.
 * Time complexity: O(1)
 */
typedef struct node{
    unsigned int value1;
    unsigned long long int value2;
    struct node* next;
} node;


/**
 * @brief Create a new node
 * @details Dynamically allocates memory for a new node,
 * initialize the integer values to the argument and the pointer to NULL.
 * Time complexity: O(1)
 * @warning If memory allocation fails prints an error and exit program.
 * @param v1 The first integer value of the node
 * @param v2 The second integer value of the node
 * @return node* Pointer to the new node
 */
node* create_node(unsigned int v1, unsigned long long int v2){
    node* new_node = (node*)malloc(sizeof(node)); // dynamic allocation for the new node
    if (!new_node) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE); // critic error
    }
    (*new_node).value1 = v1; // (*...) dereference
    (*new_node).value2 = v2;
    (*new_node).next = NULL;
    return new_node;
}


/**
 * @brief Insert a node at the head of a linked list
 * @details Takes a node and inserts it at the beginning of the list.
 * Time complexity: O(1)
 * @param head Pointer to the current head of the linked list
 * @param n Pointer to the node to be inserted at the head
 * @return node* Pointer to the new head of the linked list
 */
node* insertion_head_node(node* head, node* n){
    (*n).next = head;
    return n;
}


/**
 * @brief Insert a node at the end of a linked list
 * @details Takes a node and inserts it at the end of the list.
 * Time complexity: O(n), n = number of nodes in the list
 * @param head Pointer to the head of the linked list
 * @param n Pointer to the node to be inserted at the end
 * @return node* Pointer to the head of the modified linked list
 */
/* node* insertion_end_node(node* head, node* n){
    node* temp = head;
    while((*temp).next) { // while is not null
        temp = (*temp).next;
    }
    (*temp).next = n;
    return head;
} */
/// there are other types of insertion but these are enough


/**
 * @brief Prints the values of each node of the linked list
 * @details Time complexity: O(n), n = number of nodes in the list
 * @param head Pointer to the head of the linked list
 * @return void Doesn't return a value
 */
void print_list(node* head){
    node* temp = head;
    while(temp) {
        printf("(%u, %llu)\n", (*temp).value1, (*temp).value2);
        temp = (*temp).next;
    }
}


/**
 * @brief Frees the memory allocated for a linked list
 * @details Deallocates each node's memory of a linked list.
 * Time complexity: O(n), n = number of nodes in the list
 * @param head Pointer to the head of the list
 * @return void Doesn't return a value
 */
/* void free_list(node* head){
    node* temp;
    while(temp) {
        temp = head;
        head = (*head).next;
        free(temp); // deallocate memory
    }
} */



// ::::::::::::::::::::::::::::::::::::::::::::::::::: IS_PRIME ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/**
 * @brief Checks if a number is prime
 * @details Prime numbers are integers greater than 1 and divisible only by 1 and themselves.
 * Time complexity: O(sqrt(n)), since the function iterates up to sqrt(n)
 * @param n The number to check
 * @return 1 if the number is prime or 0 if it is not prime
 */
int is_prime(unsigned long long int n){
    if (n % 2 == 0 || n % 5 == 0) return 0; // all prime numbers are odd and don't end with 5

    unsigned long long int limit = (unsigned long long int)sqrt(n);
    for (int i = 3; i <= limit; i+=2) if (n % i == 0) return 0;

    return 1;
}



// :::::::::::::::::::::::::::::::::::::::::::::::: PERFECT_NUMBERS ::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/**
 * @brief Generates a linked list containing the first n perfect numbers
 * @details Uses Mersenne primes to compute even perfect numbers and stores them in a linked list.
 * Prints the execution time.
 * Time complexity: O(n * sqrt(m)), n = number of perfect numbers to generate, m = the largest Mersenne primaly test
 * @param n Number of perfect numbers to generate
 * @return node* Pointer to the head of the linked list containing the perfect numbers
 */
node* n_perfect_numbers(unsigned short int n){
    clock_t time = clock();
    unsigned int prime_index = 1;
    unsigned long long int mersenne = 0, perfect_number = 0;
    node* head = NULL;
    while (n > 0){
        prime_index ++;

        mersenne = (1 << prime_index) - 1;// calculates Mersenne's number, mersenne = pow(2, prime_index)-1;
        if (is_prime(mersenne) != 1) continue; // valid <=> Mersenne's number is prime (extra: all perfect number computed using Mersenne's number are even)
        node* new_node = create_node(prime_index, (1 << (prime_index - 1)) * mersenne); // possibile failure to memory allocation handled in create_node
        //node* new_node = create_node(prime_index, pow(2, prime_index-1) * mersenne); // possibile failure to memory allocation handled in create_node
        head = insertion_head_node(head, new_node);

        n--;
    }
    time = (clock() - time)/CLOCKS_PER_SEC; // execution time
    printf("Execution time: %dsec.\n", (int)time);
    return head;
}



// :::::::::::::::::::::::::::::::::::::::::::::::::::::: TESTS ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/**
 * @brief Entry point of the program
 * @details Prompts the user to enter the number of perfect numbers to generate, ensuring the input is a non-negative integer.
 * It then computes the perfect numbers and prints the resulting list.
 * Time complexity: O(n * sqrt(m)), n = number of perfect numbers to generate, m = the largest Mersenne primaly test
 * @return 0 on successful execution
 */
int main(){
    unsigned short int list_lenght = 0;
    printf("How many perfect numbers? ");
    scanf("%d", &list_lenght);

    node* result = n_perfect_numbers(list_lenght);
    print_list(result);
    // free_list(result); // redundant, memory deallocated by default
    return 0;

    /* compiling: gcc perfectNumbersV1.c -o perfectNumbersV1
    executing: perfectNumbersV1 */
}

// limited to 19 digits (unsigned long long int)
