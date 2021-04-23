class FunctionDirectory(object):
    """docstring for FunctionDirectory."""

    def __init__(self):
        self.SYMBOLS = {"GLOBAL" : {}}

    def declare_function(self, func_id, func_type, scope = "GLOBAL"):
        if func_id not in self.SYMBOLS[scope]:
            self.SYMBOLS[scope][func_id] = (func_type, None)
        else:
            raise Exception("Multiple Declarations of " + func_id + " in " + scope)
