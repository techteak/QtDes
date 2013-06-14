#include <memory.h>

#include "qt_des.h"

/// patch:���������޸�
#define ROUND_TIME 10

//��ʼ�û���IP
int IP_Table[64] =
{
    57,49,41,33,25,17,9,1,
    59,51,43,35,27,19,11,3,
    61,53,45,37,29,21,13,5,
    63,55,47,39,31,23,15,7,
    56,48,40,32,24,16,8,0,
    58,50,42,34,26,18,10,2,
    60,52,44,36,28,20,12,4,
    62,54,46,38,30,22,14,6
};

//���ʼ�û���IP^-1
int IP_1_Table[64] =
{
    39,7,47,15,55,23,63,31,
    38,6,46,14,54,22,62,30,
    37,5,45,13,53,21,61,29,
    36,4,44,12,52,20,60,28,
    35,3,43,11,51,19,59,27,
    34,2,42,10,50,18,58,26,
    33,1,41,9,49,17,57,25,
    32,0,40,8,48,16,56,24
};

//�����û���E
int E_Table[48] =
{
    31, 0, 1, 2, 3, 4,
    3,  4, 5, 6, 7, 8,
    7,  8,9,10,11,12,
    11,12,13,14,15,16,
    15,16,17,18,19,20,
    19,20,21,22,23,24,
    23,24,25,26,27,28,
    27,28,29,30,31, 0
};

//�û�����P
int P_Table[32] =
{
    15,6,19,20,28,11,27,16,
    0,14,22,25,4,17,30,9,
    1,7,23,13,31,26,2,8,
    18,12,29,5,21,10,3,24
};

//S��
int S[8][4][16] =
{
    //S1
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    /// patch:S2��S4�û�
    //S4
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    //S3
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    /// patch:S2��S4�û�
    //S2
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    //S5
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    /// patch:S6��һ�к͵����е���
    //S6

    //    {
    //        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
    //        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
    //        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
    //        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    //    },
    {
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    //S7
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    //S8
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};

//�û�ѡ��1
int PC_1[56] =
{
    56,48,40,32,24,16,8,
    0,57,49,41,33,25,17,
    9,1,58,50,42,34,26,
    18,10,2,59,51,43,35,
    62,54,46,38,30,22,14,
    6,61,53,45,37,29,21,
    13,5,60,52,44,36,28,
    20,12,4,27,19,11,3
};

//�û�ѡ��2
int PC_2[48] =
{
    13,16,10,23,0,4,2,27,
    14,5,20,9,22,18,11,3,
    25,7,15,6,26,19,12,1,
    40,51,30,36,46,54,29,39,
    50,44,32,46,43,48,38,55,
    33,52,45,41,49,35,28,31
};


//�����ƴ����Ĺ涨
// int MOVE_TIMES[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
/// patch:����Կ��λ�޸�
int MOVE_TIMES[16] = {1,2,1,2,2,2,2,2,1,2,2,2,2,2,2,1};

//�ֽ�ת���ɶ�����
int ByteToBit(ElemType ch, ElemType bit[8])
{
    for(int i = 0; i < 8; i++)
    {
        *(bit+i) = (ch>>i)&1;
    }
    return 0;
}

//������ת�����ֽ�
int BitToByte(ElemType bit[8],ElemType *ch)
{
    for(int i = 0;i < 8; i++)
    {
        *ch |= *(bit + i)<<i;
    }
    return 0;
}

//������Ϊ8���ַ���תΪ������λ��
int Char8ToBit64(ElemType ch[8],ElemType bit[64])
{
    for(int i = 0; i < 8; i++){
        ByteToBit(*(ch+i),bit+(i<<3));
    }
    return 0;
}

//��������λ��תΪ����Ϊ8���ַ���
int Bit64ToChar8(ElemType bit[64],ElemType ch[8])
{
    memset(ch,0,8);
    for(int i = 0; i < 8; i++){
        BitToByte(bit+(i<<3),ch+i);
    }
    return 0;
}

//��������Կ
int DES_MakeSubKeys(ElemType key[64],ElemType subKeys[16][48])
{
    ElemType temp[56];
    //PC1�û�
    DES_PC1_Transform(key,temp);

    //16�ֵ���������16������Կ
    for(int i = 0; i < 16; i++)
    {
        DES_ROL(temp,MOVE_TIMES[i]);//ѭ������
        DES_PC2_Transform(temp,subKeys[i]);//PC2�û�����������Կ
    }
    return 0;
}

//��Կ�û�1
int DES_PC1_Transform(ElemType key[64], ElemType tempbts[56])
{
    for(int i = 0; i < 56; i++)
    {
        tempbts[i] = key[PC_1[i]];
    }
    return 0;
}

//��Կ�û�2
int DES_PC2_Transform(ElemType key[56], ElemType tempbts[48])
{
    for(int i = 0; i < 48; i++)
    {
        tempbts[i] = key[PC_2[i]];
    }
    return 0;
}

//ѭ������
int DES_ROL(ElemType data[56], int time)
{
    ElemType temp[56];

    //���潫Ҫѭ���ƶ����ұߵ�λ
    memcpy(temp,data,time);
    memcpy(temp+time,data+28,time);

    //ǰ28λ�ƶ�
    memcpy(data,data+time,28-time);
    memcpy(data+28-time,temp,time);

    //��28λ�ƶ�
    memcpy(data+28,data+28+time,28-time);
    memcpy(data+56-time,temp+time,time);

    return 0;
}

//IP�û�
int DES_IP_Transform(ElemType data[64])
{
    ElemType temp[64];
    for(int i = 0; i < 64; i++)
    {
        temp[i] = data[IP_Table[i]];
    }
    memcpy(data,temp,64);
    return 0;
}

//IP���û�
int DES_IP_1_Transform(ElemType data[64])
{
    ElemType temp[64];
    for(int i = 0; i < 64; i++)
    {
        temp[i] = data[IP_1_Table[i]];
    }
    memcpy(data,temp,64);
    return 0;
}

//��չ�û�
int DES_E_Transform(ElemType data[48])
{
    ElemType temp[48];
    for(int i = 0; i < 48; i++)
    {
        temp[i] = data[E_Table[i]];
    }
    memcpy(data,temp,48);
    return 0;
}

//P�û�
int DES_P_Transform(ElemType data[32])
{
    ElemType temp[32];
    for(int i = 0; i < 32; i++)
    {
        temp[i] = data[P_Table[i]];
    }
    memcpy(data,temp,32);
    return 0;
}

//���
int DES_XOR(ElemType R[48], ElemType L[48] ,int count)
{
    for(int i = 0; i < count; i++){
        R[i] ^= L[i];
    }
    return 0;
}

//S���û�
int DES_SBOX(ElemType data[48])
{
    int line,row,output;
    int cur1,cur2;
    for(int i = 0; i < 8; i++)
    {
        cur1 = i*6;
        cur2 = i<<2;

        //������S���е�������
        line = (data[cur1]<<1) + data[cur1+5];
        row = (data[cur1+1]<<3) + (data[cur1+2]<<2)
                + (data[cur1+3]<<1) + data[cur1+4];
        output = S[i][line][row];

        //��Ϊ2����
        data[cur2] = (output&0X08)>>3;
        data[cur2+1] = (output&0X04)>>2;
        data[cur2+2] = (output&0X02)>>1;
        data[cur2+3] = output&0x01;
    }
    return 0;
}

//����
int DES_Swap(ElemType left[32], ElemType right[32])
{
    ElemType temp[32];
    memcpy(temp,left,32);
    memcpy(left,right,32);
    memcpy(right,temp,32);
    return 0;
}

//���ܵ�������
int DES_EncryptBlock(ElemType plainBlock[8], ElemType subKeys[16][48], ElemType cipherBlock[8])
{
    ElemType plainBits[64];
    ElemType copyRight[48];

    Char8ToBit64(plainBlock,plainBits);
    //��ʼ�û���IP�û���
    DES_IP_Transform(plainBits);

    //16�ֵ���
    for(int i = 0; i < ROUND_TIME; i++){
        memcpy(copyRight,plainBits+32,32);
        //���Ұ벿�ֽ�����չ�û�����32λ��չ��48λ
        DES_E_Transform(copyRight);
        //���Ұ벿��������Կ����������
        DES_XOR(copyRight,subKeys[i],48);
        //���������S�У����32λ���
        DES_SBOX(copyRight);
        //P�û�
        DES_P_Transform(copyRight);
        //��������벿�����Ұ벿�ֽ������
        DES_XOR(plainBits,copyRight,32);
        if(i != ROUND_TIME - 1){
            //����������Ҳ��Ľ���
            DES_Swap(plainBits,plainBits+32);
        }
    }
    //���ʼ�û���IP^1�û���
    DES_IP_1_Transform(plainBits);
    Bit64ToChar8(plainBits,cipherBlock);
    return 0;
}

//���ܵ�������
int DES_DecryptBlock(ElemType cipherBlock[8], ElemType subKeys[16][48],ElemType plainBlock[8])
{
    ElemType cipherBits[64];
    ElemType copyRight[48];

    Char8ToBit64(cipherBlock,cipherBits);
    //��ʼ�û���IP�û���
    DES_IP_Transform(cipherBits);

    //16�ֵ���
    for(int i = ROUND_TIME - 1; i >= 0; i--)
    {
        memcpy(copyRight,cipherBits+32,32);
        //���Ұ벿�ֽ�����չ�û�����32λ��չ��48λ
        DES_E_Transform(copyRight);
        //���Ұ벿��������Կ����������
        DES_XOR(copyRight,subKeys[i],48);
        //���������S�У����32λ���
        DES_SBOX(copyRight);
        //P�û�
        DES_P_Transform(copyRight);
        //��������벿�����Ұ벿�ֽ������
        DES_XOR(cipherBits,copyRight,32);
        if(i != 0)
        {
            //����������Ҳ��Ľ���
            DES_Swap(cipherBits,cipherBits+32);
        }
    }
    //���ʼ�û���IP^1�û���
    DES_IP_1_Transform(cipherBits);
    Bit64ToChar8(cipherBits,plainBlock);
    return 0;
}

//�����ļ�
unsigned DES_Encrypt(const char *pSrc,
                     const unsigned uSrcLen,
                     const char *pKey,
                     char *pEncrypt)
{
    ElemType SrcBlock[8],EncryptBlock[8],KeyBlock[8];
    ElemType bKey[64];
    ElemType subKeys[16][48];

    //������Կ
    memcpy(KeyBlock,pKey,8);
    //����Կת��Ϊ��������
    Char8ToBit64(KeyBlock,bKey);
    //��������Կ
    DES_MakeSubKeys(bKey,subKeys);

    // ���ܺ����ĳ���
    int EncryptLen = 0;
    for (unsigned i=0; i<uSrcLen; i+=8)
    {
        // pSrc�ռ��㹻���ұ������Ὣ�����ַ���ʼ��Ϊ\0�����Լ�ʹ����8λ��Ҳ��ֱ��memcpy
        memcpy(SrcBlock, pSrc+i, 8);
        // ÿ8λ���м���,����8λ������һ�д��벹��
        DES_EncryptBlock(SrcBlock,subKeys,EncryptBlock);
        memcpy(pEncrypt+i, EncryptBlock, 8);
        EncryptLen += 8;
    }

    return EncryptLen;
}

//�����ļ�
unsigned DES_Decrypt(const char *pEncrypt,
                     const unsigned EncryptLen,
                     const char *pKey,
                     char *pDecrypt)
{
    ElemType EncryptBlock[8],DecryptBlock[8],KeyBlock[8];
    ElemType bKey[64];
    ElemType subKeys[16][48];

    //������Կ
    memcpy(KeyBlock,pKey,8);
    //����Կת��Ϊ��������
    Char8ToBit64(KeyBlock,bKey);
    //��������Կ
    DES_MakeSubKeys(bKey,subKeys);

    //���ĵ��ֽ���һ����8��������
    for (unsigned i=0; i<EncryptLen; i+=8)
    {
        // ÿ8λ���н���
        memcpy(EncryptBlock, pEncrypt+i, 8);
        DES_DecryptBlock(EncryptBlock,subKeys,DecryptBlock);
        memcpy(pDecrypt+i, DecryptBlock, 8);
    }

    return 1;
}
