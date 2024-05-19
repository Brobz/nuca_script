from .OPCodes import OPCodes

class Quad(object):
    """ Mostly quads, anyway... """

    def __init__(self, op, arg_one, arg_2, arg_3, arg_4 = None, arg_5 = None):
        self.operator = OPCodes[op]
        self.arg_one = arg_one
        self.arg_2 = arg_2
        self.arg_3 = arg_3
        self.arg_4 = arg_4
        self.arg_5 = arg_5

    def get_string(self):
        return str(self.operator) + " " + str(self.arg_one) + " "  + str(self.arg_2) + " " + str(self.arg_3)

    def get_cpp_string(self):
        if self.arg_4 == None:
            return '{' + str(self.operator) + ', ' + str(self.arg_one) + ', '  + str(self.arg_2) + ', ' + str(self.arg_3) + '},'
        elif self.arg_5 == None:
            return '{' + str(self.operator) + ', ' + str(self.arg_one) + ', '  + str(self.arg_2) + ', ' + str(self.arg_3) + ', ' + str(self.arg_4) + '},'
        else:
            return '{' + str(self.operator) + ', ' + str(self.arg_one) + ', '  + str(self.arg_2) + ', ' + str(self.arg_3) + ', ' + str(self.arg_4) + ', ' + str(self.arg_5) +  '},'
