#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>

using namespace std;

//function that contains all the data and functions realted to the game itself
class SnakeNLadder{
    public:
    static const int winpoint=100;
    map<int, int> snake;
    map<int, int> ladder;

    //initialize the snakes and ladder start and finish position
    SnakeNLadder(){
      snake.insert(pair<int, int>(99, 54));
      snake.insert(pair<int, int>(70, 55));
      snake.insert(pair<int, int>(52, 42));
      snake.insert(pair<int, int>(25, 2));
      snake.insert(pair<int, int>(95, 72));

      ladder.insert(pair<int, int>(6, 25));
      ladder.insert(pair<int, int>(11, 40));
      ladder.insert(pair<int, int>(60, 85));
      ladder.insert(pair<int, int>(46, 90));
      ladder.insert(pair<int, int>(19, 69));
    }
    
    //funciton that returns a random 6 face dice value
    int rolldice(){
      int result = 1 + (rand() % 6);
      return result;
    }

    //this function is intended to calculate the player's value on the board
    int playervalue (int player, int dicevalue){
      player=player+dicevalue;
      if (player>winpoint){
        player=player - dicevalue;
      }
      map<int,int>::iterator it;
      it = snake.find(player);
      if (it != snake.end()){
        std::cout<<"swallowed by snake\n";
        player= snake.find(player)->second;
      }
      it=ladder.find(player);
      if (it != ladder.end()){
        std::cout<<"climb up the ladder\n";
        player= ladder.find(player)->second;
      }
      return player;
    }

    //function that checks if a player won
    bool iswin(int player){
      return player==winpoint;
    }

    //main function of the class that contains the game mechanics, data, and make the game run
    void startgame(){
      int nplayer=0;
      std::cout<<"choose number of players\n";
      cin >> nplayer;

      //make sure that the number of player is correct
      while(std::cin.fail() || nplayer<=0) {
        std::cout << "You need to insert a number of player that's an int and that's higher than 0\n";
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cout<<"choose number of players\n";
        std::cin >> nplayer;
      }

      //initialize player position (value in the array of player)
      int players[nplayer];
      for (int i=0; i< nplayer; i++){
        players[i]=0;
      }

      string str;
      int diceValue =0, counter=0;

      //main mechanics of the game
      do
      {   std::cout<<"PLAYER " <<counter+1<< "'S TURN\n";
          std::cout<<"Press r to roll Dice\n";
          cin >> str;
          while (str!="r"){
            std::cout<<"You pressed the wrong letter\n";
            std::cout<<"Press r to roll Dice\n";
            cin >> str;
          }
          diceValue = rolldice();
          std::cout<<"Dice value :: " << diceValue <<endl;
          players[counter] = playervalue(players[counter],diceValue);
          for (int i=1; i<= nplayer; i++){
            std::cout<<"Player " << i<<" :: " << players[i-1] <<endl;
          }
          std::cout<<"------------------\n";
          if(iswin(players[counter]))
            {
                std::cout<<"Player "<<counter+1<<" wins\n";
                return;
            }
          if (counter==nplayer){
            counter=0;
          }
          else {counter++;}
      }while(str=="r");
    }
};

int main() {
  //initialize and start game
  SnakeNLadder game;
  game.startgame();
}