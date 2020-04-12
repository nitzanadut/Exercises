**Cmd1 (1 Point)**


The PATH environment variable is used to locate the directory of linux commands.
We can simply change it to it's origianl value and use cat.


```diff
cmd1@pwnable:~$ ./cmd1 "cat f*"
sh: 1: cat: not found
cmd1@pwnable:~$ ./cmd1 "echo f*"
flag
cmd1@pwnable:~$ echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
cmd1@pwnable:~$ ./cmd1 "export PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin; cat f*"
mommy now I get what PATH environment is for :)

```