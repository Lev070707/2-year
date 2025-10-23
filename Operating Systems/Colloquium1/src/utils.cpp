#include "utils.h"
#include <limits>

Node* rev(Node* h) {
    if (!h || !h->n) return h;
    Node* nh = rev(h->n);
    h->n->n = h;
    h->n = nullptr;
    return nh;
}

void free_list(Node* h) {
    while (h) {
        Node* t = h->n;
        delete h;
        h = t;
    }
}

std::vector<unsigned long long> compute_factorials(long long n) {
    std::vector<unsigned long long> v;
    if (n <= 0) return v;
    unsigned long long f = 1;
    for (long long i = 1; i <= n; ++i) {
        if (f > std::numeric_limits<unsigned long long>::max() / static_cast<unsigned long long>(i)) {
            break;
        }
        f *= static_cast<unsigned long long>(i);
        v.push_back(f);
    }
    return v;
}

std::vector<long long> remove_duplicates(const std::vector<long long>& a) {
    std::vector<long long> out;
    out.reserve(a.size());
    for (long long x : a) {
        bool found = false;
        for (long long y : out) {
            if (y == x) { found = true; break; }
        }
        if (!found) out.push_back(x);
    }
    return out;
}

Node* make_list_from_vector(const std::vector<int>& v) {
    Node* head = nullptr;
    Node* tail = nullptr;
    for (int x : v) {
        Node* p = new Node(x);
        if (!head) head = tail = p;
        else { tail->n = p; tail = p; }
    }
    return head;
}

std::vector<int> to_vector(Node* head) {
    std::vector<int> out;
    for (Node* cur = head; cur; cur = cur->n) out.push_back(cur->v);
    return out;
}
