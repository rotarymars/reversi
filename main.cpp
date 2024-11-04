#include <iostream>
#define private public
#include "board.hpp"
int main() {
  board b;
  b.print();
  b.printplacable('w');
}
