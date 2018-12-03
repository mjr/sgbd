#include "sgbd.h"

#define CREATE_TABLE 1
#define LIST_TABLES 2
#define CREATE_NEW_LINE_IN_TABLE 3
#define LIST_DATA_OF_ONE_TABLE 4
#define SEARCH_VALUE_IN_TABLE 5
#define DELETE_VALUE_OF_ONE_TABLE 6
#define DELETE_TABLE 7
#define EXIT 0

#define FILE_TABLES "tables.txt"
#define FILE_TEMP "temp.txt"
#define PATH_DATA "data/"
#define BUFFER_SIZE 155

struct _table {
    char name[BUFFER_SIZE];
};

int table_exists(char *name_table, int check_table) {
    char *line = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *default_path = (char *) malloc(BUFFER_SIZE * sizeof(char));
    strcpy(default_path, PATH_DATA);
    strcat(default_path, FILE_TABLES);

    FILE *file_tables = fopen(default_path, "r");
    if (file_tables == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo %s\n", FILE_TABLES);
        return -1;
    }

    int total_read = 0;
    while (fgets(line, BUFFER_SIZE, file_tables) != NULL) {
        total_read = strlen(line);
        line[total_read - 1] = line[total_read - 1] == '\n' ? '\0' : line[total_read - 1];
        if (strcmp(line, name_table) == 0) {
            if (check_table == 0) {
                fprintf(stderr, "Já existe uma tabela | %s | no sistema!!!\n", name_table);
                printf("Digite outro nome para a tabela\n");
            }
            fclose(file_tables);
            return 0;
        }
    }

    file_tables = fopen(default_path, "a+");
    fprintf(file_tables, "%s\n", name_table);
    fclose(file_tables);

    if (check_table == 2) {
        fprintf(stderr, "Não existe uma tabela | %s | no sistema!!!\n", name_table);
        printf("Digite o nome de uma tabela existente!\n");
    }

    free(line);
    free(default_path);

    return 1;
}

int check_column(char *column) {
    return 0;
}

int check_value_of_column(char *column, char* value) {
    return 0;
}

void str_table(char *table) {
    char *path = (char *) malloc(BUFFER_SIZE * sizeof(char));
    strcat(path, PATH_DATA);
    strcat(path, table);
    strcat(path, ".txt");

    FILE *file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "Não foi possível abrir o arquivo %s\n", path);
    }

    char *line = (char *) malloc(BUFFER_SIZE * sizeof(char));
    while (fgets(line, BUFFER_SIZE, file) != NULL) {
        char **res = NULL;
        char *point = strtok(line, " ");
        int spaces = 0;

        while (point) {
            res = realloc(res, sizeof(char*) * ++spaces);

            if (res == NULL) {
                exit(EXIT_FAILURE);
            }

            res[spaces - 1] = point;

            point = strtok(NULL, " ");
        }

        res = realloc(res, sizeof(char*) * (spaces + 1));
        res[spaces] = 0;

        if (strcmp(res[0], "pk") == 0) {
            printf("| %s ", res[1]);
        } else {
            printf("| %s ", res[0]);
        }

        free(res);
        free(point);
    }

    printf("|\n");

    fclose(file);

    free(path);
    free(line);
}

void create_table() {
    printf("| CRIAR TABELA |\n");
    printf("--------------------\n");
    printf("DIGITE O NOME DA TABELA:\n");
    char *name = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *default_path = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *default_path_data = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *name_concat = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *name_data_concat = (char *) malloc(BUFFER_SIZE * sizeof(char));

    do {
        scanf("%s", name);
    } while (table_exists(name, 0) == 0);

    strcat(name_concat, name);
    strcat(name_concat, ".txt");

    strcat(name_data_concat, name);
    strcat(name_data_concat, "_data.txt");

    strcpy(default_path, PATH_DATA);
    strcat(default_path, name_concat);

    strcpy(default_path_data, PATH_DATA);
    strcat(default_path_data, name_data_concat);


    FILE *table_data = fopen(default_path_data, "w");
    fclose(table_data);

    FILE *table = fopen(default_path, "w");

    char *field = (char *) malloc(BUFFER_SIZE * sizeof(char));
    printf("DIGITE AS COLUNAS DA TABELA:\n");
    printf("UTILIZE O FORMATO DESCRITO ABAIXO.\n");
    printf("tipo_de_dado nome_da_coluna\n");
    printf("PARA DEFINIR COMO CHAVE PRIMÁRIA ADICIONE NO INICIO pk.\n");
    printf("pk tipo_de_dado nome_da_coluna\n");
    printf("DIGITE 0 QUANDO NÃO QUISER ADICIONAR MAIS COLUNAS.\n");
    printf("--------------------\n");
    while (strcmp("0\n", field) != 0) {
        fgets(field, BUFFER_SIZE, stdin);
        if (strcmp("0\n", field) != 0 && strcmp("\n", field) != 0) {
            fprintf(table, "%s", field);
        }
    }

    fclose(table);

    free(name);
    free(default_path);
    free(default_path_data);
    free(name_concat);
    free(name_data_concat);
    free(field);

    call_menu();
}

void list_tables() {
    printf("| TABELAS |\n");
    printf("--------------------\n");
    char *line = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *default_path = (char *) malloc(BUFFER_SIZE * sizeof(char));

    strcpy(default_path, PATH_DATA);
    strcat(default_path, FILE_TABLES);

    FILE *file_tables = fopen(default_path, "r");
    if (file_tables == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo %s\n", FILE_TABLES);
    }

    Table table = {};
    while (fgets(line, BUFFER_SIZE, file_tables) != NULL) {
        strcpy(table.name, line);
        printf("%s", table.name);
    }

    fclose(file_tables);

    free(line);
    free(default_path);

    call_menu();
}

void create_new_line_in_table() {
    printf("| ADICIONAR DADOS NA TABELA |\n");
    printf("--------------------\n");
    printf("DIGITE O NOME DA TABELA:\n");
    char *name = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *name_concat = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *default_path = (char *) malloc(BUFFER_SIZE * sizeof(char));

    do {
        scanf("%s", name);
    } while (table_exists(name, 2) != 0);

    strcat(name_concat, name);
    strcat(name_concat, "_data.txt");

    strcpy(default_path, PATH_DATA);
    strcat(default_path, name_concat);

    FILE *table = fopen(default_path, "a+");

    char *field = (char *) malloc(BUFFER_SIZE * sizeof(char));

    printf("DIGITE AS DADOS:\n");
    str_table(name);
    printf("UTILIZE O FORMATO DESCRITO ABAIXO.\n");
    printf("chave_primaria valor_da_coluna valor_da_coluna valor_da_coluna\n");
    printf("DIGITE 0 QUANDO NÃO QUISER ADICIONAR MAIS DADOS.\n");
    printf("--------------------\n");
    while (strcmp("0\n", field) != 0) {
        fgets(field, BUFFER_SIZE, stdin);
        if (strcmp("0\n", field) != 0 && strcmp("\n", field) != 0) {
            fprintf(table, "%s", field);
        }
    }

    fclose(table);

    free(name);
    free(name_concat);
    free(default_path);
    free(field);

    call_menu();
}

void list_data_of_one_table() {
    printf("| DADOS DA TABELA |\n");
    printf("--------------------\n");
    printf("DIGITE O NOME DA TABELA:\n");
    char *line = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *name = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *name_concat = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *default_path = (char *) malloc(BUFFER_SIZE * sizeof(char));

    do {
        scanf("%s", name);
    } while (table_exists(name, 1) != 0);

    strcat(name_concat, name);
    strcat(name_concat, "_data.txt");

    strcpy(default_path, PATH_DATA);
    strcat(default_path, name_concat);

    FILE *file_tables = fopen(default_path, "r");
    if (file_tables == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo %s\n", FILE_TABLES);
    }

    while (fgets(line, BUFFER_SIZE, file_tables) != NULL) {
        printf("%s", line);
    }

    fclose(file_tables);

    free(line);
    free(name);
    free(name_concat);
    free(default_path);

    call_menu();
}

void remove_line_from_file(char *table) {
    FILE *file, *file_temporary;
    char *default_path = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *line = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *temporary = (char *) malloc(BUFFER_SIZE * sizeof(char));

    strcat(temporary, PATH_DATA);
    strcat(temporary, FILE_TEMP);

    strcat(table, "\n");
    strcpy(default_path, PATH_DATA);
    strcat(default_path, FILE_TABLES);

    file = fopen(default_path, "r");
    if (!file) {
        fprintf(stderr, "Não foi possível abrir o arquivo %s\n", default_path);
    }

    file_temporary = fopen(temporary, "w");
    if (!file_temporary) {
        fprintf(stderr, "Não foi possível abrir o arquivo %s\n", temporary);
        fclose(file);
    }

    while (!feof(file)) {
        strcpy(line, "\0");
        fgets(line, BUFFER_SIZE, file);

        if (!feof(file)) {
          if (strcmp(line, table) != 0) {
              fprintf(file_temporary, "%s", line);
          }
        }
    }

    fclose(file);
    fclose(file_temporary);

    remove(default_path);
    rename(temporary, default_path);

    free(default_path);
    free(line);
}

void remove_line_from_file_by_pk(unsigned int pk, char *path_table) {
    FILE *file, *file_temporary;
    char *line = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *line_full = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *temporary = (char *) malloc(BUFFER_SIZE * sizeof(char));
    unsigned int pk_temp;

    strcat(temporary, PATH_DATA);
    strcat(temporary, FILE_TEMP);

    file = fopen(path_table, "r");
    if (!file) {
        fprintf(stderr, "Não foi possível abrir o arquivo %s\n", path_table);
    }
    file_temporary = fopen(temporary, "w");
    if (!file_temporary) {
        fprintf(stderr, "Não foi possível abrir o arquivo %s\n", temporary);
        fclose(file);
    }

    char *first_column = NULL;
    while (!feof(file)) {
        fgets(line, BUFFER_SIZE, file);
        if (!feof(file)) {
          strcpy(line_full, line);
          // const char deli[] = "[";
          first_column = strtok(line, " ");
          pk_temp = atoi(first_column);

          if (pk_temp != pk) {
              fprintf(file_temporary, "%s", line_full);
          }
        }
    }
    fclose(file);
    fclose(file_temporary);

    remove(path_table);
    rename(temporary, path_table);

    free(line);
    free(line_full);
    free(first_column);
}

void delete_table() {
    printf("| APAGAR TABELA |\n");
    printf("--------------------\n");
    printf("DIGITE O NOME DA TABELA:\n");
    char *name = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *name_concat = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *name_concat_data = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *default_path = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *default_path_data = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *name_default = (char *) malloc(BUFFER_SIZE * sizeof(char));

    do {
        scanf("%s", name);
    } while (table_exists(name, 1) != 0);

    strcpy(name_default, name);

    strcat(name_concat, name);
    strcat(name_concat, ".txt");

    strcat(name_concat_data, name_default);
    strcat(name_concat_data, "_data.txt");

    strcpy(default_path, PATH_DATA);
    strcpy(default_path_data, PATH_DATA);

    strcat(default_path, name_concat);
    strcat(default_path_data, name_concat_data);

    remove_line_from_file(name_default);

    // int info_delete, info_delete_data;
    remove(default_path);
    remove(default_path_data);

    free(name);
    free(name_concat);
    free(name_concat_data);
    free(default_path);
    free(default_path_data);
    free(name_default);
    // if (info_delete == 0) {
    //   printf("File deleted successfully\n");
    // } else {
    //   printf("Error: unable to delete the file\n");
    // }
    //
    // if (info_delete_data == 0) {
    //   printf("File data deleted successfully\n");
    // } else {
    //   printf("Error: unable to delete the file data\n");
    // }
    call_menu();
}

void delete_line_in_table() {
    printf("| APAGAR DADOS DA TABELA |\n");
    printf("--------------------\n");
    printf("DIGITE O NOME DA TABELA:\n");
    char *name = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *name_concat_data = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *default_path_data = (char *) malloc(BUFFER_SIZE * sizeof(char));
    unsigned int pk;

    do {
        scanf("%s", name);
    } while (table_exists(name, 1) != 0);

    strcat(name_concat_data, name);
    strcat(name_concat_data, "_data.txt");

    strcpy(default_path_data, PATH_DATA);
    strcat(default_path_data, name_concat_data);

    printf("DIGITE O VALOR DA CHAVE PRIMÁRIA:\n");
    scanf("%d", &pk);

    remove_line_from_file_by_pk(pk, default_path_data);

    free(name);
    free(name_concat_data);
    free(default_path_data);
}

void setup() {
    struct stat sb;

    if (stat(PATH_DATA, &sb) == 0 && S_ISDIR(sb.st_mode)) {
        // printf("Pasta já existe!!!\n");
    } else {
        mkdir(PATH_DATA, 0700);
    }

    char *default_path = malloc(BUFFER_SIZE);

    strcpy(default_path, PATH_DATA);
    strcat(default_path, FILE_TABLES);

    FILE *file_tables = fopen(default_path, "a+");
    fclose(file_tables);
}

void menu() {
    unsigned int OPTION;

    system("clear");
    printf("|    SGBD Simplificado   |\n");
    printf("ESCOLHA UMA DAS OPÇÕES\n");
    printf("1 - CRIAR TABELA\n");
    printf("2 - LISTAR TABELAS\n");
    printf("3 - ADICIONAR DADOS NA TABELA\n");
    printf("4 - LISTAR DADOS DA TABELA\n");
    printf("5 - PESQUISAR VALOR DA TABELA\n");
    printf("6 - APAGAR DADOS DA TABELA\n");
    printf("7 - APAGAR TABELA\n");
    printf("0 - SAIR\n");
    scanf("%d", &OPTION);
    switch (OPTION) {
        case CREATE_TABLE:
            create_table();
            break;
        case LIST_TABLES:
            list_tables();
            break;
        case CREATE_NEW_LINE_IN_TABLE:
            create_new_line_in_table();
            break;
        case LIST_DATA_OF_ONE_TABLE:
            list_data_of_one_table();
            break;
        case SEARCH_VALUE_IN_TABLE:
            printf("Em breve!!!\n");
            break;
        case DELETE_VALUE_OF_ONE_TABLE:
            delete_line_in_table();
            break;
        case DELETE_TABLE:
            delete_table();
            break;
        case EXIT:
            exit(EXIT_SUCCESS);
            break;
        default:
            exit(EXIT_FAILURE);
    }
}

void call_menu() {
    while('\n' != getchar());
    printf("Pressione enter para continuar...");
    getchar();
    menu();
}
