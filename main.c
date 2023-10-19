#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "./word_sort.h"

int main(int argc, char **argv) {
  char *dst = malloc(12);

  assert(word_sort("The   \t\n cat  sat", dst, 12, 0) == 12);
  assert(strcmp(dst, "The cat sat") == 0);

  assert(word_sort("The   \t\n cat  sat", dst, 12, WORD_SORT_IGNORE_CASE) == 12);
  assert(strcmp(dst, "cat sat The") == 0);

  assert(word_sort("The   \t\n cat  sat", dst, 12, WORD_SORT_REVERSE) == 12);
  assert(strcmp(dst, "sat cat The") == 0);

  assert(word_sort("The   \t\n cat  sat", dst, 12, WORD_SORT_REVERSE | WORD_SORT_IGNORE_CASE) == 12);
  assert(strcmp(dst, "The sat cat") == 0);

  // insufficient space in dst
  assert(word_sort("The   \t\n cat  sat", dst, 11, 0) == 0);

  printf("%s\n", "✔ all tests have been passed");
}
