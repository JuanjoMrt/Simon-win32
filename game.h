#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
using namespace std;


class Game{
private:
    int counter = 0;
    vector<int> sequence;

public:


    void talk(){
    cout << "counter: " << counter << endl;
    }

    void WhoTalk(int i){
    cout << "\t I'm number: " << i << endl;
    }

    bool PushColor(int color){
        if( sequence[counter] != color){
            counter = 0;
            sequence.clear();
        }
        else{
            counter++;
        }
    }









};

#endif
