|             Symbol |                          First |                     Follow |
|--------------------|--------------------------------|----------------------------|
|               TERM |                      id num (  |           relop ; ) addop  |
|                 IF |                            if  | $ while id int } float if  |
|             FACTOR |                      id num (  |     addop ) ; relop mulop  |
| SIMPLE_EXPRESSION' |                 addop epsilon  |                 relop ; )  |
|       EXPRESSION_1 |                 relop epsilon  |                       ) ;  |
|              TERM' |                 mulop epsilon  |           addop ) ; relop  |
|     PRIMITIVE_TYPE |                     int float  |                        id  |
|              WHILE |                         while  | $ while id int } float if  |
|    STATEMENT_LIST' | while id float if int epsilon  |                         $  |
|        DECLARATION |                     int float  | $ while id int } float if  |
|  SIMPLE_EXPRESSION |                id num ( addop  |                 ) ; relop  |
|     STATEMENT_LIST |         while id int float if  |                         $  |
|         EXPRESSION |                id num ( addop  |                       ; )  |
|          STATEMENT |         int float if while id  | $ if float } int id while  |
|         ASSIGNMENT |                            id  | $ while id int } float if  |
|        METHOD_BODY |         while id int float if  |                         $  |
|               SIGN |                         addop  |                  ( num id  |
