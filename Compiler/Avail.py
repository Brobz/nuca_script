class Avail(object):
    """ Object that handles temporal variable assignment """

    def __init__(self):
        self.current = -1


    def next(self):
        self.current += 1
        # Strange temporal name is so that no possible ID could preventa a temporal from being generated
        # (IDs cannot start with a number)
        return "93t" + str(self.current)

    def reset_counter(self):
        self.current = -1
