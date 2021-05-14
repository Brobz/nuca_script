from Compiler.Avail import *

class SymbolTable(object):
    """docstring for SymbolTable."""

    def __init__(self, scope):
        self.scope = scope
        self.SYMBOLS = {}
        self.var_memory_signature = { "int" : 0, "float" : 0, "string" : 0, "boolean" : 0}
        self.temp_memory_signature = { "int" : 0, "float" : 0, "string" : 0, "boolean" : 0}

    def next_avail(self, type):
        self.update_temp_mem_sign(type)

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

    def declare_symbol(self, sym_id, sym_type, is_temp = False):
        if sym_id not in self.SYMBOLS:
            self.SYMBOLS[sym_id] = (sym_type, None, is_temp)
            self.update_var_mem_sign(sym_type)
        else:
            raise Exception("Multiple Declarations of " + sym_id + " in " + self.scope)

    def define_symbol(self, sym_id, sym_dir):
        if sym_id in self.SYMBOLS:
            self.SYMBOLS[sym_id] = (self.SYMBOLS[sym_id][0], sym_dir)
        else:
            raise Exception("No Declarations of " + sym_id + " in " + self.scope)

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
