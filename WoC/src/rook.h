#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include "board.h"

class Rook : public Piece
{
private:

public:
    Rook(int x,int y,bool side):Piece(x,y,side ? PieceType::RED_JU: PieceType::BLACK_JU){};
    virtual bool isBasicMove(int x,int y)const{
        if(!Board::getBoard()->find(x,y,side()).empty())return false;
        if(Board::getBoard()->find(x,y).empty() || !isSidePiece(*(Board::getBoard()->find(x,y).begin())))//要去的位置是否为空或者是敌方的一个棋子
        {
            if(x==this->x)
            {
                if(y>this->y)
                {
                    for(int i=1;i<y-this->y;i++)
                    {
                        //路径上不是空的
                        if(!Board::getBoard()->find(x,(this->y)+i).empty())
                            return false;
                    }
                }else{
                    for(int i=1;i<(this->y)-y;i++)
                    {
                        if(!Board::getBoard()->find(x,(this->y)-i).empty())
                            return false;
                    }
                }
                return true;
            }else if(y==this->y)
            {
                if(x>this->x)
                {
                    for(int i=1;i<x-(this->x);i++)
                    {
                        if(!Board::getBoard()->find((this->x)+i,y).empty())
                            return false;
                    }
                }else{
                    for(int i=1;i<(this->x)-x;i++)
                    {
                        if(!Board::getBoard()->find((this->x)-i,y).empty())
                            return false;
                    }
                }
                return true;
            }
            return false;
        }
    }
    virtual const std::list<Pos> getPossibleMoves() const{
        std::list<Pos> result;
        //遍历車所在的十字区域
        for(int j=1;j<=9;j++){
            if(isValidMove(j,y)){
                result.push_back(std::make_pair(j,y));
            }
        }
        for(int j=1;j<=10;j++){
            if(isValidMove(x,j)){
                result.push_back(std::make_pair(x,j));
            }
        }
        return result;
    }
    virtual bool isThreat(const std::list<std::pair<Pos, Piece::PieceType>>& pieces)const{
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
        auto PosExistPiece = [=](int a,int b)->bool{
            for(auto [pos,type]:pieces)
            {
                if(pos.first==a&&pos.second==b)
                    return true;
            }
            return false;
        };
        if(kx==(this->x)){
            if(ky>this->y){
                for(int i=((this->y)+1);i<=ky-1;i++){
                    if(PosExistPiece(kx,i)) return false;
                }
            }else if(ky<this->y){
                for(int i=ky+1;i<=((this->y)-1);i++){
                    if(PosExistPiece(kx,i)) return false;
                }
            }
            return true;
        }else if(ky==(this->y)){
            if(kx>this->x){
                for(int i=((this->x)+1);i<=kx-1;i++){
                    if(!PosExistPiece(i,ky)) return false;
                }
            }else if(kx<this->x){
                for(int i=kx+1;i<=((this->x)-1);i++){
                    if(!PosExistPiece(i,ky)) return false;
                }
            }
            return true;
        }
        return false;
    }
};

#endif // ROOK_H
