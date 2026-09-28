/*
what went wrong - WA
Assumed the problem had to due with stack limit and AtCoder not compiling with enough stack size
The several ways to test this were not successful at testing it. 
The problem was with if we dfs at an even vs odd degree root. -> Assumed the dfs started at a leaf, but not always the case
moral of the story - hard to test problems that require a large stack size, but it shouldn't be the problem for most online judges
*/