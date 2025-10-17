// Task20(Палиндромы).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// Дана строка, состоящая из строчных букв латинского алфавита, без пробелов. Палиндромом называется текст, одинаково
// читаемый слева-направо и справа-налево. Необходимо найти палиндром максимальной длины, который можно получить из
// исходной строки вычеркиванием символов (менять порядок символов нельзя). Так как ответов может быть несколько, то найти
// минимальный и максимальный лексикографически (как в словаре).
/* Будем искать LCS строки s и обратной ей строки t это и будет палиндром. В dp[i][j] лежит длина LCS(s,t) начиная с i 
в s и j в t, т.е dp[0][0] и будет размер самого длинного палиндрома и далее будем восстанавливать наш палиндром длины
dp[0][0] добавляя в результат букву, если после этого ещё можно собрать палиндром максимальной длины*/
/* При маленьких строках программа работает корректно и проверки dp[i1 + 1][j1 + 1] >= rem - 1(*) достаточно, однако эта 
гарантирует только то, что наш результат будет нужной длины, но не гарантирует того, что он будет палиндромом и таким
образом мы можем добавить не ту букву(ищем первую удовлетворяющую условию (*) но это не всегда правильно),ведь после этого
может уже не выйти собрать палиндром.В больших строках много повторяющихся букв и там этот алгоритм даёт сбой у нас
получается не палиндром.
Пример: gxlnxvsjxzdsvxcpfaeuwcffvvkyojetfdcsuyfihuirdwfyfgpwnrkadxuqxwxhwpbwnmebmolmzsdjucxtpibtbhhtlvvjgtcjdngtirzbshzufhbmgrsveglylyqtnemkvupvydendkythmvanliblqfdxlabajardccjikobbqzsajuqtpdtxmzuuwhpmwceodtpbfozarnkhaoxevsvrezqwnzwiggcvjmlpjlrkgenwmreswlcnxxlgbl
glxxcewkjcgwnqxhnbomuxtpbbjcdrbfblnmkdedkmnlbfbrdcjbbptxmwhwdakrnwgcjkwecxxlg
glxxsewkjciwwrxhnbomzxtptbjcdrbfllynevuvkmnllfbrdcjbtptxzwpwdarnwwicjkwesxxlg
Правильный ответ:
glxxcewkjcgwnqxhnbomuxtpbbjcdrbfblnmkdedkmnlbfbrdcjbbptxumobnhxqnwgcjkwecxxlg
glxxsewkjciwwrxhnbomzxtptbjcdrbfllynevuvenyllfbrdcjbtptxzmobnhxrwwicjkwesxxlg
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string buildPal(string& s, string& t, vector<vector<int>>& dp, vector<vector<int>>& nextS,
    vector<vector<int>>& nextT, bool min) {
    int n = s.size();
    int i = 0, j = 0;
    int rem = dp[0][0];
    string res;
    res.reserve(rem);
    while (rem > 0) {
        bool found = false;
        if (min) {
            for (int c = 0; c < 26; c++) {
                int i1 = (i <= n ? nextS[i][c] : -1);
                int j1 = (j <= n ? nextT[j][c] : -1);
                if (i1 == -1 || j1 == -1) continue;
                if (dp[i1 + 1][j1 + 1] >= rem - 1) {
                    res.push_back(char('a' + c));
                    i = i1 + 1;
                    j = j1 + 1;
                    rem--;
                    found = true;
                    break;
                }
            }
        }
        else {
            for (int c = 25; c >= 0; c--) {
                int i1 = (i <= n ? nextS[i][c] : -1);
                int j1 = (j <= n ? nextT[j][c] : -1);
                if (i1 == -1 || j1 == -1) continue;
                if (i1 >= n || j1 >= n) continue;
                if (dp[i1 + 1][j1 + 1] >= rem - 1) {
                    res.push_back(char('a' + c));
                    i = i1 + 1;
                    j = j1 + 1;
                    rem--;
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            if (i < s.size() && dp[i + 1][j] >= dp[i][j + 1]) i++;
            else j++;
        }
    }
    return res;
}

int main()
{
    string s;
    cin >> s;
    int n = s.size();
    string t = s;
    reverse(t.begin(), t.end());
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            if (s[i] == t[j]) {
                dp[i][j] = 1 + dp[i + 1][j + 1];
            }
            else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j + 1]);
            }
        }
    }

    vector<vector<int>> nextS(n + 1, vector<int>(26, -1)), nextT(n + 1, vector<int>(26, -1));
    for (int i = n - 1;i >= 0;i--) {
        for (int c = 0; c < 26; c++) nextS[i][c] = nextS[i + 1][c];
        nextS[i][s[i] - 'a'] = i;
        for (int c = 0; c < 26; c++) nextT[i][c] = nextT[i + 1][c];
        nextT[i][t[i] - 'a'] = i;
    }

    string minPal = buildPal(s, t, dp, nextS, nextT, true);
    string maxPal = buildPal(s, t, dp, nextS, nextT, false);

    cout << minPal << "\n" << maxPal;
}