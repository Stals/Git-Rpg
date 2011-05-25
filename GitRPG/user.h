#ifndef USER_H
#define USER_H
#include <string>

struct Stats{

    int lvl;
    int exp;
    int maxExp;
    int lastExp;//опыт предведущего уровня (на первой уровне = 0)
    Stats():lastExp(0){}
};
class User
{
public:

    User(); //загружает данные из файла Stats.grpg
    ~User();//Вызывается при заверщении программы, сохраняет статистики обратно в Stats.grpg
    std::string name;
    Stats joint;
    Stats plus;
    Stats minus;
void checkForLvls();//проверяет и увеличивает уровень

};

#endif // USER_H
