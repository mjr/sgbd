APPS = ./apps
BIN = ./bin
INCLUDE = ./include
LIB = ./lib
OBJ = ./obj
SRC = ./src
DATA = ./data

FLAGS = -O3 -Wall -std=c99
LIBS = -led -lm -L $(LIB)

all: libed app


libed: \
		$(OBJ)/sgbd.o
		ar -rcs $(LIB)/libed.a $(OBJ)/*.o


app: $(BIN)/main


$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
		gcc $(FLAGS) -c $< -I $(INCLUDE) -o $@


$(BIN)/%: $(APPS)/%.c
		gcc $(FLAGS) $< -I $(INCLUDE) $(LIBS) -o $@


run:
		$(BIN)/main


clean:
		rm $(OBJ)/*.o
		rm $(BIN)/*
		rm $(DATA)/*
