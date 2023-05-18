#pragma once
#include"Client.h"
class Admin:public Client
{
public:
	Admin() {}
	Admin(string nam, string pers, string pho, string card, string pass, float balance) :Client(nam, pers, pho, card, pass, balance) {}

};

