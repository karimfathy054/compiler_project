|             Symbol |                          First |                     Follow |
|--------------------|--------------------------------|----------------------------|
|                 IF |                            if  | if while id $ int float }  |
| SIMPLE_EXPRESSION' |                 addop epsilon  |                 ; relop )  |
|               TERM |                      id num (  |           ; relop ) addop  |
|       EXPRESSION_1 |                 relop epsilon  |                       ; )  |
|              TERM' |                 mulop epsilon  |           ; addop ) relop  |
|     STATEMENT_LIST |         if while id int float  |                         $  |
|              WHILE |                         while  | if while id $ int float }  |
|         EXPRESSION |                addop id num (  |                       ; )  |
|             FACTOR |                      id num (  |     ; addop ) relop mulop  |
|        DECLARATION |                     int float  | if while id $ int float }  |
|    STATEMENT_LIST' | if while id int float epsilon  |                         $  |
|  SIMPLE_EXPRESSION |                id num ( addop  |                 ; ) relop  |
|     PRIMITIVE_TYPE |                     int float  |                        id  |
|          STATEMENT |         int float if while id  | } float int $ id while if  |
|               SIGN |                         addop  |                  ( num id  |
|         ASSIGNMENT |                            id  | if while id $ int float }  |
|        METHOD_BODY |         if while id int float  |                         $  |
