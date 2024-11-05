#include <iostream>
#include <vector>
class board {
private:
  long long white, black;

  int whitescore,blackscore;
  constexpr int getshiftfromco(int h, int w) { return 63 - h * 8 + w; }

  int weight[64] = {30, -12, 0,   -1,  -1, 0,   -12, 30, -12, -15, -3,  -3, -3,
                    -3, -15, -12, 0,   -3, 0,   -1,  -1, 0,   -3,  0,   -1, -3,
                    -1, -1,  -1,  -1,  -3, -1,  -1,  -3, -1,  -1,  -1,  -1, -3,
                    -1, 0,   -3,  0,   -1, -1,  0,   -3, 0,   -12, -15, -3, -3,
                    -3, -3,  -15, -12, 30, -12, 0,   -1, -1,  0,   -12, 30};
  int gh[4] = {-1, 0, 1, 0};
  int gw[4] = {0, 1, 0, -1};
  void place(int h, int w, char turn) {
    if (turn == 'w')
      white |= (1ll << getshiftfromco(h, w));
    else
      black |= (1ll << getshiftfromco(h, w));
    return;
  }

public:
  board() {
    white = black = 0;
    white |= (1ll << getshiftfromco(3, 3));
    white |= (1ll << getshiftfromco(4, 4));
    black |= (1ll << getshiftfromco(3, 4));
    black |= (1ll << getshiftfromco(4, 3));
    whitescore=blackscore=-2;
    // std::cout<<white<<' '<<black<<std::endl;
  }
  void print() {
    std::cout << "  1 2 3 4 5 6 7 8\n";
    for (int i = 0; i < 8; ++i) {
      std::cout << i + 1 << ' ';
      for (int j = 0; j < 8; ++j) {
        if (black & (1ll << getshiftfromco(i, j)))
          std::cout << 'X';
        else if (white & (1ll << getshiftfromco(i, j)))
          std::cout << 'O';
        else
          std::cout << '.';
        if (j != 7) [[likely]]
          std::cout << ' ';
      }
      std::cout << '\n';
    }
  }

  void printplacable(char turn) {
    auto placable = this->getplacable(turn);
    long long placable_mask = 0ll;
    for (auto &i : placable)
      placable_mask |= (1ll << i);
    std::cout << "  1 2 3 4 5 6 7 8\n";
    for (int i = 0; i < 8; ++i) {
      std::cout << i + 1 << ' ';
      for (int j = 0; j < 8; ++j) {
        if (placable_mask & (1ll << getshiftfromco(i, j)))
          std::cout << '_';
        else if (black & (1ll << getshiftfromco(i, j)))
          std::cout << 'X';
        else if (white & (1ll << getshiftfromco(i, j)))
          std::cout << 'O';
        else
          std::cout << '.';
        if (j != 7) [[likely]]
          std::cout << ' ';
      }
      std::cout << '\n';
    }
    return;
  }
  std::vector<int> getplacable(char turn) {
    std::vector<int> ret;
    if (turn == 'w') {
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          if (black & (1ll << getshiftfromco(i, j)))
            continue;
          if (white & (1ll << getshiftfromco(i, j)))
            continue;
          for (int k = 0; k < 4; k++) {
            int nh = i + gh[k];
            int nw = j + gw[k];
            if (nh < 0 || nh >= 8 || nw < 0 || nw >= 8)
              continue;
            if (black & (1ll << getshiftfromco(nh, nw))) {
              while (nh >= 0 && nh < 8 && nw >= 0 && nw < 8) {
                nh += gh[k];
                nw += gw[k];
                if (nh < 0 || nh >= 8 || nw < 0 || nw >= 8)
                  break;
                if(!(black&(1ll<<getshiftfromco(nh,nw)))&&!(white&(1ll<<getshiftfromco(nh,nw))))
                  break;
                if (white & (1ll << getshiftfromco(nh, nw))) {
                  ret.push_back(getshiftfromco(i, j));
                  break;
                }
              }
            }
          }
        }
      }
    } else {
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          if (black & (1ll << getshiftfromco(i, j)))
            continue;
          if (white & (1ll << getshiftfromco(i, j)))
            continue;
          for (int k = 0; k < 4; k++) {
            int nh = i + gh[k];
            int nw = j + gw[k];
            if (nh < 0 || nh >= 8 || nw < 0 || nw >= 8)
              continue;
            if (white & (1ll << getshiftfromco(nh, nw))) {
              while (nh >= 0 && nh < 8 && nw >= 0 && nw < 8) {
                nh += gh[k];
                nw += gw[k];
                if (nh < 0 || nh >= 8 || nw < 0 || nw >= 8)
                  break;
                if(!(black&(1ll<<getshiftfromco(nh,nw)))&&!(white&(1ll<<getshiftfromco(nh,nw))))
                  break;
                if (black & (1ll << getshiftfromco(nh, nw))) {
                  ret.push_back(getshiftfromco(i, j));
                  break;
                }
              }
            }
          }
        }
      }
    }
    return ret;
  }

};
