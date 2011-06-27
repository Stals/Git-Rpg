#ifndef USER_H
#define USER_H
#include <string>
#include "eventqueue.h"

struct Stats{

    int lvl;
    int exp;
    int maxExp;
    int lastExp;//опыт предведущего уровн€ (на первой уровне = 0)
    Stats():lastExp(0){}
};
class User
{
public:

    User(); //загружает данные из файла Stats.grpg
    ~User();//¬ызываетс€ при заверщении программы, сохран€ет статистики обратно в Stats.grpg
    std::string name;
    Stats joint;
    Stats plus;
    Stats minus;
    std::pair<int,int>newExp;//плюс и минус полученные из файла Stals first - Additions, second - delitions
    //(обновл€етс€ методами mainwindow,даже при старте приложени€ получает значени€ там)
    //Ќо после того как пройдЄт func статы в newExp и в plus,minus будут одинаковы


    void checkForLvls();//провер€ет и увеличивает уровень
    std::string getStats();//возвращает строку дл€ печати или вывода
    void loadStats();
    void saveStats();

};

#endif // USER_H
