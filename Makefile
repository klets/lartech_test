INCDIR = inc
SRCDIR = src
BINDIR = bin

OUT_DIR = $(BINDIR)

CC=gcc

CFLAGS=-Wall -pedantic -std=gnu99 -Wno-variadic-macros -I$(INCDIR) $(LDFLAGS) $(XCFLAGS)

TARGET = lartech

MKDIR_P = mkdir -p

.PHONY: directories

all: directories $(TARGET) 

lartech: $(SRCDIR)/*.c
	$(CC) $(CFLAGS) $^ -o $(BINDIR)/$@

directories: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

clean:
	rm -rf $(OUT_DIR)
