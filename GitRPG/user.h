#ifndef USER_H
#define USER_H
#include <string>
#include "eventqueue.h"

struct Stats{

    int lvl;
    int exp;
    int maxExp;
    int lastExp;//���� ������������ ������ (�� ������ ������ = 0)
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
    std::pair<int,int>newExp;//���� � ����� ���������� �� ����� Stals first - insertions, second - delitions
    //(����������� �������� mainwindow,���� ��� ������ ���������� �������� �������� ���)
    //�� ����� ���� ��� ������ func ����� � newExp � � plus,minus ����� ���������


    void checkForLvls();//��������� � ����������� �������
    std::string getStats();//���������� ������ ��� ������ ��� ������
    void loadStats();
    void saveStats();

};

#endif // USER_H
