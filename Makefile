CC      = gcc
CFLAGS  = -Wall -O2 -std=c99
TARGET  = demo

SRC     = demo.c \
          c-map.c \
          map_cmp.c \
          map_core.c \
          map_delete.c \
          map_insert.c \
          map_rotate.c \
          map_search.c

OBJ     = $(SRC:.c=.o)

$(TARGET): $(OBJ)
    $(CC) $(CFLAGS) -o $@ $^

clean:
    rm -f $(TARGET) $(OBJ)
    
test: $(TARGET)
    ./$(TARGET)