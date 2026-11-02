#include"bookmanage.h"
using namespace std;
const string BOOKS = "books.txt";
const string USER = "user.txt";
const string LOG = "log.txt";
const string TEMP = "temp.txt";
const string TEMP1 = "temp1.txt";
bookmanage::bookmanage()
{

}
user bookmanage::login()
{
	ifstream ifs(USER, ios::in);
	ofstream ofs(USER, ios::app);
	user u;
	cout << "登录或注册" << endl;
	cout << "请输入姓名和编号：" << endl;
	cin >> u.uname >> u.uid;
	string line;
	bool found = false;
	while (getline(ifs, line))
	{
		string name = line.substr(0, line.find(","));
		if (u.uname == name)
		{
			found = true;
		}
	}
	if (found)
	{
		cout << "欢迎回来" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		ofs << u.uname << "," << u.uid << endl;
		cout << "注册成功" << endl;
		system("pause");
		system("cls");
	}
	ifs.close();
	ofs.close();
	return u;
}
void bookmanage::showmanu()
{
	cout << "欢迎使用图书管理系统" << endl;
	cout << "请选择要使用的功能：" << endl;
	cout << "1.借书" << endl;
	cout << "2.还书" << endl;
	cout << "3.添书" << endl;
	cout << "4.查书" << endl;
	cout << "5.查看借书记录" << endl; //管理员拥有权限，用户只能看见自己的记录
	cout << "0.退出" << endl;
}
void bookmanage::borrowbooks(const user& u)
{
	ifstream ifs(BOOKS, ios::in);
	ofstream temp(TEMP, ios::out);
	ofstream log(LOG,ios::app);
	//user u;
	book b;
	if (!ifs.is_open()||!temp.is_open()||!log.is_open())
	{
		cout << "没有书籍或加载失败" << endl;
		return;
	}
	else
	{
		//cout << "请输入你的姓名和编号：" << endl;
		//cin >> u.uname >> u.uid;
		cout << "请输入你要找的书籍名称：" << endl;
		cin >> b.bname;
		string line;
		bool found = false;
		while (getline(ifs, line))
		{
			string name = line.substr(0, line.find(','));
			if (name == b.bname)
			{
				cout << "找到了:" <<line << endl;
				size_t pos = line.find("已借出");
				if (pos != string::npos)
				{
					cout << "该书籍已被借出，请选择其他书籍" << endl;
					return;
				}
				else
				{
					temp << line << "(已借出)" << endl;
					//u.count++;
					log << u.uname << "," << u.uid << "," << line << "," << u.count << " 次" << "(未还)" << endl;
					found = true;
				}
			}
		}
		ifs.close();
		temp.close();
		log.close();
		if (remove(BOOKS.c_str())!=0||rename(TEMP.c_str(), BOOKS.c_str())!=0)
		{
			cout << "文件内容迁移过程发生错误" << endl;
		}
		if (found)
		{
			cout << b.bname << "已成功借出" << endl;
		}
		else
		{
			cout << "没有找到《" << b.bname << "》" << endl;
		}
		return;
	}
	
}
void bookmanage::returnbooks(const user& u)
{
	ifstream ifs(BOOKS, ios::in);
	ofstream temp(TEMP, ios::out);
	ofstream temp1(TEMP1, ios::out);
	ifstream log(LOG, ios::in);
	//user u;
	book b;
	if (!ifs.is_open()||!temp.is_open()||!temp1.is_open()||!log.is_open())
	{
		cout << "加载失败" << endl;
		return;
	}
	else
	{
		//cout << "请输入你的姓名和编号：" << endl;
		//cin >> u.uname >> u.uid;
		cout << "请输入要还的书籍名称：" << endl;
		cin >> b.bname;
		string line;
		bool found1 = false;
		bool found2 = false;
		while (getline(ifs, line))
		{
			string name = line.substr(0, line.find(","));
			if (name == b.bname)
			{
				found1 = true;
				size_t pos = line.find("(");
				if (pos != string::npos)
				{
					line.erase(pos, string("(已借出)").length());
					string yline;
					while (getline(log, yline))
					{
						size_t ypos = yline.find(name);
						if (ypos != string::npos)
						{
							size_t pos1 = yline.find("未");
							if (pos1 != string::npos)
							{
								found2 = true;
								yline.replace(pos1, string("未还").length(), "已还");
							}
							else
							{
								cout << "此人并未借出该书籍，请重新检查" << endl;
							}
						}
						temp1 << yline << endl;
					}
				}
				else
				{
					cout << "该书并未借出，请检查是否输入错误" << endl;
					return;
				}
			}
			temp << line << endl;
		}
		ifs.close();
		temp.close();
		temp1.close();
		log.close();
		if (remove(BOOKS.c_str()) !=0|| rename(TEMP.c_str(), BOOKS.c_str()) !=0||
			remove(LOG.c_str())!=0 || rename(TEMP1.c_str(), LOG.c_str())!=0)
		{
			cout << "文件迁移过程中发生错误" << endl;
		}
		if (found1 == true && found2 == true)
		{
			cout << "归还成功：《" << b.bname << "》且记录已更新" << endl;
		}
		else
		{
			cout << "该书籍未记录在库，请重新检查" << endl;
		}
	}
}
void bookmanage::addbooks()
{
	ofstream ofs(BOOKS,ios::app);
	book b;
	if (!ofs.is_open())
	{
		cout << "文件打开失败！" << endl;
		return;
	}
	else
	{
		cout << "请输入要添加的书名，作者，价格和编号：" << endl;
		cin >> b.bname >> b.author >> b.price >> b.bid;
		ofs << b.bname <<","<< b.author <<","<< b.price <<","<< b.bid << endl;
		ofs.close();
		cout << "已保存：" << b.bname << endl;
		return;
	}
}
void bookmanage::checkbooks()
{
	ifstream ifs(BOOKS);
	if (!ifs.is_open())
	{
		cout << "没有书籍" << endl;
		return;
	}
	else
	{
		string line;
		while (getline(ifs, line))
		{
			cout << line << endl;
		}
		ifs.close();
		cout << "书籍已加载完成" << endl;
		return;
	}
}
void bookmanage::checkrecord()
{
	ifstream ifs(LOG,ios::in);
	if (!ifs.is_open())
	{
		cout << "暂未借过书" << endl;
		return;
	}
	else
	{
		//cout << "请选择方式：" << endl;
		//cout << "1.按时间查看" << endl;
		//cout << "2.按书名查看" << endl;
		//int select = 0;
		//cin >> select;
		string line;
		while (getline(ifs, line))
		{
			cout << line << endl;
		}
		ifs.close();
		cout << "记录加载完成" << endl;
		return;
	}
}
bookmanage::~bookmanage()
{

}