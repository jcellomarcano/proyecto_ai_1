# Inteligencia Artificial I - CI5437
## Profesor: Carlos Infante
### Integrantes:
- Jesus Marcano, 12-10359

## Proyecto I PSVN

Especificaciones del entorno de prueba:
- Memoria: 32 GB RAM
- Procesamiento: Intel(R) Core(TM) i7-4790K CPU @ 4.40GHz

## Resultados

### Parte 1 - Árboles de búsqueda
Para esta parte del proyecto se implementó el algoritmo de iterative deepening depth first search debido a las ventajas que proporciona en espacio de memoria a la hora de realizar la búsqueda dado a que solo necesita guardar la rama actual. El tiempo de corrida para cada problema con pruning y sin pruning fue de 15 minutos y no existió algún tipo de problema durante esta fase.

En general se pudo observar durante esta parte uno del proyecto que al utilizar el pruning generaba como consecuencia que el factor de ramificación disminuyera notablemente para casi cualquier problema, cabe destacar que para el caso de las Torres de Hanoi no, es decir, se mantienen cercanas las cifras por nivel de profundidad del factor de ramificación para el caso de poda y sin poda, pero la cantidad de nodos expandidos siempre fue menor en los casos en los que se aplicaba pruning como era de esperar.

Los datos relacionados a los árboles de búsqueda para cada problema se encuentran dentro la carpeta “Resultados Corridas”, en ella se suministran las tablas con toda la información relacionada a la cantidad de nodos generados por profundidad y su factor de ramificación.

### Parte 2 - Heurísticas (Manhattan/PDBs)

1. N-puzzles:
    - 15 Puzzle:
        - Para la distancia de Manhattan se implementó la versión II vista en clase, la cual guarda las distancias de cada tile a cualquier otra posición en el tablero.
        - Se generó una PDB aditiva utilizando tres abstracciones donde cada una está compuesta por 5 tiles con costo uno que solo pueden aparecer en una de las abstracciones y el blanco que era el único elemento que se repetía entre los tres conjuntos. El resto de los elementos que no tienen costo uno se toman como iguales dentro de las misma abstracción y poseen costo cero.
    - 24 Puzzle:
        - Para esta parte se intentó implementar una PDB aditiva de 4 abstracciones de seis elementos cada una, pero no pudo ser creada dada la magnitud de memoria que requería, por lo que se procedió a crear una PDB de 6 abstracciones de cuatro elementos cada una.

2. Cubo de Rubik
    - 3x3x3:
        - Para este problema se planteó el máximo de diferentes PDBs los cuales estaban compuestos por una corner PDB y dos edges PDB. La base de datos de patrones corner contiene todas las caras que se encuentran en una esquina del cubo de Rubik, por otro lado las de edges contienen cada una la mitad de edges cubies, es decir seis y seis. Al final no se logró generar la PDB para este problema dado al gran espacio en memoria que consume dicha representación.

3. Top Spin
    - Para cada una de las partes de este problema se implementó el máximo de dos PDB las cuales utilizan el mapeo de varias fichas por otra fija con el fin de simplificar el modelo del problema.

4. Tor

re de Hanoi
- Para cada una de las partes de este problema se implementó el máximo de dos PDB las cuales utilizan la proyección de varias variables de estados con el fin de simplificar el modelo del problema.

### Parte 3 - Algoritmos informados

Para esta parte del proyecto se implementaron los algoritmos de A* e IDA* con el fin de realizar las búsquedas sobre los problemas planteados en el enunciado utilizando las heurísticas respectivas para cada uno de los casos.

1. N-puzzles:
    - 15 Puzzle:
        - Con la heurística Manhattan, en el algoritmo IDA* los resultados coincidieron con los ya mostrados en el archivo de korf con soluciones, dado en el enunciado del proyecto. Sin embargo, con A* no se pudo generar ninguna solución, a pesar de haberlo dejado bastante tiempo ejecutándose, y a pesar de que esta heurística no consume mucho espacio de memoria.
    - 24 Puzzle:
        - Para esta sección se lograron generar las PDB, pero al momento de ejecutar este problema con las distintas implementaciones a pesar de haber dejado un tiempo considerable los algoritmos ejecutándose, con ninguna de las implementaciones se logró obtener las soluciones a dicho problema.

2. Cubo de Rubik
    - 3x3x3:
        - No se pudo ejecutar esta parte dado a que no se pudo generar la PDB debido a la alta demanda de las abstracciones propuestas.

3. Torre Spin:
    - Para este problema en general fue mejor opción IDA* exceptuando el caso de 17-4 con el cual A* obtuvo un mejor desempeño, cabe destacar que en general se observó a través de los resultados obtenidos que A* también genera notablemente menos nodos por segundo que IDA*.
        - 12-4: Se lograron resolver sin ningún problema los casos de prueba propuestos y generados con ambas implementaciones.
        - 14-4: En general IDA* fue notablemente más rápido en esta sección que A* obteniéndose una gran diferencia entre los tiempos de ejecución de ambas implementaciones, cabe destacar que para A* no se pudo solucionar el caso 3 de d=2000 ya que consumió los recursos de la computadora.
        - 17-4: En esta sección se obtuvó que A* es notablemente más rápido resolviendo estas instancias de los problemas que IDA*. Por otro lado también se pudo observar que la magnitud de nodos por segundo que A* genera se encuentra aproximadamente entre la mitad y un tercio de lo que genera IDA*.

4. Torre de Hanoi:
    - En este problema se pudo observar que A* generaron menos nodos por segundos de lo que generó IDA* en las corridas de dichos casos de prueba, por otro lado el tiempo de ejecución por parte de A* es sustancialmente menor comparado al que toma IDA* para este problema.
        - 12d-4p: En A* con d=2.000.000 no se pudo resolver el caso 009, porque consumió todos los recursos. Por otro lado IDA* no pudo resolver los casos para d=2.000 y d=2.000.000.
        - 14d-4p: Para A* se lograron resolver las distintas instancias, pero

para IDA* no se lograron resolver para d=2.000 y d=2.000.000.
- 18d-4p: Para esta parte A* se logró resolver las distintas instancias excepto para d =2.000.000 y para IDA* no se lograron resolver las instancias d=2.000 y d=2.000.000.

### Conclusión

Pudo observarse que en los casos de prueba en los que se espera que la profundidad de la solución sea alta, el algoritmo A* fue más rápido que IDA*. De hecho, en algunos casos no se pudo generar una solución con IDA*, porque tardaba demasiado, y hubo que abortar.

Pero también se apreció siempre que IDA* genera más nodos por segundo que A*, lo cual era de esperarse por el tiempo que tarda A* en actualizar la tabla de Hash.