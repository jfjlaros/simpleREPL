EXEC := calculator
MAIN := calculator


CC := g++
INCLUDE_PATH := 
CC_ARGS := -Wno-pmf-conversions


.PHONY: all check clean distclean


all: $(EXEC)

$(EXEC): $(MAIN).cc
	$(CC) $(CC_ARGS) -o $@ $^

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(EXEC)
