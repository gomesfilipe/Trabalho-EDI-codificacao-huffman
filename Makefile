#	gcc src/*.c client/Compacta.c -o Compacta
#	gcc src/*.c client/Descompacta.c -o Descompacta

NOMECOMPACTA := string.txt
NOMEDESCOMPACTA := $(NOMECOMPACTA).comp

TARGET1 := Compacta
TARGET2 := Descompacta

LIBS := -lm
#CFLAGS := -g -O3 -Wno-unused-result

OBJDIR1 := obj_compacta/
OBJDIR2 := obj_descompacta/

SRCDIR := src/

INCLUDEDIR := include/
INCLUDE_PATHS := -Iinclude

CLI1 := client/Compacta.c
CLI2 := client/Descompacta.c
CC := gcc

all: $(TARGET1) $(TARGET2)

SRC = $(wildcard $(SRCDIR)*.c)
HEADERS = $(wildcard $(INCLUDEDIR)*.h)

CLIENT1 = $(OBJDIR1)$(basename $(notdir $(CLI1)))
CLIENT2 = $(OBJDIR2)$(basename $(notdir $(CLI2)))

OBJECTS1 := $(SRC:$(SRCDIR)%.c=$(OBJDIR1)%.o)
OBJECTS1 += $(CLIENT1).o

OBJECTS2 := $(SRC:$(SRCDIR)%.c=$(OBJDIR2)%.o)
OBJECTS2 += $(CLIENT2).o

$(OBJDIR1)%.o: $(SRCDIR)%.c $(HEADERS)
	@ mkdir -p $(OBJDIR1)
	$(CC) $(INCLUDE_PATHS) $(CFLAGS) -c -o $@ $<

$(OBJDIR2)%.o: $(SRCDIR)%.c $(HEADERS)
	@ mkdir -p $(OBJDIR2)
	$(CC) $(INCLUDE_PATHS) $(CFLAGS) -c -o $@ $<

$(CLIENT1).o: $(CLI1)
	$(CC) $(INCLUDE_PATHS) $(CFLAGS) -c -o $@ $<

$(CLIENT2).o: $(CLI2)
	$(CC) $(INCLUDE_PATHS) $(CFLAGS) -c -o $@ $<

$(TARGET1): $(OBJECTS1)
	$(CC) $(INCLUDE_PATHS) $(OBJECTS1) $(LIBS) -o $@

$(TARGET2): $(OBJECTS2)
	$(CC) $(INCLUDE_PATHS) $(OBJECTS2) $(LIBS) -o $@

clean: # Remove pasta com os arquivos objeto.
	-rm -f -r $(OBJDIR1)
	-rm -f -r $(OBJDIR2)
	-rm -f *.o
	-rm -f $(TARGET1)
	-rm -f $(TARGET2)

runComp:
	valgrind ./$(TARGET1) $(NOMECOMPACTA)

runDescomp:
	valgrind ./$(TARGET2) $(NOMEDESCOMPACTA)
