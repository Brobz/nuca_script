
# parsetab.py
# This file is automatically generated. Do not edit.
# pylint: disable=W,C,R
_tabversion = '3.10'

_lr_method = 'LALR'

_lr_signature = 'AND ATTR_KWD BIGGER CLASS_KWD CLOSE_CURLY CLOSE_PARENTHESIS COLON COMMA CTE_F CTE_I CTE_S DERIVES_KWD DIFFERENT DOUBLE_EQUALS ELSE_KWD EQUALS FOR_KWD FWD_SLASH ID IF_KWD MAIN_KWD MINUS NOT OPEN_CURLY OPEN_PARENTHESIS OR PLUS PROGRAM_KWD READ_KWD RETURN_KWD SEMI_COLON SMALLER STAR TYPE VARS_KWD WHILE_KWD WRITE_KWD PROGRAM : PROGRAM_KWD ID seen_program_id SEMI_COLON CLASS_STAR GLOBAL_VAR FUNC_DEF_STAR MAIN_KWD OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_CURLY seen_main_kwd STATEMENT_STAR CLOSE_CURLY  seen_program_id : empty  seen_main_kwd : empty  CLASS_STAR : CLASS CLASS_STAR\n                   | empty  CLASS : CLASS_KWD ID SMALLER DERIVES_KWD TYPE BIGGER OPEN_CURLY CLASS_ATTR FUNC_DEF_STAR CLOSE_CURLY  CLASS_ATTR : ATTR_KWD OPEN_CURLY VAR_LIST_STAR CLOSE_CURLY  VAR_LIST_STAR : VAR_LIST VAR_LIST_STAR\n                      | empty  VAR_LIST : ID_LIST COLON TYPE SEMI_COLON  ID_LIST : ID ID_LIST_P  ID_LIST_P : COMMA ID ID_LIST_P\n                  | empty  READABLE_LIST : ID seen_readable READABLE_LIST_P  READABLE_LIST_P : COMMA ID seen_readable READABLE_LIST_P\n                  | empty  seen_readable  : empty  GLOBAL_VAR : VAR_LIST_STAR  FUNC_DEF_STAR : FUNC_DEF FUNC_DEF_STAR\n                      | empty  FUNC_DEF : TYPE ID seen_func_id OPEN_PARENTHESIS FUNC_PARAM CLOSE_PARENTHESIS seen_func_params VARS seen_func_vars OPEN_CURLY FUNC_STATEMENT_STAR CLOSE_CURLY  seen_func_id : empty  seen_func_params : empty  seen_func_vars : empty  FUNC_PARAM : VAR FUNC_PARAM_P\n                   | empty  FUNC_PARAM_P : COMMA VAR FUNC_PARAM_P\n                     | empty  VAR : ID COLON TYPE  VARS : VARS_KWD OPEN_CURLY VAR_LIST_STAR CLOSE_CURLY  FUNC_STATEMENT_STAR :       STATEMENT FUNC_STATEMENT_STAR\n                                |   FUNC_RETURN FUNC_STATEMENT_STAR\n                                |   empty  STATEMENT_STAR :  STATEMENT STATEMENT_STAR\n                       | empty  STATEMENT : ASSIGN SEMI_COLON\n                  | FUNC_CALL SEMI_COLON\n                  | READ SEMI_COLON\n                  | WRITE SEMI_COLON\n                  | DECISION\n                  | REPETITION  FOR_INCR_STATEMENT :    ASSIGN\n                              | FUNC_CALL\n                              | READ\n                              | WRITE  ASSIGN : ID seen_id EQUALS seen_equals EXPRESSION  seen_equals  : empty  EXP :   TERM seen_term EXP_P\n              | NOT seen_not EXP pop_not seen_term :   EXP_P : PLUS seen_term_op TERM seen_term EXP_P\n            | MINUS seen_term_op TERM seen_term EXP_P\n            | empty  seen_term_op :   EXPRESSION :   EXP\n                     | EXP COMP seen_comp_op EXPRESSION seen_comp  seen_comp : empty  seen_comp_op : empty  COMP : BIGGER\n             | SMALLER\n             | DOUBLE_EQUALS\n             | DIFFERENT\n             | AND\n             | OR  FACTOR :  OPEN_PARENTHESIS seen_open_parenthesis EXPRESSION CLOSE_PARENTHESIS seen_close_parenthesis\n                | NOT seen_not FACTOR pop_not\n                | FUNC_CALL\n                | ID seen_id\n                | CNST  pop_not : empty  seen_not : empty  seen_open_parenthesis : empty  seen_close_parenthesis : empty  seen_id :   seen_cte_i :   seen_cte_f :   seen_cte_s :   CNST : CTE_S seen_cte_s\n             | CTE_F seen_cte_f\n             | CTE_I seen_cte_i  TERM : FACTOR seen_factor TERM_P   TERM_P :    STAR seen_factor_op FACTOR seen_factor TERM_P\n                 |  FWD_SLASH seen_factor_op FACTOR seen_factor TERM_P\n                 |  empty  seen_factor :   seen_factor_op :   FUNC_CALL : ID OPEN_PARENTHESIS ARG_LIST CLOSE_PARENTHESIS  ARG_LIST : ID_LIST ARG_LIST_P\n                 | EXPRESSION ARG_LIST_P\n                 | empty  ARG_LIST_P : COMMA ID_LIST ARG_LIST_P\n                   | COMMA EXPRESSION ARG_LIST_P\n                   | empty  FUNC_RETURN : RETURN_KWD EXPRESSION SEMI_COLON  READ : READ_KWD OPEN_PARENTHESIS READABLE_LIST CLOSE_PARENTHESIS  WRITE : WRITE_KWD OPEN_PARENTHESIS PRINTABLE CLOSE_PARENTHESIS  PRINTABLE : EXPRESSION seen_printable PRINTABLE_P  PRINTABLE_P : COMMA EXPRESSION seen_printable PRINTABLE_P\n                    | empty  seen_printable  : empty  DECISION : IF_KWD OPEN_PARENTHESIS EXPRESSION CLOSE_PARENTHESIS seen_if_kwd OPEN_CURLY STATEMENT_STAR CLOSE_CURLY DECISION_P  DECISION_P : ELSE_KWD seen_else_kwd OPEN_CURLY STATEMENT_STAR CLOSE_CURLY\n                   | empty  seen_if_kwd : empty  seen_else_kwd : empty  REPETITION : CONDITIONAL_REP\n                   | UNCONDITIONAL_REP  CONDITIONAL_REP : WHILE_KWD seen_while_kwd OPEN_PARENTHESIS EXPRESSION CLOSE_PARENTHESIS seen_while_exp OPEN_CURLY STATEMENT_STAR CLOSE_CURLY  seen_while_kwd : empty  seen_while_exp : empty  UNCONDITIONAL_REP : FOR_KWD OPEN_PARENTHESIS ID seen_for_kwd EQUALS EXPRESSION seen_for_start_exp SEMI_COLON EXPRESSION seen_for_end_exp SEMI_COLON FOR_INCR_STATEMENT seen_for_incr_exp CLOSE_PARENTHESIS OPEN_CURLY STATEMENT_STAR CLOSE_CURLY  seen_for_kwd : empty  seen_for_incr_exp : empty seen_for_start_exp : empty  seen_for_end_exp : empty empty :'
    
_lr_action_items = {'PROGRAM_KWD':([0,],[2,]),'$end':([1,84,],[0,-1,]),'ID':([2,6,7,8,9,10,14,17,20,25,39,42,44,50,51,55,61,67,68,72,73,81,83,86,87,88,89,90,91,92,95,99,101,103,110,123,127,129,130,132,133,136,139,140,141,142,143,144,145,147,148,163,169,170,172,173,178,179,182,185,190,192,193,195,201,202,206,207,210,223,230,233,235,241,243,249,251,252,258,259,266,270,272,],[3,-116,11,-116,-5,18,11,-4,29,32,-10,45,-116,59,-3,45,59,-40,-41,-106,-107,11,102,-36,-37,-38,-39,118,121,121,124,-6,-116,-116,-116,121,11,121,-47,121,-72,102,-116,-59,-60,-61,-62,-63,-64,121,-71,59,121,-58,-54,-54,-86,-86,208,121,121,59,59,121,121,121,121,121,59,-116,59,-94,121,-116,121,-101,-103,-108,59,59,-102,59,-111,]),'SEMI_COLON':([3,4,5,33,63,64,65,66,108,109,111,112,113,114,115,116,121,131,134,146,149,150,151,152,153,156,165,171,174,175,176,177,180,197,200,203,204,205,213,217,218,219,220,221,222,224,225,226,231,232,234,236,237,238,244,245,246,247,248,253,256,257,],[-116,6,-2,39,86,87,88,89,-55,-50,-85,-67,-69,-77,-76,-75,-74,-68,-87,-116,-116,-78,-79,-80,-95,-96,-46,-48,-53,-116,-85,-81,-84,-116,-116,-49,-70,-66,-116,233,-65,-73,-56,-57,-50,-50,-85,-85,243,-114,-116,-116,-116,-116,-51,-116,-52,-82,-83,-116,259,-115,]),'CLASS_KWD':([6,8,99,],[10,10,-6,]),'TYPE':([6,7,8,9,12,13,14,15,17,23,26,27,34,39,52,57,99,128,214,],[-116,-116,-116,-5,25,-18,-116,-9,-4,25,-8,33,40,-10,76,25,-6,-7,-21,]),'MAIN_KWD':([6,7,8,9,12,13,14,15,17,22,23,24,26,31,39,99,214,],[-116,-116,-116,-5,-116,-18,-116,-9,-4,30,-116,-20,-8,-19,-10,-6,-21,]),'COMMA':([11,19,21,29,35,47,76,79,102,105,106,108,109,111,112,113,114,115,116,118,120,121,131,134,146,149,150,151,152,154,155,157,158,167,168,171,174,175,176,177,180,197,200,203,204,205,208,209,218,219,220,221,222,224,225,226,227,228,234,236,237,238,244,245,246,247,248,],[20,-11,-13,20,-12,55,-29,55,20,136,136,-55,-50,-85,-67,-69,-77,-76,-75,-116,-116,-74,-68,-87,-116,-116,-78,-79,-80,182,-17,185,-100,136,136,-48,-53,-116,-85,-81,-84,-116,-116,-49,-70,-66,-116,-116,-65,-73,-56,-57,-50,-50,-85,-85,182,185,-116,-116,-116,-116,-51,-116,-52,-82,-83,]),'COLON':([11,16,19,21,29,35,45,],[-116,27,-11,-13,-116,-12,52,]),'CLOSE_CURLY':([14,15,23,24,26,31,39,44,50,51,57,60,61,62,67,68,72,73,80,81,85,86,87,88,89,100,127,128,163,164,191,192,193,194,210,214,215,216,229,230,233,241,242,249,251,252,258,260,266,270,271,272,],[-116,-9,-116,-20,-8,-19,-10,-116,-116,-3,-116,84,-116,-35,-40,-41,-106,-107,99,-116,-34,-36,-37,-38,-39,128,-116,-7,-116,196,214,-116,-116,-33,-116,-21,-31,-32,241,-116,-94,-116,252,-101,-103,-108,-116,266,-102,-116,272,-111,]),'SMALLER':([18,102,108,109,111,112,113,114,115,116,121,131,134,146,149,150,151,152,171,174,175,176,177,180,197,203,204,205,218,219,222,224,225,226,234,236,237,238,244,245,246,247,248,],[28,-74,141,-50,-85,-67,-69,-77,-76,-75,-74,-68,-87,-116,-116,-78,-79,-80,-48,-53,-116,-85,-81,-84,-116,-49,-70,-66,-65,-73,-50,-50,-85,-85,-116,-116,-116,-116,-51,-116,-52,-82,-83,]),'CLOSE_PARENTHESIS':([19,21,29,35,36,42,46,47,48,54,56,76,79,83,98,102,104,105,106,107,108,109,111,112,113,114,115,116,117,118,119,120,121,122,131,134,135,137,138,146,149,150,151,152,153,154,155,156,157,158,160,165,166,167,168,171,174,175,176,177,180,181,183,184,186,197,198,199,200,203,204,205,208,209,218,219,220,221,222,224,225,226,227,228,234,236,237,238,239,240,244,245,246,247,248,261,262,263,264,265,267,268,],[-11,-13,-116,-12,41,-116,53,-116,-26,-25,-28,-29,-116,-116,-27,-74,134,-116,-116,-90,-55,-50,-85,-67,-69,-77,-76,-75,153,-116,156,-116,-74,159,-68,-87,-88,-93,-89,-116,-116,-78,-79,-80,-95,-116,-17,-96,-116,-100,189,-46,197,-116,-116,-48,-53,-116,-85,-81,-84,-14,-16,-97,-99,-116,-91,-92,-116,-49,-70,-66,-116,-116,-65,-73,-56,-57,-50,-50,-85,-85,-116,-116,-116,-116,-116,-116,-15,-98,-51,-116,-52,-82,-83,-116,-42,-43,-44,-45,269,-113,]),'DERIVES_KWD':([28,],[34,]),'OPEN_PARENTHESIS':([30,32,37,38,59,69,70,71,74,75,83,91,92,93,94,101,102,103,110,121,123,129,130,132,133,136,139,140,141,142,143,144,145,147,148,169,170,172,173,178,179,185,190,195,201,202,206,207,223,235,243,],[36,-116,42,-22,83,90,91,92,-116,95,103,103,103,123,-109,-116,83,-116,-116,83,103,103,-47,103,-72,103,-116,-59,-60,-61,-62,-63,-64,103,-71,103,-58,-54,-54,-86,-86,103,103,103,103,103,103,103,-116,103,103,]),'BIGGER':([40,102,108,109,111,112,113,114,115,116,121,131,134,146,149,150,151,152,171,174,175,176,177,180,197,203,204,205,218,219,222,224,225,226,234,236,237,238,244,245,246,247,248,],[43,-74,140,-50,-85,-67,-69,-77,-76,-75,-74,-68,-87,-116,-116,-78,-79,-80,-48,-53,-116,-85,-81,-84,-116,-49,-70,-66,-65,-73,-50,-50,-85,-85,-116,-116,-116,-116,-51,-116,-52,-82,-83,]),'OPEN_CURLY':([41,43,58,96,97,125,126,159,187,188,189,196,211,212,250,254,255,269,],[44,49,81,-116,127,163,-24,-116,210,-104,-116,-30,230,-110,-116,258,-105,270,]),'READ_KWD':([44,50,51,61,67,68,72,73,86,87,88,89,163,192,193,210,230,233,241,249,251,252,258,259,266,270,272,],[-116,69,-3,69,-40,-41,-106,-107,-36,-37,-38,-39,69,69,69,69,69,-94,-116,-101,-103,-108,69,69,-102,69,-111,]),'WRITE_KWD':([44,50,51,61,67,68,72,73,86,87,88,89,163,192,193,210,230,233,241,249,251,252,258,259,266,270,272,],[-116,70,-3,70,-40,-41,-106,-107,-36,-37,-38,-39,70,70,70,70,70,-94,-116,-101,-103,-108,70,70,-102,70,-111,]),'IF_KWD':([44,50,51,61,67,68,72,73,86,87,88,89,163,192,193,210,230,233,241,249,251,252,258,266,270,272,],[-116,71,-3,71,-40,-41,-106,-107,-36,-37,-38,-39,71,71,71,71,71,-94,-116,-101,-103,-108,71,-102,71,-111,]),'WHILE_KWD':([44,50,51,61,67,68,72,73,86,87,88,89,163,192,193,210,230,233,241,249,251,252,258,266,270,272,],[-116,74,-3,74,-40,-41,-106,-107,-36,-37,-38,-39,74,74,74,74,74,-94,-116,-101,-103,-108,74,-102,74,-111,]),'FOR_KWD':([44,50,51,61,67,68,72,73,86,87,88,89,163,192,193,210,230,233,241,249,251,252,258,266,270,272,],[-116,75,-3,75,-40,-41,-106,-107,-36,-37,-38,-39,75,75,75,75,75,-94,-116,-101,-103,-108,75,-102,75,-111,]),'ATTR_KWD':([49,],[58,]),'VARS_KWD':([53,77,78,],[-116,97,-23,]),'EQUALS':([59,82,124,161,162,],[-74,101,-116,190,-112,]),'RETURN_KWD':([67,68,72,73,86,87,88,89,163,192,193,233,241,249,251,252,266,272,],[-40,-41,-106,-107,-36,-37,-38,-39,195,195,195,-94,-116,-101,-103,-108,-102,-111,]),'NOT':([83,91,92,101,103,110,123,129,130,132,133,136,139,140,141,142,143,144,145,147,148,169,170,172,173,178,179,185,190,195,201,202,206,207,223,235,243,],[110,110,110,-116,-116,-116,110,110,-47,110,-72,110,-116,-59,-60,-61,-62,-63,-64,110,-71,110,-58,-54,-54,-86,-86,110,110,110,223,223,223,223,-116,223,110,]),'CTE_S':([83,91,92,101,103,110,123,129,130,132,133,136,139,140,141,142,143,144,145,147,148,169,170,172,173,178,179,185,190,195,201,202,206,207,223,235,243,],[114,114,114,-116,-116,-116,114,114,-47,114,-72,114,-116,-59,-60,-61,-62,-63,-64,114,-71,114,-58,-54,-54,-86,-86,114,114,114,114,114,114,114,-116,114,114,]),'CTE_F':([83,91,92,101,103,110,123,129,130,132,133,136,139,140,141,142,143,144,145,147,148,169,170,172,173,178,179,185,190,195,201,202,206,207,223,235,243,],[115,115,115,-116,-116,-116,115,115,-47,115,-72,115,-116,-59,-60,-61,-62,-63,-64,115,-71,115,-58,-54,-54,-86,-86,115,115,115,115,115,115,115,-116,115,115,]),'CTE_I':([83,91,92,101,103,110,123,129,130,132,133,136,139,140,141,142,143,144,145,147,148,169,170,172,173,178,179,185,190,195,201,202,206,207,223,235,243,],[116,116,116,-116,-116,-116,116,116,-47,116,-72,116,-116,-59,-60,-61,-62,-63,-64,116,-71,116,-58,-54,-54,-86,-86,116,116,116,116,116,116,116,-116,116,116,]),'STAR':([102,111,112,113,114,115,116,121,131,134,149,150,151,152,176,197,204,205,218,219,225,226,237,238,245,],[-74,-85,-67,-69,-77,-76,-75,-74,-68,-87,178,-78,-79,-80,-85,-116,-70,-66,-65,-73,-85,-85,178,178,-116,]),'FWD_SLASH':([102,111,112,113,114,115,116,121,131,134,149,150,151,152,176,197,204,205,218,219,225,226,237,238,245,],[-74,-85,-67,-69,-77,-76,-75,-74,-68,-87,179,-78,-79,-80,-85,-116,-70,-66,-65,-73,-85,-85,179,179,-116,]),'PLUS':([102,109,111,112,113,114,115,116,121,131,134,146,149,150,151,152,176,177,180,197,204,205,218,219,222,224,225,226,234,236,237,238,245,247,248,],[-74,-50,-85,-67,-69,-77,-76,-75,-74,-68,-87,172,-116,-78,-79,-80,-85,-81,-84,-116,-70,-66,-65,-73,-50,-50,-85,-85,172,172,-116,-116,-116,-82,-83,]),'MINUS':([102,109,111,112,113,114,115,116,121,131,134,146,149,150,151,152,176,177,180,197,204,205,218,219,222,224,225,226,234,236,237,238,245,247,248,],[-74,-50,-85,-67,-69,-77,-76,-75,-74,-68,-87,173,-116,-78,-79,-80,-85,-81,-84,-116,-70,-66,-65,-73,-50,-50,-85,-85,173,173,-116,-116,-116,-82,-83,]),'DOUBLE_EQUALS':([102,108,109,111,112,113,114,115,116,121,131,134,146,149,150,151,152,171,174,175,176,177,180,197,203,204,205,218,219,222,224,225,226,234,236,237,238,244,245,246,247,248,],[-74,142,-50,-85,-67,-69,-77,-76,-75,-74,-68,-87,-116,-116,-78,-79,-80,-48,-53,-116,-85,-81,-84,-116,-49,-70,-66,-65,-73,-50,-50,-85,-85,-116,-116,-116,-116,-51,-116,-52,-82,-83,]),'DIFFERENT':([102,108,109,111,112,113,114,115,116,121,131,134,146,149,150,151,152,171,174,175,176,177,180,197,203,204,205,218,219,222,224,225,226,234,236,237,238,244,245,246,247,248,],[-74,143,-50,-85,-67,-69,-77,-76,-75,-74,-68,-87,-116,-116,-78,-79,-80,-48,-53,-116,-85,-81,-84,-116,-49,-70,-66,-65,-73,-50,-50,-85,-85,-116,-116,-116,-116,-51,-116,-52,-82,-83,]),'AND':([102,108,109,111,112,113,114,115,116,121,131,134,146,149,150,151,152,171,174,175,176,177,180,197,203,204,205,218,219,222,224,225,226,234,236,237,238,244,245,246,247,248,],[-74,144,-50,-85,-67,-69,-77,-76,-75,-74,-68,-87,-116,-116,-78,-79,-80,-48,-53,-116,-85,-81,-84,-116,-49,-70,-66,-65,-73,-50,-50,-85,-85,-116,-116,-116,-116,-51,-116,-52,-82,-83,]),'OR':([102,108,109,111,112,113,114,115,116,121,131,134,146,149,150,151,152,171,174,175,176,177,180,197,203,204,205,218,219,222,224,225,226,234,236,237,238,244,245,246,247,248,],[-74,145,-50,-85,-67,-69,-77,-76,-75,-74,-68,-87,-116,-116,-78,-79,-80,-48,-53,-116,-85,-81,-84,-116,-49,-70,-66,-65,-73,-50,-50,-85,-85,-116,-116,-116,-116,-51,-116,-52,-82,-83,]),'ELSE_KWD':([241,],[250,]),}

_lr_action = {}
for _k, _v in _lr_action_items.items():
   for _x,_y in zip(_v[0],_v[1]):
      if not _x in _lr_action:  _lr_action[_x] = {}
      _lr_action[_x][_k] = _y
del _lr_action_items

_lr_goto_items = {'PROGRAM':([0,],[1,]),'seen_program_id':([3,],[4,]),'empty':([3,6,7,8,11,12,14,23,29,32,42,44,47,50,53,57,61,74,79,81,83,96,101,102,103,105,106,110,118,120,124,127,139,146,149,154,157,159,163,167,168,175,176,189,192,193,197,200,208,209,210,213,223,227,228,230,234,236,237,238,241,245,250,253,258,261,270,],[5,9,15,9,21,24,15,24,21,38,48,51,56,62,78,24,62,94,56,15,107,126,130,21,133,137,137,148,155,158,162,15,170,174,180,183,186,188,194,137,137,204,204,212,194,194,219,221,155,158,62,232,148,183,186,62,174,174,180,180,251,204,255,257,62,268,62,]),'CLASS_STAR':([6,8,],[7,17,]),'CLASS':([6,8,],[8,8,]),'GLOBAL_VAR':([7,],[12,]),'VAR_LIST_STAR':([7,14,81,127,],[13,26,100,164,]),'VAR_LIST':([7,14,81,127,],[14,14,14,14,]),'ID_LIST':([7,14,81,83,127,136,],[16,16,16,105,16,167,]),'ID_LIST_P':([11,29,102,],[19,35,19,]),'FUNC_DEF_STAR':([12,23,57,],[22,31,80,]),'FUNC_DEF':([12,23,57,],[23,23,23,]),'seen_func_id':([32,],[37,]),'FUNC_PARAM':([42,],[46,]),'VAR':([42,55,],[47,79,]),'seen_main_kwd':([44,],[50,]),'FUNC_PARAM_P':([47,79,],[54,98,]),'CLASS_ATTR':([49,],[57,]),'STATEMENT_STAR':([50,61,210,230,258,270,],[60,85,229,242,260,271,]),'STATEMENT':([50,61,163,192,193,210,230,258,270,],[61,61,192,192,192,61,61,61,61,]),'ASSIGN':([50,61,163,192,193,210,230,258,259,270,],[63,63,63,63,63,63,63,63,262,63,]),'FUNC_CALL':([50,61,83,91,92,123,129,132,136,147,163,169,185,190,192,193,195,201,202,206,207,210,230,235,243,258,259,270,],[64,64,112,112,112,112,112,112,112,112,64,112,112,112,64,64,112,112,112,112,112,64,64,112,112,64,263,64,]),'READ':([50,61,163,192,193,210,230,258,259,270,],[65,65,65,65,65,65,65,65,264,65,]),'WRITE':([50,61,163,192,193,210,230,258,259,270,],[66,66,66,66,66,66,66,66,265,66,]),'DECISION':([50,61,163,192,193,210,230,258,270,],[67,67,67,67,67,67,67,67,67,]),'REPETITION':([50,61,163,192,193,210,230,258,270,],[68,68,68,68,68,68,68,68,68,]),'CONDITIONAL_REP':([50,61,163,192,193,210,230,258,270,],[72,72,72,72,72,72,72,72,72,]),'UNCONDITIONAL_REP':([50,61,163,192,193,210,230,258,270,],[73,73,73,73,73,73,73,73,73,]),'seen_func_params':([53,],[77,]),'seen_id':([59,102,121,],[82,131,131,]),'seen_while_kwd':([74,],[93,]),'VARS':([77,],[96,]),'ARG_LIST':([83,],[104,]),'EXPRESSION':([83,91,92,123,129,132,136,169,185,190,195,243,],[106,120,122,160,165,166,168,200,209,213,217,253,]),'EXP':([83,91,92,123,129,132,136,147,169,185,190,195,243,],[108,108,108,108,108,108,108,175,108,108,108,108,108,]),'TERM':([83,91,92,123,129,132,136,147,169,185,190,195,201,202,243,],[109,109,109,109,109,109,109,109,109,109,109,109,222,224,109,]),'FACTOR':([83,91,92,123,129,132,136,147,169,185,190,195,201,202,206,207,235,243,],[111,111,111,111,111,111,111,176,111,111,111,111,111,111,225,226,245,111,]),'CNST':([83,91,92,123,129,132,136,147,169,185,190,195,201,202,206,207,235,243,],[113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,]),'READABLE_LIST':([90,],[117,]),'PRINTABLE':([91,],[119,]),'seen_func_vars':([96,],[125,]),'seen_equals':([101,],[129,]),'seen_open_parenthesis':([103,],[132,]),'ARG_LIST_P':([105,106,167,168,],[135,138,198,199,]),'COMP':([108,],[139,]),'seen_term':([109,222,224,],[146,234,236,]),'seen_not':([110,223,],[147,235,]),'seen_factor':([111,176,225,226,],[149,149,237,238,]),'seen_cte_s':([114,],[150,]),'seen_cte_f':([115,],[151,]),'seen_cte_i':([116,],[152,]),'seen_readable':([118,208,],[154,227,]),'seen_printable':([120,209,],[157,228,]),'seen_for_kwd':([124,],[161,]),'seen_comp_op':([139,],[169,]),'EXP_P':([146,234,236,],[171,244,246,]),'TERM_P':([149,237,238,],[177,247,248,]),'READABLE_LIST_P':([154,227,],[181,239,]),'PRINTABLE_P':([157,228,],[184,240,]),'seen_if_kwd':([159,],[187,]),'FUNC_STATEMENT_STAR':([163,192,193,],[191,215,216,]),'FUNC_RETURN':([163,192,193,],[193,193,193,]),'seen_term_op':([172,173,],[201,202,]),'pop_not':([175,176,245,],[203,205,205,]),'seen_factor_op':([178,179,],[206,207,]),'seen_while_exp':([189,],[211,]),'seen_close_parenthesis':([197,],[218,]),'seen_comp':([200,],[220,]),'seen_for_start_exp':([213,],[231,]),'DECISION_P':([241,],[249,]),'seen_else_kwd':([250,],[254,]),'seen_for_end_exp':([253,],[256,]),'FOR_INCR_STATEMENT':([259,],[261,]),'seen_for_incr_exp':([261,],[267,]),}

_lr_goto = {}
for _k, _v in _lr_goto_items.items():
   for _x, _y in zip(_v[0], _v[1]):
       if not _x in _lr_goto: _lr_goto[_x] = {}
       _lr_goto[_x][_k] = _y
del _lr_goto_items
_lr_productions = [
  ("S' -> PROGRAM","S'",1,None,None,None),
  ('PROGRAM -> PROGRAM_KWD ID seen_program_id SEMI_COLON CLASS_STAR GLOBAL_VAR FUNC_DEF_STAR MAIN_KWD OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_CURLY seen_main_kwd STATEMENT_STAR CLOSE_CURLY','PROGRAM',14,'p_program','main.py',192),
  ('seen_program_id -> empty','seen_program_id',1,'p_seen_program_id','main.py',198),
  ('seen_main_kwd -> empty','seen_main_kwd',1,'p_seen_main_kwd','main.py',203),
  ('CLASS_STAR -> CLASS CLASS_STAR','CLASS_STAR',2,'p_class_star','main.py',207),
  ('CLASS_STAR -> empty','CLASS_STAR',1,'p_class_star','main.py',208),
  ('CLASS -> CLASS_KWD ID SMALLER DERIVES_KWD TYPE BIGGER OPEN_CURLY CLASS_ATTR FUNC_DEF_STAR CLOSE_CURLY','CLASS',10,'p_class','main.py',211),
  ('CLASS_ATTR -> ATTR_KWD OPEN_CURLY VAR_LIST_STAR CLOSE_CURLY','CLASS_ATTR',4,'p_class_attr','main.py',214),
  ('VAR_LIST_STAR -> VAR_LIST VAR_LIST_STAR','VAR_LIST_STAR',2,'p_var_list_star','main.py',217),
  ('VAR_LIST_STAR -> empty','VAR_LIST_STAR',1,'p_var_list_star','main.py',218),
  ('VAR_LIST -> ID_LIST COLON TYPE SEMI_COLON','VAR_LIST',4,'p_var_list','main.py',225),
  ('ID_LIST -> ID ID_LIST_P','ID_LIST',2,'p_id_list','main.py',229),
  ('ID_LIST_P -> COMMA ID ID_LIST_P','ID_LIST_P',3,'p_id_list_p','main.py',235),
  ('ID_LIST_P -> empty','ID_LIST_P',1,'p_id_list_p','main.py',236),
  ('READABLE_LIST -> ID seen_readable READABLE_LIST_P','READABLE_LIST',3,'p_readable_list','main.py',243),
  ('READABLE_LIST_P -> COMMA ID seen_readable READABLE_LIST_P','READABLE_LIST_P',4,'p_readable_list_p','main.py',247),
  ('READABLE_LIST_P -> empty','READABLE_LIST_P',1,'p_readable_list_p','main.py',248),
  ('seen_readable -> empty','seen_readable',1,'p_seen_readable','main.py',251),
  ('GLOBAL_VAR -> VAR_LIST_STAR','GLOBAL_VAR',1,'p_global_var','main.py',257),
  ('FUNC_DEF_STAR -> FUNC_DEF FUNC_DEF_STAR','FUNC_DEF_STAR',2,'p_func_def_star','main.py',264),
  ('FUNC_DEF_STAR -> empty','FUNC_DEF_STAR',1,'p_func_def_star','main.py',265),
  ('FUNC_DEF -> TYPE ID seen_func_id OPEN_PARENTHESIS FUNC_PARAM CLOSE_PARENTHESIS seen_func_params VARS seen_func_vars OPEN_CURLY FUNC_STATEMENT_STAR CLOSE_CURLY','FUNC_DEF',12,'p_func_def','main.py',268),
  ('seen_func_id -> empty','seen_func_id',1,'p_seen_func_id','main.py',272),
  ('seen_func_params -> empty','seen_func_params',1,'p_seen_func_params','main.py',276),
  ('seen_func_vars -> empty','seen_func_vars',1,'p_seen_func_vars','main.py',284),
  ('FUNC_PARAM -> VAR FUNC_PARAM_P','FUNC_PARAM',2,'p_func_param','main.py',292),
  ('FUNC_PARAM -> empty','FUNC_PARAM',1,'p_func_param','main.py',293),
  ('FUNC_PARAM_P -> COMMA VAR FUNC_PARAM_P','FUNC_PARAM_P',3,'p_func_param_p','main.py',301),
  ('FUNC_PARAM_P -> empty','FUNC_PARAM_P',1,'p_func_param_p','main.py',302),
  ('VAR -> ID COLON TYPE','VAR',3,'p_var','main.py',310),
  ('VARS -> VARS_KWD OPEN_CURLY VAR_LIST_STAR CLOSE_CURLY','VARS',4,'p_vars','main.py',314),
  ('FUNC_STATEMENT_STAR -> STATEMENT FUNC_STATEMENT_STAR','FUNC_STATEMENT_STAR',2,'p_func_statement_star','main.py',319),
  ('FUNC_STATEMENT_STAR -> FUNC_RETURN FUNC_STATEMENT_STAR','FUNC_STATEMENT_STAR',2,'p_func_statement_star','main.py',320),
  ('FUNC_STATEMENT_STAR -> empty','FUNC_STATEMENT_STAR',1,'p_func_statement_star','main.py',321),
  ('STATEMENT_STAR -> STATEMENT STATEMENT_STAR','STATEMENT_STAR',2,'p_statement_star','main.py',325),
  ('STATEMENT_STAR -> empty','STATEMENT_STAR',1,'p_statement_star','main.py',326),
  ('STATEMENT -> ASSIGN SEMI_COLON','STATEMENT',2,'p_statement','main.py',329),
  ('STATEMENT -> FUNC_CALL SEMI_COLON','STATEMENT',2,'p_statement','main.py',330),
  ('STATEMENT -> READ SEMI_COLON','STATEMENT',2,'p_statement','main.py',331),
  ('STATEMENT -> WRITE SEMI_COLON','STATEMENT',2,'p_statement','main.py',332),
  ('STATEMENT -> DECISION','STATEMENT',1,'p_statement','main.py',333),
  ('STATEMENT -> REPETITION','STATEMENT',1,'p_statement','main.py',334),
  ('FOR_INCR_STATEMENT -> ASSIGN','FOR_INCR_STATEMENT',1,'p_for_incr_statement','main.py',337),
  ('FOR_INCR_STATEMENT -> FUNC_CALL','FOR_INCR_STATEMENT',1,'p_for_incr_statement','main.py',338),
  ('FOR_INCR_STATEMENT -> READ','FOR_INCR_STATEMENT',1,'p_for_incr_statement','main.py',339),
  ('FOR_INCR_STATEMENT -> WRITE','FOR_INCR_STATEMENT',1,'p_for_incr_statement','main.py',340),
  ('ASSIGN -> ID seen_id EQUALS seen_equals EXPRESSION','ASSIGN',5,'p_assign','main.py',343),
  ('seen_equals -> empty','seen_equals',1,'p_seen_equals','main.py',347),
  ('EXP -> TERM seen_term EXP_P','EXP',3,'p_exp','main.py',351),
  ('EXP -> NOT seen_not EXP pop_not','EXP',4,'p_exp','main.py',352),
  ('seen_term -> <empty>','seen_term',0,'p_seen_term','main.py',356),
  ('EXP_P -> PLUS seen_term_op TERM seen_term EXP_P','EXP_P',5,'p_exp_p','main.py',362),
  ('EXP_P -> MINUS seen_term_op TERM seen_term EXP_P','EXP_P',5,'p_exp_p','main.py',363),
  ('EXP_P -> empty','EXP_P',1,'p_exp_p','main.py',364),
  ('seen_term_op -> <empty>','seen_term_op',0,'p_seen_term_op','main.py',367),
  ('EXPRESSION -> EXP','EXPRESSION',1,'p_expression','main.py',371),
  ('EXPRESSION -> EXP COMP seen_comp_op EXPRESSION seen_comp','EXPRESSION',5,'p_expression','main.py',372),
  ('seen_comp -> empty','seen_comp',1,'p_seen_comp','main.py',375),
  ('seen_comp_op -> empty','seen_comp_op',1,'p_seen_comp_op','main.py',380),
  ('COMP -> BIGGER','COMP',1,'p_comp','main.py',384),
  ('COMP -> SMALLER','COMP',1,'p_comp','main.py',385),
  ('COMP -> DOUBLE_EQUALS','COMP',1,'p_comp','main.py',386),
  ('COMP -> DIFFERENT','COMP',1,'p_comp','main.py',387),
  ('COMP -> AND','COMP',1,'p_comp','main.py',388),
  ('COMP -> OR','COMP',1,'p_comp','main.py',389),
  ('FACTOR -> OPEN_PARENTHESIS seen_open_parenthesis EXPRESSION CLOSE_PARENTHESIS seen_close_parenthesis','FACTOR',5,'p_factor','main.py',394),
  ('FACTOR -> NOT seen_not FACTOR pop_not','FACTOR',4,'p_factor','main.py',395),
  ('FACTOR -> FUNC_CALL','FACTOR',1,'p_factor','main.py',396),
  ('FACTOR -> ID seen_id','FACTOR',2,'p_factor','main.py',397),
  ('FACTOR -> CNST','FACTOR',1,'p_factor','main.py',398),
  ('pop_not -> empty','pop_not',1,'p_pop_not','main.py',401),
  ('seen_not -> empty','seen_not',1,'p_seen_not','main.py',415),
  ('seen_open_parenthesis -> empty','seen_open_parenthesis',1,'p_seen_open_parenthesis','main.py',419),
  ('seen_close_parenthesis -> empty','seen_close_parenthesis',1,'p_seen_close_parenthesis','main.py',423),
  ('seen_id -> <empty>','seen_id',0,'p_seen_id','main.py',427),
  ('seen_cte_i -> <empty>','seen_cte_i',0,'p_seen_cte_i','main.py',432),
  ('seen_cte_f -> <empty>','seen_cte_f',0,'p_seen_cte_f','main.py',437),
  ('seen_cte_s -> <empty>','seen_cte_s',0,'p_seen_cte_s','main.py',443),
  ('CNST -> CTE_S seen_cte_s','CNST',2,'p_cnst','main.py',450),
  ('CNST -> CTE_F seen_cte_f','CNST',2,'p_cnst','main.py',451),
  ('CNST -> CTE_I seen_cte_i','CNST',2,'p_cnst','main.py',452),
  ('TERM -> FACTOR seen_factor TERM_P','TERM',3,'p_term','main.py',457),
  ('TERM_P -> STAR seen_factor_op FACTOR seen_factor TERM_P','TERM_P',5,'p_term_p','main.py',460),
  ('TERM_P -> FWD_SLASH seen_factor_op FACTOR seen_factor TERM_P','TERM_P',5,'p_term_p','main.py',461),
  ('TERM_P -> empty','TERM_P',1,'p_term_p','main.py',462),
  ('seen_factor -> <empty>','seen_factor',0,'p_seen_factor','main.py',466),
  ('seen_factor_op -> <empty>','seen_factor_op',0,'p_seen_factor_op','main.py',471),
  ('FUNC_CALL -> ID OPEN_PARENTHESIS ARG_LIST CLOSE_PARENTHESIS','FUNC_CALL',4,'p_func_call','main.py',476),
  ('ARG_LIST -> ID_LIST ARG_LIST_P','ARG_LIST',2,'p_arg_list','main.py',479),
  ('ARG_LIST -> EXPRESSION ARG_LIST_P','ARG_LIST',2,'p_arg_list','main.py',480),
  ('ARG_LIST -> empty','ARG_LIST',1,'p_arg_list','main.py',481),
  ('ARG_LIST_P -> COMMA ID_LIST ARG_LIST_P','ARG_LIST_P',3,'p_arg_list_p','main.py',484),
  ('ARG_LIST_P -> COMMA EXPRESSION ARG_LIST_P','ARG_LIST_P',3,'p_arg_list_p','main.py',485),
  ('ARG_LIST_P -> empty','ARG_LIST_P',1,'p_arg_list_p','main.py',486),
  ('FUNC_RETURN -> RETURN_KWD EXPRESSION SEMI_COLON','FUNC_RETURN',3,'p_func_return','main.py',489),
  ('READ -> READ_KWD OPEN_PARENTHESIS READABLE_LIST CLOSE_PARENTHESIS','READ',4,'p_read','main.py',492),
  ('WRITE -> WRITE_KWD OPEN_PARENTHESIS PRINTABLE CLOSE_PARENTHESIS','WRITE',4,'p_write','main.py',496),
  ('PRINTABLE -> EXPRESSION seen_printable PRINTABLE_P','PRINTABLE',3,'p_printable','main.py',500),
  ('PRINTABLE_P -> COMMA EXPRESSION seen_printable PRINTABLE_P','PRINTABLE_P',4,'p_printable_p','main.py',504),
  ('PRINTABLE_P -> empty','PRINTABLE_P',1,'p_printable_p','main.py',505),
  ('seen_printable -> empty','seen_printable',1,'p_seen_printable','main.py',508),
  ('DECISION -> IF_KWD OPEN_PARENTHESIS EXPRESSION CLOSE_PARENTHESIS seen_if_kwd OPEN_CURLY STATEMENT_STAR CLOSE_CURLY DECISION_P','DECISION',9,'p_decision','main.py',513),
  ('DECISION_P -> ELSE_KWD seen_else_kwd OPEN_CURLY STATEMENT_STAR CLOSE_CURLY','DECISION_P',5,'p_decision_p','main.py',518),
  ('DECISION_P -> empty','DECISION_P',1,'p_decision_p','main.py',519),
  ('seen_if_kwd -> empty','seen_if_kwd',1,'p_seen_if_kwd','main.py',522),
  ('seen_else_kwd -> empty','seen_else_kwd',1,'p_seen_else_kwd','main.py',526),
  ('REPETITION -> CONDITIONAL_REP','REPETITION',1,'p_repetition','main.py',533),
  ('REPETITION -> UNCONDITIONAL_REP','REPETITION',1,'p_repetition','main.py',534),
  ('CONDITIONAL_REP -> WHILE_KWD seen_while_kwd OPEN_PARENTHESIS EXPRESSION CLOSE_PARENTHESIS seen_while_exp OPEN_CURLY STATEMENT_STAR CLOSE_CURLY','CONDITIONAL_REP',9,'p_conditional_rep','main.py',537),
  ('seen_while_kwd -> empty','seen_while_kwd',1,'p_seen_while_kwd','main.py',544),
  ('seen_while_exp -> empty','seen_while_exp',1,'p_seen_while_exp','main.py',549),
  ('UNCONDITIONAL_REP -> FOR_KWD OPEN_PARENTHESIS ID seen_for_kwd EQUALS EXPRESSION seen_for_start_exp SEMI_COLON EXPRESSION seen_for_end_exp SEMI_COLON FOR_INCR_STATEMENT seen_for_incr_exp CLOSE_PARENTHESIS OPEN_CURLY STATEMENT_STAR CLOSE_CURLY','UNCONDITIONAL_REP',17,'p_unconditional_rep','main.py',554),
  ('seen_for_kwd -> empty','seen_for_kwd',1,'p_seen_for_kwd','main.py',570),
  ('seen_for_incr_exp -> empty','seen_for_incr_exp',1,'p_seen_for_incr_exp','main.py',576),
  ('seen_for_start_exp -> empty','seen_for_start_exp',1,'p_seen_for_start_exp','main.py',580),
  ('seen_for_end_exp -> empty','seen_for_end_exp',1,'p_seen_for_end_exp','main.py',585),
  ('empty -> <empty>','empty',0,'p_empty','main.py',598),
]
