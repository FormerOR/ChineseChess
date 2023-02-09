# ChineseChess
南京邮电大学2023C++组WoC，基于qt的关于实现象棋基本玩法和功能的项目

### 项目任务要求
##### （1）基本任务
1.	重写class Piece派生类中的bool isBasicMove(int x, int y)函数实现对派生类棋子基本走法的限制约束。√
2.	重写class Piece派生类中的isValidMove (int x, int y)函数实现对派生类棋子走法是否可行的判断。√
3.	在1、2的基础上，重写class Piece派生类中getBasicMoves()函数，实现获得该子所有可能走法的功能。√
4.	为class board实现find函数。其中，side筛选棋子颜色，-1不筛选；x筛选棋子横坐标，-1不筛选；y筛选棋子纵坐标，-1不筛选。√
5.	用lambda表达式为每一个class Piece的派生类实现一个工厂函数。○

    (做了但没有完全符合要求，有些棋子走法简单无需用到工厂函数就没有用lambda)
6.	实现class Piece中bool noThreat(int x, int y)判断走棋后是否处于将军状态。√
7.	正确虚析构和使用std::shared_ptr、std::weak_ptr使得吃子自动析构。×
（不太理解智能指针的使用）
8.	合理配置信号槽使得网络、数据、界面三者解耦，并使得UI正确响应。√
9.	使用Qt网络库根据API正确处理get请求的响应。√
##### （2）进阶任务（选做）
1.	学习和使用qss装点界面。√
2.	优化算法逻辑。√
3.	当遇到网络原因，引导用户重新开始。× （似乎搞定登陆和找对手后基本不会出现什么网络问题，所以就没有实现这个任务）
4.	根据API实现聊天功能。√
5.	根据API实现认输功能。√
### 相关功能图片
##### 登录界面图片
![登录界面](https://user-images.githubusercontent.com/110514151/217797785-b0f1a487-f156-4863-b529-822453aeea43.png)
##### 开始界面图片
![开始界面](https://user-images.githubusercontent.com/110514151/217798076-a15f7c48-ec87-4706-b572-becc351be85c.png)
##### 开始游戏后界面图片
![开始游戏后界面](https://user-images.githubusercontent.com/110514151/217798867-cd7bad3a-d624-44ac-a9bf-39dc4844fcbb.png)
##### 出棋后界面图片
![出棋后界面](https://user-images.githubusercontent.com/110514151/217799270-95272f71-3e03-47eb-9013-7effe12bf50f.png)
##### 己方走棋保护，防止己方被将军
![保护机制](https://user-images.githubusercontent.com/110514151/217799655-6fc130ab-ff19-4b7b-8e0e-453d9cdcf30f.png)
##### 发送消息图片
![发送消息图片](https://user-images.githubusercontent.com/110514151/217800274-a4e7e9ca-fa83-4e9c-b16f-1704d3099a4c.png)
##### 认输功能图片
![认输功能图片](https://user-images.githubusercontent.com/110514151/217800418-5a65f277-780b-49bd-b968-f68d3f17054b.png)








