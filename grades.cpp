#include<bits/stdc++.h>
#include<iostream>
#include<string>
#include<fstream>
using namespace std;


void swap(double &a,double &b){
    double temp = a;
    a = b;
    b = temp;
}


double customRound(double num) {
    double integerPart;
    double fractionalPart = modf(num, &integerPart);

    if (fractionalPart > 0.25 && fractionalPart < 0.75) {
        return integerPart + 0.5;
    } 
    else if (fractionalPart >= 0.75) {
        return ceil(num);
    } 
    else {
        return floor(num);
    }
}

double enterGrade(double min, double max, const string &prompt) {
    double grade;
    cout << prompt;
    while (true) {
        cin >> grade;
        if (cin.fail() || grade < min || grade > max) {
            cin.clear(); // Xóa lỗi trạng thái
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bỏ qua dòng đầu vào
            cout << "Invalid value, please try again!   ";
        } else {
            break;
        }
    }
    return grade;
}

class Grade {
    double chuyencan, gk1, gk2, ythuc, ck, diemquatrinh, diemhocphan;
    string xeploai;

public:
    Grade(double cc = 0, double g1 = 0, double g2 = 0, double yt = 0, double c = 0, string x = "F", double qt = 0, double hp = 0) 
        : chuyencan(cc), gk1(g1), gk2(g2), ythuc(yt), ck(c), diemquatrinh(qt), diemhocphan(hp), xeploai(x) {}

    ~Grade() {};

    double getChuyencan() const { return chuyencan; }
    double getGk1() const { return gk1; }
    double getGk2() const { return gk2; }
    double getYthuc() const { return ythuc; }
    double getCuoiki() const { return ck; }
    double getDiemquatrinh() const { return diemquatrinh; }
    double getDiemhocphan() const { return diemhocphan; }
    string getDiemchu() const { return xeploai; }

    void set_diemquatrinh();
    void set_diemhocphan();
    void diemchu();

    friend istream &operator>>(istream &is, Grade &s);

    friend ostream &operator<<(ostream &os, Grade &s);
};

void Grade::set_diemquatrinh() {
    diemquatrinh = ((gk1 + gk2) / 3 + ythuc) * 0.6 + chuyencan * 0.4;
}

void Grade::set_diemhocphan(){
    diemhocphan = ((customRound(diemquatrinh / 0.25) * 0.25) * 0.5) + (ck * 0.5);
}
void Grade:: diemchu() {
    set_diemquatrinh();
    set_diemhocphan();
    diemhocphan = customRound(diemhocphan);
    if ((diemhocphan >= 0) && (diemhocphan <= 3.9))
        xeploai = 'F';
    else if ((diemhocphan >= 4.0) && (diemhocphan <= 4.9))
        xeploai = 'D';
    else if ((diemhocphan >= 5.0) && (diemhocphan <= 5.4))
        xeploai = "D+";
    else if ((diemhocphan >= 5.5) && (diemhocphan <= 6.4))
        xeploai = 'C';
    else if ((diemhocphan >= 6.5) && (diemhocphan <= 6.9))
        xeploai = "C+";
    else if ((diemhocphan >= 7.0) && (diemhocphan <= 7.9))
        xeploai = 'B';
    else if ((diemhocphan >= 8.0) && (diemhocphan <= 8.4))
        xeploai = "B+";
    else if ((diemhocphan >= 8.5) && (diemhocphan <= 9.4))
        xeploai = 'A';
    else if ((diemhocphan >= 9.5) && (diemhocphan <= 10))
        xeploai = "A+";
}

istream& operator>>(istream& is, Grade& s) {
    cout << "Enter Student's Grade " << endl;
    s.chuyencan = enterGrade(0, 10, "Diem Chuyen Can    : ");
    s.gk1 = enterGrade(0, 15, "Diem Giua Ki Lan 1 : ");
    s.gk2 = enterGrade(0, 15, "Diem Giua Ki Lan 2 : ");
    s.ythuc = enterGrade(0, 1, "Diem Y Thuc        : ");
    s.ck = enterGrade(0, 10, "Diem Cuoi Ki       : ");
    return is;
    }

ostream& operator<<(ostream& os, Grade& s) {
    s.set_diemquatrinh();
    s.set_diemhocphan();
    s.diemchu();
    cout << left << "|" << setw(16) << s.chuyencan
         << "|" << setw(19) << s.gk1
         << "|" << setw(19) << s.gk2
         << "|" << setw(12) << s.ythuc
         << "|" << setw(13) << s.ck
         << "|" << setw(15) << customRound(s.diemquatrinh)
         << "|" << setw(14) << customRound(s.diemhocphan)
         << "|" << setw(9) << s.xeploai << endl;
    return os;
}


class Classes{
    vector<Grade> students;

public:
    void addStudent(Grade grade, const string &filename);
    void removeStudent(int number, const string &filename);
    void display();
    void sortGrade(const string &filename);
    void displayfileclass(const string &filename);
};
void Classes::addStudent(Grade grade, const string &filename){
    students.push_back(grade);
    ofstream output;
    output.open("student_grades.csv", ios::app );
    output << grade.getChuyencan() << ","
           << grade.getGk1() << ","
           << grade.getGk2() << ","
           << grade.getYthuc() << ","
           << grade.getCuoiki() << endl;
    output.close();
}
void Classes::removeStudent(int number, const string &filename){
    if(!students.empty())
        students.clear(); // clear to sort
    ifstream file(filename);
    string line;
    getline(file, line);//skip header line

    if (file.is_open()) {    
        while (getline(file,line)){
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss,token,',')){
            tokens.push_back(token);
        }
        double cc = stod(tokens[0]);
        double g1 = stod(tokens[1]);
        double g2 = stod(tokens[2]);
        double yt = stod(tokens[3]);
        double c  = stod(tokens[4]);

        Grade g(cc, g1, g2, yt, c);
        students.push_back(g);
        }
        file.close();
    }
    if (number > 0 && number <= students.size()) {
        students.erase(students.begin() + number - 1);
        cout << "Removed successfully!" << endl;
    } else {
        cout << "Invalid student number!" << endl;
    }
}
void Classes::display(){
    if (students.empty()) {
		cout << "\n--> Class is empty." << endl;
	}
	else {
        cout << "--------------------------------------------------------------COURSE GRADE--------------------------------------------------------------" << endl;
        cout << left << "|" << setw(11) << " "
             << "|" << setw(16) << "Diem Chuyen Can"
             << "|" << setw(19) << "Diem Giua Ki Lan 1"
             << "|" << setw(19) << "Diem Giua Ki Lan 2"
             << "|" << setw(12) << "Diem Y Thuc"
             << "|" << setw(13) << "Diem Cuoi Ki"
             << "|" << setw(15) << "Diem Qua Trinh"
             << "|" << setw(14) << "Diem Hoc Phan"
             << "|" << setw(9) << "XEP LOAI" << endl;

        int i = 1;
        for(auto it = students.begin(); it != students.end();++it){
            cout << left << "|" << setw(9) << "#Student " << right << setw(2) << i;
            cout << *it;
            ++i;
        }
    }
}

void Classes::sortGrade(const string &filename) {
    if(!students.empty())
        students.clear(); // clear to sort
    ifstream file(filename);
    string line;
    getline(file, line);//skip header line

    if (file.is_open()) {    
        while (getline(file,line)){
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss,token,',')){
            tokens.push_back(token);
        }
        double cc = stod(tokens[0]);
        double g1 = stod(tokens[1]);
        double g2 = stod(tokens[2]);
        double yt = stod(tokens[3]);
        double c  = stod(tokens[4]);

        Grade g(cc, g1, g2, yt, c);
        g.set_diemquatrinh();
        g.set_diemhocphan();
        g.diemchu();
        students.push_back(g);
        }
        file.close();
    }

    stable_sort(students.begin(), students.end(), [](const Grade &a, const Grade &b)
         { return a.getDiemhocphan() > b.getDiemhocphan(); });
    cout << "Grades sorted successfully!" << endl;
}

void Classes::displayfileclass(const string &filename) {
    ifstream file(filename);
    string line;
    getline(file, line);//skip header line


    if (file.is_open()) {    
        cout << "--------------------------------------------------------------COURSE GRADE--------------------------------------------------------------" << endl;
        cout << left << "|" << setw(11) << " "
             << "|" << setw(16) << "Diem Chuyen Can"
             << "|" << setw(19) << "Diem Giua Ki Lan 1"
             << "|" << setw(19) << "Diem Giua Ki Lan 2"
             << "|" << setw(12) << "Diem Y Thuc"
             << "|" << setw(13) << "Diem Cuoi Ki"
             << "|" << setw(15) << "Diem Qua Trinh"
             << "|" << setw(14) << "Diem Hoc Phan"
             << "|" << setw(9) << "XEP LOAI" << endl;

        int i = 1;
        while (getline(file,line)){
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss,token,',')){
            tokens.push_back(token);
        }
        double cc = stod(tokens[0]);
        double g1 = stod(tokens[1]);
        double g2 = stod(tokens[2]);
        double yt = stod(tokens[3]);
        double c  = stod(tokens[4]);

        Grade g(cc, g1, g2, yt, c);
        g.set_diemquatrinh();
        g.set_diemhocphan();
        g.diemchu();

        cout << left << "|" << setw(9) << "#Student " << right << setw(2) << i;
        cout << g;
        ++i;
        }
        file.close();
    } else {
        cout << "Unable to open " << endl;
    }
    
}


int main (){
    Classes clas;
    int choice;
    system("cls");
    do { // Vòng lặp sự kiện
        cout << "\n______________MENU______________" << endl;
        cout << "    1. Add student's grade" << endl;
        cout << "    2. Remove student's grade" << endl;
        cout << "    3. Display class's grades" << endl;
        cout << "    4. Import class's file" << endl;
        cout << "    5. Sort grade" << endl;
        cout << "    6. Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;
        Grade g1;
        switch (choice) {
        case 1:
            cin >> g1;
            clas.addStudent(g1,"student_grades.csv");
            cout << g1;
            cout << "Added successfully!" << endl;
            break;
        case 2:
            int num;
            cout << "Enter number of student want to remove:  ";
            cin >> num;
            clas.removeStudent(num,"student_grades.csv");
            break;
        case 3:
            clas.display();
            break;
        case 4:
            clas.displayfileclass("student_grades.csv");
            break;
        case 5:
            clas.sortGrade("student_grades.csv");
            clas.display();
            break;
        case 6:
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
    }
    } while (choice != 6);
}

    // int n, sum = 0;
    // cin >> n;
    // vector<int> v;
    // for (int i = 0; i < n;i++){
    //     int x;
    //     cin >> x;
    //     v.push_back(x);
    //     sum += v[i];
    // }
    // cout << "BEFORE : ";
    // for(int x:v){
    //     cout << x << " ";
    // }
    // cout << "\nAFTER : ";
    // selectionsort(v, n);
    // for (int x : v)
    // {
    //     cout << x << " ";
    // }

    // cout << "\nSUM = " << sum << endl;
    // int max = *max_element(v.begin(), v.end());
    // int min = *min_element(v.begin(), v.end());
    // cout << "MAX = " << max << endl;
    // cout << "MIN = " << min << endl;
    // int remove;
    // cout << "want to remove element? ___ ";
    // cin >> remove;
    // if(remove<v.size())
    //     v.erase(v.begin() + remove - 1);
    // cout << "after remove element " << remove << " : ";
    // for(int x:v){
    //     cout << x << " ";
    // }

    // vector<int> v;
    // v.push_back(10);
    // v.push_back(99);
    // cout << v.size() << endl;
    // cout << "last element = " << v[v.size() - 1] << endl;
    // cout << "last element = " << v.back() << endl;
    // for(int x:v){
    //     cout << x << endl;
    // } //duyet bang for each

    // //duyet bang iterator
    // for (vector<int>::iterator it = v.begin(); it != v.end();++it){
    //     cout << *it << endl;
    // }

    // for (auto it = v.begin(); it != v.end();++it){
    //     cout << *it << endl;
    // }

    // vector<int> u(n);// mang n phan tu
    // vector<int> a(n,9)//mang n phan tu co cung gia tri
// void selectionsort(vector<double> &v, int n){
//     for (int i = 0; i < n;i++){
//         for (int j = i; j < n;j++){
//             if(v[i]>v[j])
//                 swap(v[i], v[j]);
//         }
//     }
// }
