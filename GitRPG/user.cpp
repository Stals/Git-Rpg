#include "user.h"
#include <fstream>

User::User()
{
     std::ifstream f("Stats.grpg");
     f>>name;

     f>>joint.lvl;
     f>>joint.exp;
     f>>joint.maxExp;
     f>>joint.lastExp;

     f>>plus.lvl;
     f>>plus.exp;
     f>>plus.maxExp;
     f>>plus.lastExp;

     f>>minus.lvl;
     f>>minus.exp;
     f>>minus.maxExp;
     f>>minus.lastExp;

     f.close();
}
User::~User(){
    std::ofstream f("Stats.grpg");
    f<<name<<std::endl;

    f<<joint.lvl<<std::endl;
    f<<joint.exp<<std::endl;
    f<<joint.maxExp<<std::endl;
    f<<joint.lastExp<<std::endl;

    f<<plus.lvl<<std::endl;
    f<<plus.exp<<std::endl;
    f<<plus.maxExp<<std::endl;
    f<<plus.lastExp<<std::endl;

    f<<minus.lvl<<std::endl;
    f<<minus.exp<<std::endl;
    f<<minus.maxExp<<std::endl;
    f<<minus.lastExp<<std::endl;

    f.close();

}
void User::checkForLvls(){

    if(joint.exp>=joint.maxExp){
        joint.lastExp=joint.maxExp;
        joint.maxExp*=(double)1.5;
        joint.maxExp+=50;
      ++joint.lvl;
        eQueue.push(levelUp,"Joint Level up");
    }
    if(plus.exp>=plus.maxExp){
        plus.lastExp=plus.maxExp;
        plus.maxExp*=(double)1.5;
        plus.maxExp+=30;
      ++plus.lvl;
        eQueue.push(levelUp,"Insertions Level up");
    }
    if(minus.exp>=minus.maxExp){
        minus.lastExp=minus.maxExp;
        minus.maxExp*=(double)1.5;
        minus.maxExp+=20;
      ++minus.lvl;
        eQueue.push(levelUp,"Delitions Level up");
    }

}

