Bitacora:

|-- Avance #1 --|

En esta primer entrega, se define el primer borrador de los tokens, gramatica, y los diagramas del mismo.


|-- Avance #2 --|

En el segundo avance, se implementaaron los tokens y la gramatica definida usando PLY.
Ademas, se crearon las clases SymbolTable (directorio de variables) y FunctionDirectory (directorio de funciones).
Se implementaron de manera inicial; Es posible declarar y definir variables en el scope global, las cuales se gaurdan con su tipo y valor en una SymbolTable.
Tambien es posible declarar funciones en el scope global, las cuales se guardan con su tipo y ID en una FunctionDirectory.
Ademas, al momento de declararlas, se genera un scope para sus parametros y variables en la SymbolTable, las cuales tambien se declaran y guardan apropriadamente.

Para probar: python main.py (usar simpler_nuca.txt como input)
