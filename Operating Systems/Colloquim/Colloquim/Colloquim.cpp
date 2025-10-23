// Colloquim.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int v;
    Node* n;
    Node(int x) :v(x), n(nullptr) {} 
};
Node* rev(Node* h) {
    if (!h || !h->n) return h;
    Node* nh = rev(h->n);
    h->n->n = h;
    h->n = nullptr;
    return nh; }

int main() {
    cout << "Choose option (1=factorials, 2=remove duplicates, 3=reverse linked list): ";
    int opt;
    if (!(cin >> opt)) return 0;

    if (opt == 1) {
        cout << "Enter n: ";
        long long n;
        if (!(cin >> n)) return 0;
        vector<long long> v;
        long long f = 1;
        for (long long i = 1; i <= n; ++i) { f *= (long long)i; v.push_back(f); }
        for (size_t i = 0; i < v.size(); ++i) { if (i) cout << " "; cout << v[i]; }
        cout << "\n";
    }
    else if (opt == 2) {
        cout << "Enter number of elements: ";
        int m;
        if (!(cin >> m)) return 0;
        cout << "Enter elements separated by space or newline:\n";
        vector<long long> a(m);
        for (int i = 0; i < m; ++i) cin >> a[i];
        vector<long long> out;
        for (long long x : a) {
            bool found = false;
            for (long long y : out) if (y == x) { found = true; break; }
            if (!found) out.push_back(x);
        }
        for (size_t i = 0; i < out.size(); ++i) { if (i) cout << " "; cout << out[i]; }
        cout << "\n";
    }
    else if (opt == 3) {
        cout << "Enter number of nodes: ";
        int m;
        if (!(cin >> m)) return 0;
        cout << "Enter node values separated by space or newline:\n";
        Node* head = nullptr;
        Node* tail = nullptr;
        for (int i = 0; i < m; ++i) {
            int x; cin >> x;
            Node* p = new Node(x);
            if (!head) head = tail = p;
            else { tail->n = p; tail = p; }
        }
        head = rev(head);
        bool first = true;
        for (Node* cur = head; cur; cur = cur->n) {
            if (!first) cout << " ";
            cout << cur->v;
            first = false;
        }
        cout << "\n";
    }

    return 0;
}
