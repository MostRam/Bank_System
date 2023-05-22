#include <iostream>
#include<iomanip>
#include<sstream>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<string>
#include"Client.h"
#include"Admin.h" 
using namespace std;
Client* createaccount();
void signin();
void editfile(Client,string ="C", bool=0);
void incrementstring(string&);
void editaccountdata(Client*);
Admin* signinadmin();
Admin* signupadmin(Admin* );
void asadmin(Admin*);
string accline(string);

int main()
{
MainMenu:
    cout << setw(45) << "BANK SYSTEM\n";
    cout << "\t\tWelcome to my bank system project\n\tMain menu";
    char choose;
    cout << "\n\t\tChoose by eneter the number\n\t1- Create Client Account\n\t2- Sign in to your account\n\t3- create Admin account\n\t4- Enter AS Admin\n\t5- Exit\n";
    cin >> choose;
    if (choose == '1') {
        Client* createdclient(createaccount());
    }
    if (choose == '2')
    {
        signin();
    }
    if (choose == '3')
    {
        cout << "TO CREATE ADMIN ACCOOUNT YOU MUST LET OLD ADMIN TO LET YOU SIGNUP\nPREES A TO AGREE OR N FOR RETURN MAIN MENU\n";
        char ch;
        cin >> ch;
        if (ch == 'A') {
            Admin* admin = signinadmin();
            if (admin != nullptr)
            {
                admin = signupadmin(admin);
                asadmin(admin);
            }
        }
    }
    if (choose == '4')
    {
        Admin* admin = signinadmin();
        if (admin != nullptr)
        {
            asadmin(admin);
        }
    }
    if (choose == '5')
        return 0;
    goto MainMenu;
}

Client*createaccount()
{
    string name, phone, id, age, card, pass, checkpass;
    cout << "\t\tCREATE CLIENT ACOUNT\n\nenter 00 to back to main menu\n01 to exit\n\n";
    //get name 
    do {
        cout << "please enter your name\nName : ";
        cin.ignore();
        getline(cin, name);
        if (name == "00")
            return nullptr;
        if (name == "01")
            exit(0);
    } while (name.empty());
    //get phone
    cout << "please enter your phone number\nnum : ";
    do {
        cin >> phone;
        if (phone == "00")
            return nullptr;
        if (phone == "01")
            exit(0);
        if (phone.size() != 11)
            cout << "\nwrong phone number. please try again\nnum : ";
    } while (phone.size() != 11);
    // get id
    cout << "please enter your personal id\nid : ";
    do {
        cin >> id;
        if (id == "00")
            return nullptr;
        if (id == "01")
            exit(0);
        if (id.size() != 14)
            cout << "\nwrong personal id. please try again\nid : ";
    } while (id.size() != 14);
    //get pass
    do {
        cout << "please enter your password --- must be contain from four char or more --- \npass : ";
        cin >> pass;
        if (pass == "00")
            return nullptr;
        if (pass == "01")
            exit(0);
    } while (pass.size() < 4);
    //confirm pass
    do {
        cout << "confirm your pass \npass : ";
        cin >> checkpass;
        if (checkpass == "00")
            return nullptr;
        if (checkpass == "01")
            exit(0);
    } while (checkpass!=pass);
    //get last card num
    ifstream incard("data.txt");
    ofstream outcard("data.txt", ios::app);
    while (getline(incard, card));
    card.resize(16);
    incard.close();
    incrementstring(card);
    cout << card << " this is your account number save it\n";
    float balance;
    do {
        cout << "enter your primary balance\n";
        cin >> balance;
    } while (balance < 0);
    Client user(name,id,phone,card,pass,balance);
    outcard <<"\n"<< card << "," << name << "," << id << "," << phone << "," << pass << "," << balance << ",C";
    outcard.close();
    return &user;

}

void signin()
{
    
    ofstream outcard("data.txt", ios::app);
    cout << "\t\tSign in to your account\n\n\tEnter card id\ncard:";
    string card,temp;
    Client* current=new Client();
    bool found = 0;
    float balance, amount;
    string name, id, phone, pass, strbalance;
    //found the card num
    ifstream incard("data.txt");
    do {
        cin >> card;
        incard.open("data.txt");
        while (getline(incard, temp))
        {
            string tempcard;
            stringstream instring(temp);
            getline(instring, tempcard, ',');
            if (tempcard==card){
                getline(instring, name, ',');
                getline(instring, id, ',');
                getline(instring, phone, ',');
                getline(instring, pass, ',');
                getline(instring, strbalance, ',');
                balance = atof(strbalance.c_str());
                current = new Client(name, id, phone, card, pass, balance);
                found = 1;
                break;
            }
        }
        if (found)
            break;
        incard.close();
        cout << "card number not found in my data,please try again\ncard:";
    } while (1);
    //close the input file
    incard.close();
    //check the pass
    string forcheckpass;
    do {
        cout << "enter your password\npassword : ";
        cin >>forcheckpass;
    } while (forcheckpass != pass);
    
accountmenu:
    cout << "\n\t\t Welcome to your acount " << name << "\n\t1- edit your password\n\t2- withdraw \n\t3- deposit\n\t4- balance inqury\n\t5- acount details\n\t6- Edit account data\n\t7- delete account\n\t8- Back to mainmenu\n\t9- Exit\n";
    char choose;
    string newpass, checkpass;
    cin >> choose;
    Admin* access;
    switch (choose)
    {
    case'1':
         //get pass
        do {
            cout << "please enter your new password --- must be contain from four char or more --- \npassword : ";
            cin >> newpass;
            if (newpass == "00")
                return ;
           if (newpass == "01")
                exit(0);
        } while (newpass.size() < 4);
        //confirm pass
        do {
            cout << "confirm your pass \npassword : ";
            cin >> checkpass;
            if (checkpass == "00")
                return ;
            if (checkpass == "01")
                exit(0);
        } while (checkpass!= newpass);
        pass = newpass;
        current->setpassword(pass);
        editfile(*current);
        cout << "your password has changed correctly\n";
        break;
    case '2':
        do {
            cout << "\nEnter the amount you want to withdraw\n";
            cin >> amount;
        } while (amount < 0);
        if (amount <= balance)
        {
            cout << "\n" << amount << " has been withdrawed\n";
            balance -= amount;
            current->setbalance(balance);
        }
        else
        {
            cout << "\nsorry your balance isn\'t enoght\n";
        }
        editfile(*current);
        break;
    case'3':
        do {
            cout << "\nEnter the amount you want to deposit\n";
            cin >> amount;
        } while (amount < 0);
       
        cout << "\n" << amount << " has been deposited\n";
        balance += amount;
        current->setbalance(balance);
        editfile(*current);
        break;
    case '4':
        cout << "\nyour current balance is " << balance;
        break;
    case '5':
        cout << "\n\n\t\tname : " << name << "\n\n\t\tphone number : " << phone << "\n\n\t\tpersonal id : " << id << "\n\n\t\tcard number : " << card << "\n\n\t\tbalance : " << balance << "\n\n";
        break;
    case'6':
        cout << "YOU MUST GET ACCESS FROM ADMIN. DO YOU WANT CONTINUE?(y/n)\n";
        cin >> choose;
        if (choose == 'n')
            break;
        access = signinadmin();
        if (access) 
                editaccountdata(current);
        editfile(*current);
        name = current->getname();
        id = current->getpersonal_id();
        phone = current->getphone_num();
        cout << "\nyour data has been updated successfully\n";
        break;
    case'7':
        cout << "YOU MUST GET ACCESS FROM ADMIN. DO YOU WANT CONTINUE?(y/n)\n";
        cin >> choose;
        if (choose == 'n')
            break;
        access = signinadmin();
        if (access) {
            editfile(*current, "C", 1);
            cout << "\nyour account deleted successfully\n";
            return;
        }
        break;
    case '8':
        return;
    case'9':
        exit(0);
    default:
        cout << "undifend choose";
        break;
    }
    goto accountmenu;
}

Admin* signinadmin() {
    ifstream incard("data.txt");
    cout << "\t\tSign in to your account\n\n\tEnter card id\ncard:";
    string card, temp;
    Admin* current = new Admin();
    bool found = 0;
    float balance, amount;
    string name, id, phone, pass, strbalance,type;
    //found the card num
    do {
        incard.open("data.txt");
        cin >> card;
        while (getline(incard, temp))
        {
            if (card == "BankSystem")
            {
                found = 1;
                pass = "0000";
                current = new Admin("", "", "", "BankSystem", "0000", 0);
                break;
            }
            if (card == "00")
                return nullptr;
            if (card == "01")
                exit(0);
            string tempcard;
            stringstream instring(temp);
            getline(instring, tempcard, ',');
            if (tempcard == card) {
                getline(instring, name, ',');
                getline(instring, id, ',');
                getline(instring, phone, ',');
                getline(instring, pass, ',');
                getline(instring, strbalance, ',');
                balance = atof(strbalance.c_str());
                getline(instring, type, ',');
                if (type == "C")
                    return NULL;

                current = new Admin(name, id, phone, card, pass, balance);
                found = 1;
                break;
            }
           
        }
        if (found)
            break;
        incard.close();
        cout << "card number not found in my data,please try again\ncard:";
    } while (1);
    //check the pass
    string forcheckpass;
    do {
        cout << "enter your password\npassword : ";
        cin >> forcheckpass;
        if (forcheckpass == "00")
            return 0;
        if (forcheckpass == "01")
            exit(0);
    } while (forcheckpass != pass);
    return current;
}

Admin* signupadmin(Admin* cur) {
    string name, phone, id, age, card, pass, checkpass;
    cout << "\t\tCREATE ADMIN ACOUNT\n\nenter 00 to back to main menu\t01 to exit in any stage\n\n";
    //get name 
    do {
        cout << "please enter your name\nName : ";
        cin.ignore();
        getline(cin, name);
        if (name == "00")
            return nullptr;
        if (name == "01")
            exit(0);
    } while (name.empty());
    //get phone
    do {
        cout << "please enter your phone number\nnum : ";
        cin >> phone;
        if (phone == "00")
            return nullptr;
        if (phone == "01")
            exit(0);
    } while (phone.size() != 11);
    // get id
    do {
        cout << "please enter your personal id\nid : ";
        cin >> id;
        if (id == "00")
            return nullptr;
        if (id == "01")
            exit(0);
    } while (id.size() != 14);
    //get pass
    do {
        cout << "please enter your password --- must be contain from four char or more --- \npass : ";
        cin >> pass;
        if (pass == "00")
            return nullptr;
        if (pass == "01")
            exit(0);
    } while (pass.size() < 4);
    //confirm pass
    do {
        cout << "confirm your pass \npass : ";
        cin >> checkpass;
        if (checkpass == "00")
            return nullptr;
        if (checkpass == "01")
            exit(0);
    } while (checkpass != pass);

    //get last card num
    ifstream incard("data.txt");
    ofstream outcard("data.txt", ios::app);
    while (getline(incard, card));
    card.resize(16);

    incrementstring(card);
    cout << card << " this is your account number save it\n";
    float balance;
    do {
        cout << "enter your primary balance\n";
        cin >> balance;
    } while (balance < 0);
    delete(cur);
    cur= new Admin (name, id, phone, card, pass, balance);
    outcard << "\n" << card << "," << name << "," << id << "," << phone << "," << pass << "," << balance << ",A";
    return cur;
}

void asadmin(Admin *current) {
    ofstream outcard("data.txt", ios::app);
    string name =current->getname(),pass=current->getpassword(),phone=current->getphone_num(),id=current->getpersonal_id(),card=current->getcard_num();
    float balance = current->getbalance(), amount;
acountmenu:
    ifstream incard("data.txt");
    cout << "\n\t\t Welcome to your acount " << name << "\n\t1- edit your password\n\t2- withdraw \n\t3- deposit\n\t4- balance inqury\n\t5- acount details\n\t6- list all account\n\t7- Edit account data\n\t8- delete account\n\t9- Back to mainmenu\n\tE- Exit\n";
    char choose;
    string newpass, checkpass,temp;
    cin >> choose;

    switch (choose)
    {
    case '1':
        //get pass
        do {
            cout << "please enter your new password --- must be contain from four char or more --- \npass : ";
            cin >> newpass;
            if (newpass == "00")
                return;
            if (newpass == "01")
                exit(0);
        } while (newpass.size() < 4);
        //confirm pass
        do {
            cout << "confirm your pass \npassword : ";
            cin >> checkpass;
            if (checkpass == "00")
                return;
            if (checkpass == "01")
                exit(0);
        } while (checkpass != newpass);
        pass = newpass;
        current->setpassword(pass);
        editfile(*current,"A");
        break;
    case '2':
        do {
            cout << "\nEnter the amount you want to withdraw\n";
            cin >> amount;
        } while (amount < 0);
        if (amount <= balance)
        {
            cout << "\n" << amount << " has been withdrawed\n";
            balance -= amount;
            current->setbalance(balance);
        }
        else
        {
            cout << "\nsorry your balance isn\'t enoght\n";
        }
        editfile(*current,"A");
        break;
    case '3':
        do {
            cout << "\nEnter the amount you want to deposit\n";
            cin >> amount;
        } while (amount < 0);

        cout << "\n" << amount << " has been deposited\n";
        balance += amount;
        current->setbalance(balance);
        editfile(*current,"A");
        break;
    case '4':
        cout << "\nyour current balance is " << balance;
        break;
    case '5':
        cout << "\n\n\t\tname : " << name << "\n\n\t\tphone number : " << phone << "\n\n\t\tpersonal id : " << id << "\n\n\t\tcard number : " << card << "\n\n\t\tbalance : " << balance << "\n\n";
        break;
    case '6':
        cout << "-----------------------------------------------------------------------------------------------------------------------\n";
        cout << "Name                \tcard number     \tpersonal id   \tphone      \tbalance   \ttype\n\n";
        while (getline(incard, temp))
        {
            cout << accline(temp)<<"\n\t\t\t\t---------------------------------\n";
        }
        break;
    case'7':
        editaccountdata(current);
        editfile(*current, "A");
        name = current->getname();
        id = current->getpersonal_id();
        phone = current->getphone_num();
        cout << "\n\tyour data has been updated successfully\n";
        break;
    case '8':
        cout << "\n\tAre you sure you want to delete your account?(y/n)\n";
        cin >> choose;
        if (choose == 'y') {
            editfile(*current, "A", 1);
            cout << "\nyour account deleted successfully\n";
            return;
        }
        break;
    case '9':
        return;
    case 'E':
        exit(0);
    default:
        cout << "undifend choose";
        break;
    }
    goto acountmenu;

}

void editfile(Client newdata,string type,bool deleteaccount) {
    ifstream ifile("data.txt");
    vector<string> lines;
    string line;

    while (getline(ifile,line))
    {
        string card = line;
        if (card.substr(0, 16) == newdata.getcard_num())
        {
            if (deleteaccount)
                continue;
            string newline = newdata.getcard_num() + ',' + newdata.getname() + ',' + newdata.getpersonal_id() + ',' + newdata.getphone_num() + ',' + newdata.getpassword() + ',' + to_string(newdata.getbalance()) + ","+type;
            lines.push_back(newline);
            continue;
        }
        lines.push_back(line);
    }
    ifile.close();
    ofstream ofile("data.txt", ios::out);
    for (int i = 0, n = lines.size(); i < n; i++)
    {
        if(i!=n-1)
            ofile << lines[i] << "\n";
        else
            ofile << lines[i];
    }
    ofile.close();
}
//increament card number
void incrementstring(string& num)
{
    int size = num.size();
    for (int i = size - 1; i >= 0; i--)
    {
        num[i]++;
        if (num[i] == '9'+1)
            num[i] = '0';
        else
            break;
    }
    if (num[0] == '0')
        num = '1' + num;
}
//return line to print in list all account
string accline(string line)
{
    string card, name, id,phone,balance,type,pass;
    stringstream instring(line);
    getline(instring, card, ',');
    getline(instring, name, ',');
    getline(instring, id, ',');
    getline(instring, phone, ',');
    getline(instring, pass, ',');
    getline(instring, balance, ',');
    getline(instring, type, ',');
    for (int i = name.size(); i < 20; i++)
        name += " ";
    for (int i = balance.size(); i < 10; i++)
        balance += " ";
    line =name+'\t'+card+'\t'+id+'\t'+phone+'\t'+balance+'\t'+(type=="A"?"Admin":"Client");
    return line;
}
//to edit private data
void editaccountdata(Client* cur)
{
    cout << "\n\t\t\twhat do you want to edit\n\t1- name\n\t2- personal id\n\t3- phone number\n";
    char choose;
    cin >> choose;
    string newdata;
    switch (choose)
    {
    case'1':
        cout << "\nEnter your new name\n";
        cin >> newdata;
        cur->setname(newdata);
        break;
    case'2':
        cout << "\nEnter your new personal id\nid : ";
        do {
            cin >> newdata;
            if (newdata.size() != 14)
                cout << "\nwrong personal id. please try again\nid : ";
        } while (newdata.size() != 14);
        cur->setpersonal_id(newdata);
        break;
    case'3':
        cout << "Enter your new phone number\nnum : ";
        do {
            cin >> newdata;
            if (newdata.size() != 11)
                cout << "\nwrong phone number. please try again\nnum : ";
        } while (newdata.size() != 11);
        cur->setphone_num(newdata);
        break;
    default:
        cout << "undifend choose";
        break;
    }
}
