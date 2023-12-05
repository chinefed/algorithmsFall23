#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

void *allocate1DArray(uint32_t n, uint32_t typeSize);
void free1DArray(void *array);
uint32_t getTreeSize(uint32_t n);
void pointUpdate(uint32_t *tree, uint32_t treeSize, uint32_t index, uint32_t key);
uint32_t getPermItem(uint32_t *tree, uint32_t treeSize, uint32_t dist);

int main(void)
{

    // Get n items from standard input 
    uint32_t n;
    scanf("%" SCNu32, &n);

    // Initialize the segment tree 
    uint32_t treeSize, *tree;
    treeSize = getTreeSize(n);
    tree = (uint32_t *)allocate1DArray(treeSize, sizeof(uint32_t));

    // Initialize the inversion vector and the permutation vector
    uint32_t *invVector, *permVector;
    invVector = (uint32_t *)allocate1DArray(n, sizeof(uint32_t));
    permVector = (uint32_t *)allocate1DArray(n, sizeof(uint32_t));

    // Populate the inversion vector
    for (uint32_t i = 0; i < n; i++)
        scanf("%" SCNu32, invVector + i);

    // Set all the leaves in the segment tree to 1
    for (uint32_t i = 0; i < n; i++)
        pointUpdate(tree, treeSize, i, 1);

    // Construct the permutation vector
    for (uint32_t i = n; i > 0; i--)
        permVector[i-1] = getPermItem(tree, treeSize, invVector[i-1]) + 1;

    // Print the permutation vector
    for (uint32_t i = 0; i < n; i++)
        printf("%" PRIu32 " ", permVector[i]);
    
    // Free allocated memory
    free1DArray(tree);
    free1DArray(invVector);
    free1DArray(permVector);

    return 0;

}

void *allocate1DArray(uint32_t n, uint32_t typeSize)
{
    /* Allocates a 1-dimensional array of size n, where each element has a size of typeSize. */
    void *array = calloc(n, typeSize);
    if (array == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    return array;
}

void free1DArray(void *array)
{
    /* Frees a 1D array. */
    free(array);

    return;
}

uint32_t getTreeSize(uint32_t n)
{
    /* Returns the size of the segment tree array. */
    uint32_t treeSize = 1;
    while (treeSize < n)
        treeSize <<= 1;

    return treeSize << 1;
}

void pointUpdate(uint32_t *tree, uint32_t treeSize, uint32_t index, uint32_t key)
{
    /* Update a leaf and propagete. */
    uint32_t indexTree = (treeSize >> 1) + index;
    tree[indexTree] = (key);
    uint32_t p = indexTree >> 1;
    while (p > 0)
    {
        // Propagate to ancestors.
        tree[p] = tree[(p << 1)] + tree[(p << 1) + 1];
        p >>= 1;

    }

    return;
}

uint32_t getPermItem(uint32_t *tree, uint32_t treeSize, uint32_t dist)
{
    /* Get permutation item. */
    uint32_t root = 1;
    while (root < (treeSize >> 1))
    {
        uint32_t rightChildKey = tree[(root << 1) + 1];
        if (rightChildKey > dist)
            root = (root << 1) + 1;
        else
        {
            root = root << 1;
            dist -= rightChildKey;
        }
    }

    // Convert the index of the selected leaf to array notation
    uint32_t output = root - (treeSize >> 1);
    pointUpdate(tree, treeSize, output, 0);

    return output;
}
