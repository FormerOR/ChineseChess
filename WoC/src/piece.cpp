#include "piece.h"
#include "board.h"
#include "algorithms.h"

using Type = Piece::PieceType;

const std::map<Type, wchar_t> Piece::dict = {
    { Type::RED_SHUAI, L'帥' },
    { Type::BLACK_JIANG, L'將' },
    { Type::RED_SHI, L'仕' },
    { Type::BLACK_SHI, L'士' },
    { Type::RED_XIANG, L'相' },
    { Type::BLACK_XIANG, L'象' },
    { Type::RED_MA, L'馬' },
    { Type::BLACK_MA, L'馬' },
    { Type::RED_JU, L'車' },
    { Type::BLACK_JU, L'車' },
    { Type::RED_PAO, L'炮' },
    { Type::BLACK_PAO, L'炮' },
    { Type::RED_BING, L'兵' },
    { Type::BLACK_ZU, L'卒' }
};

//判断走了这一步之后会不会处于被将军状态
bool Piece::noThreat(int x, int y) const{
    //先创建一个所有棋子状态的列表
    auto list = Board::getBoard()->find();
    bool flag =false;
    std::pair<Pos, Piece::PieceType> temp;
    //找到当前选中棋子的信息
    for(auto &i:list){
        if(i.first.first==this->x&&i.first.second==this->y)
        {
            //如果去的地方有棋子 就把他删了
            for(auto j:list){
                if(j.first.first==x&&j.first.second==y){
                    temp.first.first=j.first.first;
                    temp.first.second=j.first.second;
                    temp.second=j.second;
                    flag = true;
                }
            }
            //把棋子移动过去
            i.first.first=x;
            i.first.second=y;
        }
    }
    if(flag)
        list.remove(temp);
    //调用isCheck判断当前状态棋盘是否会造成己方被将军,false为会被将军
    if(Algorithms::isCheck(list,side()))
        return false;
    else return true;
}
