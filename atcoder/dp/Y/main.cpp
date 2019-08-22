#include <bits/stdc++.h>

#ifdef _DEBUG
#define debug(x) cerr << "line: " << __LINE__ << ", func: " << __func__ << " ->  " << #x << " = " << x << endl
#define INFILE freopen("input.txt", "r", stdin)
#else
#define debug(x)
#define INFILE
#endif

#define ALL(s) begin(s), end(s)
#define RALL(s) rbegin(s), rend(s)
#define REP(i, a, b) for (int i = (a); i < (b); i++)
#define RREP(i, a, b) for (int i = (a); i >= (b); i--)

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
static constexpr ll MOD = 1000000007;

static map<type_index, const char* const> scanType = {
    {typeid(int), "%d"}, {typeid(ll), "%lld"}, {typeid(double), "%lf"}, {typeid(char), "%c"}};

template <class T> static void scan(vector<T>& v);
[[maybe_unused]] static void scan(vector<string>& v, bool isWord = true);
template <class T> static inline bool chmax(T& a, T b);
template <class T> static inline bool chmin(T& a, T b);
template <class A, size_t N, class T> static void Fill(A (&arr)[N], const T& val);

int main(int argc, char* argv[]) {
  long long H;
  scanf("%lld",&H);
  long long W;
  scanf("%lld",&W);
  long long N;
  scanf("%lld",&N);
  std::vector<long long> r(N);
  std::vector<long long> c(N);
  for(int i = 0 ; i < N ; i++){
    scanf("%lld",&r[i]);
    scanf("%lld",&c[i]);
  }

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
