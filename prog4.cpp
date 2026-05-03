#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

struct VoteRes {
    string borda;
    string condorcet;
};

VoteRes calculateVoting(const vector<vector<string>>& votes) {
    VoteRes res;
    if (votes.empty() || votes[0].empty()) return res;

    int num_voters = votes.size();
    int num_candidates = votes[0].size();
    map<string, int> borda_scores;
    vector<string> candidates;

    for (auto ballot : votes) {
        int pts = num_candidates - 1;
        for (auto cand : ballot) {
            if (borda_scores.find(cand) == borda_scores.end()) {
                candidates.push_back(cand);
            }
            borda_scores[cand] += pts;
            pts--;
        }
    }

    int max_borda = -1;
    for (auto pair : borda_scores) {
        if (pair.second > max_borda) {
            max_borda = pair.second;
            res.borda = pair.first;
        }
    }

    res.condorcet = "None";
    for (auto candA : candidates) {
        bool wins_all = true;
        for (auto candB : candidates) {
            if (candA == candB) continue;
            int winsA = 0, winsB = 0;
            for (auto ballot : votes) {
                int posA = -1, posB = -1;
                int pos = 0;
                for (auto c : ballot) {
                    if (c == candA) posA = pos;
                    if (c == candB) posB = pos;
                    pos++;
                }
                if (posA < posB) winsA++;
                else winsB++;
            }
            if (winsA <= winsB) {
                wins_all = false;
                break;
            }
        }
        if (wins_all) {
            res.condorcet = candA;
            break;
        }
    }
    return res;
}

int main() {
    int n, m;
    if (cin >> n >> m) {
        vector<vector<string>> votes(n, vector<string>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> votes[i][j];
            }
        }
        VoteRes r = calculateVoting(votes);
        cout << r.borda << "\n" << r.condorcet << "\n";
    }
    return 0;
}
