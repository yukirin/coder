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
#define fi first
#define se second

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

int main(int argc, char* argv[]) {
  ll N;
  string S;
  cin >> N >> S;

  vec<vec<int>> colors(3);
  vec<char> cc{'R', 'G', 'B'};
  map<char, int> cmap{{'R', 0}, {'G', 1}, {'B', 2}};
  map<char, i_i> nmap{{'R', {1, 2}}, {'G', {2, 0}}, {'B', {0, 1}}};

  rep(i, 0, N) { colors[cmap[S[i]]].pb(i); }

  ll ans = 0;
  rep(i, 0, N) {
    auto [n1, n2] = nmap[S[i]];

    rep(k, 0, 2) {
      rep(j, 0, sz(colors[n1])) {
        if (colors[n1][j] <= i) continue;
        int index = colors[n1][j];
        ans += end(colors[n2]) - lower_bound(all(colors[n2]), index);

        int dup_index = index + (index - i);
        if (dup_index < N && S[dup_index] == cc[n2]) ans--;
      }
      swap(n1, n2);
    }
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

template <class T> inline T lcm(T a, T b) {
  T c = min(a, b), d = max(a, b);
  return c * (d / gcd(c, d));
}

template <class A, size_t N, class T> void Fill(A (&arr)[N], const T& val) {
  std::fill((T*)arr, (T*)(arr + N), val);
}

template <class T> T mod(T a, T m) { return (a % m + m) % m; }
