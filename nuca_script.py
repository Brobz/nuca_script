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
        -> atom syntactic highliter ?
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
    [4 * MAX_CONSTANTS + 10 * MAX_SYMBOLS + 10 * MAX_TMP_SYMBOLS + 3 * MAX_OBJ_SYMBOLS,                        4 * MAX_CONSTANTS + 10 * MAX_SYMBOLS + 10 * MAX_TMP_SYMBOLS + 4 * MAX_OBJ_SYMBOLS - 1]           ->          Object Boooleans

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
    Creates an instace of obj_sign signature and stores it into obj_dir
    | OBJ_INST | -1 | obj_sign | obj_dir (locl_mem) |

    // OBJ_READ //
    Reads from obj_var_dir in obj_dir's memory and writes it to result_dir (local_mem)
    | OBJ_READ | obj_dir (local_mem) | obj_var_dir (obj_mem) | result_dir (local_mem) |

    // OBJ_WRITE //
    Writes value_dir into obj_var_dir in obj_dir's memory
    | OBJ_WRITE | obj_dir (local_mem) | value_dir (local_mem) | obj_var_dir (obj_mem) |

    // OBJ_GOSUB //
    Sets THIS_MEM to point to obj_dir, LOCAL_MEM to point to the top of the mem stack, and LOCAL_MEM retn addr to IP + 1; then sets IP to start_addr
    | OBJ_GOSUB | -1 | obj_dir (local_mem) | start_addr (local_mem) |

    // USNG_AS //
    -> allows the VM to instantiate all objects of an object array to their respective class type upon program start
    | USNG_AS | arr_size (local_mem) | class_sign (int) | object_dir (local_mem) |

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
    Opens the file at file_path, parses it using the separator and stores each entry into the appropriate buffer_dir inside of parent_obj (parent_obj is -1 if null, 0 if this.)Throws error if the number of entries exceeds buffer_dim
    If it reahes EOF and the buffer still has available space, it inserts a "END_OF_STREAM" entry at the end, so that the user can know the file data is over.
    | F_OPEN | parent_obj (local_mem) | file_path (local_mem) | separator (local_mem) | buffer_dim (int) | buffer_dir (parent_obj's mem) |

    // F_WRITE //
    Opens the file at file_path, and writes the contents of buffer_dir using the separator into it (parent_obj is -1 if null, 0 if this.)
    If one of the buffer entries has "END_OF_STREAM", entries that come after it will not be written to the file.
    | F_OPEN | parent_obj (local_mem) | file_path (local_mem) | separator (local_mem) | buffer_dim (int) | buffer_dir (parent_obj's mem) |

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// SPRINT //

// TODO : More builtin methods!
            -> math builtin methods (pow, sqrt)

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

'''

import sys, os, getopt

import Libraries.ply.lex as lex
import Libraries.ply.yacc as yacc

from Compiler.ExceptionHandler import *
from Compiler.SymbolTable import *
from Compiler.FunctionDirectory import *
from Compiler.Quad import *

# Tokens for the lexer
tokens = [
'HASHTAG',
'SEMI_COLON',
'COLON',
'COMMA',
'DOT',
'OPEN_CURLY',
'CLOSE_CURLY',
'OPEN_BRACKET',
'CLOSE_BRACKET',
'EQUALS',
'PLUS_PLUS',
'MINUS_MINUS',
'PLUS_EQUALS',
'MINUS_EQUALS',
'TIMES_EQUALS',
'OVER_EQUALS',
'NOT_EQUALS',
'NOT',
'DOUBLE_EQUALS',
'AND',
'OR',
'OPEN_PARENTHESIS',
'CLOSE_PARENTHESIS',
'PLUS',
'MINUS',
'STAR',
'FWD_SLASH',
'BIGGER',
'BIGGER_EQ',
'SMALLER',
'SMALLER_EQ',
'CTE_I',
'CTE_F',
'CTE_S',
'CTE_TRUE',
'CTE_FALSE',
'ID',
]

# Reserved ids for the keywords
reserved = {
    'program'   :   'PROGRAM_KWD',
    'DEF'       :   'DEF_KWD',
    'ATTR'      :   'ATTR_KWD',
    'VARS'      :   'VARS_KWD',
    'class'     :   'CLASS_KWD',
    'main'      :   'MAIN_KWD',
    'new'       :   'NEW_KWD',
    'this'      :   'THIS_KWD',
    'println'   :   'PRINTLN_KWD',
    'print'     :   'PRINT_KWD',
    'stoi'      :   'STOI_KWD',
    'stof'      :   'STOF_KWD',
    'stob'      :   'STOB_KWD',
    'substr'    :   'SUBSTR_KWD',
    'strlen'    :   'STRLEN_KWD',
    'randint'   :   'RANDINT_KWD',
    'read'      :   'READ_KWD',
    'open'      :   'OPEN_KWD',
    'write'     :   'WRITE_KWD',
    'return'    :   'RETURN_KWD',
    'while'     :   'WHILE_KWD',
    'for'       :   'FOR_KWD',
    'if'        :   'IF_KWD',
    'else'      :   'ELSE_KWD',
    'int'       :   'TYPE_I',
    'float'     :   'TYPE_F',
    'string'    :   'TYPE_S',
    'boolean'   :   'TYPE_B',
    'void'      :   'TYPE_V',
}

tokens += list(reserved.values())

# Simple Tokens
t_HASHTAG                   =   r'\#'
t_SEMI_COLON                =   r';'
t_COLON                     =   r':'
t_COMMA                     =   r','
t_DOT                       =   r'\.'
t_OPEN_CURLY                =   r'\{'
t_CLOSE_CURLY               =   r'\}'
t_OPEN_BRACKET              =   r'\['
t_CLOSE_BRACKET             =   r'\]'
t_OPEN_PARENTHESIS          =   r'\('
t_CLOSE_PARENTHESIS         =   r'\)'
t_PLUS_PLUS                 =   r'\+\+'
t_MINUS_MINUS               =   r'--'
t_PLUS_EQUALS               =   r'\+='
t_MINUS_EQUALS              =   r'-='
t_TIMES_EQUALS              =   r'\*='
t_OVER_EQUALS               =   r'/='
t_NOT_EQUALS                =   r'!='
t_DOUBLE_EQUALS             =   r'=='
t_EQUALS                    =   r'='
t_NOT                       =   r'!'
t_AND                       =   r'\&\&'
t_OR                        =   r'\|\|'
t_PLUS                      =   r'\+'
t_MINUS                     =   r'\-'
t_STAR                      =   r'\*'
t_FWD_SLASH                 =   r'\/'
t_BIGGER_EQ                 =   r'\>='
t_BIGGER                    =   r'\>'
t_SMALLER_EQ                =   r'\<='
t_SMALLER                   =   r'\<'

# Complex Tokens
def t_CTE_TRUE(t):
    r'(TRUE)|(True)|(true)'
    t.value = True
    return t

def t_CTE_FALSE(t):
    r'(FALSE)|(False)|(false)'
    t.value = False
    return t

def t_ID(t):
     r'[A-Za-z]([A-Za-z]|[0-9]|_)*'
     t.type = reserved.get(t.value, 'ID')    # Check for reserved words
     return t

def t_CTE_F(t):
    r'[0-9]+\.[0-9]+'
    t.value = float(t.value)
    return t

def t_CTE_I(t):
    r'[0-9]+'
    t.value = int(t.value)
    return t

def t_CTE_S(t):
     r'"(?:[^"\\]|\\.)*"'
     return t

def t_COMMENT(t):
    r'/\*/((?!/\*/).)*/\*/'

# Define a rule so we can track line numbers
def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

# To ignore whitespaces and tabs
t_ignore  = ' \t'

# Error handling rule
def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)

# Build the lexer
lexer = lex.lex()

# Now to parsing!

## First, lets initialize our ExceptionHandler object, which will handle excepiton raising with useful error meessages
EXCEPTION_HANDLER = ExceptionHandler(lexer)

## THen, set the reference to this exception handler object on the rest of the classes
FunctionDirectory.EXCEPTION_HANDLER = EXCEPTION_HANDLER
SymbolTable.EXCEPTION_HANDLER = EXCEPTION_HANDLER

## Here we define the memory constraints of our parser
MAX_CONSTANTS = 10000                                        # (per type)
MAX_SYMBOLS = MAX_TMP_SYMBOLS = MAX_OBJ_SYMBOLS = 30000      # (per type)
MEMORY_STACK_LIMIT = 100000                                  # (to prevent recursion)

## Then, we initialize the FunctionDirectory object which will handle all of the parsing processes
FUNC_DIR = FunctionDirectory([MAX_CONSTANTS, MAX_SYMBOLS, MAX_TMP_SYMBOLS, MAX_OBJ_SYMBOLS])

## Stack initialization
OPERATOR_STACK = []
OPERAND_STACK = []
TYPE_STACK = []
JUMP_STACK = []
FUNC_CALL_STACK = []
ARRAY_DIMENSION_STACK = []
SCOPES_STACK = ["GLOBAL"]
DOT_OP_STACK = []
OBJECT_ACCESS_STACK = []
CLASS_INSTANCE_STACK = []
CONDITIONAL_DEPTH_STACK = []

## Quad Initialization
QUAD_POINTER = 1
QUADS = [Quad("GOTO", -1, -1, "PND")]

## Quad Helper Functions ##
#  a few methods to make quad manipulation easier #

def push_to_quads(q):
    global QUADS
    global QUAD_POINTER
    QUADS.append(q)
    QUAD_POINTER += 1

def fill_quad(dir, fill):
    global QUADS
    global QUAD_POINTER

    q = QUADS[dir]

    if q.arg_3 == "PND":
        q.arg_3 = fill
    else:
        EXCEPTION_HANDLER.raiseException(">> Quad Error: trying to fill complete quad!")

def swap_quads(q1, q2):
    if q2 > len(QUADS) - 1:
        QUADS.append(QUADS.pop(q1))
        for q in QUADS:
            if q.operator in [OPCodes["GOTO"], OPCodes["GOTOF"]] and q.arg_3 != "PND": # If this QUAD is either a GOTO or a GOTOF...
                if q.arg_3 > q1: # And was pointing to a quad placed after (bigger index) the one we popped...
                    # Jump dir has been changed since we popped a quad that came before the one we were jumping to
                    q.arg_3 -= 1 # Adjust the value
    else:
        temp = QUADS[q2]
        QUADS[q2] = QUADS[q1]
        QUADS[q1] = temp

## PLY Rules ##
# the next set of functions define the grammar rules of NucaScript, as well as the actions they should execute during parsing #

def p_program(p):
    ''' PROGRAM : PROGRAM_KWD ID seen_program_id SEMI_COLON DEF_SECTION STRUCTURE_DEFINITION MAIN_KWD OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_CURLY seen_main_kwd STATEMENT_STAR CLOSE_CURLY '''
    push_to_quads(Quad("END", -1, -1, -1))
    print(">> Syntax Approved!")

def p_def_section(p):
    ''' DEF_SECTION : DEF_STATEMENT_STAR '''

def p_def_statement_star(p):
    ''' DEF_STATEMENT_STAR :        DEF_STATEMENT DEF_STATEMENT_STAR
                                |   empty '''

def p_def_statement(p):
    ''' DEF_STATEMENT : HASHTAG DEF_KWD ID COLON CONSTANT'''
    def_name = p[3]
    def_value = str(OPERAND_STACK.pop())

    if def_value in SymbolTable.TRUTH:
        # Our DEF is, technically, a string...
        # More accurately though, it is TRUTH string, which will be representing a boolean type in nuca_script
        # So we just set it to the according integer
        def_value = ["False", "True"][SymbolTable.TRUTH.index(def_value)]
    elif def_value[0] == "'" and def_value[-1:] == "'":
        # Our DEF is, indeed, a proper string; Swap ecompassing '' for ""
        def_value = '"' + def_value[1 : len(def_value) - 1] + '"'

    # Since we will be messing with the lexdata (lexer's input) on the fly,
    # we will need to reajust both the lexer cursor position (lexpos) and
    # the size of the data (lexlen)
    lexpos_shift = len(def_name) - len(def_value)
    original_lexdata_length = len(p.lexer.lexdata)

    # Here we do the actual #DEF replacements, in a C-like fashion
    # TODO: Figure out a way to NOT replace names that are inside of a string (within quotations)
    #       maybe using regex?
    p.lexer.lexdata = p.lexer.lexdata.replace(def_name, def_value)

    # Here we figure out how much the lexdata changed after the replacement
    lexdata_length_diff = original_lexdata_length - len(p.lexer.lexdata)

    # If our #DEF name is any bigger (or smaller) then the value it will be substituted with, then our cursor moved!
    # Adjust the cursor (lexpos) with the appropriate shift
    p.lexer.lexpos -= lexpos_shift

    # Finally, we adjust the lexlen value with how much text was shaved of (or added) by the substitutions
    p.lexer.lexlen -= lexdata_length_diff

def p_structure_definition(p):
    ''' STRUCTURE_DEFINITION :      GLOBAL_VAR STRUCTURE_DEFINITION
                                |   CLASS STRUCTURE_DEFINITION
                                |   FUNC_DEF STRUCTURE_DEFINITION
                                |   empty '''

def p_seen_program_id(p):
    ''' seen_program_id : empty '''
    FUNC_DIR.declare_function(p[-1], "void", "PROGRAM")

def p_seen_main_kwd(p):
    ''' seen_main_kwd : empty '''
    FUNC_DIR.set_main_start_addr(QUAD_POINTER)
    fill_quad(0, QUAD_POINTER)
    for sym in FUNC_DIR.FUNCS[FUNC_DIR.program_name].SYMBOLS:
        symbol = FUNC_DIR.FUNCS[FUNC_DIR.program_name].SYMBOLS[sym]
        if symbol[4] and symbol[7] != None: # is_arr and class_type != None
            push_to_quads(Quad("USNG_AS", FUNC_DIR.get_array_element_size(sym, SCOPES_STACK[-1]), FUNC_DIR.get_class_idx(symbol[7]), FUNC_DIR.get_symbol_mem_index(sym, SCOPES_STACK[-1], False)))

def p_class(p):
    ''' CLASS : CLASS_KWD ID seen_class_id_declaration OPEN_CURLY CLASS_ATTR seen_class_attr FUNC_DEF_STAR CLOSE_CURLY '''
    SCOPES_STACK.pop()

def p_seen_class_id_declaration(p):
    ''' seen_class_id_declaration : empty '''
    FUNC_DIR.declare_object_type(p[-1])
    SCOPES_STACK.append(p[-1])

def p_seen_class_attr(p):
    ''' seen_class_attr : empty '''
    if p[-1] != None:
        parse_vars_declaration(p[-1])

def p_class_attr(p):
    ''' CLASS_ATTR : ATTR_KWD OPEN_CURLY VAR_LIST_STAR CLOSE_CURLY '''
    p[0] = p[3]

def p_var_list_star(p):
    ''' VAR_LIST_STAR : VAR_LIST VAR_LIST_STAR
                      | empty '''
    if len(p) > 2:
        p[0] = p[1]
        if p[2] != None:
            p[0] += "||" + p[2]

def p_var_list(p):
    ''' VAR_LIST : SYMBOL_LIST COLON TYPE SEMI_COLON '''
    p[0] = p[1] + ":" + p[3]

def p_symbol_list(p):
    ''' SYMBOL_LIST : ID SYMBOL_LIST_P
                    | ARRAY_DECLARATION SYMBOL_LIST_P  '''
    p[0] = p[1]
    if p[2] != None:
        p[0] += p[2]

def p_symbol_list_p(p):
    ''' SYMBOL_LIST_P : COMMA ID SYMBOL_LIST_P
                    |   COMMA ARRAY_DECLARATION SYMBOL_LIST_P
                    |   COMMA
                    | empty '''
    if len(p) <= 2:
        p[0] = None
        return

    if p[1] == ',':
        p[0] = ',' + p[2]
        if p[3] != None:
            p[0] += p[3]

def p_readable_list(p):
    ''' READABLE_LIST : VAR seen_var_in_assign seen_readable READABLE_LIST_P '''

def p_readable_list_p(p):
    ''' READABLE_LIST_P : COMMA VAR seen_var_in_assign seen_readable READABLE_LIST_P
                  | empty '''

def p_seen_readable(p):
    ''' seen_readable  : empty '''
    id_scope = SCOPES_STACK[-1]
    id_attr = False
    id = OPERAND_STACK.pop()
    if type(id) == list:
        id, id_scope, id_attr = id
    id_type = TYPE_STACK.pop()

    if id_type in ["void", "object"]:
        if id != None:
            EXCEPTION_HANDLER.raiseException(">> Type Error: Cannot read into symbol " + id + " of type " + id_type)
        else:
            EXCEPTION_HANDLER.raiseException(">> Type Error: Cannot read into " + printable_type)

    is_ptr = int(FUNC_DIR.is_sym_ptr(id, id_scope))
    if not is_ptr:
        is_ptr = -1

    parent_obj_dir = -1
    if id_attr and len(CLASS_INSTANCE_STACK):
        parent_obj_id = CLASS_INSTANCE_STACK.pop()
        if parent_obj_id != "this_kwd":
            parent_obj_dir = FUNC_DIR.get_symbol_mem_index(parent_obj_id, SCOPES_STACK[-1])


    push_to_quads(Quad("READ", parent_obj_dir, is_ptr, FUNC_DIR.get_symbol_mem_index(FUNC_DIR.symbol_lookup(id, id_scope, id_attr), id_scope, id_attr)))

def p_global_var(p):
    ''' GLOBAL_VAR : VAR_LIST_STAR '''
    if p[1] != None:
        parse_vars_declaration(p[1])

def p_func_def_star(p):
    ''' FUNC_DEF_STAR : FUNC_DEF FUNC_DEF_STAR
                      | empty '''

def p_func_def(p):
    ''' FUNC_DEF : TYPE ID seen_func_id OPEN_PARENTHESIS FUNC_PARAM CLOSE_PARENTHESIS seen_func_params VARS seen_func_vars OPEN_CURLY STATEMENT_STAR CLOSE_CURLY '''
    if not FUNC_DIR.valid_return_check(QUAD_POINTER - 1, SCOPES_STACK[-1]): # This means the last statement of this functions block was not a return statement!
        FUNC_DIR.return_type_check("void", QUAD_POINTER, SCOPES_STACK[-1], len(CONDITIONAL_DEPTH_STACK))  # In that case, assume a void return (return;) and check if iit is valid
        push_to_quads(Quad("ENDFNC", -1, -1, int(SCOPES_STACK[-1] != "GLOBAL"))) # All good!

    FUNC_DIR.change_current_scope(None)
    FUNC_DIR.AVAIL.reset_counter()

def p_seen_func_id(p):
    ''' seen_func_id : empty '''
    FUNC_DIR.declare_function(p[-1], p[-2], SCOPES_STACK[-1])

def p_seen_func_params(p):
    ''' seen_func_params : empty '''

    if p[-2] != None:
        for list in p[-2].split(","):
            id, type = list.split(":")
            FUNC_DIR.declare_param(id, type, SCOPES_STACK[-1])

def p_seen_func_vars(p):
    ''' seen_func_vars : empty '''
    if p[-1] != None:
        parse_vars_declaration(p[-1])

    FUNC_DIR.set_start_addr(QUAD_POINTER, SCOPES_STACK[-1])
    if SCOPES_STACK[-1] != "GLOBAL":
        for sym in FUNC_DIR.FUNCS[SCOPES_STACK[-1]]["FUNCS"][FUNC_DIR.current_scope][2].SYMBOLS:
            symbol = FUNC_DIR.FUNCS[SCOPES_STACK[-1]]["FUNCS"][FUNC_DIR.current_scope][2].SYMBOLS[sym]
            if symbol[4] and symbol[7] != None: # is_arr and class_type != None
                push_to_quads(Quad("USNG_AS", FUNC_DIR.get_array_element_size(sym, SCOPES_STACK[-1]), FUNC_DIR.get_class_idx(symbol[7]), FUNC_DIR.get_symbol_mem_index(sym, SCOPES_STACK[-1], False)))
            elif symbol[7] != None:
                push_to_quads(Quad("OBJ_INST", -1, FUNC_DIR.get_class_idx(symbol[7]), FUNC_DIR.get_symbol_mem_index(sym, SCOPES_STACK[-1], False)))


def p_func_param(p):
    ''' FUNC_PARAM : ARG_DECLARATION FUNC_PARAM_P
                   | empty '''

    if len(p) > 2:
        p[0] = p[1]
        if p[2] != None:
            p[0] += p[2]

def p_func_param_p(p):
    ''' FUNC_PARAM_P : COMMA ARG_DECLARATION FUNC_PARAM_P
                     | empty '''

    if len(p) > 2:
        p[0] = "," + p[2]
        if p[3] != None:
            p[0] += p[3]

def p_arg_declaration(p):
    ''' ARG_DECLARATION : ID COLON TYPE '''
    p[0] = p[1] + ":" + p[3]

def p_vars(p):
    ''' VARS : VARS_KWD OPEN_CURLY VAR_LIST_STAR CLOSE_CURLY '''
    p[0] = p[3]

def p_statement_star(p):
    ''' STATEMENT_STAR :  STATEMENT STATEMENT_STAR
                       | empty '''

def p_statement(p):
    ''' STATEMENT : ASSIGN SEMI_COLON
                  | FUNC_CALL SEMI_COLON
                  | READ SEMI_COLON
                  | PRINT SEMI_COLON
                  | PRINTLN SEMI_COLON
                  | OPEN SEMI_COLON
                  | WRITE SEMI_COLON
                  | FLOW_CONTROL
                  | FUNC_RETURN  '''

def p_open(p):
    ''' OPEN : OPEN_KWD OPEN_PARENTHESIS VAR seen_var_in_io seen_open_buffer COMMA EXPRESSION seen_file_path COMMA EXPRESSION seen_separator CLOSE_PARENTHESIS '''
    buffer = p[5]
    buffer_dimension = buffer[3]
    file_path = p[8]
    separator = p[11]

    parent_obj_dir = -1 # This means, just use the current context!
    if buffer[2] and len(CLASS_INSTANCE_STACK):
        parent_obj = CLASS_INSTANCE_STACK.pop()
        if parent_obj != "this_kwd":
            parent_obj_dir = FUNC_DIR.get_symbol_mem_index(parent_obj, SCOPES_STACK[-1]) # This means, use parent_obj!
        else:
            parent_obj_dir = 0 # This means, use this. reference !

    push_to_quads(Quad("F_OPEN", parent_obj_dir, FUNC_DIR.get_symbol_mem_index(file_path[0], file_path[1], file_path[2]), FUNC_DIR.get_symbol_mem_index(separator[0], separator[1], separator[2]), FUNC_DIR.get_symbol_mem_index(buffer[0], buffer[1], buffer[2]), buffer_dimension))

def p_seen_open_buffer(p):
    ''' seen_open_buffer : empty '''
    buffer_scope =  SCOPES_STACK[-1]
    buffer_attr = False
    buffer = OPERAND_STACK.pop()
    buffer_type = TYPE_STACK.pop()

    if type(buffer) == list:
        buffer, buffer_scope, buffer_attr = buffer

    if not FUNC_DIR.is_sym_arr(buffer, buffer_scope, buffer_attr):
        EXCEPTION_HANDLER.raiseException(">> Type Error: cannot open file into a non-array variable")

    if buffer_type != "string":
        EXCEPTION_HANDLER.raiseException(">> Type Error: cannot open file into a non-string array")

    buffer_dimension = FUNC_DIR.get_symbol_dimensions(buffer, buffer_scope, buffer_attr)

    if len(buffer_dimension) > 1:
        EXCEPTION_HANDLER.raiseException(">> Type Error: Cannot open file into non-linear array")

    p[0] = [buffer, buffer_scope, buffer_attr, buffer_dimension[0]]

def p_write(p):
    ''' WRITE : WRITE_KWD OPEN_PARENTHESIS VAR seen_var_in_io seen_write_buffer COMMA EXPRESSION seen_file_path COMMA EXPRESSION seen_separator CLOSE_PARENTHESIS '''
    buffer = p[5]
    buffer_dimension = buffer[3]
    file_path = p[8]
    separator = p[11]

    parent_obj_dir = -1 # This means, just use the current context!
    if buffer[2] and len(CLASS_INSTANCE_STACK):
        parent_obj = CLASS_INSTANCE_STACK.pop()
        if parent_obj != "this_kwd":
            parent_obj_dir = FUNC_DIR.get_symbol_mem_index(parent_obj, SCOPES_STACK[-1]) # This means, use parent_obj!
        else:
            parent_obj_dir = 0 # This means, use this. reference !

    push_to_quads(Quad("F_WRITE", parent_obj_dir, FUNC_DIR.get_symbol_mem_index(file_path[0], file_path[1], file_path[2]), FUNC_DIR.get_symbol_mem_index(separator[0], separator[1], separator[2]), FUNC_DIR.get_symbol_mem_index(buffer[0], buffer[1], buffer[2]), buffer_dimension))

def p_seen_write_buffer(p):
    ''' seen_write_buffer : empty '''
    buffer_scope =  SCOPES_STACK[-1]
    buffer_attr = False
    buffer = OPERAND_STACK.pop()
    buffer_type = TYPE_STACK.pop()

    if type(buffer) == list:
        buffer, buffer_scope, buffer_attr = buffer

    if not FUNC_DIR.is_sym_arr(buffer, buffer_scope, buffer_attr):
        EXCEPTION_HANDLER.raiseException(">> Type Error: cannot write into file from a non-array variable")

    if buffer_type == "object":
        EXCEPTION_HANDLER.raiseException(">> Type Error: cannot write into file from an object type array")

    buffer_dimension = FUNC_DIR.get_symbol_dimensions(buffer, buffer_scope, buffer_attr)

    if len(buffer_dimension) > 1:
        EXCEPTION_HANDLER.raiseException(">> Type Error: cannot write into file from a non-linear array")

    p[0] = [buffer, buffer_scope, buffer_attr, buffer_dimension[0]]

def p_seen_file_path(p):
    '''  seen_file_path : empty '''
    file_path_scope =  SCOPES_STACK[-1]
    file_path_attr = False
    file_path = OPERAND_STACK.pop()
    file_path_type = TYPE_STACK.pop()

    if type(file_path) == list:
        file_path, file_path_scope, file_path_attr = file_path

    if file_path_type != "string":
        EXCEPTION_HANDLER.raiseException(">> Type Error: file path argument of file I/O must be a string")

    p[0] = [file_path, file_path_scope, file_path_attr]

def p_seen_separator(p):
    ''' seen_separator : empty '''
    separator_scope =  SCOPES_STACK[-1]
    separator_attr = False
    separator = OPERAND_STACK.pop()
    separator_type = TYPE_STACK.pop()

    if type(separator) == list:
        separator, separator_scope, separator_attr = separator

    if separator_type != "string":
        EXCEPTION_HANDLER.raiseException(">> Type Error: separator argument of file I/O methods must be a string")

    p[0] = [separator, separator_scope, separator_attr]

def p_flow_control(p):
    ''' FLOW_CONTROL :      DECISION
                        |   REPETITION '''

def p_for_incr_statement(p):
    ''' FOR_INCR_STATEMENT :    ASSIGN
                              | FUNC_CALL
                              | READ
                              | PRINT
                              | PRINTLN '''

def p_assign(p):
    ''' ASSIGN :        VAR seen_var_in_assign EQUALS seen_equals EXPRESSION
                    |   VAR seen_var_in_assign PLUS_EQUALS seen_plus_equals EXPRESSION
                    |   VAR seen_var_in_assign MINUS_EQUALS seen_minus_equals EXPRESSION
                    |   VAR seen_var_in_assign TIMES_EQUALS seen_times_equals EXPRESSION
                    |   VAR seen_var_in_assign OVER_EQUALS seen_over_equals EXPRESSION
                    |   VAR seen_var_in_assign PLUS_PLUS seen_plus_plus
                    |   VAR seen_var_in_assign MINUS_MINUS seen_minus_minus '''

    DOT_OP_STACK.clear()

    assign_to_var()

def p_seen_equals(p):
    ''' seen_equals  : empty '''
    DOT_OP_STACK.clear()
    OPERATOR_STACK.append('=')

def p_seen_plus_equals(p):
    ''' seen_plus_equals  : empty '''
    DOT_OP_STACK.clear()
    parse_compound_asignment('+')

def p_seen_minus_equals(p):
    ''' seen_minus_equals  : empty '''
    DOT_OP_STACK.clear()
    parse_compound_asignment('-')

def p_seen_times_equals(p):
    ''' seen_times_equals  : empty '''
    DOT_OP_STACK.clear()
    parse_compound_asignment('*')

def p_seen_over_equals(p):
    ''' seen_over_equals  : empty '''
    DOT_OP_STACK.clear()
    parse_compound_asignment('/')

def p_seen_plus_plus(p):
    ''' seen_plus_plus  : empty '''
    DOT_OP_STACK.clear()
    parse_compound_asignment('++')

def p_seen_minus_minus(p):
    ''' seen_minus_minus  : empty '''
    DOT_OP_STACK.clear()
    parse_compound_asignment('--')

def p_exp(p):
    ''' EXP :   TERM seen_term EXP_P
              | MINUS seen_unary_minus EXP pop_unary_minus '''

def p_seen_term(p):
    ''' seen_term :  '''
    if len(OPERATOR_STACK) and  (OPERATOR_STACK[-1] == '+' or OPERATOR_STACK[-1] == '-'):
        generate_expression_quad()

def p_exp_p(p):
    ''' EXP_P : PLUS seen_term_op TERM seen_term EXP_P
            | MINUS seen_term_op TERM seen_term EXP_P
            | empty '''

def p_seen_term_op(p):
    ''' seen_term_op :  '''
    OPERATOR_STACK.append(p[-1])

def p_expression(p):
    ''' EXPRESSION :   EXP
                     | EXP COMP seen_comp_op EXPRESSION seen_comp '''

def p_seen_comp(p):
    ''' seen_comp : empty '''
    generate_expression_quad()

def p_seen_comp_op(p):
    ''' seen_comp_op : empty '''
    OPERATOR_STACK.append(p[-1])

def p_comp(p):
    ''' COMP : BIGGER
             | BIGGER_EQ
             | SMALLER
             | SMALLER_EQ
             | DOUBLE_EQUALS
             | NOT_EQUALS
             | AND
             | OR '''

    p[0] = p[1]

def p_factor(p):
    ''' FACTOR :  OPEN_PARENTHESIS seen_open_parenthesis EXPRESSION CLOSE_PARENTHESIS seen_close_parenthesis
                | NOT seen_not FACTOR pop_not
                | MINUS seen_unary_minus FACTOR pop_unary_minus
                | STOI_KWD seen_stoi_kwd OPEN_PARENTHESIS seen_open_parenthesis EXPRESSION CLOSE_PARENTHESIS seen_close_parenthesis seen_stox_factor
                | STOF_KWD seen_stof_kwd OPEN_PARENTHESIS seen_open_parenthesis EXPRESSION CLOSE_PARENTHESIS seen_close_parenthesis seen_stox_factor
                | STOB_KWD seen_stob_kwd OPEN_PARENTHESIS seen_open_parenthesis EXPRESSION CLOSE_PARENTHESIS seen_close_parenthesis seen_stox_factor
                | SUBSTR_KWD OPEN_PARENTHESIS seen_open_parenthesis EXPRESSION seen_substr_str COMMA EXPRESSION seen_substr_idx COMMA EXPRESSION seen_substr_size CLOSE_PARENTHESIS seen_close_parenthesis seen_substr
                | STRLEN_KWD OPEN_PARENTHESIS seen_open_parenthesis EXPRESSION seen_strlen CLOSE_PARENTHESIS seen_close_parenthesis
                | RANDINT_KWD OPEN_PARENTHESIS seen_open_parenthesis EXPRESSION seen_randint_arg COMMA EXPRESSION seen_randint_arg seen_randint CLOSE_PARENTHESIS seen_close_parenthesis
                | FUNC_CALL
                | CLASS_INSTANCE
                | VAR seen_var_as_factor
                | CONSTANT '''

def p_seen_randint(p):
    ''' seen_randint : empty '''
    lower_arg = p[-4]
    upper_arg = p[-1]

    int_temp = FUNC_DIR.next_avail("int", SCOPES_STACK[-1])

    push_to_quads(Quad("RANDINT", FUNC_DIR.get_symbol_mem_index(lower_arg[0], lower_arg[1], lower_arg[2]),  FUNC_DIR.get_symbol_mem_index(upper_arg[0], upper_arg[1], upper_arg[2]), FUNC_DIR.get_symbol_mem_index(int_temp, SCOPES_STACK[-1], False)))

    OPERAND_STACK.append([int_temp, SCOPES_STACK[-1], False])
    TYPE_STACK.append("int")


def p_seen_randint_arg(p):
    ''' seen_randint_arg : empty '''
    randint_arg_scope =  SCOPES_STACK[-1]
    randint_arg_attr = False
    randint_arg = OPERAND_STACK.pop()
    randint_arg_type = TYPE_STACK.pop()

    if type(randint_arg) == list:
        randint_arg, randint_arg_scope, randint_arg_attr = randint_arg

    if randint_arg_type != "int":
        EXCEPTION_HANDLER.raiseException('>> Type Error: "randint" arguments must be ints')

    p[0] = [randint_arg, randint_arg_scope, randint_arg_attr]


def p_seen_strlen(p):
    ''' seen_strlen : empty '''
    strlen_arg_scope =  SCOPES_STACK[-1]
    strlen_arg_attr = False
    strlen_arg = OPERAND_STACK.pop()
    strlen_arg_type = TYPE_STACK.pop()

    if type(strlen_arg) == list:
        strlen_arg, strlen_arg_scope, strlen_arg_attr = strlen_arg

    if strlen_arg_type != "string":
        EXCEPTION_HANDLER.raiseException('>> Type Error: "strlen" argument must be a string')

    int_temp = FUNC_DIR.next_avail("int", SCOPES_STACK[-1])

    push_to_quads(Quad("STRLEN", -1, FUNC_DIR.get_symbol_mem_index(strlen_arg, strlen_arg_scope, strlen_arg_attr), FUNC_DIR.get_symbol_mem_index(int_temp, SCOPES_STACK[-1], False)))

    OPERAND_STACK.append([int_temp, SCOPES_STACK[-1], False])
    TYPE_STACK.append("int")

def p_seen_substr_str(p):
    ''' seen_substr_str : empty '''
    substr_arg_scope =  SCOPES_STACK[-1]
    substr_arg_attr = False
    substr_arg = OPERAND_STACK.pop()
    substr_arg_type = TYPE_STACK.pop()

    if type(substr_arg) == list:
        substr_arg, substr_arg_scope, substr_arg_attr = substr_arg

    if substr_arg_type != "string":
        EXCEPTION_HANDLER.raiseException('>> Type Error: "substr" argument must be a string')

    p[0] = [substr_arg, substr_arg_scope, substr_arg_attr]

def p_seen_substr_idx(p):
    ''' seen_substr_idx : empty '''
    substr_idx_scope =  SCOPES_STACK[-1]
    substr_idx_attr = False
    substr_idx = OPERAND_STACK.pop()
    substr_idx_type = TYPE_STACK.pop()

    if type(substr_idx) == list:
        substr_idx, substr_idx_scope, substr_idx_attr = substr_idx

    if substr_idx_type not in ["int", "boolean"]:
        EXCEPTION_HANDLER.raiseException('>> Type Error: starting index argument in "substr" must be an int')

    p[0] = [substr_idx, substr_idx_scope, substr_idx_attr]

def p_seen_substr_size(p):
    ''' seen_substr_size : empty '''
    susbtr_size_scope =  SCOPES_STACK[-1]
    susbtr_size_attr = False
    susbtr_size = OPERAND_STACK.pop()
    susbtr_size_type = TYPE_STACK.pop()

    if type(susbtr_size) == list:
        susbtr_size, susbtr_size_scope, susbtr_size_attr = susbtr_size

    if susbtr_size_type not in ["int", "boolean"]:
        EXCEPTION_HANDLER.raiseException('>> Type Error: starting index argument in "substr" must be an int')

    p[0] = [susbtr_size, susbtr_size_scope, susbtr_size_attr]

def p_seen_substr(p):
    ''' seen_substr : empty '''
    substr_arg_scope =  p[-9][1]
    substr_arg_attr = p[-9][2]
    substr_arg = p[-9][0]
    substr_idx = p[-6]
    substr_size = p[-3]

    new_str_temp = FUNC_DIR.next_avail("string", SCOPES_STACK[-1])

    push_to_quads(Quad("SUBSTR", FUNC_DIR.get_symbol_mem_index(substr_arg, substr_arg_scope, substr_arg_attr), FUNC_DIR.get_symbol_mem_index(substr_idx[0], substr_idx[1], substr_idx[2]), FUNC_DIR.get_symbol_mem_index(substr_size[0], substr_size[1], substr_size[2]), FUNC_DIR.get_symbol_mem_index(new_str_temp, SCOPES_STACK[-1], False)))

    OPERAND_STACK.append([new_str_temp, SCOPES_STACK[-1], False])
    TYPE_STACK.append("string")

def p_seen_stox_factor(p):
    ''' seen_stox_factor : empty '''
    stox_arg_scope =  SCOPES_STACK[-1]
    stox_arg_attr = False
    stox_arg = OPERAND_STACK.pop()
    stox_arg_type = TYPE_STACK.pop()

    x = p[-6] # The type for the string to be converted into

    if type(stox_arg) == list:
        stox_arg, stox_arg_scope, stox_arg_attr = stox_arg

    if stox_arg_type != "string":
        EXCEPTION_HANDLER.raiseException('>> Type Error: "string to ' + x + '" argument must be a string')

    new_type_temp = FUNC_DIR.next_avail(x, SCOPES_STACK[-1])

    push_to_quads(Quad("STOX", -1, FUNC_DIR.get_symbol_mem_index(stox_arg, stox_arg_scope, stox_arg_attr), FUNC_DIR.get_symbol_mem_index(new_type_temp, SCOPES_STACK[-1], False)))

    OPERAND_STACK.append([new_type_temp, SCOPES_STACK[-1], False])
    TYPE_STACK.append(x)

def p_seen_stoi_kwd(p):
    ''' seen_stoi_kwd : empty '''
    p[0] = "int"

def p_seen_stof_kwd(p):
    ''' seen_stof_kwd : empty '''
    p[0] = "float"

def p_seen_stob_kwd(p):
    ''' seen_stob_kwd : empty '''
    p[0] = "boolean"

def p_pop_not(p):
    ''' pop_not : empty '''
    op = OPERATOR_STACK.pop()
    right_operand_scope = SCOPES_STACK[-1]
    right_operand_attr = False
    right_operand = OPERAND_STACK.pop()
    if type(right_operand) == list:
        right_operand, right_operand_scope, right_operand_attr = right_operand
    right_type = TYPE_STACK.pop()
    res_type = SemanticCube[op][right_type]
    if res_type != "err":
        res = FUNC_DIR.next_avail(res_type, SCOPES_STACK[-1])
        push_to_quads(Quad(op, -1, FUNC_DIR.get_symbol_mem_index(right_operand, right_operand_scope, right_operand_attr), FUNC_DIR.get_symbol_mem_index(res, SCOPES_STACK[-1])))
        OPERAND_STACK.append(res)
        TYPE_STACK.append(res_type)
    else:
        EXCEPTION_HANDLER.raiseException(">> Type Mismatch: " + op + right_type)

def p_seen_not(p):
    ''' seen_not : empty '''
    OPERATOR_STACK.append(p[-1])

def p_pop_unary_minus(p):
    ''' pop_unary_minus : empty '''
    OPERATOR_STACK.pop() # Pop Fake Wall
    op = OPERATOR_STACK.pop()
    right_operand_scope = SCOPES_STACK[-1]
    right_operand_attr = False
    right_operand = OPERAND_STACK.pop()
    if type(right_operand) == list:
        right_operand, right_operand_scope, right_operand_attr = right_operand
    right_type = TYPE_STACK.pop()
    res_type = SemanticCube[op][right_type]
    if res_type != "err":
        res = FUNC_DIR.next_avail(res_type, SCOPES_STACK[-1])
        push_to_quads(Quad(op, -1, FUNC_DIR.get_symbol_mem_index(right_operand, right_operand_scope, right_operand_attr), FUNC_DIR.get_symbol_mem_index(res, SCOPES_STACK[-1])))
        OPERAND_STACK.append(res)
        TYPE_STACK.append(res_type)
    else:
        exception_txt = ">> Type Mismatch: " + op + right_type
        if right_type == "boolean":
            exception_txt += " (maybe use !boolean instead?)"
        EXCEPTION_HANDLER.raiseException(exception_txt)

def p_seen_unary_minus(p):
    ''' seen_unary_minus : empty '''
    OPERATOR_STACK.append(p[-1])
    OPERATOR_STACK.append("|UNARY_MINUS_WALL|") # Fake  Wall for parsing

def p_seen_open_parenthesis(p):
    ''' seen_open_parenthesis : empty '''
    OPERATOR_STACK.append(p[-1])

def p_seen_close_parenthesis(p):
    ''' seen_close_parenthesis : empty '''
    OPERATOR_STACK.pop()

def p_seen_var_in_assign(p):
    ''' seen_var_in_assign :  empty '''
    parse_var(p[-1], 0)

def p_seen_var_as_factor(p):
    ''' seen_var_as_factor : empty '''
    parse_var(p[-1], 1)

def p_seen_var_in_io(p):
    ''' seen_var_in_io : empty '''
    parse_var(p[-1], 0, 1)

def p_seen_cte_i(p):
    ''' seen_cte_i :  empty '''
    FUNC_DIR.declare_constant(p[-1], "int")
    OPERAND_STACK.append(p[-1])
    TYPE_STACK.append("int")

def p_seen_cte_f(p):
    ''' seen_cte_f :  empty '''
    FUNC_DIR.declare_constant(p[-1], "float")
    OPERAND_STACK.append(p[-1])
    TYPE_STACK.append("float")

def p_seen_cte_s(p):
    ''' seen_cte_s :  empty '''
    FUNC_DIR.declare_constant("'" + p[-1][1:-1] + "'", "string")
    OPERAND_STACK.append("'" + p[-1][1:-1] + "'")
    TYPE_STACK.append("string")

def p_seen_cte_false(p):
    ''' seen_cte_false : empty '''
    OPERAND_STACK.append(SymbolTable.TRUTH[0])
    TYPE_STACK.append("boolean")

def p_seen_cte_true(p):
    ''' seen_cte_true : empty '''
    OPERAND_STACK.append(SymbolTable.TRUTH[1])
    TYPE_STACK.append("boolean")

def p_constant(p):
    ''' CONSTANT :      CTE_I seen_cte_i
                    |   CTE_F seen_cte_f
                    |   CTE_S seen_cte_s
                    |   CTE_B '''

    p[0] = p[1]

def p_cte_b(p):
    ''' CTE_B :         CTE_TRUE seen_cte_true
                    |   CTE_FALSE seen_cte_false'''

def p_class_reference(p):
    ''' CLASS_REFERENCE :       ID DOT seen_dot_operator
                            |   ARRAY seen_var_in_assign DOT seen_dot_operator
                            |   THIS_KWD seen_this_kwd DOT seen_this_dot_operator '''
    if len(p) == 4 or p[2] == None:
        p[0] = p[1]
    else:
        p[0] = p[2]

    obj_id = p[0]

    OBJECT_ACCESS_STACK.append(obj_id)

def p_seen_this_kwd(p):
    ''' seen_this_kwd : empty '''
    if len(SCOPES_STACK) < 2:
        EXCEPTION_HANDLER.raiseException(">> Syntax Error: this operator used outside of Class scope")

    if len(OBJECT_ACCESS_STACK) and OBJECT_ACCESS_STACK[-1] != "|ARG_WALL|":
        EXCEPTION_HANDLER.raiseException(">> Attribute Error: symbol " + p[-2] + " has no attribute 'this'")

    p[0] = "this_kwd"

def p_var(p):
    ''' VAR :       ID
                |   ARRAY
                |   CLASS_REFERENCE VAR '''

    if len(p) == 2:
        p[0] = p[1] # Regualar ID / ARRAY

    else:
        if p[1] == "this_kwd": # this. reference, just look it up at the current scope
            if type(p[2]) != list: # Reference comes from an object in a list
                p[0] = FUNC_DIR.symbol_lookup(p[2], SCOPES_STACK[-1], True)
            else:
                FUNC_DIR.symbol_lookup(p[2][1][0], p[2][1][1], True)
                p[0] = p[2]
            return
        else: # obj var reference, look it up on its scope
            if type(p[1]) == list: # Reference comes from an object in a list
                p[1] = p[1][1][0]
            class_obj = FUNC_DIR.symbol_lookup(p[1], SCOPES_STACK[-1])
            if FUNC_DIR.symbol_type_lookup(p[1], SCOPES_STACK[-1]) != "object":
                EXCEPTION_HANDLER.raiseException(">> Syntax Error: cannot use . operator on non-object type " + p[1])

        if type(p[2]) != list: # Parse the accessed attribute
            accessed_attr = FUNC_DIR.symbol_lookup(p[2], DOT_OP_STACK[-1], len(DOT_OP_STACK) > 0)
        else:
            p[0] = p[2]
            return

        # Forward the var through the rules
        p[0] = [class_obj, accessed_attr]

def p_class_instance(p):
    ''' CLASS_INSTANCE : NEW_KWD ID seen_class_id_instance OPEN_PARENTHESIS CLOSE_PARENTHESIS '''
    class_instance = FUNC_DIR.next_avail("object", SCOPES_STACK[-1]) # Tmp for semantic purposes
    FUNC_DIR.set_symbol_object_type(class_instance, p[2], SCOPES_STACK[-1]) # Set its class type
    OPERAND_STACK.append(class_instance) # Push it to the stack
    CLASS_INSTANCE_STACK.append(class_instance) # Pushing it to this stack allows the compiler to easily tell the difference between instantiation and assignation of objs down the road
    TYPE_STACK.append("object") # Push the object type as well

def p_seen_class_id_instance(p):
    ''' seen_class_id_instance : empty '''
    FUNC_DIR.valid_class_check(p[-1])

def p_seen_dot_operator(p):
    ''' seen_dot_operator : empty '''
    obj_id = p[-2]
    if obj_id == None:
        obj_id = p[-3] # For the special object-type array case

    if type(obj_id) == list:
        obj_id = obj_id[1][0]

    FUNC_DIR.symbol_lookup(obj_id, SCOPES_STACK[-1])
    class_type = FUNC_DIR.get_symbol_object_type(obj_id, SCOPES_STACK[-1])
    if class_type == None:
        EXCEPTION_HANDLER.raiseException(">> Type Error: symbol " + obj_id + " has no object type in " + SCOPES_STACK[-1] + " and cannot be accessed with . operator (maybe missing initialization with 'new' or assertion with 'using as'?)")
    DOT_OP_STACK.append(class_type)

def p_seen_this_dot_operator(p):
    ''' seen_this_dot_operator : empty '''
    DOT_OP_STACK.append(SCOPES_STACK[-1])

def p_array(p):
    ''' ARRAY : ID seen_array_id OPEN_BRACKET seen_open_bracket EXPRESSION seen_array_access CLOSE_BRACKET ARRAY_P '''
    p[0] = ["ARRAY"]
    dims = ARRAY_DIMENSION_STACK.pop()
    for dim in dims:
            if dim == p[1]:
                arr_scope = SCOPES_STACK[-1]
                if len(DOT_OP_STACK) and DOT_OP_STACK[-1] != "|ARG_WALL|":
                    arr_scope = DOT_OP_STACK[-1]
                p[0].append([p[1], arr_scope])
                p[0].append([])
            else:
                p[0][2].append(dim)

def p_array_p(p):
    ''' ARRAY_P :       OPEN_BRACKET seen_open_bracket EXPRESSION seen_array_access CLOSE_BRACKET ARRAY_P
                    |   empty '''

def p_seen_array_id(p):
    ''' seen_array_id : empty '''
    id = p[-1]

    scope_in_use = SCOPES_STACK[-1]
    is_attr = False

    if len(DOT_OP_STACK) and DOT_OP_STACK[-1] != "|ARG_WALL|":
        scope_in_use = DOT_OP_STACK[-1]
        is_attr = True

    FUNC_DIR.symbol_lookup(id, scope_in_use, is_attr)
    if not FUNC_DIR.is_sym_arr(id, scope_in_use, is_attr):
        EXCEPTION_HANDLER.raiseException(">> Name Error: Cannot access non-array symbol " + id + " with [] operator")

    ARRAY_DIMENSION_STACK.append([id])

def p_seen_open_bracket(p):
    ''' seen_open_bracket : empty '''
    OPERATOR_STACK.append("|ARRAY_ACCESS_WALL|") # Stack Fake Wall
    DOT_OP_STACK.append("|ARG_WALL|") # Stack Fake Wall
    OBJECT_ACCESS_STACK.append("|ARG_WALL|") # Stack Fake Wall

def p_seen_array_access(p):
    ''' seen_array_access : empty '''
    access = OPERAND_STACK.pop()
    access_type = TYPE_STACK.pop()
    if access_type not in ["int", "boolean"]:
        EXCEPTION_HANDLER.raiseException(">> Type Error: Cannot use " + access_type + " as access index for array '" + ARRAY_DIMENSION_STACK[-1][0] + "'")

    ARRAY_DIMENSION_STACK[-1].append(access)

    OPERATOR_STACK.pop() # Pop Fake Wall

    if len(DOT_OP_STACK) and DOT_OP_STACK[-1] == "|ARG_WALL|":
        DOT_OP_STACK.pop() # Pop Fake Wall

    if len(OBJECT_ACCESS_STACK) and OBJECT_ACCESS_STACK[-1] == "|ARG_WALL|":
        OBJECT_ACCESS_STACK.pop() # Pop Fake Wall

def p_array_declaration(p):
    ''' ARRAY_DECLARATION : ID seen_array_def_id OPEN_BRACKET CTE_I seen_cte_i seen_array_def_dim CLOSE_BRACKET ARRAY_DECLARATION_P'''
    p[0] = p[1]

def p_array_declaration_p(p):
    ''' ARRAY_DECLARATION_P :       OPEN_BRACKET CTE_I seen_cte_i seen_array_def_dim CLOSE_BRACKET ARRAY_DECLARATION_P
                    |   empty'''

def p_seen_array_def_id(p):
    ''' seen_array_def_id : empty '''
    ARRAY_DIMENSION_STACK.append([p[-1]])

def p_seen_array_def_dim(p):
    ''' seen_array_def_dim : empty '''
    dim = OPERAND_STACK.pop()
    TYPE_STACK.pop() # pop dim type (will always be int)
    if dim <= 0:
        EXCEPTION_HANDLER.raiseException(">> Value Error: array dimension must be a non-zero positive integer")
    ARRAY_DIMENSION_STACK[-1].append(dim)

def p_term(p):
    ''' TERM : FACTOR seen_factor TERM_P  '''

def p_term_p(p):
    ''' TERM_P :    STAR seen_factor_op FACTOR seen_factor TERM_P
                 |  FWD_SLASH seen_factor_op FACTOR seen_factor TERM_P
                 |  empty '''

def p_seen_factor(p):
    ''' seen_factor :  empty '''
    if len(OPERATOR_STACK) and (OPERATOR_STACK[-1] == '*' or OPERATOR_STACK[-1] == '/'):
        generate_expression_quad()

def p_seen_factor_op(p):
    ''' seen_factor_op :  empty '''
    OPERATOR_STACK.append(p[-1])

def p_func_call(p):
    ''' FUNC_CALL :     ID seen_func_call_id OPEN_PARENTHESIS ARG_LIST CLOSE_PARENTHESIS
                    |   CLASS_REFERENCE FUNC_CALL'''

    if len(p) > 3: # Normal func call
        p[0] = p[1]
        if len(TYPE_STACK) and TYPE_STACK[-1] == "object": # This is a normal func call contained WITHIN the class reference one;
            TYPE_STACK.pop() # Need to get rid of the class reference "object" type on the type stack
    else:
        p[0] = p[2] # Class reference func call
        return

    if not len(DOT_OP_STACK):
        scope_in_use = SCOPES_STACK[-1]
    else:
        if DOT_OP_STACK[-1] == "|ARG_WALL|":
            scope_in_use = DOT_OP_STACK[-2]
        else:
            scope_in_use = DOT_OP_STACK[-1]

    FUNC_DIR.args_ok(p[0], scope_in_use)

    if scope_in_use == "GLOBAL":
        push_to_quads(Quad("GOSUB", -1, -1, FUNC_DIR.get_start_addr(p[1], scope_in_use)))

    else:

        parent_object = OBJECT_ACCESS_STACK.pop()

        parent_obj_is_ptr = -1
        if type(parent_object) == list: # The caller of this method is inside an object array!
            parent_object = OPERAND_STACK.pop()[0] # In this case, there is an operand at the top of the operand stacks which is the pointer to this object
            parent_obj_is_ptr = 1 # Set is_ptr to True

        if parent_object == "this_kwd":
            push_to_quads(Quad("OBJ_GOSUB", parent_obj_is_ptr, -1, FUNC_DIR.get_start_addr(p[1], scope_in_use)))

        else:
            push_to_quads(Quad("OBJ_GOSUB", parent_obj_is_ptr, FUNC_DIR.get_symbol_mem_index(parent_object, SCOPES_STACK[-1]), FUNC_DIR.get_start_addr(p[1], scope_in_use)))

    FUNC_CALL_STACK.pop()
    if len(FUNC_CALL_STACK):
        FUNC_DIR.set_param_index(FUNC_CALL_STACK[-1][0], FUNC_CALL_STACK[-1][1], scope_in_use)

    return_type = FUNC_DIR.func_type_lookup(p[1], scope_in_use)

    temp = FUNC_DIR.next_avail(return_type, SCOPES_STACK[-1])
    OPERAND_STACK.append(temp)
    TYPE_STACK.append(return_type)

    if return_type != "void": # No need to set the return value if its a void method
        rtn_obj_name = FUNC_DIR.get_return_obj_name(p[1], scope_in_use)
        push_to_quads(Quad("=", get_ptr_value(None, [temp, SCOPES_STACK[-1]]), FUNC_DIR.get_symbol_mem_index(rtn_obj_name, "GLOBAL"), FUNC_DIR.get_symbol_mem_index(temp, SCOPES_STACK[-1])))


    if len(DOT_OP_STACK):
        DOT_OP_STACK.pop()    # POP ARGUMENT FAKE WALL

def p_seen_func_call_id(p):
    ''' seen_func_call_id : empty '''
    OPERATOR_STACK.append("|ARG_WALL|") # ARGUMENT 'FAKE WALL'

    if not len(DOT_OP_STACK) or (len(DOT_OP_STACK) and DOT_OP_STACK[-1] == "|ARG_WALL|"):
        DOT_OP_STACK.append("GLOBAL")

    DOT_OP_STACK.append("|ARG_WALL|") # Stack Fake Wall
    OBJECT_ACCESS_STACK.append("|ARG_WALL|") # Stack Fake Wall

    func_type = FUNC_DIR.func_type_lookup(p[-1], DOT_OP_STACK[-2])

    push_to_quads(Quad("ERA", -1, -1, FUNC_DIR.get_start_addr(p[-1], DOT_OP_STACK[-2])))

    FUNC_DIR.set_param_index(p[-1], 0, DOT_OP_STACK[-2])
    FUNC_CALL_STACK.append([p[-1], 0])

def p_arg_list(p):
    ''' ARG_LIST : VAR seen_var_as_factor seen_arg ARG_LIST_P
                 | EXPRESSION seen_arg ARG_LIST_P
                 | FUNC_CALL seen_arg ARG_LIST_P
                 | empty '''

    OPERATOR_STACK.pop()  # POP 'ARGUMENT FAKE WALL'

    if len(DOT_OP_STACK) and DOT_OP_STACK[-1] == "|ARG_WALL|":
        DOT_OP_STACK.pop()    # POP ARGUMENT FAKE WALL

    if len(OBJECT_ACCESS_STACK) and OBJECT_ACCESS_STACK[-1] == "|ARG_WALL|":
        OBJECT_ACCESS_STACK.pop() # Pop Fake Wall

def p_arg_list_p(p):
    ''' ARG_LIST_P : COMMA VAR seen_var_as_factor seen_arg ARG_LIST_P
                   | COMMA EXPRESSION seen_arg ARG_LIST_P
                   | COMMA FUNC_CALL seen_arg ARG_LIST_P
                   | empty '''

def p_seen_arg(p):
    ''' seen_arg : empty '''
    arg_scope = SCOPES_STACK[-1]
    is_attr = False
    arg = OPERAND_STACK.pop()
    if type(arg) == list:
        arg, arg_scope, is_attr = arg
    arg_type = TYPE_STACK.pop()

    if not len(DOT_OP_STACK):
        scope_in_use = SCOPES_STACK[-1]
    else:
        if DOT_OP_STACK[-1] == "|ARG_WALL|":
            scope_in_use = DOT_OP_STACK[-2]
        else:
            scope_in_use = DOT_OP_STACK[-1]

    k = FUNC_DIR.verify_arg_type(FUNC_CALL_STACK[-1][0], arg_type, scope_in_use) # This checks to see if the next arg type is correct, and gets the index of it

    push_to_quads(Quad("PARAM", -1, FUNC_DIR.get_symbol_mem_index(arg, arg_scope, is_attr), FUNC_DIR.get_param_mem_index(FUNC_CALL_STACK[-1][0], k, scope_in_use)))
    FUNC_CALL_STACK[-1][1] = k

def p_func_return(p):
    ''' FUNC_RETURN :   RETURN_KWD EXPRESSION SEMI_COLON
                      | RETURN_KWD FUNC_CALL SEMI_COLON '''

    if FUNC_DIR.current_scope == None:
        # Return statement outside of function
        EXCEPTION_HANDLER.raiseException('>> Context Error: non-void return statement outside of function or method (maybe use "return;"?)')

    rtn_type = TYPE_STACK.pop()
    rtn_id = OPERAND_STACK.pop()

    FUNC_DIR.return_type_check(rtn_type, QUAD_POINTER + 1, SCOPES_STACK[-1], len(CONDITIONAL_DEPTH_STACK))

    if rtn_type != "void": # No need to set values in case of a void return
        retn_scope = SCOPES_STACK[-1]
        is_attr = False
        if type(rtn_id) == list:
            rtn_id, retn_scope, is_attr = rtn_id

        rtn_obj_name = FUNC_DIR.get_return_obj_name(scope = SCOPES_STACK[-1])

        push_to_quads(Quad("=", get_ptr_value([rtn_id, retn_scope], None), FUNC_DIR.get_symbol_mem_index(rtn_id, retn_scope, is_attr), FUNC_DIR.get_symbol_mem_index(rtn_obj_name, "GLOBAL")))

    push_to_quads(Quad("ENDFNC", -1, -1, int(SCOPES_STACK[-1] != "GLOBAL")))

def p_void_func_return(p):
    ''' FUNC_RETURN : RETURN_KWD SEMI_COLON '''
    if FUNC_DIR.current_scope == None:
        # Return statement outside of function (inside main), but it returns no value... may as well end the program here!
        push_to_quads(Quad("END", -1, -1, -1))
    else:
        # Void return in a regular function.. need to check if its type mathes!
        FUNC_DIR.return_type_check("void", QUAD_POINTER, SCOPES_STACK[-1], len(CONDITIONAL_DEPTH_STACK))
        push_to_quads(Quad("ENDFNC", -1, -1, int(SCOPES_STACK[-1] != "GLOBAL")))

def p_read(p):
    ''' READ : READ_KWD OPEN_PARENTHESIS READABLE_LIST CLOSE_PARENTHESIS '''
    DOT_OP_STACK.clear()

def p_print(p):
    ''' PRINT : PRINT_KWD OPEN_PARENTHESIS PRINTABLE CLOSE_PARENTHESIS '''
    push_to_quads(Quad("PRNT", -1, -1, -1))
    DOT_OP_STACK.clear()

def p_println(p):
    ''' PRINTLN : PRINTLN_KWD OPEN_PARENTHESIS PRINTABLE CLOSE_PARENTHESIS '''
    push_to_quads(Quad("PRNTLN", -1, -1, -1))
    DOT_OP_STACK.clear()

def p_printable(p):
    ''' PRINTABLE : EXPRESSION seen_printable PRINTABLE_P '''

def p_printable_p(p):
    ''' PRINTABLE_P : COMMA EXPRESSION seen_printable PRINTABLE_P
                    | empty '''

def p_seen_printable(p):
    ''' seen_printable  : empty '''
    printable_scope = SCOPES_STACK[-1]
    printable_is_attr = False
    printable = OPERAND_STACK.pop()
    if type(printable) == list:
        printable, printable_scope, printable_is_attr = printable
    printable_type = TYPE_STACK.pop()

    if printable_type in ["void", "object"]:
            EXCEPTION_HANDLER.raiseException(">> Type Error: Cannot print '" + printable_type + "' type")

    push_to_quads(Quad("PRNTBFFR", -1, -1, FUNC_DIR.get_symbol_mem_index(printable, printable_scope, printable_is_attr)))

def p_entered_condition(p):
    ''' entered_condition : empty '''
    CONDITIONAL_DEPTH_STACK.append("|CONDITION|")

def p_left_condition(p):
    ''' left_condition : empty '''
    CONDITIONAL_DEPTH_STACK.pop()

def p_decision(p):
    ''' DECISION : IF_KWD OPEN_PARENTHESIS EXPRESSION CLOSE_PARENTHESIS seen_if_kwd OPEN_CURLY entered_condition STATEMENT_STAR left_condition CLOSE_CURLY DECISION_P '''
    dir = JUMP_STACK.pop()
    fill_quad(dir, QUAD_POINTER)

def p_decision_p(p):
    ''' DECISION_P :            ELSE_KWD seen_else_kwd DECISION
                        |       ELSE_KWD seen_else_kwd OPEN_CURLY STATEMENT_STAR CLOSE_CURLY
                        |       empty '''

def p_seen_if_kwd(p):
    ''' seen_if_kwd : empty '''
    decision_statement()

def p_seen_else_kwd(p):
    ''' seen_else_kwd : empty '''
    push_to_quads(Quad("GOTO", -1, -1,"PND"))
    dir = JUMP_STACK.pop()
    JUMP_STACK.append(QUAD_POINTER - 1)
    fill_quad(dir, QUAD_POINTER)

def p_repetition(p):
    ''' REPETITION : CONDITIONAL_REP
                   | UNCONDITIONAL_REP '''

def p_conditional_rep(p):
    ''' CONDITIONAL_REP : WHILE_KWD seen_while_kwd OPEN_PARENTHESIS EXPRESSION CLOSE_PARENTHESIS seen_while_exp OPEN_CURLY entered_condition STATEMENT_STAR CLOSE_CURLY left_condition '''
    end_dir = JUMP_STACK.pop()
    return_dir = JUMP_STACK.pop()
    push_to_quads(Quad("GOTO", -1, -1, return_dir))
    fill_quad(end_dir, QUAD_POINTER)

def p_seen_while_kwd(p):
    ''' seen_while_kwd : empty '''
    JUMP_STACK.append(QUAD_POINTER)

def p_seen_while_exp(p):
    ''' seen_while_exp : empty '''
    decision_statement()

def p_unconditional_rep(p):
    ''' UNCONDITIONAL_REP : FOR_KWD OPEN_PARENTHESIS VAR seen_for_kwd EQUALS EXPRESSION seen_for_start_exp SEMI_COLON EXPRESSION seen_for_end_exp SEMI_COLON FOR_INCR_STATEMENT seen_for_incr_exp CLOSE_PARENTHESIS OPEN_CURLY entered_condition STATEMENT_STAR CLOSE_CURLY left_condition '''
    swap_end_dir = JUMP_STACK.pop()
    swap_start_dir = JUMP_STACK.pop()
    end_dir = JUMP_STACK.pop()
    loop_dir = JUMP_STACK.pop()

    incr_res = OPERAND_STACK.pop()

    for i in range(swap_start_dir, swap_end_dir):
        swap_quads(swap_start_dir, QUAD_POINTER) # This ensures that the increment statement will execute at the end of the for loop, and not at the start!

    push_to_quads(Quad("GOTO", -1, -1, loop_dir))
    fill_quad(end_dir, QUAD_POINTER)

def p_seen_for_kwd(p):
    ''' seen_for_kwd : empty '''
    OPERAND_STACK.append(FUNC_DIR.symbol_lookup(p[-1], SCOPES_STACK[-1]))
    TYPE_STACK.append(FUNC_DIR.symbol_type_lookup(p[-1], SCOPES_STACK[-1]))
    OPERATOR_STACK.append("=")

def p_seen_for_incr_exp(p):
    ''' seen_for_incr_exp : empty'''
    JUMP_STACK.append(QUAD_POINTER)

def p_seen_for_start_exp(p):
    ''' seen_for_start_exp : empty '''
    assign_to_var(True)
    JUMP_STACK.append(QUAD_POINTER)

def p_seen_for_end_exp(p):
    ''' seen_for_end_exp : empty '''

    expr_end_type = TYPE_STACK.pop()

    if SemanticCube[expr_end_type]["=="]["boolean"] == "err":
        EXCEPTION_HANDLER.raiseException(">> Type mismatch: non-boolean end expression in 'for' statement")

    res_scope = SCOPES_STACK[-1]
    res = OPERAND_STACK.pop()
    if type(res) == list:
        res, res_scope = res

    JUMP_STACK.append(QUAD_POINTER)
    push_to_quads(Quad("GOTOF", -1, FUNC_DIR.get_symbol_mem_index(res, res_scope), "PND"))
    JUMP_STACK.append(QUAD_POINTER)

def p_type(p):
    ''' TYPE :      TYPE_I
                |   TYPE_F
                |   TYPE_S
                |   TYPE_B
                |   ID seen_id_as_class_name
                |   TYPE_V '''

    if len(p) == 2: # Regular Type
        p[0] = p[1]
    else: # Class Type
        p[0] = p[2]

def p_seen_id_as_class_name(p):
    ''' seen_id_as_class_name : empty '''
    FUNC_DIR.valid_class_check(p[-1])
    p[0] = "object|" + p[-1]

def p_empty(p):
     'empty :'
     pass

def p_error(p): # Error rule for syntax errors
    EXCEPTION_HANDLER.raiseException(">> Syntax error! Unexpected token: '" + str(p.value) + "', of type '" + p.type + "'")

## Helper Action Methods ##
# a few methods that help reuse code on some of the similar actions thtat need to be taken by the parser in multiple situations #

def parse_vars_declaration(var_list):
    for list in var_list.split("||"):
        type = list.split(":")[1]
        class_name = None
        if "object" in type:
            type, class_name = type.split("|")
        for id in list.split(":")[0].split(','):
            if type == "void":
                EXCEPTION_HANDLER.raiseException(">> Type Error: Cannot declare 'void' type variables")
            if len(ARRAY_DIMENSION_STACK) and ARRAY_DIMENSION_STACK[0][0] == id:
                dims = ARRAY_DIMENSION_STACK.pop(0)
                FUNC_DIR.declare_symbol(id, type, SCOPES_STACK[-1], is_array = True, dimensions = dims[1:])
            else:
                FUNC_DIR.declare_symbol(id, type, SCOPES_STACK[-1])

            if class_name != None:
                FUNC_DIR.set_symbol_object_type(id, class_name, SCOPES_STACK[-1])

def get_ptr_value(left = None, right = None):
    ptr_value = -1

    if left != None:
        if FUNC_DIR.is_sym_ptr(left[0], left[1]):
            ptr_value = 1
    if right != None:
        if FUNC_DIR.is_sym_ptr(right[0], right[1]):
            if ptr_value > 0:
                ptr_value = 3
            else:
                ptr_value = 2

    return ptr_value

def generate_expression_quad():
    right_scope = left_scope= SCOPES_STACK[-1]
    right_operand = OPERAND_STACK.pop()
    right_attr = False
    if type(right_operand) == list:
        right_operand, right_scope, right_attr  = right_operand
    right_type = TYPE_STACK.pop()
    left_operand = OPERAND_STACK.pop()
    left_attr = False
    if type(left_operand) == list:
        left_operand, left_scope, left_attr = left_operand
    left_type = TYPE_STACK.pop()
    operator = OPERATOR_STACK.pop()
    result_type = SemanticCube[left_type][operator][right_type]

    if result_type != "err":
        result = FUNC_DIR.next_avail(result_type, SCOPES_STACK[-1])
        push_to_quads(Quad(operator, FUNC_DIR.get_symbol_mem_index(left_operand, left_scope, left_attr), FUNC_DIR.get_symbol_mem_index(right_operand, right_scope, right_attr), FUNC_DIR.get_symbol_mem_index(result, SCOPES_STACK[-1])))
        OPERAND_STACK.append(result)
        TYPE_STACK.append(result_type)
    else:
        EXCEPTION_HANDLER.raiseException(">> Type Mismatch: " + left_type + " " + operator + " " + right_type)

def parse_var(id, is_factor, is_io = 0):
    is_arr = False

    if type(id) == list:
        if id[0] == "ARRAY":
            is_arr = True
            id = id[1:]
        else:
            id = id[1]

    is_class_attr = (len(OBJECT_ACCESS_STACK) > 0) and OBJECT_ACCESS_STACK[-1] != "|ARG_WALL|"

    if is_arr:
        # It is an array!
        array_id, array_scope = id[0]
        FUNC_DIR.symbol_lookup(array_id, array_scope, is_class_attr)
        dims = FUNC_DIR.get_symbol_dimensions(array_id, array_scope, is_class_attr)
        access_values = id[1]

        if len(access_values) != len(dims):
            # Accessing array incompletely (would need to return an array obj)
            EXCEPTION_HANDLER.raiseException(">> Index Error: array " + array_id + " expects " + str(len(dims)) + " access indices, received " + str(len(access_values)))

        final_access_value = FUNC_DIR.next_avail("int", SCOPES_STACK[-1])
        # Here, we need to reset the values of all the temps used in the array index calculation, in case there is a loop going on, since it will use the same temporals over and over again, causing an eventual overflow
        push_to_quads(Quad("TMP_RESET", -1,  0, FUNC_DIR.get_symbol_mem_index(final_access_value, SCOPES_STACK[-1])))

        for i, d in enumerate(access_values):
            if type(d) != list:
                d = [d, SCOPES_STACK[-1]]
            try:
                d[0] = int(d[0]) # d might be an ID, or it might be a a CTE_I
            except:
                pass

            # Check if access value is in bounds
            push_to_quads(Quad("ARR_BNDS", -1, FUNC_DIR.get_symbol_mem_index(d[0], d[1]), dims[i]))

            if i == len(access_values) - 1:
                # We are reading the last dimension of the access values
                if len(access_values) == 1:
                    # This is a linear vector; simply access whatever index we just read
                    push_to_quads(Quad("=", -1, FUNC_DIR.get_symbol_mem_index(d[0], d[1]), FUNC_DIR.get_symbol_mem_index(final_access_value, SCOPES_STACK[-1])))
                else:
                    # This is a matrix; add the dimension we read to the final access_value
                    push_to_quads(Quad("+", FUNC_DIR.get_symbol_mem_index(final_access_value, SCOPES_STACK[-1]),  FUNC_DIR.get_symbol_mem_index(d[0], d[1]), FUNC_DIR.get_symbol_mem_index(final_access_value, SCOPES_STACK[-1])))

            else:
                access_increment = FUNC_DIR.next_avail("int", SCOPES_STACK[-1])
                # Defining a new temp; As above, need to set it to 0 in the case of a loop where its value could overflow
                push_to_quads(Quad("TMP_RESET", -1,  0, FUNC_DIR.get_symbol_mem_index(access_increment, SCOPES_STACK[-1])))
                push_to_quads(Quad("=", -1,  FUNC_DIR.get_symbol_mem_index(d[0], d[1]), FUNC_DIR.get_symbol_mem_index(access_increment, SCOPES_STACK[-1])))
                for j, size in enumerate(dims):
                    if i < j:
                        push_to_quads(Quad("*", FUNC_DIR.get_symbol_mem_index(access_increment, SCOPES_STACK[-1]),  FUNC_DIR.get_symbol_mem_index(int(size), SCOPES_STACK[-1]), FUNC_DIR.get_symbol_mem_index(access_increment, SCOPES_STACK[-1])))

                push_to_quads(Quad("+", FUNC_DIR.get_symbol_mem_index(final_access_value, SCOPES_STACK[-1]),  FUNC_DIR.get_symbol_mem_index(access_increment, SCOPES_STACK[-1]), FUNC_DIR.get_symbol_mem_index(final_access_value, SCOPES_STACK[-1])))


        array_type = FUNC_DIR.symbol_type_lookup(array_id, array_scope, is_class_attr)

        ptr_to_array_value_at_index = FUNC_DIR.next_avail("int", SCOPES_STACK[-1], is_ptr = True, arr_pointed = [array_id, array_scope])
        # Defining a new temp; As above, need to set it to 0 in the case of a loop where its value could overflow
        push_to_quads(Quad("TMP_RESET", -1,  0, FUNC_DIR.get_symbol_mem_index(ptr_to_array_value_at_index, SCOPES_STACK[-1])))

        # Check array value at index

        push_to_quads(Quad("ARR_ACCESS", FUNC_DIR.get_symbol_mem_index(array_id, array_scope, is_class_attr),  FUNC_DIR.get_symbol_mem_index(final_access_value, SCOPES_STACK[-1]), FUNC_DIR.get_symbol_mem_index(ptr_to_array_value_at_index, SCOPES_STACK[-1])))

        if not is_factor: # We are assigning to this array, need a pointer
            if is_class_attr:
                # Array as class attribute; Pass the parent object to class instance stack
                CLASS_INSTANCE_STACK.append(OBJECT_ACCESS_STACK.pop())

            OPERAND_STACK.append([FUNC_DIR.symbol_lookup(ptr_to_array_value_at_index, SCOPES_STACK[-1]), SCOPES_STACK[-1], is_class_attr])
            TYPE_STACK.append(array_type)

        else: # We are just using the value at this index, no need for a pointer; Can resolve into a tmp
            value_at_index = FUNC_DIR.next_avail(array_type, SCOPES_STACK[-1])
            # Defining a new temp; As above, so below. 93, 93 / 93
            push_to_quads(Quad("TMP_RESET", -1,  0, FUNC_DIR.get_symbol_mem_index(value_at_index, SCOPES_STACK[-1])))
            if not is_class_attr:
                # Global / local array! Just use a regular =
                push_to_quads(Quad("=", 1,  FUNC_DIR.get_symbol_mem_index(ptr_to_array_value_at_index, SCOPES_STACK[-1]), FUNC_DIR.get_symbol_mem_index(value_at_index, SCOPES_STACK[-1])))

                OPERAND_STACK.append([FUNC_DIR.symbol_lookup(value_at_index, SCOPES_STACK[-1]), SCOPES_STACK[-1], is_class_attr])
                TYPE_STACK.append(FUNC_DIR.symbol_type_lookup(value_at_index, SCOPES_STACK[-1]))

            else:
                # Array as an object attribute! Use OBJ_READ
                parent_obj_dir = -1
                parent_obj_id = OBJECT_ACCESS_STACK.pop()
                if parent_obj_id != "this_kwd":
                    parent_obj_dir = FUNC_DIR.get_symbol_mem_index(parent_obj_id, SCOPES_STACK[-1])

                push_to_quads(Quad("OBJ_READ", parent_obj_dir,  FUNC_DIR.get_symbol_mem_index(ptr_to_array_value_at_index, SCOPES_STACK[-1]), FUNC_DIR.get_symbol_mem_index(value_at_index, SCOPES_STACK[-1]), get_ptr_value([ptr_to_array_value_at_index, SCOPES_STACK[-1]], [value_at_index, SCOPES_STACK[-1]])))

                OPERAND_STACK.append(FUNC_DIR.symbol_lookup(value_at_index, SCOPES_STACK[-1]))
                TYPE_STACK.append(FUNC_DIR.symbol_type_lookup(value_at_index, SCOPES_STACK[-1]))

    else:
        # It is a regular (simple) variable!
        if not is_class_attr:
            # Regular Variable
            var = FUNC_DIR.symbol_lookup(id, SCOPES_STACK[-1], is_class_attr)
            if FUNC_DIR.is_sym_arr(id, SCOPES_STACK[-1], False) and not is_io:
                # Trying to access an array symbol without [] !
                EXCEPTION_HANDLER.raiseException(">> Name Error: symbol " + id + " is defined as an array and cannot be referenced directly (maybe missing [] operator?)")

            OPERAND_STACK.append([var, SCOPES_STACK[-1], is_class_attr])
            TYPE_STACK.append(FUNC_DIR.symbol_type_lookup(id, SCOPES_STACK[-1], is_class_attr))

        else:
            var = FUNC_DIR.symbol_lookup(id, DOT_OP_STACK[-1], True)
            # Class Variable
            if FUNC_DIR.is_sym_arr(id, DOT_OP_STACK[-1], is_class_attr) and not is_io:
                # Trying to access an array symbol without [] !
                EXCEPTION_HANDLER.raiseException(">> Name Error: symbol " + id + " is defined as an array and cannot be referenced directly (maybe missing [] operator?)")

            if not is_factor: # We are assigning to this object's attribute, need a pointer

                # Pass the parent object to class instance stack
                parent_obj = OBJECT_ACCESS_STACK[-1]
                if type(parent_obj) == list: # Parent object is within an object array!
                    CLASS_INSTANCE_STACK.append(OPERAND_STACK.pop()) # In this case, the parent obj has already been processed into a temp containing the address of it inside the array
                    TYPE_STACK.pop() # Remove "object" instance from typestack
                    OBJECT_ACCESS_STACK.pop() # Free up obj access stack anyway
                else:
                    CLASS_INSTANCE_STACK.append(OBJECT_ACCESS_STACK.pop()) # Just a regular parent object variable!

                OPERAND_STACK.append([var, DOT_OP_STACK[-1], is_class_attr])
                TYPE_STACK.append(FUNC_DIR.symbol_type_lookup(id, DOT_OP_STACK[-1], True))

            else: # We are just using the value from this object's attribute, no need for a pointer; Can resolve into a tmp

                attr_type = FUNC_DIR.symbol_type_lookup(id, DOT_OP_STACK[-1], True)
                value_at_attr = FUNC_DIR.next_avail(attr_type, SCOPES_STACK[-1])

                parent_obj = OBJECT_ACCESS_STACK[-1]
                parent_obj_is_ptr = -1
                if type(parent_obj) == list: # Parent object is within an object array!
                    parent_obj = OPERAND_STACK.pop()[0] # In this case, the parent obj has already been processed into a temp containing the address of it inside the array
                    TYPE_STACK.pop() # Remove "object" instance from typestack
                    OBJECT_ACCESS_STACK.pop() # Free up obj access stack anyway
                    parent_obj_is_ptr = 1
                else:
                    parent_obj = OBJECT_ACCESS_STACK.pop() # Just a regular parent object variable!

                if parent_obj == "this_kwd":
                    push_to_quads(Quad("OBJ_READ", -1, FUNC_DIR.get_symbol_mem_index(var, DOT_OP_STACK[-1], is_class_attr), FUNC_DIR.get_symbol_mem_index(value_at_attr, SCOPES_STACK[-1])))
                else:
                    push_to_quads(Quad("OBJ_READ", FUNC_DIR.get_symbol_mem_index(parent_obj, SCOPES_STACK[-1]), FUNC_DIR.get_symbol_mem_index(var, DOT_OP_STACK[-1], is_class_attr), FUNC_DIR.get_symbol_mem_index(value_at_attr, SCOPES_STACK[-1]), -1, parent_obj_is_ptr))

                OPERAND_STACK.append(FUNC_DIR.symbol_lookup(value_at_attr, SCOPES_STACK[-1]))
                TYPE_STACK.append(attr_type)

    if len(DOT_OP_STACK):
        DOT_OP_STACK.pop()

def assign_to_var(push_back_operand = False):
    op = OPERATOR_STACK.pop()
    right_scope = res_scope = SCOPES_STACK[-1]
    right_attr = False
    right_operand =  OPERAND_STACK.pop()
    if type(right_operand) == list:
        right_operand, right_scope, right_attr  = right_operand
    res = OPERAND_STACK.pop()
    res_attr = False
    if type(res) == list:
        res, res_scope, res_attr = res
    right_type  = TYPE_STACK.pop()
    res_type = TYPE_STACK.pop()

    if SemanticCube[res_type][op][right_type] == "err":
        EXCEPTION_HANDLER.raiseException(">> Type Mismatch: " + res_type + " " + op + " " + right_type)

    class_idx = -1
    if res_type == "object":
        # We are assigning to an object, which means we are instantiating it!
        # First lets check this is ACTUALLY an instantation  and check  if the right operand is a temporal:
        if not  len(CLASS_INSTANCE_STACK): # Its not an instantation!
            EXCEPTION_HANDLER.raiseException(">> Type Error: cannot assign to objects directly, only by instantiation!")
        CLASS_INSTANCE_STACK.pop() # Remove the instantiation validation
        class_type = FUNC_DIR.get_symbol_object_type(right_operand, SCOPES_STACK[-1]) # Get the class type from the right operand of the =
        class_idx = FUNC_DIR.get_class_idx(class_type) # From that, find out what the class index is
        if FUNC_DIR.is_sym_ptr(res, res_scope): # If we are instantiating into an array,
            arr_pointed = FUNC_DIR.get_arr_pointed(res, res_scope) # We need to check if this array has the appropriate (if any) class type, and update it if needed
            arr_pointed_object_type = FUNC_DIR.get_symbol_object_type(arr_pointed[0], arr_pointed[1])
            if arr_pointed_object_type != class_type:
                EXCEPTION_HANDLER.raiseException(">> Type Error: " + arr_pointed_object_type + " = " + class_type)
        else:
            res_class_type = FUNC_DIR.get_symbol_object_type(res, res_scope)
            if res_class_type != class_type:
                EXCEPTION_HANDLER.raiseException(">> Type Error: " + res_class_type + " = " + class_type)
            FUNC_DIR.set_symbol_object_type(res, class_type, SCOPES_STACK[-1]) # Set this object's type


    if not res_attr:
        if class_idx == -1:
            # Assigning to regular variable; Use =
            push_to_quads(Quad("=", get_ptr_value([right_operand, right_scope], [res, res_scope]), FUNC_DIR.get_symbol_mem_index(right_operand, right_scope, right_attr), FUNC_DIR.get_symbol_mem_index(res, res_scope, res_attr)))
        else:
            # Assigning to Object variable; Use OBJ_INST

            res_is_ptr = -1
            if FUNC_DIR.is_sym_ptr(res, res_scope):
                res_is_ptr = 1

            push_to_quads(Quad("OBJ_INST", res_is_ptr, class_idx, FUNC_DIR.get_symbol_mem_index(res, res_scope, res_attr)))
    else:
        # Assigning to class variable; Use OBJ_WRITE

        if FUNC_DIR.is_sym_ptr(res, res_scope):
            res_attr = False # This is for the special case of writing to an object's array variable;
                             # Since res will contain a temporal with its value set to the obj arr var memory index,
                             # As classes do not contain temporals, we now need to use res_attr as False so that get_symbol_mem_index
                             # can find it within the current local scope

        parent_obj = CLASS_INSTANCE_STACK.pop()
        parent_obj_scope = SCOPES_STACK[-1]
        parent_obj_is_ptr = -1
        if type(parent_obj) == list:
            parent_obj, parent_obj_scope = parent_obj[0], parent_obj[1]
            parent_obj_is_ptr = 1

        if parent_obj == "this_kwd":
            push_to_quads(Quad("OBJ_WRITE", -1, FUNC_DIR.get_symbol_mem_index(right_operand, right_scope, right_attr), FUNC_DIR.get_symbol_mem_index(res, res_scope, res_attr), get_ptr_value([right_operand, right_scope], [res, res_scope])))
        else:
            push_to_quads(Quad("OBJ_WRITE", FUNC_DIR.get_symbol_mem_index(parent_obj, parent_obj_scope), FUNC_DIR.get_symbol_mem_index(right_operand, right_scope, right_attr), FUNC_DIR.get_symbol_mem_index(res, res_scope, res_attr), get_ptr_value([right_operand, right_scope], [res, res_scope]), parent_obj_is_ptr))

    if push_back_operand:
        OPERAND_STACK.append(res)

def parse_compound_asignment(op):
    OPERATOR_STACK.append('=')

    if FUNC_DIR.is_sym_ptr(OPERAND_STACK[-1][0], OPERAND_STACK[-1][1]):
        # Since this is an array, need to figure out the pointer from the left side of the compound assignment into a factor on the left side
        value_at_index = FUNC_DIR.next_avail(TYPE_STACK[-1], SCOPES_STACK[-1])
        if not OPERAND_STACK[-1][2]:
            # Global / local array! Just use a regular =
            push_to_quads(Quad("=", 1,  FUNC_DIR.get_symbol_mem_index(OPERAND_STACK[-1][0], OPERAND_STACK[-1][1]), FUNC_DIR.get_symbol_mem_index(value_at_index, SCOPES_STACK[-1])))

            OPERAND_STACK.append([FUNC_DIR.symbol_lookup(value_at_index, SCOPES_STACK[-1]), SCOPES_STACK[-1], OPERAND_STACK[-1][2]])

        else:
            # Array as an object attribute! Use OBJ_READ
            parent_obj_dir = -1
            parent_obj_id = CLASS_INSTANCE_STACK[-1]
            if parent_obj_id != "this_kwd":
                parent_obj_dir = FUNC_DIR.get_symbol_mem_index(parent_obj_id, SCOPES_STACK[-1])

            push_to_quads(Quad("OBJ_READ", parent_obj_dir,  FUNC_DIR.get_symbol_mem_index(OPERAND_STACK[-1][0], OPERAND_STACK[-1][1]), FUNC_DIR.get_symbol_mem_index(value_at_index, SCOPES_STACK[-1]), get_ptr_value([OPERAND_STACK[-1][0], OPERAND_STACK[-1][1]], [value_at_index, SCOPES_STACK[-1]])))

            OPERAND_STACK.append(FUNC_DIR.symbol_lookup(value_at_index, SCOPES_STACK[-1]))

    elif OPERAND_STACK[-1][2]:
        # Just a class varible, need to use OBJ_READ to turn it into the actual value for the left side of the compound assignment
        value_at_attr = FUNC_DIR.next_avail(TYPE_STACK[-1], SCOPES_STACK[-1])

        parent_object = CLASS_INSTANCE_STACK[-1]
        parent_object_scope = SCOPES_STACK[-1]
        parent_obj_is_ptr = -1
        if type(parent_object) == list: # Parent object is inside of an object array!
            parent_object, parent_object_scope = parent_object[0], parent_object[1]
            parent_obj_is_ptr = 1

        if parent_object == "this_kwd":
            push_to_quads(Quad("OBJ_READ", -1, FUNC_DIR.get_symbol_mem_index(OPERAND_STACK[-1][0], OPERAND_STACK[-1][1], OPERAND_STACK[-1][2]), FUNC_DIR.get_symbol_mem_index(value_at_attr, SCOPES_STACK[-1])))
        else:
            push_to_quads(Quad("OBJ_READ", FUNC_DIR.get_symbol_mem_index(parent_object, parent_object_scope), FUNC_DIR.get_symbol_mem_index(OPERAND_STACK[-1][0], OPERAND_STACK[-1][1], OPERAND_STACK[-1][2]), FUNC_DIR.get_symbol_mem_index(value_at_attr, SCOPES_STACK[-1]), -1, parent_obj_is_ptr))

        OPERAND_STACK.append(FUNC_DIR.symbol_lookup(value_at_attr, SCOPES_STACK[-1]))


    else:
        OPERAND_STACK.append(OPERAND_STACK[-1])

    TYPE_STACK.append(TYPE_STACK[-1])

    if op in ['++', '--']: # Increment / decrement compound assignment!
        if TYPE_STACK[-1] not in ["int", "float"]:
            EXCEPTION_HANDLER.raiseException(">> Type Error: cannot use " + op + " operator with " + TYPE_STACK[-1] + " type variable")

        OPERATOR_STACK.append(op[0])
        unit_temp = FUNC_DIR.next_avail("int", SCOPES_STACK[-1])
        push_to_quads(Quad("TMP_RESET", -1, 1, FUNC_DIR.get_symbol_mem_index(unit_temp, SCOPES_STACK[-1])))
        OPERAND_STACK.append(unit_temp)
        TYPE_STACK.append("int")

        generate_expression_quad()

    else: # Just a regular compound assignment!
        OPERATOR_STACK.append(op)

def decision_statement():
    expr_type = TYPE_STACK.pop()

    if SemanticCube[expr_type]["=="]["boolean"] == "err":
        EXCEPTION_HANDLER.raiseException(">> Type Mismatch: non-boolean (" + expr_type + ") expression in decision statement")

    res_scope = SCOPES_STACK[-1]
    res_attr = False
    res = OPERAND_STACK.pop()
    if type(res) == list:
        res, res_scope, res_attr = res
    push_to_quads(Quad("GOTOF", -1, FUNC_DIR.get_symbol_mem_index(res, res_scope, res_attr), "PND"))
    JUMP_STACK.append(QUAD_POINTER - 1)

def fill_vm_file(file_path, marker_str, start_str, end_str, info):
    line_indices = []
    with open(file_path, "r") as f:
        contents = f.readlines()

        for i, c in enumerate(contents):
            if c == marker_str:
                line_indices.append(i)

    info_size = len(info)
    if not info_size:
        info_size = 1

    # IF THERE ARE MORE/LESS LINES THAN LAST TIME...
    quad_size_diff = info_size - (line_indices[1] - line_indices[0]) + 2

    for i in range(quad_size_diff):
        contents.insert(line_indices[1], "\n") # More info! Add more lines

    for i in range(-quad_size_diff):
        contents.pop(line_indices[0] + info_size) # Less info! Get rid of useless lines

    insert_start_index =  line_indices[0] + 2
    insert_end_index = insert_start_index + info_size

    contents[line_indices[0] + 1] = start_str

    if len(info):
        for i in range(insert_start_index, insert_end_index):
            contents[i] = info[i - insert_start_index]

    if "};" not in contents[insert_end_index - 1]:
        contents[insert_end_index] = end_str + marker_str
    else:
        contents[insert_end_index] = marker_str

    with open(VM_FILE_PATH, "w") as f:
        contents = "".join(contents)
        f.write(contents)

## Constants to write to VM file for C++ compilation ##

VM_FILE_PATH = "VM/main.cpp"

VM_QUAD_MARKER_STR = "// QUADS //\n"
VM_QUAD_START_STR = "const vector<vector<int>> QUADS = {\n"
VM_QUAD_END_STR = "\t" * 10 + "};\n"

VM_MEMORY_CONSTRAINTS_MARKER_STR = "// MEMORY_CONSTRAINTS //\n"
VM_MEMORY_CONSTRAINTS_START_STR = ""
VM_MEMORY_CONSTRAINTS_END_STR = ""

VM_FUNCTION_MEMORY_MARKER_STR = "// FUNCTION_MEMORY //\n"
VM_FUNCTION_MEMORY_START_STR = "const map<int, vector<vector<int>>> FUNCTION_MEMORY_CONTEXT_SIGN = {\n"
VM_FUNCTION_MEMORY_END_STR = "\t" * 10 + "};\n"

VM_OBJECT_MEMORY_MARKER_STR = "// OBJECT_MEMORY //\n"
VM_OBJECT_MEMORY_START_STR = "const map<int, vector<int>> OBJECT_MEMORY_CONTEXT_SIGN = {\n"
VM_OBJECT_MEMORY_END_STR = "\t" * 10 + "};\n"

VM_CONSTANTS_MARKER_STR = "// CONSTANTS //\n"
VM_CONSTANTS_START_STR = "const map<int, string> CONSTANTS = {\n"
VM_CONSTANTS_END_STR = "\t" * 10 + "};\n"

## Main Compiler Method ##

def main(argv):

    # Build the parser
    parser = yacc.yacc()

    output_file_path = None
    input_file_path = None

    while len(argv):
        if len(argv) == 1:
            input_file_path = argv.pop()
            break

        arg = argv.pop()
        param = argv.pop()

        if param == "-i":
            input_file_path = arg
        elif param == "-o":
            output_file_path = arg
        else:
            EXCEPTION_HANDLER.raiseException(">> Param Error! Use -i for input file path (assumed as first parameter) and -o for output file path.")

    if input_file_path == None:
        EXCEPTION_HANDLER.raiseException(">> Param Error! Please provide an input file path (assumed as first parameter)")

    EXCEPTION_HANDLER.setSourceFilePath(input_file_path)

    lex_data = ""
    with open(input_file_path) as source_file:
        lines = source_file.readlines()
        for line in lines:
            lex_data += line
        print(">> Parsing " + input_file_path + "...")
        parser.parse(lex_data)

    mem_constraints_str = "const int MAX_CONSTANTS = " + str(MAX_CONSTANTS) + ", MAX_SYMBOLS = " + str(MAX_SYMBOLS) + ", MAX_TMP_SYMBOLS = " + str(MAX_TMP_SYMBOLS) + ", MAX_OBJ_SYMBOLS = " + str(MAX_OBJ_SYMBOLS) + ", VAR_TYPES = " + str(FunctionDirectory.VAR_TYPES) + ", MEMORY_STACK_LIMIT = " + str(MEMORY_STACK_LIMIT) + ";"

    fill_vm_file(VM_FILE_PATH, VM_MEMORY_CONSTRAINTS_MARKER_STR, mem_constraints_str, VM_MEMORY_CONSTRAINTS_END_STR, [])

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
                    mem_sign = "\t" * 10 +  "{" + str(FUNC_DIR.get_start_addr(func, context)) + ", {{" + ",".join([str(x) for x in list(FUNC_DIR.FUNCS[context][func][2].var_memory_signature.values())]) + "}"
                    temp_sign = "{" + ",".join([str(x) for x in list(FUNC_DIR.FUNCS[context][func][2].temp_memory_signature.values())]) + "}}},\n"
                    vm_func_memory.append(mem_sign + ", " + temp_sign)
            else:
                for func in FUNC_DIR.FUNCS[context]["FUNCS"].keys():
                    mem_sign = "\t" * 10 +  "{" + str(FUNC_DIR.get_start_addr(func, context)) + ", {{" + ",".join([str(x) for x in list(FUNC_DIR.FUNCS[context]["FUNCS"][func][2].var_memory_signature.values())]) + "}"
                    temp_sign = "{" + ",".join([str(x) for x in list(FUNC_DIR.FUNCS[context]["FUNCS"][func][2].temp_memory_signature.values())]) + "}}},\n"
                    vm_func_memory.append(mem_sign + ", " + temp_sign)

    fill_vm_file(VM_FILE_PATH, VM_FUNCTION_MEMORY_MARKER_STR, VM_FUNCTION_MEMORY_START_STR, VM_FUNCTION_MEMORY_END_STR, vm_func_memory)

    vm_obj_memory = []
    for i, context in enumerate(FUNC_DIR.FUNCS.keys()):
        if context not in [FUNC_DIR.program_name, "GLOBAL"]:
            mem_sign = "\t" * 10 +  '{' + str(i) + ', {' + ",".join([str(x) for x in list(FUNC_DIR.FUNCS[context]["SYMBOLS"].var_memory_signature.values())]) + "}},\n"
            vm_obj_memory.append(mem_sign)

    fill_vm_file(VM_FILE_PATH, VM_OBJECT_MEMORY_MARKER_STR, VM_OBJECT_MEMORY_START_STR, VM_OBJECT_MEMORY_END_STR, vm_obj_memory)


    vm_constants = []
    for id in FUNC_DIR.FUNCS[FUNC_DIR.program_name].SYMBOLS.keys():
        var = FUNC_DIR.FUNCS[FUNC_DIR.program_name].SYMBOLS[id]
        if var[3] or var[7] != None: # If is constant OR object
            if id in SymbolTable.TRUTH: # Bool constant
                constant_string = "\t" * 10 + "{" + str(var[1]) + ', "' + str(SymbolTable.TRUTH.index(id)) + '"},\n'
            elif var[7] != None:  # Object to be initialized
                constant_string = "\t" * 10 + "{" + str(var[1]) + ', "' + str(FUNC_DIR.get_class_idx(var[7])) + '"},\n'
            elif isinstance(id, str): # String Constant
                constant_string = "\t" * 10 + "{" + str(var[1]) + ', "' + id[1:-1] + '"},\n'
            else: # Int / Float constant
                constant_string = "\t" * 10 + "{" + str(var[1]) + ', "' + str(id) + '"},\n'
            vm_constants.append(constant_string)

    fill_vm_file(VM_FILE_PATH, VM_CONSTANTS_MARKER_STR, VM_CONSTANTS_START_STR, VM_CONSTANTS_END_STR, vm_constants)


    vm_quads = []
    for i in range(len(QUADS)):
        vm_quads.append("\t" * 10 + QUADS[i].get_cpp_string() + "\n")

    fill_vm_file(VM_FILE_PATH, VM_QUAD_MARKER_STR, VM_QUAD_START_STR, VM_QUAD_END_STR, vm_quads)

    if output_file_path == None:
        output_file_path = FUNC_DIR.program_name

    print(">> Compiling " + input_file_path + " into " + output_file_path)
    if not os.system('g++ ' + VM_FILE_PATH + ' -o ' + output_file_path):
        print(">> Compilation Successfull!")

## Runs main upon invoking this script with python nuca_script.py ##
if __name__=='__main__':
    main(sys.argv[1:])
