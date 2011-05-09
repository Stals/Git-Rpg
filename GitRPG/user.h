#ifndef USER_H
#define USER_H
#include <string>
struct Stats{

    int lvl;
    int exp;
    int maxExp;
};
class User
{
public:

    User(); //загружает данные из файла Stats.grpg
    ~User();//Вызывается при заверщении программы, сохраняет статистики обратно в Stats.grpg
    std::string name;
    Stats user;
    Stats plus;
    Stats minus;


};

#endif // USER_H
