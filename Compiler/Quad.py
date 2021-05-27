from Compiler.OPCodes import *

class Quad(object):
    """docstring for Quad."""

    def __init__(self, op, left_operand, right_operand, res, extra_value_0 = None, extra_value_1 = None):
        self.operator = OPCodes[op]
        self.left_operand = left_operand
        self.right_operand = right_operand
        self.result = res
        self.extra_value_0 = extra_value_0
        self.extra_value_1 = extra_value_1

    def get_string(self):
        return str(self.operator) + " " + str(self.left_operand) + " "  + str(self.right_operand) + " " + str(self.result)

    def get_cpp_string(self):
        if self.extra_value_0 == None:
            return '{' + str(self.operator) + ', ' + str(self.left_operand) + ', '  + str(self.right_operand) + ', ' + str(self.result) + '},'
        elif self.extra_value_1 == None:
            return '{' + str(self.operator) + ', ' + str(self.left_operand) + ', '  + str(self.right_operand) + ', ' + str(self.result) + ', ' + str(self.extra_value_0) + '},'
        else:
            return '{' + str(self.operator) + ', ' + str(self.left_operand) + ', '  + str(self.right_operand) + ', ' + str(self.result) + ', ' + str(self.extra_value_0) + ', ' + str(self.extra_value_1) +  '},'
