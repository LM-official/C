// ::::::::::::::::::::::::::::::::::::::::::::::::: LIBRARIES :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/**
 * @file linkedList.c
 * @author Lorenzo Mercuri
 * @brief Methods for list manipulation
 */
#include <stdio.h>
#include <stdlib.h>



// :::::::::::::::::::::::::::::::::::::::::::::::::::::: LIST ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/* LIST OF FUNCTIONS:
    creations:
        1) create_node
        2) create_empty_node
        3) create_list
    4) print_list
    5) clear_list
    insertions:
        6) insertion_head_node
        7) insertion_end_node
        8) insertion_after_node
        9) insertion_before_node
    10) concatenate_lists
    11) split_list_at_node
    12) split_list_at_value
    removes:
        13) remove_node
        14) remove_node_with_value
    changes:
        15) change_node_value
        16) change_node_value_with_value
    17) is_empty_list
    in_list:
        18) node_in_list
        19) value_in_list
    20) reverse_list
    21) list_length
    22) max_list
    23) min_list
    24) count_frequents_in_list
    25) sort_list 
    26) list_values */


/**
 * @struct node
 * @brief Represent a node of a linked list
 * @details It has a value and a pointer to the next node in the list.
 * Time complexity: O(1)
 */
typedef struct node{
    int value1; // change type if needed (apply changes to all references)
    struct node* next;
} node;

const int DEFAULT_VALUE = 0; // change 0 to another default value

/**
 * @struct tuple
 * @brief Represent a tuple of 2 nodes of a linked list
 * Time complexity: O(1)
 */
typedef struct{
    node* node1;
    node* node2;
} tuple;


/**
 * @brief Create a new node
 * @details Dynamically allocates memory for a new node,
 * initialize the values to the argument and the pointer to NULL.
 * Time complexity: O(1)
 * @warning If memory allocation fails prints an error and exit program
 * @param v1 The value of the node
 * @return node* Pointer to the new node
 */
node* create_node(int v1){
    node* new_node = (node*)malloc(sizeof(node)); // dynamic allocation for the new node
    if (!new_node) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE); // critical error
    }

    (*new_node).value1 = v1; // (*...) dereference
    (*new_node).next = NULL;
    return new_node;
}

/**
 * @brief Create a new node
 * @details Dynamically allocates memory for a new node,
 * initialize the argument and the pointer to NULL.
 * Time complexity: O(1)
 * @warning If memory allocation fails prints an error and exit program
 * @return node* Pointer to the new node
 */
node* create_empty_node(){
    return create_node(DEFAULT_VALUE);
}


/**
 * @brief Create a new linked list
 * @details Dynamically allocates memory for each node of the list,
 * for each node initialize the value to the argument and the pointer to NULL.
 * Time complexity: O(n), n = number of nodes in the list
 * @warning If memory allocation fails prints an error and exit program
 * @param values Array of values to initialize the linked list
 * @param length Number of elements in the values array
 * @return node* Pointer to the head of the linked list.
 * If the argument is NULL or the length is zero returns NULL
 */
node* create_list(int values[], unsigned int length) {
    if (length == 0 || values == NULL) return NULL;

    node* head = create_node(values[0]);
    node* temp = head;
    for (unsigned int i = 1; i < length; i++){
        node* n = create_node(values[i]);
        (*temp).next = n;
        temp = n;
    }
    return head;
}


/**
 * @brief Prints the values of each node of the linked list
 * @details Time complexity: O(n), n = number of nodes in the list
 * @param head Pointer to the head of the linked list
 * @return void Doesn't return a value
 */
void print_list(node* head){
    if (!head) return;

    node* temp = head;
    printf("[");
    while((*temp).next) {
        printf("%d, ", (*temp).value1);
        temp = (*temp).next;
    }
    printf("%d]", (*temp).value1);
}


/**
 * @brief Frees the memory allocated for a linked list
 * @details Deallocates each node's memory of a linked list.
 * Time complexity: O(n), n = number of nodes in the list
 * @param head Pointer to the head of the list
 * @return void Doesn't return a value
 */
void clear_list(node* head){
    if (!head) return;

    node* temp;
    while(head) {
        temp = head;
        head = (*head).next;
        free(temp); // deallocate memory
    }

    // alternative:
    // clear_list((*head).next);
    // free(head);
}


/**
 * @brief Insert a node at the head of a linked list
 * @details Time complexity: O(1)
 * @param head Pointer to the current head of the linked list
 * @param n Pointer to the node to be inserted at the head
 * @return node* Pointer to the new head of the linked list
 */
node* insertion_head_node(node* head, node* n){
    if (!head && !n) return NULL;
    if (!head) return n;
    if (!n) return head;

    (*n).next = head;
    return n;
}


/**
 * @brief Insert a node at the end of a linked list
 * @details Time complexity: O(n), n = number of nodes in the list
 * @param head Pointer to the head of the linked list
 * @param n Pointer to the node to be inserted at the end
 * @return node* Pointer to the head of the modified linked list
 */
node* insertion_end_node(node* head, node* n){
    if (!head && !n) return NULL;
    if (!head) return n;
    if (!n) return head;

    node* temp = head;
    while((*temp).next) temp = (*temp).next;
    (*temp).next = n;
    return head;
}


/**
 * @brief Insert a node after another node of a linked list
 * @details Time complexity: O(n), n = number of nodes seen in the list
 * @param head Pointer to the head of the linked list
 * @param n Pointer to the node after which the new node will be inserted of the linked list
 * @param after_n Pointer to the node to be inserted after the other node
 * @return node* Pointer to the head of the modified linked list
 */
node* insertion_after_node(node* head, node* n, node* after_n){
    if (!head && !after_n) return NULL;
    if (!head) return after_n;
    if (!after_n || !n) return head;

    node* temp = head;
    while(temp && temp != n) temp = (*temp).next;
    if (!temp) return head;

    (*after_n).next = (*temp).next;
    (*temp).next = after_n;    
    return head;
}


/**
 * @brief Insert a node before another node of a linked list
 * @details Time complexity: O(n), n = number of nodes seen in the list
 * @param head Pointer to the head of the linked list
 * @param n Pointer to the node before which the new node will be inserted of the linked list
 * @param before_n Pointer to the node to be inserted before the other node
 * @return node* Pointer to the head of the modified linked list
 */
node* insertion_before_node(node* head, node* n, node* before_n){
    if (!head && !before_n) return NULL;
    if (!head) return before_n;
    if (!before_n || !n) return head;

    node* temp = head;
    while((*temp).next && (*temp).next != n) temp = (*temp).next;
    if (!(*temp).next) return head;

    (*before_n).next = (*temp).next;
    (*temp).next = before_n;
    return head;
}


/**
 * @brief Concatenates two linked lists
 * @details Appends the second linked list to the end of the first linked list.
 * Time complexity: O(n), n = number of nodes in the first list
 * @param head1 Pointer to the head of the first linked list
 * @param head2 Pointer to the head of the second linked list
 * @return node* Pointer to the head of the concatenated linked list.
 * If both lists are empty, returns NULL
 */
node* concatenate_lists(node* head1, node* head2){
    if(!head1 && !head2) return NULL;
    if(!head1) return head2;
    if(!head2) return head1;

    return insertion_end_node(head1, head2);
}


/**
 * @brief Splits a linked list in two linked list at a specified node
 * @details The first part includes all nodes up to and including the specified node, and the second part includes all nodes after it.
 * Time complexity: O(n), n = number of nodes before the specified node
 * @param head Pointer to the head of the linked list.
 * @param n Pointer to the node at which the list will be split.
 * @return tuple Contains the pointer to the head of the first part of the list and 
 * the pointer to the head of the second part of the list.
 * If the specified node is not found, the second part will be NULL.
 */
tuple split_list_at_node(node* head, node* n){
    tuple result = {head, NULL};

    if (!head) return result;

    if (n == head){
        result.node2 = (*head).next;
        (*head).next = NULL;
        return result;
    }

    node* temp = head;
    while(temp && temp != n) temp = (*temp).next;
    if (!temp) return result; // n not found

    result.node2 = (*temp).next;
    (*temp).next = NULL;
    return result;
}

/**
 * @brief Splits a linked list in two linked list at a specified value
 * @details The first part includes all nodes up to and including the node with the specified value, and the second part includes all nodes after it.
 * Time complexity: O(n), n = number of nodes before the specified value
 * @param head Pointer to the head of the linked list.
 * @param value Value of the node at which the list will be split.
 * @return tuple Contains the pointer to the head of the first part of the list and 
 * the pointer to the head of the second part of the list.
 * If the specified value is not found, the second part will be NULL.
 */
tuple split_list_at_value(node* head, int value){
    tuple result = {head, NULL};

    if (!head) return result;

    if ((*head).value1 == value){
        result.node2 = (*head).next;
        (*head).next = NULL;
        return result;
    }

    node* temp = head;
    while(temp && (*temp).value1 != value) temp = (*temp).next;
    if (!temp) return result; // n not found

    result.node2 = (*temp).next;
    (*temp).next = NULL;
    return result;
}


/**
 * @brief Remove a node of a linked list
 * @details Time complexity: O(n), n = number of nodes seen in the list
 * @param head Pointer to the head of the linked list
 * @param n Pointer to the node to be removed from the linked list
 * @return tuple Contains the pointer to the head of the modified linked list
 * and the pointer to the removed node
 */
tuple remove_node(node* head, node* n){
    tuple result = {head, NULL};
    
    if (!head || !n) return result;

    if (n == head){
        result.node1 = (*head).next;
        (*n).next = NULL;
        result.node2 = n;
        return result;
    }

    node* temp = head;
    while((*temp).next && (*temp).next != n) temp = (*temp).next;
    if (!(*temp).next) return result; // n not found

    (*temp).next = (*n).next;
    (*n).next = NULL;
    result.node2 = n;
    return result;
}

/**
 * @brief Remove the first node of the linked list with the value equals to the argument
 * @details Time complexity: O(n), n = number of nodes seen in the list
 * @param head Pointer to the head of the linked list
 * @param value The value of the node to be removed from the linked list
 * @return tuple Contains the pointer to the head of the modified linked list
 * and the pointer to the removed node
 */
tuple remove_node_with_value(node* head, int value){
    tuple result = {head, NULL};
    
    if (!head) return result;

    if ((*head).value1 == value){
        result.node1 = (*head).next;
        (*head).next = NULL;
        result.node2 = head;
        return result;
    }

    node* temp = head;
    while((*temp).next && (*(*temp).next).value1 != value) temp = (*temp).next;
    if (!(*temp).next) return result; // n not found

    result.node2 = (*temp).next;
    (*temp).next = (*(*temp).next).next;
    (*result.node2).next = NULL;
    return result;
}


/**
 * @brief Changes the value of a node in a linked list
 * @details Time complexity: O(n), n = number of nodes seen in the list
 * @param head Pointer to the head of the linked list
 * @param n Pointer to the node whose value is to be changed
 * @param new_value The new value to be assigned to the node
 * @return node* Pointer to the head of the linked list.
 * If the list is empty, returns NULL
 */
node* change_node_value(node* head, node* n, int new_value){
    if (!head) return NULL;
    if (!n) return head;

    node* temp = head;
    while(temp){
        if (temp == n){
            (*temp).value1 = new_value;
            return head;
        }
        temp = (*temp).next;
    }
    return head;
}

/**
 * @brief Changes the value of a node in a linked list
 * @details Time complexity: O(n), n = number of nodes seen in the list
 * @param head Pointer to the head of the linked list
 * @param value The value of the node to be changed
 * @param new_value The new value to be assigned to the node
 * @return node* Pointer to the head of the linked list.
 * If the list is empty, returns NULL
 */
node* change_node_value_with_value(node* head, int value, int new_value){
    if (!head) return NULL;

    node* temp = head;
    while(temp){
        if ((*temp).value1 == value){
            (*temp).value1 = new_value;
            return head;
        }
        temp = (*temp).next;
    }
    return head;
}


/**
 * @brief Checks if a linked list is empty
 * @details Time complexity: O(1)
 * @param head Pointer to the head of the linked list
 * @return int Returns 1 if the list is empty, otherwise returns 0
 */
int is_empty_list(node* head){
    if(!head) return 1;
    return 0;
}


/**
 * @brief Searches for a node in a linked list
 * @details Time complexity: O(n), n = number of nodes seen in the list
 * @param head Pointer to the head of the linked list
 * @param n Pointer to the node to be searched for in the list
 * @return tuple Contains the pointer to the head of the list and the pointer to the found node.
 * If the node is not found, the second element of the tuple is NULL.
 */
tuple node_in_list(node* head, node* n){
    tuple result = {head, NULL};

    if(!head || !n) return result;

    node* temp = head;
    while(temp){
        if (temp == n){
            (*n).next = NULL;
            result.node2 = n;
            return result;
        }
        temp = (*temp).next;
    }
    return result;
}

/**
 * @brief Searches for a value in a linked list
 * @details Time complexity: O(n), n = number of nodes seen in the list
 * @param head Pointer to the head of the linked list
 * @param value Value to be searched for in the list
 * @return tuple Contains the pointer to the head of the list and the pointer to the node with the searched value.
 * If the value is not found, the second element of the tuple is NULL
 */
tuple value_in_list(node* head, int value){
    tuple result = {head, NULL};

    if(!head) return result;

    node* temp = head;
    while(temp){
        if ((*temp).value1 == value){
            result.node2 = temp;
            return result;
        }
        temp = (*temp).next;
    }
    return result;
}


/**
 * @brief Reverses a linked list
 * @details Time complexity: O(n), n = number of nodes in the list
 * @param head Pointer to the head of the linked list
 * @return node* Pointer to the new head of the reversed list
 * If the list is empty returns NULL
 */
node* reverse_list(node* head){
    if (!head) return NULL;

    node* prev = NULL;
    node* current = head;
    node* next = NULL;
    while(current){
        next = (*current).next;
        (*current).next = prev;
        prev = current;
        current = next;
    }
    return prev;
}


/**
 * @brief Length of a linked list
 * @details Time complexity: O(n), n = number of nodes in the list
 * @param head Pointer to the head of the linked list
 * @return int The length of the linked list
 */
int list_length(node* head){
    int length = 0;
    node* temp = head;
    while(temp){
        temp = (*temp).next;
        length ++;
    }
    return length;
}


/**
 * @brief Max value of a linked list
 * @details Time complexity: O(n), n = number of nodes in the list
 * @param head Pointer to the head of the linked list
 * @return int The max value of the linked list.
 * If the list is empty return the default value of a node
 */
int max_list(node* head){
    if (!head) return DEFAULT_VALUE;

    node* temp = head;
    int max = (*head).value1;
    while(temp){
        if((*temp).value1 > max) max = (*temp).value1;
        temp = (*temp).next;
    }
    return max;
}

/**
 * @brief Min value of a linked list
 * @details Time complexity: O(n), n = number of nodes in the list
 * @param head Pointer to the head of the linked list
 * @return int The min value of the linked list.
 * If the list is empty return the default value of a node
 */
int min_list(node* head){
    if (!head) return DEFAULT_VALUE;

    node* temp = head;
    int min = (*head).value1;
    while(temp){
        if((*temp).value1 < min) min = (*temp).value1;
        temp = (*temp).next;
    }
    return min;
}


/**
 * @brief Counts the frequency of a value in the linked list
 * @details Time complexity: O(n), n = number of nodes in the list
 * @param head Pointer to the head of the linked list
 * @return int The value to count the frequency of in the linked list
 */
int count_frequents_in_list(node* head, int value){
    if (!head) return 0;

    int freq = 0;
    node* temp = head;
    while(temp){
        if((*temp).value1 == value) freq ++;
        temp = (*temp).next;
    }
    return freq;
}


/**
 * @brief Sorts a linked list
 * @details Uses the quicksort algorithm for sorting the list.
 * (algorithm: https://www.geeksforgeeks.org/quick-sort-algorithm).
 * Time complexity: O(n log n), n = number of nodes in the list
 * @param head Pointer to the head of the linked list
 * @return node* Pointer to the head of the sorted linked list
 */
node* sort_list(node* head){
    if (!head || !(*head).next) return head; // base case

    int pivot = (*head).value1;
    node* left = NULL;
    node* middle = NULL;
    node* right = NULL;
    node* temp = head;

    while(temp){
        node* next = (*temp).next;
        (*temp).next = NULL;

        if ((*temp).value1 < pivot) left = insertion_head_node(left, temp);
        else if ((*temp).value1 == pivot) middle = insertion_head_node(middle, temp);
            else right = insertion_head_node(right, temp);

        temp = next;
    }
    left = sort_list(left);
    right = sort_list(right);
    middle = insertion_end_node(middle, right);
    return insertion_end_node(left, middle);
}


/**
 * @brief Extracts the values from a linked list into an array
 * @details Time complexity: O(n), n = number of nodes in the list
 * @param head Pointer to the head of the linked list
 * @return int* Pointer to an array containing the values of the linked list nodes.
 * If the list is empty, returns NULL.
 * If memory allocation fails, the program exits with an error
 */
int* list_values(node* head){
    if (!head) return NULL;

    int length = list_length(head);
    int* values = (int*)malloc(length * sizeof(int)); // dynamic allocation for the values
    if (!values) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE); // critical error
    }

    node* temp = head;
    int index = 0;
    while(temp){
        values[index++] = (*temp).value1;
        temp = (*temp).next;
    }
    return values;

    // print values:
    // for (int i = 0; i < length; i++) printf("%d ", values[i]);
}




// :::::::::::::::::::::::::::::::::::::::::::::::::::::: TESTS ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/**
 * @brief Entry point of the program, used for testing
 * @return 0 on successful execution
 */
int main(){
    return 0;

    /* compiling: gcc linkedList.c -o linkedList
    executing: linkedList */
}