'''
----------------------------------------------------------------------------
|                                                                           |
|                     NucaScript                                            |
|                                                                           |
|                     Diseno de Compiladores - OBJ17                        |
|                     ITESM 2021                                            |
|                                                                           |
|                     Guilherme Bittencourt de Borba                        |
|                      A01194571                                            |
|                     Alvaro Fernando Santana Martinez                      |
|                      A01196914                                            |
|                                                                           |
----------------------------------------------------------------------------


----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// IDEAS FOR FUTURE IMPROVEMENT //

    OBJECTS:
        -> add special "constructor" and  "initializer" keywords for constructor methods
        -> have the constructor method run uppon using the "new" keyword; this method can have any amount of parameters
        -> have the initializer method run uppon declaring an array of objects of that type; this method cannot have parameters

    ARRAYS:
        -> add List methods! (upon accessing list variable name directly with a . operator, trigger search for special list methods!)
            -> size()!
            -> head()!
            -> tail()!
            -> find()! -> returns idx if in list, -1 otherwise !
            -> what to do with multidimentional arrays????
        -> optimize array access process by either reusing temps or having specific global temps for the process

    FUNCTIONS:
        -> default arguments?
        -> time-related builtin methods? (wait, exit, time, etc..)
        -> overloaded functions?

    OTHER:
        -> VSCode syntactic highliter ?
        -> try / catch block?
        -> post-compile quad optimization ?
        -> tmp management optimization (in Avail)?

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// VIRTUAL MEMORY MODEL //

||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    [0,                                                                                                        MAX_CONSTANTS - 1]                                                                               ->          Constant Ints
    [MAX_CONSTANTS,                                                                                            2 * MAX_CONSTANTS - 1]                                                                           ->          Constant Floats
    [2 * MAX_CONSTANTS,                                                                                        3 * MAX_CONSTANTS - 1]                                                                           ->          Constant Strings
    [3 * MAX_CONSTANTS,                                                                                        4 * MAX_CONSTANTS - 1]                                                                           ->          Constant Booleans

||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    [4 * MAX_CONSTANTS,                                                                                        4 * MAX_CONSTANTS + MAX_SYMBOLS - 1]                                                             ->          Global Ints
    [4 * MAX_CONSTANTS + MAX_SYMBOLS,                                                                          4 * MAX_CONSTANTS + 2 * MAX_SYMBOLS - 1]                                                         ->          Global Floats
    [4 * MAX_CONSTANTS + 2 * MAX_SYMBOLS,                                                                      4 * MAX_CONSTANTS + 3 * MAX_SYMBOLS - 1]                                                         ->          Global Strings
    [4 * MAX_CONSTANTS + 3 * MAX_SYMBOLS,                                                                      4 * MAX_CONSTANTS + 4 * MAX_SYMBOLS - 1]                                                         ->          Global Booleans
    [4 * MAX_CONSTANTS + 4 * MAX_SYMBOLS,                                                                      4 * MAX_CONSTANTS + 5 * MAX_SYMBOLS - 1]                                                         ->          Global Objects

||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    [4 * MAX_CONSTANTS + 5 * MAX_SYMBOLS,                                                                      4 * MAX_CONSTANTS + 5 * MAX_SYMBOLS + MAX_TMP_SYMBOLS - 1]                                       ->          Global Temp Ints
    [4 * MAX_CONSTANTS + 5 * MAX_SYMBOLS + MAX_TMP_SYMBOLS,                                                    4 * MAX_CONSTANTS + 5 * MAX_SYMBOLS + 2 * MAX_TMP_SYMBOLS - 1]                                   ->          Global Temp Floats
    [4 * MAX_CONSTANTS + 5 * MAX_SYMBOLS + 2 * MAX_TMP_SYMBOLS,                                                4 * MAX_CONSTANTS + 5 * MAX_SYMBOLS + 3 * MAX_TMP_SYMBOLS - 1]                                   ->          Global Temp Strings
    [4 * MAX_CONSTANTS + 5 * MAX_SYMBOLS + 3 * MAX_TMP_SYMBOLS,                                                4 * MAX_CONSTANTS + 5 * MAX_SYMBOLS + 4 * MAX_TMP_SYMBOLS - 1]                                   ->          Global Temp Booleans
    [4 * MAX_CONSTANTS + 5 * MAX_SYMBOLS + 4 * MAX_TMP_SYMBOLS,                                                4 * MAX_CONSTANTS + 5 * MAX_SYMBOLS + 5 * MAX_TMP_SYMBOLS - 1]                                   ->          Global Temp Objects

||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    [4 * MAX_CONSTANTS + 5 * MAX_SYMBOLS + 5 * MAX_TMP_SYMBOLS,                                                4 * MAX_CONSTANTS + 6 * MAX_SYMBOLS + 5 * MAX_TMP_SYMBOLS - 1]                                   ->          Local Ints
    [4 * MAX_CONSTANTS + 6 * MAX_SYMBOLS + 5 * MAX_TMP_SYMBOLS,                                                4 * MAX_CONSTANTS + 7 * MAX_SYMBOLS + 5 * MAX_TMP_SYMBOLS - 1]                                   ->          Local Floats
    [4 * MAX_CONSTANTS + 7 * MAX_SYMBOLS + 5 * MAX_TMP_SYMBOLS,                                                4 * MAX_CONSTANTS + 8 * MAX_SYMBOLS + 5 * MAX_TMP_SYMBOLS - 1]                                   ->          Local Strings
    [4 * MAX_CONSTANTS + 8 * MAX_SYMBOLS + 5 * MAX_TMP_SYMBOLS,                                                4 * MAX_CONSTANTS + 9 * MAX_SYMBOLS + 5 * MAX_TMP_SYMBOLS - 1]                                   ->          Local Booleans
    [4 * MAX_CONSTANTS + 9 * MAX_SYMBOLS + 5 * MAX_TMP_SYMBOLS,                                                4 * MAX_CONSTANTS + 10 * MAX_SYMBOLS + 5 * MAX_TMP_SYMBOLS - 1]                                  ->          Local Objects

||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    [4 * MAX_CONSTANTS + 10 * MAX_SYMBOLS + 5 * MAX_TMP_SYMBOLS,                                               4 * MAX_CONSTANTS + 10 * MAX_SYMBOLS + 6 * MAX_TMP_SYMBOLS - 1]                                  ->          Local Temp Ints
    [4 * MAX_CONSTANTS + 10 * MAX_SYMBOLS + 6 * MAX_TMP_SYMBOLS,                                               4 * MAX_CONSTANTS + 10 * MAX_SYMBOLS + 7 * MAX_TMP_SYMBOLS - 1]                                  ->          Local Temp Floats
    [4 * MAX_CONSTANTS + 10 * MAX_SYMBOLS + 7 * MAX_TMP_SYMBOLS,                                               4 * MAX_CONSTANTS + 10 * MAX_SYMBOLS + 8 * MAX_TMP_SYMBOLS - 1]                                  ->          Local Temp Strings
    [4 * MAX_CONSTANTS + 10 * MAX_SYMBOLS + 8 * MAX_TMP_SYMBOLS,                                               4 * MAX_CONSTANTS + 10 * MAX_SYMBOLS + 9 * MAX_TMP_SYMBOLS - 1]                                  ->          Local Temp Booleans
    [4 * MAX_CONSTANTS + 10 * MAX_SYMBOLS + 9 * MAX_TMP_SYMBOLS,                                               4 * MAX_CONSTANTS + 10 * MAX_SYMBOLS + 10 * MAX_TMP_SYMBOLS - 1]                                 ->          Local Temp Objects

||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    [4 * MAX_CONSTANTS + 10 * MAX_SYMBOLS + 10 * MAX_TMP_SYMBOLS,                                              4 * MAX_CONSTANTS + 10 * MAX_SYMBOLS + 10 * MAX_TMP_SYMBOLS + MAX_OBJ_SYMBOLS - 1]               ->          Object Ints
    [4 * MAX_CONSTANTS + 10 * MAX_SYMBOLS + 10 * MAX_TMP_SYMBOLS + MAX_OBJ_SYMBOLS,                            4 * MAX_CONSTANTS + 10 * MAX_SYMBOLS + 10 * MAX_TMP_SYMBOLS + 2 * MAX_OBJ_SYMBOLS - 1]           ->          Object Floats
    [4 * MAX_CONSTANTS + 10 * MAX_SYMBOLS + 10 * MAX_TMP_SYMBOLS + 2 * MAX_OBJ_SYMBOL,                         4 * MAX_CONSTANTS + 10 * MAX_SYMBOLS + 10 * MAX_TMP_SYMBOLS + 3 * MAX_OBJ_SYMBOLS - 1]           ->          Object Strings
    [4 * MAX_CONSTANTS + 10 * MAX_SYMBOLS + 10 * MAX_TMP_SYMBOLS + 3 * MAX_OBJ_SYMBOLS,                        4 * MAX_CONSTANTS + 10 * MAX_SYMBOLS + 10 * MAX_TMP_SYMBOLS + 4 * MAX_OBJ_SYMBOLS - 1]           ->          Object Booleans

||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// OBJECT MANAGEMENT //

    //|||\\ //|||\\ //|||\\ //|||\\ //|||\\ //|||\\ //|||\\ //|||\\ //|||\\

    -> Store class function quads just like any other function
    -> Create FuncDir scope and memory signature for each object type
    -> Create a THIS_MEM pointer in VM, which will be used to know which object's memory to use as the "this" referentiator inside class methods
    -> Uppon creating an object instance, generate a MemoryContext using the signature, and store it in this symbols mem (will need to have a Memory var in Value to store this)

    -> Similarly to arrays, objects quads will depend on where they are seen:
        - If an obj is seen on the left side of an assignment, we will use OBJ_WRITE
        - If an obj is seen on the right side of an assignment (as a factor), we will use OBJ_READ
        - If an obj calls a function, we will OBJ_GOSUB to that function, setting all of the  "this" to point to its memory context, so that the function can do OBJ_READS on it

    // OBJ_INST //
    Creates an instace of obj_sign signature and stores it into obj_addr
    | OBJ_INST | -1 | obj_sign | obj_addr (locl_mem) |

    // OBJ_READ //
    Reads from obj_var_addr in obj_addr's memory and writes it to result_addr (local_mem)
    | OBJ_READ | obj_addr (local_mem) | obj_var_addr (obj_mem) | result_addr (local_mem) |

    // OBJ_WRITE //
    Writes value_addr into obj_var_addr in obj_addr's memory
    | OBJ_WRITE | obj_addr (local_mem) | value_addr (local_mem) | obj_var_addr (obj_mem) |

    // OBJ_GOSUB //
    Sets THIS_MEM to point to obj_addr, LOCAL_MEM to point to the top of the mem stack, and LOCAL_MEM retn addr to IP + 1; then sets IP to start_addr
    | OBJ_GOSUB | -1 | obj_addr (local_mem) | start_addr (local_mem) |

    // USNG_AS //
    -> allows the VM to instantiate all objects of an object array to their respective class type upon program start
    | USNG_AS | arr_size (local_mem) | class_sign (int) | object_addr (local_mem) |

    //|||\\ //|||\\ //|||\\ //|||\\ //|||\\ //|||\\ //|||\\ //|||\\ //|||\\

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 // File I/O //

    Syntax:

    word_array[1000], line_array[100] : string;

    open(word_array, "file.txt", " "); // Stores each word [separated by spaces] on the passed array index, throws error on overflow
    open(line_array, "file.txt", "\n"); // Stores each line [separated by \n] on the passed array index, throws error on overflow

    write(word_array, "file.txt", " ") // Writes each word_array entry to the file, separated by empty spaces
    write(line_array, "file.txt", "\n") // Writes each line_array entry to the file, separated by "\n"

    QUADS (more like HEXES):

    // F_OPEN //
    Opens the file at file_path, parses it using the separator and stores each entry into the appropriate buffer_addr inside of parent_obj (parent_obj is -1 if null, 0 if this.)Throws error if the number of entries exceeds buffer_dim
    If it reahes EOF and the buffer still has available space, it inserts a "END_OF_STREAM" entry at the end, so that the user can know the file data is over.
    | F_OPEN | parent_obj (local_mem) | file_path (local_mem) | separator (local_mem) | buffer_addr (parent_obj's mem) | buffer_dim (int) |

    // F_WRITE //
    Opens the file at file_path, and writes the contents of buffer_addr using the separator into it (parent_obj is -1 if null, 0 if this.)
    If one of the buffer entries has "END_OF_STREAM", entries that come after it will not be written to the file.
    | F_WRITE | parent_obj (local_mem) | file_path (local_mem) | separator (local_mem) | buffer_addr (parent_obj's mem) | buffer_dim (int) |

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// SPRINT //

// TODO : Get rid of C++ code injection for VM compilation
            !DONE! -> Have default compilation method generate intermediate object file, C++ main reads it, stores data and deletes it
                --> Well, kind of...
                    --> Might be nice to have this happen in .txt (.onuca ?) file that gets properly searched for, read and parsed into data
                        --> Would allow me to get rid of that nasty #include statement that is bound to failure in VM code
                        --> Might be another TODO refactor down the line :P
            -> Optional compilation flags:
                !DONE! -> --keep-object: Does not delete intermediate object file after VM compilation
                    --> Well, kind of... again...
                        --> Need to refacor the CLI for NucaScript ASAP!
                -> --object-only: Only generates object file; Does not call any VM utilities
                -> --from-object: Pass in pre-generated object file to VM; does not call any Compiler utilities
            
            --> Update README with proper CLI instructions
                --> Maybe a whole CLI section is warranted now (!)

// TODO: Add Unit Tests!
            -> Project is getting large
            -> This is a must and you know it
            -> Could start by unit testing example_nuca and tutorial_nuca outputs (both to console and to files)
                -> Eventually evolve into UT for every single possible use case?
                    -> Sounds boring but might be cheerful work [figuring out how to break things, and then fixing them :)]
                
// TODO: Bump Compiler's default MAX_CNST, MAX_TMP_SYMBOLS, MAX_SYMBOLS and MEMORY_STACK_LIMIT values
            -> Add optional compilation flags to change these values dinamically (?)
                --> --large: BIG memory (?)
                --> --small: SMALL memory (?)
                --> --max-cnst <NUM> --max-tmp <NUM> --max-sym <NUM> --max-stack <NUM>: Sets values accordingly
                
// TODO: Write a tic-tac-toe game (just like in the good olden days of learning python) in NucaScript as an example!
            -> Make it just like the original! (either single or 2 player)
            -> Computer would be smart enough to win if allowed to :)

// TODO : Add .nuca file extension type enforcing (for aesthetic reasons)
            -> Have compiler raise an error when trying to compile any other file extension type

// TODO : Take a look at py2exe && py2app (or other alternatives?)
            -> Would be cool to package everything in there so that a NucaScript executable could be distributed
            -> Might need to look at an installer or an image instead, since g++ needs to be available as well            

// TODO : More builtin methods!
            -> math builtin methods (pow, sqrt)

// TODO: Search README.md and VERSION_LOG.md for forgotten TODO tags
            -> There is always something else to fix or improve!
            -> If empty (doubt), just look at the IDEAS FOR FUTURE IMPROVEMENT section near the top of this file : )

// TODO: Organize repo
            -> Cleanup nuca_script.py comments & main method (!!!)
            -> VM Code refactor, maybe ENUMs for memory_context_signature int (?)
            -> Breakuo VM/main.cpp further (?)
            -> Could also look into a C++ linter for VSCode to fix all of the ugly indentantion in all of the VM code... (?)
            -> Further subdivide Compiler package into smaller packages (?)
            -> Breakup Grammar.py further (?)

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

'''

import sys, os

import Libraries.ply.yacc as yacc

from Compiler.Boostrapper import *
from Compiler.Utils import fill_vm_file

## Main Compiler Method ##

def main(argv):

    # Build the parser
    parser = yacc.yacc()

    output_file_path = None
    input_file_path = None

    keep_intermediate_object_code = False

    while len(argv):
        #TODO: fix this mess so that one can write reasonable NucaScript commands
        if len(argv) == 1:
            input_file_path = argv.pop()
            break

        if argv[-1] == "--keep-object":
            keep_intermediate_object_code = True
            argv.pop()
            continue

        arg = argv.pop()
        param = argv.pop()

        if param == "-i":
            input_file_path = arg
        elif param == "-o":
            output_file_path = arg
        else:
            EXCEPTION_HANDLER.raiseException("Param Error! Use -i for input file path (assumed as first parameter) and -o for output file path.")

    if input_file_path == None:
        EXCEPTION_HANDLER.raiseException("Param Error! Please provide an input file path (assumed as first parameter)")

    EXCEPTION_HANDLER.setSourceFilePath(input_file_path)

    lex_data = ""
    with open(input_file_path) as source_file:
        lines = source_file.readlines()
        for line in lines:
            lex_data += line
        print(">> Parsing " + input_file_path + "...")
        parser.parse(lex_data)

    mem_constraints_str = "const int MAX_CONSTANTS = " + str(MAX_CONSTANTS) + ", MAX_SYMBOLS = " + str(MAX_SYMBOLS) + ", MAX_TMP_SYMBOLS = " + str(MAX_TMP_SYMBOLS) + ", MAX_OBJ_SYMBOLS = " + str(MAX_OBJ_SYMBOLS) + ", VAR_TYPES = " + str(VAR_TYPES) + ", MEMORY_STACK_LIMIT = " + str(MEMORY_STACK_LIMIT) + ";"

    fill_vm_file(INTERMEDIATE_OBJECT_CODE_PATH, VM_MEMORY_CONSTRAINTS_MARKER_STR, mem_constraints_str, VM_MEMORY_CONSTRAINTS_END_STR, [])

    vm_func_memory = []
    for context in FUNC_DIR.FUNCS.keys():
        if context == FUNC_DIR.program_name:
            global_mem_sign = "\t" * 10 +  "{" + str(FUNC_DIR.get_main_start_addr()) + ", {{" + ",".join([str(x) for x in list(FUNC_DIR.FUNCS[context].var_memory_signature.values())]) + "}"
            global_temp_sign = "{" + ",".join([str(x) for x in list(FUNC_DIR.FUNCS[context].temp_memory_signature.values())]) + "}"
            global_const_sign = "{" + ",".join([str(x) for x in list(FUNC_DIR.FUNCS[context].const_memory_signature.values())]) + "}}},\n"
            vm_func_memory.insert(0, global_mem_sign + ", " + global_temp_sign + ", " + global_const_sign)
        else:
            if context == "GLOBAL":
                for func in FUNC_DIR.FUNCS[context].keys():
                    mem_sign = "\t" * 10 +  "{" + str(FUNC_DIR.get_start_addr(func, context)) + ", {{" + ",".join([str(x) for x in list(FUNC_DIR.FUNCS[context][func].var_table.var_memory_signature.values())]) + "}"
                    temp_sign = "{" + ",".join([str(x) for x in list(FUNC_DIR.FUNCS[context][func].var_table.temp_memory_signature.values())]) + "}}},\n"
                    vm_func_memory.append(mem_sign + ", " + temp_sign)
            else:
                for func in FUNC_DIR.FUNCS[context]["FUNCS"].keys():
                    mem_sign = "\t" * 10 +  "{" + str(FUNC_DIR.get_start_addr(func, context)) + ", {{" + ",".join([str(x) for x in list(FUNC_DIR.FUNCS[context]["FUNCS"][func].var_table.var_memory_signature.values())]) + "}"
                    temp_sign = "{" + ",".join([str(x) for x in list(FUNC_DIR.FUNCS[context]["FUNCS"][func].var_table.temp_memory_signature.values())]) + "}}},\n"
                    vm_func_memory.append(mem_sign + ", " + temp_sign)

    fill_vm_file(INTERMEDIATE_OBJECT_CODE_PATH, VM_FUNCTION_MEMORY_MARKER_STR, VM_FUNCTION_MEMORY_START_STR, VM_FUNCTION_MEMORY_END_STR, vm_func_memory)

    vm_obj_memory = []
    for i, context in enumerate(FUNC_DIR.FUNCS.keys()):
        if context not in [FUNC_DIR.program_name, "GLOBAL"]:
            mem_sign = "\t" * 10 +  '{' + str(i) + ', {' + ",".join([str(x) for x in list(FUNC_DIR.FUNCS[context]["SYMBOLS"].var_memory_signature.values())]) + "}},\n"
            vm_obj_memory.append(mem_sign)

    fill_vm_file(INTERMEDIATE_OBJECT_CODE_PATH, VM_OBJECT_MEMORY_MARKER_STR, VM_OBJECT_MEMORY_START_STR, VM_OBJECT_MEMORY_END_STR, vm_obj_memory)


    vm_constants = []
    for id in FUNC_DIR.FUNCS[FUNC_DIR.program_name].SYMBOLS.keys():
        symbol = FUNC_DIR.FUNCS[FUNC_DIR.program_name].SYMBOLS[id]
        if symbol.is_constant or symbol.object_type != None: # If is constant OR object
            if id in SymbolTable.TRUTH: # Bool constant
                constant_string = "\t" * 10 + "{" + str(symbol.mem_index) + ', "' + str(SymbolTable.TRUTH.index(id)) + '"},\n'
            elif symbol.object_type != None:  # Object to be initialized
                constant_string = "\t" * 10 + "{" + str(symbol.mem_index) + ', "' + str(FUNC_DIR.get_class_idx(symbol.object_type)) + '"},\n'
            elif isinstance(id, str): # String Constant
                constant_string = "\t" * 10 + "{" + str(symbol.mem_index) + ', "' + id[1:-1] + '"},\n'
            else: # Int / Float constant
                constant_string = "\t" * 10 + "{" + str(symbol.mem_index) + ', "' + str(id) + '"},\n'
            vm_constants.append(constant_string)

    fill_vm_file(INTERMEDIATE_OBJECT_CODE_PATH, VM_CONSTANTS_MARKER_STR, VM_CONSTANTS_START_STR, VM_CONSTANTS_END_STR, vm_constants)


    vm_quads = []
    for i in range(len(GLOBALS.QUADS)):
        vm_quads.append("\t" * 10 + GLOBALS.QUADS[i].get_cpp_string() + "\n")

    fill_vm_file(INTERMEDIATE_OBJECT_CODE_PATH, VM_QUAD_MARKER_STR, VM_QUAD_START_STR, VM_QUAD_END_STR, vm_quads)

    if output_file_path == None:
        output_file_path = FUNC_DIR.program_name

    #TODO: ADD FLAGS FOR NOT COMPILING QUITE YET (?)
    print(">> Compiling " + input_file_path + " into " + output_file_path)
    
    if not os.system('g++ -std=c++11 ' + MAIN_VM_FILE_PATH + ' -o ' + output_file_path):

        if not keep_intermediate_object_code:
            os.system("rm " + INTERMEDIATE_OBJECT_CODE_PATH)
        
        print(">> Compilation Successfull!")

## Runs main upon invoking this script with python nuca_script.py ##
if __name__=='__main__':
    main(sys.argv[1:])
