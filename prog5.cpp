#include <iostream>
#include <vector>
#include <random>

using namespace std;

bool algo_cooperate(int32_t round_number, const vector<bool>& self_choices, const vector<bool>& enemy_choices) {
    return true;
}

bool algo_tit_for_tat(int32_t round_number, const vector<bool>& self_choices, const vector<bool>& enemy_choices) {
    if (round_number == 0) return true;
    return enemy_choices.back();
}

bool algo_betray(int32_t round_number, const vector<bool>& self_choices, const vector<bool>& enemy_choices) {
    return false;
}

struct MatchRes {
    int scoreA;
    int scoreB;
};

MatchRes play_match(bool (*algoA)(int32_t, const vector<bool>&, const vector<bool>&),
                    bool (*algoB)(int32_t, const vector<bool>&, const vector<bool>&),
                    int rounds) {
    vector<bool> historyA;
    vector<bool> historyB;
    MatchRes res = {0, 0};

    for (int i = 0; i < rounds; i++) {
        bool choiceA = algoA(i, historyA, historyB);
        bool choiceB = algoB(i, historyB, historyA);

        if (choiceA && choiceB) {
            res.scoreA += 24;
            res.scoreB += 24;
        } else if (!choiceA && !choiceB) {
            res.scoreA += 4;
            res.scoreB += 4;
        } else if (choiceA && !choiceB) {
            res.scoreB += 20;
        } else {
            res.scoreA += 20;
        }

        historyA.push_back(choiceA);
        historyB.push_back(choiceB);
    }
    return res;
}

int main() {
    int seed;
    if (cin >> seed) {
        mt19937 gen(seed);
        uniform_int_distribution<> dist(100, 200);

        int rounds = dist(gen);
        MatchRes m1 = play_match(algo_cooperate, algo_tit_for_tat, rounds);
        MatchRes m2 = play_match(algo_cooperate, algo_betray, rounds);
        MatchRes m3 = play_match(algo_tit_for_tat, algo_betray, rounds);

        cout << m1.scoreA << " " << m1.scoreB << "\n";
        cout << m2.scoreA << " " << m2.scoreB << "\n";
        cout << m3.scoreA << " " << m3.scoreB << "\n";
    }
    return 0;
}
