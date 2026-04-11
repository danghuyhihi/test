#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include <iostream>
#include <cstring>
using namespace std;

#define MAXCTHD 20
#define MAXNV 500

//==================== DATE ====================
struct Date
{
    int day;
    int month;
    int year;
};

//==================== CHI TIET HOA DON ====================
struct CT_HOADON
{
    char MAVT[11];      // toi da 10 ky tu
    int Soluong;
    long Dongia;
    int VAT;            // phan tram VAT
};

struct DSCTHD
{
    int n;
    CT_HOADON ct[MAXCTHD];
};

//==================== HOA DON ====================
struct HOADON
{
    char SoHD[21];      // toi da 20 ky tu
    Date Ngaylap;
    char Loai;          // N hoac X
    DSCTHD dscthd;
};

struct NodeHD
{
    HOADON data;
    NodeHD *next;
};

typedef NodeHD* DSHD;

//==================== NHAN VIEN ====================
struct NHANVIEN
{
    char MANV[11];      // toi da 10 ky tu
    char HO[51];
    char TEN[21];
    char PHAI[5];       // "NAM", "NU"
    DSHD dshd;
};

struct DSNHANVIEN
{
    int n;
    NHANVIEN *nv[MAXNV];
};

//==================== VAT TU ====================
struct VATTU
{
    char MAVT[11];      // toi da 10 ky tu
    char TENVT[51];
    char DVT[21];
    int SLT;            // so luong ton
};

struct NodeVT
{
    VATTU data;
    NodeVT *left;
    NodeVT *right;
};

typedef NodeVT* TREE;

#endif