class Avail(object):
    """docstring for Avail."""

    def __init__(self):
        self.current = -1


    def next(self):
        self.current += 1
        return "t" + str(self.current)
