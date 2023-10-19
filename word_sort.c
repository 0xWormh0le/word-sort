#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "./word_sort.h"

char* strlwr(const char *str) {
  unsigned int i;
  char *buf = malloc(strlen(str));

  for (i = 0; str[i]; i++) {
    buf[i] = tolower(str[i]);
  }

  buf[i] = '\0';

  return buf;
}

int compare(
  const char *a,
  const char *b,
  unsigned int flag
) {
  char *aa = (char*)a, *bb = (char*)b;
  unsigned int cmp = 0;

  if (flag & WORD_SORT_IGNORE_CASE) {
    aa = strlwr(a);
    bb = strlwr(b);
  }

  if (flag & WORD_SORT_REVERSE) {
    cmp = -strcmp(aa, bb);
  } else {
    cmp = strcmp(aa, bb);
  }

  if (flag & WORD_SORT_IGNORE_CASE) {
    free(aa);
    free(bb);
  }

  return cmp;
}

unsigned int word_sort(
  const char *src,
  char *dst,
  unsigned int dst_len,
  unsigned int flags
) {
  char *srcdmp;
  char **words;
  char delimiters[10] = " \t\n";
  unsigned int count = 0, buf_size = 0;

  srcdmp = malloc(strlen(src));
  strcpy(srcdmp, src);

  char *token = strtok(srcdmp, delimiters);

  // iterate token to get token count

  while (token != NULL) {
    count++;
    buf_size += strlen(token);
    token = strtok(NULL, delimiters);
  }

  buf_size += count;

  if (buf_size > dst_len) {
    return 0;
  }

  strcpy(srcdmp, src);

  // assign words based on count

  words = malloc(count);
  token = strtok(srcdmp, delimiters);
  count = 0;

  // iterate token again to assign to words

  while (token != NULL) {
    words[count] = malloc(strlen(token) + 1);
    strcpy(words[count], token);
    token = strtok(NULL, delimiters);
    count++;
  }

  // compare

  for (unsigned int i = 0; i < count; i++) {
    for (unsigned int j = i; j < count; j++) {
      if (compare(words[i], words[j], flags) > 0) {
        char *tmp = words[i];

        words[i] = words[j];
        words[j] = tmp;
      }
    }
  }

  // copy to dst

  dst[0] = '\0';

  for (unsigned int i = 0; i < count; i++) {
    strcat(dst, words[i]);

    if (i < count - 1) {
      strcat(dst, " ");
    }

    free(words[i]);
  }

  free(srcdmp);
  free(words);

  return buf_size;
}
