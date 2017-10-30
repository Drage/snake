# Compiler setup
COMPILER = g++
CXXFLAGS += -O2

# Program name
DIR = $(shell basename $(shell pwd))
PROGRAM  = $(shell echo $(DIR) | tr A-Z a-z)

# Input files
VPATH = ../Common
SRC = $(wildcard *.cpp)
SRC += $(wildcard ../Common/*.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRC))

# Link libraries
LDFLAGS = -lGL -lglut
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
LDFLAGS = -framework OpenGL -framework GLUT
endif

all : $(PROGRAM)
	mv $(PROGRAM) ../../bin
	rm *.o

$(PROGRAM) : $(OBJS)
	$(COMPILER) -o $(PROGRAM) $(OBJS) $(LDFLAGS)

%.o : %.c
	$(COMPILER) -c $<
