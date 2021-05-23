from Compiler.Avail import *

class SymbolTable(object):
    """docstring for SymbolTable."""

    #                                   // Memory Signature Translation
    #
    #                                           0 -> INT
    #                       0 -> CONSANT        1 -> FLOAT
    #                       1 -> GLOBAL         2 -> STRING
    #                       2 -> LOCAL          3 -> BOOL           0 -> VAR
    #                       3 -> CLASS          4 -> OBJECT         1 -> TMP

    SYMBOL_CLASSES = ["constant", "symbol", "temporal variable"]
    MEMORY_SECTOR_SIGN = [["0", "1", "2", "3"], ["0", "1", "2", "3", "4"], ["0", "1"]]
    MEMORY_SECTOR_SHIFTS = None


    def __init__(self, scope, mem_constraints, var_types, program_name):
        self.scope = scope
        self.SYMBOLS = {}
        self.param_indices = []
        self.var_memory_signature = { "int" : 0, "float" : 0, "string" : 0, "boolean" : 0, "object" : 0}
        self.temp_memory_signature = { "int" : 0, "float" : 0, "string" : 0, "boolean" : 0, "object" : 0 }
        self.const_memory_signature = {"int" : 0, "float" : 0, "string" : 0, "boolean" : 0, "object" : 0 } # FOR GLOBAL SCOPE ONLY
        self.mem_constraints = mem_constraints
        self.var_types = var_types
        self.program_name = program_name

        if SymbolTable.MEMORY_SECTOR_SHIFTS == None:
            self.build_memory_secor_shift(self.mem_constraints)


    def set_sym_obj_type(self, sym_id, obj_type):
        if sym_id in self.SYMBOLS:
            self.SYMBOLS[sym_id] = (self.SYMBOLS[sym_id][0], self.SYMBOLS[sym_id][1], self.SYMBOLS[sym_id][2], self.SYMBOLS[sym_id][3], self.SYMBOLS[sym_id][4], self.SYMBOLS[sym_id][5], self.SYMBOLS[sym_id][6], obj_type)
        else:
            raise Exception("Cannot set object type of " + sym_id + " to " + obj_type)


    def get_object_symbol_type(self, sym_id):
        if sym_id in self.SYMBOLS:
            return self.SYMBOLS[sym_id][7]

        raise Exception("Cannot get objet symbol type for " + sym_id + " in " + self.scope)

    def is_sym_arr(self, sym_id):
        if sym_id in self.SYMBOLS:
            return self.SYMBOLS[sym_id][4]
        else:
            if self.scope == self.program_name:
                raise Exception("Cannot check if " + sym_id + " is an array in " + self.scope)
            return -1

    def is_sym_ptr(self, sym_id):
        if sym_id in self.SYMBOLS:
            return self.SYMBOLS[sym_id][6]
        else:
            if self.scope == self.program_name:
                raise Exception("Cannot check if " + sym_id + " is a pointer in " + self.scope)
            return -1

    def get_dimensions(self, sym_id):
        if sym_id in self.SYMBOLS:
            return self.SYMBOLS[sym_id][5]
        else:
            if self.scope == self.program_name:
                raise Exception("Cannot get dimensions for symbol " + sym_id + " in " + self.scope)
            return -1

    def build_memory_secor_shift(self, mem_constraints):
        SymbolTable.MEMORY_SECTOR_SHIFTS = [[0, mem_constraints[0] * self.var_types, mem_constraints[0] * self.var_types + (mem_constraints[1] + mem_constraints[2]) * self.var_types, mem_constraints[0] * self.var_types + (mem_constraints[1] + mem_constraints[2] + mem_constraints[3] + mem_constraints[4]) * self.var_types], [0, mem_constraints[2] * self.var_types]]

    def get_mem_index(self, sym_id):
        if sym_id in self.SYMBOLS:
            return self.SYMBOLS[sym_id][1]
        else:
            if self.scope == self.program_name:
                raise Exception("Cannot get memory index for symbol " + sym_id + " in " + self.scope)
            return -1


    def next_avail(self, t_id, type, mem_sec_sign, is_ptr):
        self.declare_symbol(t_id, type, mem_sec_sign, is_temp = True, is_ptr = is_ptr)


    def update_const_mem_sign(self, type, dimensions = None):
        is_arr = dimensions != None

        if type not in self.const_memory_signature:
            if type == "void":
                return
            raise Exception("Type error: type " + type + " is unknown")

        if is_arr:
            self.const_memory_signature[type] += self.get_array_element_size(dimensions)
        else:
            self.const_memory_signature[type] += 1

    def update_temp_mem_sign(self, type, dimensions = None):
        is_arr = dimensions != None

        if type not in self.temp_memory_signature:
            if type == "void":
                return
            raise Exception("Type error: type " + type + " is unknown")

        if is_arr:
            self.temp_memory_signature[type] += self.get_array_element_size(dimensions)
        else:
            self.temp_memory_signature[type] += 1

    def update_var_mem_sign(self, type, dimensions = None):
        is_arr = dimensions != None

        if type not in self.var_memory_signature:
            if type == "void":
                return
            raise Exception("Type error: type " + type + " is unknown")

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

    def declare_symbol(self, sym_id, sym_type, mem_sec_sign, is_return_value = False, is_temp = False, is_cnst = False, is_param = False, is_array = False, dimensions = None, is_ptr = False):
        if sym_id not in self.SYMBOLS:
            mem_index = self.calculate_mem_index(mem_sec_sign)
            self.SYMBOLS[sym_id] = (sym_type, mem_index, is_return_value, is_cnst, is_array, dimensions, is_ptr, None)

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
                raise Exception("Multiple Declarations of " + sym_id + " in " + self.scope)

    def calculate_mem_index(self, mem_sec_sign):
        # Here we define where in memory to place this based on the memory sector signature
        mem_index = 0
        is_cnst = (mem_sec_sign[0] == "0")
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
            raise Exception("Memory Error: Program " + self.program_name + " exceeds " + SymbolTable.SYMBOL_CLASSES[int(mem_sec_sign[0])] + " limit of " + str(limit))

        mem_index += displacement

        return mem_index

    def symbol_lookup(self, sym_id):
        in_table_id = sym_id

        if "+" in sym_id:
            # It is an array!
            _plus_index = sym_id.index("+")
            in_table_id = sym_id[:_plus_index]

        if in_table_id in self.SYMBOLS:
            if self.SYMBOLS[in_table_id][2]: # This symbol is marked as RETURN VALUE, meaning it is used as a global storage for the function with the same name to store its return value
                raise Exception("Syntax Error: Use of function name " + in_table_id + " as variable ID. (Maybe missing '()' ?)")
            return sym_id
        else:
            raise Exception("Unseen symbol " + in_table_id + " in " + self.scope)

    def type_lookup(self, sym_id):
        in_table_id = sym_id

        if "+" in sym_id:
            # It is an array!
            _plus_index = sym_id.index("+")
            in_table_id = sym_id[:_plus_index]

        if in_table_id in self.SYMBOLS:
            return self.SYMBOLS[in_table_id][0]
        else:
            raise Exception("Unseen symbol " + in_table_id + " in " + self.scope)
