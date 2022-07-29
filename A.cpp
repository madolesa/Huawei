#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// This function gets two numbers represented as a string and returns their sum as string.
string StringSum(const string& num1, const string& num2) {
    string res = "";
    // Using the pointers to the current element for each string, that runs in parallel, implement column addition
    int p1 = num1.size(), p2 = num2.size();
    int sum = 0;
    while (p1 > 0 || p2 > 0) {
        if (p1 > 0) {
            sum += num1[--p1] - '0';
        }
        if (p2 > 0) {
            sum += num2[--p2] - '0';
        }
        res += (sum % 10) + '0';
        sum /= 10;
    }
    if (sum != 0) {
        res += sum + '0';
    }
    reverse(res.begin(), res.end());
    return res;
}

signed main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        string num1, num2;
        cin >> num1 >> num2;
        cout << "Case " << i + 1 << ":\n";
        cout << num1 << " + " << num2 << " = " << StringSum(num1, num2) << endl << endl;
    }
}
