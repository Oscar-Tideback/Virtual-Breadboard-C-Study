#ifndef RESISTOR_H
#define RESISTOR_H

struct resistor_s {
    int length, starting_column, ending_column, row;
    struct resistor_s* next;
};
typedef struct resistor_s resistor;

void create_new_resistor(int length, int column, int row);
resistor *find_resistor(int column, int row);
int find_resistor_in_link(int column, int row);
void remove_resistor(resistor **head, int resistor_to_remove);
int total_res_length(resistor *head);
#endif 
