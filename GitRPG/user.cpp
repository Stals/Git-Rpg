#include "user.h"
#include "tray.h"
#include <fstream>

User::User()
{
    loadStats();
}
User::~User(){
   saveStats();
}
void User::loadStats(){
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
void User::saveStats(){
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
	joint.maxExp=joint.lastExp+(plus.maxExp-plus.lastExp)+(minus.maxExp-minus.lastExp);
      ++joint.lvl;
      eQueue.push(levelUp,"You've achieved Joint Level "+ QString::number(joint.lvl).toStdString());

    }
    if(plus.exp>=plus.maxExp){
        plus.lastExp=plus.maxExp;
	plus.maxExp=plus.lastExp+200+20*plus.lvl;
      ++plus.lvl;
	eQueue.push(levelUp,"You've achieved Insertions Level "+ QString::number(plus.lvl).toStdString());
    }
    if(minus.exp>=minus.maxExp){
        minus.lastExp=minus.maxExp;
	minus.maxExp=minus.lastExp+50+10*minus.lvl;
      ++minus.lvl;
	eQueue.push(levelUp,"You've achieved Delitions Level "+ QString::number(minus.lvl).toStdString());
    }

}

