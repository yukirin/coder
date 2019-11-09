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
  ll n;
  cin >> n;
  vector<ll> a(n);
  scan(a);

  vector<ll> sum(n + 1);
  rep(i, 0, n) sum[i + 1] = sum[i] + a[i];
  vector<ll> l_ans(n), r_ans(n);

  ll l_middle = 1, r_middle = n - 1;
  rep(i, 2, n - 1) {
    double sub = abs(sum[i] / 2.0 - sum[l_middle]);
    rep(l, l_middle, i) {
      if (l + 1 == i) break;
      double half = abs(sum[i] / 2.0 - sum[l + 1]);
      if (half >= sub) break;
      l_middle = l + 1;
      sub = half;
    }

    l_ans[i] = l_middle;
  }

  rrep(i, n - 1, 2) {
    double sub = abs((sum[n] - sum[i]) / 2.0 - (sum[n] - sum[r_middle]));
    rrep(r, r_middle + 1, i + 1) {
      if (r - 1 == i) break;
      double half = abs((sum[n] - sum[i]) / 2.0 - (sum[n] - sum[r - 1]));
      if (half >= sub) break;
      r_middle = r - 1;
      sub = half;
    }

    r_ans[i] = r_middle;
  }

  ll ans = LL_INF;
  rep(i, 2, n - 1) {
    ll l = l_ans[i], r = r_ans[i];
    vector<ll> tmp(4);
    tmp[0] = sum[l], tmp[1] = sum[i] - sum[l];
    tmp[2] = sum[r] - sum[i], tmp[3] = sum[n] - sum[r];

    ll v_max = *max_element(all(tmp));
    ll v_min = *min_element(all(tmp));
    chmin(ans, abs(v_max - v_min));
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
