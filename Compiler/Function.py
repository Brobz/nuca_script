from .SymbolTable import SymbolTable


class Function(object):
    """ 

    Basic data structure that holds information about a specific function scope in a NucaScript program.
    This data is stored and manipulated via internal SymbolTable instances.

    Function objects contain the needed information for validating and building the memory structure
    of each defined function during compilation time, including the main method.
    
    They are instantiated, stored and manipulated by an all-ecompassing FunctionDirectory instance.

    """

    # The abstract value below is initialized and set via the Bootsrapper file
    # This ensures no messy circular dependencies and a cleaner import order
    VAR_TYPES = None

    def __init__(self, func_id, func_data_type, mem_constraints, program_name, start_adrr = None, param_pointer = 0, has_valid_return = False):
        self.id = func_id
        # ---------------------------------------------------------------------------------------------------------------------- #
        self.data_type = func_data_type                                                                                 # 0                    
        self.arg_table = SymbolTable(func_id + "_param", mem_constraints, Function.VAR_TYPES, program_name)             # 1
        self.var_table = SymbolTable(func_id, mem_constraints, Function.VAR_TYPES, program_name)                        # 2
        self.start_addr = start_adrr                                                                                    # 3
        self.param_pointer = param_pointer                                                                              # 4
        self.has_valid_return = has_valid_return                                                                        # 5