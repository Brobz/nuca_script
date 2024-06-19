import os
from .OPCodes import OPCodes
from .Quad import Quad
from .SemanticCube import SemanticCube
from .Boostrapper import ARRAY_DIMENSION_STACK, CLASS_INSTANCE_STACK, DOT_OP_STACK, EXCEPTION_HANDLER, FUNC_DIR, GLOBALS, JUMP_STACK, OBJECT_ACCESS_STACK, OPERAND_STACK, OPERATOR_STACK, SCOPES_STACK, TYPE_STACK, VM_CONSTANTS_MARKER_STR, VM_FUNCTION_MEMORY_MARKER_STR, VM_MEMORY_CONSTRAINTS_MARKER_STR, VM_OBJECT_MEMORY_MARKER_STR, VM_QUAD_MARKER_STR

## Quad Helper Functions ##
#  a few methods to make quad manipulation easier #

def push_to_quads(q):
    GLOBALS.QUADS.append(q)
    GLOBALS.QUAD_POINTER = GLOBALS.QUAD_POINTER + 1

def fill_quad(dir, fill):
    q = GLOBALS.QUADS[dir]

    if q.arg_3 == "PND":
        q.arg_3 = fill
    else:
        EXCEPTION_HANDLER.raiseException("Quad Error: trying to fill complete quad!")

def swap_quads(q1, q2):
    if q2 > len(GLOBALS.QUADS) - 1:
        GLOBALS.QUADS.append(GLOBALS.QUADS.pop(q1))
        for q in GLOBALS.QUADS:
            if q.operator in [OPCodes["GOTO"], OPCodes["GOTOF"]] and q.arg_3 != "PND": # If this QUAD is either a GOTO or a GOTOF...
                if q.arg_3 > q1: # And was pointing to a quad placed after (bigger index) the one we popped...
                    # Jump dir has been changed since we popped a quad that came before the one we were jumping to
                    q.arg_3 -= 1 # Adjust the value
    else:
        temp = GLOBALS.QUADS[q2]
        GLOBALS.QUADS[q2] = GLOBALS.QUADS[q1]
        GLOBALS.QUADS[q1] = temp

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
                EXCEPTION_HANDLER.raiseException("Type Error: Cannot declare 'void' type variables")
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
        if FUNC_DIR.is_sym_pointer(left[0], left[1]):
            ptr_value = 1
    if right != None:
        if FUNC_DIR.is_sym_pointer(right[0], right[1]):
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
        EXCEPTION_HANDLER.raiseException("Type Mismatch: " + left_type + " " + operator + " " + right_type)

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
            EXCEPTION_HANDLER.raiseException("Index Error: array " + array_id + " expects " + str(len(dims)) + " access indices, received " + str(len(access_values)))

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
                parent_obj_addr = -1
                parent_obj_id = OBJECT_ACCESS_STACK.pop()
                if parent_obj_id != "this_kwd":
                    parent_obj_addr = FUNC_DIR.get_symbol_mem_index(parent_obj_id, SCOPES_STACK[-1])

                push_to_quads(Quad("OBJ_READ", parent_obj_addr,  FUNC_DIR.get_symbol_mem_index(ptr_to_array_value_at_index, SCOPES_STACK[-1]), FUNC_DIR.get_symbol_mem_index(value_at_index, SCOPES_STACK[-1]), get_ptr_value([ptr_to_array_value_at_index, SCOPES_STACK[-1]], [value_at_index, SCOPES_STACK[-1]])))

                OPERAND_STACK.append(FUNC_DIR.symbol_lookup(value_at_index, SCOPES_STACK[-1]))
                TYPE_STACK.append(FUNC_DIR.symbol_type_lookup(value_at_index, SCOPES_STACK[-1]))

    else:
        # It is a regular (simple) variable!
        if not is_class_attr:
            # Regular Variable
            var = FUNC_DIR.symbol_lookup(id, SCOPES_STACK[-1], is_class_attr)
            if FUNC_DIR.is_sym_arr(id, SCOPES_STACK[-1], False) and not is_io:
                # Trying to access an array symbol without [] !
                EXCEPTION_HANDLER.raiseException("Name Error: symbol " + id + " is defined as an array and cannot be referenced directly (maybe missing [] operator?)")

            OPERAND_STACK.append([var, SCOPES_STACK[-1], is_class_attr])
            TYPE_STACK.append(FUNC_DIR.symbol_type_lookup(id, SCOPES_STACK[-1], is_class_attr))

        else:
            var = FUNC_DIR.symbol_lookup(id, DOT_OP_STACK[-1], True)
            # Class Variable
            if FUNC_DIR.is_sym_arr(id, DOT_OP_STACK[-1], is_class_attr) and not is_io:
                # Trying to access an array symbol without [] !
                EXCEPTION_HANDLER.raiseException("Name Error: symbol " + id + " is defined as an array and cannot be referenced directly (maybe missing [] operator?)")

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
        EXCEPTION_HANDLER.raiseException("Type Mismatch: " + res_type + " " + op + " " + right_type)

    class_idx = -1
    if res_type == "object":
        # We are assigning to an object, which means we are instantiating it!
        # First lets check this is ACTUALLY an instantation  and check  if the right operand is a temporal:
        if not  len(CLASS_INSTANCE_STACK): # Its not an instantation!
            EXCEPTION_HANDLER.raiseException("Type Error: cannot assign to objects directly, only by instantiation!")
        CLASS_INSTANCE_STACK.pop() # Remove the instantiation validation
        class_type = FUNC_DIR.get_symbol_object_type(right_operand, SCOPES_STACK[-1]) # Get the class type from the right operand of the =
        class_idx = FUNC_DIR.get_class_idx(class_type) # From that, find out what the class index is
        if FUNC_DIR.is_sym_pointer(res, res_scope): # If we are instantiating into an array,
            arr_pointed = FUNC_DIR.get_arr_pointed_to(res, res_scope) # We need to check if this array has the appropriate (if any) class type, and update it if needed
            arr_pointed_object_type = FUNC_DIR.get_symbol_object_type(arr_pointed[0], arr_pointed[1])
            if arr_pointed_object_type != class_type:
                EXCEPTION_HANDLER.raiseException("Type Error: " + arr_pointed_object_type + " = " + class_type)
        else:
            res_class_type = FUNC_DIR.get_symbol_object_type(res, res_scope)
            if res_class_type != class_type:
                EXCEPTION_HANDLER.raiseException("Type Error: " + res_class_type + " = " + class_type)
            FUNC_DIR.set_symbol_object_type(res, class_type, SCOPES_STACK[-1]) # Set this object's type


    if not res_attr:
        if class_idx == -1:
            # Assigning to regular variable; Use =
            push_to_quads(Quad("=", get_ptr_value([right_operand, right_scope], [res, res_scope]), FUNC_DIR.get_symbol_mem_index(right_operand, right_scope, right_attr), FUNC_DIR.get_symbol_mem_index(res, res_scope, res_attr)))
        else:
            # Assigning to Object variable; Use OBJ_INST

            res_is_ptr = -1
            if FUNC_DIR.is_sym_pointer(res, res_scope):
                res_is_ptr = 1

            push_to_quads(Quad("OBJ_INST", res_is_ptr, class_idx, FUNC_DIR.get_symbol_mem_index(res, res_scope, res_attr)))
    else:
        # Assigning to class variable; Use OBJ_WRITE

        if FUNC_DIR.is_sym_pointer(res, res_scope):
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

    if FUNC_DIR.is_sym_pointer(OPERAND_STACK[-1][0], OPERAND_STACK[-1][1]):
        # Since this is an array, need to figure out the pointer from the left side of the compound assignment into a factor on the left side
        value_at_index = FUNC_DIR.next_avail(TYPE_STACK[-1], SCOPES_STACK[-1])
        if not OPERAND_STACK[-1][2]:
            # Global / local array! Just use a regular =
            push_to_quads(Quad("=", 1,  FUNC_DIR.get_symbol_mem_index(OPERAND_STACK[-1][0], OPERAND_STACK[-1][1]), FUNC_DIR.get_symbol_mem_index(value_at_index, SCOPES_STACK[-1])))

            OPERAND_STACK.append([FUNC_DIR.symbol_lookup(value_at_index, SCOPES_STACK[-1]), SCOPES_STACK[-1], OPERAND_STACK[-1][2]])

        else:
            # Array as an object attribute! Use OBJ_READ
            parent_obj_addr = -1
            parent_obj_id = CLASS_INSTANCE_STACK[-1]
            if parent_obj_id != "this_kwd":
                parent_obj_addr = FUNC_DIR.get_symbol_mem_index(parent_obj_id, SCOPES_STACK[-1])

            push_to_quads(Quad("OBJ_READ", parent_obj_addr,  FUNC_DIR.get_symbol_mem_index(OPERAND_STACK[-1][0], OPERAND_STACK[-1][1]), FUNC_DIR.get_symbol_mem_index(value_at_index, SCOPES_STACK[-1]), get_ptr_value([OPERAND_STACK[-1][0], OPERAND_STACK[-1][1]], [value_at_index, SCOPES_STACK[-1]])))

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
            EXCEPTION_HANDLER.raiseException("Type Error: cannot use " + op + " operator with " + TYPE_STACK[-1] + " type variable")

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
        EXCEPTION_HANDLER.raiseException("Type Mismatch: non-boolean (" + expr_type + ") expression in decision statement")

    res_scope = SCOPES_STACK[-1]
    res_attr = False
    res = OPERAND_STACK.pop()
    if type(res) == list:
        res, res_scope, res_attr = res
    push_to_quads(Quad("GOTOF", -1, FUNC_DIR.get_symbol_mem_index(res, res_scope, res_attr), "PND"))
    JUMP_STACK.append(GLOBALS.QUAD_POINTER - 1)

def fill_vm_file(file_path, marker_str, start_str, end_str, info):
    line_indices = []

    ## If the intermediate object-code file does not exist, create it
    if not os.path.exists(file_path):
        with open(file_path, "w+") as f:
            f.write("#include <vector>\n")
            f.write("#include <map>\n")
            f.write("using namespace std;\n")
            f.write("\n// \t\t!!! ATENTION !!!\n\n")
            f.write("// \tThe next few code segments are automatically generated during compilation time,\n")
            f.write("// \tand should not be tampered with!\n")
            f.write("// \tDoing so migh mess up the following compilation cycle!\n")
            f.write("\n// \t\t!!! ATENTION !!!\n\n")
            for marker_string in [VM_MEMORY_CONSTRAINTS_MARKER_STR, VM_FUNCTION_MEMORY_MARKER_STR, VM_OBJECT_MEMORY_MARKER_STR, VM_CONSTANTS_MARKER_STR, VM_QUAD_MARKER_STR]: 
                for i in range(2):
                    f.write(marker_string)
                
    
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

    with open(file_path, "w") as f:
        contents = "".join(contents)
        f.write(contents)