test: collection_test
	./collection_test

u_test: unicode_test
	./unicode_test

collection_test: test.c
	gcc -o collection_test test.c ../src/libccollection.a -I../src

unicode_test: unicode_test.c
	gcc -o unicode_test unicode_test.c ../src/libccollection.a -I../src `pkg-config --cflags --libs icu-io icu-uc`

clean:
	rm -rf collection_test unicode_test
