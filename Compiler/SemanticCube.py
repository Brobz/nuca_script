SemanticCube = {}

SemanticCube["int"] = {
                        "=" :  {"int" : "int", "float" : "err", "string" : "err", "boolean" : "int", "void" : "err"} ,
                        "==" :  {"int" : "boolean", "float" : "err", "string" : "err", "boolean" : "boolean", "void" : "err"} ,
                        ">" :  {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "boolean", "void" : "err"} ,
                        "<" :  {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "boolean", "void" : "err"} ,
                        ">=" :  {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "boolean", "void" : "err"} ,
                        "<=" :  {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "boolean", "void" : "err"} ,
                        "&&" :  {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "boolean", "void" : "err"} ,
                        "||" :  {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "boolean", "void" : "err"} ,
                        "!=" :  {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "boolean", "void" : "err"} ,
                        "*" :  {"int" : "int", "float" : "float", "string" : "string", "boolean" : "int", "void" : "err"} ,
                        "/" :  {"int" : "int", "float" : "float", "string" : "err", "boolean" : "err", "void" : "err"} ,
                        "+" :  {"int" : "int", "float" : "float", "string" : "err", "boolean" : "int", "void" : "err"} ,
                        "-" :  {"int" : "int", "float" : "float", "string" : "err", "boolean" : "int", "void" : "err"}
                    }

SemanticCube["float"] = {

                        "=" :  {"int" : "float", "float" : "float", "string" : "err", "boolean" : "err", "void" : "err"} ,
                        "==" : {"int" : "err", "float" : "boolean", "string" : "err", "boolean" : "err", "void" : "err"},
                        ">" : {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "err", "void" : "err"},
                        "<" : {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "err", "void" : "err"},
                        ">=" : {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "err", "void" : "err"},
                        "<=" : {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "err", "void" : "err"},
                        "&&" :  {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err"} ,
                        "||" :  {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err"} ,
                        "!=" : {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "err", "void" : "err"} ,
                        "*" : {"int" : "float", "float" : "float", "string" : "err", "boolean" : "float", "void" : "err"},
                        "/" : {"int" : "float", "float" : "float", "string" : "err", "boolean" : "err", "void" : "err"},
                        "+" : {"int" : "float", "float" : "float", "string" : "err", "boolean" : "err", "void" : "err"},
                         "-" : {"int" : "float", "float" : "float", "string" : "err", "boolean" : "err", "void" : "err"}
                        }


SemanticCube["string"] = {

                        "=" :  {"int" : "err", "float" : "err", "string" : "string", "boolean" : "err", "void" : "err"} ,
                        "==" : {"int" : "err", "float" : "err", "string" : "boolean", "boolean" : "err", "void" : "err"},
                        ">" : {"int" : "err", "float" : "err", "string" : "boolean", "boolean" : "err", "void" : "err"},
                        "<" : {"int" : "err", "float" : "err", "string" : "boolean", "boolean" : "err", "void" : "err"},
                        ">=" : {"int" : "err", "float" : "err", "string" : "boolean", "boolean" : "err", "void" : "err"},
                        "<=" : {"int" : "err", "float" : "err", "string" : "boolean", "boolean" : "err", "void" : "err"},
                        "&&": {"int" : "err", "float" : "err", "string" : "boolean", "boolean" : "err", "void" : "err"},
                        "||" : {"int" : "err", "float" : "err", "string" : "boolean", "boolean" : "err", "void" : "err"},
                        "!=" : {"int" : "err", "float" : "err", "string" : "boolean", "boolean" : "err", "void" : "err"},
                        "*" : {"int" : "string", "float" : "err", "string" : "err", "boolean" : "string", "void" : "err"},
                        "/" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err"},
                        "+" : {"int" : "err", "float" : "err", "string" : "string",  "boolean" : "err", "void" : "err"},
                         "-" : {"int" : "err", "float" : "err", "string" : "err",  "boolean" : "err", "void" : "err"}
                        }

SemanticCube["boolean"] = {

                        "=" :  {"int" : "boolean", "float" : "err", "string" : "err", "boolean" : "boolean", "void" : "err"} ,
                        "==" : {"int" : "boolean", "float" : "err", "string" : "err", "boolean" : "boolean", "void" : "err"},
                        ">" : {"int" : "boolean", "float" : "err", "string" : "err", "boolean" : "boolean", "void" : "err"},
                        "<" : {"int" : "boolean", "float" : "err", "string" : "err", "boolean" : "boolean", "void" : "err"},
                        ">=" : {"int" : "boolean", "float" : "err", "string" : "err", "boolean" : "boolean", "void" : "err"},
                        "<=" : {"int" : "boolean", "float" : "err", "string" : "err", "boolean" : "boolean", "void" : "err"},
                        "&&" : {"int" : "boolean", "float" : "err", "string" : "err", "boolean" : "boolean", "void" : "err"},
                        "||" : {"int" : "boolean", "float" : "err", "string" : "err", "boolean" : "boolean", "void" : "err"},
                        "!=" : {"int" : "boolean", "float" : "err", "string" : "err", "boolean" : "boolean", "void" : "err"},
                        "*" : {"int" : "int", "float" : "float", "string" : "string", "boolean" : "err", "void" : "err"},
                        "/" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err"},
                        "+" : {"int" : "int", "float" : "err", "string" : "err",  "boolean" : "err", "void" : "err"},
                         "-" : {"int" : "int", "float" : "err", "string" : "err",  "boolean" : "err", "void" : "err"}
                        }

SemanticCube["void"] = {
                        "=" :  {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err"} ,
                        "==" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "boolean"},
                        ">" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err"},
                        "<" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err"},
                        ">=" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err"},
                        "<=" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err"},
                        "&&" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err"},
                        "||" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err"},
                        "!=" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err"},
                        "*" : {"int" : "err", "float" : "err", "string" : "string", "boolean" : "err", "void" : "err"},
                        "/" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err"},
                        "+" : {"int" : "err", "float" : "err", "string" : "err",  "boolean" : "err", "void" : "err"},
                         "-" : {"int" : "err", "float" : "err", "string" : "err",  "boolean" : "err", "void" : "err"}
                        }

SemanticCube["!"] = {
                        "int" : "boolean",
                        "float" : "err",
                        "string" : "boolean",
                        "boolean" : "boolean"
                        }
