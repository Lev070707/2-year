#pragma once
#include <vector>

struct Node {
    int v;
    Node* n;
    Node(int x) : v(x), n(nullptr) {}
};
Node* rev(Node* h);
void free_list(Node* h);
std::vector<unsigned long long> compute_factorials(long long n);
std::vector<long long> remove_duplicates(const std::vector<long long>& a);
Node* make_list_from_vector(const std::vector<int>& v);
std::vector<int> to_vector(Node* head);