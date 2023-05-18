#pragma once
#include"Person.h"
class Client :public Person
{
private:
	
public:
	Client() {}
	Client(string nam, string pers, string pho, string card, string pass,float balance) :Person(nam, pers, pho, card,pass,balance){}
};

