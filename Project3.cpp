#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>
using namespace std;


const string file = "student.dat";

enum Menu {Add = 1, Remove = 2, Display = 3, Search = 4, Results = 5, Quit = 6};

struct Student {

    char* studName; //
    int idNum;
    int testsTaken;
    int* testScores; //
    double averageScore;
};

int getNumber()
{
	ifstream fin;
	fin.open("student.dat");
	if (fin.fail())
	{
		cout<<"File error."<<endl;
		exit(1);
	}
	int count=0;
	string line;
	while(!fin.eof())
	{
		getline(fin, line);
		++count;
	}
	
	fin.close();
	return(count);
	
}

int findMin(int scores[], int size, int testsTaken){
    int min;
    min = scores[0];
    if (testsTaken < 5){
        min = 0;
    }
    else {
        for (int i = 0; i < 5; ++i){
            if (min > scores[i]){
                min = scores[i];
            }
        }
    }
    return min;
}

void addStudent(){
    Student myStud;
    string name;
    int length;
    ofstream write;
    char check;


    write.open("student.dat", fstream::app);

    if (!write.is_open()){
        cout<<"Error opening file"<<endl;
        exit(1);
    }
    
    

    cout<<"Enter student name (Last,First): "<<flush;
    cin.ignore();
    getline(cin, name);
    cout<<"Is this correct? (any key = yes, N = no):\n"<<name<<endl;
    cin>> check;

    while (tolower(check) == 'n'){
    cout<<"Enter student name (Last,First): "<<flush;
    cin.ignore();
    getline(cin, name);
    cout<<"Is this correct? (any key = yes, N = no):\n"<<name<<endl;
    cin>> check;
    }

    length = name.length();

    myStud.studName = (char*)malloc(sizeof(char) * length);

    // for loop that places each character into the character array
    for (int i = 0; i < length; ++i){
        myStud.studName[i] = name.at(i); 
    }

    cout<<"What is their student ID?"<<endl;
    cin>>myStud.idNum;
    

    cout<<"How many tests did they take?"<<endl;
    cin>>myStud.testsTaken;

    myStud.testScores = (int*)malloc(sizeof(int) * myStud.testsTaken);
    
    for (int i = 0; i < myStud.testsTaken; ++i){
        cout<< "Enter score for test #"<< i + 1<<": "<<flush;
        cin>>myStud.testScores[i];
    }
    

    write<<endl;
    write<<myStud.studName;
    write<<","<<myStud.idNum<<","<<myStud.testsTaken<<",";
    for (int i = 0; i < myStud.testsTaken; ++i){
        write<< myStud.testScores[i]<<",";
    }
    write<<endl;

    write.close();

    free(myStud.studName);
    free(myStud.testScores);
}

void removeStudent(int ID){
int usrAmt = getNumber();
Student* students; //
string namePt2, namePt1, wholeName, line, temp;
ifstream read;
ofstream write;

int* length; //
bool check = false;

students = (Student*)malloc(sizeof(Student) * usrAmt);
length = (int*)malloc(sizeof(int) * usrAmt);

read.open(file);

if (!read.is_open()){
    cout<<"Error opening the file."<<endl;
    exit(1);
}


for (int i = 0; i < usrAmt; ++i){
    students[i].testScores = new int[5]; //
}


int x = 0;
while (getline(read, line)){
    stringstream sStr(line);
    getline(sStr, namePt2, ',');

    getline(sStr, namePt1, ',');


    wholeName = namePt2 + "," + namePt1;
    length[x] = wholeName.length();
    int tempLength = wholeName.length();
    students[x].studName = (char*)malloc(sizeof(char) * tempLength);
    for (int i = 0; i < namePt2.length() + 1; ++i){
        students[x].studName[i] = wholeName.at(i);
    }
    for (int i = namePt2.length() + 1; i < tempLength; ++i){
        students[x].studName[i] = wholeName.at(i);
    }

    getline(sStr, temp, ',');
    students[x].idNum = stoi(temp);

    getline(sStr, temp, ',');
    students[x].testsTaken = stoi(temp);
    for (int i = 0; i < students[x].testsTaken; ++i){
         getline(sStr, temp, ',');
         students[x].testScores[i] = stoi(temp);
    }

    if (ID == students[x].idNum){
        check = true;
    }
    ++x;
}





if (check == true){
    write.open(file);
    if (!write.is_open()){
        cout<<"Error writing to file"<<endl;
    }
    for (int i = 0; i < usrAmt; ++i){
        if (ID == students[i].idNum){
            ++i;
            if (i == usrAmt){
            }
        }
    for (int j = 0; j < length[i]; ++j){
        write<<students[i].studName[j];
    }
    write<<","<<students[i].idNum<<","<<students[i].testsTaken<<",";
    for (int y = 0; y < students[i].testsTaken; ++y){
        write<< students[i].testScores[y]<<",";
    }
        write<<endl;
    }
    write.close();
}
else{
    cout<<"Student ID #"<<ID<<" does not match any of our records."<<endl;
}


    read.close();
    for (int i = 0; i < usrAmt; ++i){
        delete[] students[i].testScores;
        free(students[i].studName);
    }
    free(students);
    free(length);
}

void display(){
    ifstream reader;
    Student* stud;
    string name2, name1, bigName, temp, line;
    int* size;
    int amt = getNumber();
    
    stud = (Student*)malloc(sizeof(Student) * amt);
    size = (int*)malloc(sizeof(int) * amt);

    reader.open(file);
    if (!reader.is_open()){
        cout<<"Error opening the file."<<endl;
        exit(1);
    }

    for (int i = 0; i < amt; ++i){
        stud[i].testScores = new int[5]; //
    }
    
    int x = 0;
while (getline(reader, line)){
    stringstream sStr(line);
    getline(sStr, name2, ',');

    getline(sStr, name1, ',');


    bigName = name2 + "," + name1;
    size[x] = bigName.length();
    int tempLength = bigName.length();
    stud[x].studName = (char*)malloc(sizeof(char) * tempLength);
    for (int i = 0; i < name2.length() + 1; ++i){
        stud[x].studName[i] = bigName.at(i);
    }
    for (int i = name2.length() + 1; i < tempLength; ++i){
        stud[x].studName[i] = bigName.at(i);
    }

    getline(sStr, temp, ',');
    stud[x].idNum = stoi(temp);

    getline(sStr, temp, ',');
    stud[x].testsTaken = stoi(temp);
    for (int i = 0; i < stud[x].testsTaken; ++i){
        getline(sStr, temp, ',');
        stud[x].testScores[i] = stoi(temp);
    }
    ++x;
}

for (int i = 0 ; i < amt; ++i){
    
    cout<<setw(30)<<left<<stud[i].studName;
    cout<<" "<<setw(15)<<left<<stud[i].idNum;
    for (int y = 0; y < stud[i].testsTaken; ++y){
        cout<<" "<<setw(5)<<left<<stud[i].testScores[y];
    }
    cout<<endl;
    
}
reader.close();
    for (int i = 0; i < amt; ++i){
        delete[] stud[i].testScores;
        free(stud[i].studName);
    }
    free(stud);
    free(size);


}

void search(int ID){ // uses the id number to locate and display the student's data
    int usrAmt = getNumber();
Student* theStud; //
string namePt2, namePt1, wholeName, line, temp;
ifstream read;
int studNum;

int* length2; //
bool check = false;

theStud = (Student*)malloc(sizeof(Student) * usrAmt);
length2 = (int*)malloc(sizeof(int) * usrAmt);

read.open(file);

if (!read.is_open()){
    cout<<"Error opening the file."<<endl;
    exit(1);
}


for (int i = 0; i < usrAmt; ++i){
    theStud[i].testScores = new int[5]; //
}


int x = 0;
while (getline(read, line)){
    stringstream sStr(line);
    getline(sStr, namePt2, ',');

    getline(sStr, namePt1, ',');


    wholeName = namePt2 + "," + namePt1;
    length2[x] = wholeName.length();
    int tempLength = wholeName.length();
    theStud[x].studName = (char*)malloc(sizeof(char) * tempLength);
    for (int i = 0; i < namePt2.length() + 1; ++i){
        theStud[x].studName[i] = wholeName.at(i);
    }
    for (int i = namePt2.length() + 1; i < tempLength; ++i){
        theStud[x].studName[i] = wholeName.at(i);
    }

    getline(sStr, temp, ',');
    theStud[x].idNum = stoi(temp);

    getline(sStr, temp, ',');
    theStud[x].testsTaken = stoi(temp);
    for (int i = 0; i < theStud[x].testsTaken; ++i){
         getline(sStr, temp, ',');
         theStud[x].testScores[i] = stoi(temp);
    }

    if (ID == theStud[x].idNum){
        check = true;
        studNum = x;
    }
    ++x;
}


    if (check == true){
        cout<<setw(30)<<left<<theStud[studNum].studName;
        cout<<" "<<setw(15)<<left<<theStud[studNum].idNum;
        for (int y = 0; y < theStud[studNum].testsTaken; ++y){
            cout<<" "<<setw(5)<<left<<theStud[studNum].testScores[y];
        }
    cout<<endl;
    }
    else {
        cout<<"Student ID #"<<ID<<" was not found."<<endl;
    }

    read.close();
    for (int i = 0; i < usrAmt; ++i){
        delete[] theStud[i].testScores;
        free(theStud[i].studName);
    }
    free(theStud);
    free(length2);
}

void exportResults(){ // writes the averages to another file.
    ifstream input;
    ofstream output;
    Student* lastStud;
    string namel, namef, longname, temp, line;
    int* height;
    int amount = getNumber();
    int* sum;

    sum = (int*)malloc(sizeof(int) * amount);

    lastStud = (Student*)malloc(sizeof(Student) * amount);
    height = (int*)malloc(sizeof(int) * amount);

    input.open(file);
    if (!input.is_open()){
        cout<<"Error opening the file."<<endl;
        exit(1);
    }

    output.open("averages.dat");
    if (!output.is_open()){
        cout<<"Error opening the file"<<endl;
        exit(1);
    }

    for (int i = 0; i < amount; ++i){
        lastStud[i].testScores = new int[5]; //
    }
    int x = 0;
    while (getline(input, line)){
    stringstream sStr(line);
    getline(sStr, namel, ',');

    getline(sStr, namef, ',');


    longname = namel + "," + namef;
    height[x] = longname.length();
    int tempLength = longname.length();
    lastStud[x].studName = (char*)malloc(sizeof(char) * tempLength);
    for (int i = 0; i < namel.length() + 1; ++i){
        lastStud[x].studName[i] = longname.at(i);
    }
    for (int i = namel.length() + 1; i < tempLength; ++i){
        lastStud[x].studName[i] = longname.at(i);
    }

    getline(sStr, temp, ',');
    lastStud[x].idNum = stoi(temp);

    getline(sStr, temp, ',');
    lastStud[x].testsTaken = stoi(temp);
    for (int i = 0; i < lastStud[x].testsTaken; ++i){ 
        getline(sStr, temp, ',');
        lastStud[x].testScores[i] = stoi(temp);
    }
    ++x;
}

    for (int i = 0 ; i < amount; ++i){
        for (int j = 0; j < lastStud[i].testsTaken; ++j){
            sum[i] += lastStud[i].testScores[j];
        }
        int myMin = findMin(lastStud[i].testScores, amount, lastStud[i].testsTaken);
        lastStud[i].averageScore = ((sum[i] - myMin) / 4.0);
    }

    for (int i = 0; i < amount; ++i){
        output<<setw(15)<<left<<lastStud[i].idNum<<left<<":";
        output<<setprecision(1)<<fixed<<lastStud[i].averageScore<<endl;
    }


    input.close();
    output.close();

    for (int i = 0; i < amount; ++i){
        free(lastStud[i].studName);
        delete[] lastStud[i].testScores;
    }  
    free(lastStud);
    free(sum);
    free(height);

}

int main(){

    int choice;
    int lookupID;


    
    cout<<"1. Add\n"<<"2. Remove\n"<<"3. Display\n"<<"4. Search\n"<<"5. Results\n"<<"6. Quit"<<endl;
    cout<<"Please enter the appropriate number value: "<<endl;
    cin>>choice;

    while ((choice > 6) || (choice < 0)){
    cout<<"1. Add\n"<<"2. Remove\n"<<"3. Display\n"<<"4. Search\n"<<"5. Results\n"<<"6. Quit"<<endl;
    cout<<"**Invalid Entry**\n"<<"Please enter the appropriate number value: "<<endl;
    cin>> choice;
    }


    switch(static_cast<Menu>(choice)){
      
        case Add:

        addStudent();
        
        break;

        case Remove:
        cout<<"Enter student ID."<<endl;
        cin>>lookupID;

        removeStudent(lookupID);

        break;

        case Display:
        
        display();
        break;

        case Search:
        cout<<"Enter student ID"<<endl;
        cin>>lookupID;
        search(lookupID);
        break;

        case Results:
        exportResults();
        break;

        case Quit:
        cout<<"Thank you"<<endl;
        break;
       
    } 
    
    return 0;
}