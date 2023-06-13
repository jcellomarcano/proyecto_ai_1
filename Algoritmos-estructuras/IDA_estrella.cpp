/*
 * Archivo: IDA_estrella.cpp
 * 
 * Descripcion: Codigo con las funciones para implementar IDA*, incluyendo
 *              un main que lo ejecuta.
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

#include "node.hpp"   

using namespace std;

/* Eĺ numero "generatedNodes" indica cuantos nodos fue necesario generar para encontrar el goal.
   Esto incluye los duplicados y los que fueron generados en una iteracion previa de IDA*. */
int64_t generatedNodes; 


// Esta función representa la visita a un nodo en el dfs acotado para IDA*.
pair <Node*, unsigned> f_bounded_dfs_visit(Node *n, unsigned bound, const int history) {
    unsigned f = (*n).g + heuristic((*n).state); /* Costo acumulado desde la raiz hasta el nodo actual,
                                                    mas el costo estimado para llegar al goal (heuristica).*/
    ruleid_iterator_t iter;   // Iterador sobre las reglas dado un estado
    state_t child;            // Guarda el estado hijo del nodo actual (no el nodo hijo, sino el estado)
    int ruleid;               // Identificador de la regla aplicada 

    /*SALIDA: La primera coordenada podria ser el goal si se encontro, o bien NULL,
              y la segunda coordenada es el costo acumulado hasta el nodo actual.*/
    pair <Node*, unsigned> result;                                    

    // No se sigue buscando si la funcion de costo supera la cota de esta iteracion
    if (f > bound) {  
        result.first = NULL;
        result.second = f;
        return result;
    }

    // Si el estado es goal, retornamos el apuntador a su nodo junto con el costo
    if ( is_goal(&(n->state)) ){
        result.first = n;
        result.second = (*n).g;
        return result;
    }

    ++generatedNodes;
    unsigned t = INT_MAX; // Simulamos el valor infinito con el máximo posible para un entero.

    init_fwd_iter(&iter, &(n->state));
    while((ruleid = next_ruleid(&iter)) >= 0) {

        //apply_fwd_rule(ruleid, &(n->state), &child);

        if( fwd_rule_valid_for_history(history, ruleid) == 0){
            // NOTA: psvn2c debe ser llamado con history_length > 0 para que haga poda parcial
            continue; 
        }

        apply_fwd_rule(ruleid, &(n->state), &child);

        // Este es el nodo que tendra al estado hijo del estado actual
        Node n_child(child, n, (n->g)+1); 
            /* El estado de este nuevo nodo es "child".
             * El padre de este nuevo nodo es "n", que es el que estabamos examinando.
             * En este algoritmo no importan los costos, asi que siempre seran cero. 
             */

        int new_history = next_fwd_history(history, ruleid);  // Proxima historia para el hijo
        pair <Node*, unsigned> p = f_bounded_dfs_visit(&n_child, bound, new_history); 

        if (p.first != NULL){
            // Uno de los nodos de la descendencia es el goal, asi que lo retornamos
            return p;
        }
        t = min(t,p.second);
    }
    // Caso en que no hay camino desde el nodo actual hasta el goal
    result.first = NULL;
    result.second = t;
    return result;
}

// Esta función se encarga de llamar a f_bounded_dfs_visit
Node ida_search(state_t *rootState, int mode){   
    unsigned bound = heuristic(*rootState); /* La primera cota es el valor de la heuristica para el
                                               estado inicial  */

    // Creamos el nodo raiz
    Node rootNode(*rootState, NULL, 0);
        /* El estado de este nuevo nodo es el que esta apuntado por "initialState".
         * El padre de este nuevo nodo es NULL por ser la raiz.
         */

    // Caso en que no debemos imprimir las cotas que se van generando
    if (mode == 0){
        while (1) {
            pair <Node*, unsigned> p = f_bounded_dfs_visit(&rootNode, bound, init_history);
            if (p.first != NULL){
                return *p.first;
            }
            bound = p.second;
        }
    }
    // Caso en que sí debemos ir imprimiendo las cotas
    else{
        while (1) {
            cout << bound << " "; // Imprimimos la cota que tendra esta iteracion de IDA*.
            pair <Node*, unsigned> p = f_bounded_dfs_visit(&rootNode, bound, init_history);
            if (p.first != NULL){
                return *p.first;
            }
            bound = p.second;
        }
    }
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
    double nodesPerSecond; // Numero de nodos generados por segundo

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
            Node goal = ida_search(&firstState,0); // --> Ejecutamos el algoritmo A*
            cout << goal.g << endl;           
        }
    }
    // Caso en que se desea imprimir la información completa.
    else{
        printf("\nCargando la heuristica...\n");
        establishHeuristic(); // Puede ser una PDB u otra heuristica especifica al problema.
        if (printInstance){
            // Cabecera del resultado: caso en que debemos imprimir la instancia
            cout << "\n<id> : <instance> : <thresholds> : <# generated nodes> <final-value> <time-in-secs> <#gen/sec>\n";
        }
        else {
            // Cabecera del resultado: caso en que no debemos imprimir la instancia
            cout << "\n<id> : <thresholds> : <# generated nodes> <final-value> <time-in-secs> <#gen/sec>\n"; 
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
            Node goal = ida_search(&firstState,1); // --> Ejecutamos el algoritmo A*
            finalTime = clock();  // --> Paramos el cronometro
            totalTime = (double) (finalTime - initTime) / CLOCKS_PER_SEC;  // Tiempo total requerido
            nodesPerSecond = generatedNodes/totalTime;
            cout << ": " << generatedNodes << " " << goal.g << " " << totalTime << " " << nodesPerSecond << endl;           
        }
    }
    file.close();
    return 0;
}
