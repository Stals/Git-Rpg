#ifndef USER_H
#define USER_H
#include <string>
class User
{
public:

    User(); //загружает данные из файла Stats.grpg
    std::string name;
    int userLvl;
    int userExp;
    int userMaxExp;

    int plusLvl;
    int plusExp;
    int plusMaxExp;

    int minusLvl;
    int minusExp;
    int minusMaxExp;

};

#endif // USER_H
