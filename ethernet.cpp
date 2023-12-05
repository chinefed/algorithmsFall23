#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

vector<uint32_t> transition( vector<uint32_t> &inputState, vector<uint32_t> &permutation);
uint32_t getTreeSize(uint32_t n);
void pointUpdate(vector< vector<uint32_t> > &tree, uint32_t treeSize, uint32_t index,  vector<uint32_t> &key);

int main() {
    // Get the number of devices
    uint32_t nDevices;
    cin >> nDevices;

    // Initialize the segment tree 
    uint32_t treeSize;
    vector< vector<uint32_t> > tree;
    treeSize = getTreeSize(nDevices);
    tree.resize(treeSize, vector<uint32_t>(8));

    // Every node is initially set to {1, 2, 3, 4, 5, 6, 7, 8}
    vector<uint32_t> initCase(8);
    for (uint32_t i = 0; i < 8; i++)
        initCase[i] = i + 1;
    for (uint32_t i = 0; i < treeSize; i++)
        tree[i] = initCase;

    // Store initial device permutations 
    for (uint32_t i = 0; i < nDevices; i++) {
        vector<uint32_t> permutation(8);
        for (uint32_t j = 0; j < 8; j++)
            cin >> permutation[j];
        // Update the segment tree
        pointUpdate(tree, treeSize, i, permutation);
    }

    // Get the number of substitutions
    uint32_t nSubstitutions;
    cin >> nSubstitutions;

    // Apply the substitutions
    for (uint32_t i = 0; i < nSubstitutions; i++) {
        // Get the device index
        uint32_t idx;
        cin >> idx;
        // Store new permutations
        vector<uint32_t> permutation(8);
        for (uint32_t j = 0; j < 8; j++)
            cin >> permutation[j];
        // Update the segment tree
        pointUpdate(tree, treeSize, idx - 1, permutation);
        // Print result
        for (uint32_t j = 0; j < 8; j++)
            cout << tree[1][j] << " ";
        cout << endl;
    }

    return 0;
}

vector<uint32_t> transition(vector<uint32_t> &inputState, vector<uint32_t> &permutation) {
    /* Transition function between states. */
    vector<uint32_t> outputState(8);
    for (uint32_t i = 0; i < 8; i++) {
        outputState[i] = inputState[permutation[i] - 1];
    }

    return outputState;
}

uint32_t getTreeSize(uint32_t n) {
    /* Returns the size of the segment tree array. */
    uint32_t treeSize = 1;
    while (treeSize < n)
        treeSize <<= 1;

    return treeSize << 1;
}

void pointUpdate(vector< vector<uint32_t> > &tree, uint32_t treeSize, uint32_t index,  vector<uint32_t> &key) {
    /* Update a leaf and propagate. */
    uint32_t indexTree = (treeSize >> 1) + index;
    tree[indexTree] = key;
    uint32_t p = indexTree >> 1;
    while (p > 0) {
        // Propagate to ancestors.
        tree[p] = transition(tree[(p << 1)], tree[(p << 1) + 1]);
        p >>= 1;
    }

    return;
}
