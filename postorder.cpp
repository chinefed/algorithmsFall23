#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int find(vector<int>& array, int l, int r, int key);
void traverse(vector<int>& preorder, unordered_map<int, int>& mapInOrder, int l1, int r1, int l2, int r2);

int main() {
    int nTestCases;
    cin >> nTestCases;

    for (int i = 0; i < nTestCases; i++) {
        int nNodes;
        cin >> nNodes;

        vector<int> preorder(nNodes);

        for (int j = 0; j < nNodes; j++) {
            cin >> preorder[j];
        }

        unordered_map<int, int> mapInOrder;
        int val;
        for (int j = 0; j < nNodes; j++) {
            cin >> val;
            mapInOrder[val] = j;
        }

        traverse(preorder, mapInOrder, 0, nNodes - 1, 0, nNodes - 1);
        cout << endl;
    }
}

void traverse(vector<int>& preorder, unordered_map<int, int>& mapInOrder, int l1, int r1, int l2, int r2) {

    if (l1 > r1 || l2 > r2) {
        return;
    }

    int p = preorder[l1];
    int pInOrder = mapInOrder[p];

    int leftSize = pInOrder - l2;
    int rightSize = r2 - pInOrder;

    traverse(preorder, mapInOrder, l1 + 1, l1 + leftSize, l2, pInOrder - 1);
    traverse(preorder, mapInOrder, l1 + leftSize + 1, r1, pInOrder + 1, r2);
    cout << p << " ";
}

