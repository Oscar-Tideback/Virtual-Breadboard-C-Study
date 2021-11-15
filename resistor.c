#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"
#include "resistor.h"

extern resistor *head;
extern int total_resistors;

// Creates resistor and adds at list head
void create_new_resistor(int length, int column, int row){
    resistor *temp_res = malloc(sizeof(resistor));      // Allocate memory for resistor, don't forget to free
    temp_res->length = length;
    temp_res->starting_column = column;
    temp_res->ending_column = column + length - 1;
    temp_res->row = row;
    temp_res->next = head;    
    head = temp_res;
    total_resistors++;
}
// Finds a resistor at given place and returns it
resistor *find_resistor(int column, int row){
    resistor *temp_res = head;
    while(temp_res != NULL){
        if(temp_res->row == row && temp_res->starting_column == column){
            return temp_res;
        }
        temp_res = temp_res->next;
    }
    return NULL;
}
// Finds a specific resistor and returns it's place in the list
int find_resistor_in_link(int column, int row){
    int counter = 0;
    resistor *temp_res = head;
    while(temp_res != NULL){
        counter++;
        if(temp_res->row == row && temp_res->starting_column == column){
            return counter;
        }
        temp_res = temp_res->next;
    }
    return -1;
}
// Removes a specific resistor form the list at given place
void remove_resistor(resistor **head, int resistor_to_remove){
    resistor *prev_res = *head, *current_res = *head;
    if(*head == NULL){
        printf("Resistorlist is empty, please add resistor before removing one.");
    }
    else if(resistor_to_remove == 1){       // Remove if posision to remove is at head
        *head = current_res->next;
        free(current_res);                  // Return memmory allocation
        current_res = NULL;
    }
    else{                                   // Remove if posision to remove is in list
        while(resistor_to_remove != 1){
            prev_res = current_res;
            current_res = current_res->next;
            resistor_to_remove--;
        }
        prev_res->next = current_res->next;
        free(current_res);                  // Return memmory allocation
        current_res = NULL;
    }
}

int total_res_length(resistor *head){
    resistor *temp_res = head;
    int total_length = 0;
       while(temp_res != NULL){
            total_length = total_length + temp_res->length;
            temp_res = temp_res->next;
       }
       return total_length;
}