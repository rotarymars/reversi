#include <iostream>
#define private public
#include "board.hpp"
int main() {
  board b;
  b.print();
  b.printplacable('w');
  std::cout<<std::boolalpha<<b.isplaced(3,3);
}
