#pragma once
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

string test1() {
  return "Hello";
}

struct point {
  int x, y;
  point() : x(0), y(0) {}
  point(int _x, int _y) : x(_x), y(_y) {}
  point operator+(const point& pt) { return point(x + pt.x, y + pt.y); }
  point operator-(const point& pt) { return point(x - pt.x, y - pt.y); }
  bool operator==(const point& pt) { return x == pt.x && y == pt.y; }
};
const point dirs[] = {point(0, 1), point(1, 0), point(0, -1), point(-1, 0)};

// 'b'Ïä×Ó£¬'w'Ç½£¬'.'¿Õ°×
enum atom { box = 'b', wall = 'w', blank = '.' };
enum direction { east, south, west, north };

struct boxState {
  vector<string> board;
  point cur;
  static vector<point> targets;
  vector<point> ops;
  boxState() : cur(-1, -1) {}
  bool operator==(boxState& bs) { return index() == bs.index(); }
  char& getAtom(point pt) { return board[pt.x][pt.y]; }
  void forward(const point& dir) {
    // point dir = dirs[d];
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
    if (cur == dest) {
      ops.push_back(dir);
    }
    //return cur == dest;
  }
  void backward() {
    auto lastOp = ops.back();
    ops.pop_back();
    auto dest = cur + lastOp;
    if (getAtom(dest) == atom::box) {
      getAtom(cur) = atom::box;
      getAtom(dest) = atom::blank;
    }
    cur = cur - lastOp;
  }

  bool isFin() {
    for (const point& pt : targets) {
      if (getAtom(pt) != atom::box) {
        return false;
      }
    }
    return true;
  }
  string toString() {
    getAtom(cur) = 'P';
    string res;
    for (int i = 0; i < board.size(); i++) {
      res += board[i] + '\n';
    }
    getAtom(cur) = '.';
    return res;
  }
  string index() {
    return toString();
    //return toString() + to_string(cur.x) + to_string(cur.y);
  }
};

vector<point> boxState::targets = vector<point>();

boxState bfs(boxState st) {
  static queue<boxState> q;
  static set<string> s;
  q.push(st);
  s.insert(st.index());
  while (!q.empty()) {
    auto top = q.front();
    q.pop();
    if (top.isFin()) {
      return top;
    }
    for (int i = 0; i < 4; i++) {
      auto temp = top;
      temp.forward(dirs[i]);
      if (!s.count(temp.index())) {
        q.push(temp);
        s.insert(temp.index());
      }

    }
  }
  return boxState();
}