# csce434-pp2
## Operator Precedence
For the most part, I used precedence directives to tell bison explicitly when it
should shift when it came to expressions in order to keep those expression
productions relatively shallow.

Additionally, rather than capturing precedence in the grammar itself, I chose to
use precedence directives to resolve shift reduce conflicts surrounding if/else
and empty case/default statements.
## Resolving Shift/Reduce Conflicts
In some cases, it was not obvious how to rewrite the productions to avoid these
conflicts in an elegant way. For example, in the case of the Statement Block, I resolved the
shift/reduce errors by using 4 different productions that each captured one of
the combinations of Variable Declaration List plus Statement List. If there are
other productions that seem repetitive and look like they could be rewritten to
avoid the repition, it is because the way I wrote them initially caused such
conflicts.
