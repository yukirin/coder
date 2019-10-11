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

static map<type_index, const char* const> scanType = {
    {typeid(int), "%d"}, {typeid(ll), "%lld"}, {typeid(double), "%lf"}, {typeid(char), "%c"}};

template <class T> static void scan(vector<T>& v);
[[maybe_unused]] static void scan(vector<string>& v, bool isWord = true);
template <class T> static inline bool chmax(T& a, T b);
template <class T> static inline bool chmin(T& a, T b);
template <class T> static inline T gcd(T a, T b);
template <class T> static inline T lcm(T a, T b);
template <class A, size_t N, class T> static void Fill(A (&arr)[N], const T& val);

int main(int argc, char* argv[]) {
  ll a, b, q;
  cin >> a >> b >> q;
  vector<ll> s(a + 2), t(b + 2), x(q);
  rep(i, 0, a) cin >> s[i + 1];
  rep(i, 0, b) cin >> t[i + 1];
  rep(i, 0, q) cin >> x[i];
  s[0] = -LL_INF, s[a + 1] = LL_INF;
  t[0] = -LL_INF, t[b + 1] = LL_INF;

  vector<ll> ans(q, LL_INF);
  rep(i, 0, q) {
    ll pos = x[i];
    auto s_itr = lower_bound(all(s), pos);
    auto t_itr = lower_bound(all(t), pos);

    ll s_right = abs(pos - *s_itr);
    ll s_left = abs(pos - *(--s_itr));
    ll t_right = abs(pos - *t_itr);
    ll t_left = abs(pos - *(--t_itr));

    chmin(ans[i], max(s_left, t_left));
    chmin(ans[i], max(s_right, t_right));
    for (ll_ll p : {ll_ll{s_right, t_left}, ll_ll{t_right, s_left}}) {
      chmin(ans[i], p.first * 2 + p.second);
      chmin(ans[i], p.second * 2 + p.first);
    }
  }

  for (auto val : ans) put(val);
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
