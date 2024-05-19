from .Quad import Quad

class Globals():    
    _QUAD_POINTER = 1
    _QUADS = [Quad("GOTO", -1, -1, "PND")]

    @property
    def QUAD_POINTER(self):
        return self._QUAD_POINTER

    @QUAD_POINTER.setter
    def QUAD_POINTER(self, new_quad_pointer):
        self._QUAD_POINTER = new_quad_pointer
    

    @property
    def QUADS(self):
        return self._QUADS

    @QUADS.setter
    def QUADS(self, new_quads):
        self._QUADS = new_quads

