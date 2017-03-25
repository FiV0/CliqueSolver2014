#makefile
CC = g++
CFLAGS = -ansi -Wall -O3#-pedantic

# uncomment "EXE = tomita_t" and comment "EXE = mode_solver" to change to the tomita algorithm
# Attention! : Don't forget to do the changes as described in the tomita.h header file 

#EXE = tomita_t
EXE = mode_solver 
OBJ = obj

all: $(OBJ) $(EXE) 

$(OBJ):
	mkdir $@

#all the commented object files and programs are normally only for testing

#$(OBJ)/dm.o : dm.c dm_english.h
#	$(CC) $(CFLAGS) -o $@  -c $<
#
#$(OBJ)/main.o : random.c dm_english.h
#	$(CC) $(CFLAGS)  -o $@ -c $<
#
#test:  $(OBJ)/main.o $(OBJ)/dm.o 
#	$(CC) $(CFLAGS) $^ -o $@ 
#
#$(OBJ)/prime_graph_io.o : prime_graph_io.cpp prime_graph_io.h
#	$(CC) $(CFLAGS)  -o $@ -c $<
#
#$(OBJ)/tree_clique_test.o : tree_clique_test.cpp prime_graph_io.h
#	$(CC) $(CFLAGS)  -o $@ -c $<
#
#tree_clique_test:  $(OBJ)/tree_clique_test.o $(OBJ)/prime_graph_io.o 
#	$(CC) $(CFLAGS) $^ -o $@ 
#
$(OBJ)/tomita.o : tomita.cpp tomita.h
	$(CC) $(CFLAGS) -o $@  -c $<

ifeq ($(EXE),tomita_t)

$(OBJ)/tomita_test.o : tomita_test.cpp tomita.h
	$(CC) $(CFLAGS) -o $@  -c $<

tomita_t: $(OBJ)/tomita_test.o $(OBJ)/tomita.o 
	$(CC) $(CFLAGS) $^ -o $@ 

else

$(OBJ)/dm_clique.o : dm_clique.cpp dm_clique.h
	$(CC) $(CFLAGS) -o $@  -c $<

$(OBJ)/prime_graph_io.o : prime_graph_io.cpp prime_graph_io.h
	$(CC) $(CFLAGS) -o $@  -c $<

$(OBJ)/tomita_tree.o : tomita_tree.cpp tomita_tree.h
	$(CC) $(CFLAGS) -o $@  -c $<

$(OBJ)/mode_sovler.o : mode_solver.cpp tomita.h dm_clique.h tomita_tree.h prime_graph_io.h
	$(CC) $(CFLAGS) -o $@  -c $<

mode_solver: $(OBJ)/mode_sovler.o $(OBJ)/tomita.o $(OBJ)/dm_clique.o $(OBJ)/prime_graph_io.o $(OBJ)/tomita_tree.o 
	$(CC) $(CFLAGS) $^ -o $@ 

endif

clean:
	rm -f $(OBJ)/*.o $(EXE)
