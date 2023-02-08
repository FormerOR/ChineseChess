#ifndef CANNON_H
#define CANNON_H

#include "piece.h"
#include "board.h"

class Cannon : public Piece
{
public:
    Cannon(int x,int y,bool side):Piece(x,y,side ? PieceType::RED_PAO: PieceType::BLACK_PAO){};
    virtual bool isBasicMove(int x,int y)const{
        //第一种走法，走直线不吃子
        if(Board::getBoard()->find(x,y).empty()){
            //上下移动
            if(this->x==x){
                //向上走
                if(y>this->y){
                    for(int i=this->y+1;i<=y;i++){
                        if(!Board::getBoard()->find(x,i).empty())
                            return false;
                    }
                    return true;
                }else{
                    //向下走
                    for(int i=this->y-1;i>=y;i--){
                        if(!Board::getBoard()->find(x,i).empty())
                            return false;
                    }
                    return true;
                }
            }else if(this->y==y){
                //左右移动
                //向左走
                if(this->x>x){
                    for(int i=x;i<this->x;i++){
                        if(!Board::getBoard()->find(i,y).empty())
                            return false;
                    }
                    return true;
                }else{
                    //向右走
                    for(int i=x;i>this->x;i--){
                        if(!Board::getBoard()->find(i,y).empty())
                            return false;
                    }
                    return true;
                }

            }
            return false;
        }else if(!isSidePiece(*(Board::getBoard()->find(x,y).begin()))){//第二种走法，中间隔一个棋子吃子
            int count=0;
            if(this->x==x){
                //向上走
                if(y>this->y){
                    for(int i=this->y+1;i<y;i++){
                        if(!Board::getBoard()->find(x,i).empty())
                            count++;
                    }
                }else{
                    //向下走
                    for(int i=this->y-1;i>y;i--){
                        if(!Board::getBoard()->find(x,i).empty())
                            count++;
                    }
                }
                if(count==1)
                    return true;
            }else if(this->y==y){
                //左右移动
                //向左走
                if(this->x>x){
                    for(int i=x+1;i<this->x;i++){
                        if(!Board::getBoard()->find(i,y).empty())
                            count++;
                    }

                }else{
                    //向右走
                    for(int i=x-1;i>this->x;i--){
                        if(!Board::getBoard()->find(i,y).empty())
                            count++;
                    }

                }
                if(count==1)
                    return true;

            }
            return false;
        }

    }
    virtual const std::list<Pos> getPossibleMoves() const{
        std::list<Pos> result;
        //遍历跑所在的十字区域
        for(int j=1;j<=9;j++){
            if(j==this->x)
                continue;
            if(isValidMove(j,y)){
                result.push_back(std::make_pair(j,y));
            }
        }
        for(int j=1;j<=10;j++){
            if(j==this->y)
                continue;
            if(isValidMove(x,j)){
                result.push_back(std::make_pair(x,j));
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
        auto PosExistPiece = [=](int a,int b)->bool{
            for(auto [pos,type]:pieces)
            {
                if(pos.first==a&&pos.second==b)
                    return true;
            }
            return false;
        };
//        if(kx==(this->x)){
//            if(ky>this->y){
//                int j = 0;
//                for(int i=((this->y)+1);i<=ky-1;i++){
//                    if(PosExistPiece(kx,i)) j++;
//                }
//                if(j==0||j>1)return false;
//                else return true;
//            }else if(ky<this->y){
//            int j = 0;
//            for(int i=ky+1;i<=((this->y)-1);i++){
//                if(PosExistPiece(kx,i)) j++;
//            }
//                if(j==0||j>1)return false;
//                else return true;
//            }
//        }else if(ky==(this->y)){
//            if(kx>this->x){
//                int j = 0;
//                for(int i=((this->x)+1);i<=kx-1;i++){
//                    if(PosExistPiece(i,ky)) j++;
//                }
//                if(j==0||j>1)return false;
//                else return true;
//            }else if(kx<this->x){
//                int j = 0;
//                for(int i=kx+1;i<=((this->x)-1);i++){
//                    if(PosExistPiece(i,ky)) j++;
//                }
//                if(j==0||j>1)return false;
//                else return true;
//            }
//        }else return false;

        //首先排除不在同行同列的情况
        if(this->x!=kx&&this->y!=ky)
            return false;
        //只有第二种走法才可以对王造成威胁
        int count=0;
        if(this->x==kx){
            //向上走
            if(ky>this->y){
                for(int i=this->y+1;i<ky;i++){
                    if(PosExistPiece(x,i))
                        count++;
                }
            }else{
                //向下走
                for(int i=this->y-1;i>ky;i--){
                    if(PosExistPiece(x,i))
                        count++;
                }
            }
            if(count==1)
                return true;
        }else if(this->y==ky){
            //左右移动
            //向左走
            if(this->x>kx){
                for(int i=kx+1;i<this->x;i++){
                    if(PosExistPiece(i,y))
                        count++;
                }

            }else{
                //向右走
                for(int i=kx-1;i>this->x;i--){
                    if(PosExistPiece(i,y))
                        count++;
                }
            }
            if(count==1)
                return true;
        }
        return false;
    }
};

#endif // CANNON_H
