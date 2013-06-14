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
    const char sSrc[1024] = "China Mobile (Shenzhen) Limited 中国移动(深圳)有限公司 2003/3/20成立";
    char sEncrypt[1024] = {0};
    char sDecrypt[1024] = {0};

    unsigned sEncryptLen = 0;

    cout << "原字符串:" << sSrc << endl;
    cout << "密钥:" << sKey << endl << endl;

    // 加密
    start = clock();
    sEncryptLen = DES_Encrypt(sSrc, strlen(sSrc), sKey, sEncrypt);
    stop = clock();

    cout << "加密耗时" << stop-start << "毫秒" << endl;
    cout << "加密后:" << sEncrypt << endl << endl;

    // 解密
    start = clock();
    DES_Decrypt(sEncrypt, sEncryptLen,  sKey, sDecrypt);
    stop = clock();

    cout << "解密耗时" << stop-start << "毫秒" << endl;
    cout << "解密后:" << sDecrypt << endl << endl;


    if (0 == strcmp (sSrc, sDecrypt))
    {
        cout << "原字符串和解密字符串相同" << endl;
    }
    else
    {
        cout << "原字符串和解密字符串不相同" << endl;
    }

    getchar();

    return 0;
}

