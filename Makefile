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

cppcheck:
	@echo "🔍 Running Cppcheck..."
	cppcheck --enable=all --inconclusive --std=c99 --force \
	--suppress=missingIncludeSystem \
	-I . $(SRC) 2> cppcheck_report.txt
	@echo "✅ Cppcheck finished. See cppcheck_report.txt"

format:
	@echo "🎨 Running clang-format on all source files..."
	clang-format -i -style=file $(SRC) c-map.h map_internal.h
	@echo "✅ Formatting complete."
