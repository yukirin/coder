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

template <typename FI> void parted_rotate(FI first1, FI last1, FI first2, FI last2) {
  if (first1 == last1 || first2 == last2) return;
  FI next = first2;
  while (first1 != next) {
    std::iter_swap(first1++, next++);
    if (first1 == last1) first1 = first2;
    if (next == last2) {
      next = first2;
    } else if (first1 == first2) {
      first2 = next;
    }
  }
}

template <typename BI> bool next_combination_imp(BI first1, BI last1, BI first2, BI last2) {
  if (first1 == last1 || first2 == last2) return false;
  auto target = last1;
  --target;
  auto last_elem = last2;
  --last_elem;
  // find right-most incrementable element: target
  while (target != first1 && !(*target < *last_elem)) --target;
  if (target == first1 && !(*target < *last_elem)) {
    parted_rotate(first1, last1, first2, last2);
    return false;
  }
  // find the next value to be incremented: *next
  auto next = first2;
  while (!(*target < *next)) ++next;
  std::iter_swap(target++, next++);
  parted_rotate(target, last1, next, last2);
  return true;
}

// INVARIANT: is_sorted(first, mid) && is_sorted(mid, last)
template <typename BI> inline bool next_combination(BI first, BI last, BI mid) {
  return next_combination_imp(first, mid, mid, last);
}

// INVARIANT: is_sorted(first, mid) && is_sorted(mid, last)
template <typename BI> inline bool prev_combination(BI first, BI last, BI mid) {
  return next_combination_imp(mid, last, first, mid);
}

int main(int argc, char* argv[]) {
  int n;
  cin >> n;
  vec<vec<i_i>> a(n);

  rep(i, 0, n) {
    int b;
    cin >> b;
    rep(j, 0, b) {
      int x, y;
      cin >> x >> y;
      x--;
      a[i].pb({x, y});
    }
  }

  ll ans = 0;
  rep(i, 0, (1 << n)) {
    ll count = 0;
    bool check = true;
    rep(j, 0, n) {
      if (!(i & (1 << j))) continue;
      count++;
      rep(k, 0, sz(a[j])) {
        int who = a[j][k].first;
        int t = a[j][k].second;
        if (bool(i & (1 << who)) == bool(t)) continue;
        check = false;
        break;
      }

      if (!check) break;
    }

    if (!check) continue;
    ans = max(ans, count);
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
