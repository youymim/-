#pragma once
#include"book.h"
#include"user.h"
#include<iostream>
#include<string>
#include<fstream>
#include<cstdio>
#include<limits>
class bookmanage {
public:
	bookmanage();
	user login();
	void showmanu();
	void borrowbooks(const user& u);
	void returnbooks(const user& u);
	void addbooks();
	void checkbooks();
	void checkrecord();
	~bookmanage();
};