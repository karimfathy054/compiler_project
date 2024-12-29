|                                    Stack | Curr Input Token |                        Action |
|------------------------------------------|------------------|-------------------------------|
|                                 $ bexpr  |                ( |        bexpr -> bterm bexpr'  |
|                          $ bexpr' bterm  |                ( |      bterm -> bfactor bterm'  |
|                 $ bexpr' bterm' bfactor  |                ( |         bfactor -> ( bexpr )  |
|               $ bexpr' bterm' ) bexpr (  |                ( |                    Matched: ( |
|                 $ bexpr' bterm' ) bexpr  |             true |        bexpr -> bterm bexpr'  |
|          $ bexpr' bterm' ) bexpr' bterm  |             true |      bterm -> bfactor bterm'  |
| $ bexpr' bterm' ) bexpr' bterm' bfactor  |             true |              bfactor -> true  |
|    $ bexpr' bterm' ) bexpr' bterm' true  |             true |                 Matched: true |
|                $ bexpr' bterm' ) bexpr'  |               or |    bexpr' -> or bterm bexpr'  |
|       $ bexpr' bterm' ) bexpr' bterm or  |               or |                   Matched: or |
|          $ bexpr' bterm' ) bexpr' bterm  |            false |      bterm -> bfactor bterm'  |
| $ bexpr' bterm' ) bexpr' bterm' bfactor  |            false |             bfactor -> false  |
|   $ bexpr' bterm' ) bexpr' bterm' false  |            false |                Matched: false |
|                       $ bexpr' bterm' )  |                ) |                    Matched: ) |
|                         $ bexpr' bterm'  |              and | bterm' -> and bfactor bterm'  |
|             $ bexpr' bterm' bfactor and  |              and |                  Matched: and |
|                 $ bexpr' bterm' bfactor  |            false |             bfactor -> false  |
|                   $ bexpr' bterm' false  |            false |                Matched: false |
|                                $ bexpr'  |               or |    bexpr' -> or bterm bexpr'  |
|                       $ bexpr' bterm or  |               or |                   Matched: or |
|                          $ bexpr' bterm  |             true |      bterm -> bfactor bterm'  |
|                 $ bexpr' bterm' bfactor  |             true |              bfactor -> true  |
|                    $ bexpr' bterm' true  |             true |                 Matched: true |
|                                       $  |                $ |                    Matched: $ |
