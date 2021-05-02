from SymbolTable import *

class FunctionDirectory(object):
    """docstring for FunctionDirectory."""

    def __init__(self):
        self.current_scope = None
        self.FUNCS = {"PROGRAM" : None, "GLOBAL" : {}}


    def declare_symbol(self, sym_id, sym_type, scope = "GLOBAL"):
        if self.current_scope != None:
            if sym_id in self.FUNCS["PROGRAM"].SYMBOLS:
                print("WARNING: Definition of "  + sym_id + " in " + self.current_scope + " shadows previous global definition.")
            self.FUNCS[scope][self.current_scope][2].declare_symbol(sym_id, sym_type)
        else:
            self.FUNCS["PROGRAM"].declare_symbol(sym_id,  sym_type)

    def declare_param(self, param_id, param_type, scope = "GLOBAL"):
        if self.current_scope == None:
            raise Exception("Scope Error: Cant declare param")

        if param_id in self.FUNCS["PROGRAM"].SYMBOLS:
            print("WARNING: Definition of "  + param_id + " in " + self.current_scope + " shadows previous global definition.")

        self.FUNCS[scope][self.current_scope][1].declare_symbol(param_id, param_type)
        self.FUNCS[scope][self.current_scope][2].declare_symbol(param_id, param_type)


    def define_symbol(self, sym_id, sym_dir):
        if self.current_scope != None:
            self.FUNCS[scope][self.current_scope][2].define_symbol(sym_id, sym_dir)
        else:
            self.FUNCS["PROGRAM"].define_symbol(sym_id,  sym_dir)

    def declare_function(self, func_id, func_type, scope = "GLOBAL"):
        if scope == "PROGRAM":
            self.FUNCS[scope] = SymbolTable("GLOBAL")
        elif func_id not in self.FUNCS[scope]:
            self.FUNCS[scope][func_id] = (func_type, SymbolTable(func_id + "_param"), SymbolTable(func_id))
            self.current_scope = func_id
        else:
            raise Exception("Multiple Declarations of " + func_id + " in " + scope)

    def symbol_lookup(self, sym_id, scope = "GLOBAL"):
        if self.current_scope != None:
            try:
                return self.FUNCS[scope][self.current_scope][2].symbol_lookup(sym_id)
            except:
                return self.FUNCS["PROGRAM"].symbol_lookup(sym_id)

        return self.FUNCS["PROGRAM"].symbol_lookup(sym_id)


    def symbol_type_lookup(self, sym_id, scope = "GLOBAL"):
        if self.current_scope != None:
            try:
                return self.FUNCS[scope][self.current_scope][2].type_lookup(sym_id)
            except:
                return self.FUNCS["PROGRAM"].type_lookup(sym_id)

        return self.FUNCS["PROGRAM"].type_lookup(sym_id)


    def func_type_lookup(self, func_id, scope = "GLOBAL"):
        if func_id in self.FUNCS:
            return self.FUNCS[func_id][0]
        else:
            raise Exception("Unseen function: " + func_id)
