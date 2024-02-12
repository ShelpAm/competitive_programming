// C++ implementation of the approach
#include <bits/stdc++.h>
using namespace std;

// Merge procedure to merge two
// vectors into a single vector
vector<int> merge(vector<int>& v1, vector<int>& v2)
{
  int i = 0, j = 0;

  // Final vector to return
  // after merging
  vector<int> v;

  // Loop continues until it reaches
  // the end of one of the vectors
  while (i < v1.size() && j < v2.size()) {
    if (v1[i] <= v2[j]) {
      v.push_back(v1[i]);
      i++;
    }
    else {
      v.push_back(v2[j]);
      j++;
    }
  }

  // Here, simply add the remaining
  // elements to the vector v
  for (int k = i; k < v1.size(); k++)
    v.push_back(v1[k]);
  for (int k = j; k < v2.size(); k++)
    v.push_back(v2[k]);
  return v;
}

// Procedure to build the segment tree
void buildTree(vector<int>* tree, vector<size_t> arr, int index, int s, int e)
{
  // Reached the leaf node
  // of the segment tree
  if (s == e) {
    tree[index].push_back(arr[s]);
    return;
  }

  // Recursively call the buildTree
  // on both the nodes of the tree
  int mid = (s + e) / 2;
  buildTree(tree, arr, 2 * index, s, mid);
  buildTree(tree, arr, 2 * index + 1, mid + 1, e);

  // Storing the final vector after merging
  // the two of its sorted child vector
  tree[index] = merge(tree[2 * index], tree[2 * index + 1]);
}

// Query procedure to get the answer
// for each query l and r are query range
int query(vector<int>* tree, int index, int s, int e, int l, int r, int k)
{
  // out of bound or no overlap
  if (r < s || l > e)
    return 0;

  // Complete overlap
  // Query range completely lies in
  // the segment tree node range
  if (s >= l && e <= r) {
    // binary search to find index of k
    return (tree[index].size()
            - (lower_bound(tree[index].begin(), tree[index].end(), k) - tree[index].begin()));
  }

  // Partially overlap
  // Query range partially lies in
  // the segment tree node range
  int mid = (s + e) / 2;
  return (query(tree, 2 * index, s, mid, l, r, k)
          + query(tree, 2 * index + 1, mid + 1, e, l, r, k));
}

// Function to perform the queries
void performQueries(int L[], int R[], int K[], int n, int q, vector<int> tree[]) {}

// Driver code
int main()
{
  size_t n;
  cin >> n;
  vector<size_t> arr(n);
  for (auto& e: arr) {
    cin >> e;
  }
  vector<int> tree[4 * n + 1];
  buildTree(tree, arr, 1, 0, n - 1);

  size_t cnt{};
  for (int i = 1; i < n - 1; i++) {
    cnt += query(tree, 1, 0, n - 1, 0, i - 1, arr[i])
           * query(tree, 1, 0, n - 1, i + 1, n - 1, arr[i]);
  }
  cout << cnt;

  return 0;
}
