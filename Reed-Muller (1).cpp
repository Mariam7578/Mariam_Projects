//© Գևորգյան Մարիամ Վաղարշակի Երևան 2022 

//Այս լուծումը մշակվել է Հայաստանի Ազգային Պոլիտեխնիկական Համալսարանում
//«Տեղեկատվության գաղտնագրային և թաքնագրային պաշտպանություն» առարկայի ընթացքում։
//Ծրագրային ապահովումը վերաբերվում է Ռիդ Մյուլերի ալգորիթմին։
//Մշակված հատվածը կիրառելու դեպքում հեղիանկի անունը նշելը պարտադիր է։

#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
using namespace std;

int factorial(int n)
{
    if (n == 0)
        return 1;
    int i = n, fact = 1;
    while (n / i != n) {
        fact = fact * i;
        i--;
    }
    return fact;
}
string DecConvertBin(int a) {
    string binNum;
    int n = a;
    if (n == 0) {
        binNum = '0';
        return binNum;
    }
    while (n != 0) {
        int reminder = n % 2;
        (reminder == 0) ? binNum = '0' + binNum : binNum = '1' + binNum;
        n = n / 2;
    }
    return binNum;
}

int main()
{
    int m, r, k, i, j;
    cout << "Input m and r :";
    cin >> m >> r;
    i = 1, k = 1;
    while (i <= r) {
        k = k + (factorial(m) / (factorial(m - i) * factorial(i)));
        i++;
    }
    int index;
    int row = k;
    int col = pow(2, m);
    bool** RM = new bool* [row];
    for (i = 0; i < row; ++i) {
        RM[i] = new bool[col];
    }
    for (j = 0; j < col; ++j) {
        RM[0][j] = 1;
    }
    int matrixNum = -1;
    for (i = col - 1; i >= 0; --i) {
        string num = DecConvertBin(++matrixNum);
        int numLength = num.size();


        int count = numLength;
        while (count < m) {
            num = '0' + num;
            count++;
        }
        bool n;
        index = 0;
        for (int h = 1; h < m + 1; ++h) {
            (num[index++] == '0') ? n = 0 : n = 1;
            RM[h][i] = n;
        }
    }
    bool res;
    int val = m + 1;
    while (val < k) {
        for (i = 1; i < m + 1 && val < k; ++i) {
            for (j = i + 1; j < m + 1 && val < k; ++j) {
                for (int g = 0; g < col; ++g) {
                    res = (RM[i][g] == 1 && RM[j][g] == 1) ? 1 : 0;
                    RM[val][g] = res;
                }
                val++;
            }
        }
    }
    cout << "-----Encryption-----\n";
    cout << "Generator matrix RM:\n";
    for (i = 0; i < row; ++i) {
        for (j = 0; j < col; ++j) {
            cout << RM[i][j] << " ";
        }
        cout << endl;
    }

    cout << "count of row: " << k << "\nInput message : ";
    string message;
    string decode;
    int* vector = new int[k];
    bool* output = new bool[k];
    for (i = 0; i < k; ++i) {
        vector[i] = -1;
    }
    for (i = 0; i < col; ++i) {
        output[i] = 0;
    }
    cin.ignore();
    getline(cin, message);
    int  count = 0;
    for (i = 0; i < k; ++i) {
        if (message[i] == '1') {
            vector[i] = i;
            count++;
        }
    }
    if (count >= 1) {
        for (i = 0; i < k; ++i) {
            if (vector[i] != -1) {
                for (j = 0; j < col; ++j) {
                    output[j] = RM[vector[i]][j] ^ output[j];

                }
        }
            }
    }
    cout << "Encrypted text:\n";
    for (i = 0; i < col; ++i) {
        cout << output[i];
    }
    if (m == 3 && r == 1) {
        cout << "\n-------Decryption------\n";
        //output[2] = 0;
        bool** X = new bool* [2];
        for (i = 0; i < 2; ++i) {
            X[i] = new bool[col];
        }
        bool* res = new bool[col];
        bool** X_ = new bool* [2];
        for (i = 0; i < 2; ++i) {
            X_[i] = new bool[col];
        }
       
        int vector[4] = { 0 };
        for (int f = 0; f < 3; ++f) {
           
            if (f == 0) {
                for (i = 0; i < 2; ++i) {
                    for (j = 0; j < col; ++j) {
                        if (i == 0) X[i][j] = RM[1][j];
                        else if (i == 1) X[i][j] = (RM[1][j] == 1) ? 0 : 1;

                    }
                }
                for (i = 0; i < 2; ++i) {
                    for (j = 0; j < col; ++j) {
                        if (i == 0) X_[i][j] = RM[2][j];
                        else if (i == 1) X_[i][j] = (RM[2][j] == 1) ? 0 : 1;

                    }
                }
            }
            else if (f == 1) {
                for (i = 0; i < 2; ++i) {
                    for (j = 0; j < col; ++j) {
                        if (i == 0) X[i][j] = RM[1][j];
                        else if (i == 1) X[i][j] = (RM[1][j] == 1) ? 0 : 1;

                    }
                }

                for (i = 0; i < 2; ++i) {
                    for (j = 0; j < col; ++j) {
                        if (i == 0) X_[i][j] = RM[3][j];
                        else if (i == 1) X_[i][j] = (RM[3][j] == 1) ? 0 : 1;

                    }
                }
            }
            else if (f == 2) {
                for (i = 0; i < 2; ++i) {
                    for (j = 0; j < col; ++j) {
                        if (i == 0) {
                            X[i][j] = RM[2][j];
                            
                        }
                        else if (i == 1) {
                            X[i][j] = (RM[2][j] == 1) ? 0 : 1;
                            
                        }

                    }
                }
                for (i = 0; i < 2; ++i) {
                    for (j = 0; j < col; ++j) {
                        if (i == 0) {
                            X_[i][j] = RM[3][j];
                           
                        }
                        else if (i == 1) {
                            X_[i][j] = (RM[3][j] == 1) ? 0 : 1;
                           
                        }

                    }
                }
            }
            index = -1;
            for (i = 0; i < 2; ++i) {
                for (j = 0; j < 2; ++j) {
                    for (int p = 0; p < col; ++p)
                    {
                        res[p] = X[i][p] & X_[j][p];
                    }

                    int coef = 0;
                    for (int g = 0; g < col; ++g) {
                        bool t = res[g] & output[g];
                        coef = coef ^ t;
                    }
                    vector[++index] = coef;
                }
            }
            int count0 = 0, count1 = 0;
            for (int h = 0; h < 4; ++h) {
                (vector[h] == 0) ? count0++ : count1++;
            }
            if (count1 >= count0) decode = '1' + decode;
            else decode = '0' + decode;
        }
        string result = "00000000";
        for (int g = 0; g < 3; ++g) {
            if (decode[g] == '1') {
                for (i = 0; i < col; ++i) {
                    {
                        result[i] = result[i] ^ RM[g + 1][i];
                    }
                }
            }
        }
     
        string out;
        for (i = 0; i < col; ++i) {
            out+= result[i] ^ output[i];
        }
        int count0 = 0, count1 = 0;
        for (i = 0; i < col; ++i) {
            if (out[i] == '1') count1++;
            else count0++;
        }
        if (count1 >= count0) decode = '1' + decode;
        else decode = '0' + decode;
        cout << "Decrypted text:\n";
        cout << decode;
    }

}

