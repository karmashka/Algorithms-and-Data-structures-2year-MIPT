//Витя хочет придумать новую игру с числами. В этой игре от игроков требуется преобразовывать четырехзначные числа не содержащие нулей при помощи следующего разрешенного набора действий:
//
//1. Можно увеличить первую цифру числа на 1, если она не равна 9.
//
//2. Можно уменьшить последнюю цифру на 1, если она не равна 1.
//
//3. Можно циклически сдвинуть все цифры на одну вправо.
//
//4. Можно циклически сдвинуть все цифры на одну влево.
//
//Например, применяя эти правила к числу 1234 можно получить числа 2234, 1233, 4123 и 2341 соответственно. Точные правила игры Витя пока не придумал, но пока его интересует вопрос, как получить из одного числа другое за минимальное количество операций.
//
//Input format
//Во входном файле содержится два различных четырехзначных числа, каждое из которых не содержит нулей.
//
//Output format
//Программа должна вывести последовательность четырехзначных чисел, не содержащих нулей. Последовательность должна начинаться первым из данных чисел и заканчиваться вторым из данных чисел, каждое последующее число в последовательности должно быть получено из предыдущего числа применением одного из правил. Количество чисел в последовательности должно быть минимально возможным.
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


class Vertex {
private:
  e_color m_colour = white;
  int m_board_number;
  int m_discovered_time;
  int m_closed_time;
  int m_parent = -1;
  int m_depth = -1;
  vector <int> m_related;

public:
  Vertex () = default;
  Vertex(const Vertex& second) = default;


  explicit Vertex (int x): m_board_number(x) {
    int thousands = x / 1000;
    int hundreds = (x - thousands * 1000) / 100;
    int tens = (x - thousands * 1000 - hundreds * 100) / 10;
    int ones = x % 10;
    if (!thousands || !hundreds || !tens || !ones) {
      return;
    }
    if (thousands != 9) {
      m_related.push_back(x + 1000);
    }
    if (ones != 1) {
      m_related.push_back(x - 1);
    }
    int left_cycle = ones * 1000 + thousands * 100 + hundreds * 10 + tens;
    int right_cycle = hundreds * 1000 + tens * 100 + ones * 10 + thousands;
    m_related.push_back(left_cycle);
    m_related.push_back(right_cycle);
  }

  ~Vertex() = default;

  void set_colour (e_color new_colour) {
    m_colour = new_colour;
  }

  e_color get_colour() const {
    return m_colour;
  }

  void set_number(int num) {
    m_board_number = num;
  }

  int get_number() const {
    return m_board_number;
  }

  void set_depth(int depth) {
    m_depth = depth;
  }

  int get_depth() const {
    return m_depth;
  }
  void set_closed_time(int time) {
    m_closed_time = time;
  }

  int get_closed_time() const {
    return m_closed_time;
  }

  int get_discovered_time() const {
    return m_discovered_time;
  }

  void set_discovered_time(int time) {
    m_discovered_time = time;
  }

  void add_related(const int v) {
    m_related.push_back(v);
  }

  void add_parent(const int parent) {
    m_parent = parent;
  }

  const vector <int>& get_related() const  {
    return m_related;
  }

  vector <int>& get_related()  {
    return m_related;
  }

  int get_parent() const {
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
  map<int, Vertex> graph;
public:
  Graph() = default;

  void add_vertex(int n) {
    graph.insert(make_pair(n, Vertex(n)));
  }

  Vertex& get_vert(int i) {
    if (!graph.count(i)) {
      add_vertex(i);
    }
    return graph[i];
  }

  map <int, Vertex>& get_graph() {
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

void BFS(Graph& graph, int start, int to) {
  graph.add_vertex(start);
  queue<int> q;

  graph.get_vert(start).set_depth(0);
  graph.get_vert(start).set_colour(gray);
  q.push(start);

  while(!q.empty()) {
    int v = q.front();
    q.pop();
    if (v == to) {
      break;
    }
    for (int neighbor:graph.get_vert(v).get_related()) {
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

void get_path(Graph& graph, int finish) {
  vector<int> path;

  for (int v = finish; v != -1; v = graph.get_vert(v).get_parent()) {
    path.push_back(v);
  }
  reverse(path.begin(), path.end());

  for (auto it = path.begin(); it != path.end(); ++it) {
    cout << *it << '\n';
  }
}


int main() {
  Graph g;
  int from, to;
  cin >> from >> to;

  BFS(g, from, to);
  get_path(g, to);

}

