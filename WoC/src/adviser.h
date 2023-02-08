#ifndef ADVISER_H
#define ADVISER_H

#include "piece.h"
#include "board.h"

class Adviser : public Piece
{
private:
    const Pos s[4]={{1,1},{1,-1},{-1,1},{-1,-1}};
public:
    Adviser(int x,int y,bool side):Piece(x,y,side ? PieceType::RED_SHI: PieceType::BLACK_SHI){};
    virtual bool isBasicMove(int x,int y)const{
        if(Board::getBoard()->find(x,y).empty() || !isSidePiece(*(Board::getBoard()->find(x,y).begin()))){
            if(isInNinePalaces(x,y)){
                for(int i=0;i<4;i++)
                {
                    if(this->x+s[i].first==x&&this->y+s[i].second==y)
                        return true;
                }
            }
        }
        return false;
    }
    virtual const std::list<Pos> getPossibleMoves() const{
        std::list<Pos> result;
        for(int i=4;i<=6;i++)
        {
            for(int j=(side()?1:8);j<=(side()?3:10);i++)
            {
                if(isValidMove(i,j))
                    result.push_back(std::make_pair(i,j));
            }
        }
        return result;
    }
    virtual bool isThreat(const std::list<std::pair<Pos, Piece::PieceType>>& pieces)const{
        //仕不出宫没有威胁
        return false;
    }
};

#endif // ADVISER_H
