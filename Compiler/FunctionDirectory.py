from Compiler.SemanticCube import *
from Compiler.SymbolTable import *

class FunctionDirectory(object):
    """docstring for FunctionDirectory."""

    MEMORY_SECTOR_INDICES = ["int", "float", "string", "boolean"]

    def __init__(self):
        self.current_scope = None
        self.program_name = None
        self.main_start_addr = None
        self.FUNCS = {"GLOBAL" : {}}
        self.AVAIL = Avail()


    def declare_constant(self, cnst_id, cnst_type):
        self.declare_symbol(cnst_id, cnst_type, is_cnst = True)

    def get_symbol_mem_index(self, sym_id, scope = "GLOBAL"):
        if self.current_scope == None:
            return self.FUNCS[self.program_name].get_mem_index(sym_id, self.program_name)
        else:
            mem_index = self.FUNCS[scope][self.current_scope][2].get_mem_index(sym_id, self.program_name)
            if mem_index == -1:
                return self.FUNCS[self.program_name].get_mem_index(sym_id, self.program_name)
            return mem_index

    def next_avail(self, type, scope = "GLOBAL"):
        if type == "void": # Nope?
            return
        t_id = self.AVAIL.next()
        if self.current_scope == None:
            self.FUNCS[self.program_name].next_avail(t_id, type, "1" + str(FunctionDirectory.MEMORY_SECTOR_INDICES.index(type)) + "1")
        else:
            self.FUNCS[scope][self.current_scope][2].next_avail(t_id, type, "2" + str(FunctionDirectory.MEMORY_SECTOR_INDICES.index(type)) + "1")

        return t_id

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


    def set_main_start_addr(self, addr):
        self.main_start_addr = addr

    def get_main_start_addr(self):
        return self.main_start_addr

    def set_start_addr(self, addr, scope = "GLOBAL"):
        if self.current_scope != None:
            self.FUNCS[scope][self.current_scope][3] = addr # INDEX 3 IS START_ADDR
        else:
            raise Exception("Scope Error: Cant declare func start addr")

    def get_start_addr(self, func_id, scope = "GLOBAL"):
        if func_id in self.FUNCS[scope]:
            return self.FUNCS[scope][func_id][3] # INDEX 3 IS START_ADDR
        else:
            raise Exception("Scope Error: Cant get func start addr")

    def declare_symbol(self, sym_id, sym_type, is_return_value = False, scope = "GLOBAL", is_param = False, is_cnst = False, give_warning = True):
        if sym_type == "void": # Trying to declare a space for the return value of a void function... useless!
            return

        if sym_id in self.FUNCS[scope]:
            raise Exception("Attribute error: symbol " + sym_id + " is already declared as a function within " + scope)

        # Here we decide where in memory to place this symbol
        memory_sector_signature = list(str(FunctionDirectory.MEMORY_SECTOR_INDICES.index(sym_type)) + "0")


        if is_cnst:
            memory_sector_signature.insert(0, "0") # Global Constant
        elif self.current_scope != None:
            memory_sector_signature.insert(0, "2") # Local Variable
            if sym_id in self.FUNCS[self.program_name].SYMBOLS and give_warning:
                print("WARNING: Definition of "  + sym_id + " in " + self.current_scope + " shadows previous global definition.")
            sym_table_index = 2
            if is_param:
                sym_table_index = 1
            self.FUNCS[scope][self.current_scope][sym_table_index].declare_symbol(sym_id, sym_type, "".join(memory_sector_signature), is_return_value, False, is_cnst)
            return
        else:
            memory_sector_signature.insert(0, "1") # Global Variable

        self.FUNCS[self.program_name].declare_symbol(sym_id,  sym_type, "".join(memory_sector_signature), is_return_value, False, is_cnst)


    def declare_param(self, param_id, param_type, scope = "GLOBAL"):
        if self.current_scope == None:
            raise Exception("Scope Error: Cant declare param")

        self.declare_symbol(param_id, param_type, is_param = True)
        self.declare_symbol(param_id, param_type, give_warning = False)



    def define_symbol(self, sym_id, sym_dir):
        if self.current_scope != None:
            self.FUNCS[scope][self.current_scope][2].define_symbol(sym_id, sym_dir)
        else:
            self.FUNCS[self.program_name].define_symbol(sym_id,  sym_dir)

    def declare_function(self, func_id, func_type, scope = "GLOBAL"):
        if scope == "PROGRAM":
            self.program_name = func_id
            self.FUNCS[self.program_name] = SymbolTable(func_id)
        elif func_id not in self.FUNCS[scope]:
            self.declare_symbol(func_id, func_type, True) # Third argument as true sets this simbol to a return value; This is used as storage for the return value of the function with the same ID
            self.FUNCS[scope][func_id] = [func_type, SymbolTable(func_id + "_param"), SymbolTable(func_id), None, 0, False] # TYPE, ARG_TABLE, VAR_TABLE, START_ADDR, PARAM_POINTER, HAS_VALID_RTN
            self.current_scope = func_id
        else:
            raise Exception("Multiple Declarations of " + func_id + " in " + scope)

    def symbol_lookup(self, sym_id, scope = "GLOBAL"):
        if self.current_scope != None:
            try:
                return self.FUNCS[scope][self.current_scope][2].symbol_lookup(sym_id)
            except:
                return self.FUNCS[self.program_name].symbol_lookup(sym_id)

        return self.FUNCS[self.program_name].symbol_lookup(sym_id)


    def symbol_type_lookup(self, sym_id, scope = "GLOBAL"):
        if self.current_scope != None:
            try:
                return self.FUNCS[scope][self.current_scope][2].type_lookup(sym_id)
            except:
                return self.FUNCS[self.program_name].type_lookup(sym_id)

        return self.FUNCS[self.program_name].type_lookup(sym_id)


    def func_type_lookup(self, func_id, scope = "GLOBAL"):
        if func_id in self.FUNCS[scope]:
            return self.FUNCS[scope][func_id][0]
        else:
            raise Exception("Unseen function: " + func_id)
