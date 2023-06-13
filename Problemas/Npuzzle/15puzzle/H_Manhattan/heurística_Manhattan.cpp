/*
 * Archivo: Heuristica_Manhattan.cpp
 * 
 * Descripcion: Codigo con las distancias de la heurística Manhattan para el 
 *              15-puzzle.
 *
 * Integrantes: 
 *   - Jesus Marcano    (12-10359)
 *   - Daniel Figueroa  (16-10371)
 * 
 */

unsigned mtable[16][16];

void establishHeuristic(){
	unsigned prov[16][16]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						   {1,0,1,2,2,1,2,3,3,2,3,4,4,3,4,5},
						   {2,1,0,1,3,2,1,2,4,3,2,3,5,4,3,4},
						   {3,2,1,0,4,3,2,1,5,4,3,2,6,5,4,3},
						   {1,2,3,4,0,1,2,3,1,2,3,4,2,3,4,5},
						   {2,1,2,3,1,0,1,2,2,1,2,3,3,2,3,4},
						   {3,2,1,2,2,1,0,1,3,2,1,2,4,3,2,3},
						   {4,3,2,1,3,2,1,0,4,3,2,1,5,4,3,2},
						   {2,3,4,5,1,2,3,4,0,1,2,3,1,2,3,4},
						   {3,2,3,4,2,1,2,3,1,0,1,2,2,1,2,3},
						   {4,3,2,3,3,2,1,2,2,1,0,1,3,2,1,2},
						   {5,4,3,2,4,3,2,1,3,2,1,0,4,3,2,1},
						   {3,4,5,6,2,3,4,5,1,2,3,4,0,1,2,3},
						   {4,3,4,5,3,2,3,4,2,1,2,3,1,0,1,2},
						   {5,4,3,4,4,3,2,3,3,2,1,2,2,1,0,1},
						   {6,5,4,3,5,4,3,2,4,3,2,1,3,2,1,0}};

	for (int i=0; i<16; i++) {
		for (int j=0; j<16; j++) {
			mtable[i][j] = prov[i][j];
		}
	}
}

// Manhattan II 

unsigned heuristic(state_t puzzle_state){
   unsigned h=0;
   for (int i=0; i<=15; i++){
      h += mtable[puzzle_state.vars[i]][i];
   }
   return h;
}
