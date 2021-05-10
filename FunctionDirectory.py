from SemanticCube import *
from SymbolTable import *

class FunctionDirectory(object):
    """docstring for FunctionDirectory."""

    def __init__(self):
        self.current_scope = None
        self.FUNCS = {"PROGRAM" : None, "GLOBAL" : {}}


    def get_return_obj_name(self, func_name =  None, scope = "GLOBAL"):
        if func_name == None:
            if self.current_scope == None:
                raise Exception("Scope error: cannot get function return object name for " + func_name)
            func_name = self.current_scope

        if func_name not in self.FUNCS[scope]:
            raise  Exception("Name error: cannot get function return object name for " + func_name  + " in " + scope)

        return func_name

    def valid_return_check(self, ptr, scope = "GLOBAL"):
        if self.current_scope == None:
            raise Exception("Scope error: cant check for valid return")

        return self.FUNCS[scope][self.current_scope][5] == ptr

    def return_type_check(self, rtn_type, ptr, scope = "GLOBAL"):
        if self.current_scope == None:
            raise Exception("Scope error: cant check return type")

        func_type = self.FUNCS[scope][self.current_scope][0]
        if SemanticCube[rtn_type]["=="][func_type] == "err":
            raise Exception("Type mismatch: function " + self.current_scope + " expects " + func_type + ", got " + rtn_type + " instead. Maybe missing default return statement?")

        self.FUNCS[scope][self.current_scope][5] = ptr

    def args_ok(self, func_id, scope = "GLOBAL"):
        if func_id not in self.FUNCS[scope]:
            raise Exception("Unseen function: " + func_id)

        k = self.FUNCS[scope][func_id][4]
        if len(self.FUNCS[scope][func_id][1].SYMBOLS) != k:
            if k > 0:
                raise Exception("Argument mismatch: Call to " + func_id + " received " + str(k) + " parameters, was expecting " + str(len(self.FUNCS[scope][func_id][1].SYMBOLS)))
            elif k < 0:
                raise Exception("Argument mismatch: Call to " + func_id + " received parameters, was expecting " + str(len(self.FUNCS[scope][func_id][1].SYMBOLS)))

    def verify_arg_type(self, func_id, arg_type, scope = "GLOBAL"):
        if func_id not in self.FUNCS[scope]:
            raise Exception("Unseen function: " + func_id)

        k = self.FUNCS[scope][func_id][4]
        types_list = self.FUNCS[scope][func_id][1].get_types_list()

        if not len(types_list): # NO PARAM FUNC
            self.FUNCS[scope][func_id][4] = -1
            return

        if k >= len(types_list): # TOO MANY PARAMS
            raise Exception("Argument mismatch: Call to " + func_id + " received " + str(k + 1) + " or more parameters, was expecting " + str(len(types_list)))

        if arg_type != types_list[k]:
            raise Exception("Type mismatch: Call to " + func_id + " received " + arg_type + " argument, was expecting " + types_list[k])

        self.goto_next_param(func_id, scope)
        return k + 1

    def set_param_index(self, func_id, index, scope = "GLOBAL"):
        if func_id not in self.FUNCS[scope]:
            raise Exception("Unseen function: " + func_id)

        self.FUNCS[scope][func_id][4] = index

    def goto_next_param(self, func_id, scope = "GLOBAL"):
        if func_id not in self.FUNCS[scope]:
            raise Exception("Unseen function: " + func_id)

        if not len(self.FUNCS[scope][func_id][1].SYMBOLS): # NO PARAM FUNC
            self.FUNCS[scope][func_id][4] = -1
            return

        self.FUNCS[scope][func_id][4] += 1

    def get_func_size(self, func_id, scope = "GLOBAL"):
        if func_id not in self.FUNCS[scope]:
            raise Exception("Unseen function: " + func_id)
        return len(self.FUNCS[scope][func_id][2].SYMBOLS)

    def set_start_addr(self, addr, scope = "GLOBAL"):
        if self.current_scope != None:
            self.FUNCS[scope][self.current_scope][3] = addr # INDEX 3 IS START_ADDR
        else:
            raise Exception("Scope Error: Cant declare start addr")

    def declare_symbol(self, sym_id, sym_type, scope = "GLOBAL"):
        if sym_id in self.FUNCS[scope]:
            raise Exception("Attribute error: symbol " + sym_id + " is already declared as a function within " + scope)

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
            self.FUNCS[scope][func_id] = [func_type, SymbolTable(func_id + "_param"), SymbolTable(func_id), None, 0, False] # TYPE, ARG_TABLE, VAR_TABLE, START_ADDR, PARAM_POINTER, HAS_VALID_RTN
            self.FUNCS["PROGRAM"].declare_symbol(func_id, func_type, True) # Third argument as true sets this simbol to TEMPORARY
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
        if func_id in self.FUNCS[scope]:
            return self.FUNCS[scope][func_id][0]
        else:
            raise Exception("Unseen function: " + func_id)
