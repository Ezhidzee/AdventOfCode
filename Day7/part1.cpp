#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class hand {
private:
    string cards;

    int bit;

    int handRank;

public:
    hand(const string &card, int bit) {
        cards = card;
        this->bit = bit;

        map<char, int> cardsNames;
        for (int i = 0; i < card.size(); ++i) {
            cardsNames[card[i]] += 1;
        }

        if (cardsNames.size() == 1) {
            handRank = 1;
        } else if (cardsNames.size() == 2) {
            if (cardsNames.begin()->second == 1 || cardsNames.begin()->second == 4) {
                handRank = 2;
            } else handRank = 3;
        } else if (cardsNames.size() == 3) {
            for (pair<char, int> i: cardsNames) {
                if (i.second == 3) {
                    handRank = 4;
                    return;
                }
            }
            handRank = 5;
        } else if (cardsNames.size() == 4) {
            handRank = 6;
        } else handRank = 7;
    }

    const string &getCards() const {
        return cards;
    }

    int getBit() const {
        return bit;
    }

    const int &getHandRank() const {
        return handRank;
    }
};

int main() {
    ifstream input("input.txt");
    vector<hand> hands;

    string line;
    while (getline(input, line)) {
        hands.emplace_back(line.substr(0, line.find(' ')),
                           stoi(line.substr(line.find(' ') + 1, line.size() - line.find(' ') + 1)));
    }



    std::sort(hands.begin(), hands.end(), [](const hand &a, const hand &b) {
        map<char, int> lettersRanks = {{'A', 13}, {'K', 12}, {'Q', 11}, {'J', 10}, {'T', 9}, {'9', 8}, {'8', 7}, {'7', 6},
                                       {'6', 5}, {'5', 4}, {'4', 3}, {'3', 2}, {'2', 1}};
        if (a.getHandRank() == b.getHandRank()) {
            for (int i = 0; i < a.getCards().size(); ++i) {
                if (lettersRanks[a.getCards()[i]] < lettersRanks[b.getCards()[i]]) {
                    return true;
                } else if (lettersRanks[a.getCards()[i]] > lettersRanks[b.getCards()[i]]) return false;
            }
        } else {
            return a.getHandRank() > b.getHandRank();
        }
    });

    long long result = 0;
    for (int i = 0; i < hands.size(); ++i) result += hands[i].getBit() * (i + 1);

    cout << result;
}