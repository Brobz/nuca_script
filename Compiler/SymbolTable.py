from Compiler.Avail import *

class SymbolTable(object):
    """docstring for SymbolTable."""

    def __init__(self, scope):
        self.scope = scope
        self.SYMBOLS = {}
        self.Avail = Avail()


    def get_types_list(self): # FOR FUNCTION ARGUMENT VERIFICATION
        l = []
        for tuple in self.SYMBOLS.values():
            l.append(tuple[0])
        return l

    def declare_symbol(self, sym_id, sym_type, is_temp = False):
        if sym_id not in self.SYMBOLS:
            self.SYMBOLS[sym_id] = (sym_type, None, is_temp)
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
