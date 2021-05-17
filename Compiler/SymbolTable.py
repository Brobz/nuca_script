from Compiler.Avail import *

class SymbolTable(object):
    """docstring for SymbolTable."""

    MEMORY_SECTOR_SIGN = [["0", "1", "2"], ["0", "1", "2", "3"], ["0", "1"]]
    MEMORY_SECTOR_SHIFTS = [[0, 1000, 9000], [0, 250, 500, 750], [0, 1000]]


    def __init__(self, scope):
        self.scope = scope
        self.SYMBOLS = {}
        self.param_indices = []
        self.var_memory_signature = { "int" : 0, "float" : 0, "string" : 0, "boolean" : 0}
        self.temp_memory_signature = { "int" : 0, "float" : 0, "string" : 0, "boolean" : 0 }
        self.const_memory_signature = {"int" : 0, "float" : 0, "string" : 0, "boolean" : 0 } # FOR GLOBAL SCOPE ONLY

    def get_mem_index(self, sym_id, global_scope):
        if sym_id in self.SYMBOLS:
            return self.SYMBOLS[sym_id][1]
        else:
            if self.scope == global_scope:
                raise Exception("Cannot get memory index for symbol " + sym_id + " in " + self.scope)
            return -1


    def next_avail(self, t_id, type, mem_sec_sign):
        self.declare_symbol(t_id, type, mem_sec_sign, is_temp = True)


    def update_const_mem_sign(self, type):
        if type not in self.const_memory_signature:
            if type == "void":
                return
            raise Exception("Type error: type " + type + " is unknown")
        self.const_memory_signature[type] += 1

    def update_temp_mem_sign(self, type):
        if type not in self.temp_memory_signature:
            if type == "void":
                return
            raise Exception("Type error: type " + type + " is unknown")
        self.temp_memory_signature[type] += 1

    def update_var_mem_sign(self, type):
        if type not in self.var_memory_signature:
            if type == "void":
                return
            raise Exception("Type error: type " + type + " is unknown")
        self.var_memory_signature[type] += 1

    def get_types_list(self): # FOR FUNCTION ARGUMENT VERIFICATION
        l = []
        for tuple in self.SYMBOLS.values():
            l.append(tuple[0])
        return l

    def declare_symbol(self, sym_id, sym_type, mem_sec_sign, is_return_value = False, is_temp = False, is_cnst = False, is_param = False):
        if sym_id not in self.SYMBOLS:
            mem_index = self.calculate_mem_index(mem_sec_sign)
            self.SYMBOLS[sym_id] = (sym_type, mem_index, is_return_value, is_cnst)
            if is_cnst:
                self.update_const_mem_sign(sym_type)
            elif not is_temp:
                self.update_var_mem_sign(sym_type)
            else:
                self.update_temp_mem_sign(sym_type)

            if is_param:
                self.param_indices.append(mem_index)

        else:
            if is_cnst:
                pass
            else:
                raise Exception("Multiple Declarations of " + sym_id + " in " + self.scope)

    def calculate_mem_index(self, mem_sec_sign):
        # Here we define where in memory to place this based on the memory sector signature
        mem_index = 0
        is_cnst = (mem_sec_sign[0] == "0")
        for i, char in enumerate(mem_sec_sign):
            shift_index = SymbolTable.MEMORY_SECTOR_SIGN[i].index(char)
            shift = SymbolTable.MEMORY_SECTOR_SHIFTS[i][shift_index]
            if not is_cnst and i:
                shift *= 4
            mem_index += shift

        if mem_sec_sign[2] == "1":
            displacement = list(self.temp_memory_signature.values())[int(mem_sec_sign[1])]
        elif mem_sec_sign[0] == "0":
            displacement = list(self.const_memory_signature.values())[int(mem_sec_sign[1])]
        else:
            displacement = list(self.var_memory_signature.values())[int(mem_sec_sign[1])]

        mem_index += displacement

        return mem_index

    def symbol_lookup(self, sym_id):
        if sym_id in self.SYMBOLS:
            if self.SYMBOLS[sym_id][2]: # This symbol is marked as TEMPORARY, meaning it is used as a global storage for the function with the same name to store its return value
                raise Exception("Syntax Error: Use of function name " + sym_id + " as variable ID. (Maybe missing '()' ?)")
            return sym_id
        else:
            raise Exception("Unseen symbol " + sym_id + " in " + self.scope)

    def type_lookup(self, sym_id):
        if sym_id in self.SYMBOLS:
            return self.SYMBOLS[sym_id][0]
        else:
            raise Exception("Unseen symbol " + sym_id + " in " + self.scope)
