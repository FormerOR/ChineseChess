#include "board.h"
#include "algorithms.h"
#include "network.h"
#include "king.h"
#include "rook.h"
#include "pawn.h"
#include "adviser.h"
#include "elephant.h"
#include "horse.h"
#include "cannon.h"

using Type = Piece::PieceType;

Board::Board() {
    //Add your own code below
    //////////////////////////
    connect(this,&Board::onMyMove,Network::getInstance(),&Network::onMove);
    connect(Network::getInstance(),&Network::move,this,&Board::onMove);
    connect(Network::getInstance(),&Network::onWin,this,&Board::onWin);
    //////////////////////////
}
void Board::onWin(){
    emit win(side());
}
void Board::judgeStatus() {
    checked[!side()] = Algorithms::isCheck(!side());
    checked[side()] = Algorithms::isCheck(side());
    if (Algorithms::isStalemate(side()))
        return emit win(!side());
    if (Algorithms::isStalemate(!side()))
        return emit win(side());
}

void Board::onSetup(Cell** cells) {
    for (int i = 0; i < 10 * 9; i++) {
        auto& cell = cells[i];
        this->cells.emplace(std::piecewise_construct, std::tuple(cell->x, cell->y), std::tuple(cell));
    }
    std::map<Type, Constructor> factory = {
        //请将nullptr替换为'new ClassName(x, y, side)'，请正确设置派生类构造函数参数
        { Type::JIANG_SHUAI, [](int x, int y, bool side)->const Piece* { return new King(x,y,side); } },
        { Type::SHI, [](int x, int y, bool side)->const Piece* { return new Adviser(x,y,side); } },
        { Type::XIANG, [](int x, int y, bool side)->const Piece* { return new Elephant(x,y,side); } },
        { Type::MA, [](int x, int y, bool side)->const Piece* { return new Horse(x,y,side); } },
        { Type::JU, [](int x, int y, bool side)->const Piece* { return new Rook(x,y,side); } },
        { Type::PAO, [](int x, int y, bool side)->const Piece* { return new Cannon(x,y,side); } },
        { Type::BING_ZU, [](int x, int y, bool side)->const Piece* { return new Pawn(x,y,side); } }
    };
    setPieces(factory);
    for (const auto& [pos, piece] : pieces)
        this->cells[pos]->change(piece);
    if (side()) 
        your_turn = true;

    //Add your own code below
    //////////////////////////


    //////////////////////////
}

void Board::setPieces(const std::map<Type, Constructor> & factory) {
    static std::list<std::pair<Pos, Type>> piece_list = {
        { { 1, 1 }, Type::RED_JU },
        { { 2, 1 }, Type::RED_MA },
        { { 3, 1 }, Type::RED_XIANG },
        { { 4, 1 }, Type::RED_SHI },
        { { 5, 1 }, Type::RED_SHUAI },
        { { 6, 1 }, Type::RED_SHI },
        { { 7, 1 }, Type::RED_XIANG },
        { { 8, 1 }, Type::RED_MA },
        { { 9, 1 }, Type::RED_JU },
        { { 2, 3 }, Type::RED_PAO },
        { { 8, 3 }, Type::RED_PAO },
        { { 1, 4 }, Type::RED_BING },
        { { 3, 4 }, Type::RED_BING },
        { { 5, 4 }, Type::RED_BING },
        { { 7, 4 }, Type::RED_BING },
        { { 9, 4 }, Type::RED_BING },
        { { 1, 10 }, Type::BLACK_JU },
        { { 2, 10 }, Type::BLACK_MA },
        { { 3, 10 }, Type::BLACK_XIANG },
        { { 4, 10 }, Type::BLACK_SHI },
        { { 5, 10 }, Type::BLACK_JIANG },
        { { 6, 10 }, Type::BLACK_SHI },
        { { 7, 10 }, Type::BLACK_XIANG },
        { { 8, 10 }, Type::BLACK_MA },
        { { 9, 10 }, Type::BLACK_JU },
        { { 2, 8 }, Type::BLACK_PAO },
        { { 8, 8 }, Type::BLACK_PAO },
        { { 1, 7 }, Type::BLACK_ZU },
        { { 3, 7 }, Type::BLACK_ZU },
        { { 5, 7 }, Type::BLACK_ZU },
        { { 7, 7 }, Type::BLACK_ZU },
        { { 9, 7 }, Type::BLACK_ZU }
    };

    for (const auto& [pos, type] : piece_list)
        pieces.emplace(pos, factory.at(removeSide(type))(pos.first, pos.second, side() == getSide(type)));
}

void Board::move(const Pos from, const Pos to) {
//    qDebug()<<pieces;
    const auto piece = pieces.at(from);
    piece->move(to.first, to.second);
    emit waitSide();
//    qDebug()<<cells;
    auto cell_from = cells.at(from);
    cell_from->change(nullptr);
//    qDebug()<<cells;
    auto cell_to = cells.at(to);
    cell_to->change(piece);
    pieces.erase(from);
//      显而易见的胜利条件，但是象棋规则一般是以对方无棋可走为胜利条件
    if (pieces.count(to) && removeSide(pieces.at(to)->type) == Type::JIANG_SHUAI)
        emit win(your_turn ? side() : !side());
    pieces[to] = piece;
    judgeStatus();
}

void Board::onClick(int x, int y) {
    std::lock_guard guard(lock);
    static Piece const* selected = nullptr;
    if (!isYourTurn() || isMoved())
        return;
    const auto pos = std::make_pair(x, y);
    if (pieces.count(pos)) {
        const auto& piece = pieces.at(pos);
        if (piece->side() == side()) {
            selected = piece;
//            qDebug()<<selected->isValidMove(x,y);
            cells.at(pos)->select();
            return;
        }
    }
    if (!selected)
        return;
    if (selected->isValidMove(x, y)) {
//        qDebug()<<selected->isValidMove(x,y);
        cells.at(pos)->fineMove();
//        qDebug()<<"Board.cpp:onClick->selected->pos()在move之前:"<<selected->pos();
        //Add your own code here
        //////////////////////////
        emit onMyMove(selected->pos(),pos);
        //////////////////////////
        /// \brief move
        your_turn = false;
        move(selected->pos(), pos);
        moved = true;
        selected = nullptr;
    } else
        cells.at(pos)->wrongMove();
}

void Board::admit(){
    emit win(!side());
}

void Board::onMove(const Pos from, const Pos to) {
    std::lock_guard guard(lock);
//    qDebug()<<"Board:onMove->from,to:"<<from<<to;
    your_turn = true;
    move(from, to);
    moved = false;
}

const std::list<std::pair<Pos, Piece::PieceType>> Board::find(int x, int y, int side) const {
    //Add your own code here
    //////////////////////////
    std::list<std::pair<Pos, Piece::PieceType>> result;
    for (const auto& [pos, piece] : pieces){
        if(((x==-1)||(x==pos.first))&&((y==-1)||(y==pos.second))&&((side==-1)||((side!=-1)&&(side==piece->side())))){
            result.push_back(std::make_pair(pos,piece->type));
        }
    }
    return result;
    //////////////////////////
}
