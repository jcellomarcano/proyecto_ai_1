# Universidad Simón Bolívar

## Departamento de Computación y Tecnología de la Información

### Inteligencia Artificial I

#### Integrantes:

* Jesus Marcano, 12-10359

## Manual - Proyecto 1

El proyecto consta de las siguientes carpetas:

1. **Algoritmos-estructuras**: En esta carpeta se encuentran los siguientes archivos:
   * a) **A\_estrella.cpp**: Implementación del algoritmo A\*. Contiene la función main que lo ejecuta.
   * b) **IDA\_estrella.cpp**: Implementación del algoritmo IDA\*. Contiene la función main que lo ejecuta.
   * c) **IterativeDeepeningDFS**: Variación del algoritmo Iterative Deepening DFS en la que las funciones retornan void porque no buscan un estado goal. El propósito es recorrer las ramas de un árbol de búsqueda lo más profundo posible durante 15 minutos para responder a la parte 1 del proyecto.
   * d) **node.hpp**: Definición de la clase para crear los nodos que contienen los estados del problema a tratar. Se utiliza en el algoritmo IDA\*.
   * e) **priority\_queue.hpp**: Copia del mismo archivo que viene implementado por psvn.
2. **bin**: Carpeta ya implementada por psvn. Contiene el ejecutable psvn2c, que es el compilador de psvn. Para crearlo, es necesario ejecutar "make" en la carpeta más externa del proyecto.
3. **global**: Copia de la carpeta del mismo nombre que viene con psvn.
4. **src**: Copia de la carpeta del mismo nombre que viene con psvn.
5. **Problemas**: Dentro de esta carpeta se encuentran las subcarpetas correspondientes a los problemas a tratar: Npuzzle, CuboRubik, TopSpin y TorresHanoi. Si se desea ejecutar los algoritmos A\* o IDA\* para un problema específico, se debe acceder a la subcarpeta correspondiente en el terminal. Por ejemplo, para ejecutar el 15-puzzle con la heurística Manhattan, se debe acceder a: Problemas > Npuzzle > 15puzzle > H\_Manhattan. Una vez allí, se encuentra un archivo llamado INSTRUCCIONES que indica los pasos para generar los algoritmos A\* e IDA\* específicos para ese problema. Lo mismo ocurre con los otros casos. Cada subcarpeta correspondiente a un problema siempre contendrá un archivo INSTRUCCIONES similar, un makefile, el o los archivos de prueba a ejecutar, el archivo .psvn que define el problema, los archivos .txt con las abstracciones necesarias para crear una base de patrones (si corresponde), etc. Todos estos archivos se encuentran mezclados en una misma carpeta para que el usuario no tenga que buscar en otros lugares los archivos necesarios para realizar la ejecución.

Es importante tener en cuenta que el archivo INSTRUCCIONES no especifica cómo generar el algoritmo Iterative Deepening DFS, pero de todas formas, dentro de la subcarpeta correspondiente al problema, se debe realizar lo siguiente:

`make <nombreProblema>.IDDFS`

Donde "nombreProblema" debe ser el mismo nombre que tiene el archivo .psvn que define el problema. Por ejemplo, para el 15-puzzle, se haría "make 15-puzzle.IDDFS" y luego se ejecutaría con "./15-puzzle.IDDFS". Antes de ejecutar el make, es necesario dirigirse al archivo makefile y cambiar manualmente la variable "fwd\_history\_len" por 1 si se desea una poda parcial de duplicados, o por 0 si no se desea poda. Por defecto, este valor está en 1 y debe mantenerse así al ejecutar los algoritmos A\* e IDA\*.

En algunos casos, los archivos de prueba fueron generados por nosotros mismos, con 10, 200, 500, 1000, 10000, 100000 y 1000000 aplicaciones de las reglas a partir del estado goal.

6. **ResultadosCorridas**: Aquí se encuentran todos los resultados de las ejecuciones de los algoritmos, incluyendo un archivo con los resultados de la pregunta 1. Para el resto de los problemas, hay una carpeta con el nombre correspondiente al problema a tratar.
