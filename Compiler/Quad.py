from Compiler.OPCodes import *

class Quad(object):
    """docstring for Quad."""

    def __init__(self, op, left_operand, right_operand, res, extra_value = None):
        self.operator = OPCodes[op]
        self.left_operand = left_operand
        self.right_operand = right_operand
        self.result = res
        self.extra_value = extra_value

    def get_string(self):
        return str(self.operator) + " " + str(self.left_operand) + " "  + str(self.right_operand) + " " + str(self.result)

    def get_cpp_string(self):
        if self.extra_value == None:
            return '{' + str(self.operator) + ', ' + str(self.left_operand) + ', '  + str(self.right_operand) + ', ' + str(self.result) + '},'
        else:
            return '{' + str(self.operator) + ', ' + str(self.left_operand) + ', '  + str(self.right_operand) + ', ' + str(self.result) + ', ' + str(self.extra_value) + '},'
