#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
    ifstream file(filename);
    string x;
    char format[] = " %[^:]:%d %d %d";
    while(getline(file,x)){
            char z[100];
            int a,b,c;
            sscanf(x.c_str(),format,&z,&a,&b,&c);
            names.push_back(z);
            scores.push_back(a+b+c);
            grades.push_back(score2grade(a+b+c));
        }
}

void getCommand(string &command ,string &key){
    cout << "Please input your command: ";
    cin >> command;
    if (toUpperStr(command) == "GRADE" || toUpperStr(command) == "NAME"){
        cin.ignore();
        getline(cin,key);
    }
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
    int count = 0;
    cout << "---------------------------------\n";
    for(unsigned int i=0;i < names.size();i++){
        if(toUpperStr(names[i]) ==toUpperStr(key)){
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            count++;
        }
    }
    if(count == 0){
        cout << "Cannot found."<< endl;
    }
    cout << "---------------------------------\n";
}
void searchGrade(vector<string> names,vector<int> scores,vector<char> grades,string key){
    int count = 0;
    cout << "---------------------------------\n";
    for(unsigned int i=0;i < grades.size();i++){
        if(*key.c_str() == grades[i]){
            cout << names[i] << " (" << scores[i] << ")" << endl;
            count++;
        }
    }
    if(count == 0){
        cout << "Cannot found."<< endl;
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
