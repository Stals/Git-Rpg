#include "user.h"
#include <fstream>
User::User()
{
     std::ifstream f("Stats.grpg");
     f>>name;

     f>>user.lvl;
     f>>user.exp;
     f>>user.maxExp;

     f>>plus.lvl;
     f>>plus.exp;
     f>>plus.maxExp;

     f>>minus.lvl;
     f>>minus.exp;
     f>>minus.maxExp;

     f.close();
}
User::~User(){
    std::ofstream f("Stats.grpg");
    f<<name<<std::endl;

    f<<user.lvl<<std::endl;
    f<<user.exp<<std::endl;
    f<<user.maxExp<<std::endl;

    f<<plus.lvl<<std::endl;
    f<<plus.exp<<std::endl;
    f<<plus.maxExp<<std::endl;

    f<<minus.lvl<<std::endl;
    f<<minus.exp<<std::endl;
    f<<minus.maxExp<<std::endl;

    f.close();

}
