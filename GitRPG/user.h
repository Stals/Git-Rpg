#ifndef USER_H
#define USER_H
#include <string>
struct Stats{

    int lvl;
    int exp;
    int maxExp;
};
class User
{
public:

    User(); //��������� ������ �� ����� Stats.grpg
    ~User();//���������� ��� ���������� ���������, ��������� ���������� ������� � Stats.grpg
    std::string name;
    Stats user;
    Stats plus;
    Stats minus;


};

#endif // USER_H
