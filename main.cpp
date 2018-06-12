#include <windows.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>
#include <cmath>

using namespace std;

int key, lang, key0, stroka0, d_key, d_slova, i, j, z, index1, index2, sum;
char LENG[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}; //Английский алфавит
char stroka[3700];
char result[3700];
char podobkey[10];
//char* result = new char[1];
//C:\\Users\\ars\\Desktop\\Crypto\\new1.txt

class Encryption
{
    public:
string path1 = "3500.txt"; //1000-3500

void openfile() {
ifstream fs;
//cout << "Введите путь до файла (*.txt) с исходным текстом: ";
//cin >> path;
fs.open(path1);
fs.getline(stroka, 3700); //Считываю исходный текст
fs.close();
}

void encryp() {
lang = 26;
sum = 0;
d_key = 10;
//d_slova = 100;
char key[d_key];
//char LRUS[33] = {'А', 'Б', 'В', 'Г', 'Д', 'Е', 'Ё', 'Ж', 'З', 'И', 'Й', 'К', 'Л', 'М', 'Н', 'О', 'П', 'Р', 'С', 'Т', 'У', 'Ф', 'Х', 'Ц', 'Ч', 'Ш', 'Щ', 'Ъ', 'Ы', 'Ь', 'Э', 'Ю', 'Я'}; //Русский алфавит
 //   cin.clear();
//    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    stroka0 = strlen(stroka);
char repeat_key[stroka0];
    cout <<"Введите ключ: ";
    cin.getline(key, d_key);
    key0 = strlen(key);
     //Запись строки из повторяющихся ключей
    for (i = 0; i < stroka0; i++) {
        repeat_key[i] = key[i % key0];
    }
    //Шифрование
                for (i = 0; i < stroka0; i++) {
            for (j = 0; j < lang; j++) {
               if (LENG[j] == stroka[i]) {
                    index1 = j;
                }
            }
            for (z = 0; z < lang; z++) {
                if (LENG[z] == repeat_key[i]) {
                    index2 = z;
                }
                }
        sum = (index1 + index2) % lang;
        result[i] = LENG[sum];
        sum = 0;
    }
    //Вывод
    cout <<"Зашифрованный текст: ";
    for (i = 0; i < stroka0; i++) {
        cout <<result[i];
    }
    cout <<endl;
}
};

class Vzlom {
public:

void vzlom1_index() {    //Метод индекса совпадений
int keypos;
float ins;
float mass[7];
int index;
float ivon1,ivon2;
ivon1=0;
ivon2=0;
for (keypos = 0; keypos < 8; keypos++){
    index=(stroka0/(keypos+2))+(stroka0%(keypos+2));
    for (i=0; i<26; i++) {
        for (j=0; j < stroka0; j= j+keypos+2) {
            if (LENG[i]==result[j])
                ivon1++;
        }
            ivon2 = (ivon1/index) * (ivon1/index);
            //ivon2 = (ivon1*(ivon1-1))/(index*(index-1));
            //ivon2 = round(ivon2*1000000)/1000000;
            ins = ins + ivon2;
            ivon1=0;
            ivon2=0;
        }
       mass[keypos] = ins;
       ins=0;
}
for (i=0; i<8; i++) {
        //cout << mass[i]<<" "<< endl;
    if (mass[i] > 0.066) {
        ins = i;
        break;
}
}
key = ins +2;
cout << "Длина ключа: "<< key<<endl;
}

void vzlom2_index() { //Автокорреляционный метод
    int tmp;
    float ins, total;
char diffmas[stroka0];
total = 0;

for (i=0; i<10; i++) {
    tmp = diffmas[0];
    for (j = 0; j<(stroka0-1); j++) {
    diffmas[j]= diffmas[j+1];
}
    diffmas[stroka0-1] = tmp;
    for (z=0; z<stroka0; z++) {
        if (diffmas[z] == result[z]) {
          total++;
        }
    }
    //cout << total<< " ";
    ins = (total / (stroka0 - i));
    total=0;
    //cout << ins<<" "<<endl;
    if (ins > 0.046 && ins <= 0.05) {
        key = i+1;
        break;
    }
}
cout << "Длина ключа: "<<key<<endl;
}

int nod(int a, int b) {
 long nod = 1L;
    for (long i = a; i > 0; i--) {
        if (a % i == 0 && b % i == 0) {
            nod = i;
            break;
        }
    }
    return nod;
}

void vzlom3_index() { //Метод Касиски
char arrhelp[3];
int inde, chet;
int max_here = 0;
long int massive;
for (i=0; i < (stroka0-2); i++) {
    inde = 0;
    arrhelp[0] = result[i];
    arrhelp[1] = result[i+1];
    arrhelp[2] = result[i+2];
    for (j=0; j < (stroka0-2); j++) {
        if ((arrhelp[0] == result[j]) && (arrhelp[1] == result[j+1]) && (arrhelp[2] == result[j+2])) {
            inde++;
        }
    }
    if (max_here < inde) {
        max_here = inde;
        chet=i;
    }
    if (max_here > 10 ) //Изменение числа увеличивает точность, либо уменьшает
        break;
}
int kasis[max_here];
    arrhelp[0] = result[chet];
    arrhelp[1] = result[chet+1];
    arrhelp[2] = result[chet+2];
    j=0;
    for (i=0; i<(stroka0-2); i++) {
     if ((arrhelp[0] == result[i]) && (arrhelp[1] == result[i+1]) && (arrhelp[2] == result[i+2]) && (i - chet !=0)) {
    kasis[j] =abs(i - chet);
    j++;
  }
 }
index1=max_here-1;
massive = index1 * (index1-1);
int arr1[massive];
z=0;
for (i=0; i<index1; i++) {
    for (j=0; j<index1; j++) {
            if (nod(kasis[i],kasis[j]) < 10) {
                arr1[z] = nod(kasis[i],kasis[j]);
                //cout << arr1[z]<<" ";
                z++;
            }
    }
}
int chislo[9];
for (i=0; i<9; i++) {
    chislo[i] =0;
}

key=0;
int kolik = 0;
for (i=2; i<11; i++) {
    for (j=0; j<massive; j++) {
        if (arr1[j] == i) {
            chislo[i-2]++;
        }
    }
    if (chislo[i-2] > kolik) {
        kolik=chislo[i-2];
        key = i;
    }
}
cout <<"Длина ключа: "<<key<<endl;
}

void vzlom1_key() {
int hope,maxi;
maxi=0;
int inde,ko;
int arr[key];
for (i=0; i<key; i++) {
    for (j=0; j<26; j++) {
        for (z=i; z<stroka0; z=z+key) {
            if (LENG[j]==result[z])
                hope++;
        }
        if (hope > maxi) {
            maxi = hope;
            arr[i] = j;
        }
        hope = 0;
    }
    maxi=0;
}
cout <<"Подобранный ключ: ";
for (i=0; i<key; i++) {
        ko = (26+((arr[i]-4)))%26;
        podobkey[i] = LENG[ko];
    cout << podobkey[i];
}
cout << endl;
}
};


class Decryption {
public:
void decryp () {
lang = 26;
sum = 0;
char repeat_key[stroka0];
    for (i = 0; i < stroka0; i++) {
        repeat_key[i] = podobkey[i % key];
    }
            for (i = 0; i < stroka0; i++) {
            for (j = 0; j < lang; j++) {
                if (LENG[j] == result[i]) {
                    index1 = j;
                }
            }
            for (z = 0; z < lang; z++) {
                if (LENG[z] == repeat_key[i]) {
                    index2 = z;
                }
            }
        sum = (index1 - index2 + lang) % lang;
        result[i] = LENG[sum];
        sum = 0;
    }
    //Вывод
  /*  cout <<"Результат: ";
    for (i = 0; i < stroka0; i++) {
        cout <<result[i];
    }*/
   // cout <<endl;
}

void compar() {
    int comp=0;
for (i=0; i< stroka0; i++) {
    if (stroka[i]!=result[i])
        comp++;
}
if (comp == 0) {
cout << "Исходный текст абсолютно совпадает с полученным!"<<endl;
}
else if (comp < 500) {
cout <<"В текстах есть разница в "<<comp<<" отличий!"<<endl;
}
else if (comp >=500) {
cout <<"Проблема с полученным ключем, "<<comp<<" несовпадений!" << endl;
}
}
};

int main() {
setlocale(LC_ALL, "");
int proverka;
Encryption objEnc;
Decryption objDec;
Vzlom objVz;
objEnc.openfile();
cout << "Шифрование текста..." << endl;
objEnc.encryp();
cout << "Выберите метод криптовзлома:"<<endl<<"1 - Метод индекса совпадения;"<<endl<<"2 - Метод автокорреляционный;"<<endl<<"3 - Метод Касиски;"<<endl<<"0 - выход: ";
cin >> proverka;
cout << endl;
if (proverka == 1) {
        //МЕТОД ДЛЯ БОЛЬШИХ ТЕКСТОВ, ИБО НУЖЕН БОЛЕЕ ТОЧНЫЙ ИНДЕКС СОВПАДЕНИЙ
    cout <<"МЕТОД ИНДЕКСА СОВПАДЕНИЙ"<<endl;
    cout <<"--------------------"<<endl;
    objVz.vzlom1_index();
    objVz.vzlom1_key();
    objDec.decryp();
    objDec.compar();
    cout <<"--------------------"<<endl;
}
if (proverka == 2) {
        //АВТОКОРРЕЛЯЦИОННЫЙ МЕТОД, САМЫЙ ЛУЧШИЙ ВЗЛОМ
    cout <<"МЕТОД АВТОКОРРЕЛЯЦИОННЫЙ"<<endl;
    cout <<"--------------------"<<endl;
    objVz.vzlom2_index();
    objVz.vzlom1_key();
    objDec.decryp();
    objDec.compar();
    cout <<"--------------------"<<endl;
}
if (proverka == 3) {
    //МЕТОД КАСИСКИ
    cout <<"МЕТОД КАСИСКИ(best)"<<endl;
    cout <<"--------------------"<<endl;
    objVz.vzlom3_index();
    objVz.vzlom1_key();
    objDec.decryp();
    objDec.compar();
    cout <<"--------------------"<<endl;
}
if (proverka == 0) {
    return 0;
}
}

