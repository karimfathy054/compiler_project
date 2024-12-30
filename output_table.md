|                                                                                              Stack | Curr Input Token |                                                    Action |
|----------------------------------------------------------------------------------------------------|------------------|-----------------------------------------------------------|
|                                                                                     $ METHOD_BODY  |              int |                            METHOD_BODY -> STATEMENT_LIST  |
|                                                                                  $ STATEMENT_LIST  |              int |              STATEMENT_LIST -> STATEMENT STATEMENT_LIST'  |
|                                                                       $ STATEMENT_LIST' STATEMENT  |              int |                                 STATEMENT -> DECLARATION  |
|                                                                     $ STATEMENT_LIST' DECLARATION  |              int |                       DECLARATION -> PRIMITIVE_TYPE id ;  |
|                                                             $ STATEMENT_LIST' ; id PRIMITIVE_TYPE  |              int |                                    PRIMITIVE_TYPE -> int  |
|                                                                        $ STATEMENT_LIST' ; id int  |              int |                                              Matched: int |
|                                                                            $ STATEMENT_LIST' ; id  |               id |                                               Matched: id |
|                                                                               $ STATEMENT_LIST' ;  |                ; |                                                Matched: ; |
|                                                                                 $ STATEMENT_LIST'  |               id |             STATEMENT_LIST' -> STATEMENT STATEMENT_LIST'  |
|                                                                       $ STATEMENT_LIST' STATEMENT  |               id |                                  STATEMENT -> ASSIGNMENT  |
|                                                                      $ STATEMENT_LIST' ASSIGNMENT  |               id |                     ASSIGNMENT -> id assign EXPRESSION ;  |
|                                                          $ STATEMENT_LIST' ; EXPRESSION assign id  |               id |                                               Matched: id |
|                                                             $ STATEMENT_LIST' ; EXPRESSION assign  |           assign |                                           Matched: assign |
|                                                                    $ STATEMENT_LIST' ; EXPRESSION  |              num |             EXPRESSION -> SIMPLE_EXPRESSION EXPRESSION_1  |
|                                                $ STATEMENT_LIST' ; EXPRESSION_1 SIMPLE_EXPRESSION  |              num |             SIMPLE_EXPRESSION -> TERM SIMPLE_EXPRESSION'  |
|                                          $ STATEMENT_LIST' ; EXPRESSION_1 SIMPLE_EXPRESSION' TERM  |              num |                                     TERM -> FACTOR TERM'  |
|                                  $ STATEMENT_LIST' ; EXPRESSION_1 SIMPLE_EXPRESSION' TERM' FACTOR  |              num |                                            FACTOR -> num  |
|                                     $ STATEMENT_LIST' ; EXPRESSION_1 SIMPLE_EXPRESSION' TERM' num  |              num |                                              Matched: num |
|                                                                               $ STATEMENT_LIST' ;  |                ; |                                                Matched: ; |
|                                                                                 $ STATEMENT_LIST'  |               if |             STATEMENT_LIST' -> STATEMENT STATEMENT_LIST'  |
|                                                                       $ STATEMENT_LIST' STATEMENT  |               if |                                          STATEMENT -> IF  |
|                                                                              $ STATEMENT_LIST' IF  |               if | IF -> if ( EXPRESSION ) { STATEMENT } else { STATEMENT }  |
|                              $ STATEMENT_LIST' } STATEMENT { else } STATEMENT { ) EXPRESSION ( if  |               if |                                               Matched: if |
|                                 $ STATEMENT_LIST' } STATEMENT { else } STATEMENT { ) EXPRESSION (  |                ( |                                                Matched: ( |
|                                   $ STATEMENT_LIST' } STATEMENT { else } STATEMENT { ) EXPRESSION  |               id |             EXPRESSION -> SIMPLE_EXPRESSION EXPRESSION_1  |
|               $ STATEMENT_LIST' } STATEMENT { else } STATEMENT { ) EXPRESSION_1 SIMPLE_EXPRESSION  |               id |             SIMPLE_EXPRESSION -> TERM SIMPLE_EXPRESSION'  |
|         $ STATEMENT_LIST' } STATEMENT { else } STATEMENT { ) EXPRESSION_1 SIMPLE_EXPRESSION' TERM  |               id |                                     TERM -> FACTOR TERM'  |
| $ STATEMENT_LIST' } STATEMENT { else } STATEMENT { ) EXPRESSION_1 SIMPLE_EXPRESSION' TERM' FACTOR  |               id |                                             FACTOR -> id  |
|     $ STATEMENT_LIST' } STATEMENT { else } STATEMENT { ) EXPRESSION_1 SIMPLE_EXPRESSION' TERM' id  |               id |                                               Matched: id |
|                                 $ STATEMENT_LIST' } STATEMENT { else } STATEMENT { ) EXPRESSION_1  |            relop |                  EXPRESSION_1 -> relop SIMPLE_EXPRESSION  |
|                      $ STATEMENT_LIST' } STATEMENT { else } STATEMENT { ) SIMPLE_EXPRESSION relop  |            relop |                                            Matched: relop |
|                            $ STATEMENT_LIST' } STATEMENT { else } STATEMENT { ) SIMPLE_EXPRESSION  |              num |             SIMPLE_EXPRESSION -> TERM SIMPLE_EXPRESSION'  |
|                      $ STATEMENT_LIST' } STATEMENT { else } STATEMENT { ) SIMPLE_EXPRESSION' TERM  |              num |                                     TERM -> FACTOR TERM'  |
|              $ STATEMENT_LIST' } STATEMENT { else } STATEMENT { ) SIMPLE_EXPRESSION' TERM' FACTOR  |              num |                                            FACTOR -> num  |
|                 $ STATEMENT_LIST' } STATEMENT { else } STATEMENT { ) SIMPLE_EXPRESSION' TERM' num  |              num |                                              Matched: num |
|                                              $ STATEMENT_LIST' } STATEMENT { else } STATEMENT { )  |                ) |                                                Matched: ) |
|                                                $ STATEMENT_LIST' } STATEMENT { else } STATEMENT {  |                { |                                                Matched: { |
|                                                  $ STATEMENT_LIST' } STATEMENT { else } STATEMENT  |               id |                                  STATEMENT -> ASSIGNMENT  |
|                                                 $ STATEMENT_LIST' } STATEMENT { else } ASSIGNMENT  |               id |                     ASSIGNMENT -> id assign EXPRESSION ;  |
|                                     $ STATEMENT_LIST' } STATEMENT { else } ; EXPRESSION assign id  |               id |                                               Matched: id |
|                                        $ STATEMENT_LIST' } STATEMENT { else } ; EXPRESSION assign  |           assign |                                           Matched: assign |
|                                               $ STATEMENT_LIST' } STATEMENT { else } ; EXPRESSION  |              num |             EXPRESSION -> SIMPLE_EXPRESSION EXPRESSION_1  |
|                           $ STATEMENT_LIST' } STATEMENT { else } ; EXPRESSION_1 SIMPLE_EXPRESSION  |              num |             SIMPLE_EXPRESSION -> TERM SIMPLE_EXPRESSION'  |
|                     $ STATEMENT_LIST' } STATEMENT { else } ; EXPRESSION_1 SIMPLE_EXPRESSION' TERM  |              num |                                     TERM -> FACTOR TERM'  |
|             $ STATEMENT_LIST' } STATEMENT { else } ; EXPRESSION_1 SIMPLE_EXPRESSION' TERM' FACTOR  |              num |                                            FACTOR -> num  |
|                $ STATEMENT_LIST' } STATEMENT { else } ; EXPRESSION_1 SIMPLE_EXPRESSION' TERM' num  |              num |                                              Matched: num |
|                                                          $ STATEMENT_LIST' } STATEMENT { else } ;  |                ; |                                                Matched: ; |
|                                                            $ STATEMENT_LIST' } STATEMENT { else }  |                } |                                                Matched: } |
|                                                              $ STATEMENT_LIST' } STATEMENT { else  |                $ |                       Error: token else is added to input |
|                                                                   $ STATEMENT_LIST' } STATEMENT {  |                $ |                          Error: token { is added to input |
|                                                                     $ STATEMENT_LIST' } STATEMENT  |                $ |                                    Error: awaiting follow |
|                                                                               $ STATEMENT_LIST' }  |                $ |                          Error: token } is added to input |
|                                                                                                 $  |                $ |                                                Matched: $ |
