#include <iostream>
#include <cstring>			//16h 11/04
#include <iomanip>
#include <fstream>
#include <conio.h>			//Sang mai, sửa phần hiệu chỉnh vật tư....
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



struct Date {
    int day;
    int month;
    int year;
};

struct CT_HOADON {
    char MAVT[MAX_MAVT + 1];
    int Soluong;
    long Dongia;
    int VAT;
};

struct DSCTHD {
    int n;
    CT_HOADON ct[MAXCTHD];
};

struct HOADON {
    char SoHD[MAX_SOHD + 1];
    Date Ngaylap;
    char Loai;
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

void SaveVatTuToFile(TREE root, ofstream &f) {
    if (root == NULL) return;

    SaveVatTuToFile(root->left, f);
    f << root->data.MAVT << '|'
      << root->data.TENVT << '|'
      << root->data.DVT << '|'
      << root->data.SLT << endl;
    SaveVatTuToFile(root->right, f);
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
        gotoxy(x, y + i);        // đi từng dòng
        for (int j = 0; j < w; j++) {
            cout << ' ';         // in khoảng trắng để xóa
        }
    }
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
int KiemTraSoHoaDon(char ma[]){
	return KiemTraMa(ma,11);
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

void InTieuDe() {
    cout << left
         << setw(10) << "Ma VT"
         << setw(25) << "Ten vat tu"
         << setw(20) << "Don vi tinh"
         << setw(15) << "So luong ton"
         << endl;

    cout << setfill('-') << setw(70) << "" << endl;
    cout << setfill(' ');
}

void InDongVatTu(TREE root) {
	if(root == NULL){
		return;
	}
	InDongVatTu(root->left);
	    cout << left
	         << setw(10) << root->data.MAVT
	         << setw(25) <<	root->data.TENVT
	         << setw(20) << root->data.DVT
	         << setw(15) << root->data.SLT
	         << endl;
	InDongVatTu(root->right);}


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


int ThemVT(TREE &root, VATTU x) {
    if (root == NULL) {
        root = TaoNodeVT(x);
        return 1;
    }

    int cmp = strcmp(x.MAVT, root->data.MAVT);

    if (cmp == 0) {
        return 0; // trung ma
    }

    if (cmp < 0) return ThemVT(root->left, x);
    return ThemVT(root->right, x);
}
void SaveNhanVienToFile(DSNHANVIEN ds) {
    ofstream f("nhanvien.txt");

    for (int i = 0; i < ds.n; i++) {
        f << ds.nv[i]->MANV << '|'
          << ds.nv[i]->HO << '|'
          << ds.nv[i]->TEN << '|'
          << ds.nv[i]->PHAI << endl;
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
        cout << "[N] Trang sau	[P] Trang truoc		[ESC] Thoat";
        clearLine(2,y+ pageSize+5,58);
	    gotoxy(2,y+pageSize +5);
	    cout<< "[F2] Them VT	[F3] Hieu Chinh VT	[F4] Xoa VT";
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
    cout << "[N] Trang sau	[P] Trang truoc		[ESC] Thoat";
    clearLine(2,y+ pageSize+5,8);
    gotoxy(2,y+pageSize +5);
    cout<< "[F2] Them VT	[F3] Hieu Chinh VT	[F4] Xoa VT";
}
void LoadNhanVienFromFile(DSNHANVIEN &ds) {
    ifstream f("nhanvien.txt");
    if (!f.is_open()) return;

    while (!f.eof()) {
        NHANVIEN *p = new NHANVIEN;

        f.getline(p->MANV, MAX_MANV + 1, '|');
        f.getline(p->HO, MAX_HO + 1, '|');
        f.getline(p->TEN, MAX_TEN + 1, '|');
        f.getline(p->PHAI, MAX_PHAI + 1);

        if (strlen(p->MANV) == 0) {
            delete p;
            break;
        }

        p->dshd = NULL;
        ds.nv[ds.n++] = p;
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

        ThemVT(root, x);
    }

    f.close();
}

void XoaXuongDong(char s[]) {
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
    }
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
                clearLine(65, 18, 45);
                gotoxy(65, 18);
                cout << "Da huy nhap vat tu.";
                clearArea(65,3,45,16);
                return false;
            }
            else if (c == 13) { // ENTER
                x.MAVT[len] = '\0';

                if (len == 0) {
                    clearLine(65, 18, 45);
                    gotoxy(65, 18);
                    cout << "Ma vat tu khong duoc rong.";
                    break;
                }

                if (!KiemTraMaVT(x.MAVT)) {
                    clearLine(65, 18, 45);
                    gotoxy(65, 18);
                    cout << "Ma khong hop le.";
                    break;
                }

                UpperCase(x.MAVT);

                if (KiemTraTrungMaVT(root, x.MAVT)) {
                    clearLine(65, 18, 45);
                    gotoxy(65, 18);
                    cout << "Ma da ton tai.";
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
                clearLine(65, 18, 45);
                gotoxy(65, 18);
                cout << "Da huy nhap vat tu.";
                return false;
            }
            else if (c == 13) { // ENTER
                x.TENVT[len] = '\0';

                XoaKhoangTrangDauCuoi(x.TENVT);
                ChuanHoaKhoangTrang(x.TENVT);
                VietHoaChuCaiDau(x.TENVT);

                if (strlen(x.TENVT) == 0) {
                    clearLine(65, 18, 45);
                    gotoxy(65, 18);
                    cout << "Ten vat tu khong duoc rong.";
                    break;
                }

                if (!KiemTraTenVatTu(x.TENVT)) {
                    clearLine(65, 18, 45);
                    gotoxy(65, 18);
                    cout << "Ten vat tu khong hop le.";
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
                clearLine(65, 18, 45);
                gotoxy(65, 18);
                cout << "Da huy nhap vat tu.";
                return false;
            }
            else if (c == 13) { // ENTER
                x.DVT[len] = '\0';

                XoaKhoangTrangDauCuoi(x.DVT);
                ChuanHoaKhoangTrang(x.DVT);

                if (strlen(x.DVT) == 0) {
                    clearLine(65, 18, 45);
                    gotoxy(65, 18);
                    cout << "Don vi tinh khong duoc rong.";
                    break;
                }

                if (!KiemTraDVT(x.DVT)) {
                    clearLine(65, 18, 45);
                    gotoxy(65, 18);
                    cout << "Don vi tinh khong hop le.";
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
                clearLine(65, 18, 45);
                gotoxy(65, 18);
                cout << "Da huy nhap vat tu.";
                return false;
            }
            else if (c == 13) { // ENTER
                sSLT[len] = '\0';

                if (len == 0) {
                    clearLine(65, 18, 45);
                    gotoxy(65, 18);
                    cout << "So luong ton khong duoc rong.";
                    break;
                }

                x.SLT = atoi(sSLT);
                clearLine(65, 18, 45);
                gotoxy(65, 18);
                cout << "Nhap vat tu thanh cong.";
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


void VeFormSuaVTCoBan() {
    gotoxy(65, 3);  cout << "| Ma VT : [__________] |";
    gotoxy(65, 5);  cout << "| Ten VT: [____________________] |";
    gotoxy(65, 7);  cout << "| DVT   : [__________] |";
    gotoxy(65, 9);  cout << "| SLT   : [__________] |";
}

void XoaVungSuaVT() {
    clearArea(65, 1, 55, 22);
}
//
void HieuChinhVT(TREE root) {
	int start =0;
    if (root == NULL) {
        gotoxy(65, 2);
        cout << "Danh sach vat tu rong. Nhan phim bat ky de quay lai...";
        getch();
        return;
    }

    TREE p = NULL;
    char maVT[MAX_MAVT + 1];
    char c;
    int len;

    int xMa  = 76, yMa  = 3;
    int xTen = 76, yTen = 5;
    int xDVT = 76, yDVT = 7;
    int xSLT = 76, ySLT = 9;

TIM_VAT_TU:	
    XoaVungSuaVT();
	
    gotoxy(65, 1);
    cout << "Nhap ma VT muon sua (ESC de thoat):";

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
            gotoxy(65, 2);
            cout << "Da thoat hieu chinh vat tu.";
            return;
        }
        else if (c == 13) { // ENTER
            maVT[len] = '\0';
            XoaKhoangTrangDauCuoi(maVT);
            UpperCase(maVT);

            if (strlen(maVT) == 0) {
                clearLine(65, 12, 50);
                gotoxy(65, 12);
                cout << "Ma vat tu khong duoc rong.";
                clearLine(xMa, yMa, 10);
                gotoxy(xMa, yMa);
                len = 0;
                maVT[0] = '\0';
                continue;
            }

            if (!KiemTraMaVT(maVT)) {
                clearLine(65, 12, 50);
                gotoxy(65, 12);
                cout << "Ma vat tu khong hop le.";
                clearLine(xMa, yMa, 10);
                gotoxy(xMa, yMa);
                len = 0;
                maVT[0] = '\0';
                continue;
            }

            p = TimVT(root, maVT);
            if (p == NULL) {
                clearLine(65, 12, 50);
                gotoxy(65, 12);
                cout << "Khong tim thay vat tu.";
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

    gotoxy(65, 1);
    cout << "Thong tin vat tu can sua:";

    VeFormSuaVTCoBan();

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
            return;
        }
        else if (c == '1') {
            char tenMoi[MAX_TENVT + 1];
            len = 0;
            tenMoi[0] = '\0';

            clearLine(65, 17, 50);
            gotoxy(65, 17);
            cout << "Nhap Ten VT moi, ENTER de luu, ESC de huy";

            clearLine(xTen, yTen, 20);
            gotoxy(xTen, yTen);


            while (true) {
                c = getch();

                if (c == 27) { // ESC
                    clearLine(xTen, yTen, 20);
                    gotoxy(xTen, yTen);
                    cout << p->data.TENVT;

                    clearLine(65, 17, 50);
                    goto MENU_SUA;
                }
                else if (c == 13) { // ENTER
                    tenMoi[len] = '\0';

                    XoaKhoangTrangDauCuoi(tenMoi);
                    ChuanHoaKhoangTrang(tenMoi);
                    VietHoaChuCaiDau(tenMoi);

                    if (strlen(tenMoi) == 0) {
                        clearLine(65, 17, 50);
                        gotoxy(65, 17);
                        cout << "Ten vat tu khong duoc rong.";
                        clearLine(xTen, yTen, 20);
                        gotoxy(xTen, yTen);
                        len = 0;
                        tenMoi[0] = '\0';
                        
                        continue;
                    }

                    if (!KiemTraTenVatTu(tenMoi)) {
                        clearLine(65, 17, 50);
                        gotoxy(65, 17);
                        cout << "Ten vat tu khong hop le.";
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

                    clearLine(65, 17, 50);
                    gotoxy(65, 17);
                    cout << "Da cap nhat Ten VT.";
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

            clearLine(65, 17, 50);
            gotoxy(65, 17);
            cout << "Nhap DVT moi, ENTER de luu, ESC de huy";

            clearLine(xDVT, yDVT, 10);
            gotoxy(xDVT, yDVT);

            while (true) {
                c = getch();

                if (c == 27) { // ESC
                    clearLine(xDVT, yDVT, 10);
                    gotoxy(xDVT, yDVT);
                    cout << p->data.DVT;

                    clearLine(65, 17, 50);
                    goto MENU_SUA;
                }
                else if (c == 13) { // ENTER
                    dvtMoi[len] = '\0';

                    XoaKhoangTrangDauCuoi(dvtMoi);
                    ChuanHoaKhoangTrang(dvtMoi);

                    if (strlen(dvtMoi) == 0) {
                        clearLine(65, 17, 50);
                        gotoxy(65, 17);
                        cout << "Don vi tinh khong duoc rong.";
                        clearLine(xDVT, yDVT, 10);
                        gotoxy(xDVT, yDVT);
                        len = 0;
                        dvtMoi[0] = '\0';
                        continue;
                    }

                    if (!KiemTraDVT(dvtMoi)) {
                        clearLine(65, 17, 50);
                        gotoxy(65, 17);
                        cout << "Don vi tinh khong hop le.";
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

                    clearLine(65, 17, 50);
                    gotoxy(65, 17);
                    cout << "Da cap nhat DVT.";
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
   
void NodeThayThe(TREE &p, TREE &temp) {	
    if (temp->left != NULL) {
        NodeThayThe(p, temp->left);
    } else {
        p->data = temp->data;
        p = temp;
        temp = temp->right;
    }
}

int RemoveVT(TREE &root, const char maVT[]) {
    if (root == NULL) return 0;

    int cmp = strcmp(maVT, root->data.MAVT);

    if (cmp < 0) return RemoveVT(root->left, maVT);
    if (cmp > 0) return RemoveVT(root->right, maVT);

    TREE p = root;

    if (root->left == NULL) {
        root = root->right;
    } else if (root->right == NULL) {
        root = root->left;
    } else {
        NodeThayThe(p, root->right);
    }

    delete p;
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
    cout << "[N] Trang sau   [P] Trang truoc   [ESC] Thoat";
    gotoxy(2,y+pageSize+6);
	cout<<"[F2] Them Nhan Vien";
    
}


bool ThemNhanVien(DSNHANVIEN &ds) {
    if (ds.n >= MAXNV) {
        gotoxy(70, 18);
        cout << "Danh sach nhan vien da day.";
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
    gotoxy(70, 9); cout << "| Phai   : 	[1.Nam 2.Nu] |";

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
                clearLine(70, 18, 60);
                gotoxy(70, 18);
                cout << "Da huy them nhan vien.";
                delete p;
                return false;
            }
            else if (c == 13) { // ENTER
                maTam[len] = '\0';
                XoaKhoangTrangDauCuoi(maTam);
                UpperCase(maTam);

                if (strlen(maTam) == 0) {
                    clearLine(70, 18, 60);
                    gotoxy(70, 18);
                    cout << "Ma nhan vien khong duoc rong.";
                    break;
                }

                if (!KiemTraMaNV(maTam)) {
                    clearLine(70, 18, 60);
                    gotoxy(70, 18);
                    cout << "Ma nhan vien khong hop le.";
                    break;
                }

                // Neu ham cua em: true = khong trung, false = trung
                if (!KiemTraTrungMANV(ds, maTam)) {
                    clearLine(70, 18, 60);
                    gotoxy(70, 18);
                    cout << "Ma nhan vien da ton tai.";
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
                clearLine(70, 18, 60);
                gotoxy(70, 18);
                cout << "Da huy them nhan vien.";
                delete p;
                return false;
            }
            else if (c == 13) { // ENTER
                hoTam[len] = '\0';
                XoaKhoangTrangDauCuoi(hoTam);
                ChuanHoaKhoangTrang(hoTam);
                ChuanHoaHoTen(hoTam);

                if (strlen(hoTam) == 0) {
                    clearLine(70, 18, 60);
                    gotoxy(70, 18);
                    cout << "Ho khong duoc rong.";
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
                    clearLine(70, 18, 60);
                    gotoxy(70, 18);
                    cout << "Ho khong hop le.";
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
            	
                clearLine(70, 18, 60);
                gotoxy(70, 18);
                cout << "Da huy them nhan vien.";
                delete p;
                return false;
            }
            else if (c == 13) { // ENTER
                tenTam[len] = '\0';
                XoaKhoangTrangDauCuoi(tenTam);
                ChuanHoaKhoangTrang(tenTam);
                ChuanHoaHoTen(tenTam);

                if (strlen(tenTam) == 0) {
                    clearLine(70, 18, 60);
                    gotoxy(70, 18);
                    cout << "Ten khong duoc rong.";
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
                    clearLine(70, 18, 60);
                    gotoxy(70, 18);
                    cout << "Ten khong hop le.";
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
        clearLine(xPhai, yPhai, 5);
        gotoxy(xPhai, yPhai);

        c = getch();

        if (c == 27) { // ESC
            gotoxy(70, 18);
            cout << "Da huy them nhan vien.";
            delete p;
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
            clearLine(70, 18, 60);
            gotoxy(70, 18);
            cout << " chi duoc chon 1 hoac 2.";
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

    clearLine(70, 18, 60);
    gotoxy(70, 18);
    cout << "Them nhan vien thanh cong.";
    return true;
}
void ThemHoaDonVaoCuoi(DSHD &dshd, HOADON hd) {
    NodeHD* p = TaoNodeHD(hd);

    if (dshd == NULL) {
        dshd = p;
        return;
    }

    NodeHD* q = dshd;
    while (q->next != NULL)
        q = q->next;

    q->next = p;
}
int KiemTraTrungSoHD(DSNHANVIEN ds, const char sohd[]) {
    for (int i = 0; i < ds.n; i++) {
        DSHD p = ds.nv[i]->dshd;
        while (p != NULL) {
            if (strcmp(p->data.SoHD, sohd) == 0)
                return 1;
            p = p->next;
        }
    }
    return 0;
}
void CapNhatTonKho(TREE root, HOADON hd) {
    for (int i = 0; i < hd.dscthd.n; i++) {
        TREE p = TimVT(root, hd.dscthd.ct[i].MAVT);

        if (hd.Loai == 'N')
            p->data.SLT += hd.dscthd.ct[i].Soluong;
        else
            p->data.SLT -= hd.dscthd.ct[i].Soluong;
    }
}
void NhapMotCTHD(TREE root, HOADON &hd, int i) {
    CT_HOADON &ct = hd.dscthd.ct[i];

    while (true) {
        cout << "Nhap ma vat tu: ";
        cin.getline(ct.MAVT, MAX_MAVT + 1);
        KiemTraMaVT(ct.MAVT);
        UpperCase(ct.MAVT);
        KiemTraTrungMaVT(root, ct.MAVT);
        
        TREE p = TimVT(root, ct.MAVT);
        if (p == NULL) {
            cout << "Khong ton tai vat tu\n";
            continue;
        }

        cout << "Nhap so luong: ";
        ct.Soluong = NhapSoNguyenKhongAm();

        if (hd.Loai == 'X' && ct.Soluong > p->data.SLT) {
            cout << "Khong du hang\n";
            continue;
        }

        cout << "Nhap don gia: ";
        ct.Dongia = NhapSoNguyenKhongAm();
		
        cout << "Nhap VAT: ";						
        ct.VAT = NhapSoNguyenKhongAm();
		
        break;
    }
}
void LapHoaDon(TREE root, DSNHANVIEN &dsnv) {
    char maNV[MAX_MANV + 1];

    cout << "Nhap ma nhan vien: ";
    cin.getline(maNV, MAX_MANV + 1);
    KiemTraMaNV(maNV);
    UpperCase(maNV);
	
    NHANVIEN* nv = TimNhanVienTheoMa(dsnv, maNV);
    if (nv == NULL) {
        cout << "Khong tim thay nhan vien\n";
        return;
    }

    HOADON hd;
    hd.dscthd.n = 0;

    // So hoa don
    do {
        cout << "Nhap so hoa don: ";
        cin.getline(hd.SoHD, MAX_SOHD + 1);
        KiemTraSoHoaDon(hd.SoHD);
        UpperCase(hd.SoHD);

        if (KiemTraTrungSoHD(dsnv, hd.SoHD)) {
            cout << "So hoa don da ton tai\n";
            continue;
        }
        break;
    } while (true);

    // Loai
    do {
        cout << "Nhap loai (N/X): ";
        cin >> hd.Loai;
        hd.Loai = toupper(hd.Loai);
        cin.ignore(1000, '\n');

    } while (hd.Loai != 'N' && hd.Loai != 'X');

    // So chi tiet
    int n;
    cout << "Nhap so luong chi tiet hoa don: ";
    n = NhapSoNguyenKhongAm();
    hd.dscthd.n = n;

    for (int i = 0; i < n; i++) {
        cout << "\nChi tiet " << i + 1 << endl;
        NhapMotCTHD(root, hd, i);
    }

    // cap nhat ton
    CapNhatTonKho(root, hd);

    // them vao ds hoa don
    ThemHoaDonVaoCuoi(nv->dshd, hd);

    cout << "Lap hoa don thanh cong\n";
}



int main() {
	system("mode con cols=140 lines=40");
    TREE root;
    InitTree(root);
    DSNHANVIEN dsnv;
    InitDSNV(dsnv);
    LoadNhanVienFromFile(dsnv);
    LoadVatTuFromFile(root);

	HOADON hd;
    int choice;
    VATTU x;
    char ma[MAX_MAVT];

    do {
    	cout <<endl;
        cout << "====================================\n";
        cout << "         QUAN LY VAT TU              \n";
        cout << "====================================\n";
        cout << "1. Them vat tu\n";
        cout << "2. Tim vat tu\n";
        cout << "3. Sua vat tu\n";
        cout << "4. Xoa vat tu\n";
        cout << "5. In danh sach vat tu ton kho\n";
        cout << "6. Them Nhan vien\n";
        cout << "7. In Nhan Vien\n";
        cout << "0. Thoat\n";
        cout << "Chon chuc nang (0-7): ";
        cin >> choice;  // SUA LAI : neu nhap choice la string thi tu dong thoat? -> bat nhap lai 0-5
        while (cin.fail() || choice < 0 || choice > 8) {
               cin.clear();
             cin.ignore(1000, '\n');						//Suaưr lai
             cout << "Nhap sai. Vui long nhap lai (0-8): ";
             cin >> choice;
            }
        cin.ignore(1000, '\n');

        switch (choice) {
        case 1: {
	    int start = 0;
	    XoaManHinh();
	    InDanhSachVatTuTonKho(root, start);
	
	    while (true) {
	        char c = getch();
	
	        if (c == 'n' || c == 'N') {
	            start += 15;
	            InDanhSachVatTuTonKho(root, start);
	        }
	        else if (c == 'p' || c == 'P') {
	            start -= 15;
	            if (start < 0) start = 0;
	            InDanhSachVatTuTonKho(root, start);
	        }
	        
	        else if (c == 0 || c == -32) {
	            char f = getch();
	            if (f == 60) { // F2
	                VATTU x;
	                char n = getch();
	                while (true){
		                if(!NhapThongTinVT(root, x)) break; 
		                	ThemVT(root,x);
		                	InDanhSachVatTuTonKho(root,start);	
	        		}
	            }
	            else if(f==61){
	            	HieuChinhVT(root);
	            	
				}
	    	}	
	    	else if (c == 27) {
	        	
	            XoaManHinh();
	            break;
	        }
		}
}
//        case 2:{        // SUA LAI CASE 2: moi khi tim thay vat tu, chi in ra dung vattu do o danh sach'
//        	XoaManHinh();
//        	cout << "DANH SACH VAT TU HIEN CO\n";   
//        	InTieuDe();
//			InDongVatTu(root);
//
//            cout << "Nhap ma can tim: ";
//            cin.getline(ma, MAX_MAVT);
//			UpperCase(ma);
//			
//			TREE p =TimVT(root,ma)	;
//            if (p != NULL){
//                cout << "Tim thay\n";
//                InTieuDe();
//                  cout << left
//                        << setw(10) << p->data.MAVT
//                        << setw(25) << p->data.TENVT
//                        << setw(20) << p->data.DVT
//                        << setw(15) << p->data.SLT
//                        << endl;
//            }
//            else{
//			
//                cout << "Khong tim thay\n";
//            }
//            break;
//	}
	
//        case 6: {
//		    int start = 0;
//		    int pageSize = 15;
//		
//		    XoaManHinh();
//		    InDanhSachNhanVien(dsnv, start);
//		
//		    while (true) {
//		        char c = getch();
//		
//		        // Phim dac biet: F1, F2, mui ten...
//		        if (c == 0 || c == -32) {
//		            char f = getch();
//		
//		            if (f == 60) {			//F2
//		                ThemNhanVien(dsnv);
//		                InDanhSachNhanVien(dsnv, start);
//		            }
//		        }
//		        else if (c == 'n' || c == 'N') {
//		            if (start + pageSize < dsnv.n) {
//		                start += pageSize;
//		                InDanhSachNhanVien(dsnv, start);
//		            }
//		        }
//		        else if (c == 'p' || c == 'P') {
//		            if (start - pageSize >= 0) {
//		                start -= pageSize;
//		                InDanhSachNhanVien(dsnv, start);
//		
//		            }
//		        }
//		        else if (c == 27) { // ESC
//		            XoaManHinh();
//		            break;
//		        }
//		    }
//		    break;
//}
//        case 7:{
//			int start = 0;
//			int pageSize = 15;
//			
//			XoaManHinh();
//			InDanhSachNhanVien(dsnv,start);
//			clearLine(2, 2+ pageSize + 6, 20);
//			while (true){
//				char c = getch();
//	        	if (c == 'n' || c == 'N') {
//		            if (start + pageSize < dsnv.n) {
//		                start += pageSize;
//		                InDanhSachNhanVien(dsnv, start);
//		                clearLine(2, 2+ pageSize + 6, 60);
//		            }
//		        }
//		        else if (c == 'p' || c == 'P') {
//		            if (start - pageSize >= 0) {
//		                start -= pageSize;
//		                InDanhSachNhanVien(dsnv, start);
//						clearLine(2, 2+ pageSize + 6, 60);
//		            }
//		        }
//		        else if (c == 27) { // ESC
//		            XoaManHinh();
//		            break;
//		        }
//	}
//		break;
//          
//}
//        case 8:{
//        	LapHoaDon(root,dsnv);
//        	int next_choice;				
//        	cout<<"1. Them vat tu\n";						//12/4/2026 	16h
//        	cout<<"2. Xoa vat tu\n";						//ngay lap hd, cin next_choice
//        													//Them,sua,xoa VT(CTHD) chua oke
//        	cout<<"3. Xem vat tu\n";	
//        	while (cin.fail() || next_choice < 0 || next_choice > 8) {
//            cin.clear();
//            cin.ignore(1000, '\n');
//            cout << "Nhap sai. Vui long nhap lai (0-8): ";
//            cin >> next_choice;
//            }
//        	cin.ignore(1000, '\n');
//        	
//        	switch(next_choice){
//			
//        	case 1:
//        		NhapMotCTHD(root,hd,hd.dscthd.n);
//        		break;
//        	case 0:
//        		cout <<"thoat\n";
//        		break;
//			}
//		case 0: {  
//            cout << "Thoat\n";
//            break;
//		}
//
//        default:
//            cout << "Lua chon khong hop le\n";
//        }
	}
    } while (choice != 0);

    return 0;
}



