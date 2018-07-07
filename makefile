# GNU General Public License - Version 3.0

RM      = rm
CC      = g++
CFLAGS  = -ansi -pedantic -Wall -O2
SOURCES = $(shell find -maxdepth 1 -type f -name "*.cpp")
OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))
DPFILES = $(patsubst %.cpp,%.d,$(SOURCES))
PROJECT = parcolor

.PHONY: all clean

# set default target
all: $(PROJECT)

# import dependencies
-include $(DPFILES)

# spot dependencies
$(DPFILES): %.d: %.cpp
	$(CC) -MM -o $@ $<

# link object files
$(PROJECT): $(OBJECTS)
	$(CC) -o $(PROJECT) $+
	
# compile source code
$(OBJECTS): %.o: %.cpp %.d
	$(CC) -c $(CFLAGS) -o $@ $<

# remove producible files
clean:
	@$(RM) $(OBJECTS) $(DPFILES) $(PROJECT)
