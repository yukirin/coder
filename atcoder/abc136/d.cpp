#include <bits/stdc++.h>

#define ALL(s) begin(s), end(s)
#define RALL(s) rbegin(s), rend(s)
#define REP(i, a, b) for (int i = (a); i < (b); i++)
#define RREP(i, a, b) for (int i = (a); i >= (b); i--)

#ifdef _DEBUG
#define DEBUG(x) cout << "line: " << __LINE__ << ", func: " << __func__ << " ->  " << #x << " = " << x << endl
#define INFILE freopen("input.txt", "r", stdin)
#else
#define DEBUG(x)
#define INFILE
#endif

using namespace std;

using ll = long long;
using ull = unsigned long long;
using i_i = pair<int, int>;
using ll_ll = pair<ll, ll>;
using d_ll = pair<double, ll>;
using ll_d = pair<ll, double>;
using d_d = pair<double, double>;

static constexpr ll LL9_MOD = 1000000009LL;
static constexpr ll LL7_MOD = 1000000007LL;
static constexpr ll INF = 1LL << 60;
static constexpr double PI = static_cast<double>(3.14159265358979323846264338327950288);
static constexpr double EPS = numeric_limits<double>::epsilon();

static map<type_index, const char* const> scanType = {
    {typeid(int), "%d"}, {typeid(ll), "%lld"}, {typeid(double), "%lf"}, {typeid(char), "%c"}};

template <class T> static void scan(vector<T>& v);
static void scan(vector<string>& v, bool isWord = true);
template <class T> inline bool chmax(T& a, T b);
template <class T> inline bool chmin(T& a, T b);
template <class A, size_t N, class T> void Fill(A (&arr)[N], const T& val);

int main(int argc, char* argv[]) {
  INFILE;

  string s;
  cin >> s;

  ll l = s.size();
  ll first = 0, last = 0;
  vector<ll> result(l, 0);

  char stop = 'L';

  while (last < l) {
    last++;
    if (s[last] == stop || last == l) {
      for (int i = first; i < last; i++) {
        ll pivot = stop == 'L' ? last : first;
        ll diff = abs(pivot - i);
        ll pos = pivot - (diff % 2);
        result[pos]++;
      }

      first = last;
      stop = stop == 'L' ? 'R' : 'L';
    }
  }

  string ans;
  for (ll v : result) {
    ans += to_string(v);
    ans += " ";
  }
  ans.pop_back();
  cout << ans << endl;
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