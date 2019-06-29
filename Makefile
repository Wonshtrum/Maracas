GCC = g++ -std=c++11 -Wall -g
GOO = $(GCC) -c
RM = rm -if
srcdir = src/
bindir = bin/
docdir = doc/
savedir = save/
SRC = $(wildcard $(srcdir)*.cpp)
HEAD = $(wildcard $(srcdir)*.h)
OBJ = $(subst $(srcdir), $(bindir), $(SRC:.cpp=.o))
PROG = ProgCompil

all = $(PROG)

$(PROG) : $(OBJ)
	$(GCC) $^ -o $@ -lGL -lGLU -lglfw3 -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor

$(bindir)%.o : $(srcdir)%.cpp
	$(GOO) $^ -o $@

.PHONY : clean
clean :
	$(RM) $(bindir)*
