#include"bookmanage.h"
#include<cstdlib>
using namespace std;
int main()
{
	bookmanage bm;
	user u = bm.login();
	while (true)
	{
		bm.showmanu();
		int select = 0;
		cin >> select;
		if (cin.fail())              // 读数字失败了
		{
			cin.clear();             // 1. 清除错误状态
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 2. 扔掉缓冲区里的字母
			cout << "输入无效，请输入数字！" << endl;
			system("pause");
			system("cls");
			continue;                // 3. 直接进入下一圈，不执行 switch
		}
		switch (select)
		{
		case 1:
			bm.borrowbooks(u);
			break;
		case 2:
			bm.returnbooks(u);
			break;
		case 3:
			bm.addbooks();
			break;
		case 4:
			bm.checkbooks();
			break;
		case 5:
			bm.checkrecord();
			break;
		case 0:
			cout << "成功退出" << endl;
			exit(0);
		default:
			cout << "没有这个选项，请重新输入" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}
