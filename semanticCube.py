SemanticCube = {}

SemanticCube["int"] = {
                        "==" :  {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "boolean"} ,
                        ">" :  {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "boolean"} ,
                        "<" :  {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "boolean"} ,
                        ">=" :  {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "boolean"} ,
                        "<=" :  {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "boolean"} ,
                        "&&" :  {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "boolean"} ,
                        "||" :  {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "boolean"} ,
                        "!=" :  {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "boolean"} ,
                        "*" :  {"int" : "int", "float" : "float", "str" : "str", "boolean" : "int"} ,
                        "/" :  {"int" : "int", "float" : "float", "str" : "err", "boolean" : "err"} ,
                        "+" :  {"int" : "int", "float" : "float", "str" : "err", "boolean" : "int"} ,
                        "-" :  {"int" : "int", "float" : "float", "str" : "err", "boolean" : "int"}
                    }

SemanticCube["float"] = {
                        "==" : {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "err"},
                        ">" : {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "err"},
                        "<" : {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "err"},
                        ">=" : {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "err"},
                        "<=" : {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "err"},
                        "&&" :  {"int" : "err", "float" : "err", "str" : "err", "boolean" : "err"} ,
                        "||" :  {"int" : "err", "float" : "err", "str" : "err", "boolean" : "err"} ,
                        "!=" : {"int" : "boolean", "float" : "boolean", "str" : "err", "boolean" : "err"} ,
                        "*" : {"int" : "float", "float" : "float", "str" : "err", "boolean" : "float"},
                        "/" : {"int" : "float", "float" : "float", "str" : "err", "boolean" : "err"},
                        "+" : {"int" : "float", "float" : "float", "str" : "err", "boolean" : "err"},
                         "-" : {"int" : "float", "float" : "float", "str" : "err", "boolean" : "err"}
                        }


SemanticCube["str"] = {
                        "==" : {"int" : "err", "float" : "err", "str" : "boolean", "boolean" : "err"},
                        ">" : {"int" : "err", "float" : "err", "str" : "boolean", "boolean" : "err"},
                        "<" : {"int" : "err", "float" : "err", "str" : "boolean", "boolean" : "err"},
                        ">=" : {"int" : "err", "float" : "err", "str" : "boolean", "boolean" : "err"},
                        "<=" : {"int" : "err", "float" : "err", "str" : "boolean", "boolean" : "err"},
                        "&&": {"int" : "err", "float" : "err", "str" : "boolean", "boolean" : "err"},
                        "||" : {"int" : "err", "float" : "err", "str" : "boolean", "boolean" : "err"},
                        "!=" : {"int" : "err", "float" : "err", "str" : "boolean", "boolean" : "err"},
                        "*" : {"int" : "str", "float" : "err", "str" : "err", "boolean" : "str"},
                        "/" : {"int" : "err", "float" : "err", "str" : "err", "boolean" : "err"},
                        "+" : {"int" : "err", "float" : "err", "str" : "str",  "boolean" : "err"},
                         "-" : {"int" : "err", "float" : "err", "str" : "err",  "boolean" : "err"}
                        }

SemanticCube["boolean"] = {
                        "==" : {"int" : "boolean", "float" : "err", "str" : "err", "boolean" : "boolean"},
                        ">" : {"int" : "boolean", "float" : "err", "str" : "err", "boolean" : "boolean"},
                        "<" : {"int" : "boolean", "float" : "err", "str" : "err", "boolean" : "boolean"},
                        ">=" : {"int" : "boolean", "float" : "err", "str" : "err", "boolean" : "boolean"},
                        "<=" : {"int" : "boolean", "float" : "err", "str" : "err", "boolean" : "boolean"},
                        "&&" : {"int" : "boolean", "float" : "err", "str" : "err", "boolean" : "boolean"},
                        "||" : {"int" : "boolean", "float" : "err", "str" : "err", "boolean" : "boolean"},
                        "!=" : {"int" : "boolean", "float" : "err", "str" : "err", "boolean" : "boolean"},
                        "*" : {"int" : "int", "float" : "float", "str" : "str", "boolean" : "err"},
                        "/" : {"int" : "err", "float" : "err", "str" : "err", "boolean" : "err"},
                        "+" : {"int" : "int", "float" : "err", "str" : "err",  "boolean" : "err"},
                         "-" : {"int" : "int", "float" : "err", "str" : "err",  "boolean" : "err"}
                        }
