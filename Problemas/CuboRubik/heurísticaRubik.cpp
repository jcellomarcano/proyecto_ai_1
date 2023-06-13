#include <iostream>

state_map_t *map1;
state_map_t *map2;
state_map_t *map3;
abstraction_t *abs1;
abstraction_t *abs2;
abstraction_t *abs3;
state_t abs_state1;
state_t abs_state2;
state_t abs_state3;
unsigned maximo;

void establishHeuristic(){
	FILE *f1 = fopen("cuboRubik_1-edgeCubies.pdb","r");
	FILE *f2 = fopen("cuboRubik_2-edgeCubies.pdb","r");
	FILE *f3 = fopen("cuboRubik_cornersCubies.pdb","r");

	abs1 = read_abstraction_from_file("cuboRubik_1-edgeCubies.abst");
	map1 = read_state_map(f1);

	abs2 = read_abstraction_from_file("cuboRubik_2-edgeCubies.abst");
	map2 = read_state_map(f2);

	abs3 = read_abstraction_from_file("cuboRubik_cornersCubies.abst");
	map3 = read_state_map(f3);

	fclose(f1);
	fclose(f2);
	fclose(f3);	
}

unsigned heuristic(state_t puzzle_state){
	abstract_state(abs1, &puzzle_state, &abs_state1);
	abstract_state(abs2, &puzzle_state, &abs_state2);
	abstract_state(abs3, &puzzle_state, &abs_state3);

	/*Aplicamos el maximo de las 3 heuristicas para el cubo de rubik, donde la primera abstraccion contiene la mitad de los edge cubies,
	  la 2da contiene la otra mitad de los edges cubies y por ultimo la 3era contiene todos los corner cubies */

	maximo = std::max(*state_map_get(map1, &abs_state1), std::max(*state_map_get(map2, &abs_state2), *state_map_get(map3, &abs_state3)));

	return (maximo);
}