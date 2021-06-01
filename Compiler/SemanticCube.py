## Contais all of the typematching information needed for NucaScript ##
SemanticCube = {}

SemanticCube["int"] = {
                        "=" :  {"int" : "int", "float" : "err", "string" : "err", "boolean" : "int", "void" : "err", "object" : "err"} ,
                        "==" :  {"int" : "boolean", "float" : "err", "string" : "err", "boolean" : "boolean", "void" : "err", "object" : "err"} ,
                        ">" :  {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "boolean", "void" : "err", "object" : "err"} ,
                        "<" :  {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "boolean", "void" : "err", "object" : "err"} ,
                        ">=" :  {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "boolean", "void" : "err", "object" : "err"} ,
                        "<=" :  {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "boolean", "void" : "err", "object" : "err"} ,
                        "&&" :  {"int" : "boolean", "float" : "boolean", "string" : "boolean", "boolean" : "boolean", "void" : "err", "object" : "err"} ,
                        "||" :  {"int" : "boolean", "float" : "boolean", "string" : "boolean", "boolean" : "boolean", "void" : "err", "object" : "err"} ,
                        "!=" :  {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "boolean", "void" : "err", "object" : "err"} ,
                        "*" :  {"int" : "int", "float" : "float", "string" : "string", "boolean" : "int", "void" : "err", "object" : "err"} ,
                        "/" :  {"int" : "int", "float" : "float", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"} ,
                        "+" :  {"int" : "int", "float" : "float", "string" : "string", "boolean" : "err", "void" : "err", "object" : "err"} ,
                        "-" :  {"int" : "int", "float" : "float", "string" : "err", "boolean" : "int", "void" : "err", "object" : "err"}
                    }

SemanticCube["float"] = {

                        "=" :  {"int" : "float", "float" : "float", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"} ,
                        "==" : {"int" : "err", "float" : "boolean", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        ">" : {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        "<" : {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        ">=" : {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        "<=" : {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        "&&" : {"int" : "boolean", "float" : "boolean", "string" : "boolean", "boolean" : "boolean", "void" : "err", "object" : "err"} ,
                        "||" : {"int" : "boolean", "float" : "boolean", "string" : "boolean", "boolean" : "boolean", "void" : "err", "object" : "err"} ,
                        "!=" : {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"} ,
                        "*" : {"int" : "float", "float" : "float", "string" : "err", "boolean" : "float", "void" : "err", "object" : "err"},
                        "/" : {"int" : "float", "float" : "float", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        "+" : {"int" : "float", "float" : "float", "string" : "string", "boolean" : "err", "void" : "err", "object" : "err"},
                         "-" : {"int" : "float", "float" : "float", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"}
                        }


SemanticCube["string"] = {

                        "=" :  {"int" : "err", "float" : "err", "string" : "string", "boolean" : "err", "void" : "err", "object" : "err"} ,
                        "==" : {"int" : "err", "float" : "err", "string" : "boolean", "boolean" : "err", "void" : "err", "object" : "err"},
                        ">" : {"int" : "err", "float" : "err", "string" : "boolean", "boolean" : "err", "void" : "err", "object" : "err"},
                        "<" : {"int" : "err", "float" : "err", "string" : "boolean", "boolean" : "err", "void" : "err", "object" : "err"},
                        ">=" : {"int" : "err", "float" : "err", "string" : "boolean", "boolean" : "err", "void" : "err", "object" : "err"},
                        "<=" : {"int" : "err", "float" : "err", "string" : "boolean", "boolean" : "err", "void" : "err", "object" : "err"},
                        "&&": {"int" : "boolean", "float" : "boolean", "string" : "boolean", "boolean" : "boolean", "void" : "err", "object" : "err"},
                        "||" : {"int" : "boolean", "float" : "boolean", "string" : "boolean", "boolean" : "boolean", "void" : "err", "object" : "err"},
                        "!=" : {"int" : "err", "float" : "err", "string" : "boolean", "boolean" : "err", "void" : "err", "object" : "err"},
                        "*" : {"int" : "string", "float" : "err", "string" : "err", "boolean" : "string", "void" : "err", "object" : "err"},
                        "/" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        "+" : {"int" : "string", "float" : "string", "string" : "string",  "boolean" : "string", "void" : "err", "object" : "err"},
                         "-" : {"int" : "err", "float" : "err", "string" : "err",  "boolean" : "err", "void" : "err", "object" : "err"}
                        }

SemanticCube["boolean"] = {

                        "=" :  {"int" : "boolean", "float" : "err", "string" : "err", "boolean" : "boolean", "void" : "err", "object" : "err"} ,
                        "==" : {"int" : "boolean", "float" : "err", "string" : "err", "boolean" : "boolean", "void" : "err", "object" : "err"},
                        ">" : {"int" : "boolean", "float" : "err", "string" : "err", "boolean" : "boolean", "void" : "err", "object" : "err"},
                        "<" : {"int" : "boolean", "float" : "err", "string" : "err", "boolean" : "boolean", "void" : "err", "object" : "err"},
                        ">=" : {"int" : "boolean", "float" : "err", "string" : "err", "boolean" : "boolean", "void" : "err", "object" : "err"},
                        "<=" : {"int" : "boolean", "float" : "err", "string" : "err", "boolean" : "boolean", "void" : "err", "object" : "err"},
                        "&&" : {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "boolean", "void" : "err", "object" : "err"},
                        "||" : {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "boolean", "void" : "err", "object" : "err"},
                        "!=" : {"int" : "boolean", "float" : "boolean", "string" : "err", "boolean" : "boolean", "void" : "err", "object" : "err"},
                        "*" : {"int" : "int", "float" : "float", "string" : "string", "boolean" : "err", "void" : "err", "object" : "err"},
                        "/" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        "+" : {"int" : "int", "float" : "err", "string" : "string",  "boolean" : "err", "void" : "err", "object" : "err"},
                         "-" : {"int" : "int", "float" : "err", "string" : "err",  "boolean" : "err", "void" : "err", "object" : "err"}
                        }


SemanticCube["object"] = {
                        "=" :  {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "object"} ,
                        "==" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        ">" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        "<" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        ">=" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        "<=" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        "&&" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        "||" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        "!=" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        "*" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        "/" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        "+" : {"int" : "err", "float" : "err", "string" : "err",  "boolean" : "err", "void" : "err", "object" : "err"},
                         "-" : {"int" : "err", "float" : "err", "string" : "err",  "boolean" : "err", "void" : "err", "object" : "err"}
                        }


SemanticCube["void"] = {
                        "=" :  {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"} ,
                        "==" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "boolean", "object" : "err"},
                        ">" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        "<" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        ">=" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        "<=" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        "&&" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        "||" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        "!=" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        "*" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        "/" : {"int" : "err", "float" : "err", "string" : "err", "boolean" : "err", "void" : "err", "object" : "err"},
                        "+" : {"int" : "err", "float" : "err", "string" : "err",  "boolean" : "err", "void" : "err", "object" : "err"},
                         "-" : {"int" : "err", "float" : "err", "string" : "err",  "boolean" : "err", "void" : "err", "object" : "err"}
                        }

# Unary Minus
SemanticCube["-"] = {
                        "int" : "int",
                        "float" : "float",
                        "string" : "string",
                        "boolean" : "err",
                        "object" : "err"
                    }

# Unary Negtaion
SemanticCube["!"] = {
                        "int" : "boolean",
                        "float" : "err",
                        "string" : "boolean",
                        "boolean" : "boolean",
                        "object" : "err"
                    }
