#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct _table Table;

void create_table();

void list_tables();

void create_new_line_in_table();

void list_data_of_one_table();

void delete_line_in_table();

void delete_table();

void setup();

void menu();

void call_menu();
