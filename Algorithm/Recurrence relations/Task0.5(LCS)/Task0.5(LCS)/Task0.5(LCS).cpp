// Task0.5(LCS).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Даны две последовательности A и B, каждая имеет длину n.найти наибольшее k, для которого существуют две последовательности
//индексов 0 <= i_1 < i_2 < ... < i_k < n и 0 <= j_1 < j_2 < ... < j_k < n, что A_{ i_1} = B_{j_1}, A_{ i_2} = B_{j_2}, …,
// A_{ i_k} = B_{j_k}.Также нужно найти и сами последовательности индексов.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> A(n), B(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int j = 0; j < n; j++) cin >> B[j];

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (A[i - 1] == B[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    int k = dp[n][n];
    cout << k << "\n";

    vector<int> ia, jb;
    int i = n, j = n;
    while (i > 0 && j > 0) {
        if (A[i - 1] == B[j - 1]) {
            ia.push_back(i - 1);
            jb.push_back(j - 1);
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        }
        else {
            j--;
        }
    }

    reverse(ia.begin(), ia.end());
    reverse(jb.begin(), jb.end());

    for (int t = 0; t < static_cast<int>(ia.size()); t++) {
        if (t) cout << ' ';
        cout << ia[t];
    }
    cout << "\n";
    for (int t = 0; t < static_cast<int>(jb.size()); t++) {
        if (t) cout << ' ';
        cout << jb[t];
    }
    cout << "\n";

    return 0;
}

