CC = clang
STD = -std=c11
POSIX = -D_POSIX_C_SOURCE=200809L

INC_DIR = misc
OBJ_DIR = objs
SRC = src
OPENSSL=-L/usr/local/lib/ -lssl -lcrypto
EXE = launch

CFLAGS = -I$(INC_DIR) $(POSIX)

DFLAGS = -I$(INC_DIR) -Wall -Wextra -Werror -Weverything -Wshadow -Wwrite-strings $(POSIX)

OBJS = $(OBJ_DIR)/misc.o
OBJ_SRC = $(DAY).o

start: $(OBJ_DIR)
build: $(DAY)
	@if [ -a $(OBJ_SRC) ]; then \
		rm $(OBJ_SRC); \
	fi
	@./launch

$(OBJ_DIR):
	mkdir -p objs/

$(DAY): $(OBJS) $(OBJ_SRC)

	$(CC) $(STD) $(CFLAGS) -o $(EXE) $^

$(OBJ_SRC):
	$(CC) $(STD) $(CFLAGS) -c $(SRC)/$(DAY).c -o $@

$(OBJ_DIR)/misc.o:
	$(CC) $(STD) $(CFLAGS) -c $(INC_DIR)/misc.c -o $@

debug: $(OBJS) $(OBJ_SRC)
	$(CC) $(STD) $(DFLAGS) -o $(EXE) $^
	./$(EXE)

openssl: $(OBJS) $(OBJ_SRC)
	$(CC) $(STD) $(OPENSSL) $(CFLAGS) -o $(DAY) $^

openssl_debug: $(OBJS)
	$(CC) $(STD) $(OPENSSL) $(DFLAGS) -o $(DAY) $^

valgrind:
	valgrind -s --max-stackframe=8388608 --show-leak-kinds=all --track-origins=yes --leak-check=full ./$(EXE)

valgrindTest: $(DAY)
	valgrind -s --max-stackframe=8388608 --show-leak-kinds=all --track-origins=yes --leak-check=full ./$(EXE)

cleanObjs:
	rm objs/*.o

cleanAll:
	rm objs/*.o *.o

cleanDay:
	rm *.o

.PHONY: cleanObjs cleanAll cleanDay
