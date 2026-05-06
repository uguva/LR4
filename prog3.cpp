#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct LCGRes {
    vector<long> seq;
    int repeat_idx;
};

LCGRes lcg(long x0, long a, long b, long c) {
    LCGRes res;
    set<long> seen;
    res.repeat_idx = 0;
    long curr = x0;
    int n = 10; 

    for (int i = 0; i < n; ++i) {
        res.seq.push_back(curr);
        
        if (res.repeat_idx == 0 && seen.count(curr)) {
            res.repeat_idx = i + 1;
        }
        
        seen.insert(curr);
        curr = (a * curr + b) % c;
    }
    
    if (res.repeat_idx == 0) res.repeat_idx = n;
    
    return res;
}

int main() {
    long x0, a, b, c;
    
    if (cin >> x0 >> a >> b >> c) {
        LCGRes r = lcg(x0, a, b, c);
        
        bool first = true;
        for (auto v : r.seq) {
            if (!first) cout << " ";
            cout << v;
            first = false;
        }
        
        cout << "\n" << r.repeat_idx << "\n";
    }
    
    return 0;
}
