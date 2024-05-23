from .SymbolTable import SymbolTable
from .Quad import Quad
from .SemanticCube import SemanticCube
from .Boostrapper import ARRAY_DIMENSION_STACK, CLASS_INSTANCE_STACK, CONDITIONAL_DEPTH_STACK, DOT_OP_STACK, EXCEPTION_HANDLER, FUNC_CALL_STACK, FUNC_DIR, GLOBALS, JUMP_STACK, OBJECT_ACCESS_STACK, OPERAND_STACK, OPERATOR_STACK, SCOPES_STACK, TYPE_STACK
from . import Utils

## PLY Rules ##
# the next set of functions define the grammar rules of NucaScript, as well as the actions they should execute during parsing #

def p_program(p):
    ''' PROGRAM : PROGRAM_KWD ID seen_program_id SEMI_COLON DEF_SECTION STRUCTURE_DEFINITION MAIN_KWD OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_CURLY seen_main_kwd STATEMENT_STAR CLOSE_CURLY '''
    Utils.push_to_quads(Quad("END", -1, -1, -1))
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
    ### TODO: Figure out a way to NOT replace names that are inside of a string (within quotations)
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
    FUNC_DIR.set_main_start_addr(GLOBALS.QUAD_POINTER)
    Utils.fill_quad(0, GLOBALS.QUAD_POINTER)
    for sym_id in FUNC_DIR.FUNCS[FUNC_DIR.program_name].SYMBOLS:
        symbol = FUNC_DIR.FUNCS[FUNC_DIR.program_name].SYMBOLS[sym_id]
        if symbol.is_array and symbol.object_type != None: # is_arr and class_type != None
            Utils.push_to_quads(Quad("USNG_AS", FUNC_DIR.get_array_element_size(sym_id, SCOPES_STACK[-1]), FUNC_DIR.get_class_idx(symbol.object_type), FUNC_DIR.get_symbol_mem_index(sym_id, SCOPES_STACK[-1], False)))

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
        Utils.parse_vars_declaration(p[-1])

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
            EXCEPTION_HANDLER.raiseException("Type Error: Cannot read into symbol " + id + " of type " + id_type)
        else:
            EXCEPTION_HANDLER.raiseException("Type Error: Cannot read into " + id_type)

    is_pointer = int(FUNC_DIR.is_sym_pointer(id, id_scope))
    if not is_pointer:
        is_pointer = -1

    parent_obj_dir = -1
    if id_attr and len(CLASS_INSTANCE_STACK):
        parent_obj_id = CLASS_INSTANCE_STACK.pop()
        if parent_obj_id != "this_kwd":
            parent_obj_dir = FUNC_DIR.get_symbol_mem_index(parent_obj_id, SCOPES_STACK[-1])


    Utils.push_to_quads(Quad("READ", parent_obj_dir, is_pointer, FUNC_DIR.get_symbol_mem_index(FUNC_DIR.symbol_lookup(id, id_scope, id_attr), id_scope, id_attr)))

def p_global_var(p):
    ''' GLOBAL_VAR : VAR_LIST_STAR '''
    if p[1] != None:
        Utils.parse_vars_declaration(p[1])

def p_func_def_star(p):
    ''' FUNC_DEF_STAR : FUNC_DEF FUNC_DEF_STAR
                      | empty '''

def p_func_def(p):
    ''' FUNC_DEF : TYPE ID seen_func_id OPEN_PARENTHESIS FUNC_PARAM CLOSE_PARENTHESIS seen_func_params VARS seen_func_vars OPEN_CURLY STATEMENT_STAR CLOSE_CURLY '''
    if not FUNC_DIR.valid_return_check(GLOBALS.QUAD_POINTER - 1, SCOPES_STACK[-1]): # This means the last statement of this functions block was not a return statement!
        FUNC_DIR.return_type_check("void", GLOBALS.QUAD_POINTER, SCOPES_STACK[-1], len(CONDITIONAL_DEPTH_STACK))  # In that case, assume a void return (return;) and check if iit is valid
        Utils.push_to_quads(Quad("ENDFNC", -1, -1, int(SCOPES_STACK[-1] != "GLOBAL"))) # All good!

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
        Utils.parse_vars_declaration(p[-1])

    FUNC_DIR.set_start_addr(GLOBALS.QUAD_POINTER, SCOPES_STACK[-1])
    if SCOPES_STACK[-1] != "GLOBAL":
        for sym_id in FUNC_DIR.FUNCS[SCOPES_STACK[-1]]["FUNCS"][FUNC_DIR.current_scope][2].SYMBOLS:
            symbol = FUNC_DIR.FUNCS[SCOPES_STACK[-1]]["FUNCS"][FUNC_DIR.current_scope][2].SYMBOLS[sym_id]
            if symbol.is_array and symbol.object_type != None: # is_arr and class_type != None
                Utils.push_to_quads(Quad("USNG_AS", FUNC_DIR.get_array_element_size(sym_id, SCOPES_STACK[-1]), FUNC_DIR.get_class_idx(symbol.object_type), FUNC_DIR.get_symbol_mem_index(sym_id, SCOPES_STACK[-1], False)))
            elif symbol.object_type != None:
                Utils.push_to_quads(Quad("OBJ_INST", -1, FUNC_DIR.get_class_idx(symbol.object_type), FUNC_DIR.get_symbol_mem_index(sym_id, SCOPES_STACK[-1], False)))


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

    Utils.push_to_quads(Quad("F_OPEN", parent_obj_dir, FUNC_DIR.get_symbol_mem_index(file_path[0], file_path[1], file_path[2]), FUNC_DIR.get_symbol_mem_index(separator[0], separator[1], separator[2]), FUNC_DIR.get_symbol_mem_index(buffer[0], buffer[1], buffer[2]), buffer_dimension))

def p_seen_open_buffer(p):
    ''' seen_open_buffer : empty '''
    buffer_scope =  SCOPES_STACK[-1]
    buffer_attr = False
    buffer = OPERAND_STACK.pop()
    buffer_type = TYPE_STACK.pop()

    if type(buffer) == list:
        buffer, buffer_scope, buffer_attr = buffer

    if not FUNC_DIR.is_sym_arr(buffer, buffer_scope, buffer_attr):
        EXCEPTION_HANDLER.raiseException("Type Error: cannot open file into a non-array variable")

    if buffer_type != "string":
        EXCEPTION_HANDLER.raiseException("Type Error: cannot open file into a non-string array")

    buffer_dimension = FUNC_DIR.get_symbol_dimensions(buffer, buffer_scope, buffer_attr)

    if len(buffer_dimension) > 1:
        EXCEPTION_HANDLER.raiseException("Type Error: Cannot open file into non-linear array")

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

    Utils.push_to_quads(Quad("F_WRITE", parent_obj_dir, FUNC_DIR.get_symbol_mem_index(file_path[0], file_path[1], file_path[2]), FUNC_DIR.get_symbol_mem_index(separator[0], separator[1], separator[2]), FUNC_DIR.get_symbol_mem_index(buffer[0], buffer[1], buffer[2]), buffer_dimension))

def p_seen_write_buffer(p):
    ''' seen_write_buffer : empty '''
    buffer_scope =  SCOPES_STACK[-1]
    buffer_attr = False
    buffer = OPERAND_STACK.pop()
    buffer_type = TYPE_STACK.pop()

    if type(buffer) == list:
        buffer, buffer_scope, buffer_attr = buffer

    if not FUNC_DIR.is_sym_arr(buffer, buffer_scope, buffer_attr):
        EXCEPTION_HANDLER.raiseException("Type Error: cannot write into file from a non-array variable")

    if buffer_type == "object":
        EXCEPTION_HANDLER.raiseException("Type Error: cannot write into file from an object type array")

    buffer_dimension = FUNC_DIR.get_symbol_dimensions(buffer, buffer_scope, buffer_attr)

    if len(buffer_dimension) > 1:
        EXCEPTION_HANDLER.raiseException("Type Error: cannot write into file from a non-linear array")

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
        EXCEPTION_HANDLER.raiseException("Type Error: file path argument of file I/O must be a string")

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
        EXCEPTION_HANDLER.raiseException("Type Error: separator argument of file I/O methods must be a string")

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

    Utils.assign_to_var()

def p_seen_equals(p):
    ''' seen_equals  : empty '''
    DOT_OP_STACK.clear()
    OPERATOR_STACK.append('=')

def p_seen_plus_equals(p):
    ''' seen_plus_equals  : empty '''
    DOT_OP_STACK.clear()
    Utils.parse_compound_asignment('+')

def p_seen_minus_equals(p):
    ''' seen_minus_equals  : empty '''
    DOT_OP_STACK.clear()
    Utils.parse_compound_asignment('-')

def p_seen_times_equals(p):
    ''' seen_times_equals  : empty '''
    DOT_OP_STACK.clear()
    Utils.parse_compound_asignment('*')

def p_seen_over_equals(p):
    ''' seen_over_equals  : empty '''
    DOT_OP_STACK.clear()
    Utils.parse_compound_asignment('/')

def p_seen_plus_plus(p):
    ''' seen_plus_plus  : empty '''
    DOT_OP_STACK.clear()
    Utils.parse_compound_asignment('++')

def p_seen_minus_minus(p):
    ''' seen_minus_minus  : empty '''
    DOT_OP_STACK.clear()
    Utils.parse_compound_asignment('--')

def p_exp(p):
    ''' EXP :   TERM seen_term EXP_P
              | MINUS seen_unary_minus EXP pop_unary_minus '''

def p_seen_term(p):
    ''' seen_term :  '''
    if len(OPERATOR_STACK) and  (OPERATOR_STACK[-1] == '+' or OPERATOR_STACK[-1] == '-'):
        Utils.generate_expression_quad()

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
    Utils.generate_expression_quad()

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

    Utils.push_to_quads(Quad("RANDINT", FUNC_DIR.get_symbol_mem_index(lower_arg[0], lower_arg[1], lower_arg[2]),  FUNC_DIR.get_symbol_mem_index(upper_arg[0], upper_arg[1], upper_arg[2]), FUNC_DIR.get_symbol_mem_index(int_temp, SCOPES_STACK[-1], False)))

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

    Utils.push_to_quads(Quad("STRLEN", -1, FUNC_DIR.get_symbol_mem_index(strlen_arg, strlen_arg_scope, strlen_arg_attr), FUNC_DIR.get_symbol_mem_index(int_temp, SCOPES_STACK[-1], False)))

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

    Utils.push_to_quads(Quad("SUBSTR", FUNC_DIR.get_symbol_mem_index(substr_arg, substr_arg_scope, substr_arg_attr), FUNC_DIR.get_symbol_mem_index(substr_idx[0], substr_idx[1], substr_idx[2]), FUNC_DIR.get_symbol_mem_index(substr_size[0], substr_size[1], substr_size[2]), FUNC_DIR.get_symbol_mem_index(new_str_temp, SCOPES_STACK[-1], False)))

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

    Utils.push_to_quads(Quad("STOX", -1, FUNC_DIR.get_symbol_mem_index(stox_arg, stox_arg_scope, stox_arg_attr), FUNC_DIR.get_symbol_mem_index(new_type_temp, SCOPES_STACK[-1], False)))

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
        Utils.push_to_quads(Quad(op, -1, FUNC_DIR.get_symbol_mem_index(right_operand, right_operand_scope, right_operand_attr), FUNC_DIR.get_symbol_mem_index(res, SCOPES_STACK[-1])))
        OPERAND_STACK.append(res)
        TYPE_STACK.append(res_type)
    else:
        EXCEPTION_HANDLER.raiseException("Type Mismatch: " + op + right_type)

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
        Utils.push_to_quads(Quad(op, -1, FUNC_DIR.get_symbol_mem_index(right_operand, right_operand_scope, right_operand_attr), FUNC_DIR.get_symbol_mem_index(res, SCOPES_STACK[-1])))
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
    Utils.parse_var(p[-1], 0)

def p_seen_var_as_factor(p):
    ''' seen_var_as_factor : empty '''
    Utils.parse_var(p[-1], 1)

def p_seen_var_in_io(p):
    ''' seen_var_in_io : empty '''
    Utils.parse_var(p[-1], 0, 1)

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
        EXCEPTION_HANDLER.raiseException("Syntax Error: this operator used outside of Class scope")

    if len(OBJECT_ACCESS_STACK) and OBJECT_ACCESS_STACK[-1] != "|ARG_WALL|":
        EXCEPTION_HANDLER.raiseException("Attribute Error: symbol " + p[-2] + " has no attribute 'this'")

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
                EXCEPTION_HANDLER.raiseException("Syntax Error: cannot use . operator on non-object type " + p[1])

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
        EXCEPTION_HANDLER.raiseException("Type Error: symbol " + obj_id + " has no object type in " + SCOPES_STACK[-1] + " scope and cannot be accessed with . operator (maybe missing initialization with 'new' keyword ?)")
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
        EXCEPTION_HANDLER.raiseException("Name Error: Cannot access non-array symbol " + id + " with [] operator")

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
        EXCEPTION_HANDLER.raiseException("Type Error: Cannot use " + access_type + " as access index for array '" + ARRAY_DIMENSION_STACK[-1][0] + "'")

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
        EXCEPTION_HANDLER.raiseException("Value Error: array dimension must be a non-zero positive integer")
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
        Utils.generate_expression_quad()

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
        Utils.push_to_quads(Quad("GOSUB", -1, -1, FUNC_DIR.get_start_addr(p[1], scope_in_use)))

    else:

        parent_object = OBJECT_ACCESS_STACK.pop()

        parent_obj_is_ptr = -1
        if type(parent_object) == list: # The caller of this method is inside an object array!
            parent_object = OPERAND_STACK.pop()[0] # In this case, there is an operand at the top of the operand stacks which is the pointer to this object
            parent_obj_is_ptr = 1 # Set is_ptr to True

        if parent_object == "this_kwd":
            Utils.push_to_quads(Quad("OBJ_GOSUB", parent_obj_is_ptr, -1, FUNC_DIR.get_start_addr(p[1], scope_in_use)))

        else:
            Utils.push_to_quads(Quad("OBJ_GOSUB", parent_obj_is_ptr, FUNC_DIR.get_symbol_mem_index(parent_object, SCOPES_STACK[-1]), FUNC_DIR.get_start_addr(p[1], scope_in_use)))

    FUNC_CALL_STACK.pop()
    if len(FUNC_CALL_STACK):
        FUNC_DIR.set_param_index(FUNC_CALL_STACK[-1][0], FUNC_CALL_STACK[-1][1], scope_in_use)

    return_type = FUNC_DIR.func_type_lookup(p[1], scope_in_use)

    temp = FUNC_DIR.next_avail(return_type, SCOPES_STACK[-1])
    OPERAND_STACK.append(temp)
    TYPE_STACK.append(return_type)

    if return_type != "void": # No need to set the return value if its a void method
        rtn_obj_name = FUNC_DIR.get_return_obj_name(p[1], scope_in_use)
        Utils.push_to_quads(Quad("=", Utils.get_ptr_value(None, [temp, SCOPES_STACK[-1]]), FUNC_DIR.get_symbol_mem_index(rtn_obj_name, "GLOBAL"), FUNC_DIR.get_symbol_mem_index(temp, SCOPES_STACK[-1])))


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

    Utils.push_to_quads(Quad("ERA", -1, -1, FUNC_DIR.get_start_addr(p[-1], DOT_OP_STACK[-2])))

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

    Utils.push_to_quads(Quad("PARAM", -1, FUNC_DIR.get_symbol_mem_index(arg, arg_scope, is_attr), FUNC_DIR.get_param_mem_index(FUNC_CALL_STACK[-1][0], k, scope_in_use)))
    FUNC_CALL_STACK[-1][1] = k

def p_func_return(p):
    ''' FUNC_RETURN :   RETURN_KWD EXPRESSION SEMI_COLON
                      | RETURN_KWD FUNC_CALL SEMI_COLON '''

    if FUNC_DIR.current_scope == None:
        # Return statement outside of function
        EXCEPTION_HANDLER.raiseException('>> Context Error: non-void return statement outside of function or method (maybe use "return;"?)')

    rtn_type = TYPE_STACK.pop()
    rtn_id = OPERAND_STACK.pop()

    FUNC_DIR.return_type_check(rtn_type, GLOBALS.QUAD_POINTER + 1, SCOPES_STACK[-1], len(CONDITIONAL_DEPTH_STACK))

    if rtn_type != "void": # No need to set values in case of a void return
        retn_scope = SCOPES_STACK[-1]
        is_attr = False
        if type(rtn_id) == list:
            rtn_id, retn_scope, is_attr = rtn_id

        rtn_obj_name = FUNC_DIR.get_return_obj_name(scope = SCOPES_STACK[-1])

        Utils.push_to_quads(Quad("=", Utils.get_ptr_value([rtn_id, retn_scope], None), FUNC_DIR.get_symbol_mem_index(rtn_id, retn_scope, is_attr), FUNC_DIR.get_symbol_mem_index(rtn_obj_name, "GLOBAL")))

    Utils.push_to_quads(Quad("ENDFNC", -1, -1, int(SCOPES_STACK[-1] != "GLOBAL")))

def p_void_func_return(p):
    ''' FUNC_RETURN : RETURN_KWD SEMI_COLON '''
    if FUNC_DIR.current_scope == None:
        # Return statement outside of function (inside main), but it returns no value... may as well end the program here!
        Utils.push_to_quads(Quad("END", -1, -1, -1))
    else:
        # Void return in a regular function.. need to check if its type mathes!
        FUNC_DIR.return_type_check("void", GLOBALS.QUAD_POINTER, SCOPES_STACK[-1], len(CONDITIONAL_DEPTH_STACK))
        Utils.push_to_quads(Quad("ENDFNC", -1, -1, int(SCOPES_STACK[-1] != "GLOBAL")))

def p_read(p):
    ''' READ : READ_KWD OPEN_PARENTHESIS READABLE_LIST CLOSE_PARENTHESIS '''
    DOT_OP_STACK.clear()

def p_print(p):
    ''' PRINT : PRINT_KWD OPEN_PARENTHESIS PRINTABLE CLOSE_PARENTHESIS '''
    Utils.push_to_quads(Quad("PRNT", -1, -1, -1))
    DOT_OP_STACK.clear()

def p_println(p):
    ''' PRINTLN : PRINTLN_KWD OPEN_PARENTHESIS PRINTABLE CLOSE_PARENTHESIS '''
    Utils.push_to_quads(Quad("PRNTLN", -1, -1, -1))
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
            EXCEPTION_HANDLER.raiseException("Type Error: Cannot print '" + printable_type + "' type")

    Utils.push_to_quads(Quad("PRNTBFFR", -1, -1, FUNC_DIR.get_symbol_mem_index(printable, printable_scope, printable_is_attr)))

def p_entered_condition(p):
    ''' entered_condition : empty '''
    CONDITIONAL_DEPTH_STACK.append("|CONDITION|")

def p_left_condition(p):
    ''' left_condition : empty '''
    CONDITIONAL_DEPTH_STACK.pop()

def p_decision(p):
    ''' DECISION : IF_KWD OPEN_PARENTHESIS EXPRESSION CLOSE_PARENTHESIS seen_if_kwd OPEN_CURLY entered_condition STATEMENT_STAR left_condition CLOSE_CURLY DECISION_P '''
    dir = JUMP_STACK.pop()
    Utils.fill_quad(dir, GLOBALS.QUAD_POINTER)

def p_decision_p(p):
    ''' DECISION_P :            ELSE_KWD seen_else_kwd DECISION
                        |       ELSE_KWD seen_else_kwd OPEN_CURLY STATEMENT_STAR CLOSE_CURLY
                        |       empty '''

def p_seen_if_kwd(p):
    ''' seen_if_kwd : empty '''
    Utils.decision_statement()

def p_seen_else_kwd(p):
    ''' seen_else_kwd : empty '''
    Utils.push_to_quads(Quad("GOTO", -1, -1,"PND"))
    dir = JUMP_STACK.pop()
    JUMP_STACK.append(GLOBALS.QUAD_POINTER - 1)
    Utils.fill_quad(dir, GLOBALS.QUAD_POINTER)

def p_repetition(p):
    ''' REPETITION : CONDITIONAL_REP
                   | UNCONDITIONAL_REP '''

def p_conditional_rep(p):
    ''' CONDITIONAL_REP : WHILE_KWD seen_while_kwd OPEN_PARENTHESIS EXPRESSION CLOSE_PARENTHESIS seen_while_exp OPEN_CURLY entered_condition STATEMENT_STAR CLOSE_CURLY left_condition '''
    end_dir = JUMP_STACK.pop()
    return_dir = JUMP_STACK.pop()
    Utils.push_to_quads(Quad("GOTO", -1, -1, return_dir))
    Utils.fill_quad(end_dir, GLOBALS.QUAD_POINTER)

def p_seen_while_kwd(p):
    ''' seen_while_kwd : empty '''
    JUMP_STACK.append(GLOBALS.QUAD_POINTER)

def p_seen_while_exp(p):
    ''' seen_while_exp : empty '''
    Utils.decision_statement()

def p_unconditional_rep(p):
    ''' UNCONDITIONAL_REP : FOR_KWD OPEN_PARENTHESIS VAR seen_for_kwd EQUALS EXPRESSION seen_for_start_exp SEMI_COLON EXPRESSION seen_for_end_exp SEMI_COLON FOR_INCR_STATEMENT seen_for_incr_exp CLOSE_PARENTHESIS OPEN_CURLY entered_condition STATEMENT_STAR CLOSE_CURLY left_condition '''
    swap_end_dir = JUMP_STACK.pop()
    swap_start_dir = JUMP_STACK.pop()
    end_dir = JUMP_STACK.pop()
    loop_dir = JUMP_STACK.pop()

    incr_res = OPERAND_STACK.pop()

    for i in range(swap_start_dir, swap_end_dir):
        Utils.swap_quads(swap_start_dir, GLOBALS.QUAD_POINTER) # This ensures that the increment statement will execute at the end of the for loop, and not at the start!

    Utils.push_to_quads(Quad("GOTO", -1, -1, loop_dir))
    Utils.fill_quad(end_dir, GLOBALS.QUAD_POINTER)

def p_seen_for_kwd(p):
    ''' seen_for_kwd : empty '''
    OPERAND_STACK.append(FUNC_DIR.symbol_lookup(p[-1], SCOPES_STACK[-1]))
    TYPE_STACK.append(FUNC_DIR.symbol_type_lookup(p[-1], SCOPES_STACK[-1]))
    OPERATOR_STACK.append("=")

def p_seen_for_incr_exp(p):
    ''' seen_for_incr_exp : empty'''
    JUMP_STACK.append(GLOBALS.QUAD_POINTER)

def p_seen_for_start_exp(p):
    ''' seen_for_start_exp : empty '''
    Utils.assign_to_var(True)
    JUMP_STACK.append(GLOBALS.QUAD_POINTER)

def p_seen_for_end_exp(p):
    ''' seen_for_end_exp : empty '''

    expr_end_type = TYPE_STACK.pop()

    if SemanticCube[expr_end_type]["=="]["boolean"] == "err":
        EXCEPTION_HANDLER.raiseException("Type mismatch: non-boolean end expression in 'for' statement")

    res_scope = SCOPES_STACK[-1]
    res = OPERAND_STACK.pop()
    if type(res) == list:
        res, res_scope = res

    JUMP_STACK.append(GLOBALS.QUAD_POINTER)
    Utils.push_to_quads(Quad("GOTOF", -1, FUNC_DIR.get_symbol_mem_index(res, res_scope), "PND"))
    JUMP_STACK.append(GLOBALS.QUAD_POINTER)

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
    if p != None:
        EXCEPTION_HANDLER.raiseException("Syntax error! Unexpected token: '" + str(p.value) + "', of type '" + p.type + "'")
    else:
        EXCEPTION_HANDLER.raiseException("Syntax error! No token information found. Maybe an unterminated comment (/*/) pair?")
