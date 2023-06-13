# to make a PDB starting from foo.psvn  type the command:     make pdb ss=foo
# if $(absname).txt exists it will be used as the input (abstraction commands) to build the abstraction,
#   otherwise the user will enter the abstraction commands interactively.

CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --backwards_moves --fwd_history_len=1

psvn2c_core.c:
	cp ../../../src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ../../../src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ../../../src/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../../../bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

priority_queue.hpp:
	cp ../../../global/priority_queue.hpp ./priority_queue.hpp

node.hpp:
	cp ../../../Algoritmos-estructuras/node.hpp ./node.hpp

%.succ: %.c ../../../global/succ.c
	$(CC) $(OPT) ../../../global/succ.c -include $< -o $@
	rm -f $*.c

%.dist: %.c ../../../global/dist.cpp
	$(CXX) $(OPT) ../../../global/dist.cpp -include $< -o $@
	rm -f $*.c

%.distSummary: %.c ../../../global/distSummary.cpp
	$(CXX) $(OPT) ../../../global/distSummary.cpp -include $< -o $@
	rm -f $*.c

abstractor:
	$(CXX) $(OPT) ../../../src/abstractor.cpp ../../../src/psvn.cpp -o $@

%.pdb: abstractor
	@rm -f `dirname $*`_`basename $*`.{abst,pdb,psvn}
	./abstractor `dirname $*`.psvn `dirname $*`_`basename $*` < `basename $*`.txt
	make `dirname $*`_`basename $*`.distSummary
	echo Calculating `dirname $*`_`basename $*.pdb` ...
	@./`dirname $*`_`basename $*`.distSummary `dirname $*`_`basename $*`.pdb

%.dist_pdb: %.c ../../../global/dist_pdb.cpp
	$(CXX) $(OPT) ../../../global/dist_pdb.cpp -include $< -o $@
	rm -f $*.c

# IDDFS -> significa: Iterative deepening depth-first search
%.IDDFS: %.c ../../../Algoritmos-estructuras/IterativeDeepeningDFS.cpp priority_queue.hpp node.hpp
	$(CXX) $(OPT) ../../../Algoritmos-estructuras/IterativeDeepeningDFS.cpp -include $< -o $@

%.IDA*: %.c ../../../Algoritmos-estructuras/IDA_estrella.cpp node.hpp
	$(CXX) $(OPT) ../../../Algoritmos-estructuras/IDA_estrella.cpp -include $< -include heurísticaPDB4-4-4-4-4-4.cpp -o $@

%.A*: %.c ../../../Algoritmos-estructuras/A_estrella.cpp priority_queue.hpp
	$(CXX) $(OPT) ../../../Algoritmos-estructuras/A_estrella.cpp -include $< -include heurísticaPDB4-4-4-4-4-4.cpp -o $@

.PHONY: clean
clean:
	rm -fr *.succ *.dist *.distSummary *.dist_pdb psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c abstractor *.dSYM *.o *~
