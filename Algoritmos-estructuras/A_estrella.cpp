/*
 * Archivo: A_estrella.cpp
 * 
 * Descripcion: Codigo con las funciones para implementar A* con eliminación
 *              retardada de duplicados, incluyendo un main que lo ejecuta.
 *
 * Integrantes: 
 *   - Jesus Marcano    (12-10359)
 *   - Daniel Figueroa  (16-10371)
 * 
 */

#include <vector>
#include <stdbool.h>
#include <iostream>
#include <stdbool.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <time.h> 
#include <iomanip>

#include "priority_queue.hpp" 

using namespace std;

// Eĺ numero "generatedNodes" indica cuantos nodos fue necesario generar para encontrar el goal.
int64_t generatedNodes; 

/* El siguiente algoritmo es A* ---> best-first search + admissible heuristic

   Gracias a los atributos que contiene la priority_queue definida por psvn,
   no es necesario definir los nodos que están en el algoritmo de las láminas,
   sino que se puede trabajar directamente con los estados.

   No necesitamos retornar el nodo goal, sino únicamente su costo, y por ello
   la función devuleve un entero */
int best_first_search(state_t *rootState){

    state_t current_s;        // Guarda el estado actual.
    state_t child_s;          // Guarda el estado hijo del estado actual.
    int current_g;            // Costo acumulado desde la raiz hasta el estado actual, hallado actualmente
    int *previous_g;          // Costo del estado actual que fue almacenado en una iteración previa.
    int child_h;              // Heuristica que estima el costo del hijo.
    int child_g;              // Costo acumulado hasta el momento más el costo de llegar al hijo.
    int ruleid;               // Identificador de la regla aplicada.
    ruleid_iterator_t iter;   // Iterador sobre las reglas dado un estado.
    PriorityQueue<state_t> q; /* Cola de prioridades ordenada por el valor de f,
                                 donde f(n) = g(n)+h(state) */
    state_map_t *mapCosts = new_state_map(); /* Contiene el costo hasta el goal de todos los
                                                estados que han sido generados. */


	// Al state_map llamado "map" le añadimos el estado inicial "rootState", cuya distancia es 0.
	state_map_add(mapCosts, rootState, 0);
    q.Add(0, 0, *rootState);

    while (!q.Empty()) {  	
    	current_s = q.Top();
    	current_g = q.CurrentPriority();
    	q.Pop();

    	previous_g = state_map_get(mapCosts, &current_s);

    	if ((previous_g == NULL) || (!compare_states(&current_s, rootState)) || (current_g < *previous_g)) {
    		state_map_add(mapCosts, &current_s, current_g);

    		if (is_goal(&current_s)) {
                return current_g;
            }

            /* Si el estado actual no es goal, creamos un nodo nuevo 
               (que en realidad no es un nodo sino un estado)*/
    		++generatedNodes; 

    		init_fwd_iter( &iter, &current_s ); 
            while((ruleid = next_ruleid(&iter)) >= 0) {
                apply_fwd_rule(ruleid, &current_s, &child_s);
                child_h = heuristic(child_s);
                // Caso en que el valor devuelto por la heuristica es menor que "infinito"
                if (child_h < INT_MAX) { 
                	child_g = current_g + get_fwd_rule_cost(ruleid);
                	q.Add( child_g+child_h, child_g, child_s);
                }
            }
    	}
    }
    return -1;    
}

/* El usuario debera ingresar un archivo cuyas lineas representen los estados iniciales a
   a partir de los cuales se busca el goal. Sin embargo, el problema a tratar (15-puzzle,
   cubo de Rubik, etc.) debe especificarse al compilar con el makefile */
int main(int argc, char **argv) {
    char fileName[1000];  // Nombre del archivo de pruebas que ingresara el usuario.
    int printInstance;    // Entero que determina si debe imprimirse la instancia en cada paso, o no.
    char strMode[10];  // Lee la cadena que representa la respuesta ingresada por el usuario.
    ifstream file;  // Aqui se guardara la información del archivo con el nombre guardado en "fileName".
    string line;    // Esta variable ira almacenando las lineas leidas del archivo.
    ssize_t nchars; // Determina si un estado leido es valido para este problema.
    clock_t initTime, finalTime; // Declaramos las variables para tomar el tiempo de corrida.
    double totalTime;      // Tiempo de corrida de IDA* para encontrar el goal, dado un estado inicial, 
    state_t firstState;    // Estado a partir del cual se iniciara la busqueda con IDA*.
    int instanceId = 0;    // Representa el número de instancia a examinar.
    double nodesPerSecond; // Número de nodos generados por segundo
    int goalCost; // El costo de llegar al goal, devuelto por el algoritmo

    printf("1) Ingrese un archivo de prueba seguido de ENTER: ");
    if (fgets(fileName, sizeof fileName, stdin) == NULL) {
        printf("\n>>>Error: la linea ingresada esta vacia.\n");
        return 0;
    }

    fileName[strlen(fileName)-1] = '\0';

    file.open(fileName);

    if (!file.is_open()) {
        printf("\n>>>Error: El nombre del archivo es invalido: %s\n", fileName);
        return -1;
    }

    printf("2) Ingrese:\n   * 1 si desea imprimir la instancia inicial en cada paso.\n");
    printf("   * 0 en caso contrario.\n");
    printf("---> Respuesta seguida de ENTER: ");
    if (fgets(strMode, sizeof strMode, stdin) == NULL) {
        printf("\n>>>Error: la linea ingresada esta vacia.\n");
        return 0;
    }

    printInstance = atoi(strMode);

    printf("3) Ahora ingrese:\n   * 0 si solo desea generar el numero optimo de pasos.\n");
    printf("   * 1 si adicionalmente quiere los tiempos y la cantidad de nodos generados.\n");
    printf("---> Respuesta seguida de ENTER: ");
    if (fgets(strMode, sizeof strMode, stdin) == NULL) {
        printf("\n>>>Error: la linea ingresada esta vacia.\n");
        return 0;
    }
    // Caso en que solo se desea imprimir el numero optimo de pasos.
    else if (atoi(strMode) == 0){
        printf("\nCargando la heuristica...\n");
        establishHeuristic(); // Puede ser una PDB u otra heuristica especifica al problema.
        if (printInstance){
            // Cabecera del resultado: caso en que debemos imprimir la instancia
            cout << "\n<id> : <instance> : <final-value>\n";  
        }
        else {
            // Cabecera del resultado: caso en que no debemos imprimir la instancia
            cout << "\n<id> : <final-value>\n";  
        }
        
        // Cada iteracion de este ciclo es una instancia nueva desde la cual se va a buscar el goal
        while (!file.eof()) {
            getline(file, line);

            if (line == "\0"){
                break;
            }

            nchars = read_state(line.c_str(), &firstState);
            ++instanceId;
            cout << setfill('0') << setw(3) << instanceId << " : "; // Imprimimos el número de instancia a examinar
            
            if (nchars <= 0) {
                printf("\n>>>Error: El estado que se leyo no es valido para este problema.\n");
                continue;
            }

            if (printInstance){
                // Imprimimos el estado a examinar
                print_state(stdout, &firstState); 
                cout << ": ";  
            }

            generatedNodes = 1; // --> Cantidad de nodos que se generarán (aparte del inicial).
            goalCost = best_first_search(&firstState); // --> Ejecutamos el algoritmo A*
            cout << goalCost << endl;           
        }
    }
    // Caso en que se desea imprimir la información completa.
    else{
        printf("\nCargando la heuristica...\n");
        establishHeuristic(); // Puede ser una PDB u otra heuristica especifica al problema.
        if (printInstance){
            // Cabecera del resultado: caso en que debemos imprimir la instancia
            cout << "\n<id> : <instance> : <# generated nodes> <final-value> <time-in-secs> <#gen/sec>\n";
        }
        else {
            // Cabecera del resultado: caso en que no debemos imprimir la instancia
            cout << "\n<id> : <# generated nodes> <final-value> <time-in-secs> <#gen/sec>\n"; 
        }
               
        // Cada iteracion de este ciclo es una instancia nueva desde la cual se va a buscar el goal
        while (!file.eof()) {
            getline(file, line);

            if (line == "\0"){
                break;
            }

            nchars = read_state(line.c_str(), &firstState);
            ++instanceId;
            cout << setfill('0') << setw(3) << instanceId << " : "; // Imprimimos el número de instancia a examinar
            if (nchars <= 0) {
                printf("\n>>>Error: El estado que se leyo no es valido para este problema.\n");
                continue;
            }

            if (printInstance){
                // Imprimimos el estado a examinar
                print_state(stdout, &firstState); 
                cout << ": ";  
            }

            initTime = clock(); // --> Iniciamos el cronometro
            generatedNodes = 1; // --> Cantidad de nodos que se generarán (aparte del incial).
            goalCost = best_first_search(&firstState); // --> Ejecutamos el algoritmo A*
            finalTime = clock();  // --> Paramos el cronometro
            totalTime = (double) (finalTime - initTime) / CLOCKS_PER_SEC;  // Tiempo total requerido
            nodesPerSecond = generatedNodes/totalTime;
            cout << generatedNodes << " " << goalCost << " " << totalTime << " " << nodesPerSecond << endl;           
        }
    }
    file.close();
    return 0;
}
