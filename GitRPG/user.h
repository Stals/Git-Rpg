#ifndef USER_H
#define USER_H
#include <string>

struct Stats{

    int lvl;
    int lastExp;//���� ������������ ������ (�� ������ ������ = 0)
    int exp;
    int maxExp;
    Stats():lastExp(0){}
};
class User
{
public:

    User(); //��������� ������ �� ����� Stats.grpg
    ~User();//���������� ��� ���������� ���������, ��������� ���������� ������� � Stats.grpg
    std::string name;
    Stats joint;
    Stats plus;
    Stats minus;
void checkForLvls();//��������� � ����������� �������

};

#endif // USER_H
