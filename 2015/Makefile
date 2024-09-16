CC = clang -std=c99

CFLAGS = -Imisc -D_POSIX_C_SOURCE=200809L
# CFLAGS = -Imisc

DFLAGS = -Imisc -Wall -Wextra -Werror -Wpedantic -Wshadow -Wwrite-strings -D_POSIX_C_SOURCE=200809L
# DFLAGS = -Imisc -Wall -Wextra -Wpedantic -Wshadow -Wwrite-strings

IDIR = misc
ODIR = objs
SRC = src
OPENSSL=-L/usr/local/lib/ -lssl -lcrypto
EXE = launch

OBJS = $(ODIR)/misc.o
OSRC = $(DAY).o

start: $(ODIR)
build: $(DAY)
	@if [ -a $(OSRC) ]; then \
		rm $(OSRC); \
	fi
	@./launch

$(ODIR):
	mkdir -p objs/

$(DAY): $(OBJS) $(OSRC)

	$(CC) $(CFLAGS) -o $(EXE) $^

$(OSRC):
	$(CC) $(CFLAGS) -c $(SRC)/$(DAY).c -o $@

$(ODIR)/misc.o:
	$(CC) $(CFLAGS) -c $(IDIR)/misc.c -o $@

debug: $(OBJS) $(OSRC)
	$(CC) $(DFLAGS) -o $(EXE) $^
	./$(EXE)

openssl: $(OBJS) $(OSRC)
	$(CC) $(OPENSSL) $(CFLAGS) -o $(DAY) $^

openssl_debug: $(OBJS)
	$(CC) $(OPENSSL) $(DFLAGS) -o $(DAY) $^

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
