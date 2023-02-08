#ifndef HORSE_H
#define HORSE_H

#include "piece.h"
#include "board.h"
#include "QDebug"

class Horse : public Piece
{
private:
    //马可到的8个点
    const Pos s[8]={{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{-1,2},{1,-2},{-1,-2}};
    //蹩马腿的8个点与前往的方向一一对应
    const Pos b[8]={{1,0},{1,0},{-1,0},{-1,0},{0,1},{0,1},{0,-1},{0,-1}};
public:
    Horse(int x,int y,bool side):Piece(x,y,side ? PieceType::RED_MA: PieceType::BLACK_MA){};
    virtual bool isBasicMove(int x,int y)const{
        if(Board::getBoard()->find(x,y).empty() || !isSidePiece(*(Board::getBoard()->find(x,y).begin()))){
            for(int i=0;i<8;i++){
                if((x-(this->x)==s[i].first)&&(y-(this->y)==s[i].second)){
                    bool flag=((x-(this->x)==s[i].first)&&(y-(this->y)==s[i].second));
//                    qDebug()<<"让此次允许移动的判断条件"<<flag;
//                    qDebug()<<"马对应的i:"<<i;
                    //相应的蹩马腿点位没有棋子
                    if(Board::getBoard()->find(this->x+b[i].first,this->y+b[i].second).empty()){
                        return true;
                    }
                }
            }
        }
        return false;
    }
    virtual const std::list<Pos> getPossibleMoves() const{
        std::list<Pos> result;
        for(int i=0;i<8;i++){
            //尝试的8种点位不能超出棋盘
            if(this->x+s[i].first>9||this->x+s[i].first<1||this->y+s[i].second>10||this->y+s[i].second<1){
                continue;
            }
            if(isValidMove(this->x+s[i].first,this->y+s[i].second))
                result.push_back(std::make_pair(this->x+s[i].first,this->y+s[i].second));
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
        //先判断对方将在不在马的攻击范围内
        for(int i=0;i<8;i++){
            if(kx==this->x+s[i].first&&ky==this->y+s[i].second){
                //再判断对于蹩马腿位置有没有棋子
                auto notExistAtPos = [=](int a,int b)->bool{
                    for(auto [pos,type]:pieces){
                        if(pos.first==a&&pos.second==b)return false;//如果存在坐标相等的，就返回false
                    }
                    return true;//empty则输出true
                };
                if(notExistAtPos(this->x+b[i].first,this->y+b[i].second))
                    return true;
            }
        }
        return false;
    }
};

#endif // HORSE_H
