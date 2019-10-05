#include <bits/stdc++.h>

#ifdef _DEBUG
#define debug(x) cerr << "line: " << __LINE__ << ", func: " << __func__ << " ->  " << #x << " = " << x << endl
#else
#define debug(x)
#endif

#define all(s) begin(s), end(s)
#define rall(s) rbegin(s), rend(s)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define rrep(i, a, b) for (int i = ((a)-1); i >= (b); i--)
#define pb push_back
#define sz(a) int((a).size())
#define put(a) ((cout) << (a) << (endl))
#define putf(a, n) ((cout) << (fixed) << (setprecision(n)) << (a) << (endl))

using namespace std;

using ll = long long;
using ull = unsigned long long;
using i_i = pair<int, int>;
using ll_ll = pair<ll, ll>;
using d_ll = pair<double, ll>;
using ll_d = pair<ll, double>;
using d_d = pair<double, double>;

static constexpr ll LL_INF = 1LL << 60;
static constexpr int I_INF = 1 << 28;
static constexpr double PI = static_cast<double>(3.14159265358979323846264338327950288);
static constexpr double EPS = numeric_limits<double>::epsilon();
static constexpr ll MOD = 1000000007;

static map<type_index, const char* const> scanType = {
    {typeid(int), "%d"}, {typeid(ll), "%lld"}, {typeid(double), "%lf"}, {typeid(char), "%c"}};

template <class T> static void scan(vector<T>& v);
[[maybe_unused]] static void scan(vector<string>& v, bool isWord = true);
template <class T> static inline bool chmax(T& a, T b);
template <class T> static inline bool chmin(T& a, T b);
template <class T> static inline T gcd(T a, T b);
template <class T> static inline T lcm(T a, T b);
template <class A, size_t N, class T> static void Fill(A (&arr)[N], const T& val);

ll dp[105][5][5][5];  // 0: " ", 1: "A", 2: "C", 3: "G", 4: "T"

bool agc(int cur, vector<int>& last) {
  int l = sz(last);
  if (last[l - 2] == 1 && last[l - 1] == 2 && cur == 3) return false;
  if (last[l - 2] == 1 && last[l - 1] == 3 && cur == 2) return false;
  if (last[l - 2] == 2 && last[l - 1] == 1 && cur == 3) return false;

  if (cur == 3 && last[l - 3] == 1 && (last[l - 1] == 2 || last[l - 2] == 2)) return false;
  return true;
}

ll dfs(int n, vector<int>& last) {
  int l = sz(last);
  if (dp[n][last[l - 3]][last[l - 2]][last[l - 1]] >= 0) return dp[n][last[l - 3]][last[l - 2]][last[l - 1]];
  if (!n) return 1;

  ll ret = 0;
  rep(i, 1, 5) {
    if (!agc(i, last)) continue;
    last.pb(i);
    ret += dfs(n - 1, last);
    last.pop_back();
  }

  return dp[n][last[l - 3]][last[l - 2]][last[l - 1]] = ret % MOD;
};

int main(int argc, char* argv[]) {
  long long N;
  scanf("%lld", &N);
  Fill(dp, ll(-1));

  vector<int> last{0, 0, 0};
  ll ans = dfs(N, last);
  put(ans);
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

template <class T> inline T gcd(T a, T b) { return __gcd(a, b); }

template <class T> inline T lcm(T a, T b) { return (a * b) / gcd(a, b); }

template <class A, size_t N, class T> void Fill(A (&arr)[N], const T& val) {
  std::fill((T*)arr, (T*)(arr + N), val);
}
