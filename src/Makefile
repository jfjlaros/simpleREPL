EXEC := test
MAIN := test
OBJS := io


CC := g++
INCLUDE_PATH := 
CC_ARGS := -Wno-pmf-conversions -std=c++11


OBJS := $(addsuffix .o, $(OBJS))

.PHONY: all check clean distclean


all: $(EXEC)

$(EXEC): $(MAIN).cc $(OBJS)
	$(CC) $(CC_ARGS) -o $@ $^

%.o: %.cc %.h
	$(CC) $(CC_ARGS) -c $^

check: all
	valgrind ./$(EXEC)

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(EXEC)
