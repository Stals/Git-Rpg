#ifndef USER_H
#define USER_H
#include <string>
//! TODO ���������� ��� ����� ���� minimumExp ��� ���� ������� ��� ������ �� ������� �������, ������� �� =0, � ������������ ��� ���� ����� �������� �� �������� ����� �����������, � ��� � ����� value ��� progressbara , ����� �������� ��� �� maximumExp � ��� ������ ��� maximumValue

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
    Stats joint;
    Stats plus;
    Stats minus;
void checkForLvls();//��������� � ����������� �������

};

#endif // USER_H
