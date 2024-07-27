#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
void PRINT_BOARD(vector<vector<char>> &a) {
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < a.size(); j++) {
      if (j == 0)
        cout << a[i][j];
      else
        cout << " " << a[i][j];
    }
    cout << "\n";
  }
  return;
}
void __INIT___BOARD(vector<vector<char>> &a) {
  a[3][3] = a[4][4] = 'W';
  a[3][4] = a[4][3] = 'B';
  return;
}
vector<pair<int, int>> __LISTCANPUT(vector<vector<char>> &a, int b) {
  vector<int> gh{-1, 0, 0, 1}, gw{0, -1, 1, 0};
  /*
  #0#
  1.2
  #3#
  */
  vector<pair<int, int>> ret;
  char userchar = (b == 1 ? 'B' : 'W');
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++) {
      if (a[i][j] != '#')
        continue;
      pair<int, int> maybecoordinate{i, j};
      vector<int> originh{-1, -1, 0, 1, 1, 1, 0, -1},
          originw{0, 1, 1, 1, 0, -1, -1, -1};
      for (int k = 0; k < 8; k++) {
        pair<int, int> nextcoordinate{maybecoordinate.first + originh[k],
                                      maybecoordinate.second + originw[k]};
        if (!(0 <= nextcoordinate.first && nextcoordinate.first < 8 &&
              0 <= nextcoordinate.second && nextcoordinate.second < 8))
          continue;
        if (a[nextcoordinate.first][nextcoordinate.second] == '#' ||
            a[nextcoordinate.first][nextcoordinate.second] == userchar)
          continue;
        bool ok = false;
        for (int l = 2; l < 8; l++) {
          pair<int, int> checkingcoordinate{
              maybecoordinate.first + originh[k] * l,
              maybecoordinate.second + originw[k] * l};
          if (!(0 <= checkingcoordinate.first && checkingcoordinate.first < 8 &&
                0 <= checkingcoordinate.second &&
                checkingcoordinate.second < 8))
            break;
          if (a[checkingcoordinate.first][checkingcoordinate.second] ==
              userchar) {
            ok = true;
            break;
          }
        }
        if (ok)
          ret.push_back(maybecoordinate);
      }
    }
  return ret;
}
void __EDIT_BOARD(vector<vector<char>> &a, int h, int w, char userchar) {
  pair<int, int> origincoordinate{h, w};
  vector<int> originh{-1, -1, 0, 1, 1, 1, 0, -1},
      originw{0, 1, 1, 1, 0, -1, -1, -1};
  for (int i = 0; i < 8; i++) {
    pair<int, int> nextcoordinate{origincoordinate.first + originh[i],
                                  origincoordinate.second + originw[i]};
    if (0 <= nextcoordinate.first && nextcoordinate.first < 8 &&
        0 <= nextcoordinate.second && nextcoordinate.second < 8) {
      if (userchar != a[nextcoordinate.first][nextcoordinate.second] &&
          a[nextcoordinate.first][nextcoordinate.second] != '#') {
        bool ok = false;
        for (int j = 2; j < 8; j++) {
          pair<int, int> tmpcoordinate{origincoordinate.first + originh[i] * j,
                                       origincoordinate.second +
                                           originw[i] * j};
          if (0 <= tmpcoordinate.first && tmpcoordinate.first < 8 &&
              0 <= tmpcoordinate.second && tmpcoordinate.second < 8) {
            if (userchar == a[tmpcoordinate.first][tmpcoordinate.second]) {
              ok = true;
              break;
            }
          } else
            break;
        }
        if (ok) {
          for (int j = 1; true; j++) {
            pair<int, int> tmpcoordinate{
                origincoordinate.first + originh[i] * j,
                origincoordinate.second + originw[i] * j};
            if (a[tmpcoordinate.first][tmpcoordinate.second] == userchar)
              break;
            a[tmpcoordinate.first][tmpcoordinate.second] = userchar;
          }
        }
      }
    }
  }
  a[origincoordinate.first][origincoordinate.second] = userchar;
}
int main() {
  int player = 0, turn = 1;
  cout << "Select first or second(B/W)\n";
  do {
    char tmp;
    cin >> tmp;
    if (tmp == 'B')
      player = 1;
    else if (tmp == 'W')
      player = -1;
    else
      abort();
  } while (false);
  vector<vector<char>> board(
      8, vector<char>(8, '#')); //#=free, W=WHITE=-1, B=BLACK=1
  __INIT___BOARD(board);
  PRINT_BOARD(board);
  int times_left = 60;
  while (times_left) {
    auto place_to_put = __LISTCANPUT(board, turn);
    if (place_to_put.empty()) {
      cout << "Skipping turn " << (turn == 1 ? 'B' : 'W')
           << " due to no place to put\n";
    } else {
      auto cpboard = board;
      for (auto tmp : place_to_put)
        cpboard[tmp.first][tmp.second] = '_';
      cout << "Places which are available to put\n";
      PRINT_BOARD(cpboard);
      if (player == turn) {
      START_OF_ASKING_PLAYER:
        cout << "Enter the coordinate to put(0-indexed).\n";
        int a, b;
        cin >> a >> b;
        sort(place_to_put.begin(), place_to_put.end());
        auto it = lower_bound(place_to_put.begin(), place_to_put.end(),
                              make_pair(a, b));
        if (it != place_to_put.end())
          if (*it == make_pair(a, b))
            __EDIT_BOARD(board, a, b, (turn == 1 ? 'B' : 'W'));
          else {
            cout << "Invalid input. Cannot put in such place\n";
            goto START_OF_ASKING_PLAYER;
          }
        PRINT_BOARD(board);
      } else {
      START_OF_ASKING_PC:
        cout << "CP putting\n";
        cout << "Enter number for now\n";
        int a, b;
        cin >> a >> b;
        sort(place_to_put.begin(), place_to_put.end());
        auto it = lower_bound(place_to_put.begin(), place_to_put.end(),
                              make_pair(a, b));
        if (it != place_to_put.end())
          if (*it == make_pair(a, b))
            __EDIT_BOARD(board, a, b, (turn == 1 ? 'B' : 'W'));
          else {
            cout << "INVALID INPUT\n";
            goto START_OF_ASKING_PC;
          }
      }
    }
    turn *= -1;
    times_left--;
  }
  return 0;
}
