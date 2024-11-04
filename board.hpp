#include <iostream>
class board
{
  private:
    long long white,black;

    constexpr int getshiftfromco(int h, int w){
      return h*8+w;
    }

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
