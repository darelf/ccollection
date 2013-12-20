#include <stdio.h>
#include <assert.h>
#include "cvector.h"
#include "chashtable.h"

#include <unicode/utypes.h>
#include <unicode/uchar.h>
#include <unicode/ustring.h>
#include <unicode/ustdio.h>

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
  UChar * key3[7];
  int32_t destLen = 0;
  UErrorCode * err;
  u_strFromUTF8(key3, 7, &destLen, "Anυther", strlen("Anυther"), err);
  
  ch_set(ht, key3, "Yet another entry");
  
  assert( strcmp(ch_get(ht, key1), "Mar") == 0 );
  
  u_printf("Showing value for key '%S': %s\n", key1, (char *)ch_get(ht, key1));
  u_printf("Showing value for key '%S': %s\n", key2, (char *)ch_get(ht, key2));
  u_printf("Showing value for key '%S': %s\n", key3, (char *)ch_get(ht, key3));
  
  ch_free(ht);
  u_cleanup();
  
  return 0;
}
