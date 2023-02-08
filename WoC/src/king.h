#ifndef KING_H
#define KING_H

#include "piece.h"
#include "board.h"

class King:public Piece{
private:
    const Pos s[4] = { {0,1},{0,-1},{1,0},{-1,0} };//将帅可以到达的四个点位
public :
    King(int x,int y,bool side):Piece(x,y,side ? PieceType::RED_SHUAI : PieceType::BLACK_JIANG){}
    virtual bool isBasicMove(int x, int y) const{
        if(!Board::getBoard()->find(x,y,side()).empty())return false;
        if(Board::getBoard()->find(x,y).empty() || !isSidePiece(*(Board::getBoard()->find(x,y).begin())))//要去的位置是否为空或者是敌方的一个棋子
        {
            if(isInNinePalaces(x,y))//要去的地方是否是在九宫格里
            {
                for(int i=0;i<4;i++)
                {
                    if ((x==this->x+s[i].first)&&(y==this->y+s[i].second))//是否满足将帅只走左右上下的规则
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    virtual bool isThreat(const std::list<std::pair<Pos, Piece::PieceType>>& pieces)const{
        if(Board::getBoard()->isChecked(side()))return false;
        //获取对面王的坐标
        int ox,oy;
        for(auto &i:pieces){
            if(i.second==(side()?Piece::PieceType::BLACK_JIANG:Piece::PieceType::RED_SHUAI)){
                ox = i.first.first;
                oy = i.first.second;
                break;
            }
        }
        auto notExistAtPos = [=](int a,int b)->bool{
            for(auto [pos,type]:pieces){
                if(pos.first==a&&pos.second==b)return false;
            }
            return true;
        };
        //将帅之间不能有棋子
        if(ox==x){
            if(oy>y){
                for(int i=y+1;i<=oy-1;i++){
                    if(!notExistAtPos(ox,i)) return false;
                }
                return true;
            }else if(oy<y){
                for(int i=oy+1;i<=y-1;i++){
                    if(!notExistAtPos(ox,i)) return false;
                }
                return true;
            }
        }else return false;
    }
    virtual const std::list<Pos> getPossibleMoves() const{
        std::list<Pos> result;
        for(auto &i:s){
            if(isValidMove(this->x+i.first,this->y+i.second)){
                result.push_back(i);
            }
        }
        return result;
    }

};
#endif // KING_H
