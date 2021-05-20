# Guilherme Bittencourt de Borba
# A01194571
# Diseno de Compiladores
# ------------------------------------------------------------

import sys, os, getopt

import ply.lex as lex
import ply.yacc as yacc

from Compiler.SymbolTable import *
from Compiler.FunctionDirectory import *
from Compiler.Quad import *

# List of token names.   This is always required
tokens = [
'SEMI_COLON',
'COLON',
'COMMA',
'OPEN_CURLY',
'CLOSE_CURLY',
'OPEN_BRACKET',
'CLOSE_BRACKET',
'EQUALS',
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
'DIFFERENT',

'CTE_I',
'CTE_F',
'CTE_S',
'ID',


]

reserved = {

    'program' : 'PROGRAM_KWD',
    'ATTR' : 'ATTR_KWD',
    'VARS' : 'VARS_KWD',
    'main' : 'MAIN_KWD',
    'class' : 'CLASS_KWD',
    'derives' : 'DERIVES_KWD',
    'println' : 'PRINTLN_KWD',
    'print' : 'PRINT_KWD',
    'read' : 'READ_KWD',
    'return' : 'RETURN_KWD',
    'while' : 'WHILE_KWD',
    'for' : 'FOR_KWD',
    'if' : 'IF_KWD',
    'else' : 'ELSE_KWD',
    'int' : 'TYPE_I',
    'float' : 'TYPE_F',
    'string' : 'TYPE_S',
    'boolean' : 'TYPE_B',
    'void' : 'TYPE_V',
}


tokens += list(reserved.values())

# A string containing ignored characters (spaces and tabs)
t_SEMI_COLON                =   r';'
t_COLON                     =   r':'
t_COMMA                     =   r','
t_OPEN_CURLY                =   r'\{'
t_CLOSE_CURLY               =   r'\}'
t_OPEN_BRACKET                =   r'\['
t_CLOSE_BRACKET               =   r'\]'
t_OPEN_PARENTHESIS          =   r'\('
t_CLOSE_PARENTHESIS         =   r'\)'
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
t_DIFFERENT                 =   r'\<\>'



t_ignore  = ' \t'

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
    r'//((?!/).)*//'

# Define a rule so we can track line numbers
def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

# Error handling rule
def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)

# Build the lexer
lexer = lex.lex()

'''

// IDEAS //

    FUNCTIONS:

        -> overloaded functions?
        -> default arguments?
        -> builtin methods? (wait, exit, etc..)

    OTHER:

        -> allow max memory customization (also max call stack) via command line inpus (argv)
        -> atom syntactic highliter ?

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// VIRTUAL MEMORY MODEL //

    [0,                                                                             MAX_CONSTANTS - 1]                                                              ->          Constant Ints
    [MAX_CONSTANTS,                                                                 2 * MAX_CONSTANTS - 1]                                                          ->          Constant Floats
    [2 * MAX_CONSTANTS,                                                             3 * MAX_CONSTANTS - 1]                                                          ->          Constant Strings
    [3 * MAX_CONSTANTS,                                                             4 * MAX_CONSTANTS - 1]                                                          ->          Constant Booleans
    [4 * MAX_CONSTANTS,                                                             4 * MAX_CONSTANTS + MAX_SYMBOLS - 1]                                            ->          Global Ints
    [4 * MAX_CONSTANTS + MAX_SYMBOLS,                                               4 * MAX_CONSTANTS + 2 * MAX_SYMBOLS - 1]                                        ->          Global Floats
    [4 * MAX_CONSTANTS + 2 * MAX_SYMBOLS,                                           4 * MAX_CONSTANTS + 3 * MAX_SYMBOLS - 1]                                        ->          Global Strings
    [4 * MAX_CONSTANTS + 3 * MAX_SYMBOLS,                                           4 * MAX_CONSTANTS + 4 * MAX_SYMBOLS - 1]                                        ->          Global Booleans
    [4 * MAX_CONSTANTS + 4 * MAX_SYMBOLS,                                           4 * MAX_CONSTANTS + 4 * MAX_SYMBOLS + MAX_TMP_SYMBOLS - 1]                      ->          Global Temp Ints
    [4 * MAX_CONSTANTS + 4 * MAX_SYMBOLS + MAX_TMP_SYMBOLS,                         4 * MAX_CONSTANTS + 4 * MAX_SYMBOLS + 2 * MAX_TMP_SYMBOLS - 1]                  ->          Global Temp Floats
    [4 * MAX_CONSTANTS + 4 * MAX_SYMBOLS + 2 * MAX_TMP_SYMBOLS,                     4 * MAX_CONSTANTS + 4 * MAX_SYMBOLS + 3 * MAX_TMP_SYMBOLS - 1]                  ->          Global Temp Strings
    [4 * MAX_CONSTANTS + 4 * MAX_SYMBOLS + 3 * MAX_TMP_SYMBOLS,                     4 * MAX_CONSTANTS + 4 * MAX_SYMBOLS + 4 * MAX_TMP_SYMBOLS - 1]                  ->          Global Temp Booleans
    [4 * MAX_CONSTANTS + 4 * MAX_SYMBOLS + 4 * MAX_TMP_SYMBOLS,                     4 * MAX_CONSTANTS + 5 * MAX_SYMBOLS + 4 * MAX_TMP_SYMBOLS - 1]                  ->          Local Ints
    [4 * MAX_CONSTANTS + 5 * MAX_SYMBOLS + 4 * MAX_TMP_SYMBOLS,                     4 * MAX_CONSTANTS + 6 * MAX_SYMBOLS + 4 * MAX_TMP_SYMBOLS - 1]                  ->          Local Floats
    [4 * MAX_CONSTANTS + 6 * MAX_SYMBOLS + 4 * MAX_TMP_SYMBOLS,                     4 * MAX_CONSTANTS + 7 * MAX_SYMBOLS + 4 * MAX_TMP_SYMBOLS - 1]                  ->          Local Strings
    [4 * MAX_CONSTANTS + 7 * MAX_SYMBOLS + 4 * MAX_TMP_SYMBOLS,                     4 * MAX_CONSTANTS + 8 * MAX_SYMBOLS + 4 * MAX_TMP_SYMBOLS - 1]                  ->          Local Booleans
    [4 * MAX_CONSTANTS + 8 * MAX_SYMBOLS + 4 * MAX_TMP_SYMBOLS,                     4 * MAX_CONSTANTS + 8 * MAX_SYMBOLS + 5 * MAX_TMP_SYMBOLS - 1]                  ->          Local Temp Ints
    [4 * MAX_CONSTANTS + 8 * MAX_SYMBOLS + 5 * MAX_TMP_SYMBOLS,                     4 * MAX_CONSTANTS + 8 * MAX_SYMBOLS + 6 * MAX_TMP_SYMBOLS - 1]                  ->          Local Temp Floats
    [4 * MAX_CONSTANTS + 8 * MAX_SYMBOLS + 6 * MAX_TMP_SYMBOLS,                     4 * MAX_CONSTANTS + 8 * MAX_SYMBOLS + 7 * MAX_TMP_SYMBOLS - 1]                  ->          Local Temp Strings
    [4 * MAX_CONSTANTS + 8 * MAX_SYMBOLS + 7 * MAX_TMP_SYMBOLS,                     4 * MAX_CONSTANTS + 8 * MAX_SYMBOLS + 8 * MAX_TMP_SYMBOLS - 1]                  ->          Local Temp Booleans

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// SPRINT //

// TODO : Implement list syntax and quad generation!

    1. Implement a way to check during runtime wether or not the array is being indexed out of bounds
    2. Have funcs take arrays as arguments

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// BACKLOG //

// TODO : Refactor files and methods

// TODO : Add +=,-=, *= and /= operators as possible ASSIGN statements in grammar and SemanticCube

// TODO : Fix shift/reduce && reduce/reduce conflict warnings

// TODO : Make list of includes/dependencies and add them to the project

// TODO: Update Formal grammar and flow diagrams.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

'''

# Now to parsing!

MAX_CONSTANTS = 1000        # (per type)
MAX_SYMBOLS = 3000          # (per type)
MAX_TMP_SYMBOLS = 3000      # (per type)
MEMORY_STACK_LIMIT = 100000

FUNC_DIR = FunctionDirectory([MAX_CONSTANTS, MAX_SYMBOLS, MAX_TMP_SYMBOLS])
OPERATOR_STACK = []
OPERAND_STACK = []
TYPE_STACK = []
JUMP_STACK = []
FUNC_CALL_STACK = []
ARRAY_DIMENSION_STACK = []
QUAD_POINTER = 1
QUADS = [Quad("GOTO", -1, -1, "PND")]

def push_to_quads(q):
    global QUADS
    global QUAD_POINTER
    QUADS.append(q)
    QUAD_POINTER += 1

def fill_quad(dir, fill):
    global QUADS
    global QUAD_POINTER

    q = QUADS[dir]

    if q.result == "PND":
        q.result = fill
    else:
        raise Exception("Quad Error: trying to fill complete quad")

def swap_quads(q1, q2):
    if q2 > len(QUADS) - 1:
        QUADS.append(QUADS.pop(q1))
        for q in QUADS:
            if q.operator in [OPCodes["GOTO"], OPCodes["GOTOF"]] and q.result != "PND": # If this QUAD is either a GOTO or a GOTOF...
                if q.result > q1: # And was pointing to a quad placed after (bigger index) the one we popped...
                    # Jump dir has been changed since we popped a quad that came before the one we were jumping to
                    q.result -= 1 # Adjust the value
    else:
        temp = QUADS[q2]
        QUADS[q2] = QUADS[q1]
        QUADS[q1] = temp

# First lets define our grammar rules...

def p_program(p):
    ''' PROGRAM : PROGRAM_KWD ID seen_program_id SEMI_COLON CLASS_STAR GLOBAL_VAR FUNC_DEF_STAR MAIN_KWD OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_CURLY seen_main_kwd STATEMENT_STAR CLOSE_CURLY '''
    push_to_quads(Quad("END", -1, -1, -1))
    print(">> Syntax Approved!")

def p_seen_program_id(p):
    ''' seen_program_id : empty '''
    FUNC_DIR.declare_function(p[-1], "void", "PROGRAM")

def p_seen_main_kwd(p):
    ''' seen_main_kwd : empty '''
    FUNC_DIR.set_main_start_addr(QUAD_POINTER)
    fill_quad(0, QUAD_POINTER)

def p_class_star(p):
    ''' CLASS_STAR : CLASS CLASS_STAR
                   | empty '''

def p_class(p):
    ''' CLASS : CLASS_KWD ID SMALLER DERIVES_KWD TYPE BIGGER OPEN_CURLY CLASS_ATTR FUNC_DEF_STAR CLOSE_CURLY '''

def p_class_attr(p):
    ''' CLASS_ATTR : ATTR_KWD OPEN_CURLY VAR_LIST_STAR CLOSE_CURLY '''

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
                    | ARRAY_DEFINITION SYMBOL_LIST_P  '''
    p[0] = p[1]
    if p[2] != None:
        p[0] += p[2]

def p_symbol_list_p(p):
    ''' SYMBOL_LIST_P : COMMA ID SYMBOL_LIST_P
                    |   COMMA ARRAY_DEFINITION SYMBOL_LIST_P
                    | empty '''
    if p[1] == ',':
        p[0] = ',' + p[2]
        if p[3] != None:
            p[0] += p[3]

def p_readable_list(p):
    ''' READABLE_LIST : VAR seen_readable READABLE_LIST_P '''

def p_readable_list_p(p):
    ''' READABLE_LIST_P : COMMA VAR seen_readable READABLE_LIST_P
                  | empty '''

def p_seen_readable(p):
    ''' seen_readable  : empty '''
    push_to_quads(Quad("READ", -1, -1, FUNC_DIR.get_symbol_mem_index(FUNC_DIR.symbol_lookup(p[-1]))))

def p_global_var(p):
    ''' GLOBAL_VAR : VAR_LIST_STAR '''
    for list in p[1].split("||"):
        type = list.split(":")[1]
        for id in list.split(":")[0].split(','):
            if len(ARRAY_DIMENSION_STACK) and ARRAY_DIMENSION_STACK[0][0] == id:
                dims = ARRAY_DIMENSION_STACK.pop(0)
                FUNC_DIR.declare_symbol(id, type, is_array = True, dimensions = dims[1:])
            else:
                FUNC_DIR.declare_symbol(id, type)

def p_func_def_star(p):
    ''' FUNC_DEF_STAR : FUNC_DEF FUNC_DEF_STAR
                      | empty '''

def p_func_def(p):
    ''' FUNC_DEF : TYPE ID seen_func_id OPEN_PARENTHESIS FUNC_PARAM CLOSE_PARENTHESIS seen_func_params VARS seen_func_vars OPEN_CURLY FUNC_STATEMENT_STAR CLOSE_CURLY '''
    if not FUNC_DIR.valid_return_check(QUAD_POINTER - 1):
        FUNC_DIR.return_type_check("void", QUAD_POINTER)
        push_to_quads(Quad("ENDFNC", -1, -1, -1))

    FUNC_DIR.current_scope = None
    FUNC_DIR.AVAIL.reset_counter()

def p_seen_func_id(p):
    ''' seen_func_id : empty '''
    FUNC_DIR.declare_function(p[-1], p[-2])

def p_seen_func_params(p):
    ''' seen_func_params : empty '''

    if p[-2] != None:
        for list in p[-2].split(","):
            id, type = list.split(":")
            FUNC_DIR.declare_param(id, type)

def p_seen_func_vars(p):
    ''' seen_func_vars : empty '''
    if p[-1] != None:
        for list in p[-1].split("||"):
            type = list.split(":")[1]
            for id in list.split(":")[0].split(','):
                if len(ARRAY_DIMENSION_STACK) and ARRAY_DIMENSION_STACK[0][0] == id:
                    dims = ARRAY_DIMENSION_STACK.pop(0)
                    FUNC_DIR.declare_symbol(id, type, is_array = True, dimensions = dims[1:])
                else:
                    FUNC_DIR.declare_symbol(id, type)

    FUNC_DIR.set_start_addr(QUAD_POINTER)

def p_func_param(p):
    ''' FUNC_PARAM : VAR_DECLARATION FUNC_PARAM_P
                   | empty '''

    if len(p) > 2:
        p[0] = p[1]
        if p[2] != None:
            p[0] += p[2]

def p_func_param_p(p):
    ''' FUNC_PARAM_P : COMMA VAR_DECLARATION FUNC_PARAM_P
                     | empty '''

    if len(p) > 2:
        p[0] = "," + p[2]
        if p[3] != None:
            p[0] += p[3]

def p_var_declaration(p):
    ''' VAR_DECLARATION : ID COLON TYPE '''
    p[0] = p[1] + ":" + p[3]

def p_vars(p):
    ''' VARS : VARS_KWD OPEN_CURLY VAR_LIST_STAR CLOSE_CURLY '''
    p[0] = p[3]

def p_func_statement_star(p):
    ''' FUNC_STATEMENT_STAR :      ASSIGN SEMI_COLON FUNC_STATEMENT_STAR
                                |  FUNC_CALL SEMI_COLON FUNC_STATEMENT_STAR
                                |  READ SEMI_COLON FUNC_STATEMENT_STAR
                                |  PRINT SEMI_COLON FUNC_STATEMENT_STAR
                                |  PRINTLN SEMI_COLON FUNC_STATEMENT_STAR
                                |  FUNC_FLOW_CONTROL FUNC_STATEMENT_STAR
                                |  FUNC_RETURN FUNC_STATEMENT_STAR
                                |  empty '''

def p_statement_star(p):
    ''' STATEMENT_STAR :  STATEMENT STATEMENT_STAR
                       | empty '''

def p_statement(p):
    ''' STATEMENT : ASSIGN SEMI_COLON
                  | FUNC_CALL SEMI_COLON
                  | READ SEMI_COLON
                  | PRINT SEMI_COLON
                  | PRINTLN SEMI_COLON
                  | FLOW_CONTROL '''

def p_flow_control(p):
    ''' FLOW_CONTROL :      DECISION
                        |   REPETITION '''

def p_func_flow_control(p):
    ''' FUNC_FLOW_CONTROL :     FUNC_DECISION
                            |   FUNC_REPETITION '''

def p_for_incr_statement(p):
    ''' FOR_INCR_STATEMENT :    ASSIGN
                              | FUNC_CALL
                              | READ
                              | PRINT
                              | PRINTLN '''

def p_assign(p):
    ''' ASSIGN : VAR seen_id_in_assign EQUALS seen_equals EXPRESSION '''
    assign_to_var()

def p_seen_equals(p):
    ''' seen_equals  : empty '''
    OPERATOR_STACK.append('=')

def p_exp(p):
    ''' EXP :   TERM seen_term EXP_P
              | MINUS seen_unary_minus EXP pop_unary_minus
              | NOT seen_not EXP pop_not'''

def p_seen_term(p):
    ''' seen_term :  '''
    if len(OPERATOR_STACK) and  (OPERATOR_STACK[-1] == '+' or OPERATOR_STACK[-1] == '-'):
        generateExpressionQuad()

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
    generateExpressionQuad()

def p_seen_comp_op(p):
    ''' seen_comp_op : empty '''
    OPERATOR_STACK.append(p[-1])

def p_comp(p):
    ''' COMP : BIGGER
             | BIGGER_EQ
             | SMALLER
             | SMALLER_EQ
             | DOUBLE_EQUALS
             | DIFFERENT
             | AND
             | OR '''

    p[0] = p[1]

def p_factor(p):
    ''' FACTOR :  OPEN_PARENTHESIS seen_open_parenthesis EXPRESSION CLOSE_PARENTHESIS seen_close_parenthesis
                | NOT seen_not FACTOR pop_not
                | MINUS seen_unary_minus FACTOR pop_unary_minus
                | FUNC_CALL
                | VAR seen_id_as_factor
                | CNST '''

def p_pop_not(p):
    ''' pop_not : empty '''
    op = OPERATOR_STACK.pop()
    right_operand = OPERAND_STACK.pop()
    right_type = TYPE_STACK.pop()
    res_type = SemanticCube[op][right_type]
    if res_type != "err":
        res = FUNC_DIR.next_avail(res_type)
        push_to_quads(Quad(op, -1, FUNC_DIR.get_symbol_mem_index(right_operand), FUNC_DIR.get_symbol_mem_index(res)))
        OPERAND_STACK.append(res)
        TYPE_STACK.append(res_type)
    else:
        raise Exception("Type Mismatch: " + op + right_type)

def p_seen_not(p):
    ''' seen_not : empty '''
    OPERATOR_STACK.append(p[-1])

def p_pop_unary_minus(p):
    ''' pop_unary_minus : empty '''
    OPERATOR_STACK.pop() # Pop Fake Wall
    op = OPERATOR_STACK.pop()
    right_operand = OPERAND_STACK.pop()
    right_type = TYPE_STACK.pop()
    res_type = SemanticCube[op][right_type]
    if res_type != "err":
        res = FUNC_DIR.next_avail(res_type)
        push_to_quads(Quad(op, -1, FUNC_DIR.get_symbol_mem_index(right_operand), FUNC_DIR.get_symbol_mem_index(res)))
        OPERAND_STACK.append(res)
        TYPE_STACK.append(res_type)
    else:
        exception_txt = "Type Mismatch: " + op + right_type
        if right_type == "boolean":
            exception_txt += " (maybe use !boolean instead?)"
        raise Exception(exception_txt)



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

def p_seen_id_in_assign(p):
    ''' seen_id_in_assign :  empty '''
    parse_id(p[-1], 0)

def p_seen_id_as_factor(p):
    ''' seen_id_as_factor : empty '''
    parse_id(p[-1], 1)


def parse_id(id, mode):
    if "+" in id:
        # It is an array!
        array_id = id[:id.index("+")]
        dims = FUNC_DIR.get_symbol_dimensions(id[:id.index("+")])
        access_values = id[id.index("+") + 1:].split(",")[:-1]
        if len(access_values) != len(dims):
            # Accessing array incompletely (would need to return an array obj)
            raise Exception("Index Error: array " + array_id + " expects " + str(len(dims)) + " access indices, received " + str(len(access_values)))
        final_access_value = FUNC_DIR.next_avail("int")
        for i, d in enumerate(access_values):

            '''
            if int(d) >= dims[i]:
                # Index out of bounds!
                raise Exception("Index Error: index " + d + " is out of range for " + array_id)
            '''

            try:
                d = int(d) # might be an ID, might be a stright up int
            except:
                pass

            if i == len(access_values) - 1:
                push_to_quads(Quad("+", FUNC_DIR.get_symbol_mem_index(final_access_value),  FUNC_DIR.get_symbol_mem_index(d), FUNC_DIR.get_symbol_mem_index(final_access_value)))
            else:
                access_increment = FUNC_DIR.next_avail("int")
                push_to_quads(Quad("=", -1,  FUNC_DIR.get_symbol_mem_index(d), FUNC_DIR.get_symbol_mem_index(access_increment)))
                for j, size in enumerate(dims):
                    if i < j:
                        push_to_quads(Quad("*", FUNC_DIR.get_symbol_mem_index(access_increment),  FUNC_DIR.get_symbol_mem_index(int(size)), FUNC_DIR.get_symbol_mem_index(access_increment)))

                push_to_quads(Quad("+", FUNC_DIR.get_symbol_mem_index(final_access_value),  FUNC_DIR.get_symbol_mem_index(access_increment), FUNC_DIR.get_symbol_mem_index(final_access_value)))

        array_type = FUNC_DIR.symbol_type_lookup(array_id)
        ptr_to_array_value_at_index = FUNC_DIR.next_avail(array_type, is_ptr = True)
        push_to_quads(Quad("ACCESS", FUNC_DIR.get_symbol_mem_index(array_id),  FUNC_DIR.get_symbol_mem_index(final_access_value), FUNC_DIR.get_symbol_mem_index(ptr_to_array_value_at_index)))

        if not mode: # We are assigning to this array, need a pointer
            OPERAND_STACK.append(FUNC_DIR.symbol_lookup(ptr_to_array_value_at_index))
            TYPE_STACK.append(FUNC_DIR.symbol_type_lookup(ptr_to_array_value_at_index))

        else: # We are just using the value at this index, no need for a pointer; Can resolve into a tmp
            value_at_index = FUNC_DIR.next_avail(array_type)
            push_to_quads(Quad("=", 1,  FUNC_DIR.get_symbol_mem_index(ptr_to_array_value_at_index), FUNC_DIR.get_symbol_mem_index(value_at_index)))
            OPERAND_STACK.append(FUNC_DIR.symbol_lookup(value_at_index))
            TYPE_STACK.append(FUNC_DIR.symbol_type_lookup(value_at_index))
    else:
        OPERAND_STACK.append(FUNC_DIR.symbol_lookup(id))
        TYPE_STACK.append(FUNC_DIR.symbol_type_lookup(id))

def p_seen_cte_i(p):
    ''' seen_cte_i :  '''
    FUNC_DIR.declare_constant(p[-1], "int")
    OPERAND_STACK.append(p[-1])
    TYPE_STACK.append("int")

def p_seen_cte_f(p):
    ''' seen_cte_f :  '''
    FUNC_DIR.declare_constant(p[-1], "float")
    OPERAND_STACK.append(p[-1])
    TYPE_STACK.append("float")

def p_seen_cte_s(p):
    ''' seen_cte_s :  '''
    FUNC_DIR.declare_constant("'" + p[-1][1:-1] + "'", "string")
    OPERAND_STACK.append("'" + p[-1][1:-1] + "'")
    TYPE_STACK.append("string")

def p_cnst(p):
    ''' CNST : CTE_S seen_cte_s
             | CTE_F seen_cte_f
             | CTE_I seen_cte_i '''

    p[0] = p[1]


def p_var(p):
    ''' VAR :       ID
                |   ARRAY'''
    p[0] = p[1]

def p_array(p):
    ''' ARRAY : ID seen_array_id OPEN_BRACKET EXPRESSION seen_array_access CLOSE_BRACKET ARRAY_P '''
    p[0] = ""
    dims = ARRAY_DIMENSION_STACK.pop()
    for dim in dims:
            if dim == p[1]:
                p[0] += p[1] + "+"
            else:
                p[0] += str(dim) + ","

def p_array_p(p):
    ''' ARRAY_P :       OPEN_BRACKET EXPRESSION seen_array_access CLOSE_BRACKET ARRAY_P
                    |   empty '''

def p_seen_array_id(p):
    ''' seen_array_id : empty '''
    ARRAY_DIMENSION_STACK.append([p[-1]])

def p_seen_array_access(p):
    ''' seen_array_access : empty '''
    access = OPERAND_STACK.pop()
    access_type = TYPE_STACK.pop()
    if access_type not in ["int", "bool"]:
        raise Exception("TypeError: Cannot use " + access_type + " as access index for " + ARRAY_DIMENSION_STACK[-1][0])

    ARRAY_DIMENSION_STACK[-1].append(access)


def p_array_definition(p):
    ''' ARRAY_DEFINITION : ID seen_array_def_id OPEN_BRACKET CTE_I seen_cte_i seen_array_def_dim CLOSE_BRACKET ARRAY_DEFINITION_P'''
    p[0] = p[1]

def p_array_definition_p(p):
    ''' ARRAY_DEFINITION_P :       OPEN_BRACKET CTE_I seen_cte_i seen_array_def_dim CLOSE_BRACKET ARRAY_DEFINITION_P
                    |   empty'''


def p_seen_array_def_id(p):
    ''' seen_array_def_id : empty '''
    ARRAY_DIMENSION_STACK.append([p[-1]])

def p_seen_array_def_dim(p):
    ''' seen_array_def_dim : empty '''
    dim = p[-2]
    ARRAY_DIMENSION_STACK[-1].append(dim)

def p_term(p):
    ''' TERM : FACTOR seen_factor TERM_P  '''

def p_term_p(p):
    ''' TERM_P :    STAR seen_factor_op FACTOR seen_factor TERM_P
                 |  FWD_SLASH seen_factor_op FACTOR seen_factor TERM_P
                 |  empty '''

def p_seen_factor(p):
    ''' seen_factor :  '''
    if len(OPERATOR_STACK) and (OPERATOR_STACK[-1] == '*' or OPERATOR_STACK[-1] == '/'):
        generateExpressionQuad()

def p_seen_factor_op(p):
    ''' seen_factor_op :  '''
    OPERATOR_STACK.append(p[-1])

def p_func_call(p):
    ''' FUNC_CALL : ID seen_func_call_id OPEN_PARENTHESIS ARG_LIST CLOSE_PARENTHESIS '''
    FUNC_DIR.args_ok(p[1])

    push_to_quads(Quad("GOSUB", -1, -1, FUNC_DIR.get_start_addr(p[1])))

    FUNC_CALL_STACK.pop()
    if len(FUNC_CALL_STACK):
        FUNC_DIR.set_param_index(FUNC_CALL_STACK[-1][0], FUNC_CALL_STACK[-1][1])

    return_type = FUNC_DIR.func_type_lookup(p[1])


    temp = FUNC_DIR.next_avail(return_type)
    OPERAND_STACK.append(temp)
    TYPE_STACK.append(return_type)
    rtn_obj_name = FUNC_DIR.get_return_obj_name(p[1])
    if return_type != "void":
        push_to_quads(Quad("=", get_ptr_value(rtn_obj_name, temp), FUNC_DIR.get_symbol_mem_index(rtn_obj_name), FUNC_DIR.get_symbol_mem_index(temp)))

def p_seen_func_call_id(p):
    ''' seen_func_call_id : empty '''
    OPERATOR_STACK.append("|ARG_WALL|") # ARGUMENT 'FAKE WALL'
    func_type = FUNC_DIR.func_type_lookup(p[-1])
    size = FUNC_DIR.get_func_size(p[-1])
    push_to_quads(Quad("ERA", -1, -1, FUNC_DIR.get_start_addr(p[-1])))
    FUNC_DIR.set_param_index(p[-1], 0)
    FUNC_CALL_STACK.append([p[-1], 0])

def p_arg_list(p):
    ''' ARG_LIST : VAR seen_id_as_factor seen_arg ARG_LIST_P
                 | EXPRESSION seen_arg ARG_LIST_P
                 | FUNC_CALL seen_arg ARG_LIST_P
                 | empty '''

    OPERATOR_STACK.pop()  # POP 'ARGUMENT FAKE WALL'

def p_arg_list_p(p):
    ''' ARG_LIST_P : COMMA VAR seen_id_as_factor seen_arg ARG_LIST_P
                   | COMMA EXPRESSION seen_arg ARG_LIST_P
                   | COMMA FUNC_CALL seen_arg ARG_LIST_P
                   | empty '''

def p_seen_arg(p):
    ''' seen_arg : '''
    arg = OPERAND_STACK.pop()
    arg_type = TYPE_STACK.pop()
    k = FUNC_DIR.verify_arg_type(FUNC_CALL_STACK[-1][0], arg_type)
    push_to_quads(Quad("PARAM", -1, FUNC_DIR.get_symbol_mem_index(arg), FUNC_DIR.get_param_mem_index(FUNC_CALL_STACK[-1][0], k)))
    FUNC_CALL_STACK[-1][1] = k

def p_func_return(p):
    ''' FUNC_RETURN :   RETURN_KWD EXPRESSION SEMI_COLON
                      | RETURN_KWD FUNC_CALL SEMI_COLON '''

    rtn_type = TYPE_STACK.pop()
    rtn_id = OPERAND_STACK.pop()
    rtn_obj_name = FUNC_DIR.get_return_obj_name()

    push_to_quads(Quad("=", get_ptr_value(rtn_id, rtn_obj_name), FUNC_DIR.get_symbol_mem_index(rtn_id), FUNC_DIR.get_symbol_mem_index(rtn_obj_name)))
    push_to_quads(Quad("ENDFNC", -1, -1, -1))

    FUNC_DIR.return_type_check(rtn_type, QUAD_POINTER - 1)

def p_void_func_return(p):
    ''' FUNC_RETURN : RETURN_KWD SEMI_COLON '''
    FUNC_DIR.return_type_check("void", QUAD_POINTER)
    push_to_quads(Quad("ENDFNC", -1, -1, -1))

def p_read(p):
    ''' READ : READ_KWD OPEN_PARENTHESIS READABLE_LIST CLOSE_PARENTHESIS '''

def p_print(p):
    ''' PRINT : PRINT_KWD seen_print_kwd OPEN_PARENTHESIS PRINTABLE CLOSE_PARENTHESIS '''
    push_to_quads(Quad("PRNT", -1, -1, -1))

def p_seen_print_kwd(p):
    ''' seen_print_kwd : empty '''

def p_println(p):
    ''' PRINTLN : PRINTLN_KWD seen_println_kwd OPEN_PARENTHESIS PRINTABLE CLOSE_PARENTHESIS '''
    push_to_quads(Quad("PRNTLN", -1, -1, -1))

def p_seen_println_kwd(p):
    ''' seen_println_kwd : empty '''

def p_printable(p):
    ''' PRINTABLE : EXPRESSION seen_printable PRINTABLE_P '''

def p_printable_p(p):
    ''' PRINTABLE_P : COMMA EXPRESSION seen_printable PRINTABLE_P
                    | empty '''

def p_seen_printable(p):
    ''' seen_printable  : empty '''
    printable = OPERAND_STACK.pop()
    printable_type = TYPE_STACK.pop()
    push_to_quads(Quad("PRNTBFFR", -1, -1, FUNC_DIR.get_symbol_mem_index(printable)))

def p_func_decision(p):
    ''' FUNC_DECISION : IF_KWD OPEN_PARENTHESIS EXPRESSION CLOSE_PARENTHESIS seen_if_kwd OPEN_CURLY FUNC_STATEMENT_STAR CLOSE_CURLY FUNC_DECISION_P '''
    seen_decision()

def p_func_decision_p(p):
    ''' FUNC_DECISION_P : ELSE_KWD seen_else_kwd OPEN_CURLY FUNC_STATEMENT_STAR CLOSE_CURLY
                            | empty '''

def p_decision(p):
    ''' DECISION : IF_KWD OPEN_PARENTHESIS EXPRESSION CLOSE_PARENTHESIS seen_if_kwd OPEN_CURLY STATEMENT_STAR CLOSE_CURLY DECISION_P '''
    seen_decision()

def p_decision_p(p):
    ''' DECISION_P : ELSE_KWD seen_else_kwd OPEN_CURLY STATEMENT_STAR CLOSE_CURLY
                   | empty '''

def seen_decision():
    dir = JUMP_STACK.pop()
    fill_quad(dir, QUAD_POINTER)

def p_seen_if_kwd(p):
    ''' seen_if_kwd : empty '''
    decision_statement()

def p_seen_else_kwd(p):
    ''' seen_else_kwd : empty '''
    push_to_quads(Quad("GOTO", -1, -1,"PND"))
    dir = JUMP_STACK.pop()
    JUMP_STACK.append(QUAD_POINTER - 1)
    fill_quad(dir, QUAD_POINTER)

def p_func_repetition(p):
    ''' FUNC_REPETITION :     FUNC_CONDITIONAL_REP
                            | FUNC_UNCONDITIONAL_REP '''

def p_func_conditional_rep(p):
    ''' FUNC_CONDITIONAL_REP : WHILE_KWD seen_while_kwd OPEN_PARENTHESIS EXPRESSION CLOSE_PARENTHESIS seen_while_exp OPEN_CURLY FUNC_STATEMENT_STAR CLOSE_CURLY '''
    seen_conditional_rep()

def p_func_unconditional_rep(p):
    ''' FUNC_UNCONDITIONAL_REP : FOR_KWD OPEN_PARENTHESIS VAR seen_for_kwd EQUALS EXPRESSION seen_for_start_exp SEMI_COLON EXPRESSION seen_for_end_exp SEMI_COLON FOR_INCR_STATEMENT seen_for_incr_exp CLOSE_PARENTHESIS OPEN_CURLY FUNC_STATEMENT_STAR CLOSE_CURLY '''
    seen_unconditional_rep()

def p_repetition(p):
    ''' REPETITION : CONDITIONAL_REP
                   | UNCONDITIONAL_REP '''

def p_conditional_rep(p):
    ''' CONDITIONAL_REP : WHILE_KWD seen_while_kwd OPEN_PARENTHESIS EXPRESSION CLOSE_PARENTHESIS seen_while_exp OPEN_CURLY STATEMENT_STAR CLOSE_CURLY '''
    seen_conditional_rep()

def seen_conditional_rep():
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
    ''' UNCONDITIONAL_REP : FOR_KWD OPEN_PARENTHESIS VAR seen_for_kwd EQUALS EXPRESSION seen_for_start_exp SEMI_COLON EXPRESSION seen_for_end_exp SEMI_COLON FOR_INCR_STATEMENT seen_for_incr_exp CLOSE_PARENTHESIS OPEN_CURLY STATEMENT_STAR CLOSE_CURLY '''
    seen_unconditional_rep()

def seen_unconditional_rep():
    swap_end_dir = JUMP_STACK.pop()
    swap_start_dir = JUMP_STACK.pop()
    end_dir = JUMP_STACK.pop()
    loop_dir = JUMP_STACK.pop()

    incr_res = OPERAND_STACK.pop()

    for i in range(swap_start_dir, swap_end_dir):
        swap_quads(swap_start_dir, QUAD_POINTER)

    push_to_quads(Quad("GOTO", -1, -1, loop_dir))
    fill_quad(end_dir, QUAD_POINTER)

def p_seen_for_kwd(p):
    ''' seen_for_kwd : empty '''
    OPERAND_STACK.append(FUNC_DIR.symbol_lookup(p[-1]))
    TYPE_STACK.append(FUNC_DIR.symbol_type_lookup(p[-1]))
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

    if expr_end_type != "boolean":
        raise Exception("Type mismatch: 'for' end expression type is not boolean")
    else:
        res = OPERAND_STACK.pop()
        JUMP_STACK.append(QUAD_POINTER)
        push_to_quads(Quad("GOTOF", -1, FUNC_DIR.get_symbol_mem_index(res), "PND"))
        JUMP_STACK.append(QUAD_POINTER)

def p_type(p):
    ''' TYPE :      TYPE_I
                |   TYPE_F
                |   TYPE_S
                |   TYPE_B
                |   TYPE_V '''

    p[0] = p[1]

def p_empty(p):
     'empty :'
     pass

# Error rule for syntax errors
def p_error(p):
    print("Syntax error in input!")
    print(p)
    exit()

def get_ptr_value(left, right):
    ptr_value = -1

    if FUNC_DIR.is_sym_ptr(left):
        ptr_value = 1

    if FUNC_DIR.is_sym_ptr(right):
        if ptr_value > 0:
            ptr_value = 3
        else:
            ptr_value = 2

    return ptr_value


def generateExpressionQuad():
    right_operand = OPERAND_STACK.pop()
    right_type = TYPE_STACK.pop()
    left_operand = OPERAND_STACK.pop()
    left_type = TYPE_STACK.pop()
    operator = OPERATOR_STACK.pop()
    result_type = SemanticCube[left_type][operator][right_type]
    if result_type != "err":
        result = FUNC_DIR.next_avail(result_type)
        push_to_quads(Quad(operator, FUNC_DIR.get_symbol_mem_index(left_operand), FUNC_DIR.get_symbol_mem_index(right_operand), FUNC_DIR.get_symbol_mem_index(result)))
        OPERAND_STACK.append(result)
        TYPE_STACK.append(result_type)
    else:
        raise Exception("Type Mismatch: " + left_type + " " + operator + " " + right_type)

def assign_to_var(push_back_operand = False, push_back_type = False):
    op = OPERATOR_STACK.pop()
    right_operand  = OPERAND_STACK.pop()
    res =  OPERAND_STACK.pop()
    right_type  = TYPE_STACK.pop()
    res_type = TYPE_STACK.pop()
    if SemanticCube[res_type][op][right_type] == "err":
        raise Exception("Type Mismatch: " + res_type + " " + op + " " + right_type)
    else:
        push_to_quads(Quad(op, get_ptr_value(right_operand, res), FUNC_DIR.get_symbol_mem_index(right_operand), FUNC_DIR.get_symbol_mem_index(res)))
        if push_back_operand:
            OPERAND_STACK.append(res)
        if push_back_type:
            TYPE_STACK.append(res_type)

def decision_statement():
    expr_type = TYPE_STACK.pop()
    if SemanticCube[expr_type]["=="]["boolean"]:
        res = OPERAND_STACK.pop()
        push_to_quads(Quad("GOTOF", -1, FUNC_DIR.get_symbol_mem_index(res), "PND"))
        JUMP_STACK.append(QUAD_POINTER - 1)
    else:
        raise Exception("Type Mismatch: non-boolean (" + expr_type + ") expression in decision statement")

def fill_vm_file(file_path, marker_str, start_str, end_str, info):
    line_indices = []
    with open(file_path, "r") as f:
        contents = f.readlines()

        for i, c in enumerate(contents):
            if c == marker_str:
                line_indices.append(i)

    # IF THERE ARE MORE/LESS LINES THAN LAST TIME...
    quad_size_diff = len(info) - (line_indices[1] - line_indices[0]) + 2

    for i in range(quad_size_diff):
        contents.insert(line_indices[1], "\n") # More info! Add more lines

    for i in range(-quad_size_diff):
        contents.pop(line_indices[0] + len(info)) # Less info! Get rid of useless lines

    insert_start_index =  line_indices[0] + 2
    insert_end_index = insert_start_index + len(info)

    contents[line_indices[0] + 1] = start_str

    for i in range(insert_start_index, insert_end_index):
        contents[i] = info[i - insert_start_index]

    contents[insert_end_index] = end_str + marker_str

    with open(VM_FILE_PATH, "w") as f:
        contents = "".join(contents)
        f.write(contents)


## For VM compilation
VM_FILE_PATH = "VM/main.cpp"

VM_QUAD_MARKER_STR = "// QUADS //\n"
VM_QUAD_START_STR = "const vector<vector<int>> QUADS = {\n"
VM_QUAD_END_STR = "\t" * 10 + "};\n"

VM_MEMORY_MARKER_STR = "// MEMORY //\n"
VM_MEMORY_START_STR = "const map<int, vector<vector<int>>> MEMORY_MAP_SIGN = {\n"
VM_MEMORY_END_STR = "\t" * 10 + "};\n"

VM_CONSTANTS_MARKER_STR = "// CONSTANTS //\n"
VM_CONSTANTS_START_STR = "const map<int, string> CONSTANTS = {\n"
VM_CONSTANTS_END_STR = "\t" * 10 + "};\n"

def main(argv):

    # Build the parser
    parser = yacc.yacc()

    output_file_path = None

    while len(argv):
        if len(argv) == 1:
            input_file_path = argv.pop()
            break

        arg = argv.pop()
        param = argv.pop()

        if param == "-i":
            input_file_path = arg
        elif param == "-o":
            output_file_path = arg + ".exe"
        else:
            raise Exception("Param Error! Use -i for input file path (assumed as first parameter) and -o for output file path.")


    s = ""
    with open(input_file_path) as f:
        lines = f.readlines()
        for l in lines:
            s += l[:-1]
        print(">> Parsing " + input_file_path + "...")
        parser.parse(s)
        '''
        for f in FUNC_DIR.FUNCS.values():
            try:
                print(f.SYMBOLS)
            except:
                for k in f.keys():
                    print(f[k][0], k, f[k][1].SYMBOLS, f[k][2].SYMBOLS)

        print(">> STACKS:", OPERAND_STACK, TYPE_STACK, OPERATOR_STACK, JUMP_STACK, FUNC_CALL_STACK)
        '''

    vm_quads = []
    for i in range(len(QUADS)):
        vm_quads.append("\t" * 10 + QUADS[i].get_cpp_string() + "\n")

    fill_vm_file(VM_FILE_PATH, VM_QUAD_MARKER_STR, VM_QUAD_START_STR, VM_QUAD_END_STR, vm_quads)

    vm_memory = []
    for context in FUNC_DIR.FUNCS.keys():
        if context == FUNC_DIR.program_name:
            global_mem_sign = "\t" * 10 +  "{" + str(FUNC_DIR.get_main_start_addr()) + ", {{" + ",".join([str(x) for x in list(FUNC_DIR.FUNCS[context].var_memory_signature.values())]) + "}"
            global_temp_sign = "{" + ",".join([str(x) for x in list(FUNC_DIR.FUNCS[context].temp_memory_signature.values())]) + "}"
            global_const_sign = "{" + ",".join([str(x) for x in list(FUNC_DIR.FUNCS[context].const_memory_signature.values())]) + "}}},\n"
            vm_memory.insert(0, global_mem_sign + ", " + global_temp_sign + ", " + global_const_sign)
        else:
            for func in FUNC_DIR.FUNCS[context].keys():
                mem_sign = "\t" * 10 +  "{" + str(FUNC_DIR.get_start_addr(func)) + ", {{" + ",".join([str(x) for x in list(FUNC_DIR.FUNCS[context][func][2].var_memory_signature.values())]) + "}"
                temp_sign = "{" + ",".join([str(x) for x in list(FUNC_DIR.FUNCS[context][func][2].temp_memory_signature.values())]) + "}}},\n"
                vm_memory.append(mem_sign + ", " + temp_sign)

    mem_constraints_str = "const int MAX_CONSTANTS = " + str(MAX_CONSTANTS) + ", MAX_SYMBOLS = " + str(MAX_SYMBOLS) + ", MAX_TMP_SYMBOLS = " + str(MAX_TMP_SYMBOLS) + ", VAR_TYPES = " + str(FunctionDirectory.VAR_TYPES) + ", MEMORY_STACK_LIMIT = " + str(MEMORY_STACK_LIMIT) + ";\n\n"

    fill_vm_file(VM_FILE_PATH, VM_MEMORY_MARKER_STR, mem_constraints_str + VM_MEMORY_START_STR, VM_MEMORY_END_STR, vm_memory)

    vm_constants = []
    for id in FUNC_DIR.FUNCS[FUNC_DIR.program_name].SYMBOLS.keys():
        var = FUNC_DIR.FUNCS[FUNC_DIR.program_name].SYMBOLS[id]
        if var[3]:
            if isinstance(id, str): # String Constant
                cnst_string = "\t" * 10 + "{" + str(var[1]) + ', "' + id[1:-1] + '"},\n'
            else:
                cnst_string = "\t" * 10 + "{" + str(var[1]) + ', "' + str(id) + '"},\n'
            vm_constants.append(cnst_string)

    fill_vm_file(VM_FILE_PATH, VM_CONSTANTS_MARKER_STR, VM_CONSTANTS_START_STR, VM_CONSTANTS_END_STR, vm_constants)

    '''
    for i, q in enumerate(QUADS):
        print(i, ":", q.get_string())
    '''

    if output_file_path == None:
        output_file_path = FUNC_DIR.program_name + ".exe"

    print(">> Compiling " + input_file_path + " into " + output_file_path)
    if not os.system('g++ ' + VM_FILE_PATH + ' -o ' + output_file_path):
        print(">> Compilation Successfull!")


if __name__=='__main__':
    main(sys.argv[1:])
