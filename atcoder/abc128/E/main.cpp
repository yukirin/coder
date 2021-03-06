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
#define fi first
#define se second

using namespace std;

using ll = long long;
using ull = unsigned long long;
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

template <typename Monoid, typename OperatorMonoid = Monoid> struct LazySegmentTree {
  using F = function<Monoid(Monoid, Monoid)>;
  using G = function<Monoid(Monoid, OperatorMonoid)>;
  using H = function<OperatorMonoid(OperatorMonoid, OperatorMonoid)>;
  using P = function<OperatorMonoid(OperatorMonoid, int)>;

  int sz;
  vector<Monoid> data;
  vector<OperatorMonoid> lazy;
  const F f;
  const G g;
  const H h;
  const P p;
  const Monoid M1;
  const OperatorMonoid OM0;

  // fは要素と要素のマージ, gは要素と作用素のマージ, hは作用素と作用素のマージ
  // pは作用素を下に降ろすときに行う演算(第一引数は作用素のもとの値, 第二引数は区間の長さ)
  // M1は要素の単位元, OM0は作用素の単位元である。
  LazySegmentTree(int n, const F f, const G g, const H h, const P p, const Monoid& M1,
                  const OperatorMonoid OM0)
      : f(f), g(g), h(h), p(p), M1(M1), OM0(OM0) {
    sz = 1;
    while (sz < n) sz <<= 1;
    data.assign(2 * sz, M1);
    lazy.assign(2 * sz, OM0);
  }

  void set(int k, const Monoid& x) { data[k + sz] = x; }

  void build() {
    for (int k = sz - 1; k > 0; k--) {
      data[k] = f(data[2 * k + 0], data[2 * k + 1]);
    }
  }

  void propagate(int k, int len) {
    if (lazy[k] != OM0) {
      if (k < sz) {
        lazy[2 * k + 0] = h(lazy[2 * k + 0], lazy[k]);
        lazy[2 * k + 1] = h(lazy[2 * k + 1], lazy[k]);
      }
      data[k] = g(data[k], p(lazy[k], len));
      lazy[k] = OM0;
    }
  }

  Monoid update(int a, int b, const OperatorMonoid& x, int k, int l, int r) {
    propagate(k, r - l);
    if (r <= a || b <= l) {
      return data[k];
    } else if (a <= l && r <= b) {
      lazy[k] = h(lazy[k], x);
      propagate(k, r - l);
      return data[k];
    } else {
      return data[k] =
                 f(update(a, b, x, 2 * k + 0, l, (l + r) >> 1), update(a, b, x, 2 * k + 1, (l + r) >> 1, r));
    }
  }

  Monoid update(int a, int b, const OperatorMonoid& x) { return update(a, b, x, 1, 0, sz); }

  Monoid query(int a, int b, int k, int l, int r) {
    propagate(k, r - l);
    if (r <= a || b <= l) {
      return M1;
    } else if (a <= l && r <= b) {
      return data[k];
    } else {
      return f(query(a, b, 2 * k + 0, l, (l + r) >> 1), query(a, b, 2 * k + 1, (l + r) >> 1, r));
    }
  }

  Monoid query(int a, int b) { return query(a, b, 1, 0, sz); }

  Monoid operator[](const int& k) { return query(k, k + 1); }
};

int main(int argc, char* argv[]) {
  ll n, q;
  cin >> n >> q;
  vec<ll> d(q);
  vec<pair<ll, ll_ll>> v(n);
  for (int i = 0; i < n; i++) cin >> (v[i].se.fi) >> (v[i].se.se) >> (v[i].fi);
  sort(all(v));
  scan(d);

  auto f = [](ll a, ll b) { return min(a, b); };
  auto g = [](ll a, ll b) { return b; };
  auto h = [](ll a, ll b) { return b; };
  auto p = [](ll a, ll len) { return a; };
  LazySegmentTree<ll> seg(q, f, g, h, p, LL_INF, LL_INF);
  seg.build();

  rrep(i, n, 0) {
    ll st = v[i].se.fi, en = v[i].se.se;
    ll pos = v[i].fi;

    int lower = lower_bound(all(d), st - pos) - begin(d);
    int upper = lower_bound(all(d), en - pos) - begin(d);
    seg.update(lower, upper, pos);
  }

  string ss = "";
  rep(i, 0, q) {
    ll num = seg[i];
    ss += to_string(num == LL_INF ? -1 : num) + "\n";
  }
  cout << ss;

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
