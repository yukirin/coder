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

static map<type_index, const char* const> scanType = {
    {typeid(int), "%d"}, {typeid(ll), "%lld"}, {typeid(double), "%lf"}, {typeid(char), "%c"}};

template <class T> static void scan(vector<T>& v);
static void scan(vector<string>& v, bool isWord = true);
template <class T> inline bool chmax(T& a, T b) {
  if (a < b) {
    a = b;
    return 1;
  }
  return 0;
}
template <class T> inline bool chmin(T& a, T b) {
  if (a > b) {
    a = b;
    return 1;
  }
  return 0;
}
template <class A, size_t N, class T> void Fill(A (&arr)[N], const T& val) {
  std::fill((T*)arr, (T*)(arr + N), val);
}

ll dp[3001][3001];

int main(int argc, char* argv[]) {
  // INFILE();

  string s, t;
  cin >> s >> t;

  int sl = s.size(), tl = t.size();

  REP(i, 1, sl + 1) {
    REP(j, 1, tl + 1) {
      chmax(dp[i][j], dp[i][j - 1]);
      chmax(dp[i][j], dp[i - 1][j]);
      chmax(dp[i][j], dp[i - 1][j - 1] + ll(s[i - 1] == t[j - 1]));
    }
  }

  string result;
  while (dp[sl][tl] != 0) {
    if (s[sl - 1] == t[tl - 1] && dp[sl - 1][tl - 1] == dp[sl][tl] - 1) {
      result.push_back(s[sl - 1]);
      sl--;
      tl--;
      continue;
    }

    dp[sl - 1][tl] == dp[sl][tl] ? sl-- : tl--;
  }

  reverse(ALL(result));
  cout << result << endl;
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
