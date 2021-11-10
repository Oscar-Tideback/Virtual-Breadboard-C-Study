#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "resistor.h"
#include "board.h"

resistor *head = NULL;
int visited_list[MAX_COLUMNS] = {0};
int counter;
int total_resistors = 0;

//Writing all the resistors of the linked list to the resistors.txt file
void write_file(char filename[], resistor *head){
    resistor *temp_res = head;  
    FILE* file;
    file = fopen (filename, "w");
    if (file == NULL){
        fprintf(stderr, "\nCouldn't open file'\n");
        exit (1);
    }
    while(temp_res!=NULL){
        fwrite(temp_res, sizeof(resistor), 1, file);
        temp_res = temp_res->next;
    } 
    fclose(file);
}
//Reading all the resistors of the file and returns a head*
resistor *read_file(char filename[]){   
    resistor *temp_res = (resistor *)malloc(sizeof(resistor));;
    resistor *head;
    resistor *last_res;
    last_res = NULL;
    head = NULL;
    
    FILE *file;
    file = fopen (filename, "r");
    if (file == NULL){
        fprintf(stderr, "\nCouldn't Open File'\n");
        exit (1);
    }
    while(fread(temp_res, sizeof(resistor), 1, file)){  
        if(head==NULL){
            head = last_res = (resistor *)malloc(sizeof(resistor));
        }
        else{
            last_res->next = (resistor *)malloc(sizeof(resistor));
            last_res = last_res->next;
        }
        last_res->length = temp_res->length;
        last_res->starting_column = temp_res->starting_column;
        last_res->ending_column = temp_res->ending_column;
        last_res->row = temp_res->row;
        last_res->next = NULL;         
    } 
    fclose(file);
    return head;
}
void add_resistor(){
    int length, column, row;
    printf("To place a resistor, choose column and row then length.\n\nColumn:");
    scanf("%d", &column);
    if(column >= MAX_COLUMNS){
        printf("You can't add resistor outside of board, board has %d columns. Try again.\n\n", MAX_COLUMNS);
        return;
    }
    printf("\nRow:");
    scanf("%d", &row);
    if(column >= MAX_ROWS){
        printf("You can't add resistor outside of board, board has %d rows. Try again.\n\n", MAX_ROWS);
        return;
    }
    printf("Finaly the length of the resistor.\nLength:");
    scanf("%d", &length);
    if((column + (length - 1)) >= MAX_ROWS){
        printf("You can't add resistor outside of board, board has %d rows. Try again.\n\n", MAX_ROWS);
        return;
    }
    for(int i = 0; i < length; i++){
        if(test_placement_on_board(head, column+i, row-1) == true){
            printf("Place on board is occupied try again.\n\n");
            return;
        }
    }
    create_new_resistor(length, (column - 1), (row - 1));
}
void remove_res(){
    int column, row;
    printf("Choose resistor to remove, start by choosing the column \nColumn:");
    scanf("%d", &column);
    printf("Finaly choose row \nRow:");
    scanf("%d", &row);
    int resistor_pos = find_resistor_in_link((column-1), (row - 1));// Om den inte går att tabort säg till.
    if(resistor_pos == -1){
        printf("No resistor to remove is found, try again.\n\n");
        return;
    }
    remove_resistor(&head, resistor_pos);
}
void check_connectivity(){
    int first_column, second_column;
    printf("Choose what colums to check for connectivity, start by choosing the first column \nFirst column:");
    scanf("%d", &first_column);
    printf("Finaly the second column \nSecond column:");
    scanf("%d", &second_column);
    first_column--;
    second_column--;
    int visited_array[MAX_COLUMNS];
    for (int i = 0; i < MAX_COLUMNS; i++){
        visited_array[i] = 0;
    }
    find_connections(first_column, visited_array);
    if(visited_array[second_column] == 1){
        printf("\nYeay! Column:%d and column:%d is connected\n", first_column, second_column);
    }
    else {
        printf("\nSorry, column:%d and column:%d is NOT connected\n", first_column, second_column);
    }
}
static void show_menu(){
    int choice;
    printf("\nWhat would you like to do?\n");
    printf("1: Add resistor to board\n");
    printf("2: Show board\n");
    printf("3: Remove resistor\n");
    printf("4: Check if connected\n");
    printf("5: Read saved board file\n");
    printf("6: Save this board to file\n");
    printf("7: Exit program\n");
    scanf("%d", &choice);
    getc(stdin);
    switch (choice) {
        case 1:
            add_resistor();
            break;
        case 2:
            print_board();
            break;
        case 3:
            remove_res();
            break;
        case 4:
            check_connectivity();
            break;      
        case 5:
            head = read_file("resistors.txt");
            break;
        case 6:
            write_file("resistors.txt", head);
            break;
        case 7:
            exit(0);
            break;
        default:
            printf("Invalid choice, try again\n");
    }
}
int main(int argc, const char * argv[]){
    // Lazy test
    /*
    create_new_resistor(2, 1, 3);

    create_new_resistor(3, 2, 4);

    create_new_resistor(5, 5, 5);

    create_new_resistor(4, 6, 8);

    create_new_resistor(5, 1, 7);

    create_new_resistor(3, 4, 2);

    create_new_resistor(6, 2, 2);
    */
    while(true){
        show_menu();
    }
    return 0;
}

