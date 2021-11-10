#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "resistor.h"
#include "board.h"

extern resistor *head;
extern int total_resistors;

// Checks if resistor can be placed on given row, it can't be placed between or over existing resistor
bool test_placement_on_board(resistor *head, int column, int row){
    resistor *temp_res;
    for(int i = 0; i < MAX_COLUMNS; i++){
        if(find_resistor(i, row)){
            temp_res = find_resistor(i, row);
            int found_column = temp_res->starting_column;
            for(int u = 0; u < temp_res->length; u++){
                if(found_column == column){
                    return true;
                }
                found_column++;
            }
        }
    }
    return false;
}
// Finds all resistors that is connected to a given column, adds that to result_list and returns number of resistors at the column
int find_resistors_to_and_from_column(int column, resistor *result_list[]){
    resistor *temp_res = head;
    int index = 0;
    while(temp_res != NULL){
        if (temp_res->starting_column == column){
            result_list[index] = temp_res;
            index++;
        }
        if (temp_res->ending_column == column){
            result_list[index] = temp_res;
            index++;
        }
        temp_res = temp_res->next;
    }
    return index;
}
// Remakes result_list to a list with columns to visit next
void columns_to_visit(resistor *resistors[], int number_of_resistors, int to_visit[], int source_column){
    for (int i = 0; i < number_of_resistors; i++) {
        resistor *a_resistor = resistors[i];
        if (a_resistor->starting_column == source_column) {
            to_visit[i] = a_resistor->ending_column;
        }
        if (a_resistor->ending_column == source_column) {
            to_visit[i] = a_resistor->starting_column;
        }
    }
}
// Adds all colums that is connected with given column to visited_array and marks it with 1
void find_connections(int column, int visited_array[]){
    visited_array[column] = 1;
    
    resistor *search_result[total_resistors];
    int number_of_resistors = find_resistors_to_and_from_column(column, &search_result[0]);
    int to_visit[total_resistors];
    columns_to_visit(search_result, number_of_resistors, to_visit, column);
    
    for (int column_index = 0; column_index < number_of_resistors; column_index++) {
        int column_to_visit = to_visit[column_index];
        if (visited_array[column_to_visit] == 0) {
            find_connections(column_to_visit, visited_array);
        }
    }
}
// Draws a matrix with size of MAX_COLUMN and MAX_ROW, and adds - as markings of the resistors on the board/matrix
void print_board(){
    resistor *temp_res;
    printf("\n\n");
    for(int i = 0; i < MAX_COLUMNS; i++){
        printf("%d\t", i+1);
    }
    printf("\n");
    for(int i = 0; i < MAX_ROWS; i++){
        printf("\n");
        for(int column = 0; column < MAX_COLUMNS; column++){
            if(find_resistor(column, i)){
                temp_res = find_resistor(column, i);
                for(int i = 0;i < temp_res->length; column++, i++){
                    printf("-\t");
                }
                column--;
            }
            else
                printf("*\t");
        }
    }
    printf("\n");
}