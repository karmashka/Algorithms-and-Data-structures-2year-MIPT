//Задан ориентированный граф, каждое ребро которого обладает целочисленной пропускной способностью. Найдите максимальный поток из вершины с номером 1 в вершину с номером n.
//
//В этой задаче необходимо реализовать алгоритм Форда-Фалкерсона.
//
//Input format
//Первая строка входного файла содержит n и m - количество вершин и количество ребер графа (2 ≤ n ≤ 100, 1 ≤ m ≤ 1000). Следующие m строк содержат по три числа: номера вершин, которые соединяет соответствующее ребро графа и его пропускную способность. Пропускные способности не превосходят 105.
//
//Output format
//В выходной файл выведите одно число - величину максимального потока из вершины с номером 1 в вершину с номером n.

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <string>
using namespace std;

int inf = INT32_MAX;
enum e_color {
  white,
  gray,
};


struct Vertex {
  e_color m_colour;
  int m_number;;
  int m_parent;
  int m_depth;
  set<int> m_related;

  Vertex () = default;
  Vertex(const Vertex& second) = default;

  explicit Vertex (int num, e_color new_colour = white): m_colour(new_colour), m_number(num), m_parent(-1) {}

  ~Vertex() = default;

  void add_related(const int v) {
    m_related.emplace(v);
  }

  bool operator== (const Vertex& v) const {
    return m_number == v.m_number;
  }

};

struct Graph {
  vector<Vertex> graph;
  vector<vector<int>> capacity;

  Graph() = default;
  explicit Graph(int number) {
    for (int i = 0; i <= number; ++i) {
      graph.emplace_back(i);
      capacity.emplace_back(vector<int>(number + 1, 0));
    }
  }

  int get_size() const {
    return graph.size() - 1;
  }

  void add_vertex(int from, int to) {
    graph[from].add_related(to);
    graph[to].add_related(from);
  }

  void read(int size) {
    int from, to;
    for (int i = 1; i <= size; ++i) {
      cin >> from >> to;
      add_vertex(from, to);
    }
  }

  int BFS(int start, int finish) {
    queue<pair<int, int>> q;
    for (Vertex& cur_vert : graph) {
      cur_vert.m_colour = white;
      cur_vert.m_parent = -1;
      cur_vert.m_depth = -1;
    }
    graph[start].m_depth = 0;
    graph[start].m_parent = -1;
    graph[start].m_colour = gray;
    q.push(make_pair(start, inf));

    while(!q.empty()) {
      int v = q.front().first;
      int cur_flow = q.front().second;
      q.pop();
      for (int neighbor:graph[v].m_related) {
        Vertex& u = graph[neighbor];
        if (u.m_parent == -1 && capacity[v][u.m_number]) {
          //u.m_colour = gray;
          u.m_depth = graph[v].m_depth + 1;
          u.m_parent = v;
          int new_flow = min(cur_flow, capacity[v][u.m_number]);
          if (u.m_number == finish) {
            return new_flow;
          }
          q.push(make_pair(neighbor, new_flow));
        }
      }
    }
    return 0;
  }

  int get_max_flow(int from, int to) {
    int flow = 0;
    int cur_flow = 0;
    cur_flow = BFS(from, to);

    while (cur_flow) {
      flow += cur_flow;
      int cur_v = to;
      while (cur_v != from) {
        int prev_v = graph[cur_v].m_parent;
        capacity[prev_v][cur_v] -= cur_flow;
        capacity[cur_v][prev_v] += cur_flow;
        cur_v = prev_v;
      }
      cur_flow = BFS(from, to);
    }
    return flow;
  }
};


int main() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int from, to, capacity;
    cin >> from >> to >> capacity;
    graph.add_vertex(from, to);
    graph.capacity[from][to] += capacity;
  }

  cout << graph.get_max_flow(1, n);
  return 0;
}
