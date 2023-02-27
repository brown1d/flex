CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g
LDFLAGS=-g
LDLIBS=

SRCS=helper.cpp main.cpp message.cpp codewords/biw1.cpp \
	codewords/biw2.cpp codewords/biw3.cpp codewords/biw4.cpp codewords/fiw.cpp \
	codewords/messageAlphaContents.cpp codewords/messageAlphaHeader.cpp \
	codewords/messageAlphaSignature.cpp test.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: test

flex: $(OBJS)
	$(CXX) $(LDFLAGS) -o flex $(OBJS) $(LDLIBS)

test: $(OBJS)
	$(CXX) $(LDFLAGS) -o test test.o message.o helper.o codewords/*.o

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) tool
