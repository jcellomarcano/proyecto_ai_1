#include <iostream>

state_map_t *map1;
state_map_t *map2;
state_map_t *map3;
state_map_t *map4;
state_map_t *map5;
state_map_t *map6;
abstraction_t *abs1;
abstraction_t *abs2;
abstraction_t *abs3;
abstraction_t *abs4;
abstraction_t *abs5;
abstraction_t *abs6;
state_t abs_state1;
state_t abs_state2;
state_t abs_state3;
state_t abs_state4;
state_t abs_state5;
state_t abs_state6;
unsigned suma;

void establishHeuristic(){
	FILE *f1 = fopen("24-puzzle_project1.pdb","r");
	FILE *f2 = fopen("24-puzzle_project2.pdb","r");
	FILE *f3 = fopen("24-puzzle_project3.pdb","r");
	FILE *f4 = fopen("24-puzzle_project4.pdb","r");
	FILE *f5 = fopen("24-puzzle_project5.pdb","r");
	FILE *f6 = fopen("24-puzzle_project6.pdb","r");

	abs1 = read_abstraction_from_file("24-puzzle_project1.abst");
	map1 = read_state_map(f1);

	abs2 = read_abstraction_from_file("24-puzzle_project2.abst");
	map2 = read_state_map(f2);

	abs3 = read_abstraction_from_file("24-puzzle_project3.abst");
	map3 = read_state_map(f3);

	abs4 = read_abstraction_from_file("24-puzzle_project4.abst");
	map4 = read_state_map(f4);

	abs5 = read_abstraction_from_file("24-puzzle_project5.abst");
	map5 = read_state_map(f5);

	abs6 = read_abstraction_from_file("24-puzzle_project6.abst");
	map6 = read_state_map(f6);

	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f4);
	fclose(f5);
	fclose(f6);		
}

unsigned heuristic(state_t puzzle_state){
	abstract_state(abs1, &puzzle_state, &abs_state1);
	abstract_state(abs2, &puzzle_state, &abs_state2);
	abstract_state(abs3, &puzzle_state, &abs_state3);
	abstract_state(abs4, &puzzle_state, &abs_state4);
	abstract_state(abs5, &puzzle_state, &abs_state5);
	abstract_state(abs6, &puzzle_state, &abs_state6);

	suma = *state_map_get(map1, &abs_state1) + *state_map_get(map2, &abs_state2) + *state_map_get(map3, &abs_state3) + *state_map_get(map4, &abs_state4) + *state_map_get(map5, &abs_state5) + *state_map_get(map6, &abs_state6);

	return (suma);
}
