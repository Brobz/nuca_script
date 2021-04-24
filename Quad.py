class Quad(object):
    """docstring for Quad."""

    def __init__(self, op, left_operand, right_operand, res):
        self.operator = op
        self.left_operand = left_operand
        self.right_operand = right_operand
        self.result = res

    def get_string(self):
        return self.operator + " " + self.left_operand + " "  + self.right_operand + " " + self.result
