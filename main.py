# Guilherme Bittencourt de Borba
# A01194571
# Diseno de Compiladores
# ------------------------------------------------------------

import ply.lex as lex
import ply.yacc as yacc

from SymbolTable import *
from FunctionDirectory import *
from SemanticCube import *
from Quad import *
from Avail import  *

# List of token names.   This is always required
tokens = [
'SEMI_COLON',
'COLON',
'COMMA',
'OPEN_CURLY',
'CLOSE_CURLY',
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
'SMALLER',
'DIFFERENT',

'CTE_I',
'CTE_F',
'CTE_S',
'ID',
'TYPE',

]

reserved = {

    'program' : 'PROGRAM_KWD',
    'ATTR' : 'ATTR_KWD',
    'VARS' : 'VARS_KWD',
    'main' : 'MAIN_KWD',
    'Class' : 'CLASS_KWD',
    'derives' : 'DERIVES_KWD',
    'write' : 'WRITE_KWD',
    'read' : 'READ_KWD',
    'return' : 'RETURN_KWD',
    'while' : 'WHILE_KWD',
    'for' : 'FOR_KWD',
    'if' : 'IF_KWD',
    'else' : 'ELSE_KWD',


}


tokens += list(reserved.values())

# A string containing ignored characters (spaces and tabs)
t_SEMI_COLON                =   r';'
t_COLON                     =   r':'
t_COMMA                     =   r','
t_OPEN_CURLY                =   r'\{'
t_CLOSE_CURLY               =   r'\}'
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
t_BIGGER                    =   r'\>'
t_SMALLER                   =   r'\<'
t_DIFFERENT                 =   r'\<\>'



t_ignore  = ' \t'

def t_TYPE(t):
    r'(int)|(float)|(str)|(void)|(boolean)'
    t.type = reserved.get(t.value, 'TYPE')    # Check for reserved words
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

// TODO: Implement RETURN stmt functionality

// TODO: Design initial virtual memory management concept for virtual machine

// TODO: Fix shift/reduce && reduce/reduce conflict warnings

// TODO: Update Formal grammar and flow diagrams.

For loop -> for (ID = EXPR;                     EXPR;                               STATEMENT) { STATEMENT* }
                # Starting assignment,          # Boolean (end) expr,               # Increment expression,
                to existing ID                  will loop until its false           will be executed at the end of each iteration, before the looping GOTO
'''

# Now to parsing!

AVAIL = Avail()
FUNC_DIR = FunctionDirectory()
OPERATOR_STACK = []
OPERAND_STACK = []
TYPE_STACK = []
JUMP_STACK = []
FUNC_CALL_STACK = []
QUAD_POINTER = 1
QUADS = [Quad("GOTO", "_", "_", "PND")]

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
    else:
        temp = QUADS[q2]
        QUADS[q2] = QUADS[q1]
        QUADS[q1] = temp

# First lets define our grammar rules...

def p_program(p):
    ''' PROGRAM : PROGRAM_KWD ID seen_program_id SEMI_COLON CLASS_STAR GLOBAL_VAR FUNC_DEF_STAR MAIN_KWD OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_CURLY seen_main_kwd STATEMENT_STAR CLOSE_CURLY '''
    push_to_quads(Quad("END", "_", "_", "_"))
    print("Syntax Approved!")


def p_seen_program_id(p):
    ''' seen_program_id : empty '''
    FUNC_DIR.declare_function(p[-1], "void", "PROGRAM")


def p_seen_main_kwd(p):
    ''' seen_main_kwd : empty '''
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
    ''' VAR_LIST : ID_LIST COLON TYPE SEMI_COLON '''
    p[0] = p[1] + ":" + p[3]

def p_id_list(p):
    ''' ID_LIST : ID ID_LIST_P '''
    p[0] = p[1]
    if p[2] != None:
        p[0] += p[2]

def p_id_list_p(p):
    ''' ID_LIST_P : COMMA ID ID_LIST_P
                  | empty '''
    if p[1] == ',':
        p[0] = ',' + p[2]
        if p[3] != None:
            p[0] += p[3]

def p_readable_list(p):
    ''' READABLE_LIST : ID seen_readable READABLE_LIST_P '''


def p_readable_list_p(p):
    ''' READABLE_LIST_P : COMMA ID seen_readable READABLE_LIST_P
                  | empty '''

def p_seen_readable(p):
    ''' seen_readable  : empty '''
    push_to_quads(Quad("RD", "_", "_", FUNC_DIR.symbol_lookup(p[-1])))



def p_global_var(p):
    ''' GLOBAL_VAR : VAR_LIST_STAR '''
    for list in p[1].split("||"):
        type = list.split(":")[1]
        for id in list.split(":")[0].split(','):
            FUNC_DIR.declare_symbol(id, type)

def p_func_def_star(p):
    ''' FUNC_DEF_STAR : FUNC_DEF FUNC_DEF_STAR
                      | empty '''

def p_func_def(p):
    ''' FUNC_DEF : TYPE ID seen_func_id OPEN_PARENTHESIS FUNC_PARAM CLOSE_PARENTHESIS seen_func_params VARS seen_func_vars OPEN_CURLY FUNC_STATEMENT_STAR CLOSE_CURLY '''
    FUNC_DIR.current_scope = None
    push_to_quads(Quad("ENDFNC", "_", "_", "_"))

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
                FUNC_DIR.declare_symbol(id, type)

    FUNC_DIR.set_start_addr(QUAD_POINTER)

def p_func_param(p):
    ''' FUNC_PARAM : VAR FUNC_PARAM_P
                   | empty '''

    if len(p) > 2:
        p[0] = p[1]
        if p[2] != None:
            p[0] += p[2]

def p_func_param_p(p):
    ''' FUNC_PARAM_P : COMMA VAR FUNC_PARAM_P
                     | empty '''

    if len(p) > 2:
        p[0] = "," + p[2]
        if p[3] != None:
            p[0] += p[3]

def p_var(p):
    ''' VAR : ID COLON TYPE '''
    p[0] = p[1] + ":" + p[3]

def p_vars(p):
    ''' VARS : VARS_KWD OPEN_CURLY VAR_LIST_STAR CLOSE_CURLY '''
    p[0] = p[3]


def p_func_statement_star(p):
    ''' FUNC_STATEMENT_STAR :       STATEMENT FUNC_STATEMENT_STAR
                                |   FUNC_RETURN FUNC_STATEMENT_STAR
                                |   empty '''


def p_statement_star(p):
    ''' STATEMENT_STAR :  STATEMENT STATEMENT_STAR
                       | empty '''

def p_statement(p):
    ''' STATEMENT : ASSIGN SEMI_COLON
                  | FUNC_CALL SEMI_COLON
                  | READ SEMI_COLON
                  | WRITE SEMI_COLON
                  | DECISION
                  | REPETITION '''

def p_for_incr_statement(p):
    ''' FOR_INCR_STATEMENT :    ASSIGN
                              | FUNC_CALL
                              | READ
                              | WRITE '''

def p_assign(p):
    ''' ASSIGN : ID seen_id EQUALS seen_equals EXPRESSION '''
    assign_to_var()

def p_seen_equals(p):
    ''' seen_equals  : empty '''
    OPERATOR_STACK.append('=')

def p_exp(p):
    ''' EXP :   TERM seen_term EXP_P
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
             | SMALLER
             | DOUBLE_EQUALS
             | DIFFERENT
             | AND
             | OR '''

    p[0] = p[1]

def p_factor(p):
    ''' FACTOR :  OPEN_PARENTHESIS seen_open_parenthesis EXPRESSION CLOSE_PARENTHESIS seen_close_parenthesis
                | NOT seen_not FACTOR pop_not
                | FUNC_CALL
                | ID seen_id
                | CNST '''

def p_pop_not(p):
    ''' pop_not : empty '''
    op = OPERATOR_STACK.pop()
    right_operand = OPERAND_STACK.pop()
    right_type = TYPE_STACK.pop()
    res = AVAIL.next()
    res_type = SemanticCube[op][right_type]
    if res_type != "err":
        push_to_quads(Quad(op, "_", right_operand, res))
        OPERAND_STACK.append(res)
        TYPE_STACK.append(res_type)
    else:
        raise Exception("Type Mismatch: " + op + right_operand)

def p_seen_not(p):
    ''' seen_not : empty '''
    OPERATOR_STACK.append(p[-1])

def p_seen_open_parenthesis(p):
    ''' seen_open_parenthesis : empty '''
    OPERATOR_STACK.append(p[-1])

def p_seen_close_parenthesis(p):
    ''' seen_close_parenthesis : empty '''
    OPERATOR_STACK.pop()

def p_seen_id(p):
    ''' seen_id :  '''
    OPERAND_STACK.append(FUNC_DIR.symbol_lookup(p[-1]))
    TYPE_STACK.append(FUNC_DIR.symbol_type_lookup(p[-1]))

def p_seen_cte_i(p):
    ''' seen_cte_i :  '''
    OPERAND_STACK.append(str(p[-1]))
    TYPE_STACK.append("int")

def p_seen_cte_f(p):
    ''' seen_cte_f :  '''
    OPERAND_STACK.append(str(p[-1]))
    TYPE_STACK.append("float")


def p_seen_cte_s(p):
    ''' seen_cte_s :  '''
    OPERAND_STACK.append(str(p[-1][1:-1]))
    TYPE_STACK.append("str")



def p_cnst(p):
    ''' CNST : CTE_S seen_cte_s
             | CTE_F seen_cte_f
             | CTE_I seen_cte_i '''

    p[0] = p[1]

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

    push_to_quads(Quad("GOSUB", p[1], "_", "_"))

    FUNC_CALL_STACK.pop()
    if len(FUNC_CALL_STACK):
        FUNC_DIR.set_param_index(FUNC_CALL_STACK[len(FUNC_CALL_STACK) - 1][0], FUNC_CALL_STACK[len(FUNC_CALL_STACK) - 1][1])


    OPERAND_STACK.append("TEMP_RETURN_OBJ")
    TYPE_STACK.append(FUNC_DIR.func_type_lookup(p[1]))



def p_seen_func_call_id(p):
    ''' seen_func_call_id : empty '''
    func_type = FUNC_DIR.func_type_lookup(p[-1])
    size = FUNC_DIR.get_func_size(p[-1])
    push_to_quads(Quad("ERA", "_", "_", p[-1]))
    FUNC_DIR.set_param_index(p[-1], 0)
    FUNC_CALL_STACK.append([p[-1], 0])

def p_arg_list(p):
    ''' ARG_LIST : ID seen_arg ARG_LIST_P
                 | EXPRESSION seen_arg ARG_LIST_P
                 | FUNC_CALL seen_arg ARG_LIST_P
                 | empty '''

def p_arg_list_p(p):
    ''' ARG_LIST_P : COMMA ID seen_arg ARG_LIST_P
                   | COMMA EXPRESSION seen_arg ARG_LIST_P
                   | COMMA FUNC_CALL seen_arg ARG_LIST_P
                   | empty '''

def p_seen_arg(p):
    ''' seen_arg : '''
    arg = OPERAND_STACK.pop()
    arg_type = TYPE_STACK.pop()
    k = FUNC_DIR.verify_arg_type(FUNC_CALL_STACK[len(FUNC_CALL_STACK) - 1][0], arg_type)
    push_to_quads(Quad("PARAM", arg, "_", k))
    FUNC_CALL_STACK[len(FUNC_CALL_STACK) - 1][1] = k

def p_func_return(p):
    ''' FUNC_RETURN :   RETURN_KWD EXPRESSION SEMI_COLON
                      | RETURN_KWD FUNC_CALL SEMI_COLON'''

def p_read(p):
    ''' READ : READ_KWD OPEN_PARENTHESIS READABLE_LIST CLOSE_PARENTHESIS '''


def p_write(p):
    ''' WRITE : WRITE_KWD OPEN_PARENTHESIS PRINTABLE CLOSE_PARENTHESIS '''


def p_printable(p):
    ''' PRINTABLE : EXPRESSION seen_printable PRINTABLE_P '''


def p_printable_p(p):
    ''' PRINTABLE_P : COMMA EXPRESSION seen_printable PRINTABLE_P
                    | empty '''

def p_seen_printable(p):
    ''' seen_printable  : empty '''
    printable_type = TYPE_STACK.pop()
    push_to_quads(Quad("WR", "_", "_",  OPERAND_STACK.pop()))

def p_decision(p):
    ''' DECISION : IF_KWD OPEN_PARENTHESIS EXPRESSION CLOSE_PARENTHESIS seen_if_kwd OPEN_CURLY STATEMENT_STAR CLOSE_CURLY DECISION_P '''
    dir = JUMP_STACK.pop()
    fill_quad(dir, QUAD_POINTER)

def p_decision_p(p):
    ''' DECISION_P : ELSE_KWD seen_else_kwd OPEN_CURLY STATEMENT_STAR CLOSE_CURLY
                   | empty '''

def p_seen_if_kwd(p):
    ''' seen_if_kwd : empty '''
    decision_statement()

def p_seen_else_kwd(p):
    ''' seen_else_kwd : empty '''
    push_to_quads(Quad("GOTO", "_", "_","PND"))
    dir = JUMP_STACK.pop()
    JUMP_STACK.append(QUAD_POINTER - 1)
    fill_quad(dir, QUAD_POINTER)

def p_repetition(p):
    ''' REPETITION : CONDITIONAL_REP
                   | UNCONDITIONAL_REP '''

def p_conditional_rep(p):
    ''' CONDITIONAL_REP : WHILE_KWD seen_while_kwd OPEN_PARENTHESIS EXPRESSION CLOSE_PARENTHESIS seen_while_exp OPEN_CURLY STATEMENT_STAR CLOSE_CURLY '''
    end_dir = JUMP_STACK.pop()
    return_dir = JUMP_STACK.pop()
    push_to_quads(Quad("GOTO", "_", "_", return_dir))
    fill_quad(end_dir, QUAD_POINTER)

def p_seen_while_kwd(p):
    ''' seen_while_kwd : empty '''
    JUMP_STACK.append(QUAD_POINTER)


def p_seen_while_exp(p):
    ''' seen_while_exp : empty '''
    decision_statement()


def p_unconditional_rep(p):
    ''' UNCONDITIONAL_REP : FOR_KWD OPEN_PARENTHESIS ID seen_for_kwd EQUALS EXPRESSION seen_for_start_exp SEMI_COLON EXPRESSION seen_for_end_exp SEMI_COLON FOR_INCR_STATEMENT seen_for_incr_exp CLOSE_PARENTHESIS OPEN_CURLY STATEMENT_STAR CLOSE_CURLY '''

    swap_end_dir = JUMP_STACK.pop()
    swap_start_dir = JUMP_STACK.pop()
    end_dir = JUMP_STACK.pop()
    loop_dir = JUMP_STACK.pop()

    incr_res = OPERAND_STACK.pop()

    for i in range(swap_start_dir, swap_end_dir):
        swap_quads(swap_start_dir, QUAD_POINTER)

    push_to_quads(Quad("GOTO", "_", "_", loop_dir))
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
        push_to_quads(Quad("GTF", "_", res, "PND"))
        JUMP_STACK.append(QUAD_POINTER)

def p_empty(p):
     'empty :'
     pass

# Error rule for syntax errors
def p_error(p):
    print("Syntax error in input!")
    print(p)


def generateExpressionQuad():
    right_operand = OPERAND_STACK.pop()
    right_type = TYPE_STACK.pop()
    left_operand = OPERAND_STACK.pop()
    left_type = TYPE_STACK.pop()
    operator = OPERATOR_STACK.pop()
    result_type = SemanticCube[left_type][operator][right_type]
    if result_type != "err":
        result = AVAIL.next()
        push_to_quads(Quad(operator, left_operand, right_operand, result))
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
    if right_type != res_type:
        raise Exception("Type Mismatch: " + right_type + " " + op + " " + res_type)
    else:
        push_to_quads(Quad(op, "_", right_operand, res))
        if push_back_operand:
            OPERAND_STACK.append(res)
        if push_back_type:
            TYPE_STACK.append(res_type)

def decision_statement():
    expr_type = TYPE_STACK.pop()
    if expr_type == "boolean":
        res = OPERAND_STACK.pop()
        push_to_quads(Quad("GTF", "_", res, "PND"))
        JUMP_STACK.append(QUAD_POINTER - 1)
    else:

        raise Exception("Type Mismatch: non-boolean (" + expr_type + ") expression in decision statement")


# Build the parser
parser = yacc.yacc()

print(">> Input file for NucaNuca parsing: ")
input_file = input("-- ")

s = ""
with open(input_file) as f:
    lines = f.readlines()
    for l in lines:
        s += l[:-1]
    result = parser.parse(s)
    for f in FUNC_DIR.FUNCS.values():
        try:
            print(f.SYMBOLS)
        except:
            for k in f.keys():
                print(f[k][0], k, f[k][1].SYMBOLS, f[k][2].SYMBOLS)

    print("STACKS:", OPERAND_STACK, TYPE_STACK, OPERATOR_STACK, JUMP_STACK, FUNC_CALL_STACK)
    print("GENERATED QUADS:")
    for i, q in enumerate(QUADS):
        print(str(i), q.get_string())
