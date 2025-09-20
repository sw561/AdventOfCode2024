
#include "stdio.h"
#include "assert.h"

#define MAX_Z 45

int x_global[MAX_Z];
int y_global[MAX_Z];

#include "day24.d"
#include "day24.h"

typedef long long ll;

void assign_vals(ll x, int * x_mem)
{
  for (size_t i=0; i < MAX_Z; i++) {
    x_mem[i] = (x & (1ll << i)) ? 1 : 0;
  }
}

ll eval()
{
  ll ret = 0;
  for (int i=0; i <= MAX_Z; i++) {
    ret |= ((ll)z(i) << i);
  }

  return ret;
}

ll wired_sum(ll x, ll y)
{
  assign_vals(x, x_global);
  assign_vals(y, y_global);

  return eval();
}

int main() {
  #include "day24.setters"
  printf("%lld\n", eval());

  for (ll x=0; x < 1; x++) {
  for (ll y=1; y < (1ll << 43); y <<= 1) {
    ll ret = wired_sum(x, y);
    if (ret != x + y) {
      printf("STOP: %lld != %lld + %lld\n", ret, x, y);
      break;
    }
  }}
}
