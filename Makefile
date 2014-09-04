# Makefile for EasySip

PROJECT		= EasySip
DESCRIPTION	= Easy-to-used SIP Stack
VERSION		= 0.0.1

INCLUDES	= include build
SRCS		= src
LIBS		=

include makefiles/predef.mk
include makefiles/basic.mk

all: easysip

easysip: $(SHARED_OBJ)
#	@echo $(MAKEFILE_LIST)

$(SHARED_OBJ): $(SHARED_OBJ).$(VERSION)
	@echo "\n===Building $@===>"
	$(RM) $(SHARED_OBJ)
	$(LN) $(shell basename $<) $@

$(SHARED_OBJ).$(VERSION) : $(OBJS)
	@echo "\n===Building $@===>"
	$(CXX) $(CFLAGS) -shared $(LDFLAGS) $(INCLUDES:%=-I%) $(MACROS:%=-D%) $(LIBS:%=-l%) -o $@ $^

$(BUILD)/%.o : %.cpp
	@echo "\n===Generating $@===>"
	$(MKDIR) $(dir $@)
	$(CXX) $(CFLAGS) $(LDFLAGS) $(INCLUDES:%=-I%) $(MACROS:%=-D%) $(LIBS:%=-l%) -c -o $@ $^

clean:
	$(RM) $(BUILD)

