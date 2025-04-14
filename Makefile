CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lmingw32 -lraylib -lraylibdll -lopengl32 -lgdi32 -lwinmm

INCLUDES = -Iinclude
LIBS = -Llib

OUTPUTDIR = build
TARGET = kissed

SRCS = $(wildcard src/*.c)

OBJS = $(SRCS:src/%.c=$(OUTPUTDIR)/%.o)

all: $(OUTPUTDIR)/$(TARGET)

$(OUTPUTDIR)/$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $(TARGET)
	@echo "$(TARGET).exe created in $(OUTPUTDIR)."

$(OUTPUTDIR)/%.o: src/%.c
	@mkdir -p $(OUTPUTDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo ".o files created."

clean:
	rm -f $(OBJS) $(TARGET)

# Règle pour nettoyer tout
distclean: clean
	rm -rf build

.PHONY: all clean distclean
