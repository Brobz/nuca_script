import Libraries.ply.lex as lex

from .ExceptionHandler import ExceptionHandler
from .SymbolTable import SymbolTable
from .FunctionDirectory import FunctionDirectory
from .Globals import Globals


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

# Lexer States (for catching multi-line comments)
states = (
    ("COMMENT", "exclusive"),
)

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

def t_start_comment(t):
    r"\/\*\/"
    t.lexer.push_state("COMMENT")

def t_COMMENT_end(t):
    r"\/\*\/"
    t.lexer.pop_state()

# Define a rule so we can track line numbers
def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

# Define a rule so we can track line numbers (in COMMENT state)
def t_COMMENT_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

# To ignore whitespaces and tabs
t_ignore  = ' \t'
t_COMMENT_ignore = ' \t' 

# Error handling rule
def t_error(t):
    print(">> Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)

# Error handling rule (in COMMENT state)
def t_COMMENT_error(t):
    t.lexer.skip(1)

# Build the lexer
lexer = lex.lex()

# Now to parsing!

## First, lets initialize our ExceptionHandler object, which will handle excepiton raising with useful error meessages
EXCEPTION_HANDLER = ExceptionHandler(lexer)

## Then, set the reference to this exception handler object on the rest of the classes
FunctionDirectory.EXCEPTION_HANDLER = EXCEPTION_HANDLER
SymbolTable.EXCEPTION_HANDLER = EXCEPTION_HANDLER

## Here we define the memory constraints of our parser
MAX_CONSTANTS = 10000                                        # (per type)
MAX_SYMBOLS = MAX_TMP_SYMBOLS = MAX_OBJ_SYMBOLS = 30000      # (per type)
MEMORY_STACK_LIMIT = 100000                                  # (to prevent recursion)

## Next, we initialize the FunctionDirectory object which will handle all of the parsing processes
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

## Global Values Initialization
GLOBALS = Globals()

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

# NucaScript Constants bootstrapped!
# Final step is to load grammar rules into memory and prepare for compilation
from Compiler.Grammar import *