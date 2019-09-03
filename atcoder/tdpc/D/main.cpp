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

using namespace std;

using ll = long long;
using ull = unsigned long long;
using i_i = pair<int, int>;
using ll_ll = pair<ll, ll>;
using d_ll = pair<double, ll>;
using ll_d = pair<ll, double>;
using d_d = pair<double, double>;

static constexpr ll INF = 1LL << 60;
static constexpr double PI = static_cast<double>(3.14159265358979323846264338327950288);
static constexpr double EPS = numeric_limits<double>::epsilon();

static map<type_index, const char* const> scanType = {
    {typeid(int), "%d"}, {typeid(ll), "%lld"}, {typeid(double), "%lf"}, {typeid(char), "%c"}};

template <class T> static void scan(vector<T>& v);
[[maybe_unused]] static void scan(vector<string>& v, bool isWord = true);
template <class T> static inline bool chmax(T& a, T b);
template <class T> static inline bool chmin(T& a, T b);
template <class A, size_t N, class T> static void Fill(A (&arr)[N], const T& val);

double dp[101][70][50][40];

int main(int argc, char* argv[]) {
  ll n, d;
  cin >> n >> d;
  vector<ll> divs{2, 3, 5};
  vector<int> counter{0, 0, 0};

  dp[0][0][0][0] = 1;

  rep(i, 0, sz(divs)) {
    while (d % divs[i] == 0) {
      d /= divs[i];
      counter[i]++;
    }
  }

  if (d != 1) {
    cout << 0 << endl;
    return 0;
  }

  rep(i, 0, n) rep(v2, 0, 70) rep(v3, 0, 50) rep(v5, 0, 40) {
    if (dp[i][v2][v3][v5] == 0) continue;

    double p = dp[i][v2][v3][v5] * (1.0 / 6.0);
    dp[i + 1][v2][v3][v5] += p;
    dp[i + 1][min(counter[0], v2 + 1)][v3][v5] += p;
    dp[i + 1][v2][min(counter[1], v3 + 1)][v5] += p;
    dp[i + 1][min(counter[0], v2 + 2)][v3][v5] += p;
    dp[i + 1][v2][v3][min(counter[2], v5 + 1)] += p;
    dp[i + 1][min(counter[0], v2 + 1)][min(counter[1], v3 + 1)][v5] += p;
  }

  cout << fixed << setprecision(9) << dp[n][counter[0]][counter[1]][counter[2]] << endl;
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

template <class A, size_t N, class T> void Fill(A (&arr)[N], const T& val) {
  std::fill((T*)arr, (T*)(arr + N), val);
}
