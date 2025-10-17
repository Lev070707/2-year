// Task20(Палиндромы).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// Дана строка, состоящая из строчных букв латинского алфавита, без пробелов. Палиндромом называется текст, одинаково
// читаемый слева-направо и справа-налево. Необходимо найти палиндром максимальной длины, который можно получить из
// исходной строки вычеркиванием символов (менять порядок символов нельзя). Так как ответов может быть несколько, то найти
// минимальный и максимальный лексикографически (как в словаре).
/* Будем хранить в dp[l][r] размер максимального палиндрома в подстроке s[l...r], тогда dp[0][n -1] будет размер
максимального палиндрома. В next[i][c] лежит первая позиция >=i для каждой буквы , а в prev[i + 1][c] последняя
позиция <= i-1 для каждой буквы*/
/* Оценка сложности: O(n^2) + 2*O(26*n) + O(26*n) ~ O(n^2) (Построение dp + построение next and prev + реконструкция
палиндрома(need не больше n и букв 26.
Память: O(n^2) + O(52*n^2) + O(k*n) ~ O(n^2) (dp + next + prev + (string s and other strings to store results) При
n = 10000(int занимает 4 байта) память ~ 400 МБ(ограничение 256 МБ) */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string buildPal(string& s,vector<vector<int>>& dp, vector<vector<int>>& nextS,
    vector<vector<int>>& prevS, bool min) {
    int n = s.size();
    int L = 0, R = n-1;
    int need = dp[0][n-1];
    vector<char> leftPart;
    string mid;
    while (need > 0 && L <= R) {
        bool found = false;
        if (need == 1) {
            if (min) {
                for (int c = 0; c < 26; c++) {
                    int pos = nextS[L][c];
                    if (pos != -1 && pos <= R) {
                        mid.push_back('a' + c); need = 0; break;
                    }
                }
            }
            else {
                for (int c = 25; c >= 0; c--) {
                    int pos = nextS[L][c];
                    if (pos != -1 && pos <= R) {
                        mid.push_back('a' + c); need = 0; break;
                    }
                }
            }
            break;
        }
        if (min) {
            for (int c = 0; c < 26; c++) {
                int i1 = nextS[L][c];
                int j1 = prevS[R + 1][c];
                if (i1 == -1 || j1 == -1) continue;
                if (i1 >= j1) continue;
                int inner = (i1 + 1 <= j1 - 1 ? dp[i1 + 1][j1 - 1] : 0);
                if (inner >= need - 2) {
                    leftPart.push_back('a' + c);
                    L = i1 + 1;
                    R = j1 - 1;
                    need -= 2;
                    found = true;
                    break;
                }
            }
        }else {
            for (int c = 25; c >= 0; c--) {
                int i1 = nextS[L][c];
                int j1 = prevS[R + 1][c];
                if (i1 == -1 || j1 == -1) continue;
                if (i1 >= j1) continue;
                int inner = (i1 + 1 <= j1 - 1 ? dp[i1 + 1][j1 - 1] : 0);
                if (inner >= need - 2) {
                    leftPart.push_back('a' + c);
                    L = i1 + 1;
                    R = j1 - 1;
                    need -= 2;
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            int valL = (L + 1 <= R ? dp[L + 1][R] : 0);
            int valR = (L <= R - 1 ? dp[L][R - 1] : 0);
            if (valL >= valR) L++;
            else R--;
        }
    }
    string res;
    res.reserve(leftPart.size() * 2 + mid.size());
    for (char c : leftPart) res.push_back(c);
    if (!mid.empty()) res += mid;
    for (auto it = leftPart.rbegin(); it != leftPart.rend(); it++) res.push_back(*it);
    return res;
}

int main()
{
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<int>> dp(n , vector<int>(n, 0));
    for (int i = 0; i < n; i++) dp[i][i] = 1;
    for (int len = 2; len <= n; len++) {
        for (int l = 0;l + len - 1 < n;l++) {
            int r = l + len - 1;
            if (s[l] == s[r]) {
                if (l + 1 <= r - 1) dp[l][r] = dp[l + 1][r - 1] + 2;
                else dp[l][r] = 2;
            }
            else {
                dp[l][r] = max(dp[l + 1][r], dp[l][r - 1]);
            }
        }
    }

    vector<vector<int>> next(n + 1, vector<int>(26, -1)), prev(n + 1, vector<int>(26, -1));
    for (int i = n - 1;i >= 0;i--) {
        for (int c = 0; c < 26; c++) next[i][c] = next[i + 1][c];
        next[i][s[i] - 'a'] = i;
    }
    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++) prev[i + 1][c] = prev[i][c];
        prev[i + 1][s[i] - 'a'] = i;
    }

    string minPal = buildPal(s, dp, next, prev, true);
    string maxPal = buildPal(s, dp, next, prev, false);

    cout << minPal << "\n" << maxPal;
}