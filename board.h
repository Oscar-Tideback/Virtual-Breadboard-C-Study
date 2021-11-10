#ifndef BOARD_H
#define BOARD_H

#define MAX_COLUMNS 10
#define MAX_ROWS 10

#include <stdbool.h>
#include "resistor.h"

bool test_placement_on_board(resistor *head, int column, int row);
int find_resistors_to_and_from_column(int column, resistor *result_list[]);
void columns_to_visit(resistor *resistors[], int number_of_resistors, int to_visit[], int source_column);
void find_connections(int column, int visited_array[]);
void print_board();
#endif 




