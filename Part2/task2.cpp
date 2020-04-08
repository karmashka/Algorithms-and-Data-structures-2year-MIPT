//Вася любит наблюдать за звездами. Но следить за всем небом сразу ему тяжело. Поэтому он наблюдает только за частью пространства, ограниченной кубом размером n на n на n. Этот куб поделён на маленькие кубики размером 1x1x1. Во время его наблюдений могут происходить следующие события:
//
//• в каком-то кубике появляются или исчезают несколько звезд;
//• к нему может заглянуть его друг Петя и поинтересоваться, сколько видно звезд в части пространства, состоящей из нескольких кубиков.
//
//Input format
//Первая строка входного файла содержит натуральное число n (n ≤ 128). Координаты кубиков - целые число от 0 до n-1. Далее следуют записи о происходивших событиях по одной в строке.
//
//В начале строки записано число m. Если m равно:
//
//• 1, то за ним следуют 4 числа: x, y, z, k. (0 ≤ x, y, z < N, -20000 ≤ k ≤ 20000) - координаты кубика и величина, на которую в нем изменилось количество видимых звезд;
//• 2, то за ним следуют 6 чисел: x1, y1, z1, x2, y2, z2 (0 ≤ xi, yi, zi < N, x1 ≤ x2, y1 ≤ y2, z1 ≤ z2 которые означают, что Петя попросил подсчитать количество звезд в кубиках (x', y', z') из области: x1 ≤ x' ≤ x2, y1 ≤ y' ≤ y2, z1 ≤ z' ≤ z2.
//• 3, то это означает, что Васе надоело наблюдать за звездами и отвечать на вопросы Пети. Эта запись встречается во входном файле только один раз и будет последней записью. Количество записей во входном файле не превосходит 100500.
//
//Output format
//Для каждого Петиного вопроса выведите на отдельной строке одно число - искомое количество звезд.

#include <vector>
#include <iostream>
using namespace std;

struct Fenvic {
  vector <vector<vector<int>>> tree;
  int size;

  Fenvic() = default;
  Fenvic (int n): size(n){
    for (int i = 0; i < n; ++i) {
      tree.emplace_back(vector<vector<int>> (n, vector<int> (n, 0)));
    }
  }

  __uint64_t sum(int x1, int y1, int z1) {
    __uint64_t result = 0;
    for (int i = x1; i >= 0; i = (i & (i + 1)) - 1) {
      for (int j = y1; j >= 0; j = (j & (j + 1)) - 1) {
        for (int k = z1; k >= 0; k = (k & (k + 1)) - 1) {
          result += tree[i][j][k];
        }
      }
    }
    return result;
  }

  __uint64_t final_summ(int x1, int y1, int z1, int x2, int y2, int z2) {
    __int64_t result = 0;
    __int64_t a = sum (x2, y2, z2);
    __int64_t b = sum (x1 - 1, y1 - 1, z1 - 1);
    __int64_t c = sum (x2, y2, z1 - 1) + sum (x2, y1 - 1, z2) + sum (x1 - 1, y2, z2);
    __int64_t d = sum (x1 - 1, y1 - 1, z2) + sum (x1 - 1, y2, z1 - 1) + sum (x2, y1 - 1, z1 - 1);
    result = a - b - c + d;
    return result;

  }

  void update(int x, int y, int z, int d) {
    for (int i = x; i < size; i = (i | (i + 1))) {
      for (int j = y; j < size; j = (j | (j + 1))) {
        for (int k = z; k < size; k = (k | (k + 1))) {
          tree[i][j][k] += d;
        }
      }
    }
  }

  void build( vector <vector<vector<int>>>& arr) {
    for (int i = 0; i < arr.size(); ++i) {
      for (int j = 0; j < arr[i].size(); ++j) {
        for (int k = 0; k < arr[i][j].size(); ++k) {
          update(i, j, k, arr[i][j][k]);
        }
      }
    }
  }
};

int main() {
  int n;
  cin >> n;
  Fenvic fenvic_tree(n);

  while (true) {
    int command;
    cin >> command;
    if (command == 1) {
      int x, y, z, k;
      cin >> x >> y >> z >> k;
      fenvic_tree.update(x, y, z, k);
    } else if (command == 2) {
      int x1, y1, z1, x2, y2, z2;
      cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
      cout << fenvic_tree.final_summ(x1, y1, z1, x2, y2, z2) << '\n';
    } else if (command == 3) {
      break;
    }
  }

  return 0;
}

