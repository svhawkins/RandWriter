# By Jae Choi generic recipe
EXE := TextWriter
objs := main.o RandWriter.o
test := test
testobjs := RandWriter.o test.o
SFML-LIBS := -lsfml-system

CXX := g++
CPPFLAGS := -std=c++17 -Wall -Werror -pedantic -g

ifneq ($(V),1)
Q = @
endif

all: $(EXE) test

#all objs has its .o replaced with .d for dependency tracking
deps := $(patsubst %.o,%.d,$(objs))
-include $(deps)
DEPFLAGS = -MMD -MF $(@: .o=.d)

all: $(EXE) test

$(EXE): $(objs)
	@echo "LINKING	$(EXE)"
	$(Q) $(CXX) $(objs) -o $(EXE) $(SFML-LIBS)

.PHONY: test
test: $(testobjs)
	@echo "LINKING	$(test)"
	$(Q) $(CXX) $(testobjs) -o $(test)

%.o: %.cpp
	@echo "CXX	$@"
	$(Q) $(CXX) $(CPPFLAGS) -c $< $(DEPFLAGS)

clean:
	@echo "CLEANING"
	$(Q) rm -f $(objs) $(EXE) $(testobjs) $(test)
