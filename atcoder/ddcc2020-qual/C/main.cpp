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
using i_i = pair<int, int>;
using ll_ll = pair<ll, ll>;
using d_ll = pair<double, ll>;
using ll_d = pair<ll, double>;
using d_d = pair<double, double>;

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

int main(int argc, char* argv[]) {
  ll h, w, k;
  cin >> h >> w >> k;
  vector<string> table(h);
  rep(i, 0, h) cin >> table[i];

  vector<i_i> s;
  rep(i, 0, h) rep(j, 0, w) {
    if (table[i][j] == '.') continue;
    s.pb({i, j});
  }

  vector<vector<int>> ans(h, vector<int>(w, 0));
  rep(i, 0, sz(s)) {
    int x = s[i].second, y = s[i].first;
    rep(j, x, w) {
      if (ans[y][j] != 0) continue;
      if (x != j && table[y][j] == '#') break;
      ans[y][j] = i + 1;
    }
    rrep(j, x, 0) {
      if (ans[y][j] != 0) continue;
      if (x != j && table[y][j] == '#') break;
      ans[y][j] = i + 1;
    }
  }

  rep(i, 0, h - 1) {
    if (ans[i][0] == 0) continue;
    if (ans[i + 1][0] != 0) continue;
    rep(j, 0, w) ans[i + 1][j] = ans[i][j];
  }
  rrep(i, h, 1) {
    if (ans[i][0] == 0) continue;
    if (ans[i - 1][0] != 0) continue;
    rep(j, 0, w) ans[i - 1][j] = ans[i][j];
  }

  rep(i, 0, h) {
    string s = "";
    rep(j, 0, w) { s += to_string(ans[i][j]) + " "; }
    s.pop_back();
    cout << s << endl;
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

template <class T> T mod(T a, T m) { return (a % m + m) % m; }
