#include<iostream>
#include<iomanip>
#include<fstream>
#include"header_files/student.h"
#include"header_files/time.h"
using namespace std;
// Utility functions
bool check_registration_record(long key){
    string name,branch,hostel,room_no;
    long roll_no;
    int year;
    bool flag = false;
    ifstream fin("records/registered_students");
    if(fin){
        fin.seekg(0,ios::beg);
        while(fin>>name>>roll_no>>branch>>hostel>>year>>room_no){
            if(roll_no==key){
                flag = true;
                break;
            }
        }
        fin.close();
        return flag;
    }
    cout<<"Registration record not opened"<<endl;
    return false;
}
int main(){    
    int choice;
    string welcome_string {"Welcome to main-menu"};
    while(1){
        cout<<endl;
        cout<<"=================================="<<endl;
        cout<<"<- "<<welcome_string<<" ->"<<endl;
        cout<<"For registering press 1:"<<endl;
        cout<<"If done press 2:"<<endl;
        cout<<"Press 3 to exit: "<<endl;
        cin>>choice;
        if(choice==1){
            string name,branch,hostel,room_no;
            int year;
            long roll_no;
            cout<<"Enter name(for spaces use underscores): ";cin>>name;
            cout<<"Enter roll_no: ";cin>>roll_no;
            cout<<"Enter branch(for spaces use underscores): ";cin>>branch;
            cout<<"Enter hostel(for spaces use underscores): ";cin>>hostel;
            cout<<"Enter year(in numeric form): ";cin>>year;
            cout<<"Enter room_no(Use underscores for spaces): ";cin>>room_no;
            Student a(name,roll_no,hostel,branch,year,room_no);
            bool flag;
            flag = check_registration_record(roll_no);
            if(!flag){
                ofstream fout("records/registered_students",ios::app);
                if(!fout){
                    cerr<<"Error"<<endl;
                    return 1;
                }
                fout<<a;
                cout<<"=================================="<<endl;
                cout<<"Successfully registered!"<<endl;
                fout.close();
            }
            else{
                cout<<"=================================="<<endl;
                cout<<"You are already registered! "<<endl;
            }
        }
        else if(choice==2){
            int choice2;
            cout<<"=================================="<<endl;
            cout<<"1.Open entry: "<<endl;
            cout<<"2.Close entry: "<<endl;
            cout<<"3.Apply for outpass: "<<endl;
            cout<<"4.Go back to main-menu "<<endl;
            cin>>choice2;
            switch(choice2){
                case 1: {
                    long roll_no;
                    cout<<"Enter your roll_no: "; cin>>roll_no;
                    bool flag = check_registration_record(roll_no);
                    if(flag){
                        Time exit_time;
                        string room_no;
                        // cout<<"=================================="<<endl;
                        cout<<"Enter Hostel exit time (hours min, use 24 hour format): "; cin>>exit_time;
                        cout<<"Enter your room number:(Use underscore in place of spaces) "; cin>>room_no;
                        ofstream fout("records/entry",ios::app);
                        if(!fout){
                            cerr<<"Error in opening the entry file"<<endl;
                            return 1;
                        }
                        fout<<roll_no<<" "<<room_no<<" "<<exit_time<<"\n";
                        fout.close();
                        cout<<"Your entry has been made. Enjoy your time!"<<endl;
                    }
                    else{
                        cout<<"You are not registered! Please register first."<<endl;
                    }
                }
                break;
                case 2:
                case 3:
                case 4: break;
            }
        }
        else{
            break;
        }
    }
    return 0;
}