from Compiler.SemanticCube import *
from Compiler.SymbolTable import *

class FunctionDirectory(object):
    """docstring for FunctionDirectory."""

    MEMORY_SECTOR_INDICES = ["int", "float", "string", "boolean", "object"]
    VAR_TYPES = len(MEMORY_SECTOR_INDICES)

    def __init__(self, mem_constraints):
        self.current_scope = None
        self.program_name = None
        self.main_start_addr = None
        self.FUNCS = {"GLOBAL" : {}}
        self.AVAIL = Avail()
        self.mem_constraints = mem_constraints


    def valid_class_check(self, cls):
        if cls == "GLOBAL" or cls == self.program_name:
            return False

        if cls not in self.FUNCS:
            raise Exception("Name Error: " + cls + " is not a valid Class Name")

    def set_symbol_object_type(self, sym_id, obj_type, scope):
        if scope == "GLOBAL" or (sym_id not in self.FUNCS[scope]["FUNCS"][self.current_scope][2].SYMBOLS and sym_id not in self.FUNCS[scope]["SYMBOLS"].SYMBOLS):
            if self.current_scope != None and scope == "GLOBAL":
                self.FUNCS[scope][self.current_scope][2].set_sym_obj_type(sym_id, obj_type)
            else:
                self.FUNCS[self.program_name].set_sym_obj_type(sym_id, obj_type)
        else:
            if self.current_scope != None:
                try:
                    self.FUNCS[scope]["FUNCS"][self.current_scope][2].set_sym_obj_type(sym_id, obj_type)
                except:
                    self.FUNCS[scope]["SYMBOLS"].set_sym_obj_type(sym_id, obj_type)
            else:
                raise Exception("???")

    def get_object_symbol_type(self, sym_id, scope):
        if scope == "GLOBAL" or (sym_id not in self.FUNCS[scope]["FUNCS"][self.current_scope][2].SYMBOLS and sym_id not in self.FUNCS[scope]["SYMBOLS"].SYMBOLS):
            if self.current_scope != None and scope == "GLOBAL":
                return self.FUNCS[scope][self.current_scope][2].get_object_symbol_type(sym_id)
            else:
                return self.FUNCS[self.program_name].get_object_symbol_type(sym_id)
        else:
            if self.current_scope != None:
                try:
                    return self.FUNCS[scope]["FUNCS"][self.current_scope][2].get_object_symbol_type(sym_id)
                except:
                    return self.FUNCS[scope]["SYMBOLS"].get_object_symbol_type(sym_id)
            else:
                raise Exception("???")

    def declare_object_type(self, object_type):
        if object_type in self.FUNCS:
            raise Exception("Name Error: object type " + object_type + " is already defined")
        if object_type in self.FUNCS[self.program_name].SYMBOLS:
            raise Exception("Name Error: " + object_type + " is already defined as a symbol in " + self.program_name)

        self.FUNCS[object_type]= {"SYMBOLS" : SymbolTable(object_type, self.mem_constraints, FunctionDirectory.VAR_TYPES, self.program_name), "FUNCS" : {}}

    def is_sym_ptr(self, sym_id, scope):
        if self.current_scope == None:
            if scope == "GLOBAL":
                return self.FUNCS[self.program_name].is_sym_ptr(sym_id)
            else:
                is_ptr = self.FUNCS[scope]["SYMBOLS"].is_sym_ptr(sym_id)
                if is_ptr == -1:
                    return self.FUNCS[self.program_name].is_sym_ptr(sym_id)
                return is_ptr
        else:
            if scope == "GLOBAL":
                is_ptr = -1
                if self.current_scope in self.FUNCS[scope]:
                    is_ptr = self.FUNCS[scope][self.current_scope][2].is_sym_ptr(sym_id)
                if is_ptr == -1:
                    return self.FUNCS[self.program_name].is_sym_ptr(sym_id)
                return is_ptr
            else:
                is_ptr = self.FUNCS[scope]["FUNCS"][self.current_scope][2].is_sym_ptr(sym_id)
                if is_ptr == -1:
                    is_ptr = self.FUNCS[scope]["SYMBOLS"].is_sym_ptr(sym_id)
                    if is_ptr == -1:
                        return self.FUNCS[self.program_name].is_sym_ptr(sym_id)
                return is_ptr

    def is_sym_arr(self, sym_id, scope):
        if self.current_scope == None:
            if scope == "GLOBAL":
                return self.FUNCS[self.program_name].is_sym_arr(sym_id)
            else:
                is_arr = self.FUNCS[scope]["SYMBOLS"].is_sym_arr(sym_id)
                if is_arr == -1:
                    return self.FUNCS[self.program_name].is_sym_arr(sym_id)
                return is_arr
        else:
            if scope == "GLOBAL":
                is_arr = -1
                if self.current_scope in self.FUNCS[scope]:
                    is_arr = self.FUNCS[scope][self.current_scope][2].is_sym_arr(sym_id)
                if is_arr == -1:
                    return self.FUNCS[self.program_name].is_sym_arr(sym_id)
                return is_arr
            else:
                is_arr = self.FUNCS[scope]["FUNCS"][self.current_scope][2].is_sym_arr(sym_id)
                if is_arr == -1:
                    is_arr = self.FUNCS[scope]["SYMBOLS"].is_sym_arr(sym_id)
                    if is_arr == -1:
                        return self.FUNCS[self.program_name].is_sym_arr(sym_id)
                return is_arr

    def get_symbol_dimensions(self, sym_id, scope, is_class_attr = False):
        if scope == "GLOBAL":
            if self.current_scope == None:
                return self.FUNCS[self.program_name].get_dimensions(sym_id)
            else:
                dimensions = self.FUNCS[scope][self.current_scope][2].get_dimensions(sym_id)
                if dimensions == -1:
                    return self.FUNCS[self.program_name].get_dimensions(sym_id)
                return dimensions
        else:
            if self.current_scope == None or is_class_attr:
                dimensions = self.FUNCS[scope]["SYMBOLS"].get_dimensions(sym_id)
                if dimensions == -1 and not is_class_attr:
                    return self.FUNCS[self.program_name].get_dimensions(sym_id)
                return dimensions
            else:
                dimensions = self.FUNCS[scope]["FUNCS"][self.current_scope][2].get_dimensions(sym_id)
                if dimensions == -1:
                    return self.FUNCS[self.program_name].get_dimensions(sym_id)
                return dimensionss

    def get_param_mem_index(self, func_id, k, scope):
        if scope == "GLOBAL":
            if func_id in self.FUNCS[scope]:
                return self.FUNCS[scope][func_id][1].param_indices[k - 1]
        else:
            if func_id in self.FUNCS[scope]["FUNCS"]:
                return self.FUNCS[scope]["FUNCS"][func_id][1].param_indices[k - 1]

        raise Exception("Unseen function: " + func_id + " in " + scope)

    def declare_constant(self, cnst_id, cnst_type):
        self.declare_symbol(cnst_id, cnst_type, "GLOBAL", is_cnst = True)

    def get_symbol_mem_index(self, sym_id, scope, is_class_attr = False):
        if self.current_scope == None and scope == "GLOBAL":
            return self.FUNCS[self.program_name].get_mem_index(sym_id)
        else:
            mem_index = -1
            if scope == "GLOBAL":
                if self.current_scope in self.FUNCS[scope]:
                    mem_index = self.FUNCS[scope][self.current_scope][2].get_mem_index(sym_id)
            else:
                mem_index = -1
                if self.current_scope != None and not is_class_attr:
                    mem_index = self.FUNCS[scope]["FUNCS"][self.current_scope][2].get_mem_index(sym_id)
                if mem_index == -1 and is_class_attr:
                    mem_index = self.FUNCS[scope]["SYMBOLS"].get_mem_index(sym_id)
            if mem_index == -1 and not is_class_attr:
                return self.FUNCS[self.program_name].get_mem_index(sym_id)

            return mem_index

    def next_avail(self, type, scope, is_ptr = False):
        if type == "void": # Nope?
            return
        t_id = self.AVAIL.next()
        if self.current_scope == None:
            self.FUNCS[self.program_name].next_avail(t_id, type, "1" + str(FunctionDirectory.MEMORY_SECTOR_INDICES.index(type)) + "1", is_ptr)
        else:
            if scope == "GLOBAL":
                self.FUNCS[scope][self.current_scope][2].next_avail(t_id, type, "2" + str(FunctionDirectory.MEMORY_SECTOR_INDICES.index(type)) + "1", is_ptr)
            else:
                self.FUNCS[scope]["FUNCS"][self.current_scope][2].next_avail(t_id, type, "2" + str(FunctionDirectory.MEMORY_SECTOR_INDICES.index(type)) + "1", is_ptr)
        return t_id

    def get_return_obj_name(self, func_name =  None):
        if func_name == None:
            if self.current_scope == None:
                raise Exception("Scope error: cannot get function return object name for " + func_name)
            func_name = self.current_scope

        if func_name not in self.FUNCS[self.program_name].SYMBOLS:
            raise  Exception("Name error: cannot get function return object name for " + func_name  + " in " + scope)

        return func_name

    def valid_return_check(self, ptr, scope):
        if self.current_scope == None:
            raise Exception("Scope error: cant check for valid return")

        if scope == "GLOBAL":
            return self.FUNCS[scope][self.current_scope][5] == ptr
        else:
            return self.FUNCS[scope]["FUNCS"][self.current_scope][5] == ptr

    def return_type_check(self, rtn_type, ptr, scope):
        if self.current_scope == None:
            raise Exception("Scope error: cant check return type")

        func_type = None

        if scope == "GLOBAL":
            if self.current_scope in self.FUNCS[scope]:
                func_type = self.FUNCS[scope][self.current_scope][0]
        else:
            func_type = self.FUNCS[scope]["FUNCS"][self.current_scope][0]

        if func_type == None:
            raise Exception("Cannot check return type for rtn_addr " + str(ptr))

        if SemanticCube[rtn_type]["=="][func_type] == "err":
            raise Exception("Type mismatch: function " + self.current_scope + " expects " + func_type + ", got " + rtn_type + " instead. Maybe missing default return statement?")

        if scope == "GLOBAL":
            self.FUNCS[scope][self.current_scope][5] = ptr
        else:
            self.FUNCS[scope]["FUNCS"][self.current_scope][5] = ptr

    def args_ok(self, func_id, scope):
        if scope == "GLOBAL":
            if func_id in self.FUNCS[scope]:
                k = self.FUNCS[scope][func_id][4]
                if len(self.FUNCS[scope][func_id][1].SYMBOLS) != k:
                    raise Exception("Argument mismatch: Call to " + func_id + " received " + str(k) + " parameters, expects " + str(len(self.FUNCS[scope][func_id][1].SYMBOLS)))
                return
        else:
            if func_id in self.FUNCS[scope]["FUNCS"]:
                k = self.FUNCS[scope]["FUNCS"][func_id][4]
                if len(self.FUNCS[scope]["FUNCS"][func_id][1].SYMBOLS) != k:
                    raise Exception("Argument mismatch: Call to " + func_id + " received " + str(k) + " parameters, expects " + str(len(self.FUNCS[scope]["FUNCS"][func_id][1].SYMBOLS)))

                return

        raise Exception("Unseen function: " + func_id + " in " + scope)


    def verify_arg_type(self, func_id, arg_type, scope):
        if scope == "GLOBAL":
            if func_id in self.FUNCS[scope]:
                k = self.FUNCS[scope][func_id][4]
                types_list = self.FUNCS[scope][func_id][1].get_types_list()

                if not len(types_list): # NO PARAM FUNC
                    self.FUNCS[scope][func_id][4] = -1
                    raise Exception("Argument mismatch: " + func_id + " expects no parameters, got at least 1")
            else:
                raise Exception("Unseen function: " + func_id + " in " + scope)
        else:
            if func_id in self.FUNCS[scope]["FUNCS"]:
                k = self.FUNCS[scope]["FUNCS"][func_id][4]
                types_list = self.FUNCS[scope]["FUNCS"][func_id][1].get_types_list()

                if not len(types_list): # NO PARAM FUNC
                    self.FUNCS[scope]["FUNCS"][func_id][4] = -1
                    raise Exception("Argument mismatch: " + func_id + " expects no parameters, got at least 1")
            else:
                raise Exception("Unseen function: " + func_id + " in " + scope)


        if k >= len(types_list): # TOO MANY PARAMS
            raise Exception("Argument mismatch: Call to " + func_id + " received " + str(k + 1) + " or more parameters, expects " + str(len(types_list)))

        if arg_type != types_list[k]:
            raise Exception("Type mismatch: Call to " + func_id + " received " + arg_type + " argument, expects " + types_list[k])

        self.goto_next_param(func_id, scope)
        return k + 1

    def set_param_index(self, func_id, index, scope):
        if scope == "GLOBAL":
            if func_id in self.FUNCS[scope]:
                self.FUNCS[scope][func_id][4] = index
                return
        else:
            if func_id in self.FUNCS[scope]["FUNCS"]:
                self.FUNCS[scope]["FUNCS"][func_id][4] = index
                return

        raise Exception("Unseen function: " + func_id + " in " + scope)


    def goto_next_param(self, func_id, scope):
        if scope == "GLOBAL":
            if func_id in self.FUNCS[scope]:
                if not len(self.FUNCS[scope][func_id][1].SYMBOLS): # NO PARAM FUNC
                    self.FUNCS[scope][func_id][4] = -1
                    return

                self.FUNCS[scope][func_id][4] += 1
                return
        else:
            if func_id in self.FUNCS[scope]["FUNCS"]:
                if not len(self.FUNCS[scope]["FUNCS"][func_id][1].SYMBOLS): # NO PARAM FUNC
                    self.FUNCS[scope]["FUNCS"][func_id][4] = -1
                    return

                self.FUNCS[scope]["FUNCS"][func_id][4] += 1
                return

        raise Exception("Unseen function: " + func_id + " in " + scope)

    def set_main_start_addr(self, addr):
        self.main_start_addr = addr

    def get_main_start_addr(self):
        return self.main_start_addr

    def set_start_addr(self, addr, scope):
        if self.current_scope != None:
            if scope == "GLOBAL":
                self.FUNCS[scope][self.current_scope][3] = addr # INDEX 3 IS START_ADDR
            else:
                self.FUNCS[scope]["FUNCS"][self.current_scope][3] = addr # INDEX 3 IS START_ADDR
        else:
            raise Exception("Scope Error: Cant declare func start addr")

    def get_start_addr(self, func_id, scope):
        if scope == "GLOBAL":
            if func_id in self.FUNCS[scope]:
                return self.FUNCS[scope][func_id][3] # INDEX 3 IS START_ADDR
        else:
            if func_id in self.FUNCS[scope]["FUNCS"]:
                return self.FUNCS[scope]["FUNCS"][func_id][3] # INDEX 3 IS START_ADDR

        raise Exception("Scope Error: Cant get " + func_id + " start addr in " + scope)

    def declare_symbol(self, sym_id, sym_type, scope, is_return_value = False, is_param = False, is_cnst = False, give_warning = True, is_array = False, dimensions = None):
        if sym_type == "void": # Trying to declare a space for the return value of a void function... useless!
            return

        if sym_type == "object":
            if is_param:
                raise Exception("Type Error: cannot declare function parameters of 'object' type")
            if scope != "GLOBAL" and self.current_scope == None:
                raise Exception("Type Error: cannot declare nested objects ('object' type class atrributes)")

        if sym_id in self.FUNCS[scope]:
            raise Exception("Attribute error: symbol " + sym_id + " is already declared as a function within " + scope)

        # Here we decide where in memory to place this symbol
        memory_sector_signature = list(str(FunctionDirectory.MEMORY_SECTOR_INDICES.index(sym_type)) + "0")

        if is_cnst:
            memory_sector_signature.insert(0, "0") # Global Constant
        elif self.current_scope != None and scope == "GLOBAL":
            memory_sector_signature.insert(0, "2") # Local Variable
            if sym_id in self.FUNCS[self.program_name].SYMBOLS and give_warning:
                print("WARNING: Definition of "  + sym_id + " in " + self.current_scope + " shadows previous global definition.")
            sym_table_index = 2
            if is_param:
                sym_table_index = 1
            self.FUNCS[scope][self.current_scope][sym_table_index].declare_symbol(sym_id, sym_type, "".join(memory_sector_signature), is_return_value, False, is_cnst, is_param, is_array, dimensions)
            return
        elif self.current_scope != None and scope != "GLOBAL":
            memory_sector_signature.insert(0, "2") # Local Variable
            if sym_id in self.FUNCS[self.program_name].SYMBOLS and give_warning:
                print("WARNING: Definition of "  + sym_id + " in " + self.current_scope + " shadows previous global definition.")
            sym_table_index = 2
            if is_param:
                sym_table_index = 1
            self.FUNCS[scope]["FUNCS"][self.current_scope][sym_table_index].declare_symbol(sym_id, sym_type, "".join(memory_sector_signature), is_return_value, False, is_cnst, is_param, is_array, dimensions)
            return
        elif scope != "GLOBAL" and not is_return_value:
            memory_sector_signature.insert(0, "3") # Class Attribute
            self.FUNCS[scope]["SYMBOLS"].declare_symbol(sym_id, sym_type, "".join(memory_sector_signature), is_return_value, False, is_cnst, is_param, is_array, dimensions)
            return
        else:
            memory_sector_signature.insert(0, "1") # Global Variable

        self.FUNCS[self.program_name].declare_symbol(sym_id, sym_type, "".join(memory_sector_signature), is_return_value, False, is_cnst, is_param, is_array, dimensions)


    def declare_param(self, param_id, param_type, scope):
        if self.current_scope == None:
            raise Exception("Scope Error: Cant declare param")

        self.declare_symbol(param_id, param_type, scope, is_param = True)
        self.declare_symbol(param_id, param_type, scope, give_warning = False)

    def define_symbol(self, sym_id, sym_dir):
        if self.current_scope != None:
            self.FUNCS[scope][self.current_scope][2].define_symbol(sym_id, sym_dir)
        else:
            self.FUNCS[self.program_name].define_symbol(sym_id,  sym_dir)

    def declare_function(self, func_id, func_type, scope):
        if func_type == "object":
            raise Exception("Type Error: cannot declare function of 'object' return type")
        if scope == "PROGRAM":
            self.program_name = func_id
            self.FUNCS[self.program_name] = SymbolTable(func_id, self.mem_constraints, FunctionDirectory.VAR_TYPES, self.program_name)
        elif func_id not in self.FUNCS[scope]:
            self.declare_symbol(func_id, func_type, scope, is_return_value = True) # Third argument as true sets this simbol to a return value; This is used as storage for the return value of the function with the same ID
            if scope == "GLOBAL":
                self.FUNCS[scope][func_id] = [func_type, SymbolTable(func_id + "_param", self.mem_constraints, FunctionDirectory.VAR_TYPES, self.program_name), SymbolTable(func_id, self.mem_constraints, FunctionDirectory.VAR_TYPES, self.program_name), None, 0, False] # TYPE, ARG_TABLE, VAR_TABLE, START_ADDR, PARAM_POINTER, HAS_VALID_RTN
            else:
                self.FUNCS[scope]["FUNCS"][func_id] = [func_type, SymbolTable(func_id + "_param", self.mem_constraints, FunctionDirectory.VAR_TYPES, self.program_name), SymbolTable(func_id, self.mem_constraints, FunctionDirectory.VAR_TYPES, self.program_name), None, 0, False] # TYPE, ARG_TABLE, VAR_TABLE, START_ADDR, PARAM_POINTER, HAS_VALID_RTN
            self.change_current_scope(func_id)
        else:
            raise Exception("Multiple Declarations of " + func_id + " in " + scope)

    def change_current_scope(self, new_scope):
        for key in self.FUNCS:
            if key == self.program_name:
                self.FUNCS[key].reset_object_symbol_types()
            elif key == "GLOBAL":
                for func in self.FUNCS[key]:
                    self.FUNCS[key][func][2].reset_object_symbol_types()
            else:
                for func in self.FUNCS[key]["FUNCS"]:
                    self.FUNCS[key]["FUNCS"][func][2].reset_object_symbol_types()

                self.FUNCS[key]["SYMBOLS"].reset_object_symbol_types()

        self.current_scope = new_scope

    def symbol_lookup(self, sym_id, scope, is_class_attr = False):
        if scope == "GLOBAL":
            if self.current_scope != None:
                try:
                    return self.FUNCS[scope][self.current_scope][2].symbol_lookup(sym_id)
                except:
                    pass
        else:
            try:
                if self.current_scope != None:
                    try:
                        if not is_class_attr:
                            return self.FUNCS[scope]["FUNCS"][self.current_scope][2].symbol_lookup(sym_id)
                    except:
                        pass
                if is_class_attr:
                    return self.FUNCS[scope]["SYMBOLS"].symbol_lookup(sym_id)
                else:
                    pass
            except:
                if is_class_attr:
                    raise Exception("Name Error: Class " + scope + " has no attribute " + sym_id)
                else:
                    try:
                        return self.FUNCS[scope]["FUNCS"][self.current_scope][1].symbol_lookup(sym_id)
                    except:
                        return self.FUNCS[self.program_name].symbol_lookup(sym_id)

        return self.FUNCS[self.program_name].symbol_lookup(sym_id)


    def symbol_type_lookup(self, sym_id, scope, is_class_attr = False):
        if scope == "GLOBAL":
            if self.current_scope != None:
                try:
                    return self.FUNCS[scope][self.current_scope][2].type_lookup(sym_id)
                except:
                    pass
        else:
            try:
                if self.current_scope != None and not is_class_attr:
                    try:
                        return self.FUNCS[scope]["FUNCS"][self.current_scope][2].type_lookup(sym_id)
                    except:
                        pass
                else:
                    return self.FUNCS[scope]["SYMBOLS"].type_lookup(sym_id)
            except:
                if is_class_attr:
                    raise Exception("Name Error: Class " + scope + " has no attribute " + sym_id)
                return self.FUNCS[self.program_name].type_lookup(sym_id)

        return self.FUNCS[self.program_name].type_lookup(sym_id)


    def func_type_lookup(self, func_id, scope):
        if scope == "GLOBAL":
            if func_id in self.FUNCS[scope]:
                return self.FUNCS[scope][func_id][0]
        else:
            if func_id in self.FUNCS[scope]["FUNCS"]:
                return self.FUNCS[scope]["FUNCS"][func_id][0]

        raise Exception("Unseen function: " + func_id + " in " + scope)
