#pragma once
#include<iostream>
using namespace std;
class Person
{
private:
	string name;
	string personal_id;
	string phone_num;
	string password;
	float balance;
	string card_num;
	int age ;

public:
	Person() {}
	Person(string nam, string pers, string pho, string card,string password,float balance):name(nam),personal_id(pers),phone_num(pho),card_num(card),password(password),balance(balance){}
	string getname();
	void setname(string);
	string getpersonal_id();
	void setpersonal_id(string);
	string getphone_num();
	void setphone_num(string);
	string getcard_num();
	float getbalance();
	string getpassword();
	void setpassword(string);
	void setbalance(float);
	int getage();
};

