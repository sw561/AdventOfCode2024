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

  bool compare(int sequence[N]) {
    for (int i=0; i < N; i++) {
      if (data[(starting_index + i) % N] != sequence[i]) {
        return false;
      }
    }
    return true;
  }

  void insert(int x) {
    data[starting_index] = x;
    starting_index = (starting_index + 1) % N;
  }

  /*
  void print() {
    for (int i=0; i < N; i++) {
      cout << data[(starting_index + i) % N] << " ";
    }
    cout << "\n";
  }
  */

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

  bool operator==(const FixedQueue& rhs)const {
    for (int i=0; i < N; i++) {
      if (this->operator[](i) != rhs[i]) {
        return false;
      }
    }
    return true;
  }
};

int sell(long long secret, int sequence[N])
{

  FixedQueue f;
  ll new_secret;

  constexpr long long digit = 10;;
  for (int i=0; i < 2000; i++) {
    new_secret = next_secret(secret);

    f.insert(new_secret % digit - secret % digit);

    if (f.compare(sequence)) {
      return new_secret % digit;
    }

    secret = new_secret;
  }

  return 0;
}


int total_value(vector<ll> data, int sequence[N]) {
  int total = 0;
  for (ll x : data) {
    total += sell(x, sequence);
  }
  return total;
}

map<FixedQueue, int> sell(long long secret)
{
  FixedQueue f;
  map<FixedQueue, int> prices;
  ll new_secret;
  constexpr long long digit = 10;;

  for (int i=0; i < 2000; i++) {
    new_secret = next_secret(secret);

    f.insert(new_secret % digit - secret % digit);

    if (auto search = prices.find(f); search == prices.end()) {
      prices[f] = new_secret % digit;
    }

    secret = new_secret;
  }

  return prices;
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
    int sequence[N] = {-1,-1,0,2};
    int ret = sell(123, sequence);
    assert(ret == 6);
  }


  {
    // int sequence[N] = {-2,1,-1,3};

    // FixedQueue f_expectation;
    // for (int i=0; i < N; i++) {
    //   f_expectation.insert(sequence[i]);
    // }

    map<FixedQueue, int> score_for_sequences;

    for (ll x : data) {
      // cout << x << " " << sell(x, sequence) << "\n";
      map<FixedQueue, int> sequences = sell(x);

      for (auto it = sequences.begin(); it != sequences.end(); it++) {
        int current_score = 0;
        auto current = score_for_sequences.find(it->first);
        if (current != score_for_sequences.end()) {
          current_score = current->second;
        }
        score_for_sequences[it->first] = current_score + it->second;
      }

      // auto search = sequences.find(f_expectation);
      // if (search != sequences.end()) {
      //   cout << search->second << "\n";
      // }
      // else {
      //   cout << "Not found\n";
      // }
    }

    // Find sequence which gives the best total
    int best_score = 0;
    for (auto it=score_for_sequences.begin(); it != score_for_sequences.end(); it++) {
      best_score = max(best_score, it->second);
    }

    cout << best_score << "\n";
  }

}
