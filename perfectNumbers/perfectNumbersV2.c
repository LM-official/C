/* :::::::::::::::::::::::::::::::::::::::::::::: MATH SOURCES :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
perfect numbers definition:       https://en.wikipedia.org/wiki/Perfect_number
every even perfect number:
    - is a triangular number:     https://en.wikipedia.org/wiki/Triangular_number
    - is an hexagonal number:     https://en.wikipedia.org/wiki/Hexagonal_number#:~:text=1%2C%206%2C%2015%2C%2028,.)%20is%20a%20hexagonal%20number.
    - is a practical number:      https://en.wikipedia.org/wiki/Practical_number
    - has a binary expression with p lenght ​​equal to one followed by p-1 zeros (p prime)
        examples:
            6 base 10 = 110 base 2
            28 base 10 = 11100 base 2
    
Mersenne's theory:                https://en.wikipedia.org/wiki/Mersenne_prime
Miller-Rabin:                     https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
list of perfect numbers:          https://en.wikipedia.org/wiki/List_of_Mersenne_primes_and_perfect_numbers
    first 12 perfect numbers:
    6
    28
    496
    8 128
    33 550 336 (8 digits)
    8 589 869 056 (10 digits)
    137 438 691 328 (12 digits)
    2 305 843 008 139 952 128 (19 digits)
    2 658 455 991 569 831 744 654 692 615 953 842 176 (37 digits)
    191 561 942 608 236 107 294 793 378 084 303 638 130 997 321 548 169 216 (54 digits)
    13 164 036 458 569 648 337 239 753 460 458 722 910 223 472 318 386 943 117 783 728 128 (65 digits)
    14 474 011 154 664 524 427 946 373 126 085 988 481 573 677 491 474 835 889 066 354 349 131 199 152 128 (77 digits)

    mpz_mul switch automatically to better algorithm for non galactic number (too big numbers)
    (Karatsuba                    https://en.wikipedia.org/wiki/Karatsuba_algorithm, 
    Toom-Cook                     https://en.wikipedia.org/wiki/Toom%E2%80%93Cook_multiplication and
    Schönhage-Strassen            https://en.wikipedia.org/wiki/Sch%C3%B6nhage%E2%80%93Strassen_algorithm) */

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
    https://en.wikipedia.org/wiki/C_data_types 
    
GNU (Multiple Precision Arithmetic Library):
There is no practical limit to the precision except the ones implied by the available memory in the machine GMP runs on
    https://gmplib.org
    https://en.wikipedia.org/wiki/GNU_Multiple_Precision_Arithmetic_Library 
    https://gmplib.org/gmp-man-6.3.0.pdf
    https://www.youtube.com/watch?v=xqUCz0Mt0Mo */



// ::::::::::::::::::::::::::::::::::::::::::::::::: LIBRARIES :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/**
 * @file perfectNumbersV2.c
 * @author Lorenzo Mercuri
 * @version 2.0
 * @brief Computes perfect numbers
 * @details Look at the sources at the begging of the file
 */
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h> // for dynamic memory allocation
#include <gmp.h> // Multiple Precision Arithmetic Library



// ::::::::::::::::::::::::::::::::::::::::::::::::::::: NODE ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/**
 * @struct node
 * @brief Represent a node of a linked list
 * @details It has mp_bitcnt_t value for storing the prime number,
 * an usize_t value for storing the lenght of the perfect number,
 * an mpz_t value for storing the perfect number
 * and a pointer to the next node in the list.
 * Time complexity: O(1)
 */
typedef struct node{
    mp_bitcnt_t value1;
    size_t value2;
    mpz_t value3;
    struct node* next;
} node;


/**
 * @brief Create a new node
 * @details Dynamically allocates memory for a new node,
 * initialize the integer values to the argument and the pointer to NULL.
 * Time complexity: O(1)
 * @warning If memory allocation fails prints an error and exit program.
 * @param v1 The mp_bitcnt_t value of the node
 * @param v2 The size_t value of the node
 * @param v3 The mpz_t value of the node
 * @return node* Pointer to the new node
 */
node* create_node(mp_bitcnt_t v1, size_t v2, mpz_t v3){
    node* new_node = (node*)malloc(sizeof(node)); // dynamic allocation for the new node
    if (!new_node) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE); // critic error
    }

    // (*...) dereference
    (*new_node).value1 = v1; // initialize
    (*new_node).value2 = v2; // initialize
    mpz_init((*new_node).value3); // initializes
    mpz_set((*new_node).value3, v3); // sets value
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
        gmp_printf("(prime: %lu\n digits: %zu\n perfect number: %Zd)\n\n", (*temp).value1, (*temp).value2, (*temp).value3); // prints
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



// :::::::::::::::::::::::::::::::::::::::::::::::: PERFECT_NUMBERS ::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/**
 * @brief Generates a linked list containing n perfect numbers
 * @details Uses Mersenne primes to compute even perfect numbers and stores them in a linked list.
 * Prints the execution time.
 * Time complexity: O(n * k * m^3),
 * n = number of perfect numbers to generate,
 * k = rounds of Miller-Rabin test,
 * m = digits of the largest Mersenne's number
 * @param n Number of perfect numbers to generate
 * @param prime_index The starting prime number
 * @return node* Pointer to the head of the linked list containing the perfect numbers
 */
node* find_perfect_numbers(unsigned short int n, mp_bitcnt_t prime_index){
    clock_t time = clock();
    mpz_t mersenne, perfect_number, one; // defines
    size_t length = 0;
    mpz_inits(mersenne, perfect_number, one, NULL); // initializes variables until NULL
    mpz_set_ui(one, 1); // sets value
    node* head = NULL;

    while (n > 0){
        prime_index++;

        mpz_mul_2exp(mersenne, one, prime_index); // mersenne = 1 * 2^prime_index
        mpz_sub_ui(mersenne, mersenne, 1); // mersenne--

        /* do 24 test (as much as Miller-Rabin primality test) to determinate if mersenne is probably prime.
        returns 2 if it's prime, returns 1 if it's probably prime, returns 0 if it's not prime */
        if (mpz_probab_prime_p(mersenne, 24) == 0) continue;
        
        mpz_mul_2exp(perfect_number, one, prime_index-1); // perfect_number = 1 * 2^(prime_index-1)
        mpz_mul(perfect_number, perfect_number, mersenne); // perfect_numer *= mersenne
        length = mpz_sizeinbase(perfect_number, 10); // length = len(perfect_number)

        node* new_node = create_node(prime_index, length, perfect_number); // possibile failure to memory allocation handled in create_node
        head = insertion_head_node(head, new_node);

        n--;
    }

    //mpz_clears(mersenne, perfect_number, NULL); // redundant, free the occupied space
    time = (clock() - time)/CLOCKS_PER_SEC; // execution time
    printf("Execution time: %dsec.\n", (int)time);
    return head;
}

/**
 * @brief Wrapper function to find the first n perfect numbers
 * @details Time complexity: O(n * k * m^3),
 * n = number of perfect numbers to generate,
 * k = rounds of Miller-Rabin test,
 * m = digits of the largest Mersenne's number
 * @param n Number of perfect numbers to generate
 * @return node* Pointer to the head of the linked list containing the perfect numbers
 */
node* perfect_numbers(unsigned short int n) {
    mp_bitcnt_t prime_start = 1; // define and initialize
    return find_perfect_numbers(n, prime_start);
}
/**
 * @brief Wrapper function to find n perfect numbers from a given prime number
 * @details Time complexity: O(n * k * m^3),
 * n = number of perfect numbers to generate,
 * k = rounds of Miller-Rabin test,
 * m = digits of the largest Mersenne's number
 * @param n Number of perfect numbers to generate
 * @param prime_start Starting prime number
 * @return node* Pointer to the head of the linked list containing the perfect numbers
 */
node* perfect_numbers_with_start_prime(unsigned short int n, mp_bitcnt_t prime_start) {
    return find_perfect_numbers(n, prime_start);
}


// :::::::::::::::::::::::::::::::::::::::::::::::::::::: TESTS ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/**
 * @brief Entry point of the program
 * @details Prompts the user to enter the number of perfect numbers to generate, ensuring the input is a non-negative integer.
 * It then computes the perfect numbers and prints the resulting list.
 * Time complexity: O(n * k * m^3),
 * n = number of perfect numbers to generate,
 * k = rounds of Miller-Rabin test,
 * m = digits of the largest Mersenne's number
 * @warning Assumes valid user input
 * @return 0 on successful execution
 */
int main(){
    unsigned short int list_lenght = 0;
    // mp_bitcnt_t prime_start = 23209; // define and initialize

    printf("How many perfect numbers? ");
    scanf("%d", &list_lenght);

    node* result = perfect_numbers(list_lenght);
    print_list(result);
    // free_list(result); // redundant, memory deallocated by default
    return 0;
    
    /* compiling: gcc perfectNumbersV2.c -o perfectNumbersV2 -lgmp
    executing: perfectNumbersV2 */
}

/* MY RESULT (with i7-9700):
first 20 perfect number computed in ~ 20 seconds (prime number: 4423)

first 21 perfect number computed in ~ 4 minutes (prime number: 9689)
the 21th perfect number computed in ~ 4 minutes (prime number: 9689) (start searching from 4423)
    
first 22 perfect number computed in ~ 4 minutes (prime number: 9941)
the 22th perfect number computed in ~ 36 seconds (prime number: 9941) (start searching from 9689)
    
first 23 perfect number computed in ~ 7 minutes (prime number: 11213)
the 23th perfect number computed in ~ 2 minutes (prime number: 11213) (start searching from 9941)
    
the 24th perfect number computed in ~ 37 minutes (prime number: 19937) (start searching from 11213)
    
the 25th perfect number computed in ~ 15 minutes (prime number: 21701) (start searching from 19937)
    
the 26th perfect number computed in ~ 16 minutes (prime number: 23209) (start searching from 21701)

the 27th perfect number not computed yet (start searching from 23209)
*/



// ::::::::::::::::::::::::::::::::::::::::::::::: POSSIBLE UPGRADES :::::::::::::::::::::::::::::::::::::::::::::::::::::::
/* the limit occurred is the time used in the computation
use multiprocessing for computing */