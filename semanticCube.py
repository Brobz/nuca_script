semanticCube = {}

semanticCube = { "int" : {"==" :  {"int" : "bool", "float" : "bool", "bool" : "bool"} } }
semanticCube = { "int" : {">" :  {"int" : "bool", "float" : "bool", "bool" : "bool"} } }
semanticCube = { "int" : {"<" :  {"int" : "bool", "float" : "bool", "bool" : "bool"} } }
semanticCube = { "int" : {">=" :  {"int" : "bool", "float" : "bool", "bool" : "bool"} } }
semanticCube = { "int" : {"<=" :  {"int" : "bool", "float" : "bool", "bool" : "bool"} } }
semanticCube = { "int" : {"&&" :  {"int" : "bool", "float" : "bool", "bool" : "bool"} } }
semanticCube = { "int" : {"||" :  {"int" : "bool", "float" : "bool", "bool" : "bool"} } }
semanticCube = { "int" : {"!=" :  {"int" : "bool", "float" : "bool", "bool" : "bool"} } }

semanticCube = { "int" : {"*" :  {"int" : "int", "float" : "float"} } }
semanticCube = { "int" : {"/" :  {"int" : "int", "float" : "float"} } }
semanticCube = { "int" : {"+" :  {"int" : "int", "float" : "float"} } }
semanticCube = { "int" : {"-" :  {"int" : "int", "float" : "float"} } }

semanticCube = { "float" : {"==" : {"int" : "bool", "float" : "bool"} } }
semanticCube = { "float" : {">" : {"int" : "bool", "float" : "bool"} } }
semanticCube = { "float" : {"<" : {"int" : "bool", "float" : "bool"} } }
semanticCube = { "float" : {"<=" : {"int" : "bool", "float" : "bool"} } }
semanticCube = { "float" : {">=" : {"int" : "bool", "float" : "bool"} } }

semanticCube = { "float" : {"!=" : {"int" : "bool", "float" : "bool"} } }

semanticCube = { "float" : {"*" : {"int" : "float", "float" : "float"} } }
semanticCube = { "float" : {"/" : {"int" : "float", "float" : "float"} } }
semanticCube = { "float" : {"+" : {"int" : "float", "float" : "float"} } }
semanticCube = { "float" : {"-" : {"int" : "float", "float" : "float"} } }

semanticCube = { "str" : {"==" : {"str" : "bool"}, ">" : {"str" : "bool"}, "<" : {"str" : "bool"}, ">=" : {"str" : "bool"}, "<=" : {"str" : "bool"}, "&&": {"str" : "bool"}, "||" : {"str" : "bool"}, "!=" : {"str" : "bool"} } }

semanticCube = { "bool" : {"==" : {"int" : "bool", "bool" : "bool"} } }
semanticCube = { "bool" : {">" : {"int" : "bool", "bool" : "bool"} } }
semanticCube = { "bool" : {"<" : {"int" : "bool", "bool" : "bool"} } }
semanticCube = { "bool" : {">=" : {"int" : "bool", "bool" : "bool"} } }
semanticCube = { "bool" : {"<=" : {"int" : "bool", "bool" : "bool"} } }

semanticCube = { "bool" : {"&&" : {"int" : "bool", "bool" : "bool"} } }
semanticCube = { "bool" : {"||" : {"int" : "bool", "bool" : "bool"} } }
semanticCube = { "bool" : {"!=" : {"int" : "bool", "bool" : "bool"} } }


