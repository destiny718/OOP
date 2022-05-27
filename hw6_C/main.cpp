#include<iostream>
#include<regex>
#include<cstring>

using namespace std;

void extract(string input){
    smatch sm_name,sm_password,sm_email;
    regex get_name(R"(("username"[\s]*:[\s]*")([^"]+)("))");
    regex get_password(R"(("password"[\s]*:[\s]*")([^"]+)("))");
    regex get_email(R"(("email"[\s]*:[\s]*")([^"]+)("))");
    regex_search(input,sm_name,get_name);
    regex_search(input,sm_password,get_password);
    regex_search(input,sm_email,get_email);
    regex check_name(R"(^[a-zA-Z]\w{3,14}$)");
    regex check_password(R"(^[[:alnum:]]{8,20}$)");smatch sm;
    regex check1(R"(\d+)");
    regex check2(R"([a-zA-Z]+)");
    regex check_email(R"(^[\w]+@[\w\.]+$)");
    string name=sm_name[2],password=sm_password[2],email=sm_email[2];
    bool flag_name=regex_match(name,check_name);
    bool flag_password=(regex_match(password,check_password)&&(regex_search(password,sm,check2))&&regex_search(password,sm,check1));
    bool flag_email=regex_match(email,check_email);
    //cout<<regex_search(password,sm,check2)<<regex_search(password,sm,check1);
    if(!flag_email||!flag_name||!flag_password){
        cout<<"Illegal ";
        if(!flag_email&&flag_name&&flag_password)    cout<<"email"<<endl;
        else if(flag_email&&!flag_name&&flag_password)      cout<<"username"<<endl;
        else if(flag_email&&flag_name&&!flag_password)      cout<<"password"<<endl;
        else if(!flag_email&&!flag_name&&flag_password)     cout<<"username,email"<<endl;
        else if(!flag_email&&flag_name&&!flag_password)     cout<<"password,email"<<endl;
        else if(flag_email&&!flag_name&&!flag_password)     cout<<"username,password"<<endl;
        else    cout<<"username,password,email"<<endl;
        return ;
    }
    cout<<"Successfully registered."<<endl;
    cout<<"username: ";
    cout<<name[0]<<name[1]<<name[2];
    for(int i=0;i<name.length()-3;++i)  cout<<"*";
    cout<<endl<<"password: ";
    for(int i=0;i<password.length();++i)    cout<<"*";
    cout<<endl<<"email: ";
    regex e(R"(\w)");
    cout<<regex_replace(email,e,"*")<<endl;
}

int main(){
    string str;
    getline(cin,str);
    extract(str);
    return 0;
}
