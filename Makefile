CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g
LDFLAGS=-g
LDLIBS=

SRCS=main.cpp message.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: flex

flex: $(OBJS)
	$(CXX) $(LDFLAGS) -o flex $(OBJS) $(LDLIBS)

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) tool
