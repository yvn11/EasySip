# Makefile for test

PROJECT		= EasySip
DESCRIPTION	= Easy-to-used SIP Stack
VERSION		= 0.0.1

INCLUDES	+= ../include ../build
SRCS		+= .
LIBS		+= easysip
LDPATH		+= ../build
LDFLAGS		+= $(LDPATH:%=-L%)
#MACROS		+= _GLIBCXX_USE_NANOSLEEP

include ../makefiles/predef.mk

all: ts-udp-d ts-udp

%: %.cpp
	@echo
	@echo "===Generating $(BUILD)/test/$@===>"
	$(MKDIR) $(dir $(BUILD)/test/$@)
	$(CXX) $(CFLAGS) $(LDFLAGS) $(INCLUDES:%=-I%) $(MACROS:%=-D%) $(LIBS:%=-l%) -o $(BUILD)/test/$@ $^
	
