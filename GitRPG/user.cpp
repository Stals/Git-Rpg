#include "user.h"
#include <fstream>
User::User()
{
     std::ifstream f("Stats.grpg");
     f>>name;

     f>>userLvl;
     f>>userExp;
     f>>userMaxExp;

     f>>plusLvl;
     f>>plusExp;
     f>>plusMaxExp;

     f>>minusLvl;
     f>>minusExp;
     f>>minusMaxExp;

}
