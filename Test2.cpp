#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// This function gets vector and integer and returns largest sum of not more than four elements from given vector not
// greater than given integer
long long LargestSumNotGreaterThanGivenNumber(const vector<long long>& nums, long long NUM) {
    // Since we can always take nothing from the vector, we can assign an initial value of 0 to the answer
    long long largest_sum = 0;

    // Make a vector from all possible sums of one or two elements from a given vector
    vector<long long> sums;
    for (int i = 0; i < nums.size(); ++i) {
        sums.push_back(nums[i]);
        for (int j = i; j < nums.size(); ++j) {
            sums.push_back(nums[i] + nums[j]);
        }
    }

    // Sort vector that contains all possible sums of one or two elements from a given vector
    sort(sums.begin(), sums.end());

    // For each element from vector "sums" we try to find another element from this vector, so that their sum is
    // maximum not greater than NUM
    for (int i = 0; i < sums.size(); ++i) {
        auto ub = upper_bound(sums.begin(),
                              sums.end(),
                              NUM - sums[i]);
        if (ub == sums.begin()) {
            if (sums[i] <= NUM) {
                largest_sum = max(largest_sum, sums[i]);
            }
            continue;
        }
        largest_sum = max(largest_sum,
                          sums[i] + *(--ub));
    }

    return largest_sum;
}

signed main() {
    int n, case_num = 0;
    long long m;
    cin >> n >> m;
    while (n != 0 || m != 0) {
        vector<long long> nums(n);
        for (int i = 0; i < n; ++i) {
            cin >> nums[i];
        }
        cout << "Case " << ++case_num << ": ";
        cout << LargestSumNotGreaterThanGivenNumber(nums, m) << endl;
        cout << endl;
        cin >> n >> m;
    }
}
