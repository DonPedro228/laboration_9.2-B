#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

enum Specialnost { Computer_Science, Informatics, Mathematics_And_Economics, Physics_And_Informatics, Labor_Education };

union Grade {
    double programmingGrade;
    double numericalMethodsGrade;
    double pedagogyGrade;
};

struct Student {
    int studentNumber;
    string prizv;
    int course;
    Specialnost specialnost;
    double physicsGrade;
    double mathGrade;
    Grade thirdGrade; 
};

void Create(Student* students, const int N);
void Print(Student* students, const int N);
void BubbleSort(Student* students, const int N);
int BinSerach(Student* S, const int N, const string prizv, const Specialnost specialnost, const double grade);
int* Index_Sort(Student* students, const int N);
void PrintIndexSorted(Student* students, int* indexArray, const int N);

int main() {
    int N;
    cout << "Enter the number of students: ";
    cin >> N;

    Student* students = new Student[N];
    string prizv;
    Specialnost specialnost;
    int ispecialnist;
    double third_grade;
    int found;

    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Select an action: " << endl << endl;
        cout << " [1] - entering data from the keyboard " << endl;
        cout << " [2] - cout data in display" << endl;
        cout << " [3] - sort" << endl;
        cout << " [4] - binary search student from last name, specialnist, thirdGrade" << endl;
        cout << " [5] - index sort and cout data" << endl;
        cout << " [0] - Exit" << endl << endl;
        cout << "Input value: "; cin >> menuItem;
        cout << endl << endl << endl;

        switch (menuItem)
        {
        case 1:
            Create(students, N);
            break;
        case 2:
            Print(students, N);
            break;
        case 3:
            BubbleSort(students, N);
            Print(students, N);
            break;
        case 4:
            cout << "Input keys of search: " << endl;
            cout << "Last Name: " << endl; 
            cin >> prizv;
            cout << endl;
            cout << "Specialnost (0 - Computer_Science, 1 - Informatics, 2 - Mathematics_And_Economics, 3 - Physics_And_Informatics, 4 - Labor_Education): ";
            cin >> ispecialnist;

            cin.get(); 
            cin.sync();

            specialnost = (Specialnost)ispecialnist;

            cout << "Input third grade: " << endl;
            cin >> third_grade;
            cout << endl;
            if ((found = BinSerach(students, N, prizv, specialnost, third_grade)) != -1)
                cout << "Student was founded " << found + 1 << endl;
            else
                cout << "Student wasn't founded " << endl;
            break;
        case 5:
            cout << "Print index massive " << endl;
            PrintIndexSorted(students, Index_Sort(students, N), N);
            break;
        case 0:
            break;
        default:
            cout << "You choose fake value! " << endl;
        }
    } while (menuItem != 0);

    delete[] students;

    return 0;
}

void Create(Student* students, const int N) {
    for (int i = 0; i < N; ++i) {
        students[i].studentNumber = i + 1;

        cout << "Student #" << students[i].studentNumber << ":" << endl;
        cin.ignore();

        cout << "Last Name: ";
        getline(cin, students[i].prizv);

        cout << "Course: ";
        cin >> students[i].course;

        cout << "Specialnost (0 - Computer_Science, 1 - Informatics, 2 - Mathematics_And_Economics, 3 - Physics_And_Informatics, 4 - Labor_Education): ";
        int specValue;
        cin >> specValue;
        students[i].specialnost = static_cast<Specialnost>(specValue);

        cout << "Physics Grade: ";
        cin >> students[i].physicsGrade;

        cout << "Math Grade: ";
        cin >> students[i].mathGrade;


        switch (students[i].specialnost) {
        case Computer_Science:
            cout << "Programming Grade: ";
            cin >> students[i].thirdGrade.programmingGrade;
            break;
        case Informatics:
            cout << "Numerical Methods Grade: ";
            cin >> students[i].thirdGrade.numericalMethodsGrade;
            break;
        case Mathematics_And_Economics:
        case Physics_And_Informatics:
        case Labor_Education:
            cout << "Pedagogy Grade: ";
            cin >> students[i].thirdGrade.pedagogyGrade;
            break;
        }

        cout << "-----------------------------\n";
    }
}

void Print(Student* students, const int N) {
    cout << "=========================================================================================================================="
        << endl;
    cout << "| # | Last Name             | Course | Specialnist                | Physics | Math | Programming | Num. Meth.  | Pedagogy |"
        << endl;

    for (int i = 0; i < N; ++i) {
        cout << "| " << setw(1) << left << students[i].studentNumber << " ";
        cout << "| " << setw(21) << left << students[i].prizv << " | " << setw(6) << left << students[i].course;

        switch (students[i].specialnost) {
        case Computer_Science:
            cout << " | Computer_Science ";
            break;
        case Informatics:
            cout << " | Informatics ";
            break;
        case Mathematics_And_Economics:
            cout << " | Mathematics_And_Economics ";
            break;
        case Physics_And_Informatics:
            cout << " | Physics_And_Informatics ";
            break;
        case Labor_Education:
            cout << " | Labor_Education ";
            break;
        }

        cout << "          | " << setw(7) << right << students[i].physicsGrade << " | " << setw(4) << left << students[i].mathGrade;

        switch (students[i].specialnost) {
        case Computer_Science:
            cout << " | " << setw(11) << left << students[i].thirdGrade.programmingGrade;
            cout << " | " << setw(11) << left << "N/A";
            cout << " | " << setw(11) << left << "N/A";
            break;
        case Informatics:
            cout << " | " << setw(11) << left << "N/A";
            cout << " | " << setw(11) << left << students[i].thirdGrade.numericalMethodsGrade;
            cout << " | " << setw(11) << left << "N/A";
            break;
        case Mathematics_And_Economics:
        case Physics_And_Informatics:
        case Labor_Education:
            cout << " | " << setw(11) << left << "N/A";
            cout << " | " << setw(11) << left << "N/A";
            cout << " | " << setw(11) << left << students[i].thirdGrade.pedagogyGrade;
            break;
        }

        cout << "|   " << endl;
    }

    cout << "=========================================================================================================================="
        << endl;
    cout << endl;
}

void BubbleSort(Student* students, const int N) {
    for (int i0 = 0; i0 < N - 1; i0++) {
        for (int i1 = 0; i1 < N - i0 - 1; i1++) {
            double grade1, grade2;

           
            if (students[i1].specialnost == Computer_Science) {
                grade1 = students[i1].thirdGrade.programmingGrade;
            }
            else {
                grade1 = students[i1].thirdGrade.pedagogyGrade;  
            }

            if (students[i1 + 1].specialnost == Computer_Science) {
                grade2 = students[i1 + 1].thirdGrade.programmingGrade;
            }
            else {
                grade2 = students[i1 + 1].thirdGrade.pedagogyGrade;  
            }

            if (grade1 < grade2) {
                swap(students[i1], students[i1 + 1]);
            }

            else if (grade1 == grade2) {
                if (students[i1].specialnost > students[i1 + 1].specialnost) {
                    swap(students[i1], students[i1 + 1]);
                }
                
                else if (students[i1].specialnost == students[i1 + 1].specialnost && students[i1].prizv > students[i1 + 1].prizv) {
                    swap(students[i1], students[i1 + 1]);
                }
            }
        }
    }
}

int BinSerach(Student* S, const int N, const string prizv, const Specialnost specialnost, const double grade)
{
    int left = 0, right = N - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (S[mid].prizv == prizv &&  S[mid].specialnost == specialnost) {
            double studentGrade;
            if (S[mid].specialnost == Computer_Science) {
                studentGrade = S[mid].thirdGrade.programmingGrade;
            }
            else {
                studentGrade = S[mid].thirdGrade.pedagogyGrade;
            }

            if (studentGrade == grade) {
                return mid;
            }
            else if (studentGrade < grade) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        else if (S[mid].prizv < prizv || (S[mid].prizv == prizv && S[mid].specialnost < specialnost)) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return -1;
}

int *Index_Sort(Student* students, const int N) {
    int* indexArray = new int[N];

    for (int i = 0; i < N; ++i) {
        indexArray[i] = i;
    }

    for (int i0 = 0; i0 < N - 1; i0++) {
        for (int i1 = 0; i1 < N - i0 - 1; i1++) {
            double grade1, grade2;

            if (students[indexArray[i1]].specialnost == Computer_Science) {
                grade1 = students[indexArray[i1]].thirdGrade.programmingGrade;
            }
            else {
                grade1 = students[indexArray[i1]].thirdGrade.pedagogyGrade;
            }

            if (students[indexArray[i1 + 1]].specialnost == Computer_Science) {
                grade2 = students[indexArray[i1 + 1]].thirdGrade.programmingGrade;
            }
            else {
                grade2 = students[indexArray[i1 + 1]].thirdGrade.pedagogyGrade;
            }

            if (grade1 < grade2) {
                swap(indexArray[i1], indexArray[i1 + 1]);
            }

            else if (grade1 == grade2) {
                if (students[indexArray[i1]].specialnost > students[indexArray[i1 + 1]].specialnost) {
                    swap(indexArray[i1], indexArray[i1 + 1]);
                }

                else if (students[indexArray[i1]].specialnost == students[indexArray[i1 + 1]].specialnost &&
                    students[indexArray[i1]].prizv > students[indexArray[i1 + 1]].prizv) {
                    swap(indexArray[i1], indexArray[i1 + 1]);
                }
            }

        }
    }

    return indexArray;
}


void PrintIndexSorted(Student* students, int *indexArray, const int N) {
    cout << "=========================================================================================================================="
        << endl;
    cout << "| # | Last Name             | Course | Specialnist                | Physics | Math | Programming | Num. Meth.  | Pedagogy |"
        << endl;

    for (int i = 0; i < N; ++i) {
        cout << "| " << setw(1) << left << students[indexArray[i]].studentNumber << " ";
        cout << "| " << setw(21) << left << students[indexArray[i]].prizv << " | " << setw(6) << left << students[indexArray[i]].course;

        switch (students[indexArray[i]].specialnost) {
        case Computer_Science:
            cout << " | Computer_Science ";
            break;
        case Informatics:
            cout << " | Informatics ";
            break;
        case Mathematics_And_Economics:
            cout << " | Mathematics_And_Economics ";
            break;
        case Physics_And_Informatics:
            cout << " | Physics_And_Informatics ";
            break;
        case Labor_Education:
            cout << " | Labor_Education ";
            break;
        }

        cout << "          | " << setw(7) << right << students[indexArray[i]].physicsGrade << " | " << setw(4) << left << students[indexArray[i]].mathGrade;

        switch (students[indexArray[i]].specialnost) {
        case Computer_Science:
            cout << " | " << setw(11) << left << students[indexArray[i]].thirdGrade.programmingGrade;
            cout << " | " << setw(11) << left << "N/A";
            cout << " | " << setw(11) << left << "N/A";
            break;
        case Informatics:
            cout << " | " << setw(11) << left << "N/A";
            cout << " | " << setw(11) << left << students[indexArray[i]].thirdGrade.numericalMethodsGrade;
            cout << " | " << setw(11) << left << "N/A";
            break;
        case Mathematics_And_Economics:
        case Physics_And_Informatics:
        case Labor_Education:
            cout << " | " << setw(11) << left << "N/A";
            cout << " | " << setw(11) << left << "N/A";
            cout << " | " << setw(11) << left << students[indexArray[i]].thirdGrade.pedagogyGrade;
            break;
        }

        cout << "|   " << endl;
    }

    cout << "=========================================================================================================================="
        << endl;
    cout << endl;
}