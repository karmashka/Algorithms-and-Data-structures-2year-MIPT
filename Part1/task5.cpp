//На шахматной доске NxN в клетке (x1, y1) стоит голодный шахматный конь. Он хочет попасть в клетку (x2, y2), где растет вкусная шахматная трава. Какое наименьшее количество ходов он должен для этого сделать?
//
//Input format
//На вход программы поступает пять чисел: N, x1, y1, x2, y2 (5 ≤ N ≤ 20, 1 ≤ x1, y1, x2, y2 ≤ N). Левая верхняя клетка доски имеет координаты (1, 1), правая нижняя — (N, N).
//
//Output format
//В первой строке выведите единственное число K — наименьшее необходимое число ходов коня. В каждой из следующих K+1 строк должно быть записано 2 числа — координаты очередной клетки в пути коня.
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

  static bool is_on_board(int x, int y, int size) {
    return (x > 0) && (y > 0) && (x <= size) && (y <= size);
  }
public:
  Vertex () = default;

  Vertex(const Vertex& second) = default;

  explicit Vertex (coord num, int board_size): m_board_number(num), m_parent(-1, -1) {
    int x = num.x;
    int y = num.y;
    if (is_on_board(x - 1, y + 2, board_size)) {
      m_related.emplace_back(make_pair(x - 1, y + 2));
    }
    if (is_on_board(x - 1, y - 2, board_size)) {
      m_related.emplace_back(make_pair(x - 1, y - 2));
    }
    if (is_on_board(x - 2, y + 1, board_size)) {
      m_related.emplace_back(make_pair(x - 2, y + 1));
    }
    if (is_on_board(x - 2, y - 1, board_size)) {
      m_related.emplace_back(make_pair(x - 2, y - 1));
    }
    if (is_on_board(x + 1, y + 2, board_size)) {
      m_related.emplace_back(make_pair(x + 1, y + 2));
    }
    if (is_on_board(x + 1, y - 2, board_size)) {
      m_related.emplace_back(make_pair(x + 1, y - 2));
    }
    if (is_on_board(x + 2, y + 1, board_size)) {
      m_related.emplace_back(make_pair(x + 2, y + 1));
    }
    if (is_on_board(x + 2, y - 1, board_size)) {
      m_related.emplace_back(make_pair(x + 2, y - 1));
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
  map<coord, Vertex>graph;
public:
  Graph() = default;
  explicit Graph(int number) {
    for (int i = 1; i <= number; ++i) {
      for (int j = 1; j <= number; ++j) {
        graph[{j, i}] = Vertex({j, i}, number);
      }
    }
  }

  int get_size() const {
    return graph.size() - 1;
  }

  Vertex& get_vert(coord i) {
    return graph[i];
  }

  map<coord, Vertex>& get_graph() {
    return graph;
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

};

void BFS(Graph& graph, coord start) {
  queue<coord> q;
  for (auto it = graph.get_graph().rbegin(); it != graph.get_graph().rend(); ++it) {
    pair<coord, Vertex> cur_vert = *it;
    cur_vert.second.set_colour(white);
    cur_vert.second.add_parent({-1, -1});
    cur_vert.second.set_depth(-1);
  }
  graph.get_vert(start).set_depth(0);
  graph.get_vert(start).set_colour(gray);
  q.push(start);

  while(!q.empty()) {
    coord v = q.front();
    q.pop();
//        for (auto it = graph.get_vert(v).get_related().rbegin(); it != graph.get_vert(v).get_related().rend(); ++it){
//            coord neighbor = *it;
    for (coord neighbor:graph.get_vert(v).get_related()) {
      Vertex& u = graph.get_vert(neighbor);
      if (u.get_colour() == white) {
        u.set_colour(gray);
        u.set_depth(graph.get_vert(v).get_depth() + 1);
        u.add_parent(v);
        q.push(neighbor);
      }
    }
    graph.get_vert(v).set_colour(black);
  }
}

void get_path(Graph& graph, coord finish) {
  vector<coord> path;


  for (coord v = finish; coord(-1, -1) != v; v = graph.get_vert(v).get_parent()) {
    path.push_back(v);
  }
  reverse(path.begin(), path.end());

  int dep = graph.get_vert(finish).get_depth();
  cout << dep << endl;

  for (auto & it : path) {
    cout << it.x << ' ' << it.y << endl;
  }
}

int main() {
  int N;
  cin >> N;
  Graph g(N);
  coord from;
  coord to;
  cin >> from.x >> from.y >> to.x >> to.y;

  BFS(g, from);
  get_path(g, to);

}