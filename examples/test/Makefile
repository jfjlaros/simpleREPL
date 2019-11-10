EXEC := test
MAIN := test
OBJS := ../../src/io


CC := g++
INCLUDE_PATH := ../../src
CC_ARGS := -Wno-pmf-conversions -fpermissive -std=c++11 -I $(INCLUDE_PATH)


OBJS := $(addsuffix .o, $(OBJS))

.PHONY: all check clean distclean


all: $(EXEC)

$(EXEC): $(MAIN).cc $(OBJS)
	$(CC) $(CC_ARGS) -o $@ $^

%.o: %.cc
	$(CC) $(CC_ARGS) -o $@ -c $^

check: all
	valgrind ./$(EXEC)

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(EXEC)
