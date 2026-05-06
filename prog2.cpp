#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>

using namespace std;

struct Task2Res {
    int min_mod_idx;
    long sum_mod;
    vector<int> original_arr1;
    vector<int> longest_inc;
    vector<int> reverse_desc;
    vector<int> original_arr2_1;
    vector<int> original_arr2_2;
    vector<int> shift_arr1;
    vector<int> shift_arr2;
};

Task2Res solveTask2(int n1, int n2, int seed) {
    Task2Res res;
    ranlux24 gen(seed);
    uniform_int_distribution<> dist1(-250, 250);
    uniform_int_distribution<> dist2(-50, 50);

    vector<int> arr1(n1);
    for (auto& val : arr1) {
        val = dist1(gen);
    }
    res.original_arr1 = arr1;

    int min_val = 1e9;
    res.min_mod_idx = -1;
    int idx = 0;
    for (auto val : arr1) {
        if (abs(val) < min_val) {
            min_val = abs(val);
            res.min_mod_idx = idx;
        }
        idx++;
    }

    res.sum_mod = 0;
    bool count_flag = false;
    idx = 0;
    for (auto val : arr1) {
        if (count_flag) {
            res.sum_mod += abs(val);
        }
        if (idx == res.min_mod_idx) {
            count_flag = true;
        }
        idx++;
    }

    vector<int> current_inc;
    for (auto val : arr1) {
        if (current_inc.empty() || val > current_inc.back()) {
            current_inc.push_back(val);
        } else {
            if (current_inc.size() > res.longest_inc.size()) {
                res.longest_inc = current_inc;
            }
            current_inc = {val};
        }
    }
    if (current_inc.size() > res.longest_inc.size()) {
        res.longest_inc = current_inc;
    }

    res.reverse_desc = arr1;
    sort(res.reverse_desc.begin(), res.reverse_desc.end(), greater<int>());
    reverse(res.reverse_desc.begin(), res.reverse_desc.end());

    vector<int> arr2_1(n2), arr2_2(n2);
    for (auto& val : arr2_1) val = dist2(gen);
    for (auto& val : arr2_2) val = dist2(gen);
    
    res.original_arr2_1 = arr2_1;
    res.original_arr2_2 = arr2_2;
    res.shift_arr1 = arr2_1;
    res.shift_arr2 = arr2_2;

    if (n2 > 0) {
        int last1 = res.original_arr2_1.back();
        int last2 = res.original_arr2_2.back();

        for (int i = n2 - 1; i > 0; --i) {
            res.shift_arr1[i] = res.original_arr2_1[i - 1];
            res.shift_arr2[i] = res.original_arr2_2[i - 1];
        }
        res.shift_arr1[0] = last2;
        res.shift_arr2[0] = last1;
    }

    return res;
}

int main() {
    int n1, n2, seed;
    if (cin >> n1 >> n2 >> seed) {
        Task2Res r = solveTask2(n1, n2, seed);
        
        for (auto v : r.original_arr1) cout << v << " ";
        cout << "\n";
        
        cout << r.min_mod_idx << " " << r.sum_mod << "\n";
        
        for (auto v : r.longest_inc) cout << v << " ";
        cout << "\n";
        
        for (auto v : r.reverse_desc) cout << v << " ";
        cout << "\n";
        
        for (auto v : r.original_arr2_1) cout << v << " ";
        cout << "\n";
        for (auto v : r.original_arr2_2) cout << v << " ";
        cout << "\n";
        
        for (auto v : r.shift_arr1) cout << v << " ";
        cout << "\n";
        for (auto v : r.shift_arr2) cout << v << " ";
        cout << "\n";
    }
    return 0;
}
