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
};

int key(const FixedQueue& f) {
  int ret = 0;
  for (int i = 0; i < N; i++) {
    if (f[i] == 10) { return -1; }
    ret *= 20;
    ret += f[i] + 10;
  }
  return ret;
}

struct Score {
  int score;
  int last_seen_index;
};

void sell(int index, long long secret, int * last_seen_index, int * scores, int size)
{
  FixedQueue f;
  ll new_secret;
  constexpr int digit = 10;

  for (int i=0; i < 2000; i++) {
    new_secret = next_secret(secret);

    f.insert(new_secret % digit - secret % digit);
    int score = (int)new_secret % digit;
    secret = new_secret;

    auto k = key(f);
    if (k < 0 || k >= size) {
      assert(i < 4);
      continue;
    }
    if (last_seen_index[k] < index) {
      last_seen_index[k] = index;
      scores[k] += score;
    }
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

    constexpr int size = 20*20*20*20;
    int * last_seen_index = (int *) calloc(size, sizeof(int));
    int * scores = (int *) calloc(size, sizeof(int));

    for (size_t index = 0; index < data.size(); index++) {
      sell(index+1, data[index], last_seen_index, scores, size);
    }

    // Find sequence which gives the best total
    int best_score = 0;
    for (size_t i = 0; i < size; i++) {
      best_score = max(best_score, scores[i]);
    }

    cout << best_score << "\n";

    free(last_seen_index);
    free(scores);
  }

}
