[![42 Profile Card](https://1337-readme.vercel.app/api/profile?cursus=42cursus&login=zoulhafi)](https://github.com/mohouyizme/1337-readme)
# Installation And Execution
make  
./21sh

# 1337-42-21sh
You’ll have to start from your minishell and make it stronger to get little by
littler closer to a real functionnal shell. You’ll add couple of features such as
multi-commande management, redirections as well as line edition that will allow you to
use arrows for example.

# Introduction
Thanks to the Minishell project, you discovered a part of what is behind the scene of a
shell, such as the one you use everyday. And more specifically the process’ synchronisation creation with functions like fork and wait.
The 21sh project will make you go further by adding, amoungst other things, interprocess communication using pipes.
You’ll discover, or rediscover if you worked on the ft_select project, termcaps. This
library will allow you to add to your shell a line edition feature. You’ll then be able to
edit a typo made on your command without having to retype it completely as well as
repeat a previous command using history. Of course you’ll have to code those features.
Good news is termcaps will help you do it, bad news is it’ll not do it for you!

# Objectives
Unix programmation is great, The school’s 3 shell projects allow you to discover a big
part of the system’s API and it can only be good for you.
However, the shell projects are commands interpreter above all and initiate you to a
very important part of IT: compilation. Interpreter are programs that read and execute
other programs, unlike compilers which translate other programs into other langages.
Interpreters and compilers have more in common than they have differences though:
whether it comes to executing or translating a program, first one need to understand the
program itself, and be able to detect and reject malformed programs.
You probably know this already, but the set of commands we can send to a shell form
a langage. This langage has lexical, syntactic and semantics rules, that will have to be
respected by your 21sh by going through a set of very precise steps well documented on
the internet. For example the “2.10 Shell Grammar” section of this document.
The key to a successful 21sh, and 42sh later on is a clear and well managed code
organisation. Be asured that a simple space based split on your command line will not
do the trick here. To avoid losing time, consider this solution as a one way ticket to
disaster.
Here are couple of key words that i suggest you to properly understand: “lexical
analysis”, “lexer”, “syntactic analysis”, “parser”, “semantics analysis”,“interpreter”, and
of course “abstract syntax tree” (or “AST”).

# For more informations
Read : https://github.com/oulhafiane/1337-42-21sh/blob/master/21sh.en.pdf
