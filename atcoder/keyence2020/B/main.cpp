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

int main(int argc, char* argv[]) {
  long long N;
  scanf("%lld", &N);
  vec<ll_ll> v(N);
  for (int i = 0; i < N; i++) {
    ll p, d;
    cin >> p >> d;
    v[i].fi = p + d;
    v[i].se = p - d;
  }
  sort(all(v));

  ll ans = 1;
  ll_ll cur = v[0];
  rep(i, 1, N) {
    if (v[i].se < cur.fi) continue;
    ans++;
    cur = v[i];
  }

  put(ans);
  return 0;
}
