class Quad(object):
    """docstring for Quad."""

    def __init__(self, op, left_operand, right_operand, res):
        self.operator = op
        self.left_operand = left_operand
        self.right_operand = right_operand
        self.result = res

    def get_string(self):
        return str(self.operator) + " " + str(self.left_operand) + " "  + str(self.right_operand) + " " + str(self.result)
