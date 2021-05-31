**

# NucaScript

A strongly-typed, string manipulation and file I/O centered language that uses python and PLY to compile down to a C++ virtual machine, generating an executable output of the program without the need for an intermediate object code file.

Developed in about 10 weeks as the final project of the Compiler Design class at ITESM.

## Dependencies

python 3.7.4 (+)
g++11 (+)

## **Basic Program Structure:**

    /*/ This is a comment! Comments are always multiline /*/

    program NUCA; /*/ Sets the program name, which is as the default path for the out after compilation /*/

    /*/ After the program name, the user may declare variables, methods and classes in any order he wishes to /*/

    i, j, k, arr[50] : int;   /*/ Declaration of four int variables, the latter being an array with size 50 /*/
    matrix[3][3][3] : float;  /*/ Declaration of a 3x3x3 matrix of floating point values /*/

    void say_hello(name : string) /*/ Declaration of a global void method that takes in a string argument /*/
    VARS{} /*/ Local variables can be defined for each method in the same manner that they are globally, inside the VARS{} section. This method has no global variables /*/
    {
      println("Hello,", name);
      /*/ If the last statement of a method's body is not a return statement, it automatically assumes a 'return;', which works in this case since the method is of void type /*/
    }

    class Class{ /*/ A class definition has two parts: attributes and methods, and it cannot contain other objects as attributes (no compound objects) /*/
      ATTR{
        n : int; /*/ All class attributes are public! /*/
      }

      int get_n()
      VARS{}
      {
        return this.n;      /*/ All class attributes must be access via the 'this.' operator /*/
      }

      void set_n(n : int)
      VARS{}
      {
        this.n = n;         /*/ That allows this kind of stuff /*/
      }

    }

    obj : object; /*/ Here we declare an object type variable, which can be instantiated to any class type /*/

    /*/ After all of the declarations, comes the main method, where the program will start its execution /*/
    main(){
      obj = new Class(); /*/ obj will now be a fresh instance of Class /*/
      print(">> Enter an integer\n-- ");
      read(i); /*/ Stores user input (from the console) into i /*/
      obj.set_n(i); /*/ Call to an object method /*/
      println(obj.get_n()); /*/ To confirm it works! /*/

      /*/ There are many more cool things one can do with NucaScript! Check out the full documentation document on the official git repository to learn more! /*/
    }

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

|-- Avance #7 --|

Se implementaron la generacion de cuadruplos y ejecucion en maquina virtual para arreglos y para objetos (excluyendo arreglos como atributos de objetos)

|-- Avance #8 --|

Se implementaron una variedad de builtin-methods como open, write, stoi, stof, stod, y substr, ademas de constantes booleanas como True y False;
Tambien se implementaron las keywords 'using as' para el manejo de tipos de objetos, lo que posibilita listas de tipo objeto.

Para probar:
            python nuca_script.py simplest_nuca.nuca -o simplest_nuca (compila)
            simplest_nuca.exe (corre el programa compilado)
