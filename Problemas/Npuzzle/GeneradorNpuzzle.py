#
# Archivo: GeneradorNpuzzle.py
#
# Descripción: Programa que pide un valor entero que representa el tamaño de un
#              lado del tablero (que es un cuadrado), y devuelve las reglas para
#              cada una de las casillas.
#
# 
# * Integrantes:
# *   - Jesus Marcano    (12-10359)
# *   - Daniel Figueroa  (16-10371)

def generarRegla(posIniBlanco, posIniX, limite):
    """ Entrada
        -------
        * posIniBlanco // Posición inicial del blanco
        * posIniX      // Posición inicial de la X, que es donde se quiere colocar
                          el blanco.
        * limite       // Cantidad de posiciones que existen en el tablero.
        Salida
        -------
        * cadena       // Cadena de caracteres que contiene la regla.
    """
    cadena = ""
    # Imprimir la parte izquierda de la regla
    for i in range(1,limite+1):
        if i == posIniBlanco:
            cadena += "0 "
        elif i == posIniX:
            cadena += "X "
        else:
            cadena += "- "
    cadena += "=> "
    # Imprimir la parte izquierda de la regla
    # (La posición del blanco se intercambia con la de la X)
    for i in range(1,limite+1):
        if i == posIniBlanco:
            cadena += "X "
        elif i == posIniX:
            cadena += "0 "
        else:
            cadena += "- "
    return cadena
	
def generarArchivo(dimensionTablero):
    """ * dimensionTablero // Por ejemplo, si es el 15-puzzle, hay 16 casillas
                              en total, lo que corresponde a una dimensión 4,
                              ya que 4x4 = 16.                                """

    totalCasillas = dimensionTablero**2
    # Última posición en la que se puede mover hacia abajo
    limiteMoverAbajo = totalCasillas-dimensionTablero 

    # Esta cadena guardará lo que posteriormente se escribirá en el archivo
    cadena = "# Archivo: "+str(totalCasillas-1)+"-puzzle.psvn\n\n"
    cadena += "DOMAIN d "+str(totalCasillas)+"\n       0 "
    for i in range(1,totalCasillas):
        cadena += str(i)+ " "
    cadena += "\n\n"+str(totalCasillas)+"\n\n"
    for i in range(1,totalCasillas+1):
    	cadena += "d "   	
    cadena += "\n\n"  

    # Ciclo para construir las reglas de todas las casillas
    for casilla in range(1,totalCasillas+1):
        cadena += "# Posición "+str(casilla)+"\n"
        # Caso en que el blanco se puede mover a la izquierda
        if casilla % dimensionTablero != 1:
            cadena += generarRegla(casilla,casilla-1,totalCasillas)
            cadena += "LABEL MOVER-"+str(casilla)+"-IZQUIERDA\n"
        # Caso en que el blanco se puede mover a la derecha
        if casilla % dimensionTablero != 0:
            cadena += generarRegla(casilla,casilla+1,totalCasillas)
            cadena += "LABEL MOVER-"+str(casilla)+"-DERECHA\n"
        # Caso en que el blanco se puede mover hacia abajo
        if casilla <= limiteMoverAbajo:
            cadena += generarRegla(casilla,casilla+dimensionTablero,totalCasillas)
            cadena += "LABEL MOVER-"+str(casilla)+"-ABAJO\n"
        # Caso en que el blanco se puede mover hacia arriba
        if casilla > dimensionTablero:
            cadena += generarRegla(casilla,casilla-dimensionTablero,totalCasillas)
            cadena += "LABEL MOVER-"+str(casilla)+"-ARRIBA\n"

        cadena += "\n"
        
    cadena += "\nGOAL 0 "  
    for i in range(1,totalCasillas):
        cadena += str(i)+" "

    # Archivo psvn a generar
    nombreArchivo = str(totalCasillas-1)+"-puzzle.psvn"
    archivo = open(nombreArchivo,"w")
    archivo.write(cadena)
    archivo.close()
    	
################################################################################
################### P r o g r a m a   P r i n c i p a l ########################
################################################################################

while True:
    try:
        dimensionTablero = int(input("Escriba la dimensión del tablero: "))
        generarArchivo(dimensionTablero)
        break
    except:
        print(">>>Debe proporcionar un valor entero\n")
    
    
    
    
	
		
		
	
	
