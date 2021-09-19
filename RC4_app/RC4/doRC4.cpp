
#include "pch.h"
#include "framework.h"
#include "RC4.h"
#include "RC4Dlg.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

#define N 256
// handle to main dialog
CRC4Dlg* hmDlg = NULL;
TCHAR cipher[256];
TCHAR plaintext[256];
TCHAR S[N];

// generate key
int KSA(TCHAR* key, TCHAR S[], int len) {

    int j = 0;

    for (int i = 0; i < N; i++)
        S[i] = i;

    for (int i = 0; i < N; i++) {
        j = (j + S[i] + key[i % len]) % N;

        int tmp = S[i];
        S[i] = S[j];
        S[j] = tmp;
    }

    return 0;
}
// generate ciphertext
int PRGA(TCHAR S[], TCHAR* plaintext, TCHAR* ciphertext, int len) {

    int i = 0;
    int j = 0;

    for (int n = 0; n < len; n++) {
        i = (i + 1) % N;
        j = (j + S[i]) % N;

        int tmp = S[i];
        S[i] = S[j];
        S[j] = tmp;
        int round = S[(S[i] + S[j]) % N];

        ciphertext[n] = round ^ plaintext[n];

    }

    return 0;
}

DWORD WINAPI doRC4(LPVOID lpParameter) {
    
    CString hexes[] = { L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", L"A", L"B", L"C", L"D", L"E", L"F" };
    CString output;
    CString str_key;
    CString str_plaintext;

    hmDlg = (CRC4Dlg*) lpParameter;
    hmDlg->key.GetWindowText(str_key);
    hmDlg->plaintext.GetWindowText(str_plaintext);

    int len_key = hmDlg->key.GetWindowTextLengthW();
    int len = hmDlg->plaintext.GetWindowTextLengthW();

    TCHAR wchr[256];
    TCHAR* a_key;
    a_key = str_key.GetBuffer(str_key.GetLength());
    wcsncpy_s(wchr, a_key, str_key.GetLength());

 
    TCHAR wchr2[256];
    TCHAR* a_plaintext;
    a_plaintext = str_plaintext.GetBuffer(str_plaintext.GetLength());
    wcsncpy_s(wchr2, a_plaintext, str_plaintext.GetLength());
       
    KSA(a_key, S, len_key);
    PRGA(S, a_plaintext, cipher, len);
    // loop to print hex value of cipher
    for (int i = len -1; i>= 0; i--) {
        output = output + hexes[(int)cipher[i] >> 4] + hexes[(int)cipher[i] & 0xf];
    }
    hmDlg->hex_value.SetWindowTextW(L"hex value: "+output );
    hmDlg->ciphertext.SetWindowTextW(L"text value : " + (CString) cipher);

    return 0;

}
