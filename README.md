
# NucaScript

A strongly-typed, syntactically *"pythonesque"* string manipulation and file I/O centered language that uses python and PLY to compile down to a C++ virtual machine, generating an executable output of the program without the need for an intermediate object code file.

Developed in about 10 weeks as the final project of the Compiler Design class at ITESM.

## List of Dependencies

python 3.7.4 (+)

g++ 8.1.0 (+)

# **NucaScript 101 : The Official Docs**

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

    touch example_nuca.nuca

First, we'll lay down the most basic structure for a (compilable) NucaScript program:

    program EXAMPLE_NUCA;

    main () {

    }
This is the bare minimun a NucaScript file must contain: a program name, which will be used as the default file name for the executable output of the program; and a main method, where the program will start its execution.

If everything was setup correctly, you should be able to compile and run this program like so:

    python nuca_script.py example_nuca.nuca
    ./EXAMPLE_NUCA

Of course, the execution result is.. Nothing!
But thats all we need to make Something happen!

    program EXAMPLE_NUCA;

    main () {
	    println("Hello World!");
    }
There we go, our Hello World in NucaScript is complete!
This just uses a println statement with a constant string as a paramater, and of course, MOST of the statements in NucaScript must end in a semicolon.

Note: Don't forget to save and recompile your program everytime you make a change, or else it will not be reflected in the executable output!

## **Variables and Types**

Next up, variables! Handy strong-typed data containers identified by a unique name.

    program EXAMPLE_NUCA;

    i, j, k : int;
    pi, phi : float;
    color, size: string;
    state : boolean;

    main () {
    	println("Hello World!");
    }
These variables are all declared as *global* variables, and can be accessed from anywhere inside our program!
All variables must be declared previous to their reference, denoting both their type and their id:

    var_name : type;

It is possible to declare multiple variables of the same type in one statement, separating the variable names with commas:

    var_name_1, var_name_2 : type;

There are four basic types in NucaScript:

 - Int
-> A natural number (internaly representend as a C++ long long)
 - Float
-> A real number (internaly represented as a C++ long double)
 - String
 -> A sequence of characters (internaly represented  as a C++ string)
 - Boolean
 -> A binary value that can be either True or False (internaly represented as a C++ bool)

Note that any and all declarations of any type must be done **before** the main method definition!

There is also a special *object* type, but more on that later : )

## **Basic Arithmetic**

NucaScript supports all of the basic arithmetic operations, and a couple more!
P.S: Anything in between  a pair of /*/ is considered a comment, and is ignored by the compiler.

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

		println(i, j, k);
		println(pi, phi);
		println(color, result);
    }


Expressions are calculated using normal mathematical precedence, and comparative operators all share the same importance (meaning they will be executed in order, so make sure to have your parenthesis in the right spot!)

Just be careful with the type semantics; You can do almost any operation that makes sense between all of the types, but some of them are still ill-defined!

For complete details on all of the operations between types and how they are defined, please take a look at the Compier/SemanticCube.py file within this repository.

## **User Input and Control Flow**

To get user input from the console, you can use the builtin method  *read*, which can take in any amount of variables separated by commas, and will prompt the user for input for each of those variables, storing the retrieved value within them.

	print(">> Enter an integer: "); /*/ Unlike println, print does not add a newline at the end of its parameter list! /*/
    read(k);
    println(">> You entered: " + k);

Of course, this may throw a runtime exception if the user input string cannot be converted to the destination variable type!

Now that we can get user input, an *if statement* would be very nice:

    if (k < 0) {
        println(">> It is less than zero!");
      } else if (k == 0){
        println(">> It is exactly zero!");
      } else {
        println(">> It is bigger than zero!");
      }

An *if statement* is used to decide which code section to run based on a boolean expression; If the expression within the parenthesis evaluates as True, the code within the curly braces  ( { and } ) will be run;
If it evaluates as False,the program will jump its execution to after the braces and keep going.

You can have as many ifs and else ifs as you would like on a chain, however there can only be one else, and it wil forcefully denote the end of the conditional chain.


## **Arrays**

This is where it starts to get interesting!
NucaScript supports homogenous lists of variables with a constant and fixed sized, decided on declaration:

    int_arr[10] : int;

This will declare an array of 10 ints called int_arr, and just like regular variables, all of them are initialized to 0 (or "" in the case of strings)

To access these values, you can simply use the bracket operator:

    int_arr[0] = 5;
    int_arr[5 + 4] = 10;

    println(int_arr[0], int_arr[9]);

All of the array elements are 0-indexed, meaning the first element will be found at index 0 and the last element at index array_size - 1.

Be careful not enter a negative number or a number that is bigger than the index of the last element, for it will throw an *Array Out of Bounds* runtime exception!

Arrays can also have multiple dimensions, which is very useful for modeling matrices and other cool things:

    float_matrix[3][3][3] : float;

This will create a 3x3x3 matrix of floating point numbers, and it can be accessed in very much the same way as a linear array:

    float_matrix[0][0][0] = 5; /*/ The first element of the first row of the first column /*/
    float_matrix[1][2][0] = 10; /*/ The first element of the third row of the second column /*/

    println(float_matrix[0][0][0], float_matrix[1][2][0]);

Arrays can have any number of dimensions with any size you want, just be careful not to exceed the compiler's variable limit of 30000 per type!

## **Loops**

You might be wondering how to quickly print out all of the values of  an integer array with size 100 without writing either one gigantic line or 100 individual *print* statements...

Loops, my friend!
One of the most essential tools on the programmer's toolkit, these bad boys will not only allow you to perform actions that before seemed unachiavable, they can also do it in very few lines of code!

The most basic loop in NucaScript is what is commonly referred to as a *while loop*:

    i = 0;

    println(">> Entering whileloop!");

    while (i < 10){
       println(">> Inside while loop! i is now: " + i);
       i += 1; /*/ The += operator is short for "add to this value and overwrite it afterwards"
			       It is the same as writing i = i + 1, and this is valid for all of the 4
				   basic arithmetic operators:  +, -, * and / 								/*/
    }

    println(">> All done with the while loop!");


The *while loop* will repeat the code segment within its curly braces until the expression inside the parenthesis is no longer True! (or it might never even run the code inside the braces, if the expression was never True in the first place!)

Be careful with these, since it is very easy to get the condition wrong or to forget your increment statement (the one inside the loop that will eventually caused the condition value to flip) and get your program stuck in an infinite loop!

If it happens to you, remember, stay calm and just hit CTRL + C on your console window to interrupt the execution of the program : )

NucaScript also has another type of loop, commonly known as a *for loop*:

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


    i++; /*/ This syntax simply increments the value of i by 1 /\*/

*For loops* are very useful when looping through arrays, or when performing a number of operations that is defined by other constants:

    for (i = 0; i < 10; i++){
       int_arr[i] = i;
       println(">> arr[" + i + "] = "  + i);
    }

Once again, be mindful of the statements that define the loop so that you don't end up with an infinite loop problem!

## **Functions**

Writing all of our code on the *main* method can become a hastle after some time, especially when we need to reuse the same bits of code over and over to perform our calculations.

This can be easily solved with the use of functions!
A function is a modularized block of code with its own local variables that only mean something inside of this block. It can also take in parameters and return values, just like in mathematics!

To declare a function in NucaScript, first we must declare its type, followed by its unique ID and whatever parameters it might take in:

    int double(n : int)

This declares a function called doubled, that will take in an integer value and return an integer value.
Next we need to declare this function's local variables:

    VARS {
	    local_int : int;
    }
As you can see, just like declaring global variables!
We won't really be using any local variables in this function, so we can leave this section empty:

    VARS {}

Next we need to define the body of our function, which will contain the code that will be executed whenever we call it:

    {
      return n * 2;
    }
The *return* statement will be responsible to.. uh.. return this functions value after its execution!
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

Note that every NucaScript function assumes an empty return as the last statement of the function body, in the case that it is not already a return statment;

This means that  this:

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
Which will throw a Type Mismatch exception at compile time, since this empty return is of type *void* (no value) and the function expects an int !

You can always declare your functions as *void* type if they don't return anything, of course!
Just like they can also be defined without any parameters to take in.

Note: as of NucaScript 1.0, functions cannot yet take in either object type parameters or arrays. Don't worry though, there are plenty of ways around it, and a future update will allow this to happen! (hopefully)

## **Classes**

This is where the fun really begins!

Classes are a way of structuring variables and functions together in one neat little package, and we can store it's information inside of variables that have the *object* type.

NucaScript objects **cannot** be *compound*; This means that a class declaration cannot contain any variable of *object* type.

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

Now that we have our class well defined, we can declare an *object* variable and *instantiate* it as MyClass!

    obj_var : object;
In NucaScript, all object  variables are of this general type, and take on the role of a specific class type one instantiated.

But what is instantiating, you ask, puzzled?

It's when we tell the compiler to generate a new instance of all of the class attributes we defined and store them inside the instantiated variable! Like this:

     obj_var = new MyClass();
To instantiate, we use the *new* keyword, followed by the class name as if it was a parameterless function call.

This will do two things: initiate the values like we talked about, and also *assert* this variable as having the MyClass type for the rest of this scope (unless re-instantiated to a different class type, of course).

This is useful for the compiler to know which attributes and methos are valid for this object variable to use.

We can now access all of the goodies that come with this class with the . operator, like so:

    obj_var.class_int = 10;
    obj_var.class_string_arr[5] = "Hi!";
    obj_var.print_class_int();
So convenient!
Imagine what we could do with a bunch of objects in an array...

Correct, many things! Good things. But to be able to do that, we'll need one extra piece of knowledge...

## **Class Type Assertion**

The *using as* keyword is used to assert the class type of an object variable (or a whole object array) without having to re-instantiate it, losing its current state in the process!

It works this way:
Imagine there is a global object variable *my_class*, which in the main is instantiated as a *MyClass* instance.
What if we want to access its values from within another function?
We could do something like this:

    void my_void()
    VARS{}
    {
      using my_class as MyClass; /*/ Asserts my_clas as instance of MyClass in this scope /*/
      println(my_class.class_int);
    }
So easy! Just tell the compiler we are *using* my_class *as* MyClass!
This makes the following statement valid, since class_int is indeed an attribute of this class type.
If the assertion was not there, there would be a Class Exception, since the compiler wouldn't know in which class type to check for the clas_int variable.

Be careful though, since this method will throw an error if the variable is either not yet instantiated, or instantiated to a different class type!

The assertion statement works similarly with object arrays, except that you **MUST** assert the array before instantiating any of its objects. Asserting an array also automatically instantiates all of the non-instantiated members for the sake of convenience. Yay!

Once again, if you assert an array that is already instantiated to a different class type, an error will ensue, so be careful!

Here is an example, supposing we have an object array called *objs*:

    objs[5] : object;

    int main (){
	    using objs as MyClass; /*/ Asserts and instatiates the array members as MyClass /*/
	    objs[0].class_int += 5;
	    objs[1].class_int += 5 * objs[0].class_int;
	    println(objs[0].class_int, objs[1].class_int);
    }
This keeps object arrays homogenous, just like we want them, and allows the compiler to know where to look for their values!

## **Builtin Methods**
