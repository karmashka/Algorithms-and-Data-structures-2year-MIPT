//Дан ориентированный граф, рёбрам которого приписаны некоторые неотрицательные веса (длины). Найти длину кратчайшего пути из вершины s в вершину t.
//
//Input format
//В первой строке заданы три числа: число вершин в графе N ≤ 50, номера вершин s и t. Далее идёт матрица смежности графа, то есть N строк, в каждой из которых записано N чисел. j-ое число в i-ой строке матрицы смежности задает длину ребра, ведущего из i-й вершину в j-ую. Длины могут принимать любые значения от 0 до 1000000, число -1 означает отсутствие соответствующего ребра. Гарантируется, что на главной диагонали матрицы стоят нули.
//
//Output format
//Выведите одно число – минимальную длину пути. Если пути не существует, выведите -1.
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const long long inf = INT64_MAX;

struct Graph {
  vector<vector<long long>> graph;
  int size;

  Graph(int size) : graph(size, vector<long long>(size, 0)), size(size) {

  }
};

void Floid (Graph gr, vector<vector<long long>>& answer) {
  for (int i = 0; i < gr.size; ++i) {
    for (int j = 0; j < gr.size; ++j) {
      if (gr.graph[i][j] == -1) {
        answer[i][j] = inf;
      } else {
        answer[i][j] = gr.graph[i][j];
      }
    }
  }

  for (int i = 0; i < gr.size; ++i) {
    answer[i][i] = 0;
  }

  for (int k = 0; k < gr.size; ++k) {
    for (int i = 0; i < gr.size; ++i) {
      for (int j = 0; j < gr.size; ++j) {
        if (answer[i][k] == inf || answer[k][j] == inf) {
          continue;
        }
        if (answer[i][j] >= answer[i][k] + answer[k][j]) {
          answer[i][j] = answer[i][k] + answer[k][j];
        }
      }
    }
  }
}

int main() {
  int N, s, f;
  cin >> N >> s >> f;
  Graph graph(N);
  vector<vector<long long>> answer(N, vector<long long>(N, 0));

  for (int i = 0; i < graph.size; ++i) {
    for (int j = 0; j < graph.size; ++j) {
      cin >> graph.graph[i][j];
    }
  }

  Floid(graph, answer);

  if (answer[s - 1][f - 1] == inf) {
    cout << -1;
  } else {
    cout << answer[s - 1][f - 1];
  }
  return 0;
}
