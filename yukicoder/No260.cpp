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
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <vector>

#define DEBUG(x) cout << #x << ": " << x << endl
#define INFILE() freopen("input.txt", "r", stdin)
#define REP(i, a, b) for (int i = (a); i < (b); i++)
#define REPC(i, a) REP(i, 0, a)
#define ALL(s) begin(s), end(s)
#define RALL(s) rbegin(s), rend(s)

using namespace std;

using ll = long long;
using ull = unsigned long long;
using i_i = pair<int, int>;
using ll_i = pair<ll, int>;
using i_ll = pair<int, ll>;
using d_i = pair<double, int>;
using ll_ll = pair<ll, ll>;
using d_d = pair<double, double>;

static constexpr ll LL_MOD = 1000000007;
static constexpr int I_MOD = 1000000007;
static constexpr double EPS = numeric_limits<double>::epsilon();
static constexpr double PI = 3.14159265358979323846264338327950288;

template <class T> static void scan(vector<T> &v);
static void scan(vector<string> &v, bool isWord = true);

ll dp[10010][2][2][3][8];
ll dp2[10010][2][2][3][8];

int main(int argc, char *argv[]) {
	INFILE();
  string a, b;
  cin >> a >> b;
  int la = a.size(), lb = b.size();

  dp[0][0][0][0][0] = dp2[0][0][0][0][0] = 1;

  REPC(i, la) REPC(less, 2) REPC(t, 2) REPC(m3, 3) REPC(m8, 8) {
    int lim = less ? 9 : a[i] - '0';
    REPC(n, lim + 1) {
      dp[i + 1][less || n < lim][t || n == 3][(m3 + n) % 3]
        [(m8 * 10 + n) % 8] += (dp[i][less][t][m3][m8] % LL_MOD);
    }
  }

  REPC(i, lb) REPC(less, 2) REPC(t, 2) REPC(m3, 3) REPC(m8, 8) {
    int lim = less ? 9 : b[i] - '0';
    REPC(n, lim + 1) {
      dp2[i + 1][less || n < lim][t || n == 3][(m3 + n) % 3]
         [(m8 * 10 + n) % 8] += (dp2[i][less][t][m3][m8] % LL_MOD);
    }
  }

  ll countA = 0, countB = 0;

  REPC(t, 2) REPC(m3, 3) REPC(m8, 8) {
    if ((t || (m3 == 0)) && (m8 != 0)) {
      (countA += dp[la][1][t][m3][m8]) %= LL_MOD;
    }
  }

  REPC(less, 2) REPC(t, 2) REPC(m3, 3) REPC(m8, 8) {
    if ((t || (m3 == 0)) && (m8 != 0)) {
      (countB += dp2[lb][less][t][m3][m8]) %= LL_MOD;
    }
  }

  cout << (countB - countA + LL_MOD) % LL_MOD << "\n";
  return 0;
}

template <class T> static void scan(vector<T> &v) {
  map<type_index, const char *const> m = {{typeid(int), "%d"},
                                          {typeid(ll), "%lld"},
                                          {typeid(double), "%lf"},
                                          {typeid(char), "%c"}};

  auto tFormat = m[typeid(T)];

  for (T &n : v) {
    scanf(tFormat, &n);
  }
}

static void scan(vector<string> &v, bool isWord) {
  if (isWord) {
    for (auto &n : v) {
      cin >> n;
    }
    return;
  }

  int i = 0, size = v.size();
  string s;
  getline(cin, s);

  if (s.size() != 0) {
    i++;
    v[0] = s;
  }

  for (; i < size; ++i) {
    getline(cin, v[i]);
  }
}
