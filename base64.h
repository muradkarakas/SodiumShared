#ifndef BASE64_H_INCLUDED
#define BASE64_H_INCLUDED

#include <ctype.h>
#include "SodiumShared.h"

/**
 * `b64.h' - b64
 *
 * copyright (c) 2014 joseph werle
 */

/**
 * Base64 index table.
 */

static const char b64_table[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
  'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
  'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
  'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
  'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
  'w', 'x', 'y', 'z', '0', '1', '2', '3',
  '4', '5', '6', '7', '8', '9', '+', '/'
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Encode `unsigned char *' source with `size_t' size.
 * Returns a `char *' base64 encoded string.
 */

SODIUM_SHARED_API char *mkBase64Encode(void *heapHandle, const unsigned char *src, size_t len);

/**
 * Dencode `char *' source with `size_t' size.
 * Returns a `unsigned char *' base64 decoded string.
 */
SODIUM_SHARED_API unsigned char *mkBase64Decode(void *heapHandle, const char *src, size_t len);

/**
 * Dencode `char *' source with `size_t' size.
 * Returns a `unsigned char *' base64 decoded string + size of decoded string.
 */
unsigned char *b64_decode_ex(void *heapHandle, const char *src, size_t len, size_t *decsize);

#ifdef __cplusplus
}
#endif




#endif // BASE64_H_INCLUDED
