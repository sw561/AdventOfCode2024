

#include "stdio.h"
#include "day24.d"
#include "day24.h"

typedef long long ll;

int main() {

  ll ret = 0;
  for (int i=0; i <= max_z; i++) {
    ret |= ((ll)z(i) << i);
  }

  printf("%lld\n", ret);

}
