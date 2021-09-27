#pragma once
#include <string>
#include <vector>
using namespace std;

string test1() { return "Hello"; }

struct point {
  int x, y;
  point(int _x, int _y) : x(_x), y(_y) {}
  point operator+(const point& pt) { return point(x + pt.x, y + pt.y); }
  bool operator==(const point& pt) { return x == pt.x && y == pt.y; }
};
const point dirs[] = {point(0, 1), point(1, 0), point(0, -1), point(-1, 0)};

// 'b'Ïä×Ó£¬'w'Ç½£¬'.'¿Õ°×
enum atom { box = 'B', wall = 'W', blank = '.' };
enum direction { east, south, west, north };

struct boxState {
  vector<vector<char>> board;
  point cur;
  vector<point> targets;

  char& getAtom(point pt) { return board[pt.x][pt.y]; }
  bool forward(int d) {
    point dir = dirs[d];
    point dest = cur + dir;
    if (getAtom(dest) == atom::box) {
      if (getAtom(dest + dir) == atom::blank) {
        getAtom(dest + dir) = atom::box;
        getAtom(dest) = atom::blank;
        cur = dest;
      }
    } else if (getAtom(dest) == atom::blank) {
      cur = dest;
    }
    return cur == dest;
  }
  void backward(int d) {

  }
  bool isFin() {
    for (const point& pt : targets) {
      if (getAtom(pt) != atom::box) {
        return false;
      }
    }
    return true;
  }
};
