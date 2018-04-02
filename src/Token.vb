
Option Explicit On
Option Strict On

Public Enum Token
    '' General
    UNKNOWN
    NUMBER
    IDENTIFIER

    '' Operators
    ADD_OPERATOR
    SUBTRACT_OPERATOR
    MULTIPLY_OPERATOR
    DIVIDE_OPERATOR
    MOD_OPERATOR
    NOT_OPERATOR
    EQUALS_OPERATOR

    '' Common Symbols
    OPEN_PARANTHESIS
    CLOSE_PARANTHESIS

    '' Type System
    VARIABLE_KEYWORD
    CONSTANT_KEYWORD
    AS_KEYWORD

    '' Terminators
    NEW_LINE
    EOF
    CLASS_KEYWORD
End Enum

