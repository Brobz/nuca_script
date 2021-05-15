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


]

reserved = {

    'program' : 'PROGRAM_KWD',
    'ATTR' : 'ATTR_KWD',
    'VARS' : 'VARS_KWD',
    'main' : 'MAIN_KWD',
    'class' : 'CLASS_KWD',
    'derives' : 'DERIVES_KWD',
    'write' : 'WRITE_KWD',
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

// TODO : Implement VM code for expressions and linear statements (ASSIGN, READ, WRITE)

        NEXT STEP : Get a simple main that sums two global vars going in the VM

            1. Design variable (and temps) indexing structure                               (compiler)
            2. Replace var (and temp) names with var (and temp) indices in quads            (compiler)
            3. Design constant Constant's MemoryMap structure, assign indices and values    (compiler)
            4. Replace constants with their indices from the constants table in quads       (compiler)
            5. Write constant memorymap to VM file                                          (compiler)
            6. Design preliminary op-to-code translation                                    (compiler)
            7. Interpret QUADS in VM file                                                   (VM)

// TODO : Implement list syntax and quad generation! arr[3] : int; arr = [1, 2, 3]; arr[0] = 1;

-----------------------------------------------------------------------------------------------

// TODO : Refactor files and methods

// TODO : Add +=,-=, *= and /= operators as possible ASSIGN statements in grammar and SemanticCube

// TODO : Fix shift/reduce && reduce/reduce conflict warnings

// TODO : Make list of includes/dependencies and add them to the project

// TODO: Update Formal grammar and flow diagrams.

'''

# Now to parsing!

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
    print(">> Syntax Approved!")

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
    if not FUNC_DIR.valid_return_check(QUAD_POINTER - 1):
        FUNC_DIR.return_type_check("void", QUAD_POINTER)
        push_to_quads(Quad("ENDFNC", "_", "_", "_"))

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
    ''' FUNC_STATEMENT_STAR :      ASSIGN SEMI_COLON FUNC_STATEMENT_STAR
                                |  FUNC_CALL SEMI_COLON FUNC_STATEMENT_STAR
                                |  READ SEMI_COLON FUNC_STATEMENT_STAR
                                |  WRITE SEMI_COLON FUNC_STATEMENT_STAR
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
                  | WRITE SEMI_COLON
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
    res_type = SemanticCube[op][right_type]
    res = FUNC_DIR.next_avail(res_type)
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
    TYPE_STACK.append("string")

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

    return_type = FUNC_DIR.func_type_lookup(p[1])


    temp = FUNC_DIR.next_avail(return_type)
    OPERAND_STACK.append(temp)
    TYPE_STACK.append(return_type)
    if return_type != "void":
        push_to_quads(Quad("=", "_", FUNC_DIR.get_return_obj_name(p[1]), temp))

def p_seen_func_call_id(p):
    ''' seen_func_call_id : empty '''
    OPERATOR_STACK.append("|ARG_WALL|") # ARGUMENT 'FAKE WALL'
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

    OPERATOR_STACK.pop()  # POP 'ARGUMENT FAKE WALL'

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
                      | RETURN_KWD FUNC_CALL SEMI_COLON '''

    rtn_type = TYPE_STACK.pop()
    rtn_id = OPERAND_STACK.pop()

    push_to_quads(Quad("=", "_", rtn_id, FUNC_DIR.get_return_obj_name()))
    push_to_quads(Quad("ENDFNC", "_", "_", "_"))

    FUNC_DIR.return_type_check(rtn_type, QUAD_POINTER - 1)

def p_void_func_return(p):
    ''' FUNC_RETURN : RETURN_KWD SEMI_COLON '''
    FUNC_DIR.return_type_check("void", QUAD_POINTER)
    push_to_quads(Quad("ENDFNC", "_", "_", "_"))

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
    push_to_quads(Quad("GOTO", "_", "_","PND"))
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
    ''' FUNC_UNCONDITIONAL_REP : FOR_KWD OPEN_PARENTHESIS ID seen_for_kwd EQUALS EXPRESSION seen_for_start_exp SEMI_COLON EXPRESSION seen_for_end_exp SEMI_COLON FOR_INCR_STATEMENT seen_for_incr_exp CLOSE_PARENTHESIS OPEN_CURLY FUNC_STATEMENT_STAR CLOSE_CURLY '''
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
    seen_unconditional_rep()

def seen_unconditional_rep():
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

def generateExpressionQuad():
    right_operand = OPERAND_STACK.pop()
    right_type = TYPE_STACK.pop()
    left_operand = OPERAND_STACK.pop()
    left_type = TYPE_STACK.pop()
    operator = OPERATOR_STACK.pop()
    result_type = SemanticCube[left_type][operator][right_type]
    if result_type != "err":
        result = FUNC_DIR.next_avail(result_type)
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
    if SemanticCube[expr_type]["=="]["boolean"]:
        res = OPERAND_STACK.pop()
        push_to_quads(Quad("GTF", "_", res, "PND"))
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
VM_MEMORY_MARKER_STR = "// MEMORY //\n"
VM_QUAD_START_STR = "vector<vector<string>> QUADS = {\n"
VM_MEMORY_START_STR = "map<string, vector<vector<int>>> MEMORY_MAP_SIGN = {\n"
VM_QUAD_END_STR = "\t" * 10 + "};\n"
VM_MEMORY_END_STR = "\t" * 10 + "};\n"


def main(argv):

    # Build the parser
    parser = yacc.yacc()

    output_file_path = "out.exe"

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
        for f in FUNC_DIR.FUNCS.values():
            try:
                print(f.SYMBOLS)
            except:
                for k in f.keys():
                    print(f[k][0], k, f[k][1].SYMBOLS, f[k][2].SYMBOLS, f[k][2].var_memory_signature, f[k][2].temp_memory_signature)

        print(">> STACKS:", OPERAND_STACK, TYPE_STACK, OPERATOR_STACK, JUMP_STACK, FUNC_CALL_STACK)

    vm_quads = []
    for i in range(len(QUADS)):
        vm_quads.append("\t" * 10 + QUADS[i].get_cpp_string() + "\n")

    fill_vm_file(VM_FILE_PATH, VM_QUAD_MARKER_STR, VM_QUAD_START_STR, VM_QUAD_END_STR, vm_quads)

    vm_memory = []
    for context in FUNC_DIR.FUNCS.keys():
        if context == FUNC_DIR.program_name:
            global_mem_sign = "\t" * 10 +  "{" +  '"' + FUNC_DIR.program_name + '"' + ", {{" + ",".join([str(x) for x in list(FUNC_DIR.FUNCS[context].var_memory_signature.values())]) + "}"
            global_temp_sign = "{" + ",".join([str(x) for x in list(FUNC_DIR.FUNCS[context].temp_memory_signature.values())]) + "}}},\n"
            vm_memory.insert(0, global_mem_sign + ", " + global_temp_sign)
        else:
            for func in FUNC_DIR.FUNCS[context].keys():
                mem_sign = "\t" * 10 +  "{" +  '"' + func + '"' + ", {{" + ",".join([str(x) for x in list(FUNC_DIR.FUNCS[context][func][2].var_memory_signature.values())]) + "}"
                temp_sign = "{" + ",".join([str(x) for x in list(FUNC_DIR.FUNCS[context][func][2].temp_memory_signature.values())]) + "}}},\n"
                vm_memory.append(mem_sign + ", " + temp_sign)

    fill_vm_file(VM_FILE_PATH, VM_MEMORY_MARKER_STR, VM_MEMORY_START_STR, VM_MEMORY_END_STR, vm_memory)


    print(">> Compiling " + input_file_path + " into " + output_file_path)
    if not os.system('g++ ' + VM_FILE_PATH + ' -o ' + output_file_path):
        print(">> Compilation Successfull!")


if __name__=='__main__':
    main(sys.argv[1:])
