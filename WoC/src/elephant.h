#ifndef ELEPHANT_H
#define ELEPHANT_H

#include "piece.h"
#include "board.h"
#include "QDebug"

class Elephant : public Piece
{
private:
    //象可去四个点位
    const Pos s[4]={ {2,2},{2,-2},{-2,2},{-2,-2} };
    //四个对于蹩象眼的点位
    const Pos b[4]={ {1,1},{1,-1},{-1,1},{-1,-1} };
public:
    Elephant(int x,int y,bool side):Piece(x,y,side ? PieceType::RED_XIANG: PieceType::BLACK_XIANG){};
    virtual bool isBasicMove(int x,int y)const{
        if(Board::getBoard()->find(x,y).empty() || !isSidePiece(*(Board::getBoard()->find(x,y).begin()))){
            //象不能过河,即判断选择的点位一定要在己方区域内
            bool isInside=(y<=5);
//            qDebug()<<y<<isInside;
            if(isInside){
                for(int i=0;i<4;i++){
                    if(this->x+s[i].first==x&&this->y+s[i].second==y){
                        //象眼不能有棋子
                        if(Board::getBoard()->find(this->x+b[i].first,this->y+b[i].second).empty())
                            return true;
                    }
                }
            }
        }
        return false;
    }
    virtual const std::list<Pos> getPossibleMoves() const{
        std::list<Pos> result;
        for(int i=0;i<4;i++){
            //不要超过棋盘
            if(this->x+s[i].first>9||this->x+s[i].first<1||this->y+s[i].second>10||this->y+s[i].second<1){
                continue;
            }
            if(isValidMove(this->x+s[i].first,this->y+s[i].second))
                result.push_back(std::make_pair(this->x+s[i].first,this->y+s[i].second));
        }
        return result;
    }
    virtual bool isThreat(const std::list<std::pair<Pos, Piece::PieceType>>& pieces)const{
        //象无法过界也就无法威胁
        return false;
    }
};

#endif // ELEPHANT_H
