//Дан ориентированный невзвешенный граф. Необходимо определить есть ли в нём циклы, и если есть, то вывести любой из них.
//
//Input format
//В первой строке входного файла находятся два натуральных числа N и M (1 ≤ N ≤ 100000, M ≤ 100000) - количество вершин и рёбер в графе соответственно. Далее в M строках перечислены рёбра графа. Каждое ребро задаётся парой чисел - номерами начальной и конечной вершин соответственно.
//
//Output format
//Если в графе нет цикла, то вывести "NO", иначе - "YES" и затем перечислить все вершины в порядке обхода цикла.
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Vertex {
private:
  string m_colour;
  int m_number;
  int m_discovered_time;
  int m_closed_time;
  int m_next_vertex;
  int m_parent;
  vector <int> m_related;

public:
  Vertex () = default;
  Vertex(const Vertex& second) = default;

  explicit Vertex (int num, string new_colour = "colorless") {
    m_colour = new_colour;
    m_number = num;
  }

  ~Vertex() = default;

  void set_colour (string new_colour) {
    m_colour = new_colour;
  }

  string get_colour() const {
    return m_colour;
  }

  void set_number(int num) {
    m_number = num;
  }

  int get_number() const {
    return m_number;
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

  int get_parent()  {
    return m_parent;
  }

  vector <int>& get_related()  {
    return m_related;
  }

  bool operator== (const Vertex& v) const {
    return m_number == v.m_number;
  }

  bool operator!= (const Vertex& v) const {
    return !(*this == v);
  }

  Vertex& operator = (const Vertex& v) {
    m_number = v.m_number;
    m_colour = v.m_colour;
    m_related = v.m_related;
    return *this;
  }

};

class Graph {
private:
  int m_time = 0;
  vector<Vertex> graph;
public:
  Graph() = default;
  explicit Graph(int number) {
    for (int i = 0; i < number; ++i) {
      graph.emplace_back(i + 1);
    }
  }

  void add_vertex(int from, int to) {
    graph[from - 1].add_related(to);
  }

  Vertex& get_vert(int i) {
    return graph[i];
  }

  vector <Vertex>& get_graph() {
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

pair<int, int> DFS_visit(Graph& gr, Vertex& v) {
  v.set_colour("gray");
  gr.time_update();
  v.set_discovered_time(gr.get_time());

  for (int elem : v.get_related()) {
    Vertex& next_vertex = gr.get_vert(elem - 1);
    if (next_vertex.get_colour() == "gray") {
      return make_pair(v.get_number(), next_vertex.get_number());
    } else if (next_vertex.get_colour() == "white") {
      next_vertex.add_parent(v.get_number());
      pair<int, int> result = DFS_visit (gr, next_vertex);
      if (result != make_pair(0,0)) {
        return result;
      }
    }
  }

  gr.time_update();
  v.set_closed_time(gr.get_time());
  v.set_colour("black");
  return make_pair(0, 0);
}

pair<int, int> DFS (Graph& gr) {
  for (Vertex& cur_vert : gr.get_graph()) {
    cur_vert.set_colour("white");
  }

  gr.set_time(0);

  for (Vertex& cur_vert : gr.get_graph()) {
    if (cur_vert.get_colour() == "white") {
      pair<int, int> result = DFS_visit(gr, cur_vert);
      if (result != make_pair(0,0)) {
        return result;
      }
    }
  }
  return make_pair(0, 0);
}

void print_cycle(Graph& graph, pair<int, int>& last_and_first_vertex_in_cycle) {
  vector<int> parents;
  if (last_and_first_vertex_in_cycle.first == last_and_first_vertex_in_cycle.second) {
    cout << last_and_first_vertex_in_cycle.first;
    cout << endl;
    return;
  }

  int parent = graph.get_vert(last_and_first_vertex_in_cycle.first - 1).get_parent();
  while(parent != last_and_first_vertex_in_cycle.second) {
    parents.push_back(parent);
    int next_vert = parent;
    parent = graph.get_vert(next_vert - 1).get_parent();
  }

  parents.push_back(last_and_first_vertex_in_cycle.second);
  for (auto it = parents.rbegin(); it != parents.rend(); ++it) {
    cout << *it << ' ';
  }
  cout << last_and_first_vertex_in_cycle.first;
  cout << endl;
}

int main() {
  int M;
  int N;
  cin >> M >> N;

  Graph graph(M);

  int from, to;
  for (int i = 0; i < N; ++i) {
    cin >> from >> to;
    graph.add_vertex(from, to);
  }

  pair<int, int> last_and_first_in_cycle = DFS(graph);

  if (last_and_first_in_cycle != make_pair(0, 0)) {
    cout << "YES" << endl;
    print_cycle(graph, last_and_first_in_cycle);
  } else {
    cout << "NO" << endl;
  }
}
