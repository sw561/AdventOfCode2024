#include <iostream>

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

int main()
{
  ll x;
  ll total = 0;
  while (cin >> x) {
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

  cout << "-1\n";
}
