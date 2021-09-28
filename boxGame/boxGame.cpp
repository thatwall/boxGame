// boxGame.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include "Box.h"

int main() {
  //FILE* pFile;
  //pFile = fopen("./input.txt", "r");
  //if (pFile == NULL) {
  //  printf("Error opening file unexist.ent: %s\n", strerror(errno));
  //  return -1;
  //}
  ifstream fin("./easy/49.txt");
  if (!fin.is_open()) {
    cerr << "failed" << endl;
    return -1;
  }
  boxState bs;
  fin >> bs.cur.x >> bs.cur.y;
  int tnum = 0;
  fin >> tnum;
  while (tnum--) {
    point tmp;
    fin >> tmp.x >> tmp.y;
    bs.targets.push_back(tmp);
  }
  string line;
  while (fin >> line) {
    bs.board.push_back(line);
  }
  auto result = bfs(bs);
  if (!(result.cur == point(-1, -1))) {
    for (int i = 0; i < result.ops.size(); i++) {
      if (result.ops[i] == point(0, 1)) {
        cout << "→" << endl;
      } else if (result.ops[i] == point(1, 0)) {
        cout << "↓" << endl;
      } else if (result.ops[i] == point(0, -1)) {
        cout << "←" << endl;
      } else if (result.ops[i] == point(-1, 0)) {
        cout << "↑" << endl;
      }
      bs.forward(result.ops[i]);
      cout << bs.toString() << endl;
    }
  }
  return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧:
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5.
//   转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
