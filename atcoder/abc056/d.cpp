#include <algorithm>
#include <bitset>
#include <cfloat>
#include <cmath>
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

#define debug(x) cout << #x << ": " << x << endl
#define INFILE() freopen("input.txt", "r", stdin)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> i_i;
typedef pair<ll, int> ll_i;
typedef pair<int, ll> i_ll;
typedef pair<double, int> d_i;
typedef pair<ll, ll> ll_ll;
typedef pair<double, double> d_d;

constexpr ll LL_MOD = 1000000009;
constexpr int I_MOD = 1000000007;
constexpr double EPS = numeric_limits<double>::epsilon();
constexpr double PI = 3.14159265358979323846264338327950288;

void sI(int *pa, int size);
void sLL(ll *pa, int size);
void sD(double *pa, int size);
void sC(char *pa, int size);
void wS(string *ps, int size);
void lS(string *ps, int size);

bool dp[5001][5000];
bool dp2[5001][5000];

int main(int argc, char *argv[]) {
	INFILE();
  int n, k;
  int needs = 0;

  cin >> n >> k;

  int cards[n];
  sI(cards, n);

  for (int i = 0; i < 5001; ++i) {
    dp[i][0] = dp2[i][0] = true;
  }

  for (int i = 1; i < n + 1; ++i) {
    for (int j = 1; j < k; ++j) {
      bool prev = (j - cards[i - 1] < 0) ? false : dp[i - 1][j - cards[i - 1]];
      if (dp[i - 1][j] || prev) {
        dp[i][j] = true;
      }

      bool prev2 =
          (j - cards[n - i] < 0) ? false : dp2[i - 1][j - cards[n - i]];
      if (dp2[i - 1][j] || prev2) {
        dp2[i][j] = true;
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    if (cards[i] >= k) {
      needs++;
      continue;
    }

    bool b = false;

    for (int nv = k - cards[i]; nv < k; ++nv) {
      if (i == 0) {
        if (dp2[n - 1][nv]) {
          needs++;
          b = true;
          break;
        }
        continue;
      }

      if (i == n - 1) {
        if (dp[n - 1][nv]) {
          needs++;
          b = true;
          break;
        }
        continue;
      }

      for (int nv2 = 0; nv2 <= nv; ++nv2) {
        if (dp[i][nv2] && dp2[n - i - 1][nv - nv2]) {
          b = true;
          needs++;
          break;
        }
      }

      if (b)
        break;
    }
  }

  cout << n - needs << "\n";
  return 0;
}

void sI(int *pa, int size) {
  for (int i = 0; i < size; ++i) {
    scanf("%d", pa + i);
  }
}

void sLL(ll *pa, int size) {
  for (int i = 0; i < size; ++i) {
    scanf("%lld", pa + i);
  }
}

void sD(double *pa, int size) {
  for (int i = 0; i < size; ++i) {
    scanf("%lf", pa + i);
  }
}

void sC(char *pa, int size) {
  for (int i = 0; i < size; ++i) {
    scanf(" %c", pa + i);
  }
}

void wS(string *ps, int size) {
  for (int i = 0; i < size; ++i) {
    cin >> ps[i];
  }
}

void lS(string *ps, int size) {
  int i = 0;
  string s;
  getline(cin, s);

  if (s.size() != 0) {
    i++;
    ps[0] = s;
  }

  for (; i < size; ++i) {
    getline(cin, ps[i]);
  }
}
