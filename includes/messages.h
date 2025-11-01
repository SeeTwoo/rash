#ifndef MESSAGES_H
# define MESSAGES_H

//msg hd
# define ERR_HD "\x1b[1;31m - tshoo - \x1b[0m"
# define WARN_HD "\x1b[38;2;255;255;0m - tshoo - \x1b[0m"

//syntax warning
# define UNCLOSED_PIPE "unclosed pipe"
# define REDIR_FILE_NAME "needs a file name to redirect"
# define UNKNOWN_TOK "unknown token"

//command not found (yeah it is obvious but i feel like I needed an explanation)
# define CMD_FND "command not found"

//alias messages
# define NEED_EQUAL "need a '=' to create an alias : <pattern>=<replace>"
# define NEED_PATTERN "need a pattern to search : <pattern>=<replace>"
# define NOT_ALIASED "malloc failed, an alias was not applied"

//unalias messages
# define UNAL_USAGE "usage : unalias <pattern> ... OR unalias -a"

//variable assignation messages
# define NEED_NAME "need a variable name to create a variable"

//cd 
# define BROKEN_ENV "malloc failed, the environment is now missing variables and may behave weirdly"
# define TOO_MANY "too many arguments"
# define HOME_NOT_SET "HOME not set"
# define OLDPWD_NOT_SET "OLDPWD not set"

//expansion
# define EXP_FAILED_MALLOC "malloc failed, a variable was not expanded"

//init env
# define NO_ENV "malloc failed, environment may be missing or incomplete"

//exec config file
# define NO_RC "tshoorc will not be run"

//malloc
#define ERR_MALLOC "malloc failed"

//home not set
#define NO_HOME "HOME variable not set"

#endif
