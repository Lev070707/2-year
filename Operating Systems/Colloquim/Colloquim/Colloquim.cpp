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
    return nh;
}

void free_list(Node* h) {
    while (h) {
        Node* t = h->n;
        delete h;
        h = t;
    }
}

int main() {
    while (true) {
        cout << "Choose option (1=factorials, 2=remove duplicates, 3=reverse linked list, 0=quit): ";
        int opt;
        if (!(cin >> opt)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), ' ');
            cout << "Invalid input for option. Try again.\n";
            continue;
        }

        if (opt == 0) {
            cout << "Bye\n";
            break;
        }

        if (opt == 1) {
            cout << "Enter n: ";
            long long n;

            if (!(cin >> n)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), ' ');
                cout << "Invalid n. Returning to menu.\n";
                continue;
            }
            if (n < 0) {
                cout << "n must be non-negative. Returning to menu.\n";
                continue;
            }
            vector<unsigned long long> v;
            unsigned long long f = 1;
            for (long long i = 1; i <= n; ++i) {
                if (f > numeric_limits<unsigned long long>::max() / static_cast<unsigned long long>(i)) {
                    cout << "Overflow would occur at " << i << ". Stopping.\n";
                    break;
                }
                f *= static_cast<unsigned long long>(i);
                v.push_back(f);
            }
            for (size_t i = 0; i < v.size(); ++i) {
                if (i) cout << " ";
                cout << v[i];
            }
            cout << "\n";
        }
        else if (opt == 2) {
            cout << "Enter number of elements: ";
            long long m;
            if (!(cin >> m)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), ' ');
                cout << "Invalid number. Returning to menu.\n";
                continue;
            }
            if (m < 0) {
                cout << "Number of elements must be non-negative. Returning to menu.\n";
                continue;
            }
            cout << "Enter elements separated by space or newline:\n";
            vector<long long> a(m);
            bool readError = false;
            for (size_t i = 0; i < m; ++i) {
                if (!(cin >> a[i])) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), ' ');
                    cout << "Failed to read element " << (i + 1) << ". Returning to menu.\n";
                    readError = true;
                    break;
                }
            }
            if (readError) continue;
            vector<long long> out;
            for (long long x : a) {
                bool found = false;
                for (long long y : out) if (y == x) { found = true; break; }
                if (!found) out.push_back(x);
            }
            for (size_t i = 0; i < out.size(); ++i) {
                if (i) cout << " ";
                cout << out[i];
            }
            cout << "\n";
        }
        else if (opt == 3) {
            cout << "Enter number of nodes: ";
            long long m;
            if (!(cin >> m)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), ' ');
                cout << "Invalid number. Returning to menu.\n";
                continue;
            }
            if (m < 0) {
                cout << "Number of nodes must be non-negative. Returning to menu.\n";
                continue;
            }
            cout << "Enter node values separated by space or newline:\n";
            Node* head = nullptr;
            Node* tail = nullptr;
            bool failed = false;
            for (size_t i = 0; i < m; ++i) {
                int x;
                if (!(cin >> x)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), ' ');
                    cout << "Failed to read node value " << (i + 1) << ". Cleaning and returning to menu.\n";
                    failed = true;
                    break;
                }
                Node* p = nullptr;
                try {
                    p = new Node(x);
                }
                catch (...) {
                    cout << "Memory allocation failed while creating node " << (i + 1) << ". Cleaning and returning to menu.\n";
                    failed = true;
                    break;
                }
                if (!head) head = tail = p;
                else { tail->n = p; tail = p; }
            }
            if (failed) {
                free_list(head);
                continue;
            }
            head = rev(head);
            bool first = true;
            for (Node* cur = head; cur; cur = cur->n) {
                if (!first) cout << " ";
                cout << cur->v;
                first = false;
            }
            cout << "\n";
            free_list(head);
        }
        else {
            cout << "Unknown option. Please enter 0, 1, 2, or 3.\n";
        }
    }
    return 0;
}
