#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include "board.h"

class Pawn : public Piece
{
private:
    const Pos s[3]={{-1,0},{1,0},{0,1}};
public:
    Pawn(int x,int y,bool side):Piece(x,y,side ? PieceType::RED_BING: PieceType::BLACK_ZU){};
    virtual bool isBasicMove(int x,int y)const{
        if(Board::getBoard()->find(x,y).empty() || !isSidePiece(*(Board::getBoard()->find(x,y).begin()))){
            bool isInside=(y<=5);
            if (isInside)
                return y==(this->y)+1;
            else{
                for(auto i:s){
                    if(x==(this->x)+i.first&&y==(this->y)+i.second)
                        return true;
                }
            }
        }
        return false;
    }
    virtual const std::list<Pos> getPossibleMoves() const{
        std::list<Pos> result;
        //遍历兵的三个方向
        for(auto i:s){
            if(isValidMove(this->x+i.first,this->y+i.second)){
                result.push_back(std::make_pair(this->x+i.first,this->y+i.second));
            }
        }
        return result;
    }
    virtual bool isThreat(const std::list<std::pair<Pos, Piece::PieceType>>& pieces)const{
        //首先找王坐标
        int kx,ky;
        for(auto &i:pieces)
        {
            if(i.second==(side()?Piece::PieceType::BLACK_JIANG:Piece::PieceType::RED_SHUAI))
            {
                kx = i.first.first;
                ky = i.first.second;
                break;
            }
        }
        bool isInside;
        if(side()){
            isInside=(this->y)<=5;
        }else{
            isInside=(this->y)>5;
        }
        if (isInside)
            return false;
        else{
            for(auto i:s){
                if(kx==(this->x)+i.first&&ky==(this->y)+i.second)
                    return true;
            }
        }
        return false;
    }
};

#endif // PAWN_H
