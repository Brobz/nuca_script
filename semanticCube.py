SemanticCube = {}

SemanticCube["int"] = {
                        "==" :  {"int" : "boolean", "float" : "boolean", "boolean" : "boolean"} ,
                        ">" :  {"int" : "boolean", "float" : "boolean", "boolean" : "boolean"} ,
                        "<" :  {"int" : "boolean", "float" : "boolean", "boolean" : "boolean"} ,
                        ">=" :  {"int" : "boolean", "float" : "boolean", "boolean" : "boolean"} ,
                        "<=" :  {"int" : "boolean", "float" : "boolean", "boolean" : "boolean"} ,
                        "&&" :  {"int" : "boolean", "float" : "boolean", "boolean" : "boolean"} ,
                        "||" :  {"int" : "boolean", "float" : "boolean", "boolean" : "boolean"} ,
                        "!=" :  {"int" : "boolean", "float" : "boolean", "boolean" : "boolean"} ,
                        "*" :  {"int" : "int", "float" : "float"} ,
                        "/" :  {"int" : "int", "float" : "float"} ,
                        "+" :  {"int" : "int", "float" : "float"} ,
                        "-" :  {"int" : "int", "float" : "float"}
                    }

SemanticCube["float"] = {
                        "==" : {"int" : "boolean", "float" : "boolean"},
                        ">" : {"int" : "boolean", "float" : "boolean"},
                        "<" : {"int" : "boolean", "float" : "boolean"},
                        "<=" : {"int" : "boolean", "float" : "boolean"},
                        ">=" : {"int" : "boolean", "float" : "boolean"},
                        "!=" : {"int" : "boolean", "float" : "boolean"} ,
                        "*" : {"int" : "float", "float" : "float"},
                        "/" : {"int" : "float", "float" : "float"},
                        "+" : {"int" : "float", "float" : "float"},
                         "-" : {"int" : "float", "float" : "float"}
                        }


SemanticCube["str"] = {
                        "==" : {"str" : "boolean"},
                        ">" : {"str" : "boolean"},
                        "<" : {"str" : "boolean"},
                        ">=" : {"str" : "boolean"},
                        "<=" : {"str" : "boolean"},
                        "&&": {"str" : "boolean"},
                        "||" : {"str" : "boolean"},
                        "!=" : {"str" : "boolean"}
                        }

SemanticCube["boolean"] = {
                        "==" : {"int" : "boolean", "boolean" : "boolean"},
                        ">" : {"int" : "boolean", "boolean" : "boolean"},
                        "<" : {"int" : "boolean", "boolean" : "boolean"},
                        ">=" : {"int" : "boolean", "boolean" : "boolean"},
                        "<=" : {"int" : "boolean", "boolean" : "boolean"},

                        "&&" : {"int" : "boolean", "boolean" : "boolean"},
                        "||" : {"int" : "boolean", "boolean" : "boolean"},
                        "!=" : {"int" : "boolean", "boolean" : "boolean"}
                        }
