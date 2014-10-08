# Makefile for test

PROJECT		= EasySip
DESCRIPTION	= Easy-to-used SIP Stack
VERSION		= 0.0.1

INCLUDES	+= ../include ../build
SRCS		+= .
SOURCES		= $(shell find $(SRCS) -iregex ".*\.c\(c\|pp\|++\|xx\)")
LIBS		+= easysip
LDPATH		+= ../build
LDFLAGS		+= $(LDPATH:%=-L%)
#MACROS		+= _GLIBCXX_USE_NANOSLEEP

include ../makefiles/predef.mk

all: $(patsubst %.cpp, %, $(SOURCES))
#ts-server ts-client ts-proxy

%: %.cpp
	@echo
	@echo "===Generating $(BUILD)/test/$@===>"
	$(MKDIR) $(dir $(BUILD)/test/$@)
	$(CXX) $(CFLAGS) $(LDFLAGS) $(INCLUDES:%=-I%) $(MACROS:%=-D%) $(LIBS:%=-l%) -o $(BUILD)/test/$@ $^
	
