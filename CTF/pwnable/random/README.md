**Random (1 Point)**


**NEVER USE RAND()!**
it's seed is never random, a simple c program can exploit this.


rand.c:

```diff
#include <stdio.h>

int main() {
	printf("%d\n", rand());
	return 0;
}
```


```diff
$ ./rand
1804289383
$ python
Python 2.7.17 (default, Nov  7 2019, 10:07:09) 
[GCC 7.4.0] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> 0xdeadbeef ^ 1804289383
3039230856
>>> 
[4]+  Stopped                 python

```


```diff
$ ./random
3039230856
Good!
Mommy, I thought libc random is unpredictable...

```