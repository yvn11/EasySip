# makefiles/predef.mk

CC		= gcc
CXX		= g++
TOUCH	= touch
MKDIR	= mkdir -p
RM		= rm -rf
LN		= ln -sf

PROJECT_ALIAS	= $(shell echo $(PROJECT)|tr '[:upper:]' '[:lower:]')
PROJECT_DIR		= $(shell pwd)
BUILD			= $(PROJECT_DIR)/build
VERSION_HEADER	= $(BUILD)/version.h
REVISION		= $(shell svn info|grep "Last Changed Rev"|cut -f2 -d:|cut -f2 -d\ ) 
SOURCES			= $(shell find $(SRCS) -iregex ".*\.c\(c\|pp\|++\|xx\)")

CFLAGS			+= -Wall -O0 -g3 --std=c++11 -MP -MMD
LDFLAGS			+=
MACROS			+=

SHARED_OBJ		= $(BUILD)/lib$(PROJECT_ALIAS).so
OBJS			= $(patsubst %.cpp, $(BUILD)/%.o, $(SOURCES))

