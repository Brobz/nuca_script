# NucaScript

An object-oriented, strongly-typed, syntactically _"C-esque"_ and semantically _"pythonesque"_ string manipulation and file I/O centered language that uses python and PLY to compile down to a C++ virtual machine, generating an executable output of the program -- without the need for an intermediate object code file during runtime.

Version 1.0 developed in about 10 weeks as the final project of the Compiler Design class at ITESM.

### **Current Version:** 1.7.0

Check out the latest changes & version history in the [official NucaScript Version Log!](VERSION_LOG.md)

# **NucaScript 101 : The Official Docs**

## **Dependencies**

python 3.7.4 (+)

g++ 8.1.0 (+)

## **Environment Setup**

To get started with NucaScript, the first step is to make sure you have all of the dependencies properly installed in your working environment;

You can run the following commands to double check:

Python version check:

    python --version

g++ version check:

    g++ --version

Once this is done, you can proceed by cloning this repository:

      git clone https://github.com/Brobz/nuca_script

## **Hello World!**

Now that we are done with the setup, let's get a hello world going!

    touch tutorial_nuca.nuca

First, we'll lay down the most basic structure for a (compilable) NucaScript program:

    program TUTORIAL_NUCA;

    main () {

    }

This is the bare minimun a NucaScript file must contain: a program name, which will be used as the default file name for the executable output of the program; and a main method, where the program will start its execution.

If everything was setup correctly, you should be able to compile this program like so:

    python nuca_script.py tutorial_nuca.nuca

This should parse the source file `tutorial_nuca.nuca` and compile it into an executable called `TUTORIAL_NUCA` (our specified program name)
**Note:** If you want to change the output file name, you can pass in an output parameter like this:

    python nuca_script.py tutorial_nuca.nuca -o output_file_name

To run the program, simply write a ./ followed by the output file name:

     ./TUTORIAL_NUCA

Of course, the execution result is... Nothing!
But thats all we need to make Something happen!

    program TUTORIAL_NUCA;

    main () {
        println("Hello World!");
    }

There we go, our Hello World in NucaScript is complete!
This just uses a `println` statement with a constant string as a paramater, and of course, MOST of the statements in NucaScript must end in a semicolon.

Note: Don't forget to save and recompile your program everytime you make a change, or else it will not be reflected in the executable output!

## **Variables and Types**

Next up, variables! Handy strong-typed data containers identified by a unique name.

    program TUTORIAL_NUCA;

    i, j, k : int;
    pi, phi : float;
    result, color: string;
    state, derived_state : boolean;

    main () {
    	println("Hello World!");
    }

These variables are all declared as _global_ variables, and can be accessed from anywhere inside our program!
All variables must be declared previous to their reference, denoting both their type and their id:

    var_name : type;

It is possible to declare multiple variables of the same type in one statement, separating the variable names with commas:

    var_name_1, var_name_2 : type;

There are four basic types in NucaScript:

- `Int`
  -> A natural number (internally representend as a C++ long long)

- `Float`
  -> A real number (internally represented as a C++ long double)
- `String`
  -> A sequence of characters (internally represented as a C++ string)
- `Boolean`
  -> A binary value that can be either True or False (internally represented as a C++ bool)

Note that any and all declarations of all types must be done **before** the main method definition!

There is also the `void` type, which is only used for functions, and a special `object` type, but more on that later : )

## **Basic Logic and Arithmetic**

NucaScript supports all of the basic arithmetical and logic operators, and a couple more!
Note: Anything in between a pair of `/\*/` is considered a comment, and is ignored by the compiler.

    main () {
        println("Hello World!");

        i = 10;                       /*/ A single = assigns the value on the right side to the variable on the  left side /*/
        j = 10 * 5 / 5;
        k = i * j + (10 / 2) - 5;     /*/ Variables can be used in expressions just like any other constant /*/

        pi = 3.14 + 0.0015;
        phi = 0.16180 * 10;

        color = "blue";               /*/ String constants go inside "" /*/
        result = "the result is:";

        state = False; /*/ This could also be FALSE, false or simply a 0 /*/
        derived_state = (state || TRUE) && (true || (0 > 1)); /*/ Standard c-style logical operators! /*/

    	println(i, j, k);
    	println(pi, phi);
    	println(color, result);
    }

Expressions are calculated using normal mathematical precedence, and comparative operators all share the same importance (meaning they will be executed in order, so make sure to have your parenthesis in the right spot!)

Just be careful with the type semantics; You can do almost any operation that makes sense between all of the types, but some of them are still ill-defined!

For complete details on all of the operations between types and how they are defined, please take a look at the Compiler/SemanticCube.py file within this repository.

## **User Input and Control Flow**

To get user input from the console, you can use the builtin method `read`, which can take in any amount of variables separated by commas, and will prompt the user for input for each of those variables, storing the retrieved value within them.

    print(">> Enter an integer: "); /*/ Unlike println, print does not add a newline at the end of its parameter list! /*/
    read(k);
    println(">> You entered: " + k);

Of course, this may throw a runtime exception if the user input string cannot be converted to the destination variable type!

Now that we can get user input, an `if` statement would be very nice:

    if (k < 0) {
        println(">> It is less than zero!");
      } else if (k == 0){
        println(">> It is exactly zero!");
      } else {
        println(">> It is bigger than zero!");
      }

An `if` statement is used to decide which code section to run based on a boolean expression; If the expression within the parenthesis evaluates as `True`, the code within the curly braces ( `{` and `}` ) will be run;
If it evaluates as `False`, the program will jump its execution to after the braces and keep going.

You can have as many `if` and `else if` as you would like on a chain, however there can only be one `else`, and it wil forcefully denote the end of the conditional chain.

## **Arrays**

This is where it starts to get interesting!
NucaScript supports homogenous lists of variables with a constant and fixed size, decided on declaration:

    int_arr[10] : int;

This will declare an array of 10 ints called `int_arr`, and just like regular variables, all of them are initialized to 0 (or "" in the case of strings)

To access these values, you can simply use the bracket operator:

    int_arr[0] = 5;
    int_arr[5 + 4] = 10;

    println(int_arr[0], int_arr[9]);

All of the array elements are 0-indexed, meaning the first element will be found at index 0 and the last element at index `array_size - 1`.

Be careful not enter a negative number or a number that is bigger than the index of the last element, for it will throw an `Array Out of Bounds` runtime exception!

Arrays can also have multiple dimensions, which is very useful for modeling matrices and other cool things:

    float_matrix[3][3][3] : float;

This will create a 3x3x3 matrix of floating point numbers, and it can be accessed in very much the same way as a linear array:

    float_matrix[0][0][0] = 5; /*/ The first element of the first row of the first column /*/
    float_matrix[1][2][0] = 10; /*/ The first element of the third row of the second column /*/

    println(float_matrix[0][0][0], float_matrix[1][2][0]);

Arrays can have any number of dimensions with any size you want, just be careful not to exceed the compiler's variable limit of 30000 per type!

## **Loops**

You might be wondering how to quickly print out all of the values of an integer array with size 100 without writing either one gigantic line or 100 individual `print` statements...

Loops, my friend!
One of the most essential tools on the programmer's toolkit, these bad boys will not only allow you to perform actions that before seemed unachiavable, they can also do it in very few lines of code!

The most basic loop in NucaScript is what is commonly referred to as a `while` loop:

    i = 0;

    println(">> Entering whileloop!");

    while (i < 10){
       println(">> Inside while loop! i is now: " + i);
       i += 1; /*/   The += operator is short for "add to this value and overwrite it afterwards"
                     It is the same as writing i = i + 1, and this is valid for all of the 4
                     basic arithmetic operators:  +, -, * and /                               /*/
    }

    println(">> All done with the while loop!");

The `while` loop will repeat the code segment within its curly braces until the expression inside the parenthesis is no longer `True` (or it might never even run the code inside the braces, if the expression was never `True` in the first place)

Be careful with these, since it is very easy to get the condition wrong or to forget your increment statement (the one inside the loop that will eventually caused the condition value to flip) and get your program stuck in an infinite loop!

If it happens to you, remember, stay calm and just hit _CTRL + C_ on your console window to interrupt the execution of the program : )

NucaScript also has another type of loop, commonly known as a `for` loop:

    println(">> Entering for loop!");

    for (i = 0; i < 10; i++){ /*/ This syntax (i++) simply increments the value of i by 1 /*/
      println(">> Inside for loop! i is now: " + i);
    }

    println(">> All done with the for loop!");

This loop type takes in three statements, in order, and separated by semicolons:

- Initialization Statement

-> This statement is only processed once, the first time that the program hits the loop; It is used to set the initial value for the counter variable.

    i = 0;

- Exit Condition Statement

-> This statement is processed every time the loop is about to restart, and if it evaluates as True, it will indeed continue looping the section within the curly braces; If it is false, however, it will jump to after the curly braces.

    i < 10;

- Increment Statement

-> This statement is processed after every loop iteration, before checking the condition statement again, and serves the purpose of modifying our counter variable so that the loop condition may eventually flip, and the program will be free from the loop!

    i++; /*/ This syntax simply increments the value of i by 1 /*/

`for` loops are very useful when looping through arrays, or when performing a number of operations that is defined by other constants:

    for (i = 0; i < 10; i++){
       int_arr[i] = i;
       println(">> arr[" + i + "] = "  + i);
    }

Once again, be mindful of the statements that define the loop so that you don't end up with an infinite loop problem!

## **Functions**

Writing all of our code on the `main` method can become a hassle after some time, especially when we need to reuse the same bits of code over and over to perform our calculations.

This can be easily solved with the use of functions!
A function is a modularized block of code with its own local variables that only mean something inside of this block. It can also take in parameters and return values, just like in mathematics!

To declare a function in NucaScript, first we must declare its type, followed by its unique ID and whatever parameters it might take in:

    int double(n : int)

This declares a function called double, that will take in an integer value and return an integer value.
Next we need to declare this function's local variables:

    VARS {
        local_int : int;
    }

As you can see, it's just like declaring global variables!
We won't really be using any local variables in this function, so we can leave this section empty:

    VARS {}

Next we need to define the body of our function, which will contain the code that will be executed whenever we call it:

    {
      return n * 2;
    }

The `return` statement will be responsible for... uh... _returning_ this function's value after its execution!
It automatically leaves the function context and returns to where the function was previously called, placing its value on the correct spot.

In this case, all our function does is take in an integer, and return its value multiplied by 2.

Be careful with function types! If you return something that is not of the same type that you declared the function as, you will get a Type Mismatch exception at compile time!

Our complete function looks like this:

    int double(n : int)
    VARS {}
    {
      return n * 2;
    }

And we can call it like this:

    println(">> 10 doubled is: " + double(10));

Note that every NucaScript function assumes an empty `return` as the last statement of the function body, in the case that it is not already a `return` statment.

This means that this:

    int double(n : int)
    VARS {}
    {
    }

Is in reality interpreted by the compiler as this:

    int double(n : int)
    VARS {}
    {
        return;
    }

Which will throw a Type Mismatch exception at compile time, since this empty return is of type `void` (no value) and the function expects an int !

You can always declare your functions as `void` type if they don't return anything, of course!
Just like they can also be defined without any parameters to take in.

Note: as of NucaScript 1.0, functions cannot yet take in neither object type parameters nor arrays. Don't worry though, there are plenty of ways around it, and a future update will allow this to happen! (hopefully)

## **Classes**

This is where the fun really begins!

Classes are a way of structuring variables and functions together in one neat little package, and we can store its information inside of variables that have the `object` type.

NucaScript objects **cannot** be _compounded_; This means that a class declaration cannot contain any variable of `object` type.

Don't worry, they are still very useful!
To declare a class, we start by using the class keyword, followed by the class name and our favorite braces, the curlies:

    class MyClass{

    }

Next we need to tell the compiler what variable attributes this class will contain.
All of the class attributes are public in NucaScript!

    class MyClass{
      ATTR{
          class_int : int;
          class_string_arr[10] : string;
      }
    }

These variables will only be available to an object of this class, and each object will have its own set of them!
We can also give our class its own functions:

    class MyClass{
      ATTR{
          class_int : int;
          class_string_arr[10] : string;
      }

      void print_class_int()
      VARS{
          class_int : int; /*/ This is a local variable, and is different from the class attribute var with the same name! /*/
      }
      {
          /*/ We can use the this. operator to identify between class variables and global / local ones /*/
          println(">> Local int is: " + class_int);
          println(">> Class Int is: " + this.class_int);
      }
    }

As you can see, the this. operator is of mandatory use to denote the use of any class attribute within its own scope.

If it is not used, the compiler will search everywhere besides the class attributes, so be careful!

Now that we have our class well defined, we can declare an `object` variable and _instantiate_ it as MyClass!

    obj_var : MyClass;

In NucaScript, all object variables **must** specify their class type upon declaration, and are automatically instantiated for their scope.

This class type **cannot** be changed, and trying to instantiate an object variable to a different class type to the one declared will result in a Type Error!

But what is instantiating, you ask, puzzled?

It's when we tell the compiler to generate a new instance of all of the class attributes we defined and store them inside the instantiated variable! Like this:

     obj_var = new MyClass();

To instantiate, we use the `new` keyword, followed by the class name as if it was a parameterless function call.

This will basically wipe out the objects state, and set all of its variables to the default values!

Of course, this is done automatically for us at the start of the variables scope, so there is no reason to explicitly instantiate an object until we have actually modified its values.

We can now access all of the goodies that come with this class with the . operator, like so:

    obj_var.class_int = 10;
    obj_var.class_string_arr[5] = "Hi!";
    obj_var.print_class_int();

So convenient!
Imagine what we could do with a bunch of objects in an array...

Correct, many things! Great things!

## **#DEF Statements**

Since version 1.4, NucaScript allows for C-like `#DEF` statements!!
These MUST come right after the program name definition, and before anything else!
You can have any amount of them as you would like (including none), and it works for all of the basic data types.
These work by substituting the actual source code that gets parsed in real time, just like in good old C!
Here's an example, taken from `Examples/example_nuca.nuca` on this very repository:

    program EXAMPLE_NUCA;

    #DEF CONSTANT_INT : 5
    #DEF TABULATOR : "\t"
    #DEF CONSTANT_FLOAT : 5.54
    #DEF CONSTANT_STATE : FALSE

    ...

    println("HI" + TABULATOR * CONSTANT_INT + CONSTANT_FLOAT * 2);

As you can see, it is as easy as writing the `#DEF` keyword, the definition name, a semicolon, and then the value to be replaced by the name.
After that, you are ready to use it in the code, making it super easy to get rid of pesky _magic numbers_, such as array sizes!

P.S & TODO: Be careful with these, since they **WILL** (_currently_) replace **ANY** instance of the definition name inside of the code, **INCLUDING** ones that are inside of a string (in between quotations). I know, pretty unintuitive behavior... Already working on a _lazy_ fix, so stay tuned : )

## **Builtin Methods**

NucaScript 1.0 shipped with a variety of useful builtin methods, with more coming in a constant stream (hopefully)
Here are all of the currently available builtin methods for NucaScript:

- `int stoi(s : string)`
  --> Takes in a string, and if possible, returns its conversion as an int
- `float stof(s : string)`
  --> Takes in a string, and if possible, returns its conversion as a float
- `boolean stob(s : string)`
  --> Takes in a string, and if possible, returns its conversion as a boolean
- `string substr(s : string, sarting_index : int, size : int)`
  --> Takes in a string s, a starting index (int) and a size (int), and returns the appropriate substring of s, from starting_index up to starting_index + size (inclusive on both ends)
- `int strlen(s : string)`
  --> Takes in a string, and returns the length of the string (total number of characters) as an integer value
- `int randint(lower_bound : int, upper_bound : int)`
  --> Takes in two ints: a lower and an upper bound, and returns a pseudo-randomly generated integer ranging from _lower_bound_ to _upper_bound_ (inclusive on both ends)
- `void open(buffer : string[],  file_path : string, separator : string)`
  --> Takes in linear string array as a _buffer_, a string as _file_path_ and a third string as _separator_. Opens and parses the file at _file_path_ (relative to the executable's directory at the moment of execution) using the _separator_ (or untill it reaches a \n character) and writes the data into the _buffer_.
  Note: The _buffer_ must be passed in with no bracket operators, and must have enough space to contain all of the file data, or else the VM will throw a Buffer Overflow error. If the file ends and there is still space left in the buffer, a "END_OF_STREAM" entry will be added at the end.
- `void write(buffer : [], file_path : string, separator : string)`
  --> Takes in any linear array type (except object) as a _buffer_, a string as _file_path_ and a second string as _separator_. Writes all of the entries from the _buffer_ into the file at _file_path_, with a _separator_ in between each entry, creating the file if it does not previously exist. If the buffer contains an "END_OF_STREAM" entry, output to the file will be stopped at that point.

## **That's It!**

You now know pretty much everything there is to know about NucaScript!
Fell free to contact me if you find any bugs or typos : )

Have fun creating!

Gui.
