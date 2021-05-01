from Avail import *

class SymbolTable(object):
    """docstring for SymbolTable."""

    def __init__(self, scope):
        self.scope = scope
        self.SYMBOLS = {}
        self.Avail = Avail()

    def declare_symbol(self, sym_id, sym_type):
        if sym_id not in self.SYMBOLS:
            self.SYMBOLS[sym_id] = (sym_type, None)
        else:
            raise Exception("Multiple Declarations of " + sym_id + " in " + self.scope)

    def define_symbol(self, sym_id, sym_dir):
        if sym_id in self.SYMBOLS:
            self.SYMBOLS[sym_id] = (self.SYMBOLS[sym_id][0], sym_dir)
        else:
            raise Exception("No Declarations of " + sym_id + " in " + self.scope)

    def symbol_lookup(self, sym_id):
        if sym_id in self.SYMBOLS:
            return sym_id
        else:
            raise Exception("Unseen symbol " + sym_id + " in " + self.scope)

    def type_lookup(self, sym_id):
        if sym_id in self.SYMBOLS:
            return self.SYMBOLS[sym_id][0]
        else:
            raise Exception("Unseen symbol " + sym_id + " in " + self.scope)
