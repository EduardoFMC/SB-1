UM: EQU 1
ZERO: EQU 0
SECTION TEXT
INPUT OLD_DATA
LOAD OLD_DATA
IF UM
L1: DIV DOIS
STORE NEW_DATA
MULT DOIS
STORE TMP_DATA
LOAD OLD_DATA
SUB TMP_DATA
IF ZERO
STORE TMP_DATA
OUTPUT TMP_DATA
COPY NEW_DATA,OLD_DATA
LOAD OLD_DATA
JMPP L1
STOP
SECTION DATA
DOIS: CONST 2
OLD_DATA: SPACE
NEW_DATA: SPACE
TMP_DATA: SPACE