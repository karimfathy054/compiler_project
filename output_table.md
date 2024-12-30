|                                                                           Stack | Curr Input Token |                                          Action |
|---------------------------------------------------------------------------------|------------------|-------------------------------------------------|
|                                                                  $ METHOD_BODY  |              int |                  METHOD_BODY -> STATEMENT_LIST  |
|                                                               $ STATEMENT_LIST  |              int |    STATEMENT_LIST -> STATEMENT STATEMENT_LIST'  |
|                                                    $ STATEMENT_LIST' STATEMENT  |              int |                       STATEMENT -> DECLARATION  |
|                                                  $ STATEMENT_LIST' DECLARATION  |              int |             DECLARATION -> PRIMITIVE_TYPE id ;  |
|                                          $ STATEMENT_LIST' ; id PRIMITIVE_TYPE  |              int |                          PRIMITIVE_TYPE -> int  |
|                                                     $ STATEMENT_LIST' ; id int  |              int |                                    Matched: int |
|                                                         $ STATEMENT_LIST' ; id  |               id |                                     Matched: id |
|                                                            $ STATEMENT_LIST' ;  |                ; |                                      Matched: ; |
|                                                              $ STATEMENT_LIST'  |            float |   STATEMENT_LIST' -> STATEMENT STATEMENT_LIST'  |
|                                                    $ STATEMENT_LIST' STATEMENT  |            float |                       STATEMENT -> DECLARATION  |
|                                                  $ STATEMENT_LIST' DECLARATION  |            float |             DECLARATION -> PRIMITIVE_TYPE id ;  |
|                                          $ STATEMENT_LIST' ; id PRIMITIVE_TYPE  |            float |                        PRIMITIVE_TYPE -> float  |
|                                                   $ STATEMENT_LIST' ; id float  |            float |                                  Matched: float |
|                                                         $ STATEMENT_LIST' ; id  |               id |                                     Matched: id |
|                                                            $ STATEMENT_LIST' ;  |                ; |                                      Matched: ; |
|                                                              $ STATEMENT_LIST'  |              int |   STATEMENT_LIST' -> STATEMENT STATEMENT_LIST'  |
|                                                    $ STATEMENT_LIST' STATEMENT  |              int |                       STATEMENT -> DECLARATION  |
|                                                  $ STATEMENT_LIST' DECLARATION  |              int |             DECLARATION -> PRIMITIVE_TYPE id ;  |
|                                          $ STATEMENT_LIST' ; id PRIMITIVE_TYPE  |              int |                          PRIMITIVE_TYPE -> int  |
|                                                     $ STATEMENT_LIST' ; id int  |              int |                                    Matched: int |
|                                                         $ STATEMENT_LIST' ; id  |               id |                                     Matched: id |
|                                                            $ STATEMENT_LIST' ;  |                ; |                                      Matched: ; |
|                                                              $ STATEMENT_LIST'  |            while |   STATEMENT_LIST' -> STATEMENT STATEMENT_LIST'  |
|                                                    $ STATEMENT_LIST' STATEMENT  |            while |                             STATEMENT -> WHILE  |
|                                                        $ STATEMENT_LIST' WHILE  |            while |    WHILE -> while ( EXPRESSION ) { STATEMENT }  |
|                           $ STATEMENT_LIST' } STATEMENT { ) EXPRESSION ( while  |            while |                                  Matched: while |
|                                 $ STATEMENT_LIST' } STATEMENT { ) EXPRESSION (  |                ( |                                      Matched: ( |
|                                   $ STATEMENT_LIST' } STATEMENT { ) EXPRESSION  |               id |   EXPRESSION -> SIMPLE_EXPRESSION EXPRESSION_1  |
|               $ STATEMENT_LIST' } STATEMENT { ) EXPRESSION_1 SIMPLE_EXPRESSION  |               id |   SIMPLE_EXPRESSION -> TERM SIMPLE_EXPRESSION'  |
|         $ STATEMENT_LIST' } STATEMENT { ) EXPRESSION_1 SIMPLE_EXPRESSION' TERM  |               id |                           TERM -> FACTOR TERM'  |
| $ STATEMENT_LIST' } STATEMENT { ) EXPRESSION_1 SIMPLE_EXPRESSION' TERM' FACTOR  |               id |                                   FACTOR -> id  |
|     $ STATEMENT_LIST' } STATEMENT { ) EXPRESSION_1 SIMPLE_EXPRESSION' TERM' id  |               id |                                     Matched: id |
|        $ STATEMENT_LIST' } STATEMENT { ) EXPRESSION_1 SIMPLE_EXPRESSION' TERM'  |            relop |                                     TERM' -> \L |
|              $ STATEMENT_LIST' } STATEMENT { ) EXPRESSION_1 SIMPLE_EXPRESSION'  |            relop |                        SIMPLE_EXPRESSION' -> \L |
|                                 $ STATEMENT_LIST' } STATEMENT { ) EXPRESSION_1  |            relop |        EXPRESSION_1 -> relop SIMPLE_EXPRESSION  |
|                      $ STATEMENT_LIST' } STATEMENT { ) SIMPLE_EXPRESSION relop  |            relop |                                  Matched: relop |
|                            $ STATEMENT_LIST' } STATEMENT { ) SIMPLE_EXPRESSION  |               id |   SIMPLE_EXPRESSION -> TERM SIMPLE_EXPRESSION'  |
|                      $ STATEMENT_LIST' } STATEMENT { ) SIMPLE_EXPRESSION' TERM  |               id |                           TERM -> FACTOR TERM'  |
|              $ STATEMENT_LIST' } STATEMENT { ) SIMPLE_EXPRESSION' TERM' FACTOR  |               id |                                   FACTOR -> id  |
|                  $ STATEMENT_LIST' } STATEMENT { ) SIMPLE_EXPRESSION' TERM' id  |               id |                                     Matched: id |
|                     $ STATEMENT_LIST' } STATEMENT { ) SIMPLE_EXPRESSION' TERM'  |                ) |                                     TERM' -> \L |
|                           $ STATEMENT_LIST' } STATEMENT { ) SIMPLE_EXPRESSION'  |                ) |                        SIMPLE_EXPRESSION' -> \L |
|                                              $ STATEMENT_LIST' } STATEMENT { )  |                ) |                                      Matched: ) |
|                                                $ STATEMENT_LIST' } STATEMENT {  |                { |                                      Matched: { |
|                                                  $ STATEMENT_LIST' } STATEMENT  |            float |                       STATEMENT -> DECLARATION  |
|                                                $ STATEMENT_LIST' } DECLARATION  |            float |             DECLARATION -> PRIMITIVE_TYPE id ;  |
|                                        $ STATEMENT_LIST' } ; id PRIMITIVE_TYPE  |            float |                        PRIMITIVE_TYPE -> float  |
|                                                 $ STATEMENT_LIST' } ; id float  |            float |                                  Matched: float |
|                                                       $ STATEMENT_LIST' } ; id  |               id |                                     Matched: id |
|                                                          $ STATEMENT_LIST' } ;  |                ; |                                      Matched: ; |
|                                                            $ STATEMENT_LIST' }  |                } |                                      Matched: } |
|                                                              $ STATEMENT_LIST'  |               id |   STATEMENT_LIST' -> STATEMENT STATEMENT_LIST'  |
|                                                    $ STATEMENT_LIST' STATEMENT  |               id |                        STATEMENT -> ASSIGNMENT  |
|                                                   $ STATEMENT_LIST' ASSIGNMENT  |               id |           ASSIGNMENT -> id assign EXPRESSION ;  |
|                                       $ STATEMENT_LIST' ; EXPRESSION assign id  |               id |                                     Matched: id |
|                                          $ STATEMENT_LIST' ; EXPRESSION assign  |               id |         Error: token 'assign' is added to input |
|                                                 $ STATEMENT_LIST' ; EXPRESSION  |               id |   EXPRESSION -> SIMPLE_EXPRESSION EXPRESSION_1  |
|                             $ STATEMENT_LIST' ; EXPRESSION_1 SIMPLE_EXPRESSION  |               id |   SIMPLE_EXPRESSION -> TERM SIMPLE_EXPRESSION'  |
|                       $ STATEMENT_LIST' ; EXPRESSION_1 SIMPLE_EXPRESSION' TERM  |               id |                           TERM -> FACTOR TERM'  |
|               $ STATEMENT_LIST' ; EXPRESSION_1 SIMPLE_EXPRESSION' TERM' FACTOR  |               id |                                   FACTOR -> id  |
|                   $ STATEMENT_LIST' ; EXPRESSION_1 SIMPLE_EXPRESSION' TERM' id  |               id |                                     Matched: id |
|                      $ STATEMENT_LIST' ; EXPRESSION_1 SIMPLE_EXPRESSION' TERM'  |           assign | Error: token mismatch ( skipping token assign ) |
|                      $ STATEMENT_LIST' ; EXPRESSION_1 SIMPLE_EXPRESSION' TERM'  |               id |     Error: token mismatch ( skipping token id ) |
|                      $ STATEMENT_LIST' ; EXPRESSION_1 SIMPLE_EXPRESSION' TERM'  |            mulop |                    TERM' -> mulop FACTOR TERM'  |
|         $ STATEMENT_LIST' ; EXPRESSION_1 SIMPLE_EXPRESSION' TERM' FACTOR mulop  |            mulop |                                  Matched: mulop |
|               $ STATEMENT_LIST' ; EXPRESSION_1 SIMPLE_EXPRESSION' TERM' FACTOR  |               id |                                   FACTOR -> id  |
|                   $ STATEMENT_LIST' ; EXPRESSION_1 SIMPLE_EXPRESSION' TERM' id  |               id |                                     Matched: id |
|                      $ STATEMENT_LIST' ; EXPRESSION_1 SIMPLE_EXPRESSION' TERM'  |                ; |                                     TERM' -> \L |
|                            $ STATEMENT_LIST' ; EXPRESSION_1 SIMPLE_EXPRESSION'  |                ; |                        SIMPLE_EXPRESSION' -> \L |
|                                               $ STATEMENT_LIST' ; EXPRESSION_1  |                ; |                              EXPRESSION_1 -> \L |
|                                                            $ STATEMENT_LIST' ;  |                ; |                                      Matched: ; |
|                                                              $ STATEMENT_LIST'  |                $ |                           STATEMENT_LIST' -> \L |
|                                                                              $  |                $ |                                      Matched: $ |
