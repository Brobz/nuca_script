from Avail import *

class SymbolTable(object):
    """docstring for SymbolTable."""

    def __init__(self):
        self.SYMBOLS = {"GLOBAL" : {}}
        self.OperatorStack = []
        self.OperandStack = []
        self.TypeStack = []
        self.Avail = Avail()

    def add_scope(self, scope):
        if scope not in self.SYMBOLS:
            self.SYMBOLS[scope] = {}
        else:
            raise Exception("Multiple Declarations of " + scope)

    def declare_symbol(self, sym_id, sym_type, scope = "GLOBAL"):
        if sym_id not in self.SYMBOLS[scope]:
            self.SYMBOLS[scope][sym_id] = (sym_type, None)
        else:
            raise Exception("Multiple Declarations of " + sym_id + " in " + scope)

    def define_symbol(self, sym_id, sym_value, scope = "GLOBAL"):
        if sym_id in self.SYMBOLS[scope]:
            self.SYMBOLS[scope][sym_id] = (self.SYMBOLS[scope][sym_id][0], sym_value)
        else:
            raise Exception("No Declarations of " + sym_id + " in " + scope)

    def symbol_lookup(self, sym_id, scope = "GLOBAL"):
        if sym_id in self.SYMBOLS[scope]:
            return self.SYMBOLS[scope][sym_id][1]
        else:
            return sym_id

    def type_lookup(self, sym_id, scope = "GLOBAL"):
        if sym_id in self.SYMBOLS[scope]:
            return self.SYMBOLS[scope][sym_id][0]
        else:
            return sym_id
