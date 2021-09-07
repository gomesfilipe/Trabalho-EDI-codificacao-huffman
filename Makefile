#comp:
#	gcc src/*.c client/main.c -o tp2

#run:
#	valgrind ./tp2

TARGET := tp2
LIBS := -lm
CFLAGS := -g -O3 -Wno-unused-result
#CFLAGS := -g -O3 
OBJDIR := obj/
SRCDIR := src/
INCLUDEDIR := include/
INCLUDE_PATHS := -Iinclude
CLI := client/main.c
CC := gcc

all: $(TARGET)

SRC = $(wildcard $(SRCDIR)*.c)
HEADERS = $(wildcard $(INCLUDEDIR)*.h)

CLIENT = $(OBJDIR)$(basename $(notdir $(CLI)))

OBJECTS := $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)
OBJECTS += $(CLIENT).o

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADERS)
	@ mkdir -p $(OBJDIR)
	$(CC) $(INCLUDE_PATHS) $(CFLAGS) -c -o $@ $<

$(CLIENT).o: $(CLI)
	$(CC) $(INCLUDE_PATHS) $(CFLAGS) -c -o $@ $<


$(TARGET): $(OBJECTS)
	$(CC) $(INCLUDE_PATHS) $(OBJECTS) $(LIBS) -o $@

clean: # Remove pasta com os arquivos objeto.
	-rm -f -r obj
	-rm -f *.o
	-rm -f $(TARGET)

run: # Executa o programa com valgrind.
	valgrind ./$(TARGET)
#	./$(TARGET)

reset: # Remove todo o conteúdo da pasta.
	-rm -f -r data/Saida/*
	