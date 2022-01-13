#include <iostream>
#include <string>
using namespace std;

string ShiftHight(string A, int b) {
    for (int i = 0; i < b; i++) {
        A = A + "0";
    }
    return A;
}

string ShiftLow(string A, int b) {
    for (int i = 0; i < b; i++) {
        A = "0" + A;
    }
    return A;
}

string Plus(string A, string B) {
    if (A.size() < B.size()) {
        A = ShiftLow(A, B.size() - A.size());
    }
    else if (A.size() > B.size()) {
        B = ShiftLow(B, A.size() - B.size());
    }
    string C = "";
    for (int i = 0; i < A.size(); i++) {
        if (A[i] == B[i]) {
            C = C + "0";
        }
        else {
            C = C + "1";
        }
    }
    return C;
}

string Delet0(string A) {
    string C = "";
    int i = 0;
    while (A[i] == '0') {
        i++;
        if (i == A.size()) {
            return "0";
        }
    }
    for (int b = i; b < A.size(); b++) {
        C = C + A[b];
    }
    return C;
}


string Mod(string A, string P) {
    string C = Delet0(A);
    string temp = "";
    while (C.size() >= P.size()) {
        temp = ShiftHight(P, C.size() - P.size());
        C = Plus(C, temp);
        C = Delet0(C);
    }
    if (C.size() < 191) {
        C = ShiftLow(C,191-C.size());
    }
    return C;
}

string Multiplication(string A, string B, string P) {
    string C = "0000";
    string temp;
    for (int i = A.size() - 1; i >= 0; i--)
    {
        if (B[i] == '1') {
            temp = ShiftHight(A, A.size() - i - 1);
            C = Plus(C, temp);
        }
    }
    if (C.size() > 191) {
        C = Mod(C,P);
    }
    return C;
}

string Degree2(string A, string P) {
    string C = "";
    for (int i = 0; i < A.size(); i++) {
        C = C + A[i];
        if (i != A.size()-1) {
            C = C + "0";
        }
    }
    C = Mod(C, P);
    return C;
}

string Trase(string A, string P) {
    string C =  A;
    string temp = A;
    for (int i = 0; i < 190; i++) {
        temp = Degree2(temp, P);
        C = Plus(C, temp);
    }
    if (C[C.size()-1] == '1') {
        return "1";
    }
    else {
        return "0";
    }
}

// по схеме горнера
string Invers(string A, string P) {
    string temp = A;
    for(int i = 0; i < 189; i++) {
        temp = Degree2(temp, P);
        A = Multiplication(A, temp,P);
    }
    A = Degree2(A,P);
    return A;
}

string DegreeN(string A, string N, string P) {
    string C = "1";
    C = ShiftLow(C,190);
    for (int i = 0; i < 191; i++) {
        if (N[i] == '1') {
            C = Multiplication(C, A, P);
        }
        if (i != 190) {
            C = Degree2(C,P);
        }
    }
    return C;
}

int main()
{
    string P = "";
    for (int i = 0; i < 192; i++) {
        if (i==0 || i==9 || i==191) {
            P = "1" + P;
        }
        else {
            P = "0" + P;
        }
    }

    string X = "01010010110100110100111101111111011110000001111100001000111111101101110010111100111010111110001100001011100010011101100101111111001000010001101011001101000110010011100100010011011110111111110";
    string Y = "01110100101111000010100011011110111110000110111101111000110101100011101100010000010001111110010100011000001100100000111100100111111100011001001000011100100011101101111110010010000111001111110";
    string Z = "00011010101110101111100010101110101001111011111111001010110010100100110100010011110100110101101101000100000011100011001001100011100001010011010100010001110010001011101111001100011000110011000";

    cout <<"+ "<< Plus(X, Y) << endl;
    cout <<"* "<< Multiplication(X, Y, P) << endl;
    cout <<"mod "<< Mod(X, P) << endl;
    cout <<"^2 "<< Degree2(X, P) << endl;
    cout <<"trase "<< Trase(X, P) << endl;
    cout <<"invers "<< Invers(X, P) << endl;
    cout <<"^n"<< DegreeN(X, Z, P) << endl;



}
