#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <sstream>
using namespace std;


class Game{
private:
    int counter = 0;
    int score = 0;
    vector<int> sequence;

public:

    void start(){
        if(sequence.size() > 0){
            sequence.clear();
            score = 0;
            counter = 0;
        }
        srand (time(NULL));
        sequence.push_back(rand()%4 + 1 );
    }

    bool endOfLvl(){
        bool endoflvl;
        if(counter == sequence.size())
            endoflvl = true;
        else
            endoflvl = false;
        return endoflvl;
    }


    int GetCurrentNum(){
        return sequence[counter];
    }

    string GetScore(){
        string str;
        ostringstream temp;
        temp<<counter;
        str=temp.str();
        return str;
    };

    int GetScoreInt(){
    return score;
    }

    bool check(int button){
        bool check = false;
        if(button == sequence[counter]){
            score++;
            counter++;
            check= true;
        }
        return check;
    }
    void AddALevel(){
        sequence.push_back(rand()%4 + 1 );
    };

    int getSizeSeq(){
    return this->sequence.size();
    }

    int GetColorPos(int index){
    return this->sequence[index];
    }
    void newLevel(){
        this->counter = 0;
    };







};

#endif
