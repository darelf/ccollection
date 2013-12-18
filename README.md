Some collections for C
======================

I'm just collecting these collection functions for other projects I do.

Much of the hashtable implementation came from http://c.learncodethehardway.org
so credit should go to them for many of the ideas behind the hashtable implementation.

The vector implementation is part mine with some ideas from this gist http://gist.github.com/EmilHernvall/953968
So again, credit for that inspiration.

I haven't really done a unified header or anything. In the tests directory there is a single
`test.c` that just tests some basic functions. I've run it against valgrind leak-check and it
seems to be happy that no memory is leaking.

I don't really have any good benchmarks or anything. The implementations are very straightforward,
so I'm certain there will be optimizations that I could do.

If you have any ideas, want to add features or new collections, don't hesitate.

