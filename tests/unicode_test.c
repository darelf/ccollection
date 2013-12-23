#include <stdio.h>
#include <assert.h>
#include "cvector.h"
#include "chashtable.h"

#include <unicode/utypes.h>
#include <unicode/uchar.h>
#include <unicode/ustring.h>
#include <unicode/ustdio.h>
#include <unicode/uclean.h>

/*
 * It may be worth mentioning that the actual hashtable implementation
 * doesn't really care about the encoding, but if you use Unicode strings
 * for the keys, then you probably want to use a string compare function
 * that works with Unicode. This is that example.
 */
// Compare unicode strings...
int mycompare(void * a, void * b) {
  return u_strcmp(a, b);
}

int main(void) {

  printf("\nTesting HashTable with Unicode Keys\n");
  
  // Let's use the default bucket size
  hashtable * ht = ch_create_full(64, mycompare);
  assert( ht->size == 64 );
  
  U_STRING_DECL(key1, "John", 4);
  U_STRING_INIT(key1, "John", 4);
  ch_set(ht, key1, "Mar");
  
  U_STRING_DECL(key2, "Jahn", 4);
  U_STRING_INIT(key2, "Jahn", 4);
  ch_set(ht, key2, "Say What?");
  
  // A key with an actual unicode character
  UChar * key3 = (UChar *)calloc(8, sizeof(UChar));
  UErrorCode err = U_ZERO_ERROR;
  char * buffer = "Anυther";
  u_printf("%S\n", u_strFromUTF8(key3, 7, NULL, buffer, -1, &err));
  if (U_FAILURE(err)) {
    printf("Error: %s\n", u_errorName(err));
  }

  ch_set(ht, key3, "Yet another entry");
  
  assert( strcmp(ch_get(ht, key1), "Mar") == 0 );
  
  u_printf("Showing value for key '%S': %s\n", key1, (char *)ch_get(ht, key1));
  u_printf("Showing value for key '%S': %s\n", key2, (char *)ch_get(ht, key2));
  u_printf("Showing value for key '%S': %s\n", key3, (char *)ch_get(ht, key3));
  
  free(key3);
  ch_free(ht);
  u_cleanup();
  
  return 0;
}
