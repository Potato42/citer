# citer
An attempt to add iterators to C

citer allows you to do things like this:

```C
// Count to 100 by 2s

iterint num;
rangei range = {0, 100, 2};

FOREACH (rangei, num, range) {
    printf("%d\n", num); // 0 2 4 6 ... 96 98
}
```

Where the macro call `FOREACH (rangei, num, range)` calls `rangei_next(range)`

When I started this project I thought it would be a little nicer than this. 
I had forgotten that C doesn't allow function overloading like C++, so my 
plan was to overload a `next` function to accomidate the needs of any 
iterator.  Unfortunately, this isn't the case, which limits the power of 
iterators to some extent.  I'm not going to implement this in C++ because 
C++ has it's own iterator protocol that isn't much fun and quite different 
from Python's.

Anyway, I've currently made a few simple iterator types:  
 * `counti`: The equivalent of Python's itertools.count
 * `rangei`: The equivalent of Python's range
 * `repeati`: The equivalent to Python's itertools.repeat
 * `copyrepeati`: Same as `repeati` but gives you new copies of things

Doing things like `filter`, and anything else that acts on an iterator is 
annoyingly hard due to both the nature of C and the problem I described 
previously.  I still want to think about it a bit though.
