#include <stdio.h>
#include <assert.h>

#include "bst.h"

/*
 * This is the data that's used to test this program.  It forms a tree that
 * looks like this:
 *
 *               64
 *              /  \
 *             /    \
 *            /      \
 *           /        \
 *          32        96
 *         /  \      /  \
 *        /    \    /    \
 *       16    48  80    112
 *      /  \     \   \   /  \
 *     8   24    56  88 104 120
 */
#define NUM_TEST_VALS 13
const int TEST_VALS[NUM_TEST_VALS] =
  {64, 32, 96, 16, 48, 80, 112, 8, 24, 56, 88, 104, 120};

#define NUM_GOOD_PATH_SUMS 6
const int GOOD_PATH_SUMS[NUM_GOOD_PATH_SUMS] = {120, 136, 200, 328, 376, 392};

int main(int argc, char** argv) {

  struct bst* bst = bst_create();
  for (int i = 0; i < NUM_TEST_VALS; i++) {
    bst_insert(TEST_VALS[i], bst);
  }

  /*
   * Test BST size function.  This should print the value of NUM_TEST_VALS.
   */
  printf("\n== BST size: %d\n", bst_size(bst));

  /*
   * Test BST height function.  This should print approximately
   * log(NUM_TEST_VALS).
   */
  printf("\n== BST height: %d\n", bst_height(bst));

  /*
   * Test BST path sum function, checking several values that the tree should
   * and should not have as path sums.
   */
  printf("\n== Checking path sums the BST should contain:\n");
  for (int i = 0; i < NUM_GOOD_PATH_SUMS; i++) {
    printf("  == %3d: ", GOOD_PATH_SUMS[i]);
    if (bst_path_sum(GOOD_PATH_SUMS[i], bst)) {
      printf("all good\n");
    } else {
      printf("bst_path_sum() says NO when it should say YES\n");
    }
  }

  printf("\n== Checking path sums the BST should NOT contain:\n");
  int num_bad_sums = 0;
  int cur_good_sum = 0;
  for (int i = 0; i < GOOD_PATH_SUMS[NUM_GOOD_PATH_SUMS - 1]; i += 4) {
    if (i == GOOD_PATH_SUMS[cur_good_sum]) {
      cur_good_sum++;
    } else if (bst_path_sum(i, bst)) {
      num_bad_sums++;
      printf("  == %3d: bst_path_sum() says YES when it should say NO\n", i);
    }
  }
  printf("  == found %d paths sums we shouldn't have found\n", num_bad_sums);

  /*
   * Test BST iterator.  This should result in values being printed in order.
   */
  struct bst_iterator* iter = bst_iterator_create(bst);
  printf("\n== BST contents (in order):");
  while (bst_iterator_has_next(iter)) {
    int val = bst_iterator_next(iter);
    printf(" %4d", val);
  }
  printf("\n");
  bst_iterator_free(iter);

  bst_free(bst);

}
