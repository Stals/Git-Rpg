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
    //Хм, так у меня не получается контролировать уровень примерно рядом с плюсом. Вопрос почему
    //Просто скорость заполнения плюсов не такая как минусов потому- то происходит так что его большая часть (минусов) например 50% успевает пройти пока у плюсов только 20 потому и идёт опережения, так как он уровень получает еще до того как его получил плюс, за опыт больший
    //но для этого мне нужно в разных потоках заполнять, просто вот так как щас написано , будет работать только если сразу заполняется немного, тоесть когда только начинаеш фигачить гит, или новый проект, а не сразу 5000 тыщь. Что делать когда первый раз запускает типо, даже например я у которого 5 тыщ. конечно можно просто не добавлять такие большие проекты, но это не решение.
    //На мой взгляд решение это заполнение по скорости какраз равной разности плюсов и минусов в Stals. Так что если плюсов в 10 раз больше, то и заполняется он в 10 раз быстрее.
    //В данный моент единственным решением без потоков евлятеся штука как в StalsRPG когда в зависимости от агилы ходы меняются. И там есть контрольное число.Вот также нада. или потоки. Лучше потоки помоему.
    //Я короче точно уверен что это проблема того что статы заполняются все на 1 одновременно
    if(minus.exp>=minus.maxExp){
        minus.lastExp=minus.maxExp;
	minus.maxExp=minus.lastExp+(plus.maxExp-plus.lastExp)*(double)((double)newExp.second/(double)newExp.first);
	++minus.lvl;
	eQueue.push(levelUp,"You've achieved Delitions Level "+ QString::number(minus.lvl).toStdString());
    }

}

