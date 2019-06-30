#include <bits/stdc++.h>

#define ALL(s) begin(s), end(s)
#define RALL(s) rbegin(s), rend(s)
#define DEBUG(x) cout << #x << ": " << x << endl
#define INFILE() freopen("input.txt", "r", stdin)
#define REP(i, a, b) for (int i = (a); i < (b); i++)
#define RREP(i, a, b) for (int i = (a); i >= (b); i--)

using namespace std;

using ll = long long;
using ull = unsigned long long;
using i_i = pair<int, int>;
using ll_ll = pair<ll, ll>;
using d_ll = pair<double, ll>;
using ll_d = pair<ll, double>;
using d_d = pair<double, double>;

static constexpr ll LL9_MOD = 1000000009;
static constexpr ll LL7_MOD = 1000000007;
static constexpr ll INF = 1LL << 60;
static constexpr double EPS = numeric_limits<double>::epsilon();
static constexpr double PI = 3.14159265358979323846264338327950288;

static map<type_index, const char *const> scanType = {
  { typeid(int), "%d" }, { typeid(ll), "%lld" }, { typeid(double), "%lf" }, { typeid(char), "%c" }};

template <class T> static void scan(vector<T>& v);
static void scan(vector<string>& v, bool isWord = true);
template <class A, size_t N, class T> void Fill(A (&arr)[N], const T &val);
template <class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template <class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }
template <class A, size_t N, class T> void Fill(A (&arr)[N], const T &val){ std::fill((T*)arr, (T*)(arr + N), val); }

ll dp[101][100001];

int main(int argc, char *argv[]) {
  INFILE();

  ll n, w;
  ll max_value = 100000;
  cin >> n >> w;

  vector<ll> weights(static_cast<int>(n));
  vector<ll> values(static_cast<int>(n));
  REP(i, 0, n) {
    cin >> weights[i] >> values[i];
  }

  Fill(dp, INF);
  dp[0][0] = 0;

  REP(i, 0, n) {
    REP(j, 0, max_value) {
      if (j != 0 && dp[i][j] == INF) continue;
      chmin(dp[i + 1][j], dp[i][j]);
      chmin(dp[i + 1][j + values[i]], dp[i][j] + weights[i]);
    }
  }

  RREP(i, max_value, 0) {
    if (dp[n][i] <= w) {
      cout << i << endl;
      return 0;
    }
  }
  
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
