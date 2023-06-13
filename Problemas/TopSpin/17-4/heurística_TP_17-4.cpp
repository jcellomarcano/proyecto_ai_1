#include <iostream>

// Variables para guardar las pdb's
state_map_t *pdb1, *pdb2;

// Variables para guardar la especificación de la abstracción correspondiente
abstraction_t *abs1, *abs2;

/* Variables para almacenar estados, que son equivalentes al estado pasado
   como entrada, pero aplicando sus respectivas abstracciones */
state_t abst_state1;
state_t abst_state2;
unsigned maximo;

void establishHeuristic(){
	FILE *f1 = fopen("TopSpin-17-4_abst1pdb.pdb","r");
	FILE *f2 = fopen("TopSpin-17-4_abst2pdb.pdb","r");


	pdb1 = read_state_map(f1);
	pdb2 = read_state_map(f2);

	abs1 = read_abstraction_from_file("TopSpin-17-4_abst1pdb.abst");
    abs2 = read_abstraction_from_file("TopSpin-17-4_abst2pdb.abst");

	fclose(f1);
	fclose(f2);
}

unsigned heuristic(state_t s){
	abstract_state(abs1, &s, &abst_state1);
	abstract_state(abs2, &s, &abst_state2);

	maximo = std::max(*state_map_get(pdb1, &abst_state1), *state_map_get(pdb2, &abst_state2));

	return maximo;
}
