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

struct RollingHash {
  static constexpr ll base1 = 1009LL;
  static constexpr ll base2 = 2009LL;
  static constexpr ll mod1 = 1000000007LL;
  static constexpr ll mod2 = 1000000009LL;
  string s;
  int n;
  vector<ll> hash1, hash2, pow1, pow2;
  vector<int> sa;

  RollingHash(const string& S)
      : s(S), n(sz(S)), hash1(n + 1, 0), hash2(n + 1, 0), pow1(n + 1, 1), pow2(n + 1, 1) {
    for (int i = 0; i < n; ++i) {
      hash1[i + 1] = (hash1[i] * base1 + S[i]) % mod1;
      hash2[i + 1] = (hash2[i] * base2 + S[i]) % mod2;
      pow1[i + 1] = (pow1[i] * base1) % mod1;
      pow2[i + 1] = (pow2[i] * base2) % mod2;
    }
  }

  // S の [l, r) のハッシュ値を返す
  inline pair<ll, ll> get(int l, int r) const {
    ll res1 = hash1[r] - hash1[l] * pow1[r - l] % mod1;
    if (res1 < 0) res1 += mod1;
    ll res2 = hash2[r] - hash2[l] * pow2[r - l] % mod2;
    if (res2 < 0) res2 += mod2;
    return make_pair(res1, res2);
  }

  // S のハッシュ値を返す
  inline pair<ll, ll> hash() const { return get(0, (int)hash1.size() - 1); }

  // LCP (Longest Common Prefix) [a, sz(S)), [b, sz(S))
  inline int getLCP(int a, int b) const {
    int len = min((int)hash1.size() - a, (int)hash1.size() - b);
    int low = 0, high = len;
    while (high - low > 1) {
      int mid = (low + high) >> 1;
      if (get(a, a + mid) != get(b, b + mid))
        high = mid;
      else
        low = mid;
    }
    return low;
  }

  // hash h1 と 長さ h2_len の文字列の hash h2 を結合
  pair<ll, ll> concat(pair<ll, ll> h1, pair<ll, ll> h2, int h2_len) {
    return make_pair((h1.first * pow1[h2_len] + h2.first) % mod1,
                     (h1.second * pow2[h2_len] + h2.second) % mod2);
  }

  // [l, r)
  bool match(int l1, int r1, int l2, int r2) { return get(l1, r1) == get(l2, r2); }

  // [l, r)
  bool match(int l, int r, ll_ll h) { return get(l, r) == h; }

  // build Suffix Array
  void buildSA() {
    auto f = [this](int i, int j) {
      int k = getLCP(i, j);
      return i + k >= n ? true : j + k >= n ? false : s[i + k] <= s[j + k];
    };

    sa.assign(n, 0);
    iota(all(sa), 0);
    sort(all(sa), f);
  }

  // 文字列tを含む接尾辞(after buldSA)のindex(of sa)の下限と上限(半開区間)を返す
  i_i lower_upper_bound(const string& t) {
    int ts = sz(t);
    auto lower_f = [this, &t](const int& i, const int& j) { return s.compare(max(i, j), n, t) < 0; };
    auto upper_f = [this, &t, ts](const int& i, const int& j) {
      int index = max(i, j);
      return ts <= (n - index) && equal(all(t), begin(s) + index);
    };

    auto l_it = lower_bound(all(sa), -1, lower_f);
    auto u_it = lower_bound(l_it, end(sa), -1, upper_f);
    return make_pair(l_it - begin(sa), u_it - begin(sa));
  }
};

int main(int argc, char* argv[]) {
  ll n;
  cin >> n;
  string s;
  cin >> s;

  RollingHash ro(s);

  ll ans = 0;
  rep(i, 0, n - 1) rep(j, i + 1, n) {
    ll l = ro.getLCP(i, j);
    chmax(ans, min<ll>(j - i, l));
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
