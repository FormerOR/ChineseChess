#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "board.h"
#include "king.h"
#include "rook.h"
#include "pawn.h"
#include "adviser.h"
#include "elephant.h"
#include "horse.h"
#include "cannon.h"

//工具类
class Algorithms {
public:
    //判断僵局(无子可走)
    static bool isStalemate(bool side) {
        auto result = Board::getBoard()->find(-1, -1, side);

        for (const auto& [pos, type] : result) {
            auto piece = Board::getBoard()->pieces.at(pos);
            if (!piece->getPossibleMoves().empty())
                return false;
        }

        return true;
    }

    //Piece::noThreat和Algorithms::isCheck的推荐辅助函数
    //反复调用对方所有棋子的isThreat，如果都是false则没有处在被将军状态
    //list里存的是每个棋子的信息而不是子类实例，想要调用子类实例的isThreat就需要创建一个信息和原棋子相同的临时棋子，然后调用这个临时棋子的isThreat
    static inline bool isCheck(const std::list<std::pair<Pos, Piece::PieceType>>& pieces, bool side) {
        auto createPiece = [=](Pos p,Piece::PieceType type)->std::shared_ptr<Piece>{
            switch(removeSide(type)){
            case Piece::PieceType::BING_ZU:{
                return std::make_shared<Pawn>(p.first,p.second,!side);
            }break;
            case Piece::PieceType::JIANG_SHUAI:{
                return std::make_shared<King>(p.first,p.second,!side);
            }break;
            case Piece::PieceType::PAO:{
                return std::make_shared<Cannon>(p.first,p.second,!side);
            }break;
            case Piece::PieceType::JU:{
                return std::make_shared<Rook>(p.first,p.second,!side);
            }break;
            case Piece::PieceType::SHI:{
                return std::make_shared<Adviser>(p.first,p.second,!side);
            }break;
            case Piece::PieceType::XIANG:{
                return std::make_shared<Elephant>(p.first,p.second,!side);
            }break;
            case Piece::PieceType::MA:{
                return std::make_shared<Horse>(p.first,p.second,!side);
            }break;
            }
        };
        //依次调用所有棋子的isThreat
        for(auto i:pieces){
            //qDebug()<<i.first<<" "<<(int)i.second;
            if(getSide(i.second)==!side){
                std::shared_ptr<Piece> temp = createPiece(i.first,i.second);
                //qDebug()<<i.first<<" "<<temp->isThreat(pieces);
                if(temp->isThreat(pieces))return true;
            }
        }
        return false;
    }


    static bool isCheck(bool side) {
        return isCheck(Board::getBoard()->find(), side);
    }
};

#endif // ALGORITHMS_H
