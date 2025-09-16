#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <set>

const int big = 16777216;

typedef long long ll;
using namespace std;

ll next_secret(ll x)
{
  x ^= x * 64;
  x %= big;

  x ^= x / 32;
  x %= big;

  x ^= x * 2048;
  x %= big;

  return x;
}

#define N 4

struct FixedQueue {
  int starting_index;
  int data[N];

  FixedQueue() : starting_index(0) {
    for (int i=0; i < N; i++) {
      data[i] = 10; // 10 means invalid...
    }
  }

  void insert(int x) {
    data[starting_index] = x;

    starting_index = starting_index == 3 ? 0 : starting_index + 1;
  }

  int operator[](const int& i) const {
    return data[(starting_index + i) % N];
  }

  bool operator<(const FixedQueue& rhs)const {
    for (int i=0; i < N; i++) {
      if (this->operator[](i) < rhs[i]) {
        return true;
      } else if (this->operator[](i) > rhs[i]) {
        return false;
      }
    }
    return false;
  }
};

struct Score {
  int score;
  int last_seen_index;
};

void sell(int index, long long secret, map<FixedQueue, Score>& score_for_sequences)
{
  FixedQueue f;
  ll new_secret;
  constexpr int digit = 10;

  for (int i=0; i < 2000; i++) {
    new_secret = next_secret(secret);

    f.insert(new_secret % digit - secret % digit);
    int score = (int)new_secret % digit;

    auto search = score_for_sequences.find(f);
    if (search == score_for_sequences.end()) {
      // It was not found
      score_for_sequences[f] = {
        .score = score,
        .last_seen_index = index
      };
    } else if (search->second.last_seen_index < index) {
      search->second.score += score;
      search->second.last_seen_index = index;
    }
    secret = new_secret;
  }
}
  


int main()
{
  vector<ll> data;
  ll x;
  ll total = 0;
  while (cin >> x) {
    data.push_back(x);
    ll s2000 = x;
    for (int i=0; i < 2000; i++) {
      s2000 = next_secret(s2000);
    }
#ifdef TEST
    cout << x << ": " << s2000 << "\n";
#endif
    total += s2000;
  }
  cout << total << "\n";

#ifdef TEST
  return 0;
#endif


  {

    map<FixedQueue, Score> score_for_sequences;

    for (size_t index = 0; index < data.size(); index++) {
      ll x = data[index];
      sell(index, x, score_for_sequences);
    }

    // Find sequence which gives the best total
    int best_score = 0;
    for (auto it=score_for_sequences.begin(); it != score_for_sequences.end(); it++) {
      best_score = max(best_score, it->second.score);
    }

    cout << best_score << "\n";
  }

}
