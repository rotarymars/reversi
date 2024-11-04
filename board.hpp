#include <iostream>
class board
{
  private:
    long long white,black;

    constexpr int getshiftfromco(int h, int w){
      return h*8+w;
    }

    int weight[64] = 
    {
    30, -12, 0, -1, -1, 0, -12, 30,
    -12, -15, -3, -3, -3, -3, -15, -12,
    0, -3, 0, -1, -1, 0, -3, 0,
    -1, -3, -1, -1, -1, -1, -3, -1,
    -1, -3, -1, -1, -1, -1, -3, -1,
    0, -3, 0, -1, -1, 0, -3, 0,
    -12, -15, -3, -3, -3, -3, -15, -12,
    30, -12, 0, -1, -1, 0, -12, 30
    };
  public:
    board() {
      white=black=0;
      white|=(1ll<<getshiftfromco(3,3));
      white|=(1ll<<getshiftfromco(4,4));
      black|=(1ll<<getshiftfromco(3,4));
      black|=(1ll<<getshiftfromco(4,3));
      // std::cout<<white<<' '<<black<<std::endl;
    }
    void print(){
      for(int i=0;i<8;++i){
        for(int j=0;j<8;++j){
          if(black&(1ll<<getshiftfromco(i,j)))
            std::cout<<'X';
          else if(white&(1ll<<getshiftfromco(i,j)))
            std::cout<<'O';
          else std::cout<<'.';
          if(j!=7)[[likely]]std::cout<<' ';
        }
        std::cout<<'\n';
      }
    }
};
