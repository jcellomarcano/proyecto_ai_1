/*
 * Archivo: IterativeDeepeningDFS.cpp
 * 
 * Descripcion: Codigo para aplicar "iterative deepening depth-first search".
 *              Esto nos permite resolver la primera parte del proyecto, en la 
 *              que tenemos que estudiar los arboles de busqueda que se generen
 *              a partir del estado goal, con y sin eliminación parcial de du-
 *              plicados, y que terminen despues de 15 minutos de ejecucion. 
 *
 *              Como no estamos buscando un estado goal sino generar la mayor 
 *              cantidad de nodos posible, hay algunas diferencias en estas
 *              funciones respecto a la representación estándar. Por ejemplo,
 *              en vez de retornar un nodo, estas funciones son void.
 *
 *              Este algoritmo es el ideal para este problema por consumir muy
 *              poca memoria.
 *
 * Integrantes: 
 *   - Jesus Marcano    (12-10359)
 *   - Daniel Figueroa  (16-10371)
 * 
 */

#include <vector>
#include "node.hpp"
#include <stdbool.h>
#include <iostream>    

using namespace std;

vector<int64_t> numberOfStates;

void bounded_dfs_visit(Node *n, unsigned depth, unsigned bound, const int history) {

    ruleid_iterator_t iter;   // Iterador sobre las reglas dado un estado
    state_t child;            // Guarda el estado hijo del nodo actual (no el nodo hijo, sino el estado).
    int ruleid;               // Identificador de la regla aplicada 

    // No se sigue buscando si la profundidad supera la cota de esta iteracion
    if (depth <= bound) {  
        // Actualizar el vector con el numero de estados por nivel
        if (numberOfStates.size() < depth+2) {
            numberOfStates.push_back(1);
        }
        else if (depth==bound) {
            numberOfStates[depth+1] += 1;
        } // -----------------------------------------------------

        init_fwd_iter(&iter, &(n->state));

        while((ruleid = next_ruleid(&iter)) >= 0) {
            if( fwd_rule_valid_for_history(history, ruleid) == 0){
                // NOTA: psvn2c debe ser llamado con history_length > 0 para que haga poda parcial
                continue; 
            }
            apply_fwd_rule(ruleid, &(n->state), &child);

            // Este es el nodo que tendra al estado hijo del estado actual
            Node n_child(child, n, 0); 
                /* El estado de este nuevo nodo es "child".
                 * El padre de este nuevo nodo es "n", que es el que estabamos examinando.
                 * En este algoritmo no importan los costos, asi que siempre seran cero. 
                 */

            int new_history = next_fwd_history(history, ruleid);  // Proxima historia para el hijo
            bounded_dfs_visit(&n_child, depth+1, bound, new_history);  
        }
    }
}

void iterative_deepening_dfs(state_t *rootState)
{   
    unsigned bound; 
    double branchingFactor; 
    numberOfStates.assign(1,1);   // Vector con la cantidad de nodos por nivel
    cout.precision(8);
    cout.setf(ios::fixed);

    // Creamos el nodo raiz
    Node rootNode(*rootState, NULL, 0);
        /* El estado de este nuevo nodo es el que esta apuntado por "initialState".
         * El padre de este nuevo nodo es NULL por ser la raiz.
         * En este algoritmo no importan los costos, asi que siempre seran cero. 
         */

    // Primera iteración donde no se hace ninguna impresión
    bounded_dfs_visit(&rootNode, 0, 0, init_history);
    bound = 1;

    while (1) {
        bounded_dfs_visit(&rootNode, 0, bound, init_history);
        branchingFactor = static_cast<float>(numberOfStates[bound+1])/ numberOfStates[bound];
        cout << bound-1 << "\t\t" << numberOfStates[bound] << "\t\t\t" << branchingFactor << endl;
        bound += 1;
    }
}

/* Este main es solo para hacer la expansion de nodos a partir del estado "goal", y estudiar el
   arbol de busqueda */
int main(int argc, char **argv)
{
    state_t goalState;
    int d;
    first_goal_state(&goalState, &d); 

    printf("\n\ndepth\t\t#nodes \t\t\temp.branching factor\n");
    printf("-----------------------------------------------------------------------------\n");
    
    iterative_deepening_dfs(&goalState);
    return 0;
}

