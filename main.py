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
    'until' : 'UNTIL_KWD',
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

def t_COMMENT(t):
    r'\#.*'
    pass
    # No return value. Token discarded

def t_TYPE(t):
    # Currently defined as an ID; Look into how to implement actual types
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
// TODO: Update Formal grammar and flow diagrams.

For loop -> for (ID = EXPR;                     EXPR;                               STATEMENT) { STATEMENT* }
                # Starting assignment,          # Boolean (end) expr,               # Increment expression,
                to existing ID                  will loop until its false           will be executed at the end of each iteration, before the looping GOTO
'''

# Now to parsing!

FUNC_DIR = FunctionDirectory()
SYMBOL_TABLE = SymbolTable()
QUAD_POINTER = 0
QUADS = []

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
    ''' PROGRAM : PROGRAM_KWD  ID  SEMI_COLON CLASS_STAR GLOBAL_VAR FUNC_DEF_STAR MAIN_KWD OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_CURLY STATEMENT_STAR CLOSE_CURLY '''

    print(">> APROPRIADO!")

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
    push_to_quads(Quad("RD", "_", "_", SYMBOL_TABLE.symbol_lookup(p[-1])))



def p_global_var(p):
    ''' GLOBAL_VAR : VAR_LIST_STAR '''
    for list in p[1].split("||"):
        type = list.split(":")[1]
        for id in list.split(":")[0].split(','):
            SYMBOL_TABLE.declare_symbol(id, type)

def p_func_def_star(p):
    ''' FUNC_DEF_STAR : FUNC_DEF FUNC_DEF_STAR
                      | empty '''

def p_func_def(p):
    ''' FUNC_DEF : TYPE ID OPEN_PARENTHESIS FUNC_PARAM CLOSE_PARENTHESIS VARS OPEN_CURLY STATEMENT_STAR CLOSE_CURLY '''
    FUNC_DIR.declare_function(p[2], p[1])
    SYMBOL_TABLE.add_scope("METHOD_" + p[2])

    if p[4] != None:
        for list in p[4].split(","):
            id, type = list.split(":")
            SYMBOL_TABLE.declare_symbol(id, type, "METHOD_" + p[2])

    if p[6] != None:
        for list in p[6].split("||"):
            type = list.split(":")[1]
            for id in list.split(":")[0].split(','):
                SYMBOL_TABLE.declare_symbol(id, type, "METHOD_" + p[2])

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

def p_statement_star(p):
    ''' STATEMENT_STAR :  STATEMENT STATEMENT_STAR
                       | empty '''

def p_statement(p):
    ''' STATEMENT : ASSIGN
                  | FUNC_RETURN
                  | READ
                  | WRITE
                  | DECISION
                  | REPETITION '''

def p_assign(p):
    ''' ASSIGN : ID seen_id EQUALS seen_equals EXPRESSION SEMI_COLON '''
    assign_to_var()

def p_seen_equals(p):
    ''' seen_equals  : empty '''
    SYMBOL_TABLE.OperatorStack.append('=')

def p_exp(p):
    ''' EXP :   TERM seen_term EXP_P
              | NOT seen_not EXP pop_not'''


def p_seen_term(p):
    ''' seen_term :  '''
    if len(SYMBOL_TABLE.OperatorStack) and  (SYMBOL_TABLE.OperatorStack[-1] == '+' or SYMBOL_TABLE.OperatorStack[-1] == '-'):
        generateExpressionQuad()


def p_exp_p(p):
    ''' EXP_P : PLUS seen_term_op TERM seen_term EXP_P
            | MINUS seen_term_op TERM seen_term EXP_P
            | empty '''

def p_seen_term_op(p):
    ''' seen_term_op :  '''
    SYMBOL_TABLE.OperatorStack.append(p[-1])

def p_expression(p):
    ''' EXPRESSION :   EXP
                     | EXP COMP seen_comp_op EXP seen_comp '''

def p_seen_comp(p):
    ''' seen_comp : empty '''
    generateExpressionQuad()


def p_seen_comp_op(p):
    ''' seen_comp_op : empty '''
    SYMBOL_TABLE.OperatorStack.append(p[-1])

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
                | CNST  '''

def p_pop_not(p):
    ''' pop_not : empty '''
    op = SYMBOL_TABLE.OperatorStack.pop()
    right_operand = SYMBOL_TABLE.OperandStack.pop()
    right_type = SYMBOL_TABLE.TypeStack.pop()
    res = SYMBOL_TABLE.Avail.next()
    res_type = SemanticCube[op][right_type]
    if res_type != "err":
        push_to_quads(Quad(op, "_", right_operand, res))
        SYMBOL_TABLE.OperandStack.append(res)
        SYMBOL_TABLE.TypeStack.append(res_type)
    else:
        raise Exception("Type Mismatch: " + op + right_operand)

def p_seen_not(p):
    ''' seen_not : empty '''
    SYMBOL_TABLE.OperatorStack.append(p[-1])

def p_seen_open_parenthesis(p):
    ''' seen_open_parenthesis : empty '''
    SYMBOL_TABLE.OperatorStack.append(p[-1])

def p_seen_close_parenthesis(p):
    ''' seen_close_parenthesis : empty '''
    SYMBOL_TABLE.OperatorStack.pop()

def p_seen_id(p):
    ''' seen_id :  '''
    SYMBOL_TABLE.OperandStack.append(SYMBOL_TABLE.symbol_lookup(p[-1]))
    SYMBOL_TABLE.TypeStack.append(SYMBOL_TABLE.type_lookup(p[-1]))

def p_seen_cte_i(p):
    ''' seen_cte_i :  '''
    SYMBOL_TABLE.OperandStack.append(str(p[-1]))
    SYMBOL_TABLE.TypeStack.append("int")

def p_seen_cte_f(p):
    ''' seen_cte_f :  '''
    SYMBOL_TABLE.OperandStack.append(str(p[-1]))
    SYMBOL_TABLE.TypeStack.append("float")


def p_seen_cte_s(p):
    ''' seen_cte_s :  '''
    SYMBOL_TABLE.OperandStack.append(str(p[-1][1:-1]))
    SYMBOL_TABLE.TypeStack.append("str")



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
    if len(SYMBOL_TABLE.OperatorStack) and (SYMBOL_TABLE.OperatorStack[-1] == '*' or SYMBOL_TABLE.OperatorStack[-1] == '/'):
        generateExpressionQuad()

def p_seen_factor_op(p):
    ''' seen_factor_op :  '''
    SYMBOL_TABLE.OperatorStack.append(p[-1])


def p_func_call(p):
    ''' FUNC_CALL : ID OPEN_PARENTHESIS ARG_LIST CLOSE_PARENTHESIS '''

def p_arg_list(p):
    ''' ARG_LIST : ID_LIST ARG_LIST_P
                 | EXPRESSION ARG_LIST_P '''

def p_arg_list_p(p):
    ''' ARG_LIST_P : COMMA ID_LIST ARG_LIST_P
                   | COMMA EXPRESSION ARG_LIST_P
                   | empty '''

def p_func_return(p):
    ''' FUNC_RETURN : RETURN_KWD EXPRESSION SEMI_COLON '''

def p_read(p):
    ''' READ : READ_KWD OPEN_PARENTHESIS READABLE_LIST CLOSE_PARENTHESIS SEMI_COLON '''


def p_write(p):
    ''' WRITE : WRITE_KWD OPEN_PARENTHESIS PRINTABLE CLOSE_PARENTHESIS SEMI_COLON '''


def p_printable(p):
    ''' PRINTABLE : EXPRESSION seen_printable PRINTABLE_P '''


def p_printable_p(p):
    ''' PRINTABLE_P : COMMA EXPRESSION seen_printable PRINTABLE_P
                    | empty '''

def p_seen_printable(p):
    ''' seen_printable  : empty '''
    printable_type = SYMBOL_TABLE.TypeStack.pop()
    push_to_quads(Quad("WR", "_", "_",  SYMBOL_TABLE.OperandStack.pop()))

def p_decision(p):
    ''' DECISION : IF_KWD OPEN_PARENTHESIS EXPRESSION CLOSE_PARENTHESIS seen_if_kwd OPEN_CURLY STATEMENT_STAR CLOSE_CURLY DECISION_P '''
    dir = SYMBOL_TABLE.JumpStack.pop()
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
    dir = SYMBOL_TABLE.JumpStack.pop()
    SYMBOL_TABLE.JumpStack.append(QUAD_POINTER - 1)
    fill_quad(dir, QUAD_POINTER)

def p_repetition(p):
    ''' REPETITION : CONDITIONAL_REP
                   | UNCONDITIONAL_REP '''

def p_conditional_rep(p):
    ''' CONDITIONAL_REP : WHILE_KWD seen_while_kwd OPEN_PARENTHESIS EXPRESSION CLOSE_PARENTHESIS seen_while_exp OPEN_CURLY STATEMENT_STAR CLOSE_CURLY '''
    end_dir = SYMBOL_TABLE.JumpStack.pop()
    return_dir = SYMBOL_TABLE.JumpStack.pop()
    push_to_quads(Quad("GOTO", "_", "_", return_dir))
    fill_quad(return_dir, QUAD_POINTER)

def p_seen_while_kwd(p):
    ''' seen_while_kwd : empty '''
    SYMBOL_TABLE.JumpStack.append(QUAD_POINTER)


def p_seen_while_exp(p):
    ''' seen_while_exp : empty '''
    decision_statement()


def p_unconditional_rep(p):
    ''' UNCONDITIONAL_REP : FOR_KWD OPEN_PARENTHESIS ID seen_for_kwd EQUALS EXPRESSION seen_for_start_exp SEMI_COLON EXPRESSION seen_for_end_exp SEMI_COLON STATEMENT seen_for_incr_exp CLOSE_PARENTHESIS OPEN_CURLY STATEMENT_STAR CLOSE_CURLY '''

    swap_end_dir = SYMBOL_TABLE.JumpStack.pop()
    swap_start_dir = SYMBOL_TABLE.JumpStack.pop()
    end_dir = SYMBOL_TABLE.JumpStack.pop()
    loop_dir = SYMBOL_TABLE.JumpStack.pop()

    incr_res = SYMBOL_TABLE.OperandStack.pop()

    for i in range(swap_start_dir, swap_end_dir):
        swap_quads(swap_start_dir, QUAD_POINTER)

    push_to_quads(Quad("GOTO", "_", "_", loop_dir))
    fill_quad(end_dir, QUAD_POINTER)

def p_seen_for_kwd(p):
    ''' seen_for_kwd : empty '''
    SYMBOL_TABLE.OperandStack.append(SYMBOL_TABLE.symbol_lookup(p[-1]))
    SYMBOL_TABLE.TypeStack.append(SYMBOL_TABLE.type_lookup(p[-1]))
    SYMBOL_TABLE.OperatorStack.append("=")

def p_seen_for_incr_exp(p):
    ''' seen_for_incr_exp : empty'''
    SYMBOL_TABLE.JumpStack.append(QUAD_POINTER)

def p_seen_for_start_exp(p):
    ''' seen_for_start_exp : empty '''
    assign_to_var(True)
    SYMBOL_TABLE.JumpStack.append(QUAD_POINTER)

def p_seen_for_end_exp(p):
    ''' seen_for_end_exp : empty '''

    expr_end_type = SYMBOL_TABLE.TypeStack.pop()

    if expr_end_type != "boolean":
        raise Exception("Type mismatch: 'for' end expression type is not boolean")
    else:
        res = SYMBOL_TABLE.OperandStack.pop()
        SYMBOL_TABLE.JumpStack.append(QUAD_POINTER)
        push_to_quads(Quad("GTF", "_", res, "PND"))
        SYMBOL_TABLE.JumpStack.append(QUAD_POINTER)

def p_empty(p):
     'empty :'
     pass

# Error rule for syntax errors
def p_error(p):
    print("Syntax error in input!")
    print(p)


def generateExpressionQuad():
    right_operand = SYMBOL_TABLE.OperandStack.pop()
    right_type = SYMBOL_TABLE.TypeStack.pop()
    left_operand = SYMBOL_TABLE.OperandStack.pop()
    left_type = SYMBOL_TABLE.TypeStack.pop()
    operator = SYMBOL_TABLE.OperatorStack.pop()
    result_type = SemanticCube[left_type][operator][right_type]
    if result_type != "err":
        result = SYMBOL_TABLE.Avail.next()
        push_to_quads(Quad(operator, left_operand, right_operand, result))
        SYMBOL_TABLE.OperandStack.append(result)
        SYMBOL_TABLE.TypeStack.append(result_type)
    else:
        raise Exception("Type Mismatch: " + left_type + " " + operator + " " + right_type)


def assign_to_var(push_back = False):
    op = SYMBOL_TABLE.OperatorStack.pop()
    right_operand  = SYMBOL_TABLE.OperandStack.pop()
    res =  SYMBOL_TABLE.OperandStack.pop()
    right_type  = SYMBOL_TABLE.TypeStack.pop()
    res_type = SYMBOL_TABLE.TypeStack.pop()
    if right_type != res_type:
        raise Exception("Type Mismatch: " + right_type + " " + op + " " + res_type)
    else:
        push_to_quads(Quad(op, "_", right_operand, res))
        if push_back:
            SYMBOL_TABLE.TypeStack.append(res_type)
            SYMBOL_TABLE.OperandStack.append(res)


def decision_statement():
    expr_type = SYMBOL_TABLE.TypeStack.pop()
    if expr_type == "boolean":
        res = SYMBOL_TABLE.OperandStack.pop()
        push_to_quads(Quad("GTF", "_", res, "PND"))
        SYMBOL_TABLE.JumpStack.append(QUAD_POINTER - 1)
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
    print(SYMBOL_TABLE.SYMBOLS)
    print(FUNC_DIR.SYMBOLS)
    print("GENERATED QUADS:")
    for i, q in enumerate(QUADS):
        print(str(i), q.get_string())
