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
    //Опыт общего уровня это опыт который нужен для уровня plus и minus вместе на момент уровня joint
    if(joint.exp>=joint.maxExp){
        joint.lastExp=joint.maxExp;
	//! TODO тут возможно на 2ом уровне нужно будет опыта меньше чем на первом...
	joint.maxExp=joint.lastExp+(plus.maxExp-plus.lastExp)+(minus.maxExp-minus.lastExp);
	++joint.lvl;
	eQueue.push(levelUp,"You've achieved Joint Level "+ QString::number(joint.lvl).toStdString());

    }
    //Увеличения  Опыта plus ,нужного для уровня,  является линейным и просто каждый уровень опыта нужно на 20 больше
    if(plus.exp>=plus.maxExp){
        plus.lastExp=plus.maxExp;
	plus.maxExp=plus.lastExp+200+20*plus.lvl;
	++plus.lvl;
	eQueue.push(levelUp,"You've achieved Insertions Level "+ QString::number(plus.lvl).toStdString());
    }
    //Опыт minus увеличивается в зависимости от разности его и plus, она получается из newExp

    if(minus.exp>=minus.maxExp){
        minus.lastExp=minus.maxExp;
	minus.maxExp=minus.lastExp+(plus.maxExp-plus.lastExp)*(double)((double)newExp.second/(double)newExp.first);
	++minus.lvl;
	eQueue.push(levelUp,"You've achieved Delitions Level "+ QString::number(minus.lvl).toStdString());
    }

}
std::string User::getStats(){
    return  "Joint Level "+QString::number(joint.lvl).toStdString()+" ("+QString::number(joint.exp-joint.lastExp).toStdString()+"/"+QString::number(joint.maxExp-joint.lastExp).toStdString()+")\n"+
	    "Insertions Level "+QString::number(plus.lvl).toStdString()+" ("+QString::number(plus.exp-plus.lastExp).toStdString()+"/"+QString::number(plus.maxExp-plus.lastExp).toStdString()+")\n"+
	    "Delitions Level "+QString::number(minus.lvl).toStdString()+" ("+QString::number(minus.exp-minus.lastExp).toStdString()+"/"+QString::number(minus.maxExp-minus.lastExp).toStdString()+")";
}

