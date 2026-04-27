#include <iostream>
#include <cstring>		
#include <iomanip>
#include <fstream>
#include <cstdlib>			//block remove VT khi da nhaapjp trong CTHD
#include <cctype>			//Khong Dung TimKiemMaVT ma van in duoc sLT, SOLUONG,....
#include <cstdio>
#include <conio.h>		
#include <windows.h>
	
using namespace std;

#define MAX_MAVT 10
#define MAX_TENVT 20
#define MAX_DVT 20
#define MAX_MANV 10
#define MAX_HO 10
#define MAX_TEN 10
#define MAX_PHAI 10
#define MAX_SOHD 20
#define MAXCTHD 20
#define MAXNV 500
#define MAXTEMP 1000

const int formX = 80; 	//o ve chitiet hoa don
const int inputX = 94; //tro nhap chi tiet hoa don
const int TB_X = 80;
const int TB_Y = 20;
const int TB_W = 60;

const int HD_FORM_X = 75;
const int HD_INPUT_X = 86;
const int HD_FORM_W = 60;
const int HD_FORM_H = 22;


struct Date {
    int day;
    int month;
    int year;
};

struct CT_HOADON {
    char MAVT[MAX_MAVT + 1];
    int Soluong;
    long Dongia;
    float VAT;
};

struct DSCTHD {
    int n;
    CT_HOADON ct[MAXCTHD];
};

struct HOADON {
    char SoHD[MAX_SOHD + 1];
    Date Ngaylap;
    char Loai;
    char MANV[MAX_MANV + 1];
    DSCTHD dscthd;
};

struct NodeHD {
    HOADON data;
    NodeHD *next;
};

typedef NodeHD* DSHD;

struct NHANVIEN {
    char MANV[MAX_MANV + 1];
    char HO[MAX_HO + 1];
    char TEN[MAX_TEN + 1];
    char PHAI[MAX_PHAI + 1];
    DSHD dshd;
};

struct DSNHANVIEN {
    int n;
    NHANVIEN *nv[MAXNV];
};

struct VATTU {
    char MAVT[MAX_MAVT + 1];
    char TENVT[MAX_TENVT + 1];
    char DVT[MAX_DVT + 1];
    int SLT;
};

struct NodeVT {
    VATTU data;
    NodeVT *left;
    NodeVT *right;
};

typedef NodeVT* TREE;

struct ITEM_HD {			//mang tam HD dslk
    DSHD hd;
    NHANVIEN *nv;
};

int TaoMangHoaDon(DSNHANVIEN ds, ITEM_HD a[]) {
    int n = 0;
    for (int i = 0; i < ds.n; i++) {
        for (DSHD p = ds.nv[i]->dshd; p != NULL; p = p->next) {
            a[n].hd = p;
            a[n].nv = ds.nv[i];
            n++;
        }
    }
    return n;
}
bool BatDauBang(const char s[], const char prefix[]) {
    int i = 0;
    while (prefix[i] != '\0') {
        if (s[i] == '\0') return false;
        if (toupper((unsigned char)s[i]) != toupper((unsigned char)prefix[i]))
            return false;
        i++;
    }
    return true;
}
int TaoMangHoaDonLoc(DSNHANVIEN ds, const char tuKhoa[], ITEM_HD a[]) {
    int n = 0;
    for (int i = 0; i < ds.n; i++) {
        for (DSHD p = ds.nv[i]->dshd; p != NULL; p = p->next) {
            if (tuKhoa[0] == '\0' || BatDauBang(ds.nv[i]->TEN, tuKhoa)) {
                a[n].hd = p;
                a[n].nv = ds.nv[i];
                n++;
            }
        }
    }
    return n;
}

void SaveVatTuToFile(TREE root, ofstream &f) {
    if (root == NULL) return;

    SaveVatTuToFile(root->left, f);
    f << root->data.MAVT << '|'
      << root->data.TENVT << '|'
      << root->data.DVT << '|'
      << root->data.SLT << endl;
    SaveVatTuToFile(root->right, f);
}
void LuuFileVatTu(TREE root) {
    ofstream f("vattu.txt");
    if (!f.is_open()) return;

    SaveVatTuToFile(root, f);
    f.close();
}


void UpperCase(char s[])
{
    int i;
    for(i = 0; s[i] != '\0'; i++)
        s[i] = toupper((unsigned char) s[i]);
}
void XoaKhoangTrangDauCuoi(char s[])
{
    while(strlen(s) > 0 && s[0] == ' ')
        strcpy(s, s + 1);

    while(strlen(s) > 0 && s[strlen(s) - 1] == ' ')
        s[strlen(s) - 1] = '\0';
}
void ChuanHoaKhoangTrang(char s[])				//
{
    int i, j;

    XoaKhoangTrangDauCuoi(s);

    i = 0;
    while(s[i] != '\0')
    {
        if(s[i] == ' ' && s[i + 1] == ' ')
        {
            for(j = i; s[j] != '\0'; j++)
                s[j] = s[j + 1];
        }
        else
            i++;
    }
}
void gotoxy(int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void clearLine(int x, int y, int width) {
    gotoxy(x, y);
    for (int i = 0; i < width; i++) cout << ' ';
}
void clearArea(int x, int y, int w, int h) {
    for (int i = 0; i < h; i++) {
        gotoxy(x, y + i);        
        for (int j = 0; j < w; j++) {
            cout << ' ';         
        }
    }
}
void VeKhungThongBao(int x, int y, int w) {
    const char *title = " Notification ";
    int titleLen = strlen(title);

    if (w < titleLen + 6) return; // khung qua nho thi bo

    // ===== dong tren =====
    gotoxy(x, y);
    cout << char(218); // goc tren trai

    cout << char(196); // 1 net ngang ben trai title
    cout << title;
    cout << char(196); // 1 net ngang ben phai title

    int daIn = 1 + 1 + titleLen + 1; 
    for (int i = daIn; i < w - 1; i++) {
        cout << char(196);
    }

    cout << char(191); // goc tren phai

    // ===== dong giua =====
    gotoxy(x, y + 1);
    cout << char(179);
    for (int i = 0; i < w - 2; i++) cout << ' ';
    cout << char(179);

    // ===== dong duoi =====
    gotoxy(x, y + 2);
    cout << char(192);
    for (int i = 0; i < w - 2; i++) cout << char(196);
    cout << char(217);
}
void XoaKhungThongBao(int x, int y, int w) {
    for (int i = 0; i < 3; i++) {
        clearLine(x, y + i, w);
    }
}
void XoaThongBaoChung() {
    for (int i = 0; i < 3; i++) {
        clearLine(TB_X, TB_Y + i, TB_W);
    }
}
void ThongBaoChung(const char *msg) {
    XoaThongBaoChung();
    VeKhungThongBao(TB_X, TB_Y, TB_W);

    clearLine(TB_X + 1, TB_Y + 1, TB_W - 2);
    gotoxy(TB_X + 2, TB_Y + 1);
    cout << msg;
}


int KiemTraMa(char s[], int max)
{
    int i;

    XoaKhoangTrangDauCuoi(s);

    if(strlen(s) == 0 || strlen(s) >= (unsigned)max)
        return false;

    for(i = 0; s[i] != '\0'; i++)
    {
        if(!(isalnum((unsigned char)s[i]) || s[i] == '-' || s[i] == '_' || s[i] == '.'))
            return false;
    }

    return true;
}	

int KiemTraMaVT(char ma[])
{
    return KiemTraMa(ma, 11);
}
int KiemTraMaNV(char ma[]){
	return KiemTraMa(ma,11);
}
bool KiemTraVatTuDaCoTrongHoaDon(DSNHANVIEN ds, const char maVT[]) {
    for (int i = 0; i < ds.n; i++) {
        for (DSHD p = ds.nv[i]->dshd; p != NULL; p = p->next) {
            for (int j = 0; j < p->data.dscthd.n; j++) {
                if (strcmp(p->data.dscthd.ct[j].MAVT, maVT) == 0)
                    return true;
            }
        }
    }
    return false;
}
int KiemTraSoHoaDon(char ma[]){
	return KiemTraMa(ma,21);
}
TREE TimVT(TREE root, const char maVT[]) {
    if (root == NULL) return NULL;

    int cmp = strcmp(maVT, root->data.MAVT);

    if (cmp == 0) return root;
    if (cmp < 0) return TimVT(root->left, maVT);
    return TimVT(root->right, maVT);
}
int KiemTraTrungMaVT(TREE root,  char maVT[])
{
    return TimVT(root, maVT) != NULL;
}
NHANVIEN* TimNhanVienTheoMa(DSNHANVIEN ds, const char ma[]) {
    for (int i = 0; i < ds.n; i++) {
        if (strcmp(ds.nv[i]->MANV, ma) == 0)
            return ds.nv[i];
    }
    return NULL;
}

int KiemTraTrungMANV(DSNHANVIEN ds, char ma[]) {
    for (int i = 0; i < ds.n; i++) {
        if (strcmp(ds.nv[i]->MANV, ma) == 0)
            return 0;
    }
    return 1;
}


int KiemTraTenVatTu(char s[])
{
    int i;

    ChuanHoaKhoangTrang(s);

    if(strlen(s) == 0)
        return false;

    for(i = 0; s[i] != '\0'; i++)
    {
        if(!(isalnum((unsigned char)s[i]) || s[i] == ' ' || s[i] == '-' || s[i] == '_'
            || s[i] == '.' || s[i] == '/' || s[i] == '(' || s[i] == ')'))
            return false;
    }

    return true;
}
void printAt(int x, int y, const char s[], int maxLen) {
    gotoxy(x, y);
    int i = 0;
    for (; i < maxLen && s[i] != '\0'; i++) {
        cout << s[i];
    }
    for (; i < maxLen; i++) {
        cout << ' ';
    }
}
int KiemTraDVT(char s[])
{
    ChuanHoaKhoangTrang(s);

    if (strlen(s) == 0)
        return false;

    int CoChu = 0;

    for (int i = 0; s[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)s[i]))
            CoChu = 1;

        if (!(isalnum((unsigned char)s[i]) || s[i] == ' ' || s[i] == '/'))
            return false;

        if (s[i] == '/')
        {
            if (i == 0) return false;                  // '/' đứng đầu
            if (s[i + 1] == '\0') return false;       // '/' đứng cuối
            if (s[i - 1] == ' ') return false;        // trước '/' là khoảng trắng
            if (s[i + 1] == ' ') return false;        // sau '/' là khoảng trắng
            if (s[i - 1] == '/') return false;        // '//' liên tiếp
            if (s[i + 1] == '/') return false;        // '//' liên tiếp
        }
    }

    if (!CoChu)
        return false;
    return true;
}


int NhapSoNguyenKhongAm() {
    char tmp[50];

    while (true) {
        cin.getline(tmp, 50);

        if (strlen(tmp) == 0) {
            cout << "Khong duoc rong. Nhap lai: ";
            continue;
        }

        bool hopLe = true;
        for (int i = 0; tmp[i] != '\0'; i++) {
            if (!isdigit((unsigned char)tmp[i])) {
                hopLe = false;
                break;
            }
        }

        if (!hopLe) {
            cout << "Chi duoc nhap so >= 0. Nhap lai: ";
            continue;
        }

        int x = atoi(tmp);

        return x;
    }
}
void VietHoaChuCaiDau(char s[]) {
    if (strlen(s) == 0) return;

    s[0] = toupper((unsigned char)s[0]);

    for (int i = 1; s[i] != '\0'; i++) {
        s[i] = tolower((unsigned char)s[i]);

        if (s[i - 1] == ' ')
            s[i] = toupper((unsigned char)s[i]);
    }
}
void ChuanHoaHoTen(char s[]) {
    VietHoaChuCaiDau(s);
}

//------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------


void XoaManHinh() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}




//------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------

void InitTree(TREE &root) {
    root = NULL;
}

void InitDSNV(DSNHANVIEN &ds) {
    ds.n = 0;
}



TREE TaoNodeVT(VATTU x) {
    TREE p = new NodeVT;
    p->data = x;
    p->left = NULL;
    p->right = NULL;
    return p;
}
NodeHD* TaoNodeHD(HOADON hd) {
    NodeHD* p = new NodeHD;
    p->data = hd;
    p->next = NULL;
    return p;
}


int ThemVTVaoCay(TREE &root, VATTU x) {
    if (root == NULL) {
        root = TaoNodeVT(x);
        return 1;
    }

    int cmp = strcmp(x.MAVT, root->data.MAVT);

    if (cmp == 0) {
        return 0; // trung ma
    }

    if (cmp < 0) return ThemVTVaoCay(root->left, x);
    return ThemVTVaoCay(root->right, x);
}
int DemHoaDon(DSHD dshd) {
    int dem = 0;
    for (DSHD p = dshd; p != NULL; p = p->next) dem++;
    return dem;
}

void SaveDSNVToFile(DSNHANVIEN ds) {
    ofstream f("dsnv.txt");
    if (!f.is_open()) return;

    f << ds.n << '\n';

    for (int i = 0; i < ds.n; i++) {
        NHANVIEN *nv = ds.nv[i];
        int soHD = DemHoaDon(nv->dshd);

        f << nv->MANV << '|'
          << nv->HO   << '|'
          << nv->TEN  << '|'
          << nv->PHAI << '|'
          << soHD << '\n';

        for (DSHD p = nv->dshd; p != NULL; p = p->next) {
            HOADON &hd = p->data;

            f << hd.SoHD << '|'
              << hd.Ngaylap.day << '|'
              << hd.Ngaylap.month << '|'
              << hd.Ngaylap.year << '|'
              << hd.Loai << '|'
              << hd.dscthd.n << '\n';

            for (int j = 0; j < hd.dscthd.n; j++) {
                CT_HOADON &ct = hd.dscthd.ct[j];

                f << ct.MAVT << '|'
                  << ct.Soluong << '|'
                  << ct.Dongia << '|'
                  << ct.VAT << '\n';
            }
        }
    }

    f.close();
}
void ChepCayRaMang(TREE root, VATTU a[], int &n) {
    if (root == NULL) return;

    ChepCayRaMang(root->left, a, n);
    a[n++] = root->data;
    
    ChepCayRaMang(root->right, a, n);
}

int SoSanhTenVT(const VATTU &a, const VATTU &b) {
    int kq = strcmp(a.TENVT, b.TENVT); 				
    if (kq != 0) return kq;

    return strcmp(a.MAVT, b.MAVT);
}

void SapXepTheoTen(VATTU a[], int n) {   //bubble sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (SoSanhTenVT(a[i], a[j]) > 0) {
                VATTU temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}
void InDanhSachVatTuTonKho(TREE root, int start) {
    VATTU a[1000];
    int n = 0;
    int pageSize = 15;
    int x = 2;
    int y = 2;

    ChepCayRaMang(root, a, n);
    SapXepTheoTen(a, n);

    // xoa vung bang ben trai
    clearArea(2, 2, 60, 22);

    // Header
    gotoxy(2, y);   cout << "Ma VT";
    gotoxy(14, y);  cout << "Ten VT";
    gotoxy(36, y);  cout << "DVT";
    gotoxy(48, y);  cout << "SLT";

    // duong ke
    gotoxy(2, y + 1);
    for (int i = 0; i < 58; i++) cout << '-';

    // neu rong
    if (n == 0) {
        gotoxy(2, y + 3);
        cout << "Danh sach vat tu rong.";

         clearLine(2, y + pageSize + 3, 58);
        gotoxy(2, y + pageSize + 3);
        cout << "Trang: 1/1";

        clearLine(2, y + pageSize + 4, 58);
        gotoxy(2, y + pageSize + 4);
        cout << "[>] Trang sau   [<] Trang truoc	[ESC] Thoat";

        clearLine(2, y + pageSize + 5, 58);
        gotoxy(2, y + pageSize + 5);
        cout << "[F2] Them VT    [F3] Sua VT   		[F4] Xoa VT";

        clearLine(2, y + pageSize + 6, 58);
        gotoxy(2, y + pageSize + 6);
        cout << "Loc TENVT: ";
        return;
    }

    // chong start vuot
    if (start < 0) start = 0;
    if (start >= n) start = (n - 1) / pageSize * pageSize;

    // Data
    for (int i = start; i < start + pageSize && i < n; i++) {
        int row = y + 2 + (i - start);

        clearLine(2, row, 58);

        printAt(2,  row, a[i].MAVT, 10);
        printAt(14, row, a[i].TENVT, 20);
        printAt(36, row, a[i].DVT,   10);

        gotoxy(48, row);
        cout << a[i].SLT << "      ";
    }

    // xoa cac dong du ben duoi neu trang moi it dong hon trang cu
    int soDongTrang = n - start;
    if (soDongTrang > pageSize) soDongTrang = pageSize;

    for (int row = y + 2 + soDongTrang; row < y + 2 + pageSize; row++) {
        clearLine(2, row, 58);
    }

    // thong tin trang
    int totalPages = (n + pageSize - 1) / pageSize;
    int currentPage = start / pageSize + 1;

    clearLine(2, y + pageSize + 3, 58);
    gotoxy(2, y + pageSize + 3);
    cout << "Trang: " << currentPage << "/" << totalPages;
    clearLine(2, y + pageSize + 4, 58);
    gotoxy(2, y + pageSize + 4);
    cout << "[>] Trang sau   [<] Trang truoc	[ESC] Thoat";
    clearLine(2, y + pageSize + 5, 58);
    gotoxy(2, y + pageSize + 5);
    cout << "[F2] Them VT    [F3] Sua VT   	[F4] Xoa VT";
    clearLine(2, y + pageSize + 6, 58);
    gotoxy(2, y + pageSize + 6);
    cout << "Loc TENVT: ";
}

void ThemHoaDonVaoCuoi(DSHD &dshd, HOADON hd) {
    NodeHD* p = TaoNodeHD(hd);
    if (dshd == NULL) {
        dshd = p;
        return;
    }

    NodeHD* q = dshd;
    while (q->next != NULL) q = q->next;
    q->next = p;
}
void LoadDSNVFromFile(DSNHANVIEN &ds) {
    ifstream f("dsnv.txt");
    if (!f.is_open()) return;

    ds.n = 0;

    int soNV;
    f >> soNV;
    f.ignore();

    for (int i = 0; i < soNV; i++) {
        NHANVIEN *nv = new NHANVIEN;
        nv->dshd = NULL;

        char line[256];
        f.getline(line, 256);

        if (strlen(line) == 0) {
            delete nv;
            break;
        }

        char *token = strtok(line, "|");
        if (token == NULL) { delete nv; break; }
        strcpy(nv->MANV, token);

        token = strtok(NULL, "|");
        if (token == NULL) { delete nv; break; }
        strcpy(nv->HO, token);

        token = strtok(NULL, "|");
        if (token == NULL) { delete nv; break; }
        strcpy(nv->TEN, token);

        token = strtok(NULL, "|");
        if (token == NULL) { delete nv; break; }
        strcpy(nv->PHAI, token);

        token = strtok(NULL, "|");
        if (token == NULL) { delete nv; break; }
        int soHD = atoi(token);

        for (int h = 0; h < soHD; h++) {
            HOADON hd;
            hd.dscthd.n = 0;
            strcpy(hd.MANV, nv->MANV);

            char lineHD[256];
            f.getline(lineHD, 256);

            char *tk = strtok(lineHD, "|");
            if (tk == NULL) break;
            strcpy(hd.SoHD, tk);

            tk = strtok(NULL, "|"); if (tk == NULL) break;
            hd.Ngaylap.day = atoi(tk);

            tk = strtok(NULL, "|"); if (tk == NULL) break;
            hd.Ngaylap.month = atoi(tk);

            tk = strtok(NULL, "|"); if (tk == NULL) break;
            hd.Ngaylap.year = atoi(tk);

            tk = strtok(NULL, "|"); if (tk == NULL) break;
            hd.Loai = tk[0];

            tk = strtok(NULL, "|"); if (tk == NULL) break;
            int soCT = atoi(tk);

            if (soCT < 0) soCT = 0;
            if (soCT > MAXCTHD) soCT = MAXCTHD;

            hd.dscthd.n = soCT;

            for (int j = 0; j < soCT; j++) {
                char lineCT[256];
                f.getline(lineCT, 256);

                char *t = strtok(lineCT, "|");
                if (t == NULL) {
                    hd.dscthd.n = j;
                    break;
                }
                strcpy(hd.dscthd.ct[j].MAVT, t);

                t = strtok(NULL, "|");
                if (t == NULL) { hd.dscthd.n = j; break; }
                hd.dscthd.ct[j].Soluong = atoi(t);

                t = strtok(NULL, "|");
                if (t == NULL) { hd.dscthd.n = j; break; }
                hd.dscthd.ct[j].Dongia = atol(t);

                t = strtok(NULL, "|");
                if (t == NULL) { hd.dscthd.n = j; break; }
                hd.dscthd.ct[j].VAT = (float)atof(t);
            }

            ThemHoaDonVaoCuoi(nv->dshd, hd);
        }

        ds.nv[ds.n++] = nv;
    }

    f.close();
}

void LoadVatTuFromFile(TREE &root) {
    ifstream f("vattu.txt");
    if (!f.is_open()) return;

    VATTU x;
    char line[200];

    while (f.getline(line, 200)) {
        char *p = strtok(line, "|");
        if (p == NULL) continue;
        strcpy(x.MAVT, p);

        p = strtok(NULL, "|");
        if (p == NULL) continue;
        strcpy(x.TENVT, p);

        p = strtok(NULL, "|");
        if (p == NULL) continue;
        strcpy(x.DVT, p);

        p = strtok(NULL, "|");
        if (p == NULL) continue;
        x.SLT = atoi(p);

        ThemVTVaoCay(root, x);
    }

    f.close();
}




bool NhapThongTinVT(TREE root, VATTU &x) {
    char c;
    int len;

    int xMa  = 76, yMa  = 3;
    int xTen = 76, yTen = 5;
    int xDVT = 76, yDVT = 7;
    int xSLT = 76, ySLT = 9;
	
	gotoxy(65, 3);  cout << "| Ma VT : [__________] |";
	gotoxy(65, 5);  cout << "| Ten VT: [____________________] |";
	gotoxy(65, 7);  cout << "| DVT   : [__________] |";
	gotoxy(65, 9);  cout << "| SLT   : [__________] |";
	
	gotoxy(65, 15); cout << "ENTER: sang o tiep theo";
	gotoxy(65, 16); cout << "ESC  : thoat";
    // xoa vung thong bao ben phai
    clearLine(65, 18, 45);

    // ===================== NHAP MA VT =====================
    while (true) {
        len = 0;
        x.MAVT[0] = '\0';

        clearLine(xMa, yMa, 10);
        gotoxy(xMa, yMa);

        while (true) {
            c = getch();

            if (c == 27) { // ESC
                clearArea(65,3,45,16);
                XoaThongBaoChung();
                return false;
            }
            else if (c == 13) { // ENTER
                x.MAVT[len] = '\0';

                if (len == 0) {
                	ThongBaoChung("Ma vat tu khong duoc rong.");
                    break;
                }

                if (!KiemTraMaVT(x.MAVT)) {
                    ThongBaoChung("Ma vat tu khong hop le.");
                    break;
                }

                UpperCase(x.MAVT);

                if (KiemTraTrungMaVT(root, x.MAVT)) {
                	ThongBaoChung("Ma da ton tai.");
                    break;
                }

                clearLine(65, 18, 45);
                goto NHAP_TENVT;
            }
            else if (c == 8) { // BACKSPACE
                if (len > 0) {
                    len--;
                    x.MAVT[len] = '\0';
                    gotoxy(xMa + len, yMa);
                    cout << ' ';
                    gotoxy(xMa + len, yMa);
                }
            }
            else if (isalnum((unsigned char)c)) {
                if (len < MAX_MAVT) {
                    c = toupper((unsigned char)c);
                    x.MAVT[len++] = c;
                    x.MAVT[len] = '\0';
                    gotoxy(xMa + len - 1, yMa);
                    cout << c;
                }
            }
        }
    }

NHAP_TENVT:
    // ===================== NHAP TEN VT =====================
    while (true) {
        len = 0;
        x.TENVT[0] = '\0';

        clearLine(xTen, yTen, 20);
        gotoxy(xTen, yTen);

        while (true) {
            c = getch();

            if (c == 27) { // ESC
            	XoaThongBaoChung();
                return false;
            }
            else if (c == 13) { // ENTER
                x.TENVT[len] = '\0';

                XoaKhoangTrangDauCuoi(x.TENVT);
                ChuanHoaKhoangTrang(x.TENVT);
                VietHoaChuCaiDau(x.TENVT);

                if (strlen(x.TENVT) == 0) {
                	ThongBaoChung("Ten vat tu khong duoc rong.");
                    break;
                }

                if (!KiemTraTenVatTu(x.TENVT)) {
                	ThongBaoChung("Ten vat tu khong hop le.");
                    break;
                }

                clearLine(65, 18, 45);
                goto NHAP_DVT;
            }
            else if (c == 8) { // BACKSPACE
                if (len > 0) {
                    len--;
                    x.TENVT[len] = '\0';
                    gotoxy(xTen + len, yTen);
                    cout << ' ';
                    gotoxy(xTen + len, yTen);
                }
            }
            else if (isprint((unsigned char)c)) {
                if (len < MAX_TENVT) {
                    if (isalnum((unsigned char)c) || c == ' ') {
                        if (len == 0 && c == ' ')
                            continue; // chan khoang trang dau

                        if (len > 0 && x.TENVT[len - 1] == ' ' && c == ' ')
                            continue; // chan 2 khoang trang lien tiep

                        x.TENVT[len++] = c;
                        x.TENVT[len] = '\0';
                        gotoxy(xTen + len - 1, yTen);
                        cout << c;
                    }
                }
            }
        }
    }

NHAP_DVT:
    // ===================== NHAP DVT =====================
    while (true) {
        len = 0;
        x.DVT[0] = '\0';

        clearLine(xDVT, yDVT, 10);
        gotoxy(xDVT, yDVT);

        while (true) {
            c = getch();

            if (c == 27) { // ESC
            	ThongBaoChung("Da huy nhap vat tu.");
            	XoaThongBaoChung();
                return false;
            }
            else if (c == 13) { // ENTER
                x.DVT[len] = '\0';

                XoaKhoangTrangDauCuoi(x.DVT);
                ChuanHoaKhoangTrang(x.DVT);

                if (strlen(x.DVT) == 0) {
                	ThongBaoChung("Don vi tinh khong duoc rong.");
                    break;
                }

                if (!KiemTraDVT(x.DVT)) {
                	ThongBaoChung( "Don vi tinh khong hop le.");
                    break;
                }

                clearLine(65, 18, 45);
                goto NHAP_SLT;
            }
            else if (c == 8) { // BACKSPACE
                if (len > 0) {
                    len--;
                    x.DVT[len] = '\0';
                    gotoxy(xDVT + len, yDVT);
                    cout << ' ';
                    gotoxy(xDVT + len, yDVT);
                }
            }
            else if (isprint((unsigned char)c)) {
                if (len < MAX_DVT) {
                    if (isalnum((unsigned char)c) || c == ' ' || c == '/') {
                        if (len == 0 && c == ' ')
                            continue;

                        if (len > 0 && x.DVT[len - 1] == ' ' && c == ' ')
                            continue;

                        x.DVT[len++] = c;
                        x.DVT[len] = '\0';
                        gotoxy(xDVT + len - 1, yDVT);
                        cout << c;
                    }
                }
            }
        }
    }

NHAP_SLT:
    // ===================== NHAP SLT =====================
    while (true) {
        len = 0;
    	int start=0;
        char sSLT[20];
        sSLT[0] = '\0';

        clearLine(xSLT, ySLT, 10);
        gotoxy(xSLT, ySLT);

        while (true) {
            c = getch();

            if (c == 27) { // ESC
                ThongBaoChung("Da huy nhap vat tu.");
                XoaThongBaoChung();
                return false;
            }
            else if (c == 13) { // ENTER
                sSLT[len] = '\0';

                if (len == 0) {
                	ThongBaoChung("So luong ton khong duoc rong.");
                    break;
                }

                x.SLT = atoi(sSLT);
                ThongBaoChung("Nhap vat tu thanh cong.");
                return true;
            }
            
            else if (c == 8) { // BACKSPACE
                if (len > 0) {
                    len--;
                    sSLT[len] = '\0';
                    gotoxy(xSLT + len, ySLT);
                    cout << ' ';
                    gotoxy(xSLT + len, ySLT);
                }
            }
            else if (isdigit((unsigned char)c)) {
                if (len < 18) {
                    sSLT[len++] = c;
                    sSLT[len] = '\0';
                    gotoxy(xSLT + len - 1, ySLT);
                    cout << c;
                }
            }
        }
    }
}




void XoaVungSuaVT() {
    clearArea(65, 1, 55, 22);
}
//
void SuaVT(TREE root) {
	int start =0;
    char c;
    char maVT[MAX_MAVT + 1];
    int len;
	if (root == NULL) {
		ThongBaoChung("danh sach rong, bam ECS de qua lai nhap VT!");
        c = getch();
        if(c==27){
        	clearLine(65,18,50);
        	XoaThongBaoChung();
        	return;
		}
    }

    TREE p = NULL;

    int xMa  = 76, yMa  = 3;
    int xTen = 76, yTen = 5;
    int xDVT = 76, yDVT = 7;
    int xSLT = 76, ySLT = 9;

TIM_VAT_TU:	
    XoaVungSuaVT();
	
    ThongBaoChung( "Nhap ma VT muon sua (ESC de thoat):");

    gotoxy(65, 3);
    cout << "| Ma VT : [__________] |";

    clearLine(xMa, yMa, 10);
    gotoxy(xMa, yMa);

    len = 0;
    maVT[0] = '\0';

    while (true) {
        c = getch();

        if (c == 27) { // ESC
            XoaVungSuaVT();
            XoaThongBaoChung();
            return;
        }
        else if (c == 13) { // ENTER
            maVT[len] = '\0';
            XoaKhoangTrangDauCuoi(maVT);
            UpperCase(maVT);

            if (strlen(maVT) == 0) {
            	ThongBaoChung("Ma vat tu khong duoc rong.");
                clearLine(xMa, yMa, 10);
                gotoxy(xMa, yMa);
                len = 0;
                maVT[0] = '\0';
                continue;
            }

            if (!KiemTraMaVT(maVT)) {
            	ThongBaoChung("Ma vat tu khong hop le.");
                clearLine(xMa, yMa, 10);
                gotoxy(xMa, yMa);
                len = 0;
                maVT[0] = '\0';
                continue;
            }

            p = TimVT(root, maVT);
            if (p == NULL) {
            	ThongBaoChung("Khong tim thay vat tu.");
                clearLine(xMa, yMa, 10);
                gotoxy(xMa, yMa);
                len = 0;
                maVT[0] = '\0';
                continue;
            }

            break;
        }
        else if (c == 8) { // BACKSPACE
            if (len > 0) {
                len--;
                maVT[len] = '\0';
                gotoxy(xMa + len, yMa);
                cout << ' ';
                gotoxy(xMa + len, yMa);
            }
        }
        else if (isalnum((unsigned char)c)) {
            if (len < MAX_MAVT) {
                c = toupper((unsigned char)c);
                maVT[len++] = c;
                maVT[len] = '\0';
                gotoxy(xMa + len - 1, yMa);
                cout << c;
            }
        }
    }

    // Tim thay -> hien day du thong tin
MENU_SUA:
    XoaVungSuaVT();
	XoaThongBaoChung();
    gotoxy(65, 1);
    cout << "Thong tin vat tu can sua:";

    gotoxy(65, 3);  cout << "| Ma VT : [__________] |";
    gotoxy(65, 5);  cout << "| Ten VT: [____________________] |";
    gotoxy(65, 7);  cout << "| DVT   : [__________] |";
    gotoxy(65, 9);  cout << "| SLT   : [__________] |";

    clearLine(xMa,  yMa,  10);
    clearLine(xTen, yTen, 20);
    clearLine(xDVT, yDVT, 10);
    clearLine(xSLT, ySLT, 10);

    gotoxy(xMa,  yMa);  cout << p->data.MAVT;
    gotoxy(xTen, yTen); cout << p->data.TENVT;
    gotoxy(xDVT, yDVT); cout << p->data.DVT;
    gotoxy(xSLT, ySLT); cout << p->data.SLT;

    gotoxy(65, 12); cout << "1. Sua Ten VT";
    gotoxy(65, 13); cout << "2. Sua DVT";
    gotoxy(65, 14); cout << "ESC: Thoat";
    gotoxy(65, 15); cout << "Chon: ";

    while (true) {
        c = getch();

        if (c == 27) { // ESC
            XoaVungSuaVT();
            XoaThongBaoChung();
            return;
        }
        else if (c == '1') {
            char tenMoi[MAX_TENVT + 1];
            len = 0;
            tenMoi[0] = '\0';
			ThongBaoChung("Nhap Ten VT moi, ENTER de luu, ESC de huy");


            clearLine(xTen, yTen, 20);
            gotoxy(xTen, yTen);


            while (true) {
                c = getch();

                if (c == 27) { // ESC
                    clearLine(xTen, yTen, 20);
                    gotoxy(xTen, yTen);
                    cout << p->data.TENVT;

                    clearLine(65, 17, 50);
                    XoaThongBaoChung();
                    goto MENU_SUA;
                }
                else if (c == 13) { // ENTER
                    tenMoi[len] = '\0';

                    XoaKhoangTrangDauCuoi(tenMoi);
                    ChuanHoaKhoangTrang(tenMoi);
                    VietHoaChuCaiDau(tenMoi);

                    if (strlen(tenMoi) == 0) {
                    	ThongBaoChung("Ten vat tu khong duoc rong.");
                        clearLine(xTen, yTen, 20);
                        gotoxy(xTen, yTen);
                        len = 0;
                        tenMoi[0] = '\0';
                        
                        continue;
                    }

                    if (!KiemTraTenVatTu(tenMoi)) {
                    	ThongBaoChung("Ten vat tu khong hop le.");
                        clearLine(xTen, yTen, 20);
                        gotoxy(xTen, yTen);
                        len = 0;
                        tenMoi[0] = '\0';
                        continue;
                    }

                    strcpy(p->data.TENVT, tenMoi);

                    clearLine(xTen, yTen, 20);
                    gotoxy(xTen, yTen);
                    cout << p->data.TENVT;
                    
                    ThongBaoChung("Da cap nhat Ten VT.");
                    InDanhSachVatTuTonKho(root,start);
                    goto MENU_SUA;
                }
                else if (c == 8) { // BACKSPACE
                    if (len > 0) {
                        len--;
                        tenMoi[len] = '\0';
                        gotoxy(xTen + len, yTen);
                        cout << ' ';
                        gotoxy(xTen + len, yTen);
                    }
                }
                else if (isprint((unsigned char)c)) {
                    if (len < MAX_TENVT) {
                        if (isalnum((unsigned char)c) || c == ' ' || c == '-' || c == '_' || c == '.' || c == '/' || c == '(' || c == ')') {
                            if (len == 0 && c == ' ')
                                continue;
                            if (len > 0 && tenMoi[len - 1] == ' ' && c == ' ')
                                continue;

                            tenMoi[len++] = c;
                            tenMoi[len] = '\0';
                            gotoxy(xTen + len - 1, yTen);
                            cout << c;
                        }
                    }
                }
            }
        }
        else if (c == '2') {
            char dvtMoi[MAX_DVT + 1];
            len = 0;
            dvtMoi[0] = '\0';
			
			ThongBaoChung("Nhap DVT moi, ENTER de luu, ESC de huy");
            clearLine(xDVT, yDVT, 10);
            gotoxy(xDVT, yDVT);

            while (true) {
                c = getch();

                if (c == 27) { // ESC
                    clearLine(xDVT, yDVT, 10);
                    gotoxy(xDVT, yDVT);
                    cout << p->data.DVT;
					XoaThongBaoChung();
                    clearLine(65, 17, 50);
                    goto MENU_SUA;
                }
                else if (c == 13) { // ENTER
                    dvtMoi[len] = '\0';

                    XoaKhoangTrangDauCuoi(dvtMoi);
                    ChuanHoaKhoangTrang(dvtMoi);

                    if (strlen(dvtMoi) == 0) {
                    	ThongBaoChung("Don vi tinh khong duoc rong.");
                        clearLine(xDVT, yDVT, 10);
                        gotoxy(xDVT, yDVT);
                        len = 0;
                        dvtMoi[0] = '\0';
                        continue;
                    }

                    if (!KiemTraDVT(dvtMoi)) {
                    	ThongBaoChung("Don vi tinh khong hop le.");
                        clearLine(xDVT, yDVT, 10);
                        gotoxy(xDVT, yDVT);
                        len = 0;
                        dvtMoi[0] = '\0';
                        continue;
                    }

                    strcpy(p->data.DVT, dvtMoi);

                    clearLine(xDVT, yDVT, 10);
                    gotoxy(xDVT, yDVT);
                    cout << p->data.DVT;

					ThongBaoChung("Da cap nhat DVT.");
                    InDanhSachVatTuTonKho(root,start);

                    goto MENU_SUA;
                }
                else if (c == 8) { // BACKSPACE
                    if (len > 0) {
                        len--;
                        dvtMoi[len] = '\0';
                        gotoxy(xDVT + len, yDVT);
                        cout << ' ';
                        gotoxy(xDVT + len, yDVT);
                    }
                }
                else if (isprint((unsigned char)c)) {
                    if (len < MAX_DVT) {
                        if (isalnum((unsigned char)c) || c == ' ' || c == '/') {
                            if (len == 0 && c == ' ')
                                continue;
                            if (len > 0 && dvtMoi[len - 1] == ' ' && c == ' ')
                                continue;

                            dvtMoi[len++] = c;
                            dvtMoi[len] = '\0';
                            gotoxy(xDVT + len - 1, yDVT);
                            cout << c;
                        }
                    }
                }
            }
        }
    }
}
   
void NodeThayThe(TREE &nodeXoa, TREE &cayPhai) {
    if (cayPhai->left != NULL) {
        NodeThayThe(nodeXoa, cayPhai->left);
    } else {
        nodeXoa->data = cayPhai->data;
        TREE q = cayPhai;
        cayPhai = cayPhai->right;
        delete q;
    }
}

int XoaVT(TREE &root, const char maVT[]) {
    if (root == NULL) return 0;

    int cmp = strcmp(maVT, root->data.MAVT);

    if (cmp < 0) return XoaVT(root->left, maVT);
    if (cmp > 0) return XoaVT(root->right, maVT);

    // tim thay node can xoa
    TREE p = root;

    if (root->left == NULL) {
        root = root->right;
        delete p;
    } 
    else if (root->right == NULL) {
        root = root->left;
        delete p;
    } 
    else {
        NodeThayThe(root, root->right);
    }

    return 1;
}

//cau b -------------+----------------+------------------+---------------



int SoSanhNhanVien(NHANVIEN *a, NHANVIEN *b) {
    int kq = strcmp(a->TEN, b->TEN);
    if (kq != 0) return kq;

    kq = strcmp(a->HO, b->HO);
    if (kq != 0) return kq;

    return strcmp(a->MANV, b->MANV);
}


void InDanhSachNhanVien(DSNHANVIEN ds, int start) {
    int x = 2;
    int y = 2;
    int pageSize = 15;

    // chi xoa vung bang ben trai
    clearArea(2, 2, 58, 25);

    // Header
    gotoxy(2, y);   cout << "Ma NV";
    gotoxy(16, y);  cout << "Ho";
    gotoxy(34, y);  cout << "Ten";
    gotoxy(50, y);  cout << "Phai";

    // duong ke
    gotoxy(2, y + 1);
    for (int i = 0; i < 58; i++) cout << '-';

    // Data
    for (int i = start; i < start + pageSize && i < ds.n; i++) {
        int row = y + 2 + (i - start);

        clearLine(2, row, 58);

        printAt(2,  row, ds.nv[i]->MANV, 12);
        printAt(16, row, ds.nv[i]->HO,   16);
        printAt(34, row, ds.nv[i]->TEN,  14);
        printAt(50, row, ds.nv[i]->PHAI, 8);
    }

    // xoa cac dong du ben duoi neu trang moi it dong hon trang cu
    for (int row = y + 2 + (ds.n - start < pageSize ? ds.n - start : pageSize); row < y + 2 + pageSize; row++) {
        clearLine(2, row, 58);
    }

    int totalPages = (ds.n + pageSize - 1) / pageSize;
	if (totalPages == 0) totalPages = 1;
	int currentPage = start / pageSize + 1;
	clearLine(2, y + pageSize + 3, 58);
	gotoxy(2, y + pageSize + 3);
	cout << "Trang: " << currentPage << "/" << totalPages;

    gotoxy(2, y + pageSize + 5);
    clearLine(2, y + pageSize + 5, 58);
    gotoxy(2, y + pageSize + 5);
    cout << "[>] Trang sau	[<] Trang truoc	[ESC] Thoat";
    gotoxy(2,y+pageSize+6);
	cout << "[F2] Them NV	[F3] Sua NV	[F4] Xoa NV";
	gotoxy(2,y+pageSize+7);
	cout<<"Loc TEN: ";
    
}


bool NhapThongTinNV(DSNHANVIEN &ds) {
    if (ds.n >= MAXNV) {
    	ThongBaoChung( "Danh sach nhan vien da day.");
        return false;
    }

    NHANVIEN *p = new NHANVIEN;
    p->dshd = NULL;

    char c;
    int len;

    char maTam[MAX_MANV + 1];
    char hoTam[MAX_HO + 1];
    char tenTam[MAX_TEN + 1];
    char phaiTam[MAX_PHAI + 1];

    // ===================== VE UI =====================
    clearLine(70, 5, 60);
    clearLine(70, 7, 60);
    clearLine(70, 9, 60);
    clearLine(70, 11, 60);
    clearLine(70, 15, 60);
    clearLine(70, 16, 60);
    clearLine(70, 18, 60);

    gotoxy(70, 3);  cout << "| Ma NV  : [__________] |";
    gotoxy(70, 5);  cout << "| Ho     : [__________] |";
    gotoxy(70, 7);  cout << "| Ten    : [__________] |";
    gotoxy(70, 9);  cout << "| Phai   : [1.Nam 2.Nu] |";

    gotoxy(70, 15); cout << "ENTER: sang o tiep theo";
    gotoxy(70, 16); cout << "ESC  : thoat ";
    int xMa = 82, yMa = 3;
    int xHo = 82, yHo = 5;
    int xTen = 82, yTen = 7;
    int xPhai = 82, yPhai = 9;

    // ===================== NHAP MA NV =====================
NHAP_MANV:
    while (true) {
        len = 0;
        maTam[0] = '\0';

        clearLine(xMa, yMa, 10);
        gotoxy(xMa, yMa);

        while (true) {
            c = getch();

            if (c == 27) { // ESC
            	 clearArea(65,1,50,16);
            	 XoaThongBaoChung();
                delete p;
                return false;
            }
            else if (c == 13) { // ENTER
                maTam[len] = '\0';
                XoaKhoangTrangDauCuoi(maTam);
                UpperCase(maTam);

                if (strlen(maTam) == 0) {
                	ThongBaoChung("Ma nhan vien khong duoc rong.");
                    break;
                }

                if (!KiemTraMaNV(maTam)) {
                	ThongBaoChung("Ma nhan vien khong hop le.");
                    break;
                }

                // Neu ham cua em: true = khong trung, false = trung
                if (!KiemTraTrungMANV(ds, maTam)) {
                	ThongBaoChung("Ma nhan vien da ton tai.");
                    break;
                }

                strcpy(p->MANV, maTam);
                clearLine(70, 18, 60);
                goto NHAP_HO;
            }
            else if (c == 8) { // BACKSPACE
                if (len > 0) {
                    len--;
                    maTam[len] = '\0';
                    gotoxy(xMa + len, yMa);
                    cout << ' ';
                    gotoxy(xMa + len, yMa);
                }
            }
            else if (isalnum((unsigned char)c)) {
                if (len < MAX_MANV) {
                    c = toupper((unsigned char)c);
                    maTam[len++] = c;
                    maTam[len] = '\0';
                    gotoxy(xMa + len - 1, yMa);
                    cout << c;
                }
            }
        }
    }

    // ===================== NHAP HO =====================
NHAP_HO:
    while (true) {
        len = 0;
        hoTam[0] = '\0';

        clearLine(xHo, yHo, 10);
        gotoxy(xHo, yHo);

        while (true) {
            c = getch();

            if (c == 27) { // ESC
             	clearArea(65,1,50,16);
             	XoaThongBaoChung();
                delete p;
                return false;
            }
            else if (c == 13) { // ENTER
                hoTam[len] = '\0';
                XoaKhoangTrangDauCuoi(hoTam);
                ChuanHoaKhoangTrang(hoTam);
                ChuanHoaHoTen(hoTam);

                if (strlen(hoTam) == 0) {
                	ThongBaoChung("Ho khong duoc rong.");
                    break;
                }

                bool hopLe = true;
                for (int i = 0; hoTam[i] != '\0'; i++) {
                    if (!(isalpha((unsigned char)hoTam[i]) || hoTam[i] == ' ')) {
                        hopLe = false;
                        break;
                    }
                }

                if (!hopLe) {
                	ThongBaoChung("Ho khong hop le.");
                    break;
                }

                strcpy(p->HO, hoTam);
                clearLine(70, 18, 60);
                goto NHAP_TEN;
            }
            else if (c == 8) { // BACKSPACE
                if (len > 0) {
                    len--;
                    hoTam[len] = '\0';
                    gotoxy(xHo + len, yHo);
                    cout << ' ';
                    gotoxy(xHo + len, yHo);
                }
            }
            else if (isalpha((unsigned char)c) || c == ' ') {
                if (len < MAX_HO) {
                    if (len == 0 && c == ' ')
                        continue; // chan khoang trang dau

                    if (len > 0 && hoTam[len - 1] == ' ' && c == ' ')
                        continue; // chan 2 khoang trang lien tiep

                    if (c != ' ') {
                        c = tolower((unsigned char)c);
                        if (len == 0 || hoTam[len - 1] == ' ')
                            c = toupper((unsigned char)c);
                    }

                    hoTam[len++] = c;
                    hoTam[len] = '\0';
                    gotoxy(xHo + len - 1, yHo);
                    cout << c;
                }
            }
        }
    }

    // ===================== NHAP TEN =====================
NHAP_TEN:
    while (true) {
        len = 0;
        tenTam[0] = '\0';

        clearLine(xTen, yTen, 10);
        gotoxy(xTen, yTen);

        while (true) {
            c = getch();

            if (c == 27) { // ESC
             	clearArea(65,1,50,16);
             	XoaThongBaoChung();
                delete p;
                return false;
            }
            else if (c == 13) { // ENTER
                tenTam[len] = '\0';
                XoaKhoangTrangDauCuoi(tenTam);
                ChuanHoaKhoangTrang(tenTam);
                ChuanHoaHoTen(tenTam);

                if (strlen(tenTam) == 0) {
                	ThongBaoChung("Ten khong duoc rong.");
                    break;
                }

                bool hopLe = true;
                for (int i = 0; tenTam[i] != '\0'; i++) {
                    if (!(isalpha((unsigned char)tenTam[i]) || tenTam[i] == ' ')) {
                        hopLe = false;
                        break;
                    }
                }

                if (!hopLe) {
                	ThongBaoChung("Ten khong hop le.");
                    break;
                }

                strcpy(p->TEN, tenTam);
                clearLine(70, 18, 60);
                goto NHAP_PHAI;
            }
            else if (c == 8) { // BACKSPACE
                if (len > 0) {
                    len--;
                    tenTam[len] = '\0';
                    gotoxy(xTen + len, yTen);
                    cout << ' ';
                    gotoxy(xTen + len, yTen);
                }
            }
            else if (isalpha((unsigned char)c) || c == ' ') {
                if (len < MAX_TEN) {
                    if (len == 0 && c == ' ')
                        continue;

                    if (len > 0 && tenTam[len - 1] == ' ' && c == ' ')
                        continue;

                    if (c != ' ') {
                        c = tolower((unsigned char)c);
                        if (len == 0 || tenTam[len - 1] == ' ')
                            c = toupper((unsigned char)c);
                    }

                    tenTam[len++] = c;
                    tenTam[len] = '\0';
                    gotoxy(xTen + len - 1, yTen);
                    cout << c;
                }
            }
        }
    }

    // ===================== NHAP PHAI =====================
NHAP_PHAI:
    while (true) {
        gotoxy(xPhai, yPhai);

        c = getch();

        if (c == 27) { // ESC
            delete p;
            clearArea(65,1,50,16);
            XoaThongBaoChung();
            return false;
        }
        else if (c == '1') {
            strcpy(phaiTam, "Nam");
            strcpy(p->PHAI, phaiTam);
            gotoxy(xPhai, yPhai); cout << "Nam";
            break;
        }
        else if (c == '2') {
            strcpy(phaiTam, "Nu");
            strcpy(p->PHAI, phaiTam);
            gotoxy(xPhai, yPhai); cout << "Nu";
            break;
        }
        else {
        	ThongBaoChung(" chi duoc chon 1 hoac 2.");
        }
    }

    // ===================== TIM VI TRI CHEN =====================
    int pos = ds.n;
    for (int i = 0; i < ds.n; i++) {
        if (SoSanhNhanVien(p, ds.nv[i]) < 0) {
            pos = i;
            break;
        }
    }

    // ===================== DAY MANG SANG PHAI =====================
    for (int i = ds.n; i > pos; i--) {
        ds.nv[i] = ds.nv[i - 1];
    }

    ds.nv[pos] = p;
    ds.n++;
	ThongBaoChung("Them nhan vien thanh cong.");
    return true;
}
bool BatDauBang(const char s[], const char prefix[]);



int KiemTraTrungSoHD(DSNHANVIEN ds, const char sohd[]) {
    for (int i = 0; i < ds.n; i++) {
        for (DSHD p = ds.nv[i]->dshd; p != NULL; p = p->next) {
            if (strcmp(p->data.SoHD, sohd) == 0) return 1;
        }
    }
    return 0;
}

void CapNhatTonKho(TREE root, HOADON hd) {
    for (int i = 0; i < hd.dscthd.n; i++) {
        TREE p = TimVT(root, hd.dscthd.ct[i].MAVT);
        if (p == NULL) continue;
        if (hd.Loai == 'N') p->data.SLT += hd.dscthd.ct[i].Soluong;
        else p->data.SLT -= hd.dscthd.ct[i].Soluong;
    }
}

bool LaNamNhuan(int nam) {
    return (nam % 400 == 0) || (nam % 4 == 0 && nam % 100 != 0);
}

bool KiemTraNgayHopLe(int ngay, int thang, int nam) {
    if (nam < 1900 || nam > 9999) return false;
    if (thang < 1 || thang > 12) return false;
    if (ngay < 1) return false;

    int soNgay[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (LaNamNhuan(nam)) soNgay[2] = 29;
    return ngay <= soNgay[thang];
}

void DinhDangNgay(const Date &d, char out[]) {
    sprintf(out, "%02d/%02d/%04d", d.day, d.month, d.year);
}

bool ParseLongKhongAm(const char s[], long &value) {
    if (strlen(s) == 0) return false;
    for (int i = 0; s[i] != '\0'; i++) {
        if (!isdigit((unsigned char)s[i])) return false;
    }
    value = atol(s);
    return value >= 0;
}

bool ParseIntDuong(const char s[], int &value) {
    long tmp;
    if (!ParseLongKhongAm(s, tmp)) return false;
    value = (int)tmp;
    return value > 0;
}

bool ParseFloatVAT(const char s[], float &value) {
    if (strlen(s) == 0) return false;

    char temp[50];
    int len = 0;
    bool hasDot = false;
    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (c == ',') c = '.';

        if (c == '.') {
            if (hasDot) return false;
            hasDot = true;
        }
        else if (!isdigit((unsigned char)c)) {
            return false;
        }
        temp[len++] = c;
    }
    temp[len] = '\0';

    if (strcmp(temp, ".") == 0) return false;

    value = (float)atof(temp);
    return value >= 0.0f && value <= 100.0f;
}

int TimCTHDTheoMa(const HOADON &hd, const char maVT[]) {
    for (int i = 0; i < hd.dscthd.n; i++) {
        if (strcmp(hd.dscthd.ct[i].MAVT, maVT) == 0) return i;
    }
    return -1;
}

long double ThanhTienCT(const CT_HOADON &ct) {
    return (long double)ct.Soluong * (long double)ct.Dongia * (1.0L + (long double)ct.VAT / 100.0L);
}

long double TongTriGiaHoaDon(const HOADON &hd) {
    long double tong = 0;
    for (int i = 0; i < hd.dscthd.n; i++) tong += ThanhTienCT(hd.dscthd.ct[i]);
    return tong;
}




void ThongBaoHD(const char *msg) {
    ThongBaoChung(msg);
}

bool NhapKyTuTaiO(int x, int y, int maxLen, char out[], bool chiSo, bool choDauCham) {
    int len = (int)strlen(out);
    gotoxy(x, y); cout << out;
    gotoxy(x + len, y);

    while (true) {
        int c = getch();
        if (c == 27) return false;
        if (c == 13) {
            out[len] = '\0';
            return true;
        }
        if (c == 8) {
            if (len > 0) {
                len--;
                out[len] = '\0';
                gotoxy(x + len, y);
                cout << ' ';
                gotoxy(x + len, y);
            }
        }
        else if (isprint((unsigned char)c)) {
            if (len >= maxLen) continue;
            if (chiSo) {
                if (!isdigit((unsigned char)c) && !(choDauCham && (c == '.' || c == ','))) continue;
            }
            else {
                if (!(isalnum((unsigned char)c) || c == '-' || c == '_' || c == '.')) continue;
                c = toupper((unsigned char)c);
            }
            out[len++] = (char)c;
            out[len] = '\0';
            gotoxy(x + len - 1, y);
            cout << (char)c;
        }
    }
}

void VeFormHD() {
    clearArea(HD_FORM_X, 1, HD_FORM_W, HD_FORM_H);
    gotoxy(HD_FORM_X, 2);  cout << "| So HD : [____________________] |";
    gotoxy(HD_FORM_X, 4);  cout << "| Ngay  : [__] |";
    gotoxy(HD_FORM_X, 6);  cout << "| Thang : [__] |";
    gotoxy(HD_FORM_X, 8);  cout << "| Nam   : [____] |";
    gotoxy(HD_FORM_X, 10); cout << "| Loai  : [N/X] |";
    gotoxy(HD_FORM_X, 14); cout << "ENTER: sang o tiep theo";
    gotoxy(HD_FORM_X, 15); cout << "ESC  : quay lai";
}
void VeDanhSachHoaDon(ITEM_HD a[], int n, int start, int selected, const char tuKhoa[]) {
    int y = 2;
    int pageSize = 15;

    clearArea(1, 1, 125, 35);

    gotoxy(2, 1);  cout << "DANH SACH HOA DON";

    gotoxy(3, y);   cout << " ";
    gotoxy(5, y);   cout << "So HD";
    gotoxy(28, y);  cout << "Ngay";
    gotoxy(42, y);  cout << "Nguoi lap";
    gotoxy(70, y);  cout << "Loai";

    gotoxy(2, y + 1);
    for (int i = 0; i < 78; i++) cout << '-';

    if (n == 0) {
        gotoxy(2, y + 3);
        cout << "Khong co hoa don phu hop.";
    } else {
        for (int i = start; i < start + pageSize && i < n; i++) {
            int row = y + 2 + (i - start);

            clearLine(2, row, 85);

            gotoxy(3, row);
            cout << (i == selected ? '>' : ' ');

            printAt(5, row, a[i].hd->data.SoHD, 20);

            char ngay[20];
            DinhDangNgay(a[i].hd->data.Ngaylap, ngay);
            printAt(28, row, ngay, 12);

            char hoten[30];
            strcpy(hoten, a[i].nv->HO);
            strcat(hoten, " ");
            strcat(hoten, a[i].nv->TEN);
            printAt(42, row, hoten, 24);

            gotoxy(70, row);
            cout << a[i].hd->data.Loai;
        }
    }

    for (int row = y + 2 + (n - start < pageSize ? n - start : pageSize); row < y + 2 + pageSize; row++) {
        clearLine(2, row, 85);
    }

    int totalPages = (n == 0 ? 1 : (n + pageSize - 1) / pageSize);
    int currentPage = (n == 0 ? 1 : start / pageSize + 1);

    clearLine(2, y + pageSize + 3, 85);
    gotoxy(2, y + pageSize + 3);
    cout << "Trang: " << currentPage << "/" << totalPages;

    clearLine(2, y + pageSize + 4, 100);
    gotoxy(2, y + pageSize + 4);
    cout << "[^][v] Len/xuong  [<-][->] Trang  [ENTER] Chon  [ESC] Thoat";

    clearLine(2, y + pageSize + 5, 100);
    gotoxy(2, y + pageSize + 5);
    cout << "Loc TEN nguoi lap: " << tuKhoa << "   [Backspace] Xoa 1 ky tu";
}
int TaoMangNhanVienLoc(DSNHANVIEN ds, const char tuKhoa[], NHANVIEN *loc[]) {
    int nLoc = 0;
    for (int i = 0; i < ds.n; i++) {
        if (tuKhoa[0] == '\0' || BatDauBang(ds.nv[i]->TEN, tuKhoa)) {
            loc[nLoc++] = ds.nv[i];
        }
    }
    return nLoc;
}

void VeBangChonNhanVienHD(NHANVIEN *loc[], int nLoc, int start, int selected, const char tuKhoa[]) {
    int y = 2;
    int pageSize = 15;

    // CHI xoa vung bang ben trai, khong xoa ca man hinh
    clearArea(2, 1, 62, 25);

    gotoxy(2, 1); cout << "CHON NHAN VIEN LAP HOA DON";

    gotoxy(3, y);   cout << " ";
    gotoxy(4, y);   cout << "Ma NV";
    gotoxy(18, y);  cout << "Ho";
    gotoxy(36, y);  cout << "Ten";
    gotoxy(52, y);  cout << "Phai";

    gotoxy(2, y + 1);
    for (int i = 0; i < 58; i++) cout << '-';

    // xoa 15 dong data truoc khi ve trang moi
    for (int i = 0; i < pageSize; i++) {
        clearLine(2, y + 2 + i, 58);
    }

    if (nLoc == 0) {
        gotoxy(2, y + 3); cout << "Khong co nhan vien phu hop.";
    } else {
        for (int i = start; i < start + pageSize && i < nLoc; i++) {
            int row = y + 2 + (i - start);

            gotoxy(2, row); cout << (i == selected ? '>' : ' ');
            printAt(4,  row, loc[i]->MANV, 12);
            printAt(18, row, loc[i]->HO,   16);
            printAt(36, row, loc[i]->TEN,  14);
            printAt(52, row, loc[i]->PHAI, 8);
        }
    }

    int totalPages = (nLoc == 0 ? 1 : (nLoc + pageSize - 1) / pageSize);
    int currentPage = (nLoc == 0 ? 1 : start / pageSize + 1);

    clearLine(2, y + pageSize + 3, 70);
    gotoxy(2, y + pageSize + 3);
    cout << "Trang: " << currentPage << "/" << totalPages;

    clearLine(2, y + pageSize + 4, 90);
    gotoxy(2, y + pageSize + 4);
    cout << "[ENTER] Chon  [<-][->] Trang  [^][v] Dong  [ESC] Thoat";

    clearLine(2, y + pageSize + 5, 90);
    gotoxy(2, y + pageSize + 5);
    cout << "Loc TEN: " << tuKhoa << "   [Backspace] Xoa 1 ky tu";
}

bool ChonNhanVienLapHoaDon(DSNHANVIEN ds, NHANVIEN* &nvChon) {
    const int pageSize = 15;
    const int y = 2;

    int selected = 0;
    int start = 0;

    char tuKhoa[MAX_TEN + 1];
    int lenLoc = 0;
    tuKhoa[0] = '\0';

    NHANVIEN *loc[MAXNV];
    int nLoc = TaoMangNhanVienLoc(ds, tuKhoa, loc);

    VeBangChonNhanVienHD(loc, nLoc, start, selected, tuKhoa);

    while (true) {
        int c = getch();

        if (c == 0 || c == 224 || c == -32) {
            int f = getch();

            if (nLoc <= 0) continue;

            int oldSelected = selected;
            int oldStart = start;

            if (f == 72) { // len
                if (selected > 0) selected--;
            }
            else if (f == 80) { // xuong
                if (selected < nLoc - 1) selected++;
            }
            else if (f == 75) { // trai = trang truoc
                if (start - pageSize >= 0) {
                    start -= pageSize;
                    selected = start;
                }
            }
            else if (f == 77) { // phai = trang sau
                if (start + pageSize < nLoc) {
                    start += pageSize;
                    selected = start;
                }
            }

            // neu doi trang -> ve lai ca trang
            if (start != oldStart) {
                VeBangChonNhanVienHD(loc, nLoc, start, selected, tuKhoa);
            }
            // neu chi doi dong trong cung 1 trang -> chi cap nhat 2 dau '>'
            else if (selected != oldSelected) {
                int oldRow = y + 2 + (oldSelected - start);
                int newRow = y + 2 + (selected - start);

                gotoxy(2, oldRow); cout << ' ';
                gotoxy(2, newRow); cout << '>';
            }
        }
        else if (c == 13) {
            if (nLoc > 0) {
                nvChon = loc[selected];
                return true;
            }
        }
        else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            if (lenLoc < MAX_TEN) {
                tuKhoa[lenLoc++] = (char)toupper((unsigned char)c);
                tuKhoa[lenLoc] = '\0';

                nLoc = TaoMangNhanVienLoc(ds, tuKhoa, loc);
                selected = 0;
                start = 0;

                VeBangChonNhanVienHD(loc, nLoc, start, selected, tuKhoa);
            }
        }
        else if (c == 8) {
            if (lenLoc > 0) {
                lenLoc--;
                tuKhoa[lenLoc] = '\0';

                nLoc = TaoMangNhanVienLoc(ds, tuKhoa, loc);
                selected = 0;
                start = 0;

                VeBangChonNhanVienHD(loc, nLoc, start, selected, tuKhoa);
            }
        }
        else if (c == 27) {
            XoaManHinh();
            return false;
        }
    }
}

int TaoMangVatTuLoc(TREE root, const char tuKhoa[], VATTU loc[]) {
    VATTU a[1000];
    int n = 0, nLoc = 0;
    ChepCayRaMang(root, a, n);
    SapXepTheoTen(a, n);

    for (int i = 0; i < n; i++) {
        if (tuKhoa[0] == '\0' || BatDauBang(a[i].TENVT, tuKhoa)) {
            loc[nLoc++] = a[i];
        }
    }
    return nLoc;
}

void VeBangChonVatTuPopup(VATTU loc[], int nLoc, int start, int selected, const char tuKhoa[]) {
    int y = 2;
    int pageSize = 15;

    // chi xoa vung popup ben trai, khong xoa ca man hinh
    XoaManHinh();
    clearArea(2, 1, 64, 25);

    gotoxy(2, 1); cout << "TIM VAT TU TON KHO";

    gotoxy(2, y);   cout << " ";
    gotoxy(3, y);   cout << "Ma VT";
    gotoxy(15, y);  cout << "Ten VT";
    gotoxy(39, y);  cout << "DVT";
    gotoxy(52, y);  cout << "SLT";

    gotoxy(2, y + 1);
    for (int i = 0; i < 60; i++) cout << '-';

    // xoa 15 dong du lieu cua trang hien tai
    for (int i = 0; i < pageSize; i++) {
        clearLine(2, y + 2 + i, 60);
    }

    if (nLoc == 0) {
        gotoxy(2, y + 3);
        cout << "Khong co vat tu phu hop.";
    }
    else {
        for (int i = start; i < start + pageSize && i < nLoc; i++) {
            int row = y + 2 + (i - start);

            gotoxy(2, row); cout << (i == selected ? '>' : ' ');
            printAt(3,  row, loc[i].MAVT, 10);
            printAt(15, row, loc[i].TENVT, 20);
            printAt(39, row, loc[i].DVT, 10);
            gotoxy(52, row); cout << loc[i].SLT << "      ";
        }
    }

    int totalPages = (nLoc == 0 ? 1 : (nLoc + pageSize - 1) / pageSize);
    int currentPage = (nLoc == 0 ? 1 : start / pageSize + 1);

    clearLine(2, y + pageSize + 3, 70);
    gotoxy(2, y + pageSize + 3);
    cout << "Trang: " << currentPage << "/" << totalPages;

    clearLine(2, y + pageSize + 4, 90);
    gotoxy(2, y + pageSize + 4);
    cout << "[ENTER] Chon  [<-][->] Trang  [^][v] Dong  [ESC] Thoat";

    clearLine(2, y + pageSize + 6, 100);
    gotoxy(2, y + pageSize + 6);
    cout << "Loc TENVT: " << tuKhoa << "   [Backspace] Xoa 1 ky tu";
}

bool ChonVatTuTonKhoPopup(TREE root, char maVTOut[]) {
    const int pageSize = 15;
    const int y = 2;

    int selected = 0;
    int start = 0;

    char tuKhoa[MAX_TENVT + 1];
    int lenLoc = 0;
    tuKhoa[0] = '\0';

    VATTU loc[1000];
    int nLoc = TaoMangVatTuLoc(root, tuKhoa, loc);

    VeBangChonVatTuPopup(loc, nLoc, start, selected, tuKhoa);

    while (true) {
        int c = getch();

        if (c == 0 || c == 224 || c == -32) {
            int f = getch();

            if (nLoc <= 0) continue;

            int oldSelected = selected;
            int oldStart = start;

            if (f == 72) { // len
                if (selected > 0) selected--;
            }
            else if (f == 80) { // xuong
                if (selected < nLoc - 1) selected++;
            }
            else if (f == 75) { // trang truoc
                if (start - pageSize >= 0) {
                    start -= pageSize;
                    selected = start;
                }
            }
            else if (f == 77) { // trang sau
                if (start + pageSize < nLoc) {
                    start += pageSize;
                    selected = start;
                }
            }

            // doi trang -> ve lai ca popup
            if (start != oldStart) {
                VeBangChonVatTuPopup(loc, nLoc, start, selected, tuKhoa);
            }
            // chi doi dong trong cung 1 trang -> chi doi dau '>'
            else if (selected != oldSelected) {
                int oldRow = y + 2 + (oldSelected - start);
                int newRow = y + 2 + (selected - start);

                gotoxy(2, oldRow); cout << ' ';
                gotoxy(2, newRow); cout << '>';
            }
        }
        else if (c == 13) {
            if (nLoc > 0) {
                strcpy(maVTOut, loc[selected].MAVT);
                return true;
            }
        }
        else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            if (lenLoc < MAX_TENVT) {
                tuKhoa[lenLoc++] = (char)toupper((unsigned char)c);
                tuKhoa[lenLoc] = '\0';

                nLoc = TaoMangVatTuLoc(root, tuKhoa, loc);
                selected = 0;
                start = 0;

                VeBangChonVatTuPopup(loc, nLoc, start, selected, tuKhoa);
            }
        }
        else if (c == 8) {
            if (lenLoc > 0) {
                lenLoc--;
                tuKhoa[lenLoc] = '\0';

                nLoc = TaoMangVatTuLoc(root, tuKhoa, loc);
                selected = 0;
                start = 0;

                VeBangChonVatTuPopup(loc, nLoc, start, selected, tuKhoa);
            }
        }
        else if (c == 27) {
            return false;
        }
    }
}

bool NhapThongTinHD(DSNHANVIEN ds, NHANVIEN *nv, HOADON &hd) {
    strcpy(hd.MANV, nv->MANV);
    hd.dscthd.n = 0;

    VeFormHD();
    gotoxy(HD_FORM_X, 1);
    cout << "Nhap thong tin dau hoa don";

    char soHD[MAX_SOHD + 1] = "";
    char sNgay[3]  = "";
    char sThang[3] = "";
    char sNam[5]   = "";
    long tmp;

    // ===================== SO HD =====================
    while (true) {
        clearLine(HD_INPUT_X, 2, 20);
        soHD[0] = '\0';

        if (!NhapKyTuTaiO(HD_INPUT_X, 2, MAX_SOHD, soHD, false, false))
            return false;

        XoaKhoangTrangDauCuoi(soHD);
        UpperCase(soHD);

        if (!KiemTraSoHoaDon(soHD)) {
            ThongBaoHD("So HD khong hop le.");
            continue;
        }

        if (KiemTraTrungSoHD(ds, soHD)) {
            ThongBaoHD("So HD da ton tai.");
            continue;
        }

        break;
    }

    // ===================== NGAY =====================
    while (true) {
        clearLine(HD_INPUT_X, 4, 2);
        sNgay[0] = '\0';

        if (!NhapKyTuTaiO(HD_INPUT_X, 4, 2, sNgay, true, false))
            return false;
	
        if (!ParseLongKhongAm(sNgay, tmp) || tmp < 1 || tmp > 31) {
            ThongBaoHD("Ngay khong hop le.");
            continue;
        }

        hd.Ngaylap.day = (int)tmp;
        break;
    }

    // ===================== THANG =====================
    while (true) {
        clearLine(HD_INPUT_X, 6, 2);
        sThang[0] = '\0';

        if (!NhapKyTuTaiO(HD_INPUT_X, 6, 2, sThang, true, false))
            return false;

        if (!ParseLongKhongAm(sThang, tmp) || tmp < 1 || tmp > 12) {
            ThongBaoHD("Thang khong hop le.");
            continue;
        }

        hd.Ngaylap.month = (int)tmp;
        break;
    }

    // ===================== NAM =====================
    while (true) {
        clearLine(HD_INPUT_X, 8, 4);
        sNam[0] = '\0';

        if (!NhapKyTuTaiO(HD_INPUT_X, 8, 4, sNam, true, false))
            return false;

        if (!ParseLongKhongAm(sNam, tmp) || tmp <= 0) {
            ThongBaoHD("Nam khong hop le.");
            continue;
        }

        hd.Ngaylap.year = (int)tmp;
        break;
    }

    // ===================== KIEM TRA NGAY THUC SU =====================
    while (!KiemTraNgayHopLe(hd.Ngaylap.day, hd.Ngaylap.month, hd.Ngaylap.year)) {
        ThongBaoHD("Ngay lap khong hop le. Nhap lai Ngay/Thang/Nam.");

        // Nhap lai NGAY
        while (true) {
            clearLine(HD_INPUT_X, 4, 2);
            sNgay[0] = '\0';

            if (!NhapKyTuTaiO(HD_INPUT_X, 4, 2, sNgay, true, false))
                return false;

            if (!ParseLongKhongAm(sNgay, tmp) || tmp < 1 || tmp > 31) {
                ThongBaoHD("Ngay khong hop le.");
                continue;
            }

            hd.Ngaylap.day = (int)tmp;
            break;
        }

        // Nhap lai THANG
        while (true) {
            clearLine(HD_INPUT_X, 6, 2);
            sThang[0] = '\0';

            if (!NhapKyTuTaiO(HD_INPUT_X, 6, 2, sThang, true, false))
                return false;

            if (!ParseLongKhongAm(sThang, tmp) || tmp < 1 || tmp > 12) {
                ThongBaoHD("Thang khong hop le.");
                continue;
            }

            hd.Ngaylap.month = (int)tmp;
            break;
        }

        // Nhap lai NAM
        while (true) {
            clearLine(HD_INPUT_X, 8, 4);
            sNam[0] = '\0';

            if (!NhapKyTuTaiO(HD_INPUT_X, 8, 4, sNam, true, false))
                return false;

            if (!ParseLongKhongAm(sNam, tmp) || tmp <= 0) {
                ThongBaoHD("Nam khong hop le.");
                continue;
            }

            hd.Ngaylap.year = (int)tmp;
            break;
        }
    }

    // ===================== LOAI =====================
    gotoxy(94, 10);

    while (true) {
        int c = getch();

        if (c == 27)
            return false;

        if (c == 'n' || c == 'N' || c == 'x' || c == 'X') {
            hd.Loai = (char)toupper((unsigned char)c);
            break;
        }

        ThongBaoHD("Loai chi duoc nhap N hoac X.");
        gotoxy(94, 10);
    }

    strcpy(hd.SoHD, soHD);
    ThongBaoHD("Nhap thong tin hoa don thanh cong.");
    return true;
}

void VeThongTinHD(const NHANVIEN *nv, const HOADON &hd) {
    char ngay[20];
    DinhDangNgay(hd.Ngaylap, ngay);

    clearArea(1, 1, 125, 9);
    gotoxy(2, 1); cout << "LAP HOA DON";
    gotoxy(2, 3); cout << "Nhan vien : " << nv->MANV << " - " << nv->HO << " " << nv->TEN;
    gotoxy(2, 4); cout << "So HD     : " << hd.SoHD;
    gotoxy(2, 5); cout << "Ngay lap  : " << ngay;
    gotoxy(2, 6); cout << "Loai      : " << hd.Loai;
}

void VeBangCTHD(const HOADON &hd) {
    int y = 10;
    clearArea(1, y, 130, 24);

    gotoxy(2, y);  cout << "Ma VT";
    gotoxy(16, y); cout << "So luong";
    gotoxy(29, y); cout << "Don gia";
    gotoxy(45, y); cout << "VAT";
    gotoxy(58, y); cout << "Thanh tien";
    gotoxy(2, y + 1); for (int i = 0; i < 75; i++) cout << '-';

    for (int i = 0; i < hd.dscthd.n; i++) {
        int row = y + 2 + i;
        clearLine(2, row, 95);
        printAt(2, row, hd.dscthd.ct[i].MAVT, 10);
        gotoxy(16, row); cout << hd.dscthd.ct[i].Soluong << "        ";
        gotoxy(29, row); cout << hd.dscthd.ct[i].Dongia << "        ";
        gotoxy(45, row); cout << fixed << setprecision(2) << hd.dscthd.ct[i].VAT << "%    ";
        gotoxy(58, row); cout << fixed << setprecision(2) << (double)ThanhTienCT(hd.dscthd.ct[i]) << "        ";
    }

    for (int row = y + 2 + hd.dscthd.n; row < y + 2 + MAXCTHD; row++) clearLine(2, row, 95);

    clearLine(2, y + 2 + MAXCTHD + 1, 100);
    gotoxy(2, y + 2 + MAXCTHD + 1); cout << "Tong: " << fixed << setprecision(2) << (double)TongTriGiaHoaDon(hd);
    clearLine(2, y + 2 + MAXCTHD + 3, 120);
    gotoxy(2, y + 2 + MAXCTHD + 3); cout << "[F2] Them CT  [F3] Sua CT  [F4] Xoa CT  [F5] Tim VT  [F9] Luu  [ESC] Thoat";
}

bool NhapThongTinCTHD(TREE root, HOADON &hd) {
    if (hd.dscthd.n >= MAXCTHD) {
        ThongBaoHD("Hoa don da du 20 chi tiet.");
        return false;
    }

    clearArea(formX, 1, HD_FORM_W, HD_FORM_H);
    gotoxy(formX, 1);  cout << "THEM CHI TIET HOA DON";
    gotoxy(formX, 3);  cout << "| Ma VT    : [__________] |";
    gotoxy(formX, 5);  cout << "| VAT      : [__________] |";
    gotoxy(formX, 7);  cout << "| So luong : [__________] |";
    gotoxy(formX, 9);  cout << "| Don gia  : [__________] |";
    gotoxy(formX, 13); cout << "F5  : tim vat tu theo TENVT";
    gotoxy(formX, 14); cout << "ENTER: sang o tiep theo";
    gotoxy(formX, 15); cout << "ESC : huy thao tac";

    CT_HOADON ct;
    ct.MAVT[0] = '\0';
    ct.Soluong = 0;
    ct.Dongia = 0;
    ct.VAT = 0;

    int len = 0;
    gotoxy(inputX, 3);

    // ===================== NHAP MAVT =====================
    while (true) {
        int c = getch();

        if (c == 27) {
            clearArea(formX, 1, HD_FORM_W, HD_FORM_H);
            XoaThongBaoChung();
            return false;
        }
        else if (c == 0 || c == 224 || c == -32) {
            int f = getch();

            if (f == 63) {   // F5
                char maPopup[MAX_MAVT + 1] = "";
                if (ChonVatTuTonKhoPopup(root, maPopup)) {
                    strcpy(ct.MAVT, maPopup);
                    len = (int)strlen(ct.MAVT);

                    // ve lai form sau popup
                    clearArea(formX, 1, HD_FORM_W, HD_FORM_H);
                    gotoxy(formX, 1);  cout << "THEM CHI TIET HOA DON";
                    gotoxy(formX, 3);  cout << "| Ma VT    : [__________] |";
                    gotoxy(formX, 5);  cout << "| VAT      : [__________] |";
                    gotoxy(formX, 7);  cout << "| So luong : [__________] |";
                    gotoxy(formX, 9);  cout << "| Don gia  : [__________] |";
                    gotoxy(formX, 13); cout << "F5  : tim vat tu theo TENVT";
                    gotoxy(formX, 14); cout << "ENTER: sang o tiep theo";
                    gotoxy(formX, 15); cout << "ESC : huy thao tac";

                    gotoxy(inputX, 3);
                    cout << ct.MAVT;

                    // F5 da chon duoc ma thi khong cho sua tiep MAVT nua
                    break;
                } else {
                    // neu dong popup thi ve lai form nhap
                    clearArea(formX, 1, HD_FORM_W, HD_FORM_H);
                    gotoxy(formX, 1);  cout << "THEM CHI TIET HOA DON";
                    gotoxy(formX, 3);  cout << "| Ma VT    : [__________] |";
                    gotoxy(formX, 5);  cout << "| VAT      : [__________] |";
                    gotoxy(formX, 7);  cout << "| So luong : [__________] |";
                    gotoxy(formX, 9);  cout << "| Don gia  : [__________] |";
                    gotoxy(formX, 13); cout << "F5  : tim vat tu theo TENVT";
                    gotoxy(formX, 14); cout << "ENTER: sang o tiep theo";
                    gotoxy(formX, 15); cout << "ESC : huy thao tac";

                    gotoxy(inputX, 3);
                    cout << ct.MAVT;
                    gotoxy(inputX + len, 3);
                }
            }
        }
        else if (c == 13) {
            XoaKhoangTrangDauCuoi(ct.MAVT);
            UpperCase(ct.MAVT);

            if (!KiemTraMaVT(ct.MAVT)) {
                ThongBaoHD("Ma VT khong hop le.");
                len = 0;
                ct.MAVT[0] = '\0';
                gotoxy(formX, 3); cout << "| Ma VT    : [__________] |";
                gotoxy(inputX, 3);
                continue;
            }

            if (TimVT(root, ct.MAVT) == NULL) {
                ThongBaoHD("Ma VT khong ton tai.");
                len = 0;
                ct.MAVT[0] = '\0';
                gotoxy(formX, 3); cout << "| Ma VT    : [__________] |";
                gotoxy(inputX, 3);
                continue;
            }

            if (TimCTHDTheoMa(hd, ct.MAVT) != -1) {
                ThongBaoHD("Ma VT da ton tai trong hoa don.");
                len = 0;
                ct.MAVT[0] = '\0';
                gotoxy(formX, 3); cout << "| Ma VT    : [__________] |";
                gotoxy(inputX, 3);
                continue;
            }

            break;
        }
        else if (c == 8) {
            if (len > 0) {
                len--;
                ct.MAVT[len] = '\0';
                gotoxy(inputX + len, 3);
                cout << ' ';
                gotoxy(inputX + len, 3);
            }
        }
        else if (isalnum((unsigned char)c)) {
            if (len < MAX_MAVT) {
                c = toupper((unsigned char)c);
                ct.MAVT[len++] = (char)c;
                ct.MAVT[len] = '\0';
                gotoxy(inputX + len - 1, 3);
                cout << (char)c;
            }
        }
    }

    // ===================== NHAP VAT =====================
    char sVAT[20] = "";
    while (true) {
        clearLine(inputX, 5, 10);
        gotoxy(inputX, 5);

        if (!NhapKyTuTaiO(inputX, 5, 10, sVAT, true, true))
            return false;

        if (!ParseFloatVAT(sVAT, ct.VAT)) {
            ThongBaoHD("VAT phai tu 0 den 100.");
            continue;
        }
        break;
    }

    // ===================== NHAP SO LUONG =====================
    char sSL[20] = "";
    while (true) {
        clearLine(inputX, 7, 10);
        gotoxy(inputX, 7);

        if (!NhapKyTuTaiO(inputX, 7, 10, sSL, true, false))
            return false;

        if (!ParseIntDuong(sSL, ct.Soluong)) {
            ThongBaoHD("So luong phai > 0.");
            continue;
        }

        TREE pVT = TimVT(root, ct.MAVT);
        if (hd.Loai == 'X' && pVT != NULL && ct.Soluong > pVT->data.SLT) {
            char msg[80];
            sprintf(msg, "Khong du hang. Ton hien co: %d", pVT->data.SLT);
            ThongBaoHD(msg);
            continue;
        }
        break;
    }

    // ===================== NHAP DON GIA =====================
    char sDG[20] = "";
    while (true) {
        clearLine(inputX, 9, 10);
        gotoxy(inputX, 9);

        if (!NhapKyTuTaiO(inputX, 9, 10, sDG, true, false))
            return false;

        if (!ParseLongKhongAm(sDG, ct.Dongia)) {
            ThongBaoHD("Don gia khong hop le.");
            continue;
        }
        break;
    }

    hd.dscthd.ct[hd.dscthd.n++] = ct;
    ThongBaoHD("Them chi tiet hoa don thanh cong.");
    return true;
}

bool SuaCTHDUI(TREE root, HOADON &hd) {
    if (hd.dscthd.n == 0) {
        ThongBaoHD("Hoa don chua co chi tiet de sua.");
        return false;
    }

    clearArea(80, 1, 60, 22);
    gotoxy(80, 1); cout << "Nhap MAVT can sua (ESC de thoat):";
    gotoxy(80, 3); cout << "| Ma VT    : [__________] |";

    char maVT[MAX_MAVT + 1] = "";
    int len = 0;
    gotoxy(94, 3);   // vì khung là "| Ma VT    : [__________] |"

    while (true) {
        int c = getch();

        if (c == 27) {
            clearArea(80, 1, 60, 22);
            return false;
        }
        else if (c == 13) {
            XoaKhoangTrangDauCuoi(maVT);
            UpperCase(maVT);

            int vt = TimCTHDTheoMa(hd, maVT);
            if (vt == -1) {
                ThongBaoHD("Khong tim thay MAVT trong hoa don.");
                len = 0;	
                maVT[0] = '\0';
                clearLine(94, 3, 10);
                gotoxy(94, 3);
                continue;
            }

            while (true) {
                clearArea(80, 1, 60, 22);

                gotoxy(80, 1);  cout << "SUA CHI TIET HOA DON";
                gotoxy(80, 3);  cout << "| Ma VT    : [__________] |";
                gotoxy(80, 5);  cout << "| VAT      : [__________] |";
                gotoxy(80, 7);  cout << "| So luong : [__________] |";
                gotoxy(80, 9);  cout << "| Don gia  : [__________] |";

                gotoxy(80, 12); cout << "1. Sua VAT";
                gotoxy(80, 13); cout << "2. Sua So luong";
                gotoxy(80, 14); cout << "3. Sua Don gia";
                gotoxy(80, 15); cout << "ESC de thoat";

                // IN TOAN BO THONG TIN HIEN TAI
                char sVAT[20];
                char sSL[20];
                char sDG[20];

                sprintf(sVAT, "%.2f", hd.dscthd.ct[vt].VAT);
                sprintf(sSL, "%d", hd.dscthd.ct[vt].Soluong);
                sprintf(sDG, "%ld", hd.dscthd.ct[vt].Dongia);

                gotoxy(94, 3); cout << hd.dscthd.ct[vt].MAVT;
                gotoxy(94, 5); cout << sVAT;
                gotoxy(94, 7); cout << sSL;
                gotoxy(94, 9); cout << sDG;

                int ch = getch();

                if (ch == 27) {
                    clearArea(80, 1, 60, 22);
                    return false;
                }
                else if (ch == '1') {
                    clearLine(94, 5, 10);
                    if (!NhapKyTuTaiO(94, 5, 10, sVAT, true, true)) {
                        continue;
                    }

                    float vatMoi;
                    if (!ParseFloatVAT(sVAT, vatMoi)) {
                        ThongBaoHD("VAT phai tu 0 den 100.");
                        continue;
                    }

                    hd.dscthd.ct[vt].VAT = vatMoi;
                    ThongBaoHD("Da cap nhat VAT.");
                    return true;
                }
                else if (ch == '2') {
                    clearLine(94, 7, 10);
                    if (!NhapKyTuTaiO(94, 7, 10, sSL, true, false)) {
                        continue;
                    }

                    int slMoi;
                    if (!ParseIntDuong(sSL, slMoi)) {
                        ThongBaoHD("So luong phai > 0.");
                        continue;
                    }

                    TREE pVT = TimVT(root, hd.dscthd.ct[vt].MAVT);

                    // Điểm cần nghĩ thêm:
                    // nếu đây là hóa đơn X và trước đó số lượng cũ là old,
                    // thì thực ch	ất chỉ nên kiểm tra phần tăng thêm:
                    // slMoi - old <= ton hien co
                    if (hd.Loai == 'X' && pVT != NULL) {
                        int oldSL = hd.dscthd.ct[vt].Soluong;
                        int chenhlech = slMoi - oldSL;

                        if (chenhlech > 0 && chenhlech > pVT->data.SLT) {
                            char msg[80];
                            sprintf(msg, "Khong du hang. Ton hien co: %d", pVT->data.SLT);
                            ThongBaoHD(msg);
                            continue;
                        }
                    }

                    hd.dscthd.ct[vt].Soluong = slMoi;
                    ThongBaoHD("Da cap nhat so luong.");
                    return true;
                }
                else if (ch == '3') {
                    clearLine(94, 9, 10);
                    if (!NhapKyTuTaiO(94, 9, 10, sDG, true, false)) {
                        continue;
                    }

                    long dgMoi;
                    if (!ParseLongKhongAm(sDG, dgMoi)) {
                        ThongBaoHD("Don gia khong hop le.");
                        continue;
                    }

                    hd.dscthd.ct[vt].Dongia = dgMoi;
                    ThongBaoHD("Da cap nhat don gia.");
                    return true;
                }
            }
        }
        else if (c == 8) {
            if (len > 0) {
		        len--;
		        maVT[len] = '\0';
		        gotoxy(94 + len, 3);
		        cout << ' ';
		        gotoxy(94 + len, 3);
		    }
        }
        else if (isalnum((unsigned char)c)) {
              if (len < MAX_MAVT) {
		        c = toupper((unsigned char)c);
		        maVT[len++] = (char)c;
		        maVT[len] = '\0';
		        gotoxy(94 + len - 1, 3);
		        cout << (char)c;
		    }
        }
    }
}

bool XoaCTHDUI(HOADON &hd) {
    if (hd.dscthd.n == 0) {
        ThongBaoHD("Hoa don chua co chi tiet de xoa.");
        return false;
    }

    clearArea(formX, 1, 60, 22);
    gotoxy(formX, 1); cout << "Nhap MAVT can sua (ESC de thoat):";
    gotoxy(formX, 3); cout << "| Ma VT    : [__________] |";

    char maVT[MAX_MAVT + 1] = "";
    int len = 0;
    gotoxy(inputX, 3);

    while (true) {
        int c = getch();
        if (c == 27) {
            clearArea(formX, 1, 60, 22);
            return false;
        }
        else if (c == 13) {
            XoaKhoangTrangDauCuoi(maVT);
            UpperCase(maVT);
            int vt = TimCTHDTheoMa(hd, maVT);
            if (vt == -1) {
                ThongBaoHD("Khong tim thay MAVT trong hoa don.");
                len = 0; maVT[0] = '\0'; clearLine(inputX, 3, 10); gotoxy(inputX, 3);
                continue;
            }
			ThongBaoChung("Ban co chac muon xoa? (Y/N): ");
            while (true) {
                int xn = getch();
                xn = toupper((unsigned char)xn);
                if (xn == 'Y') {
                    for (int i = vt; i < hd.dscthd.n - 1; i++) hd.dscthd.ct[i] = hd.dscthd.ct[i + 1];
                    hd.dscthd.n--;
                    ThongBaoHD("Da xoa chi tiet hoa don.");
                    return true;
                }
                if (xn == 'N' || xn == 27) {
                    ThongBaoHD("Da huy xoa chi tiet.");
                    return false;
                }
            }
        }
        else if (c == 8) {
            if (len > 0) {
                len--; maVT[len] = '\0';
                gotoxy(94 + len, 3); cout << ' '; gotoxy(94 + len, 3);
            }
        }
        else if (isalnum((unsigned char)c)) {
            if (len < MAX_MAVT) {
                c = toupper((unsigned char)c);
                maVT[len++] = (char)c;
                maVT[len] = '\0';
                gotoxy(94 + len - 1, 3); cout << (char)c;
            }
        }
    }
}

bool HuyHoaDonDangLapUI() {
	ThongBaoChung("Ban co muon huy hoa don dang lap? (Y/N)");
    while (true) {
        int c = getch();
        c = toupper((unsigned char)c);
        if (c == 'Y') return true;
        if (c == 'N' || c == 27) return false;
    }
}

bool LuuHoaDonDangLap(TREE &root, DSNHANVIEN &dsnv, NHANVIEN *nv, HOADON &hd) {
    if (hd.dscthd.n <= 0) {
        ThongBaoHD("Hoa don phai co it nhat 1 chi tiet.");
        getch();
        return false;
    }

    CapNhatTonKho(root, hd);
    ThemHoaDonVaoCuoi(nv->dshd, hd);
    LuuFileVatTu(root);
    SaveDSNVToFile(dsnv);
    ThongBaoHD("Luu hoa don thanh cong.");
    getch();
    return true;
}

void LapCTHDUI(TREE &root, DSNHANVIEN &dsnv, NHANVIEN *nv, HOADON &hd) {
    while (true) {
        XoaManHinh();
        VeThongTinHD(nv, hd);
        VeBangCTHD(hd);

        int c = getch();
       	if (c == 0 || c == 224 || c == -32) {
            int f = getch();
            if (f == 60) {
                NhapThongTinCTHD(root, hd);
            }
            else if (f == 61) {
                SuaCTHDUI(root, hd);
            }
            else if (f == 62) {
                XoaCTHDUI(hd);
            }
            else if (f == 63) {
 			char maVT[MAX_MAVT + 1] = "";

		    if (ChonVatTuTonKhoPopup(root, maVT)) {
		        if (TimCTHDTheoMa(hd, maVT) != -1) {
		            ThongBaoHD("MAVT da ton tai trong hoa don.");
		            continue;
		        }
		
		        if (hd.dscthd.n >= MAXCTHD) {
		            ThongBaoHD("Hoa don da du 20 chi tiet.");
		            getch();
		            continue;
		        }
		
		        CT_HOADON ct;
		        strcpy(ct.MAVT, maVT);
		        ct.Soluong = 0;
		        ct.Dongia = 0;
		        ct.VAT = 0;
		
		        clearArea(formX, 1, HD_FORM_W, HD_FORM_H);
		        gotoxy(formX, 1);  cout << "THEM CHI TIET HOA DON";
		        gotoxy(formX, 3);  cout << "| Ma VT    : [__________] |";
		        gotoxy(formX, 5);  cout << "| VAT      : [__________] |";
		        gotoxy(formX, 7);  cout << "| So luong : [__________] |";
		        gotoxy(formX, 9);  cout << "| Don gia  : [__________] |";
		        gotoxy(formX, 13); cout << "F5  : tim vat tu theo TENVT";
		        gotoxy(formX, 14); cout << "ENTER: sang o tiep theo";
		        gotoxy(formX, 15); cout << "ESC : huy thao tac";
		
		        gotoxy(inputX, 3);
		        cout << ct.MAVT;
		
		        char sVAT[20] = "";
		        while (true) {
		            clearLine(inputX, 5, 10);
		            gotoxy(inputX, 5);
		
		            if (!NhapKyTuTaiO(inputX, 5, 10, sVAT, true, true))
		                break;
		
		            if (!ParseFloatVAT(sVAT, ct.VAT)) {
		                ThongBaoHD("VAT phai tu 0 den 100.");
		                continue;
		            }
		            break;
		        }
		        if (!ParseFloatVAT(sVAT, ct.VAT)) continue;
		
		        char sSL[20] = "";
		        while (true) {
		            clearLine(inputX, 7, 10);
		            gotoxy(inputX, 7);
		
		            if (!NhapKyTuTaiO(inputX, 7, 10, sSL, true, false))
		                break;
		
		            if (!ParseIntDuong(sSL, ct.Soluong)) {
		                ThongBaoHD("So luong phai > 0.");
		                continue;
		            }
		
		            TREE pVT = TimVT(root, maVT);
		            if (hd.Loai == 'X' && pVT != NULL && ct.Soluong > pVT->data.SLT) {
		                char msg[80];
		                sprintf(msg, "Khong du hang. Ton hien co: %d", pVT->data.SLT);
		                ThongBaoHD(msg);
		                continue;
		            }
		            break;
		        }
		        if (!ParseIntDuong(sSL, ct.Soluong)) continue;
		
		        char sDG[20] = "";
		        while (true) {
		            clearLine(inputX, 9, 10);
		            gotoxy(inputX, 9);
		
		            if (!NhapKyTuTaiO(inputX, 9, 10, sDG, true, false))
		                break;
		
		            if (!ParseLongKhongAm(sDG, ct.Dongia)) {
		                ThongBaoHD("Don gia khong hop le.");
		                continue;
		            }
		            break;
		        }
		        if (!ParseLongKhongAm(sDG, ct.Dongia)) continue;
		
		        hd.dscthd.ct[hd.dscthd.n++] = ct;
		        ThongBaoHD("Them chi tiet hoa don thanh cong.");
		    }
            }
            else if (f == 67) {
                if (LuuHoaDonDangLap(root, dsnv, nv, hd)) {
                    Sleep(600);
                    return;
                }
            }
        }
        else if (c == 27) {
            if (HuyHoaDonDangLapUI()) return;
        }
    }
}

void HD(TREE &root, DSNHANVIEN &dsnv) {
    while (true) {
        NHANVIEN *nvChon = NULL;
        if (!ChonNhanVienLapHoaDon(dsnv, nvChon)) {
            XoaManHinh();
            return;
        }

        HOADON hd;
        hd.dscthd.n = 0;
        if (!NhapThongTinHD(dsnv, nvChon, hd)) {
            XoaManHinh();
            continue;
        }
    

        LapCTHDUI(root, dsnv, nvChon, hd);
        XoaManHinh();
    }
}

void XoaVatTuUI(TREE &root, int &start, DSNHANVIEN &dsnv) {
    char c;
    char maVT[MAX_MAVT + 1];
    int len;
    int xMa = 76, yMa = 3;
	if (root == NULL) {
        gotoxy(65, 18); cout<<"danh sach rong, bam ECS de qua lai nhap VT!";
        c = getch();
        if(c==27){
        	clearLine(65,18,50);
        	XoaThongBaoChung();
        	return;
		}
    }
    while (true) { // lap lai che do xoa cho toi khi bam ESC
        
        
        ThongBaoChung( "Nhap ma VT muon xoa (ESC de thoat):");
        gotoxy(65, 3);
        cout << "| Ma VT : [__________] |";

        len = 0;
        maVT[0] = '\0';

        clearLine(76, 3, 10);
        gotoxy(76, 3);

        while (true) { // vong nhap tung ky tu
            c = getch();
			
            if (c == 27) { // ESC
            	XoaVungSuaVT();
            	clearLine(65,1,20);
            	XoaThongBaoChung();
					  // xoa vung xoa vat tu
                return;                     // thoat che do xoa
            }
            else if (c == 13) { // ENTER
                maVT[len] = '\0';

                if (len == 0) {
                	ThongBaoChung("Ma vat tu khong duoc rong.");
                    break; // nhap lai ma moi
                }

                if (!KiemTraMaVT(maVT)) {
                	ThongBaoChung("Ma khong hop le.");
                    break; // nhap lai
                }

                UpperCase(maVT);

                if (!KiemTraTrungMaVT(root, maVT)) {
                	ThongBaoChung("Ma khong ton tai.");
                    break; // nhap lai
                }

                // hoi xac nhan xoa
                ThongBaoChung("Ban co chac muon xoa? (Y/N): ");
                char xn;
                while (true) {
                    xn = getch();
                    xn = toupper((unsigned char)xn);

                    if (xn == 'Y') {
                        if (KiemTraVatTuDaCoTrongHoaDon(dsnv, maVT)) {
						    ThongBaoChung("Vat tu da co trong hoa don. Khong duoc xoa.");
						    break;
						}
						XoaVT(root, maVT);
                        InDanhSachVatTuTonKho(root, start);
						ThongBaoChung("Da xoa vat tu.");
                        break; // thoat vong hoi xac nhan
                    }
                    else if (xn == 'N' || xn == 27) {
                        ThongBaoChung("Da huy xoa.");
                        
                        break; // khong xoa
                    }
                }
                break; // quay ra while lon de nhap ma moi
            }
            else if (c == 8) { // BACKSPACE
                if (len > 0) {
                    len--;
                    maVT[len] = '\0';
                    gotoxy(xMa + len, yMa);
                    cout << ' ';
                    gotoxy(xMa + len, yMa);
                }
            }
            else if (isalnum((unsigned char)c)) {
                if (len < MAX_MAVT) {
                    c = toupper((unsigned char)c);
                    maVT[len++] = c;
                    maVT[len] = '\0';
                    gotoxy(xMa + len - 1, yMa);
                    cout << c;
                }
            }
        }
    }
}


void VeMenuChinh() {
    XoaManHinh();

    int x = 35;
    int y = 8;

    gotoxy(x, y);     cout << "========================";
    gotoxy(x, y + 1); cout << "      QUAN LY KHO       ";
    gotoxy(x, y + 2); cout << "========================";

    gotoxy(x, y + 4); cout << "1. VAT TU";
    gotoxy(x, y + 5); cout << "2. NHAN VIEN";
    gotoxy(x, y + 6); cout << "3. HOA DON";
    gotoxy(x, y + 7); cout << "4. IN HOA DON";

    gotoxy(x, y + 8); cout << "ESC. THOAT";
    gotoxy(x, y + 10); cout << "Chon chuc nang: ";
}
int MenuChinh() {
    char c;

    while (true) {
        VeMenuChinh();

        gotoxy(51, 18); // vi tri sau "Chon chuc nang: "
        c = getch();

        if (c == 27) { // ESC
        	XoaThongBaoChung();
            return 0;
        }

        if (c == '1' || c == '2' || c == '3' || c == '4') {
            cout << c;
            return c - '0';
        }

        gotoxy(35, 20);
        cout << "Chi duoc nhan 1, 2, 3, 4 hoac ESC.";
        Sleep(800);
    }
}
bool KiemTraChuoiTen(char s[]) {
    XoaKhoangTrangDauCuoi(s);
    ChuanHoaKhoangTrang(s);
    if (strlen(s) == 0) return false;

    for (int i = 0; s[i] != '\0'; i++) {
        if (!(isalpha((unsigned char)s[i]) || s[i] == ' '))
            return false;
    }
    return true;
}

void XoaVungNV() {
    clearArea(65, 1, 60, 22);
}



int TimViTriNVTheoMa(DSNHANVIEN ds, const char ma[]) {
    for (int i = 0; i < ds.n; i++) {
        if (strcmp(ds.nv[i]->MANV, ma) == 0) return i;
    }
    return -1;
}

void DuaNhanVienVeDungThuTu(DSNHANVIEN &ds, int vtCu) {
    NHANVIEN *tam = ds.nv[vtCu];

    for (int i = vtCu; i < ds.n - 1; i++)
        ds.nv[i] = ds.nv[i + 1];
    ds.n--;

    int pos = ds.n;
    for (int i = 0; i < ds.n; i++) {
        if (SoSanhNhanVien(tam, ds.nv[i]) < 0) {
            pos = i;
            break;
        }
    }

    for (int i = ds.n; i > pos; i--)
        ds.nv[i] = ds.nv[i - 1];

    ds.nv[pos] = tam;
    ds.n++;
}

void SuaNV(DSNHANVIEN &ds, int &start) {
    char c;
    char maNV[MAX_MANV + 1];
    int len;

    int xMa = 82, yMa = 3;
    int xHo = 82, yHo = 5;
    int xTen = 82, yTen = 7;
    int xPhai = 82, yPhai = 9;

    if (ds.n == 0) {
    	ThongBaoChung("Danh sach nhan vien rong. ESC de thoat.");
        while (getch() != 27) {}
        clearLine(70, 18, 60);
        return;
    }

TIM_NV:
    XoaVungNV();
    ThongBaoChung("Nhap ma NV muon sua (ESC de thoat):");
    gotoxy(70, 3); cout << "| Ma NV  : [__________] |";

    len = 0;
    maNV[0] = '\0';
    clearLine(xMa, yMa, 10);
    gotoxy(xMa, yMa);

    while (true) {
        c = getch();

        if (c == 27) {
        	XoaThongBaoChung();
            XoaVungNV();
            return;
        }
        else if (c == 13) {
            maNV[len] = '\0';
            XoaKhoangTrangDauCuoi(maNV);
            UpperCase(maNV);

            if (strlen(maNV) == 0) {
            	ThongBaoChung("Ma NV khong duoc rong.");
                clearLine(xMa, yMa, 10);
                gotoxy(xMa, yMa);
                len = 0;
                continue;
            }

            NHANVIEN *p = TimNhanVienTheoMa(ds, maNV);
            if (p == NULL) {
            	ThongBaoChung("Khong tim thay nhan vien.");
                clearLine(xMa, yMa, 10);
                gotoxy(xMa, yMa);
                len = 0;
                continue;
            }

MENU_SUA:
			XoaThongBaoChung();
            XoaVungNV();
            gotoxy(70, 1); cout << "Thong tin nhan vien:";
            
			gotoxy(70, 3);  cout << "| Ma NV  : [__________] |";
		    gotoxy(70, 5);  cout << "| Ho     : [__________] |";
		    gotoxy(70, 7);  cout << "| Ten    : [__________] |";
		    gotoxy(70, 9);  cout << "| Phai   : [__________] |";


            gotoxy(xMa, yMa);   cout << p->MANV;
            gotoxy(xHo, yHo);   cout << p->HO;
            gotoxy(xTen, yTen); cout << p->TEN;
            gotoxy(xPhai, yPhai); cout << p->PHAI;

            gotoxy(70, 12); cout << "1. Sua Ho";
            gotoxy(70, 13); cout << "2. Sua Ten";
            gotoxy(70, 14); cout << "3. Sua Phai";
            gotoxy(70, 15); cout << "ESC: Thoat";

            while (true) {
                c = getch();

                if (c == 27) {
                	XoaThongBaoChung();
                    XoaVungNV();
                    return;
                }
                else if (c == '1') {
                    char hoMoi[MAX_HO + 1];
                    len = 0;
                    hoMoi[0] = '\0';
					ThongBaoChung("Nhap ho moi, ENTER luu, ESC huy");
                    clearLine(xHo, yHo, 10);
                    gotoxy(xHo, yHo);

                    while (true) {
                        c = getch();

                        if (c == 27) {
						
                        XoaThongBaoChung();
						goto MENU_SUA;
					}
                        else if (c == 13) {
                        	
                            hoMoi[len] = '\0';
                            XoaKhoangTrangDauCuoi(hoMoi);
                            ChuanHoaKhoangTrang(hoMoi);
                            ChuanHoaHoTen(hoMoi);

                            if (!KiemTraChuoiTen(hoMoi)) {
                            	ThongBaoChung("Ho khong hop le.");
                                clearLine(xHo, yHo, 10);
                                gotoxy(xHo, yHo);
                                len = 0;
                                continue;
                            }

                            strcpy(p->HO, hoMoi);
                            int vt = TimViTriNVTheoMa(ds, p->MANV);
                            if (vt != -1) DuaNhanVienVeDungThuTu(ds, vt);

                            InDanhSachNhanVien(ds, start);
                            ThongBaoChung("Da cap nhat ho.");
                            goto MENU_SUA;
                        }
                        else if (c == 8) {
                            if (len > 0) {
                                len--;
                                hoMoi[len] = '\0';
                                gotoxy(xHo + len, yHo); cout << ' ';
                                gotoxy(xHo + len, yHo);
                            }
                        }
                        else if (isalpha((unsigned char)c) || c == ' ') {
                            if (len < MAX_HO) {
                                if (len == 0 && c == ' ') continue;
                                if (len > 0 && hoMoi[len - 1] == ' ' && c == ' ') continue;

                                if (c != ' ') {
                                    c = tolower((unsigned char)c);
                                    if (len == 0 || hoMoi[len - 1] == ' ')
                                        c = toupper((unsigned char)c);
                                }

                                hoMoi[len++] = c;
                                hoMoi[len] = '\0';
                                gotoxy(xHo + len - 1, yHo); cout << c;
                            }
                        }
                    }
                }
                else if (c == '2') {
                    char tenMoi[MAX_TEN + 1];
                    len = 0;
                    tenMoi[0] = '\0';
					ThongBaoChung("Nhap ten moi, ENTER luu, ESC huy");
                    
                    clearLine(xTen, yTen, 10);
                    gotoxy(xTen, yTen);

                    while (true) {
                        c = getch();

                        if (c == 27) {
						
						XoaThongBaoChung();
						goto MENU_SUA;}
                        else if (c == 13) {
                            tenMoi[len] = '\0';
                            XoaKhoangTrangDauCuoi(tenMoi);
                            ChuanHoaKhoangTrang(tenMoi);
                            ChuanHoaHoTen(tenMoi);

                            if (!KiemTraChuoiTen(tenMoi)) {
                            	ThongBaoChung("Ten khong hop le.");
                                clearLine(xTen, yTen, 10);
                                gotoxy(xTen, yTen);
                                len = 0;
                                continue;
                            }

                            strcpy(p->TEN, tenMoi);
                            int vt = TimViTriNVTheoMa(ds, p->MANV);
                            if (vt != -1) DuaNhanVienVeDungThuTu(ds, vt);

                            InDanhSachNhanVien(ds, start);
                            ThongBaoChung("Da cap nhat ten.");
                       
                            goto MENU_SUA;
                        }
                        else if (c == 8) {
                            if (len > 0) {
                                len--;
                                tenMoi[len] = '\0';
                                gotoxy(xTen + len, yTen); cout << ' ';
                                gotoxy(xTen + len, yTen);
                            }
                        }
                        else if (isalpha((unsigned char)c) || c == ' ') {
                            if (len < MAX_TEN) {
                                if (len == 0 && c == ' ') continue;
                                if (len > 0 && tenMoi[len - 1] == ' ' && c == ' ') continue;

                                if (c != ' ') {
                                    c = tolower((unsigned char)c);
                                    if (len == 0 || tenMoi[len - 1] == ' ')
                                        c = toupper((unsigned char)c);
                                }

                                tenMoi[len++] = c;
                                tenMoi[len] = '\0';
                                gotoxy(xTen + len - 1, yTen); cout << c;
                            }
                        }
                    }
                }
                else if (c == '3') {
                    clearLine(70, 18, 60);
                    gotoxy(70, 18); cout << "1.Nam  2.Nu";

                    while (true) {
                        c = getch();
                        if (c == 27) 
						XoaThongBaoChung();
						goto MENU_SUA;
                        if (c == '1') {
                            strcpy(p->PHAI, "Nam");
                            InDanhSachNhanVien(ds, start);
                            ThongBaoChung("Da cap nhat phai.");
                            goto MENU_SUA;
                        }
                        if (c == '2') {
                            strcpy(p->PHAI, "Nu");
                            InDanhSachNhanVien(ds, start);
                            ThongBaoChung("Da cap nhat phai.");

                            goto MENU_SUA;
                        }
                    }
                }
            }
        }
        else if (c == 8) {
            if (len > 0) {
                len--;
                maNV[len] = '\0';
                gotoxy(xMa + len, yMa); cout << ' ';
                gotoxy(xMa + len, yMa);
            }
        }
        else if (isalnum((unsigned char)c)) {
            if (len < MAX_MANV) {
                c = toupper((unsigned char)c);
                maNV[len++] = c;
                maNV[len] = '\0';
                gotoxy(xMa + len - 1, yMa); cout << c;
            }
        }
    }
}

void XoaNV(DSNHANVIEN &ds, int &start) {
    char c;
    char maNV[MAX_MANV + 1];
    int len;
    int xMa = 82, yMa = 3;

    if (ds.n == 0) {
        gotoxy(70, 18);
        cout << "Danh sach nhan vien rong. ESC de thoat.";
        while (getch() != 27) {}
        clearLine(70, 18, 60);
        return;
    }

    while (true) {
        ThongBaoChung("Nhap ma NV muon xoa (ESC de thoat):");
        gotoxy(70, 3); cout << "| Ma NV  : [__________] |";

        len = 0;
        maNV[0] = '\0';
        clearLine(xMa, yMa, 10);
        gotoxy(xMa, yMa);

        while (true) {
            c = getch();

            if (c == 27) {
            	XoaThongBaoChung();
                XoaVungNV();
                return;
            }
            else if (c == 13) {
                maNV[len] = '\0';
                XoaKhoangTrangDauCuoi(maNV);
                UpperCase(maNV);

                if (strlen(maNV) == 0) {
                	ThongBaoChung("Ma NV khong duoc rong.");

                    break;
                }

                int vt = TimViTriNVTheoMa(ds, maNV);
                if (vt == -1) {
                	ThongBaoChung("Khong tim thay nhan vien.");
                    break;
                }
				clearLine(70,5,50);
				gotoxy(70, 5); cout << "Ho ten: " << ds.nv[vt]->HO << " " << ds.nv[vt]->TEN << "           ";
				clearLine(70,6,50);
                gotoxy(70, 6); cout << "Phai  : " << ds.nv[vt]->PHAI << "           ";
                ThongBaoChung("Nhan Y de xoa, phim khac de huy");

                c = getch();
                if (c == 'y' || c == 'Y') {
				    if (ds.nv[vt]->dshd != NULL) {
				    	ThongBaoChung("Nhan vien da co hoa don. Khong duoc xoa.");
				        getch();   // cho nguoi dung nhin thong bao
				        len = 0;
				        maNV[0] = '\0';
				        clearLine(xMa, yMa, 10);
				        gotoxy(xMa, yMa);
				        continue; 
				    }
				
				    delete ds.nv[vt];
				
				    for (int i = vt; i < ds.n - 1; i++)
				        ds.nv[i] = ds.nv[i + 1];
				    ds.n--;
				
				    if (start >= ds.n && start > 0) {
				        start -= 15;
				        if (start < 0) start = 0;
				    }
				
				    InDanhSachNhanVien(ds, start);
				    ThongBaoChung("Xoa nhan vien thanh cong.");
				    getch();   // cho nhin thong bao
				}
				else {
				 	ThongBaoChung("Da huy xoa.");
				    getch();   // cho nhin thong bao
				}
				
				break;
            }
            else if (c == 8) {
                if (len > 0) {
                    len--;
                    maNV[len] = '\0';
                    gotoxy(xMa + len, yMa); cout << ' ';
                    gotoxy(xMa + len, yMa);
                }
            }
            else if (isalnum((unsigned char)c)) {
                if (len < MAX_MANV) {
                    c = toupper((unsigned char)c);
                    maNV[len++] = c;
                    maNV[len] = '\0';
                    gotoxy(xMa + len - 1, yMa); cout << c;
                }
            }
        }
    }
}


void InDanhSachNhanVienTheoTuKhoa(DSNHANVIEN ds, int start, const char tuKhoa[]) {
    int y = 2;
    int pageSize = 15;

    clearArea(2, 2, 58, 25);

    gotoxy(2, y);   cout << "Ma NV";
    gotoxy(16, y);  cout << "Ho";
    gotoxy(34, y);  cout << "Ten";
    gotoxy(50, y);  cout << "Phai";

    gotoxy(2, y + 1);
    for (int i = 0; i < 58; i++) cout << '-';

    NHANVIEN* loc[MAXNV];
    int nLoc = 0;

    for (int i = 0; i < ds.n; i++) {
        if (BatDauBang(ds.nv[i]->TEN, tuKhoa)) {
            loc[nLoc++] = ds.nv[i];
        }
    }

    if (nLoc == 0) {
        gotoxy(2, y + 3);
        cout << "Khong co nhan vien nao co TEN bat dau bang: " << tuKhoa;

        clearLine(2, y + pageSize + 3, 58);
        gotoxy(2, y + pageSize + 3);
        cout << "Trang: 1/1";

        clearLine(2, y + pageSize + 5, 58);
		gotoxy(2, y + pageSize + 5);
		cout << "[>] Trang sau	[<] Trang truoc	[ESC] Thoat";
		gotoxy(2,y+pageSize+6);
		cout << "[F2] Them NV	[F3] Sua NV	[F4] Xoa NV";

        clearLine(2, y + pageSize + 7, 58);
        gotoxy(2, y + pageSize + 7);
        cout << "Loc TEN: " << tuKhoa << "   [Backspace] Xoa 1 ky tu";
        return;
    }

    if (start < 0) start = 0;
    if (start >= nLoc) start = (nLoc - 1) / pageSize * pageSize;

    for (int i = start; i < start + pageSize && i < nLoc; i++) {
        int row = y + 2 + (i - start);

        clearLine(2, row, 58);

        printAt(2,  row, loc[i]->MANV, 12);
        printAt(16, row, loc[i]->HO,   16);
        printAt(34, row, loc[i]->TEN,  14);
        printAt(50, row, loc[i]->PHAI, 8);
    }

    int soDongTrang = nLoc - start;
    if (soDongTrang > pageSize) soDongTrang = pageSize;

    for (int row = y + 2 + soDongTrang; row < y + 2 + pageSize; row++) {
        clearLine(2, row, 58);
    }

    int totalPages = (nLoc + pageSize - 1) / pageSize;
    int currentPage = start / pageSize + 1;

    clearLine(2, y + pageSize + 3, 58);
    gotoxy(2, y + pageSize + 3);
    cout << "Trang: " << currentPage << "/" << totalPages;

    clearLine(2, y + pageSize + 5, 58);
    gotoxy(2, y + pageSize + 5);
    cout << "[>] Trang sau	[<] Trang truoc	[ESC] Thoat";
    gotoxy(2,y+pageSize+6);
	cout << "[F2] Them NV	[F3] Sua NV	[F4] Xoa NV";

    clearLine(2, y + pageSize + 7, 58);
    gotoxy(2, y + pageSize + 7);
    cout << "Loc TEN: " << tuKhoa << "   [Backspace] Xoa 1 ky tu";
}
void InDanhSachVatTuTheoTuKhoa(TREE root, int start, const char tuKhoa[]) {
    VATTU a[1000];
    VATTU loc[1000];
    int n = 0, nLoc = 0;
    int pageSize = 15;
    int y = 2;

    ChepCayRaMang(root, a, n);
    SapXepTheoTen(a, n);

    for (int i = 0; i < n; i++) {
        if (BatDauBang(a[i].TENVT, tuKhoa)) {
            loc[nLoc++] = a[i];
        }
    }

    clearArea(2, 2, 60, 24);

    gotoxy(2, y);   cout << "Ma VT";
    gotoxy(14, y);  cout << "Ten VT";
    gotoxy(36, y);  cout << "DVT";
    gotoxy(48, y);  cout << "SLT";

    gotoxy(2, y + 1);
    for (int i = 0; i < 58; i++) cout << '-';

    if (nLoc == 0) {
        gotoxy(2, y + 3);
        cout << "Khong co vat tu nao co TENVT bat dau bang: " << tuKhoa;

        clearLine(2, y + pageSize + 3, 58);
        gotoxy(2, y + pageSize + 3);
        cout << "Trang: 1/1";

        clearLine(2, y + pageSize + 4, 58);
        gotoxy(2, y + pageSize + 4);
        cout << "[>] Trang sau   [<] Trang truoc	[ESC] Thoat";

        clearLine(2, y + pageSize + 5, 58);
        gotoxy(2, y + pageSize + 5);
        cout << "[F2] Them VT    [F3] Sua VT   	[F4] Xoa VT";

        clearLine(2, y + pageSize + 6, 58);
        gotoxy(2, y + pageSize + 6);
        cout << "Loc TENVT: " << tuKhoa << "   [Backspace] Xoa 1 ky tu";
        return;
    }

    if (start < 0) start = 0;
    if (start >= nLoc) start = (nLoc - 1) / pageSize * pageSize;

    for (int i = start; i < start + pageSize && i < nLoc; i++) {
        int row = y + 2 + (i - start);

        clearLine(2, row, 58);

        printAt(2,  row, loc[i].MAVT, 10);
        printAt(14, row, loc[i].TENVT, 20);
        printAt(36, row, loc[i].DVT,   10);
        gotoxy(48, row);
        cout << loc[i].SLT << "      ";
    }

    int soDongTrang = nLoc - start;
    if (soDongTrang > pageSize) soDongTrang = pageSize;

    for (int row = y + 2 + soDongTrang; row < y + 2 + pageSize; row++) {
        clearLine(2, row, 58);
    }

    int totalPages = (nLoc + pageSize - 1) / pageSize;
    int currentPage = start / pageSize + 1;

    clearLine(2, y + pageSize + 3, 58);
    gotoxy(2, y + pageSize + 3);
    cout << "Trang: " << currentPage << "/" << totalPages;

    clearLine(2, y + pageSize + 4, 58);
    gotoxy(2, y + pageSize + 4);
    cout << "[>] Trang sau   [<] Trang truoc	[ESC] Thoat";

    clearLine(2, y + pageSize + 5, 58);
    gotoxy(2, y + pageSize + 5);
    cout << "[F2] Them VT    [F3] Sua VT   	[F4] Xoa VT";

    clearLine(2, y + pageSize + 6, 58);
    gotoxy(2, y + pageSize + 6);
    cout << "Loc TENVT: " << tuKhoa << "   [Backspace] Xoa 1 ky tu";
}
void InChiTietHoaDon(TREE root, DSHD pHD, NHANVIEN *nv) {
    HOADON &hd = pHD->data;
    const int pageSize = 10;   // 10 dong / trang cho de nhin
    int start = 0;

    while (true) {
        clearArea(1, 1, 125, 35);

        char ngay[20];
        DinhDangNgay(hd.Ngaylap, ngay);

        gotoxy(2, 1);  cout << "CHI TIET HOA DON";
        gotoxy(2, 3);  cout << "So HD      : " << hd.SoHD;
        gotoxy(2, 4);  cout << "Ngay lap   : " << ngay;
        gotoxy(2, 5);  cout << "Nguoi lap  : " << nv->HO << " " << nv->TEN;
        gotoxy(2, 6);  cout << "Loai HD    : " << hd.Loai;

        gotoxy(2, 8);  cout << "Ten VT";
        gotoxy(32, 8); cout << "SL";
        gotoxy(42, 8); cout << "Don gia";
        gotoxy(58, 8); cout << "Tri gia";

        gotoxy(2, 9);
        for (int i = 0; i < 75; i++) cout << '-';

        long double tong = TongTriGiaHoaDon(hd);

        // chong start vuot bien
        if (start < 0) start = 0;
        if (start >= hd.dscthd.n) {
            start = ((hd.dscthd.n - 1) / pageSize) * pageSize;
            if (start < 0) start = 0;
        }

        // in 1 trang chi tiet
        for (int i = start; i < start + pageSize && i < hd.dscthd.n; i++) {
            int row = 10 + (i - start);
            CT_HOADON &ct = hd.dscthd.ct[i];

            TREE pVT = TimVT(root, ct.MAVT);

            char tenVT[30];
            if (pVT != NULL) strcpy(tenVT, pVT->data.TENVT);
            else strcpy(tenVT, "[Khong tim thay VT]");

            long double triGia = ThanhTienCT(ct);

            clearLine(2, row, 90);
            printAt(2, row, tenVT, 28);
            gotoxy(32, row); cout << ct.Soluong << "      ";
            gotoxy(42, row); cout << ct.Dongia << "        ";
            gotoxy(58, row); cout << fixed << setprecision(0) << triGia << "        ";
        }

        // xoa dong du neu trang cu nhieu hon trang moi
        for (int row = 10 + (hd.dscthd.n - start < pageSize ? hd.dscthd.n - start : pageSize);
             row < 10 + pageSize; row++) {
            clearLine(2, row, 90);
        }

        gotoxy(2, 22);
        cout << "Tong tri gia HD: " << fixed << setprecision(0) << tong << "        ";

        int totalPages = (hd.dscthd.n == 0 ? 1 : (hd.dscthd.n + pageSize - 1) / pageSize);
        int currentPage = (hd.dscthd.n == 0 ? 1 : start / pageSize + 1);

        clearLine(2, 24, 90);
        gotoxy(2, 24);
        cout << "Trang: " << currentPage << "/" << totalPages;

        clearLine(2, 25, 110);
        gotoxy(2, 25);
        cout << "[<-] Trang truoc   [->] Trang sau   [ESC/ENTER] Quay lai";

        int c = getch();

        if (c == 0 || c == 224 || c == -32) {
            int key = getch();

            if (key == 75) { // trai
                if (start - pageSize >= 0) {
                    start -= pageSize;
                }
            }
            else if (key == 77) { // phai
                if (start + pageSize < hd.dscthd.n) {
                    start += pageSize;
                }
            }

            // khong thoat, lap lai de ve trang moi
            continue;
        }
        else if (c == 27 || c == 13) { // ESC hoac ENTER
            return;
        }
        else {
            // phim thuong khac: cho quay lai cung duoc
            return;
        }
    }
}
void ChuyenTrang(int &start, int pageSize, int tongSoDong, int phim) {
    if (phim == 75) { // trai
        start -= pageSize;
        if (start < 0) start = 0;
    }
    else if (phim == 77) { // phai
        start += pageSize;
        if (start >= tongSoDong) {
            start -= pageSize;
            if (start < 0) start = 0;
        }
    }
}
void InHoaDonUI(TREE root, DSNHANVIEN ds) {
    const int pageSize = 15;
    const int y = 2;

    int selected = 0;   // chi so that trong mang loc
    int start = 0;      // chi so dau trang

    char tuKhoaLoc[MAX_TEN + 1];
    int lenLoc = 0;
    tuKhoaLoc[0] = '\0';

    ITEM_HD a[MAXTEMP];
    int n = TaoMangHoaDonLoc(ds, tuKhoaLoc, a);

    VeDanhSachHoaDon(a, n, start, selected, tuKhoaLoc);

    while (true) {
        int c = getch();

        if (c == 27) {
            XoaManHinh();
            return;
        }
        else if (c == 13) {
            if (n > 0) {
                InChiTietHoaDon(root, a[selected].hd, a[selected].nv);

                // ve lai danh sach sau khi xem xong chi tiet
                n = TaoMangHoaDonLoc(ds, tuKhoaLoc, a);

                if (n == 0) {
                    selected = 0;
                    start = 0;
                } else {
                    if (selected >= n) selected = n - 1;
                    if (start > selected) start = (selected / pageSize) * pageSize;
                }

                VeDanhSachHoaDon(a, n, start, selected, tuKhoaLoc);
            }
        }
        else if (c == 0 || c == 224 || c == -32) {
            int key = getch();

            if (n <= 0) continue;

            int oldSelected = selected;
            int oldStart = start;

            if (key == 72) { // len
                if (selected > 0) {
                    selected--;
                    if (selected < start) {
                        start -= pageSize;
                        if (start < 0) start = 0;
                    }
                }
            }
            else if (key == 80) { // xuong
                if (selected < n - 1) {
                    selected++;
                    if (selected >= start + pageSize) {
                        start += pageSize;
                    }
                }
            }
            else if (key == 75) { // trang truoc
                if (start - pageSize >= 0) {
                    int offset = selected - start;   // giu vi tri tuong doi trong trang
                    start -= pageSize;
                    selected = start + offset;
                    if (selected >= n) selected = n - 1;
                }
            }
            else if (key == 77) { // trang sau
                if (start + pageSize < n) {
                    int offset = selected - start;   // giu vi tri tuong doi trong trang
                    start += pageSize;
                    selected = start + offset;
                    if (selected >= n) selected = n - 1;
                }
            }

            // doi trang -> ve lai ca bang
            if (start != oldStart) {
                VeDanhSachHoaDon(a, n, start, selected, tuKhoaLoc);
            }
            // chi doi dong trong cung 1 trang -> chi doi dau '>'
            else if (selected != oldSelected) {
                int oldRow = y + 2 + (oldSelected - start);
                int newRow = y + 2 + (selected - start);

                gotoxy(3, oldRow); cout << ' ';
                gotoxy(3, newRow); cout << '>';
            }
        }
        else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            if (lenLoc < MAX_TEN) {
                c = toupper((unsigned char)c);
                tuKhoaLoc[lenLoc++] = (char)c;
                tuKhoaLoc[lenLoc] = '\0';

                n = TaoMangHoaDonLoc(ds, tuKhoaLoc, a);
                selected = 0;
                start = 0;

                VeDanhSachHoaDon(a, n, start, selected, tuKhoaLoc);
            }
        }
        else if (c == 8) {
            if (lenLoc > 0) {
                lenLoc--;
                tuKhoaLoc[lenLoc] = '\0';

                n = TaoMangHoaDonLoc(ds, tuKhoaLoc, a);
                selected = 0;
                start = 0;

                VeDanhSachHoaDon(a, n, start, selected, tuKhoaLoc);
            }
        }
    }
}
void NV(DSNHANVIEN &dsnv) {
    int start = 0;
    int pageSize = 15;

    bool dangLoc = false;
    char tuKhoaLoc[MAX_TEN + 1];
    int lenLoc = 0;
    tuKhoaLoc[0] = '\0';

    XoaManHinh();
    InDanhSachNhanVien(dsnv, start);

    while (true) {
        int c = getch();

        
        if (c == 0 || c == 224 || c == -32) {
            char f = getch();

  
            if (f == 60) {
                while (true) {
                    if (!NhapThongTinNV(dsnv)) break;
                    SaveDSNVToFile(dsnv);
                    start = 0;

                    if (dangLoc)
                        InDanhSachNhanVienTheoTuKhoa(dsnv, start, tuKhoaLoc);
                    else
                        InDanhSachNhanVien(dsnv, start);
                }
            }

            // ===== F3: S?A =====
            else if (f == 61) {
                SuaNV(dsnv, start);
                SaveDSNVToFile(dsnv);

                if (dangLoc)
                    InDanhSachNhanVienTheoTuKhoa(dsnv, start, tuKhoaLoc);
                else
                    InDanhSachNhanVien(dsnv, start);
            }

            else if (f == 62) {
                XoaNV(dsnv, start);
                SaveDSNVToFile(dsnv);

                if (dangLoc)
                    InDanhSachNhanVienTheoTuKhoa(dsnv, start, tuKhoaLoc);
                else
                    InDanhSachNhanVien(dsnv, start);
            }


            else if (f == 77) {
                start += pageSize;

                if (dangLoc) {
                    InDanhSachNhanVienTheoTuKhoa(dsnv, start, tuKhoaLoc);
                } else {
                    if (start >= dsnv.n) start -= pageSize;
                    InDanhSachNhanVien(dsnv, start);
                }
            }

            else if (f == 75) {
                start -= pageSize;
                if (start < 0) start = 0;

                if (dangLoc)
                    InDanhSachNhanVienTheoTuKhoa(dsnv, start, tuKhoaLoc);
                else
                    InDanhSachNhanVien(dsnv, start);
            }
        }

        else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            if (lenLoc < MAX_TEN) {
                c = toupper((unsigned char)c);
                tuKhoaLoc[lenLoc++] = c;
                tuKhoaLoc[lenLoc] = '\0';

                dangLoc = true;
                start = 0;

                InDanhSachNhanVienTheoTuKhoa(dsnv, start, tuKhoaLoc);
            }
        }

        // ===================== BACKSPACE =====================
        else if (c == 8) {
            if (lenLoc > 0) {
                lenLoc--;
                tuKhoaLoc[lenLoc] = '\0';

                start = 0;

                if (lenLoc == 0) {
                    dangLoc = false;
                    InDanhSachNhanVien(dsnv, start);
                } else {
                    InDanhSachNhanVienTheoTuKhoa(dsnv, start, tuKhoaLoc);
                }
            }
        }

        // ===================== ESC =====================
        else if (c == 27) {
        	XoaThongBaoChung();
            XoaManHinh();
            break;
        }
    }
}
void QuanLyVatTu(TREE &root, VATTU &x,DSNHANVIEN dsnv) {
    int start = 0;
    int pageSize = 15;

    bool dangLoc = false;
    char tuKhoaLoc[MAX_TENVT + 1];
    int lenLoc = 0;
    tuKhoaLoc[0] = '\0';

    XoaManHinh();
    InDanhSachVatTuTonKho(root, start);

    while (true) {
        int c = getch();

        if (c == 0 || c == 224 || c == -32) {
            char f = getch();

            switch (f) {

            case 60: // F2
            {
                VATTU xMoi;
                while (true) {
                    if (!NhapThongTinVT(root, xMoi)) break;
                    ThemVTVaoCay(root, xMoi);
                    LuuFileVatTu(root);

                    start = 0;
                    if (dangLoc) InDanhSachVatTuTheoTuKhoa(root, start, tuKhoaLoc);
                    else InDanhSachVatTuTonKho(root, start);
                }
                break;
            }

            case 61: // F3
            {
                SuaVT(root);
                LuuFileVatTu(root);

                if (dangLoc) InDanhSachVatTuTheoTuKhoa(root, start, tuKhoaLoc);
                else InDanhSachVatTuTonKho(root, start);
                break;
            }

            case 62: // F4
            {
                XoaVatTuUI(root, start,dsnv);
                LuuFileVatTu(root);

                if (dangLoc) InDanhSachVatTuTheoTuKhoa(root, start, tuKhoaLoc);
                else InDanhSachVatTuTonKho(root, start);
                break;
            }

            case 75: // ? tr�i
            {
                start -= pageSize;
                if (start < 0) start = 0;

                if (dangLoc)
                    InDanhSachVatTuTheoTuKhoa(root, start, tuKhoaLoc);
                else
                    InDanhSachVatTuTonKho(root, start);
                break;
            }

            case 77: // ? ph?i
            {
                start += pageSize;

                if (dangLoc)
                    InDanhSachVatTuTheoTuKhoa(root, start, tuKhoaLoc);
                else
                    InDanhSachVatTuTonKho(root, start);
                break;
            }
            }
        }

        else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            if (lenLoc < MAX_TENVT) {
                tuKhoaLoc[lenLoc++] = c;
                tuKhoaLoc[lenLoc] = '\0';
                dangLoc = true;
                start = 0;

                InDanhSachVatTuTheoTuKhoa(root, start, tuKhoaLoc);
            }
        }

        else if (c == 8) { // Backspace
            if (lenLoc > 0) {
                lenLoc--;
                tuKhoaLoc[lenLoc] = '\0';

                if (lenLoc == 0) {
                    dangLoc = false;
                    start = 0;
                    InDanhSachVatTuTonKho(root, start);
                }
                else {
                    start = 0;
                    InDanhSachVatTuTheoTuKhoa(root, start, tuKhoaLoc);
                }
            }
        }

        else if (c == 27) { // ESC
        	XoaThongBaoChung();
            XoaManHinh();
            break;
        }
    }
}
void QuanLyChinh(TREE &root, DSNHANVIEN &dsnv,VATTU &x) {
    while (true) {
        int chon = MenuChinh();

        if (chon == 0) {
            XoaManHinh();
            break;
        }

        switch (chon) {
            case 1:
                QuanLyVatTu(root,x,dsnv);      
                break;

            case 2:
                NV(dsnv);    
                break;
            case 3:
                HD(root, dsnv); 
                break;
            case 4:
            	InHoaDonUI(root,dsnv);
            	break;
        }
    }
}

int main() {
	system("mode con cols=140 lines=40");
	
    TREE root;
    InitTree(root);
    DSNHANVIEN dsnv;
    InitDSNV(dsnv);
	LoadDSNVFromFile(dsnv);
    LoadVatTuFromFile(root);


	HOADON hd;
    int choice;
    VATTU x;
    char ma[MAX_MAVT];
	
	QuanLyChinh(root,dsnv,x);
    



    return 0;
}



