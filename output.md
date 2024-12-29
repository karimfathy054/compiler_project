|                            Symbol | Curr Input Token |                     Action |
|-----------------------------------|------------------|----------------------------|
|                            $bexpr |                ( |       bexpr -> btermbexpr' |
|                      $bexpr'bterm |                ( |     bterm -> bfactorbterm' |
|              $bexpr'bterm'bfactor |                ( |         bfactor -> (bexpr) |
|              $bexpr'bterm')bexpr( |                ( |                 Matched: ( |
|               $bexpr'bterm')bexpr |             true |       bexpr -> btermbexpr' |
|         $bexpr'bterm')bexpr'bterm |             true |     bterm -> bfactorbterm' |
| $bexpr'bterm')bexpr'bterm'bfactor |             true |            bfactor -> true |
|    $bexpr'bterm')bexpr'bterm'true |             true |              Matched: true |
|              $bexpr'bterm')bexpr' |               or |    bexpr' -> orbtermbexpr' |
|       $bexpr'bterm')bexpr'btermor |               or |                Matched: or |
|         $bexpr'bterm')bexpr'bterm |            false |     bterm -> bfactorbterm' |
| $bexpr'bterm')bexpr'bterm'bfactor |            false |           bfactor -> false |
|   $bexpr'bterm')bexpr'bterm'false |            false |             Matched: false |
|                    $bexpr'bterm') |                ) |                 Matched: ) |
|                     $bexpr'bterm' |              and | bterm' -> andbfactorbterm' |
|           $bexpr'bterm'bfactorand |              and |               Matched: and |
|              $bexpr'bterm'bfactor |            false |           bfactor -> false |
|                $bexpr'bterm'false |            false |             Matched: false |
|                           $bexpr' |               or |    bexpr' -> orbtermbexpr' |
|                    $bexpr'btermor |               or |                Matched: or |
|                      $bexpr'bterm |             true |     bterm -> bfactorbterm' |
|              $bexpr'bterm'bfactor |             true |            bfactor -> true |
|                 $bexpr'bterm'true |             true |              Matched: true |
|                                 $ |                $ |                 Matched: $ |
