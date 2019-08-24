IDIR =.
CC=g++
CXXFLAGS=-I$(IDIR) -Wall -O2

ODIR=.
LDIR =

LIBS =

_DEPS = hellomake.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = hellomake.o  main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cc $(DEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS)

hellomake: $(OBJ)
	$(CC) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
