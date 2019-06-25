#include <algorithm>
#include <bitset>
#include <cfloat>
#include <cmath>
#include <ctime>
#include <chrono>
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
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define ALL(s) begin(s), end(s)
#define RALL(s) rbegin(s), rend(s)
#define DEBUG(x) cout << #x << ": " << x << endl
#define INFILE() freopen("input.txt", "r", stdin)
#define REP(i, a, b) for (int i = (a); i < (b); i++)
#define RREP(i, a, b) for (int i = (a); i >= (b); i--)
#define REPC(i, a) REP(i, 0, a)
#define RREPC(i, a) RREP(i, a, 0)

using namespace std;

using ll = long long;
using ull = unsigned long long;
using i_i = pair<int, int>;
using ll_ll = pair<ll, ll>;
using d_i = pair<double, int>;
using i_d = pair<int, double>;
using d_d = pair<double, double>;

static constexpr ll LL_MOD = 1000000009;
static constexpr ll LL2_MOD = 1000000007;
static constexpr ll INF = 1LL << 60;
static constexpr double EPS = numeric_limits<double>::epsilon();
static constexpr double PI = 3.14159265358979323846264338327950288;

static map<type_index, const char *const> scanType = {
  { typeid(int), "%d" }, { typeid(ll), "%lld" }, { typeid(double), "%lf" }, { typeid(char), "%c" }};

template <class T> static void scan(vector<T>& v);
static void scan(vector<string>& v, bool isWord = true);
template <class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template <class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

ll dp[100010][3];

int main(int argc, char *argv[]) {
  INFILE();

  int n;
  cin >> n;
  vector<ll> a(n), b(n), c(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i] >> b[i] >> c[i];
  }
  
  dp[0][0] = a[0];
  dp[0][1] = b[0];
  dp[0][2] = c[0];

  for (int i = 0; i < n - 1; i++) {
    chmax(dp[i + 1][0], dp[i][1] + a[i + 1]);
    chmax(dp[i + 1][0], dp[i][2] + a[i + 1]);

    chmax(dp[i + 1][1], dp[i][0] + b[i + 1]);
    chmax(dp[i + 1][1], dp[i][2] + b[i + 1]);

    chmax(dp[i + 1][2], dp[i][0] + c[i + 1]);
    chmax(dp[i + 1][2], dp[i][1] + c[i + 1]);
  }


  cout << *max_element(ALL(dp[n - 1])) << endl;
  return 0;
}

template <class T> static void scan(vector<T>& v) {
  auto tFormat = scanType[typeid(T)];
  for (T& n : v) {
    scanf(tFormat, &n);
  }
}

static void scan(vector<string>& v, bool isWord) {
  if (isWord) {
    for (auto& n : v) {
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
