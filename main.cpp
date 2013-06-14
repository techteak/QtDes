#include <iostream>
#include <string.h>
#include <time.h>

#include "qt_des.h"

using namespace std;

int main()
{
    cout << "DES Encryption" << endl;
    cout << "Author:fujingjing " << endl << endl;

    clock_t start, stop;

    char sKey[] = "fujingjing";
    const char sSrc[1024] = "China Mobile (Shenzhen) Limited �й��ƶ�(����)���޹�˾ 2003/3/20����";
    char sEncrypt[1024] = {0};
    char sDecrypt[1024] = {0};

    unsigned sEncryptLen = 0;

    cout << "ԭ�ַ���:" << sSrc << endl;
    cout << "��Կ:" << sKey << endl << endl;

    // ����
    start = clock();
    sEncryptLen = DES_Encrypt(sSrc, strlen(sSrc), sKey, sEncrypt);
    stop = clock();

    cout << "���ܺ�ʱ" << stop-start << "����" << endl;
    cout << "���ܺ�:" << sEncrypt << endl << endl;

    // ����
    start = clock();
    DES_Decrypt(sEncrypt, sEncryptLen,  sKey, sDecrypt);
    stop = clock();

    cout << "���ܺ�ʱ" << stop-start << "����" << endl;
    cout << "���ܺ�:" << sDecrypt << endl << endl;


    if (0 == strcmp (sSrc, sDecrypt))
    {
        cout << "ԭ�ַ����ͽ����ַ�����ͬ" << endl;
    }
    else
    {
        cout << "ԭ�ַ����ͽ����ַ�������ͬ" << endl;
    }

    getchar();

    return 0;
}

