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

static map<type_index, const char* const> scanType = {
    {typeid(int), "%d"}, {typeid(ll), "%lld"}, {typeid(double), "%lf"}, {typeid(char), "%c"}};

template <class T> static void scan(vector<T>& v);
[[maybe_unused]] static void scan(vector<string>& v, bool isWord = true);
template <class T> static inline bool chmax(T& a, T b);
template <class T> static inline bool chmin(T& a, T b);
template <class A, size_t N, class T> static void Fill(A (&arr)[N], const T& val);

int indexes[100010][26];
int f_indexes[26];
int checked[26][26];
vector<int> index_list[26];

int main(int argc, char* argv[]) {
  string s, t;
  cin >> s >> t;

  for (int& index : f_indexes) {
    index = -1;
  }
  Fill(indexes, int(-1));

  REP(i, 0, s.size()) {
    int index = s[i] - 'a';
    f_indexes[index] = f_indexes[index] == -1 ? i : f_indexes[index];

    REP(j, 0, 26) {
      REP(k, checked[j][index], index_list[j].size()) { indexes[index_list[j][k]][index] = i; }
      checked[j][index] = index_list[j].size();
    }
    index_list[index].push_back(i);
  }

  int cur_index = f_indexes[t[0] - 'a'];
  ll result = cur_index + 1;
  if (cur_index == -1) {
    cout << -1 << endl;
    return 0;
  }

  REP(i, 1, t.size()) {
    int index = t[i] - 'a';

    if (indexes[cur_index][index] == -1) {
      result += s.size() - cur_index - 1;
      cur_index = f_indexes[index];
      result += cur_index + 1;

      if (cur_index == -1) {
        cout << -1 << endl;
        return 0;
      }
      continue;
    }

    int diff = indexes[cur_index][index] - cur_index;
    result += diff;
    cur_index = indexes[cur_index][index];
  }

  cout << result << endl;
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
