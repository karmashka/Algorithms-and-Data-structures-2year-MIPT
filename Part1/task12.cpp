//Дана таблица, состоящая из N строк и M столбцов. В каждой клетке таблицы записано одно из чисел: 0 или 1. Расстоянием между клетками (x1, y1) и (x2, y2) назовем сумму |x1-x2|+|y1-y2|. Вам необходимо построить таблицу, в клетке (i, j) которой будет записано минимальное расстояние между клеткой (i, j) начальной таблицы и клеткой, в которой записана 1. Гарантируется, что хотя бы одна 1 в таблице есть.
//
//Input format
//В первой строке вводятся два натуральных числа N и M, не превосходящих 100. Далее идут N строк по M чисел — элементы таблицы.
//
//Output format
//Требуется вывести N строк по M чисел — элементы искомой таблицы.
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

enum e_color {
  white,
  gray,
  black
};

struct coord {
  coord(int x = 0, int y = 0): x(x), y(y) {}

  coord(pair<int, int> p): x(p.first), y(p.second) {}

  int x;
  int y;

  bool operator<(const coord &rhs) const {
    if (x < rhs.x)
      return true;
    if (rhs.x < x)
      return false;
    return y < rhs.y;
  }

  bool operator>(const coord &rhs) const {
    return rhs < *this;
  }

  bool operator<=(const coord &rhs) const {
    return !(rhs < *this);
  }

  bool operator>=(const coord &rhs) const {
    return !(*this < rhs);
  }

  bool operator==(const coord &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
  }

  bool operator!=(const coord &rhs) const {
    return !(rhs == *this);
  }
};

class Vertex {
private:
  e_color m_colour = white;
  coord m_board_number;
  coord m_parent;
  int m_depth = -1;
  vector <coord> m_related;

  static bool is_on_board(int x, int y, int size_x, int size_y) {
    return (x > 0) && (y > 0) && (x <= size_x) && (y <= size_y);
  }
public:
  Vertex () = default;

  Vertex(const Vertex& second) = default;

  explicit Vertex (coord num, int board_size_x, int board_size_y): m_board_number(num), m_parent(-1, -1) {
    int x = num.x;
    int y = num.y;
    if (is_on_board(x - 1, y, board_size_x, board_size_y)) {
      m_related.emplace_back(make_pair(x - 1, y));
    }
    if (is_on_board(x, y - 1, board_size_x, board_size_y)) {
      m_related.emplace_back(make_pair(x, y - 1));
    }
    if (is_on_board(x + 1, y, board_size_x, board_size_y)) {
      m_related.emplace_back(make_pair(x + 1, y));
    }
    if (is_on_board(x, y + 1, board_size_x, board_size_y)) {
      m_related.emplace_back(make_pair(x, y + 1));
    }

  }

  ~Vertex() = default;

  void set_colour (e_color new_colour) {
    m_colour = new_colour;
  }

  e_color get_colour() const {
    return m_colour;
  }

  void set_number(coord num) {
    m_board_number = num;
  }

  coord get_number() const {
    return m_board_number;
  }

  void set_depth(int depth) {
    m_depth = depth;
  }

  int get_depth() const {
    return m_depth;
  }

  void add_parent(const coord parent) {
    m_parent = parent;
  }

  vector <coord>& get_related()  {
    return m_related;
  }

  coord get_parent() const {
    return m_parent;
  }

  bool operator== (const Vertex& v) const {
    return m_board_number == v.m_board_number;
  }

  bool operator!= (const Vertex& v) const {
    return !(*this == v);
  }

};

class Graph {
private:
  int m_time = 0;
  vector<vector<Vertex>> graph;
public:
  Graph() = default;
  explicit Graph(int y, int x) {
    for (int i = 0; i <= y; ++i) {
      graph.emplace_back();
      for (int j = 0; j <= x; ++j) {
        graph[i].push_back(Vertex({j, i}, x, y));
      }
    }
  }

  int get_size() const {
    return graph.size() - 1;
  }

  Vertex& get_vert(coord i) {
    return graph[i.y][i.x];
  }
  void set_time(int time) {
    m_time = time;
  }

  int get_time() const {
    return m_time;
  }

  void time_update() {
    m_time++;
  }

  void reset() {
    for (auto& row: graph) {
      for (auto& elem: row) {
        elem.set_colour(white);
      }
    }
  }

};

int BFS(Graph& graph, coord start, vector<vector<int>>& input) {
  queue<coord> q;
  graph.reset();
  graph.get_vert(start).set_depth(0);
  graph.get_vert(start).set_colour(gray);
  q.push(start);

  while(!q.empty()) {
    coord v = q.front();
    q.pop();
    if (input[v.y][v.x] == 1) {
      return graph.get_vert(v).get_depth();
    }
    for (coord neighbor:graph.get_vert(v).get_related()) {
      Vertex& u = graph.get_vert(neighbor);
      if (u.get_colour() == white) {
        u.set_colour(gray);
        u.set_depth(graph.get_vert(v).get_depth() + 1);
        q.push(neighbor);
      }
    }
    graph.get_vert(v).set_colour(black);
  }
}



int main() {
  int N, M;
  cin >> N >> M;
  Graph g(N, M);
  vector<vector<int>> input(N + 1, vector<int>(M + 1, 0));

  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= M; ++j) {
      int elem;
      cin >> elem;
      input[i][j] = elem;
    }
  }

  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= M; ++j) {
      cout << BFS(g, coord(j, i), input) << ' ';
    }
    cout << '\n';
  }
  return 0;
}