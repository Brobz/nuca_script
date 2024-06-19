enum OPCode
{
    /*/ OPCOODE translation for the VM  /*/
    /*/ =  /*/ SINGLE_EQUALS,           /*/   0   /*/
    /*/ +  /*/ PLUS,                    /*/   1   /*/
    /*/ =  /*/ MINUS,                   /*/   2   /*/
    /*/ *  /*/ MULT,                    /*/   3   /*/
    /*/ /  /*/ DIV,                     /*/   4   /*/
    /*/ == /*/ DOUBLE_EQUALS,           /*/   5   /*/
    /*/ >  /*/ GREATER_THAN,            /*/   6   /*/
    /*/ <  /*/ LESSER_THAN,             /*/   7   /*/
    /*/ >= /*/ GREATER_THAN_OR_EQ_TO,   /*/   8   /*/
    /*/ <= /*/ LESSER_THAN_OR_EQ_TO,    /*/   9   /*/
    /*/ && /*/ AND,                     /*/  10   /*/
    /*/ || /*/ OR,                      /*/  11   /*/
    /*/ != /*/ NOT_EQUAL_TO,            /*/  12   /*/
    /*/ !  /*/ NOT,                     /*/  13   /*/
    ARR_ACCESS,                         /*/  14   /*/
    ARR_BNDS,                           /*/  15  /*/
    TMP_RESET,                          /*/  16  /*/
    USNG_AS,                            /*/  17  /*/
    OBJ_INST,                           /*/  18  /*/
    OBJ_READ,                           /*/  19  /*/
    OBJ_WRITE,                          /*/  20  /*/
    ERA,                                /*/  21  /*/
    PARAM,                              /*/  22  /*/
    GOSUB,                              /*/  23  /*/
    OBJ_GOSUB,                          /*/  24  /*/
    READ,                               /*/  25  /*/
    PRNTBFFR,                           /*/  26  /*/
    PRNT,                               /*/  27  /*/
    PRNTLN,                             /*/  28  /*/
    STOX,                               /*/  29  /*/
    SUBSTR,                             /*/  30  /*/
    STRLEN,                             /*/  31  /*/
    RANDINT,                            /*/  32  /*/
    F_OPEN,                             /*/  33  /*/
    F_WRITE,                            /*/  34  /*/
    GOTO,                               /*/  35  /*/
    GOTOF,                              /*/  36  /*/
    ENDFNC,                             /*/  37  /*/
    END                                 /*/  38  /*/
};