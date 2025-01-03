|             Symbol |                          First |                     Follow |
|--------------------|--------------------------------|----------------------------|
|               TERM |                      id num (  |           relop ; ) addop  |
|                 IF |                            if  | while int } float if id $  |
|             FACTOR |                      id num (  |     ) ; relop addop mulop  |
| SIMPLE_EXPRESSION' |                 addop epsilon  |                 relop ; )  |
|              TERM' |                 mulop epsilon  |           ) ; relop addop  |
|  SIMPLE_EXPRESSION |                id num ( addop  |                 ) ; relop  |
|        METHOD_BODY |         while int float if id  |                         $  |
|     PRIMITIVE_TYPE |                     int float  |                        id  |
|    STATEMENT_LIST' | while float if id int epsilon  |                         $  |
|        DECLARATION |                     int float  | while int } float if id $  |
|              WHILE |                         while  | while int } float if id $  |
|     STATEMENT_LIST |         while int float if id  |                         $  |
|       EXPRESSION_1 |                 relop epsilon  |                       ) ;  |
|          STATEMENT |         int float if while id  | $ id if float } int while  |
|         ASSIGNMENT |                            id  | while int } float if id $  |
|               SIGN |                         addop  |                  ( num id  |
|         EXPRESSION |                addop ( id num  |                       ; )  |
