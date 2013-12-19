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

Vector
======

Otherwise known as dynamic arrays, as well as other names. Basically an array that grows as you
add things to it.

I decided not to go with the ubiquitous `push` or `push_back` since I'm not
interested in a queue for this. That is, I don't want push/pop semantics, I just want array
semantics.

It naively doubles the allocated size of the vector when it needs more memory. I'm not sure
what a better algorithm would be, but since I'm not too concerned about it growing very
large this shouldn't be an issue for my use case. (If someone has a good idea, submit it).

Hashtable
=========

This is the wildly popular associate array, or map, or hashmap. Basically it takes a string
key and associates it with some data. Any kind of data. It doesn't care about the data. Really.
Neither should it.

It uses the very basic Jenkins hash, though I may eventually replace that. Again, if you have
a really cool hash implementation for this, submit it. It's not crytographic, obviously, it just
needs to be really fast, implemented in pure C, and "perform". That is, it needs to result in
very few key collisions.
