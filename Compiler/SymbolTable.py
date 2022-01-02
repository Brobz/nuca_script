from Compiler.Avail import *

class SymbolTable(object):
    """

    Basic data structure that stands at the bottom of the NucaScript compiler

    SymbolTables are instantiaded and maintained by the FunctionDirectory class, and store all of the information needed
    to generate the memory and instructions of the virtual machine.

    """

    #                                   // Memory Signature Translation
    #
    #                                           0 -> INT
    #                       0 -> CONSANT        1 -> FLOAT
    #                       1 -> GLOBAL         2 -> STRING
    #                       2 -> LOCAL          3 -> BOOLEAN        0 -> VAR
    #                       3 -> CLASS          4 -> OBJECT         1 -> TMP

    TRUTH = ["0FALSEFalsefalse", "1TRUETruetrue"]
    SYMBOL_CLASSES = ["constant", "symbol", "temporal variable", "class variable"]
    MEMORY_SECTOR_SIGN = [["0", "1", "2", "3"], ["0", "1", "2", "3", "4"], ["0", "1"]]
    MEMORY_SECTOR_SHIFTS = None
    EXCEPTION_HANDLER = None

    def __init__(self, scope, mem_constraints, var_types, program_name, set_truth = False):
        self.scope = scope
        self.SYMBOLS = {}
        self.param_indices = []
        self.var_memory_signature = { "int" : 0, "float" : 0, "string" : 0, "boolean" : 0, "object" : 0}
        self.temp_memory_signature = { "int" : 0, "float" : 0, "string" : 0, "boolean" : 0, "object" : 0 }
        self.const_memory_signature = {"int" : 0, "float" : 0, "string" : 0, "boolean" : 0, "object" : 0 }
        self.mem_constraints = mem_constraints
        self.var_types = var_types
        self.program_name = program_name

        if SymbolTable.MEMORY_SECTOR_SHIFTS == None:
            self.build_memory_secor_shift(self.mem_constraints)

        if set_truth:
            self.declare_symbol(SymbolTable.TRUTH[0], "boolean", "030", False, False, True, False, False, None, False)
            self.declare_symbol(SymbolTable.TRUTH[1], "boolean", "030", False, False, True, False, False, None, False)

    def get_array_symbol_element_size(self, sym_id, last_attempt = False):
        if sym_id in self.SYMBOLS:
            return self.get_array_element_size(self.SYMBOLS[sym_id][5])

        if last_attempt:
            SymbolTable.EXCEPTION_HANDLER.raiseException(">> Cannot get array element size for symbol " + sym_id)

        return None

    def get_arr_pointed(self, sym_id, last_attempt = False):
        if sym_id in self.SYMBOLS:
            return self.SYMBOLS[sym_id][8]

        if last_attempt:
            SymbolTable.EXCEPTION_HANDLER.raiseException(">> Cannot get array pointed to by " + sym_id)

        return None

    def reset_object_symbol_types(self):
        for sym_id in self.SYMBOLS:
            self.set_sym_obj_type(sym_id, None)

    def set_sym_obj_type(self, sym_id, obj_type, last_attempt = False):
        if sym_id in self.SYMBOLS:
            self.SYMBOLS[sym_id] = (self.SYMBOLS[sym_id][0], self.SYMBOLS[sym_id][1], self.SYMBOLS[sym_id][2],
                                    self.SYMBOLS[sym_id][3], self.SYMBOLS[sym_id][4], self.SYMBOLS[sym_id][5], self.SYMBOLS[sym_id][6], obj_type, self.SYMBOLS[sym_id][8])
            return True

        if last_attempt:
            SymbolTable.EXCEPTION_HANDLER.raiseException(">> Cannot set object type " + obj_type + " to " + sym_id + " in " + self.scope)

        return None

    def get_symbol_object_type(self, sym_id, last_attempt = False):
        if sym_id in self.SYMBOLS:
            return self.SYMBOLS[sym_id][7]

        if last_attempt:
            SymbolTable.EXCEPTION_HANDLER.raiseException(">> Cannot get objet type for symbol " + sym_id + " in " + self.scope)

        return None

    def is_sym_arr(self, sym_id):
        if sym_id in self.SYMBOLS:
            return self.SYMBOLS[sym_id][4]
        else:
            if self.scope == self.program_name:
                SymbolTable.EXCEPTION_HANDLER.raiseException(">> Cannot check if " + sym_id + " is an array in " + self.scope)
            return -1

    def is_sym_ptr(self, sym_id):
        if sym_id in self.SYMBOLS:
            return self.SYMBOLS[sym_id][6]
        else:
            if self.scope == self.program_name:
                SymbolTable.EXCEPTION_HANDLER.raiseException(">> Cannot check if " + sym_id + " is a pointer in " + self.scope)
            return -1

    def get_dimensions(self, sym_id):
        if sym_id in self.SYMBOLS:
            return self.SYMBOLS[sym_id][5]
        else:
            if self.scope == self.program_name:
                SymbolTable.EXCEPTION_HANDLER.raiseException(">> Cannot get dimensions for symbol " + sym_id + " in " + self.scope)
            return -1

    def build_memory_secor_shift(self, mem_constraints):
        SymbolTable.MEMORY_SECTOR_SHIFTS = [[0, mem_constraints[0] * (self.var_types - 1),
                                            mem_constraints[0] * (self.var_types - 1) + (mem_constraints[1] + mem_constraints[2]) * self.var_types,
                                            mem_constraints[0] * (self.var_types - 1) + (mem_constraints[1] + mem_constraints[2]) * self.var_types * 2],
                                            [0, mem_constraints[2] * self.var_types]]

    def get_mem_index(self, sym_id):
        if sym_id in self.SYMBOLS:
            return self.SYMBOLS[sym_id][1]
        else:
            if self.scope == self.program_name:
                SymbolTable.EXCEPTION_HANDLER.raiseException(">> Cannot get memory index for symbol " + sym_id + " in " + self.scope)
            return -1

    def next_avail(self, t_id, type, mem_sec_sign, is_ptr, arr_pointed = None):
        self.declare_symbol(t_id, type, mem_sec_sign, is_temp = True, is_ptr = is_ptr, arr_pointed = arr_pointed)

    def update_const_mem_sign(self, type, dimensions = None):
        is_arr = dimensions != None

        if type not in self.const_memory_signature:
            if type == "void":
                return
            SymbolTable.EXCEPTION_HANDLER.raiseException(">> Type error: type " + type + " is unknown")

        if is_arr:
            self.const_memory_signature[type] += self.get_array_element_size(dimensions)
        else:
            self.const_memory_signature[type] += 1

    def update_temp_mem_sign(self, type, dimensions = None):
        is_arr = dimensions != None

        if type not in self.temp_memory_signature:
            if type == "void":
                return
            SymbolTable.EXCEPTION_HANDLER.raiseException(">> Type error: type " + type + " is unknown")

        if is_arr:
            self.temp_memory_signature[type] += self.get_array_element_size(dimensions)
        else:
            self.temp_memory_signature[type] += 1

    def update_var_mem_sign(self, type, dimensions = None):
        is_arr = dimensions != None

        if type not in self.var_memory_signature:
            if type == "void":
                return
            SymbolTable.EXCEPTION_HANDLER.raiseException(">> Type error: type " + type + " is unknown")

        if is_arr:
            self.var_memory_signature[type] += self.get_array_element_size(dimensions)
        else:
            self.var_memory_signature[type] += 1

    def get_types_list(self): # FOR FUNCTION ARGUMENT VERIFICATION
        l = []
        for tuple in self.SYMBOLS.values():
            l.append(tuple[0])
        return l

    def get_array_element_size(self, dimensions):
        element_size = 1
        for d in dimensions:
            element_size *= d

        return element_size

    def declare_symbol(self, sym_id, sym_type, mem_sec_sign, is_return_value = False, is_temp = False, is_cnst = False, is_param = False, is_array = False, dimensions = None, is_ptr = False, arr_pointed = None):
        if sym_id not in self.SYMBOLS:
            mem_index = self.calculate_mem_index(mem_sec_sign)
            # type, memory index, return value flag, constant flag, array flag, dimensions (in case it is an array), ptr flag, object type (in case it is an object), array pointed to (in case it is a pointer)
            self.SYMBOLS[sym_id] = (sym_type, mem_index, is_return_value, is_cnst, is_array, dimensions, is_ptr, None, arr_pointed)
            if is_cnst:
                self.update_const_mem_sign(sym_type, dimensions)
            elif not is_temp:
                self.update_var_mem_sign(sym_type, dimensions)
            else:
                self.update_temp_mem_sign(sym_type, dimensions)

            if is_param:
                self.param_indices.append(mem_index)
        else:
            if is_cnst or is_return_value:
                pass
            else:
                SymbolTable.EXCEPTION_HANDLER.raiseException(">> Multiple Declarations of " + sym_id + " in " + self.scope)

    def calculate_mem_index(self, mem_sec_sign):
        # Here we define where in memory to place this based on the memory sector signature
        mem_index = 0

        is_cnst = (mem_sec_sign[0] == "0")
        is_obj = (mem_sec_sign[0] == "3")
        is_tmp = (mem_sec_sign[2] == "1")

        for i, char in enumerate(mem_sec_sign):
            shift_index = SymbolTable.MEMORY_SECTOR_SIGN[i].index(char)
            if i != 1:
                if i >= len(SymbolTable.MEMORY_SECTOR_SHIFTS):
                    i = len(SymbolTable.MEMORY_SECTOR_SHIFTS) - 1
                shift = SymbolTable.MEMORY_SECTOR_SHIFTS[i][shift_index]
            elif is_cnst:
                shift = self.mem_constraints[0] * shift_index
            elif is_tmp:
                shift = self.mem_constraints[2] * shift_index
            elif is_obj:
                shift = self.mem_constraints[3] * shift_index
            else:
                shift = self.mem_constraints[1] * shift_index

            mem_index += shift

        if mem_sec_sign[2] == "1":
            displacement = list(self.temp_memory_signature.values())[int(mem_sec_sign[1])]
        elif mem_sec_sign[0] == "0":
            displacement = list(self.const_memory_signature.values())[int(mem_sec_sign[1])]
        else:
            displacement = list(self.var_memory_signature.values())[int(mem_sec_sign[1])]

        limit = self.mem_constraints[int(mem_sec_sign[0])]
        if displacement >= limit:
            # TOO MANY VARIABLES!
            SymbolTable.EXCEPTION_HANDLER.raiseException(">> Memory Error: Program " + self.program_name + " exceeds " + SymbolTable.SYMBOL_CLASSES[int(mem_sec_sign[0])] + " limit of " + str(limit))

        mem_index += displacement

        return mem_index

    def symbol_lookup(self, sym_id, last_attempt = False):
        in_table_id = sym_id

        if "+" in sym_id:
            # It is an array!
            _plus_index = sym_id.index("+")
            in_table_id = sym_id[:_plus_index]

        if in_table_id in self.SYMBOLS:
            if self.SYMBOLS[in_table_id][2]: # This symbol is marked as RETURN VALUE, meaning it is used as a global storage for the function with the same name to store its return value
                SymbolTable.EXCEPTION_HANDLER.raiseException(">> Syntax Error: Use of function name " + in_table_id + " as variable ID. (Maybe missing '()' ?)")
            return sym_id

        if last_attempt:
            SymbolTable.EXCEPTION_HANDLER.raiseException(">> Unseen symbol " + in_table_id + " in " + self.scope)

        return None

    def type_lookup(self, sym_id, last_attempt = False):
        if sym_id in self.SYMBOLS:
            return self.SYMBOLS[sym_id][0]

        if last_attempt:
            SymbolTable.EXCEPTION_HANDLER.raiseException(">> Unseen symbol " + sym_id + " in " + self.scope)

        return None
