CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g
LDFLAGS=-g
LDLIBS=

SRCS=fiw.cpp helper.cpp main.cpp message.cpp test.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: test

flex: $(OBJS)
	$(CXX) $(LDFLAGS) -o flex $(OBJS) $(LDLIBS)

test: $(OBJS)
	$(CXX) $(LDFLAGS) -o test test.o message.o fiw.o helper.o

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) tool
