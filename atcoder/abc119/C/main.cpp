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

vector<ll> abc;
vector<ll> bamboo;
vector<bool> used;
ll n;

ll dfs(int i, int j, int k, vector<ll>& total) {
  if (i == 0 && j == 0 && k == 0) {
    return abs(abc[0] - total[0]) + abs(abc[1] - total[1]) + abs(abc[2] - total[2]);
  }

  ll ret = LL_INF;
  int index = 0;
  if (i > 0) {
    index = 0;
    i--;
  } else if (j > 0) {
    index = 1;
    j--;
  } else {
    index = 2;
    k--;
  }
  rep(l, 0, n) {
    if (used[l]) continue;
    total[index] += bamboo[l];
    used[l] = true;
    chmin(ret, dfs(i, j, k, total));
    total[index] -= bamboo[l];
    used[l] = false;
  }

  return ret;
}

int main(int argc, char* argv[]) {
  abc.resize(3);
  cin >> n >> abc[0] >> abc[1] >> abc[2];
  bamboo.resize(n);
  scan(bamboo);
  used.resize(n);

  ll ans = LL_INF;
  vector<ll> total{0, 0, 0};
  rep(i, 1, n + 1 - 2) rep(j, 1, n + 1 - i - 1) rep(k, 1, n + 1 - i - j) {
    ll connect = ((i - 1) + (j - 1) + (k - 1)) * 10;
    chmin(ans, dfs(i, j, k, total) + connect);
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
