SemanticCube = {}

SemanticCube["int"] = {
                        "==" :  {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "boolean", "void" : "err"} ,
                        ">" :  {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "boolean", "void" : "err"} ,
                        "<" :  {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "boolean", "void" : "err"} ,
                        ">=" :  {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "boolean", "void" : "err"} ,
                        "<=" :  {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "boolean", "void" : "err"} ,
                        "&&" :  {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "boolean", "void" : "err"} ,
                        "||" :  {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "boolean", "void" : "err"} ,
                        "!=" :  {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "boolean", "void" : "err"} ,
                        "*" :  {"int" : "int", "float" : "float", "str" : "str", "boolean" : "int", "void" : "err"} ,
                        "/" :  {"int" : "int", "float" : "float", "str" : "err", "boolean" : "err", "void" : "err"} ,
                        "+" :  {"int" : "int", "float" : "float", "str" : "err", "boolean" : "int", "void" : "err"} ,
                        "-" :  {"int" : "int", "float" : "float", "str" : "err", "boolean" : "int", "void" : "err"}
                    }

SemanticCube["float"] = {
                        "==" : {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "err", "void" : "err"},
                        ">" : {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "err", "void" : "err"},
                        "<" : {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "err", "void" : "err"},
                        ">=" : {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "err", "void" : "err"},
                        "<=" : {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "err", "void" : "err"},
                        "&&" :  {"int" : "err", "float" : "err", "str" : "err", "boolean" : "err", "void" : "err"} ,
                        "||" :  {"int" : "err", "float" : "err", "str" : "err", "boolean" : "err", "void" : "err"} ,
                        "!=" : {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "err", "void" : "err"} ,
                        "*" : {"int" : "float", "float" : "float", "str" : "err", "boolean" : "float", "void" : "err"},
                        "/" : {"int" : "float", "float" : "float", "str" : "err", "boolean" : "err", "void" : "err"},
                        "+" : {"int" : "float", "float" : "float", "str" : "err", "boolean" : "err", "void" : "err"},
                         "-" : {"int" : "float", "float" : "float", "str" : "err", "boolean" : "err", "void" : "err"}
                        }


SemanticCube["str"] = {
                        "==" : {"int" : "err", "float" : "err", "str" : "boolean", "boolean" : "err", "void" : "err"},
                        ">" : {"int" : "err", "float" : "err", "str" : "boolean", "boolean" : "err", "void" : "err"},
                        "<" : {"int" : "err", "float" : "err", "str" : "boolean", "boolean" : "err", "void" : "err"},
                        ">=" : {"int" : "err", "float" : "err", "str" : "boolean", "boolean" : "err", "void" : "err"},
                        "<=" : {"int" : "err", "float" : "err", "str" : "boolean", "boolean" : "err", "void" : "err"},
                        "&&": {"int" : "err", "float" : "err", "str" : "boolean", "boolean" : "err", "void" : "err"},
                        "||" : {"int" : "err", "float" : "err", "str" : "boolean", "boolean" : "err", "void" : "err"},
                        "!=" : {"int" : "err", "float" : "err", "str" : "boolean", "boolean" : "err", "void" : "err"},
                        "*" : {"int" : "str", "float" : "err", "str" : "err", "boolean" : "str", "void" : "err"},
                        "/" : {"int" : "err", "float" : "err", "str" : "err", "boolean" : "err", "void" : "err"},
                        "+" : {"int" : "err", "float" : "err", "str" : "str",  "boolean" : "err", "void" : "err"},
                         "-" : {"int" : "err", "float" : "err", "str" : "err",  "boolean" : "err", "void" : "err"}
                        }

SemanticCube["boolean"] = {
                        "==" : {"int" : "boolean", "float" : "err", "str" : "err", "boolean" : "boolean", "void" : "err"},
                        ">" : {"int" : "boolean", "float" : "err", "str" : "err", "boolean" : "boolean", "void" : "err"},
                        "<" : {"int" : "boolean", "float" : "err", "str" : "err", "boolean" : "boolean", "void" : "err"},
                        ">=" : {"int" : "boolean", "float" : "err", "str" : "err", "boolean" : "boolean", "void" : "err"},
                        "<=" : {"int" : "boolean", "float" : "err", "str" : "err", "boolean" : "boolean", "void" : "err"},
                        "&&" : {"int" : "boolean", "float" : "err", "str" : "err", "boolean" : "boolean", "void" : "err"},
                        "||" : {"int" : "boolean", "float" : "err", "str" : "err", "boolean" : "boolean", "void" : "err"},
                        "!=" : {"int" : "boolean", "float" : "err", "str" : "err", "boolean" : "boolean", "void" : "err"},
                        "*" : {"int" : "int", "float" : "float", "str" : "str", "boolean" : "err", "void" : "err"},
                        "/" : {"int" : "err", "float" : "err", "str" : "err", "boolean" : "err", "void" : "err"},
                        "+" : {"int" : "int", "float" : "err", "str" : "err",  "boolean" : "err", "void" : "err"},
                         "-" : {"int" : "int", "float" : "err", "str" : "err",  "boolean" : "err", "void" : "err"}
                        }

SemanticCube["void"] = {
                        "==" : {"int" : "err", "float" : "err", "str" : "err", "boolean" : "err", "void" : "boolean"},
                        ">" : {"int" : "err", "float" : "err", "str" : "err", "boolean" : "err", "void" : "err"},
                        "<" : {"int" : "err", "float" : "err", "str" : "err", "boolean" : "err", "void" : "err"},
                        ">=" : {"int" : "err", "float" : "err", "str" : "err", "boolean" : "err", "void" : "err"},
                        "<=" : {"int" : "err", "float" : "err", "str" : "err", "boolean" : "err", "void" : "err"},
                        "&&" : {"int" : "err", "float" : "err", "str" : "err", "boolean" : "err", "void" : "err"},
                        "||" : {"int" : "err", "float" : "err", "str" : "err", "boolean" : "err", "void" : "err"},
                        "!=" : {"int" : "err", "float" : "err", "str" : "err", "boolean" : "err", "void" : "err"},
                        "*" : {"int" : "err", "float" : "err", "str" : "str", "boolean" : "err", "void" : "err"},
                        "/" : {"int" : "err", "float" : "err", "str" : "err", "boolean" : "err", "void" : "err"},
                        "+" : {"int" : "err", "float" : "err", "str" : "err",  "boolean" : "err", "void" : "err"},
                         "-" : {"int" : "err", "float" : "err", "str" : "err",  "boolean" : "err", "void" : "err"}
                        }

SemanticCube["!"] = {
                        "int" : "boolean",
                        "float" : "err",
                        "str" : "boolean",
                        "boolean" : "boolean"
                        }
