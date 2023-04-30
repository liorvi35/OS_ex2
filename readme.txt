Operation Systems - Assignment 2

by Yoad Tamar&Lior Vinman.

Description:

PART A:
Tool 1: cmp:

the tool will compare two files, and return “0” if they are equal, and “1” if not 
(return an INT).
The tool will support -v flag for verbose output. By this we mean that the tool will print “equal” or
“distinct”, in addition to returning the int value.
The toll will support -i flag, that mean “ignore case” so “AAA” and “aaa” meaning equals
usage: cmp <file1> <file2> -v.


Tool 2: copy:

the tool will copy a file to another place and/or name.
The tool will return “0” on success, or “1” on failure (return an INT).
The tool will create a new file, if it does not exist, but it will not overwrite a file if it do exist.
the tool will support -v flag, that will output “success” if the file is copied, or “target file exist” if this is
the case, or “general failure” on some other problem (in addition to the returned INT value).
The tool will support -f flag (that means force), that allows to overwrite the target file
usage copy <file1> <file2> -v.


PART B:
codecA: 

A coding\shared library. This library covert all lower case chars to upper case, and all upper case to lower case. All other chars will remain unchanged.
Also 

codecB:

A coding\shared library. This library convert all chars to the 3-rd next char.
(adding a number of 3 to the ascii val).


Notes: 
Both libraries support “encode” and “decode” methods. 
Usage : encode/decode <codec> <message>.

Part C:
stshell:

A small shell program that supports the following features:

1) Be able to run CMD tools that exist on system (by fork + exec + wait).

2) Be able to stop running tool by pressing Ctrl+c, but not killing the shell itself (by signal handler).

3) Be able to redirect output with “>” and “>>”, and allow piping with “|”, at least for 2 following.

pipes. For example command like this should be supported “ls -l | grep aaa | wc”
4) be able to stop itself by “exit” command.


























