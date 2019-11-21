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

template <class T> struct CumulativeSum2D {
  int H, W;
  vector<vector<T>> data;

  CumulativeSum2D(int h, int w) : H(h + 1), W(w + 1), data(h + 1, vector<T>(w + 1, 0)) {}

  void add(int y, int x, T z) {
    ++x, ++y;
    if (y >= H || x >= W) return;
    data[y][x] += z;
  }

  void build() {
    for (int i = 1; i < H; i++)
      for (int j = 1; j < W; j++) {
        data[i][j] += data[i][j - 1] + data[i - 1][j] - data[i - 1][j - 1];
      }
  }

  // [sx, gx), [sy, gy) (Half-open section e.g. Not include gx and gy)
  T query(int sy, int sx, int gy, int gx) {
    return (data[gy][gx] - data[sy][gx] - data[gy][sx] + data[sy][sx]);
  }
};

int main(int argc, char* argv[]) {
  long long N;
  scanf("%lld", &N);
  long long K;
  scanf("%lld", &K);
  std::vector<long long> x(N);
  std::vector<long long> y(N);
  std::vector<std::string> c(N);
  for (int i = 0; i < N; i++) {
    scanf("%lld", &x[i]);
    scanf("%lld", &y[i]);
    std::cin >> c[i];
  }

  CumulativeSum2D<int> table(K * 4, K * 4);
  vector<i_i> diff{{0, 0}, {K * 2, 0}, {0, K * 2}, {K * 2, K * 2}};
  rep(i, 0, N) {
    int px = (x[i] + ((c[i][0] == 'W') ? K : 0)) % (K * 2);
    int py = y[i] % (K * 2);
    for (i_i d : diff) table.add(py + d.first, px + d.second, 1);
  }

  table.build();
  ll ans = 0;
  rep(i, 0, K * 2 + 1) rep(j, 0, K * 2 + 1) {
    ll tmp = table.query(0 + i, 0 + j, K + i, K + j);
    tmp += table.query(K + i, K + j, K + K + i, K + K + j);
    chmax(ans, tmp);
  }

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

template <class T> T mod(T a, T m) { return (a % m + m) % m; }
