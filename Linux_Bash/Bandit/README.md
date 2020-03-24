**Level 0**

Just a simple ssh with the user credentials
```diff
$ ssh bandit0@bandit.labs.overthewire.org -p 2220
$ bandit0
```

**From now on, I won't specify the starting ssh of every level**

**Level 0->1**

A simple file in the current directory, cat does the trick
```diff
$ ls
$ cat readme
```

**Level 1->2**

We needed to specify - is a file and not the start of a flag.
.: Current directory
```diff
$ ls
$ cat ./-
```

**Level 2->3**

We needed to tell cat the spaces are in the filename and not starting another argument, Quotes do the trick
```diff
$ ls
$ cat "spaces in this filename"
```

**Level 3->4**

I saw ls outputted nothing when executed in "inhere", so I thought we might have a hidden file. ls -la outputs all the files in the current directory.
```diff
$ ls
$ cd inhere
$ ls
$ ls -la
$ cat .hidden
```

**Level 4->5**

When looking through the files with the file command, i saw all of them were labeled as data and only one as ASCII.
```diff
$ ls
$ cd inhere
$ find . | xargs file | grep ASCII
```

**From now on, I won't specify trivial commands, like ls or cd inhere on the start of every level**

**Level 5->6**

Same as last one, with the -size flag to specify the size and the -not -executable to specify we *don't* want an executable.
```diff
$ find . -size 1033c -not -executable | xargs file | grep ASCII
$ cat maybehere07/.file2
```

**Level 6->7**

-user for owner and -group for group, redirecting stderr into /dev/null to get rid of the ugly error messages and piping to cat to cat the password all in one line
```diff
$ find / -user bandit7 -group bandit6 -size 33c 2>&1 | grep -v "Permission denied" | grep -v "No such" | xargs cat
```

**Level 7->8**

Piping into grep to get the line that contains millionth
```diff
$ cat data.txt | grep millionth
```

**Level 8->9**

I saw the "Commands you may need" had uniq, which i didn't know, I searched up it's man and used it like so
```diff
$ sort data.txt | uniq -u
```

**Level 9->10**

Using strings and grep.
```diff
$ strings data.txt | grep "="
```

**Level 10->11**

Using base64 --deocde.
```diff
$ base64 --decode data.txt 
```

**Level 11->12**

Using tr, a + 13 = n.
This is a basic rot13 cipher, very common in crypto CTFs.
```diff
$ cat data.txt | tr [a-zA-Z] [n-za-mN-ZA-M]
```

**Level 12->13**

A repetitive level, just used the file command and bzip, gzip -d and tar to unzip the file.
```diff
$ xxd -r data.txt out
$ file out
$ mv out out.gz
$ gzip -d out.gz
...
$ tar xf data6.tar
$ ls
$ file data8.bin
$ mv data8.bin data8.gz
$ gzip -d data8.gz
$ ls
$ file data8
$ cat data8
The password is...
```

**Level 13->14**

I found the sshkey file on the server, and tried to ssh with the -i flag like usual, then it dawned on me I am on bandit.labs... 
```diff
$ ssh -i sshkey.private bandit14@bandit.labs.overthewire.org -p 2220
$ ssh -i sshkey.private bandit14@localhost
```

**Level 14->15**

From solving this ctf in the past I remembered the password for every level is under /etc/bandit_pass. Using telnet to submit the password.
```diff
$ cat /etc/bandit_pass/bandit14
$ telnet localhost 30000
```

**Level 15->16**

In the commands you may need they give you openssl, s_client and -ign_eof.
ign_eof is used to keep the shell open and s_client is a ssl/tls client program.
```diff
$ cat /etc/bandit_pass/bandit15 | openssl s_client -ign_eof -connect localhost:30001
```

**Level 16->17**

After countless tries of trying to do a fancy for loop telnet one liner, I saw nmap in the commands you may need...
```diff
$ for((i=31000; i<=32000; i+=1)); do cat /etc/bandit_pass/bandit16 | openssl s_client -ign_eof -connect localhost:$i 2>/dev/null; done
$ nmap localhost -p 31000-32000
$ cat /etc/bandit_pass/bandit16 | openssl s_client -ign_eof -connect localhost:31518
$ cat /etc/bandit_pass/bandit16 | openssl s_client -ign_eof -connect localhost:31790
```

**Level 17->18**

basic diff.
```diff
$ diff passwords.new passwords.old
```

**Level 18->19**

You can execute a command on the remote shell with ssh that will run before .bashrc :)
```diff
$ ssh bandit18@bandit.labs.overthewire.org -p 2220 cat readme
```

**Level 19->20**

Execute the file with cat
```diff
$ ./bandit20-do
$ ./bandit20-do cat /etc/bandit_pass/bandit20
```
