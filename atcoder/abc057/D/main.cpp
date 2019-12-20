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
#define deg2rad(x) (((x)*PI) / (180.0))
#define rad2deg(x) (((x) * (180.0)) / PI)

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using i_i = pair<int, int>;
using ll_ll = pair<ll, ll>;
using d_ll = pair<double, ll>;
using ll_d = pair<ll, double>;
using d_d = pair<double, double>;
template <class T> using vec = vector<T>;

static constexpr ll LL_INF = 1LL << 60;
static constexpr int I_INF = 1 << 28;
static constexpr double PI = static_cast<double>(3.14159265358979323846264338327950288);
static constexpr double EPS = numeric_limits<double>::epsilon();

static map<type_index, const char* const> scanType = {
    {typeid(int), "%d"}, {typeid(ll), "%lld"}, {typeid(double), "%lf"}, {typeid(char), "%c"}};

template <class T> static void scan(vector<T>& v);
[[maybe_unused]] static void scan(vector<string>& v, bool isWord = true);
template <class T> static inline bool chmax(T& a, T b);
template <class T> static inline bool chmin(T& a, T b);
template <class T> static inline T gcd(T a, T b);
template <class T> static inline T lcm(T a, T b);
template <class A, size_t N, class T> static void Fill(A (&arr)[N], const T& val);
template <class T> T mod(T a, T m);

ll_ll dp[51][51];

int main(int argc, char* argv[]) {
  ll n, a, b;
  cin >> n >> a >> b;
  vec<ll> v(n);
  scan(v);

  rep(i, 0, 51) rep(j, 0, 51) dp[i][j] = make_pair(-1, -1);
  dp[0][0].first = 0;
  dp[0][0].second = 1;

  rep(i, 0, n) rep(j, 0, n) {
    if (dp[i][j].first == -1) continue;

    if (dp[i + 1][j].first == -1) dp[i + 1][j] = make_pair(0, 0);
    if (dp[i + 1][j].first < dp[i][j].first) {
      dp[i + 1][j].first = dp[i][j].first;
      dp[i + 1][j].second = dp[i][j].second;
    } else if (dp[i + 1][j].first == dp[i][j].first) {
      dp[i + 1][j].second += dp[i][j].second;
    }

    if (dp[i + 1][j + 1].first == -1) dp[i + 1][j + 1] = make_pair(0, 0);
    if (dp[i + 1][j + 1].first < (dp[i][j].first + v[i])) {
      dp[i + 1][j + 1].first = dp[i][j].first + v[i];
      dp[i + 1][j + 1].second = dp[i][j].second;
    } else if (dp[i + 1][j + 1].first == (dp[i][j].first + v[i])) {
      dp[i + 1][j + 1].second += dp[i][j].second;
    }
  }

  ld max_avg = 0.0;
  rep(i, a, b + 1) {
    ll value = dp[n][i].first;
    ld avg = ld(value) / i;
    chmax(max_avg, avg);
  }

  ll sum = 0;
  rep(i, a, b + 1) {
    ll value = dp[n][i].first;
    ld avg = ld(value) / i;
    if (abs(max_avg - avg) <= EPS) sum += dp[n][i].second;
  }
  putf(max_avg, 20);
  put(sum);

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

template <class T> inline T lcm(T a, T b) {
  T c = min(a, b), d = max(a, b);
  return c * (d / gcd(c, d));
}

template <class A, size_t N, class T> void Fill(A (&arr)[N], const T& val) {
  std::fill((T*)arr, (T*)(arr + N), val);
}

template <class T> T mod(T a, T m) { return (a % m + m) % m; }