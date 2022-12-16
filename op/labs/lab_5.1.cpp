#include <iostream>
#include <iomanip>
#include <cstring>
#include <windows.h>
#define N 80
using namespace std;

//���� � ������
int scount(char* p) {
    int word, count = 0, i = 0;
    while (p[i] == ' ' && p[i] != '\0') {
        i++;
    }
    word = 0;
    while (p[i] != '\0') {
        if (p[i] != ' ' && word == 0) {
            word = 1;
            count++;
        }
        else if (p[i] == ' ')
            word = 0;
        i++;
    }
    return count;
}

//������� ���������� ������
void results(char* s, int i, int* arr) {
    char* pstr;
    int cntrls = 0, spaces = 0, digits = 0;
    pstr = s;
    for (; *pstr; pstr++) {
        if (isdigit(*pstr)) {
            digits++;
        }
        if (isspace(*pstr)) {
            spaces++;
        }
        if (iscntrl(*pstr)) {
            cntrls++;
        }

    }
    *(arr + 4 * i) = scount(s); //����
    *(arr + (4 * i) + 1) = digits; //����
    *(arr + (4 * i) + 2) = spaces; //��������
    *(arr + (4 * i) + 3) = cntrls; //����������� ��������
}

int main() {
    setlocale(0,"Russian");

    //�������� ���� � �������, � ������� ����� �������� ����
    HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE);

    //����� ��� ����� ������
    char buff[N] = {
      "\0"
    }, ending[N] = {
      "and"
    };

    //����������� ������ ���������� ��� ��������� ������������ �����
    char* din_str[N];
    int k = 0;

    // ���� ������
    SetConsoleTextAttribute(h, 2);
    cout << "������� ������. ������� ��������� � ����� 'and'" << endl;
    SetConsoleTextAttribute(h, 15);

    while (strcmp(ending, buff)) {

        // ���� ������ � �����
        gets_s(buff);

        if (strcmp(ending, buff) != 0) {

            // ��������� ������������ ������ ��� ������
            din_str[k] = (char*)malloc(strlen(buff) + 1);

            strcpy(din_str[k], buff);
            k += 1;
        }
    }

    // ���������� �� ���������� ���������� ����
    for (int i = 0; i < k; i++)
        for (int j = i + 1; j < k; j++)
            if (scount(din_str[i]) > scount(din_str[j])) {
                char* temp = din_str[i];
                din_str[i] = din_str[j];
                din_str[j] = temp;
            }

    // ������������ ������� �����������
    int* arr = new int[4 * k];
    for (int i = 0; i < k; i++)
        results(din_str[i], i, arr);

    // ����� ��������������� ����� c �����������
    SetConsoleTextAttribute(h, 2);
    cout << "��������������� ������ � �����������:" << endl;
    cout << "(����; ����; ��������; ����������� ��������)" << endl;
    cout << endl;
    SetConsoleTextAttribute(h, 15);

    for (int i = 0; i < k; i++) {
        cout << i + 1 << ": ";
        SetConsoleTextAttribute(h, 2);
        cout << din_str[i];
        SetConsoleTextAttribute(h, 15);

        cout << " (";
        cout << *(arr + (4 * i) + 0) << " ";
        cout << *(arr + (4 * i) + 1) << " ";
        cout << *(arr + (4 * i) + 2) << " ";
        cout << *(arr + (4 * i) + 3) << "";
        cout << ")" << endl;
    }

    system("pause");
    return 0;
}