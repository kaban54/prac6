CFLAGS += -O2 -mavx2
CC = g++
OBJDIR = obj/
SRCDIR = src/

all: funcstest speedtest

funcstest: obj/funcstest.o obj/hashtable.o obj/hashfuncs.o
	$(CC) obj/funcstest.o obj/hashtable.o obj/hashfuncs.o -o $@

speedtest: obj/speedtest.o obj/hashtable.o obj/hashfuncs.o
	$(CC) obj/speedtest.o obj/hashtable.o obj/hashfuncs.o -o $@

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CC) -c $(CFLAGS) $< -o $@


clean:
	rm obj/*.o -f
	clear
	
.PHONY: clean