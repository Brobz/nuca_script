Bitacora:

|-- Avance #1 --|

En esta primer entrega, se define el primer borrador de los tokens, gramatica, y los diagramas del mismo.


|-- Avance #2 --|

En el segundo avance, se implementaaron los tokens y la gramatica definida usando PLY.
Ademas, se crearon las clases SymbolTable (directorio de variables) y FunctionDirectory (directorio de funciones).
Se implementaron de manera inicial; Es posible declarar y definir variables en el scope global, las cuales se gaurdan con su tipo y valor en una SymbolTable.
Tambien es posible declarar funciones en el scope global, las cuales se guardan con su tipo y ID en una FunctionDirectory.
Ademas, al momento de declararlas, se genera un scope para sus parametros y variables en la SymbolTable, las cuales tambien se declaran y guardan apropriadamente.


|-- Avance #3 --|

En el tercer avance, se implemento la generacion del codigo intermedio (cuadruplos) para estatutos sencillos: expresiones aritmeticas y comparativas, ademas de asignaciones.
Ademas, se implemento el cubo de semantica para asegurar de que no haya errores de tipo.


|-- Avance #4 --|

En el cuarto avance, se implemento la generacion de codigo intermedio (cuadruplos) para estatutos no lineales, como ciclos while y for. Ademas, se completo la generacion para expresiones sencillas,
como los estatuos de READ y WRITE.

|-- Avance #5 --|

En el quinto avance, se implemento la generacion de codigo intermedio (cuadruplos) para metodos y funciones, tanto en su definicion cuanto en su llamada.

|-- Avance #6.a (15/05/2021) --|

En el sexto avance, se implemento una version inicial de la maquina virtual, escrita en C++;
El compilador (nuca_script.py), al terminar de generar el codigo intermedio, escribe toda la informacion necesaria para la ejecucion del programa en el archivo de la maquina virtual,
y posteriormente lo compila, generando asi un ejecutable final.
Por el momento, solo se implemento la ejecucion de los operadores GOTO y =.

|-- Avance #6.b (16/05/2021) --|

Se implementaron la ejecucion en maquina virtual de expresiones aritmeticas, condicionales y ciclos en su totalidad, ademas de estatutos sencillos como lecturas (read) y escrituras (print y println).
Para probar:
            python nuca_script.py simplest_nuca.nuca -o simplest_nuca (compila)
            simplest_nuca.exe (corre el programa compilado)
