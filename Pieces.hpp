
#ifndef Pieces_h
#define Pieces_h

#include <iostream>
#include <map>

using namespace std;

class Piece {
    
private:
    string type;
    string colour;
    bool moved;
    int value;
    
public:
    Piece(){
        this->type =  "empty";
        this->colour = "none";
        moved = false;
        value = 0;
    }
    
    Piece(string type, string colour){
        this->type =  type;
        this->colour = colour;
        moved = false;
        value = this->GetValue();
    }
    
    int GetValue(){
        if (this->type != "empty") {
            map<string, int> PieceValues = {{"King", 100}, {"Queen", 9}, {"Rook", 5}, {"Bishop", 3}, {"Knight", 3}, {"Pawn", 1}};
            return PieceValues[type];
        }
        else{
            return 0;
        }
    }
    
    string Type(){
        return this->type;
    }
    
    string Colour(){
        return this->colour;
    }
    
    void SetMoved(bool boolean){
        this->moved = boolean;
    }
    
    bool HasMoved(){
        return this->moved;
    }
    
};

#endif
