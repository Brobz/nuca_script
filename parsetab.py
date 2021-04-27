
# parsetab.py
# This file is automatically generated. Do not edit.
# pylint: disable=W,C,R
_tabversion = '3.10'

_lr_method = 'LALR'

_lr_signature = 'AND ATTR_KWD BIGGER CLASS_KWD CLOSE_CURLY CLOSE_PARENTHESIS COLON COMMA CTE_F CTE_I CTE_S DERIVES_KWD DIFFERENT DOUBLE_EQUALS ELSE_KWD EQUALS FOR_KWD FWD_SLASH ID IF_KWD MAIN_KWD MINUS NOT OPEN_CURLY OPEN_PARENTHESIS OR PLUS PROGRAM_KWD READ_KWD RETURN_KWD SEMI_COLON SMALLER STAR TYPE UNTIL_KWD VARS_KWD WHILE_KWD WRITE_KWD PROGRAM : PROGRAM_KWD  ID  SEMI_COLON CLASS_STAR GLOBAL_VAR FUNC_DEF_STAR MAIN_KWD OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_CURLY STATEMENT_STAR CLOSE_CURLY  CLASS_STAR : CLASS CLASS_STAR\n                   | empty  CLASS : CLASS_KWD ID SMALLER DERIVES_KWD TYPE BIGGER OPEN_CURLY CLASS_ATTR FUNC_DEF_STAR CLOSE_CURLY  CLASS_ATTR : ATTR_KWD OPEN_CURLY VAR_LIST_STAR CLOSE_CURLY  VAR_LIST_STAR : VAR_LIST VAR_LIST_STAR\n                      | empty  VAR_LIST : ID_LIST COLON TYPE SEMI_COLON  ID_LIST : ID ID_LIST_P  ID_LIST_P : COMMA ID ID_LIST_P\n                  | empty  READABLE_LIST : ID seen_readable READABLE_LIST_P  READABLE_LIST_P : COMMA ID seen_readable READABLE_LIST_P\n                  | empty  seen_readable  : empty  GLOBAL_VAR : VAR_LIST_STAR  FUNC_DEF_STAR : FUNC_DEF FUNC_DEF_STAR\n                      | empty  FUNC_DEF : TYPE ID OPEN_PARENTHESIS FUNC_PARAM CLOSE_PARENTHESIS VARS OPEN_CURLY STATEMENT_STAR CLOSE_CURLY  FUNC_PARAM : VAR FUNC_PARAM_P\n                   | empty  FUNC_PARAM_P : COMMA VAR FUNC_PARAM_P\n                     | empty  VAR : ID COLON TYPE  VARS : VARS_KWD OPEN_CURLY VAR_LIST_STAR CLOSE_CURLY  STATEMENT_STAR :  STATEMENT STATEMENT_STAR\n                       | empty  STATEMENT : ASSIGN\n                  | FUNC_RETURN\n                  | READ\n                  | WRITE\n                  | DECISION\n                  | REPETITION  ASSIGN : ID seen_id EQUALS seen_equals EXPRESSION SEMI_COLON  seen_equals  : empty  EXP :   TERM seen_term EXP_P\n              | NOT seen_not EXP pop_not seen_term :   EXP_P : PLUS seen_term_op TERM seen_term EXP_P\n            | MINUS seen_term_op TERM seen_term EXP_P\n            | empty  seen_term_op :   EXPRESSION :   EXP\n                     | EXP COMP seen_comp_op EXP seen_comp  seen_comp : empty  seen_comp_op : empty  COMP : BIGGER\n             | SMALLER\n             | DOUBLE_EQUALS\n             | DIFFERENT\n             | AND\n             | OR  FACTOR :  OPEN_PARENTHESIS seen_open_parenthesis EXPRESSION CLOSE_PARENTHESIS seen_close_parenthesis\n                | NOT seen_not FACTOR pop_not\n                | FUNC_CALL\n                | ID seen_id\n                | CNST   pop_not : empty  seen_not : empty  seen_open_parenthesis : empty  seen_close_parenthesis : empty  seen_id :   seen_cte_i :   seen_cte_f :   seen_cte_s :   CNST : CTE_S seen_cte_s\n             | CTE_F seen_cte_f\n             | CTE_I seen_cte_i  TERM : FACTOR seen_factor TERM_P   TERM_P :    STAR seen_factor_op FACTOR seen_factor TERM_P\n                 |  FWD_SLASH seen_factor_op FACTOR seen_factor TERM_P\n                 |  empty  seen_factor :   seen_factor_op :   FUNC_CALL : ID OPEN_PARENTHESIS ARG_LIST CLOSE_PARENTHESIS  ARG_LIST : ID_LIST ARG_LIST_P\n                 | EXPRESSION ARG_LIST_P  ARG_LIST_P : COMMA ID_LIST ARG_LIST_P\n                   | COMMA EXPRESSION ARG_LIST_P\n                   | empty  FUNC_RETURN : RETURN_KWD EXPRESSION SEMI_COLON  READ : READ_KWD OPEN_PARENTHESIS READABLE_LIST CLOSE_PARENTHESIS SEMI_COLON  WRITE : WRITE_KWD OPEN_PARENTHESIS PRINTABLE CLOSE_PARENTHESIS SEMI_COLON  PRINTABLE : EXPRESSION seen_printable PRINTABLE_P  PRINTABLE_P : COMMA EXPRESSION seen_printable PRINTABLE_P\n                    | empty  seen_printable  : empty  DECISION : IF_KWD OPEN_PARENTHESIS EXPRESSION CLOSE_PARENTHESIS seen_if_kwd OPEN_CURLY STATEMENT_STAR CLOSE_CURLY DECISION_P  DECISION_P : ELSE_KWD seen_else_kwd OPEN_CURLY STATEMENT_STAR CLOSE_CURLY\n                   | empty  seen_if_kwd : empty  seen_else_kwd : empty  REPETITION : CONDITIONAL_REP\n                   | UNCONDITIONAL_REP  CONDITIONAL_REP : WHILE_KWD seen_while_kwd OPEN_PARENTHESIS EXPRESSION CLOSE_PARENTHESIS seen_while_exp OPEN_CURLY STATEMENT_STAR CLOSE_CURLY  seen_while_kwd : empty  seen_while_exp : empty  UNCONDITIONAL_REP : FOR_KWD OPEN_PARENTHESIS ID seen_for_kwd EQUALS EXPRESSION seen_for_start_exp SEMI_COLON EXPRESSION seen_for_end_exp SEMI_COLON STATEMENT seen_for_incr_exp CLOSE_PARENTHESIS OPEN_CURLY STATEMENT_STAR CLOSE_CURLY  seen_for_kwd : empty  seen_for_incr_exp : empty seen_for_start_exp : empty  seen_for_end_exp : empty empty :'
    
_lr_action_items = {'PROGRAM_KWD':([0,],[2,]),'$end':([1,76,],[0,-1,]),'ID':([2,4,5,6,7,8,12,15,18,23,35,36,44,48,53,55,56,57,58,59,60,61,65,66,81,83,90,91,92,95,96,97,100,101,102,103,104,105,106,107,108,109,111,112,114,115,117,126,130,132,133,134,135,137,138,143,144,166,167,171,172,176,179,181,183,185,190,191,195,205,210,219,229,231,232,234,235,241,242,245,249,251,],[3,-103,9,-103,-3,16,9,-2,27,30,39,-8,51,39,51,-28,-29,-30,-31,-32,-33,85,-93,-94,-103,-103,122,85,85,127,51,9,9,-103,-81,-103,-47,-48,-49,-50,-51,-52,85,-59,85,-60,147,85,-4,85,-35,85,-46,-42,-42,-74,-74,85,85,85,85,147,-82,203,-83,85,85,-34,-103,51,85,51,-103,85,-88,-90,-95,51,51,-89,51,-98,]),'SEMI_COLON':([3,31,78,79,80,82,84,85,86,87,88,89,110,113,116,118,119,120,136,139,140,141,142,145,151,154,164,165,168,169,170,173,174,192,193,194,196,197,198,199,200,208,209,211,212,213,220,221,222,223,224,225,226,236,239,240,],[4,36,102,-43,-38,-73,-55,-62,-57,-65,-64,-63,-103,-103,-56,-66,-67,-68,-36,-41,-103,-73,-69,-72,179,183,191,-103,-37,-58,-54,-103,-75,-44,-45,-38,-38,-73,-73,-53,-61,-103,-103,-103,-103,-103,231,-101,-39,-103,-40,-70,-71,-103,242,-102,]),'CLASS_KWD':([4,6,130,],[8,8,-4,]),'TYPE':([4,5,6,7,10,11,12,13,15,21,24,25,32,36,45,73,130,161,163,],[-103,-103,-103,-3,23,-16,-103,-7,-2,23,-6,31,37,-8,69,23,-4,-19,-5,]),'MAIN_KWD':([4,5,6,7,10,11,12,13,15,20,21,22,24,29,36,130,161,],[-103,-103,-103,-3,-103,-16,-103,-7,-2,28,-103,-18,-6,-17,-8,-4,-19,]),'COMMA':([9,17,19,27,33,41,69,72,79,80,82,84,85,86,87,88,89,110,113,116,118,119,120,122,124,136,139,140,141,142,145,147,149,150,152,153,155,156,165,168,169,170,173,174,192,193,194,196,197,198,199,200,201,202,203,204,209,211,212,213,216,217,222,223,224,225,226,],[18,-9,-11,18,-10,48,-24,48,-43,-38,-73,-55,-62,-57,-65,-64,-63,-103,-103,-56,-66,-67,-68,-103,-103,-36,-41,-103,-73,-69,-72,18,176,176,181,-15,185,-87,-103,-37,-58,-54,-103,-75,-44,-45,-38,-38,-73,-73,-53,-61,176,176,-103,-103,-103,-103,-103,-103,181,185,-39,-103,-40,-70,-71,]),'COLON':([9,14,17,19,27,33,39,],[-103,25,-9,-11,-103,-10,45,]),'CLOSE_CURLY':([12,13,21,22,24,29,36,44,52,53,54,55,56,57,58,59,60,65,66,73,77,96,97,99,100,102,128,129,131,161,163,179,183,191,205,218,219,229,230,232,234,235,241,243,245,249,250,251,],[-103,-7,-103,-18,-6,-17,-8,-103,76,-103,-27,-28,-29,-30,-31,-32,-33,-93,-94,-103,-26,-103,-103,130,-103,-81,161,162,163,-19,-5,-82,-83,-34,-103,229,-103,-103,235,-88,-90,-95,-103,245,-89,-103,251,-98,]),'SMALLER':([16,79,80,82,84,85,86,87,88,89,110,113,116,118,119,120,136,139,140,141,142,145,147,168,169,170,173,174,194,196,197,198,199,200,209,211,212,213,222,223,224,225,226,],[26,105,-38,-73,-55,-62,-57,-65,-64,-63,-103,-103,-56,-66,-67,-68,-36,-41,-103,-73,-69,-72,-62,-37,-58,-54,-103,-75,-38,-38,-73,-73,-53,-61,-103,-103,-103,-103,-39,-103,-40,-70,-71,]),'CLOSE_PARENTHESIS':([17,19,27,33,34,35,40,41,42,47,49,55,56,57,58,59,60,65,66,69,72,79,80,82,84,85,86,87,88,89,98,102,110,113,116,118,119,120,121,122,123,124,125,136,139,140,141,142,145,146,147,148,149,150,152,153,155,156,158,165,168,169,170,173,174,175,177,178,179,180,182,183,184,186,191,192,193,194,196,197,198,199,200,201,202,203,204,209,211,212,213,214,215,216,217,222,223,224,225,226,227,228,229,232,234,235,244,245,246,247,251,],[-9,-11,-103,-10,38,-103,46,-103,-21,-20,-23,-28,-29,-30,-31,-32,-33,-93,-94,-24,-103,-43,-38,-73,-55,-62,-57,-65,-64,-63,-22,-81,-103,-103,-56,-66,-67,-68,151,-103,154,-103,157,-36,-41,-103,-73,-69,-72,173,-62,174,-103,-103,-103,-15,-103,-87,189,-103,-37,-58,-54,-103,-75,-76,-80,-77,-82,-12,-14,-83,-84,-86,-34,-44,-45,-38,-38,-73,-73,-53,-61,-103,-103,-103,-103,-103,-103,-103,-103,-78,-79,-103,-103,-39,-103,-40,-70,-71,-13,-85,-103,-88,-90,-95,-103,-89,248,-100,-98,]),'DERIVES_KWD':([26,],[32,]),'OPEN_PARENTHESIS':([28,30,61,62,63,64,67,68,81,83,85,91,92,93,94,101,103,104,105,106,107,108,109,111,112,114,115,117,126,132,133,134,135,137,138,143,144,147,166,167,171,172,176,185,190,195,210,231,],[34,35,83,90,91,92,-103,95,-103,-103,117,83,83,126,-96,-103,-103,-47,-48,-49,-50,-51,-52,83,-59,83,-60,83,83,83,-35,83,-46,-42,-42,-74,-74,117,83,83,83,83,83,83,83,-103,83,83,]),'BIGGER':([37,79,80,82,84,85,86,87,88,89,110,113,116,118,119,120,136,139,140,141,142,145,147,168,169,170,173,174,194,196,197,198,199,200,209,211,212,213,222,223,224,225,226,],[43,104,-38,-73,-55,-62,-57,-65,-64,-63,-103,-103,-56,-66,-67,-68,-36,-41,-103,-73,-69,-72,-62,-37,-58,-54,-103,-75,-38,-38,-73,-73,-53,-61,-103,-103,-103,-103,-39,-103,-40,-70,-71,]),'OPEN_CURLY':([38,43,70,71,74,157,162,187,188,189,206,207,233,237,238,248,],[44,50,96,97,100,-103,-25,205,-91,-103,219,-97,-103,241,-92,249,]),'RETURN_KWD':([44,53,55,56,57,58,59,60,65,66,96,102,179,183,191,205,219,229,232,234,235,241,242,245,249,251,],[61,61,-28,-29,-30,-31,-32,-33,-93,-94,61,-81,-82,-83,-34,61,61,-103,-88,-90,-95,61,61,-89,61,-98,]),'READ_KWD':([44,53,55,56,57,58,59,60,65,66,96,102,179,183,191,205,219,229,232,234,235,241,242,245,249,251,],[62,62,-28,-29,-30,-31,-32,-33,-93,-94,62,-81,-82,-83,-34,62,62,-103,-88,-90,-95,62,62,-89,62,-98,]),'WRITE_KWD':([44,53,55,56,57,58,59,60,65,66,96,102,179,183,191,205,219,229,232,234,235,241,242,245,249,251,],[63,63,-28,-29,-30,-31,-32,-33,-93,-94,63,-81,-82,-83,-34,63,63,-103,-88,-90,-95,63,63,-89,63,-98,]),'IF_KWD':([44,53,55,56,57,58,59,60,65,66,96,102,179,183,191,205,219,229,232,234,235,241,242,245,249,251,],[64,64,-28,-29,-30,-31,-32,-33,-93,-94,64,-81,-82,-83,-34,64,64,-103,-88,-90,-95,64,64,-89,64,-98,]),'WHILE_KWD':([44,53,55,56,57,58,59,60,65,66,96,102,179,183,191,205,219,229,232,234,235,241,242,245,249,251,],[67,67,-28,-29,-30,-31,-32,-33,-93,-94,67,-81,-82,-83,-34,67,67,-103,-88,-90,-95,67,67,-89,67,-98,]),'FOR_KWD':([44,53,55,56,57,58,59,60,65,66,96,102,179,183,191,205,219,229,232,234,235,241,242,245,249,251,],[68,68,-28,-29,-30,-31,-32,-33,-93,-94,68,-81,-82,-83,-34,68,68,-103,-88,-90,-95,68,68,-89,68,-98,]),'VARS_KWD':([46,],[71,]),'ATTR_KWD':([50,],[74,]),'EQUALS':([51,75,127,159,160,],[-62,101,-103,190,-99,]),'NOT':([61,81,83,91,92,101,103,104,105,106,107,108,109,111,112,114,115,117,126,132,133,134,135,137,138,143,144,166,167,171,172,176,185,190,195,210,231,],[81,-103,-103,81,81,-103,-103,-47,-48,-49,-50,-51,-52,81,-59,81,-60,81,81,81,-35,81,-46,-42,-42,-74,-74,195,195,195,195,81,81,81,-103,195,81,]),'CTE_S':([61,81,83,91,92,101,103,104,105,106,107,108,109,111,112,114,115,117,126,132,133,134,135,137,138,143,144,166,167,171,172,176,185,190,195,210,231,],[87,-103,-103,87,87,-103,-103,-47,-48,-49,-50,-51,-52,87,-59,87,-60,87,87,87,-35,87,-46,-42,-42,-74,-74,87,87,87,87,87,87,87,-103,87,87,]),'CTE_F':([61,81,83,91,92,101,103,104,105,106,107,108,109,111,112,114,115,117,126,132,133,134,135,137,138,143,144,166,167,171,172,176,185,190,195,210,231,],[88,-103,-103,88,88,-103,-103,-47,-48,-49,-50,-51,-52,88,-59,88,-60,88,88,88,-35,88,-46,-42,-42,-74,-74,88,88,88,88,88,88,88,-103,88,88,]),'CTE_I':([61,81,83,91,92,101,103,104,105,106,107,108,109,111,112,114,115,117,126,132,133,134,135,137,138,143,144,166,167,171,172,176,185,190,195,210,231,],[89,-103,-103,89,89,-103,-103,-47,-48,-49,-50,-51,-52,89,-59,89,-60,89,89,89,-35,89,-46,-42,-42,-74,-74,89,89,89,89,89,89,89,-103,89,89,]),'DOUBLE_EQUALS':([79,80,82,84,85,86,87,88,89,110,113,116,118,119,120,136,139,140,141,142,145,147,168,169,170,173,174,194,196,197,198,199,200,209,211,212,213,222,223,224,225,226,],[106,-38,-73,-55,-62,-57,-65,-64,-63,-103,-103,-56,-66,-67,-68,-36,-41,-103,-73,-69,-72,-62,-37,-58,-54,-103,-75,-38,-38,-73,-73,-53,-61,-103,-103,-103,-103,-39,-103,-40,-70,-71,]),'DIFFERENT':([79,80,82,84,85,86,87,88,89,110,113,116,118,119,120,136,139,140,141,142,145,147,168,169,170,173,174,194,196,197,198,199,200,209,211,212,213,222,223,224,225,226,],[107,-38,-73,-55,-62,-57,-65,-64,-63,-103,-103,-56,-66,-67,-68,-36,-41,-103,-73,-69,-72,-62,-37,-58,-54,-103,-75,-38,-38,-73,-73,-53,-61,-103,-103,-103,-103,-39,-103,-40,-70,-71,]),'AND':([79,80,82,84,85,86,87,88,89,110,113,116,118,119,120,136,139,140,141,142,145,147,168,169,170,173,174,194,196,197,198,199,200,209,211,212,213,222,223,224,225,226,],[108,-38,-73,-55,-62,-57,-65,-64,-63,-103,-103,-56,-66,-67,-68,-36,-41,-103,-73,-69,-72,-62,-37,-58,-54,-103,-75,-38,-38,-73,-73,-53,-61,-103,-103,-103,-103,-39,-103,-40,-70,-71,]),'OR':([79,80,82,84,85,86,87,88,89,110,113,116,118,119,120,136,139,140,141,142,145,147,168,169,170,173,174,194,196,197,198,199,200,209,211,212,213,222,223,224,225,226,],[109,-38,-73,-55,-62,-57,-65,-64,-63,-103,-103,-56,-66,-67,-68,-36,-41,-103,-73,-69,-72,-62,-37,-58,-54,-103,-75,-38,-38,-73,-73,-53,-61,-103,-103,-103,-103,-39,-103,-40,-70,-71,]),'PLUS':([80,82,84,85,86,87,88,89,110,113,116,118,119,120,141,142,145,147,169,170,173,174,194,196,197,198,199,200,209,211,212,213,223,225,226,],[-38,-73,-55,-62,-57,-65,-64,-63,137,-103,-56,-66,-67,-68,-73,-69,-72,-62,-58,-54,-103,-75,-38,-38,-73,-73,-53,-61,137,137,-103,-103,-103,-70,-71,]),'MINUS':([80,82,84,85,86,87,88,89,110,113,116,118,119,120,141,142,145,147,169,170,173,174,194,196,197,198,199,200,209,211,212,213,223,225,226,],[-38,-73,-55,-62,-57,-65,-64,-63,138,-103,-56,-66,-67,-68,-73,-69,-72,-62,-58,-54,-103,-75,-38,-38,-73,-73,-53,-61,138,138,-103,-103,-103,-70,-71,]),'STAR':([82,84,85,86,87,88,89,113,116,118,119,120,141,147,169,170,173,174,197,198,199,200,212,213,223,],[-73,-55,-62,-57,-65,-64,-63,143,-56,-66,-67,-68,-73,-62,-58,-54,-103,-75,-73,-73,-53,-61,143,143,-103,]),'FWD_SLASH':([82,84,85,86,87,88,89,113,116,118,119,120,141,147,169,170,173,174,197,198,199,200,212,213,223,],[-73,-55,-62,-57,-65,-64,-63,144,-56,-66,-67,-68,-73,-62,-58,-54,-103,-75,-73,-73,-53,-61,144,144,-103,]),'ELSE_KWD':([229,],[233,]),}

_lr_action = {}
for _k, _v in _lr_action_items.items():
   for _x,_y in zip(_v[0],_v[1]):
      if not _x in _lr_action:  _lr_action[_x] = {}
      _lr_action[_x][_k] = _y
del _lr_action_items

_lr_goto_items = {'PROGRAM':([0,],[1,]),'CLASS_STAR':([4,6,],[5,15,]),'CLASS':([4,6,],[6,6,]),'empty':([4,5,6,9,10,12,21,27,35,41,44,53,67,72,73,81,83,96,97,100,101,103,110,113,122,124,127,140,141,147,149,150,152,155,157,165,173,189,195,201,202,203,204,205,208,209,211,212,213,216,217,219,223,229,233,236,241,244,249,],[7,13,7,19,22,13,22,19,42,49,54,54,94,49,22,112,115,54,13,13,133,135,139,145,153,156,160,169,169,19,177,177,182,186,188,193,200,207,112,177,177,153,156,54,221,139,139,145,145,182,186,54,169,234,238,240,54,247,54,]),'GLOBAL_VAR':([5,],[10,]),'VAR_LIST_STAR':([5,12,97,100,],[11,24,129,131,]),'VAR_LIST':([5,12,97,100,],[12,12,12,12,]),'ID_LIST':([5,12,97,100,117,176,],[14,14,14,14,149,201,]),'ID_LIST_P':([9,27,147,],[17,33,17,]),'FUNC_DEF_STAR':([10,21,73,],[20,29,99,]),'FUNC_DEF':([10,21,73,],[21,21,21,]),'FUNC_PARAM':([35,],[40,]),'VAR':([35,48,],[41,72,]),'FUNC_PARAM_P':([41,72,],[47,98,]),'STATEMENT_STAR':([44,53,96,205,219,241,249,],[52,77,128,218,230,243,250,]),'STATEMENT':([44,53,96,205,219,241,242,249,],[53,53,53,53,53,53,244,53,]),'ASSIGN':([44,53,96,205,219,241,242,249,],[55,55,55,55,55,55,55,55,]),'FUNC_RETURN':([44,53,96,205,219,241,242,249,],[56,56,56,56,56,56,56,56,]),'READ':([44,53,96,205,219,241,242,249,],[57,57,57,57,57,57,57,57,]),'WRITE':([44,53,96,205,219,241,242,249,],[58,58,58,58,58,58,58,58,]),'DECISION':([44,53,96,205,219,241,242,249,],[59,59,59,59,59,59,59,59,]),'REPETITION':([44,53,96,205,219,241,242,249,],[60,60,60,60,60,60,60,60,]),'CONDITIONAL_REP':([44,53,96,205,219,241,242,249,],[65,65,65,65,65,65,65,65,]),'UNCONDITIONAL_REP':([44,53,96,205,219,241,242,249,],[66,66,66,66,66,66,66,66,]),'VARS':([46,],[70,]),'CLASS_ATTR':([50,],[73,]),'seen_id':([51,85,147,],[75,116,116,]),'EXPRESSION':([61,91,92,114,117,126,132,176,185,190,231,],[78,124,125,146,150,158,164,202,204,208,236,]),'EXP':([61,91,92,111,114,117,126,132,134,176,185,190,231,],[79,79,79,140,79,79,79,79,165,79,79,79,79,]),'TERM':([61,91,92,111,114,117,126,132,134,166,167,176,185,190,231,],[80,80,80,80,80,80,80,80,80,194,196,80,80,80,80,]),'FACTOR':([61,91,92,111,114,117,126,132,134,166,167,171,172,176,185,190,210,231,],[82,82,82,141,82,82,82,82,82,82,82,197,198,82,82,82,223,82,]),'FUNC_CALL':([61,91,92,111,114,117,126,132,134,166,167,171,172,176,185,190,210,231,],[84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,]),'CNST':([61,91,92,111,114,117,126,132,134,166,167,171,172,176,185,190,210,231,],[86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,]),'seen_while_kwd':([67,],[93,]),'COMP':([79,],[103,]),'seen_term':([80,194,196,],[110,209,211,]),'seen_not':([81,195,],[111,210,]),'seen_factor':([82,141,197,198,],[113,113,212,213,]),'seen_open_parenthesis':([83,],[114,]),'seen_cte_s':([87,],[118,]),'seen_cte_f':([88,],[119,]),'seen_cte_i':([89,],[120,]),'READABLE_LIST':([90,],[121,]),'PRINTABLE':([91,],[123,]),'seen_equals':([101,],[132,]),'seen_comp_op':([103,],[134,]),'EXP_P':([110,209,211,],[136,222,224,]),'TERM_P':([113,212,213,],[142,225,226,]),'ARG_LIST':([117,],[148,]),'seen_readable':([122,203,],[152,216,]),'seen_printable':([124,204,],[155,217,]),'seen_for_kwd':([127,],[159,]),'seen_term_op':([137,138,],[166,167,]),'pop_not':([140,141,223,],[168,170,170,]),'seen_factor_op':([143,144,],[171,172,]),'ARG_LIST_P':([149,150,201,202,],[175,178,214,215,]),'READABLE_LIST_P':([152,216,],[180,227,]),'PRINTABLE_P':([155,217,],[184,228,]),'seen_if_kwd':([157,],[187,]),'seen_comp':([165,],[192,]),'seen_close_parenthesis':([173,],[199,]),'seen_while_exp':([189,],[206,]),'seen_for_start_exp':([208,],[220,]),'DECISION_P':([229,],[232,]),'seen_else_kwd':([233,],[237,]),'seen_for_end_exp':([236,],[239,]),'seen_for_incr_exp':([244,],[246,]),}

_lr_goto = {}
for _k, _v in _lr_goto_items.items():
   for _x, _y in zip(_v[0], _v[1]):
       if not _x in _lr_goto: _lr_goto[_x] = {}
       _lr_goto[_x][_k] = _y
del _lr_goto_items
_lr_productions = [
  ("S' -> PROGRAM","S'",1,None,None,None),
  ('PROGRAM -> PROGRAM_KWD ID SEMI_COLON CLASS_STAR GLOBAL_VAR FUNC_DEF_STAR MAIN_KWD OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_CURLY STATEMENT_STAR CLOSE_CURLY','PROGRAM',12,'p_program','main.py',181),
  ('CLASS_STAR -> CLASS CLASS_STAR','CLASS_STAR',2,'p_class_star','main.py',186),
  ('CLASS_STAR -> empty','CLASS_STAR',1,'p_class_star','main.py',187),
  ('CLASS -> CLASS_KWD ID SMALLER DERIVES_KWD TYPE BIGGER OPEN_CURLY CLASS_ATTR FUNC_DEF_STAR CLOSE_CURLY','CLASS',10,'p_class','main.py',190),
  ('CLASS_ATTR -> ATTR_KWD OPEN_CURLY VAR_LIST_STAR CLOSE_CURLY','CLASS_ATTR',4,'p_class_attr','main.py',193),
  ('VAR_LIST_STAR -> VAR_LIST VAR_LIST_STAR','VAR_LIST_STAR',2,'p_var_list_star','main.py',196),
  ('VAR_LIST_STAR -> empty','VAR_LIST_STAR',1,'p_var_list_star','main.py',197),
  ('VAR_LIST -> ID_LIST COLON TYPE SEMI_COLON','VAR_LIST',4,'p_var_list','main.py',204),
  ('ID_LIST -> ID ID_LIST_P','ID_LIST',2,'p_id_list','main.py',208),
  ('ID_LIST_P -> COMMA ID ID_LIST_P','ID_LIST_P',3,'p_id_list_p','main.py',214),
  ('ID_LIST_P -> empty','ID_LIST_P',1,'p_id_list_p','main.py',215),
  ('READABLE_LIST -> ID seen_readable READABLE_LIST_P','READABLE_LIST',3,'p_readable_list','main.py',222),
  ('READABLE_LIST_P -> COMMA ID seen_readable READABLE_LIST_P','READABLE_LIST_P',4,'p_readable_list_p','main.py',226),
  ('READABLE_LIST_P -> empty','READABLE_LIST_P',1,'p_readable_list_p','main.py',227),
  ('seen_readable -> empty','seen_readable',1,'p_seen_readable','main.py',230),
  ('GLOBAL_VAR -> VAR_LIST_STAR','GLOBAL_VAR',1,'p_global_var','main.py',236),
  ('FUNC_DEF_STAR -> FUNC_DEF FUNC_DEF_STAR','FUNC_DEF_STAR',2,'p_func_def_star','main.py',243),
  ('FUNC_DEF_STAR -> empty','FUNC_DEF_STAR',1,'p_func_def_star','main.py',244),
  ('FUNC_DEF -> TYPE ID OPEN_PARENTHESIS FUNC_PARAM CLOSE_PARENTHESIS VARS OPEN_CURLY STATEMENT_STAR CLOSE_CURLY','FUNC_DEF',9,'p_func_def','main.py',247),
  ('FUNC_PARAM -> VAR FUNC_PARAM_P','FUNC_PARAM',2,'p_func_param','main.py',263),
  ('FUNC_PARAM -> empty','FUNC_PARAM',1,'p_func_param','main.py',264),
  ('FUNC_PARAM_P -> COMMA VAR FUNC_PARAM_P','FUNC_PARAM_P',3,'p_func_param_p','main.py',272),
  ('FUNC_PARAM_P -> empty','FUNC_PARAM_P',1,'p_func_param_p','main.py',273),
  ('VAR -> ID COLON TYPE','VAR',3,'p_var','main.py',281),
  ('VARS -> VARS_KWD OPEN_CURLY VAR_LIST_STAR CLOSE_CURLY','VARS',4,'p_vars','main.py',285),
  ('STATEMENT_STAR -> STATEMENT STATEMENT_STAR','STATEMENT_STAR',2,'p_statement_star','main.py',289),
  ('STATEMENT_STAR -> empty','STATEMENT_STAR',1,'p_statement_star','main.py',290),
  ('STATEMENT -> ASSIGN','STATEMENT',1,'p_statement','main.py',293),
  ('STATEMENT -> FUNC_RETURN','STATEMENT',1,'p_statement','main.py',294),
  ('STATEMENT -> READ','STATEMENT',1,'p_statement','main.py',295),
  ('STATEMENT -> WRITE','STATEMENT',1,'p_statement','main.py',296),
  ('STATEMENT -> DECISION','STATEMENT',1,'p_statement','main.py',297),
  ('STATEMENT -> REPETITION','STATEMENT',1,'p_statement','main.py',298),
  ('ASSIGN -> ID seen_id EQUALS seen_equals EXPRESSION SEMI_COLON','ASSIGN',6,'p_assign','main.py',301),
  ('seen_equals -> empty','seen_equals',1,'p_seen_equals','main.py',305),
  ('EXP -> TERM seen_term EXP_P','EXP',3,'p_exp','main.py',309),
  ('EXP -> NOT seen_not EXP pop_not','EXP',4,'p_exp','main.py',310),
  ('seen_term -> <empty>','seen_term',0,'p_seen_term','main.py',314),
  ('EXP_P -> PLUS seen_term_op TERM seen_term EXP_P','EXP_P',5,'p_exp_p','main.py',320),
  ('EXP_P -> MINUS seen_term_op TERM seen_term EXP_P','EXP_P',5,'p_exp_p','main.py',321),
  ('EXP_P -> empty','EXP_P',1,'p_exp_p','main.py',322),
  ('seen_term_op -> <empty>','seen_term_op',0,'p_seen_term_op','main.py',325),
  ('EXPRESSION -> EXP','EXPRESSION',1,'p_expression','main.py',329),
  ('EXPRESSION -> EXP COMP seen_comp_op EXP seen_comp','EXPRESSION',5,'p_expression','main.py',330),
  ('seen_comp -> empty','seen_comp',1,'p_seen_comp','main.py',333),
  ('seen_comp_op -> empty','seen_comp_op',1,'p_seen_comp_op','main.py',338),
  ('COMP -> BIGGER','COMP',1,'p_comp','main.py',342),
  ('COMP -> SMALLER','COMP',1,'p_comp','main.py',343),
  ('COMP -> DOUBLE_EQUALS','COMP',1,'p_comp','main.py',344),
  ('COMP -> DIFFERENT','COMP',1,'p_comp','main.py',345),
  ('COMP -> AND','COMP',1,'p_comp','main.py',346),
  ('COMP -> OR','COMP',1,'p_comp','main.py',347),
  ('FACTOR -> OPEN_PARENTHESIS seen_open_parenthesis EXPRESSION CLOSE_PARENTHESIS seen_close_parenthesis','FACTOR',5,'p_factor','main.py',352),
  ('FACTOR -> NOT seen_not FACTOR pop_not','FACTOR',4,'p_factor','main.py',353),
  ('FACTOR -> FUNC_CALL','FACTOR',1,'p_factor','main.py',354),
  ('FACTOR -> ID seen_id','FACTOR',2,'p_factor','main.py',355),
  ('FACTOR -> CNST','FACTOR',1,'p_factor','main.py',356),
  ('pop_not -> empty','pop_not',1,'p_pop_not','main.py',359),
  ('seen_not -> empty','seen_not',1,'p_seen_not','main.py',373),
  ('seen_open_parenthesis -> empty','seen_open_parenthesis',1,'p_seen_open_parenthesis','main.py',377),
  ('seen_close_parenthesis -> empty','seen_close_parenthesis',1,'p_seen_close_parenthesis','main.py',381),
  ('seen_id -> <empty>','seen_id',0,'p_seen_id','main.py',385),
  ('seen_cte_i -> <empty>','seen_cte_i',0,'p_seen_cte_i','main.py',390),
  ('seen_cte_f -> <empty>','seen_cte_f',0,'p_seen_cte_f','main.py',395),
  ('seen_cte_s -> <empty>','seen_cte_s',0,'p_seen_cte_s','main.py',401),
  ('CNST -> CTE_S seen_cte_s','CNST',2,'p_cnst','main.py',408),
  ('CNST -> CTE_F seen_cte_f','CNST',2,'p_cnst','main.py',409),
  ('CNST -> CTE_I seen_cte_i','CNST',2,'p_cnst','main.py',410),
  ('TERM -> FACTOR seen_factor TERM_P','TERM',3,'p_term','main.py',415),
  ('TERM_P -> STAR seen_factor_op FACTOR seen_factor TERM_P','TERM_P',5,'p_term_p','main.py',418),
  ('TERM_P -> FWD_SLASH seen_factor_op FACTOR seen_factor TERM_P','TERM_P',5,'p_term_p','main.py',419),
  ('TERM_P -> empty','TERM_P',1,'p_term_p','main.py',420),
  ('seen_factor -> <empty>','seen_factor',0,'p_seen_factor','main.py',424),
  ('seen_factor_op -> <empty>','seen_factor_op',0,'p_seen_factor_op','main.py',429),
  ('FUNC_CALL -> ID OPEN_PARENTHESIS ARG_LIST CLOSE_PARENTHESIS','FUNC_CALL',4,'p_func_call','main.py',434),
  ('ARG_LIST -> ID_LIST ARG_LIST_P','ARG_LIST',2,'p_arg_list','main.py',437),
  ('ARG_LIST -> EXPRESSION ARG_LIST_P','ARG_LIST',2,'p_arg_list','main.py',438),
  ('ARG_LIST_P -> COMMA ID_LIST ARG_LIST_P','ARG_LIST_P',3,'p_arg_list_p','main.py',441),
  ('ARG_LIST_P -> COMMA EXPRESSION ARG_LIST_P','ARG_LIST_P',3,'p_arg_list_p','main.py',442),
  ('ARG_LIST_P -> empty','ARG_LIST_P',1,'p_arg_list_p','main.py',443),
  ('FUNC_RETURN -> RETURN_KWD EXPRESSION SEMI_COLON','FUNC_RETURN',3,'p_func_return','main.py',446),
  ('READ -> READ_KWD OPEN_PARENTHESIS READABLE_LIST CLOSE_PARENTHESIS SEMI_COLON','READ',5,'p_read','main.py',449),
  ('WRITE -> WRITE_KWD OPEN_PARENTHESIS PRINTABLE CLOSE_PARENTHESIS SEMI_COLON','WRITE',5,'p_write','main.py',453),
  ('PRINTABLE -> EXPRESSION seen_printable PRINTABLE_P','PRINTABLE',3,'p_printable','main.py',457),
  ('PRINTABLE_P -> COMMA EXPRESSION seen_printable PRINTABLE_P','PRINTABLE_P',4,'p_printable_p','main.py',461),
  ('PRINTABLE_P -> empty','PRINTABLE_P',1,'p_printable_p','main.py',462),
  ('seen_printable -> empty','seen_printable',1,'p_seen_printable','main.py',465),
  ('DECISION -> IF_KWD OPEN_PARENTHESIS EXPRESSION CLOSE_PARENTHESIS seen_if_kwd OPEN_CURLY STATEMENT_STAR CLOSE_CURLY DECISION_P','DECISION',9,'p_decision','main.py',469),
  ('DECISION_P -> ELSE_KWD seen_else_kwd OPEN_CURLY STATEMENT_STAR CLOSE_CURLY','DECISION_P',5,'p_decision_p','main.py',474),
  ('DECISION_P -> empty','DECISION_P',1,'p_decision_p','main.py',475),
  ('seen_if_kwd -> empty','seen_if_kwd',1,'p_seen_if_kwd','main.py',478),
  ('seen_else_kwd -> empty','seen_else_kwd',1,'p_seen_else_kwd','main.py',482),
  ('REPETITION -> CONDITIONAL_REP','REPETITION',1,'p_repetition','main.py',489),
  ('REPETITION -> UNCONDITIONAL_REP','REPETITION',1,'p_repetition','main.py',490),
  ('CONDITIONAL_REP -> WHILE_KWD seen_while_kwd OPEN_PARENTHESIS EXPRESSION CLOSE_PARENTHESIS seen_while_exp OPEN_CURLY STATEMENT_STAR CLOSE_CURLY','CONDITIONAL_REP',9,'p_conditional_rep','main.py',493),
  ('seen_while_kwd -> empty','seen_while_kwd',1,'p_seen_while_kwd','main.py',500),
  ('seen_while_exp -> empty','seen_while_exp',1,'p_seen_while_exp','main.py',505),
  ('UNCONDITIONAL_REP -> FOR_KWD OPEN_PARENTHESIS ID seen_for_kwd EQUALS EXPRESSION seen_for_start_exp SEMI_COLON EXPRESSION seen_for_end_exp SEMI_COLON STATEMENT seen_for_incr_exp CLOSE_PARENTHESIS OPEN_CURLY STATEMENT_STAR CLOSE_CURLY','UNCONDITIONAL_REP',17,'p_unconditional_rep','main.py',510),
  ('seen_for_kwd -> empty','seen_for_kwd',1,'p_seen_for_kwd','main.py',523),
  ('seen_for_incr_exp -> empty','seen_for_incr_exp',1,'p_seen_for_incr_exp','main.py',529),
  ('seen_for_start_exp -> empty','seen_for_start_exp',1,'p_seen_for_start_exp','main.py',540),
  ('seen_for_end_exp -> empty','seen_for_end_exp',1,'p_seen_for_end_exp','main.py',545),
  ('empty -> <empty>','empty',0,'p_empty','main.py',558),
]
