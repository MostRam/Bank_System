#include "Person.h"

string Person::getname()
{
	return name;
}
void Person::setname(string n) {
	name = n;
}

string Person::getpersonal_id()
{
	return personal_id;
}
void Person::setpersonal_id(string id) {
	personal_id = id;
}

string Person::getphone_num()
{
	return phone_num;
}
void Person::setphone_num(string ph)
{
	phone_num = ph;
}
string Person::getcard_num()
{
	return card_num;
}

float Person::getbalance()
{
	return balance;
}

string Person::getpassword()
{
	return password;
}

void Person::setpassword(string pass)
{
	password = pass;
}

void Person::setbalance(float newbalance)
{
	balance = newbalance;
}

int Person::getage()
{
	return age;
}