#include "user.h"
#include <fstream>
User::User()
{
     std::ifstream f("Stats.grpg");
     f>>name;

     f>>joint.lvl;
     f>>joint.exp;
     f>>joint.maxExp;

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

    f<<joint.lvl<<std::endl;
    f<<joint.exp<<std::endl;
    f<<joint.maxExp<<std::endl;

    f<<plus.lvl<<std::endl;
    f<<plus.exp<<std::endl;
    f<<plus.maxExp<<std::endl;

    f<<minus.lvl<<std::endl;
    f<<minus.exp<<std::endl;
    f<<minus.maxExp<<std::endl;

    f.close();

}
void User::checkForLvls(){
    if(joint.exp>=joint.maxExp){
        joint.maxExp*=2;
      ++joint.lvl;
    }
    if(plus.exp>=plus.maxExp){
        plus.maxExp*=2;
      ++plus.lvl;
    }
    if(minus.exp>=minus.maxExp){
        minus.maxExp*=2;
      ++minus.lvl;
    }
    //
}
