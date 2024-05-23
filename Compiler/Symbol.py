class Symbol(object):
    """ 

    Basic data structure that stands at the bottom of the NucaScript compiler.

    Symbol objects contain the needed information for building the memory structure of each NucaScript program
    once it's compiled. They are instantiated, stored and manipulated by SymbolTable instances.

    """

    def __init__(self, sym_id, sym_data_type, sym_mem_index, is_return_value, is_constant, is_array, dimensions, is_pointer, object_type, arr_pointed_to):
        self.id = sym_id
        # ------------------------------------------------------ #
        self.data_type = sym_data_type                  # 0
        self.mem_index = sym_mem_index                  # 1
        self.is_return_value = is_return_value          # 2
        self.is_constant = is_constant                  # 3
        self.is_array = is_array                        # 4
        self.dimensions = dimensions                    # 5
        self.is_pointer = is_pointer                    # 6
        self.object_type = object_type                  # 7
        self.array_pointed_to = arr_pointed_to          # 8