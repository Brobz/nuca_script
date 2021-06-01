class Avail(object):
    """ Object that handles temporal variable assignment """

    def __init__(self):
        self.current = -1


    def next(self):
        self.current += 1
        return "t" + str(self.current)

    def reset_counter(self):
        self.current = -1
