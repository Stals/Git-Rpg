#ifndef USER_H
#define USER_H
#include <string>
//! TODO получается еще нужен стат minimumExp это опыт который был нужнен на прошлый уровень, вначале он =0, и используется для того чтобы вычитать из текущего опыта минимальный, и это и будет value для progressbara , также вычитаем его из maximumExp и это ставим как maximumValue

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
    Stats joint;
    Stats plus;
    Stats minus;
void checkForLvls();//проверяет и увеличивает уровень

};

#endif // USER_H
