#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


void make_file(){
    ofstream MyFile("data.txt");
    MyFile << "QQQ" << endl << 200;
    MyFile.close();
}


int main()
{
    //make_file();
    ifstream fin("data.txt");

    string name;
    int var1;
    int var2;
    int var3;

    while (fin >> name >> var1)
    {
        /* do something with name, var1 etc. */
        cout << name << var1 << endl;
    }
    fin.close();
//    ifstream inputFile("data.txt");
//    string line;
//
//    while (getline(inputFile, line))
//    {
//        istringstream ss(line);
//
//        string name;
//        int var1;
//
//        ss >> name >> var1;
//        cout << name << var1 << endl << endl;
//    }
    return 0;
}
