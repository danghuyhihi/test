#include <iostream>
#include <cstring>			//16h 11/04
#include <iomanip>
#include <fstream>

using namespace std;

#define MAX_MAVT 10
#define MAX_TENVT 50
#define MAX_DVT 20
#define MAX_MANV 10
#define MAX_HO 50
#define MAX_TEN 20
#define MAX_PHAI 10
#define MAX_SOHD 20
#define MAXCTHD 20
#define MAXNV 500
#define MAXTEMP 1001



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



void NhapThongTinVT(TREE root, VATTU &x) {
	do {
	    cout << "Nhap ma vat tu: \n";
	    cin.getline(x.MAVT, MAX_MAVT);
	
	    if (!KiemTraMaVT(x.MAVT)) {
	        cout << "Ma khong hop le\n";
	        continue;
	    }
	    UpperCase(x.MAVT);
	    if (KiemTraTrungMaVT(root, x.MAVT)) {
	        cout << "Ma da ton tai\n";
	        continue;
	    }
	
	    break;
	
	} while (true);

	do{
		cout <<"nhap ten vat tu:\n";
		cin.getline(x.TENVT,MAX_TENVT);
		if(!KiemTraTenVatTu(x.TENVT)){
			cout<<"ten khong hop le\n";
			continue;
		}
		break;
		
	}while(true);
	
	
	do{
		cout<<"nhap don vi tinh: \n";
		cin.getline(x.DVT,MAX_DVT);
		if(!KiemTraDVT(x.DVT)){
			cout<<"sai don vi tinh, nhap lai:\n";
			continue;
		}
		break;
		
	}while(true);
	
        cout << "nhap so luong ton: ";		//Kiểm tra SLT
        x.SLT = NhapSoNguyenKhongAm();
}



//
void HieuChinhVT(TREE root,VATTU x) {
	TREE p;
	char maVT[MAX_MAVT + 1];

	do {
	    cout << "Nhap ma vt muon sua: ";
	    cin.getline(maVT, MAX_MAVT);
	
	    XoaKhoangTrangDauCuoi(maVT);
	    UpperCase(maVT);
	
	    p = TimVT(root, maVT);
	
	    if (p == NULL) {
	        cout << "Khong tim thay vat tu. Nhap lai.\n";
	    }
	
	} while (p == NULL);

    cout << "Thong tin hien tai:\n";
    cout << "Ma VT       : " << p->data.MAVT << '\n';
    cout << "Ten VT      : " << p->data.TENVT << '\n';
    cout << "Don vi tinh : " << p->data.DVT << '\n';
    cout << "So luong ton: " << p->data.SLT << '\n';

    cout << "\nChi duoc sua TENVT va DVT. Khong sua SLT o day.\n";
    cout << "1. Sua ten vat tu\n";
    cout << "2. Sua don vi tinh\n";
    cout << "Chon: ";

    int choice;
    cin >> choice;
    cin.ignore(1000, '\n');

    if (choice == 1) {
    do {
        cout << "Nhap ten vat tu moi: ";
        cin.getline(p->data.TENVT, MAX_TENVT);
        if (!KiemTraTenVatTu(p->data.TENVT)) {
            cout << "Ten khong hop le. Nhap lai.\n";
            continue;
        }
        break;
    } while (true);
}
else if (choice == 2) {
    do {
        cout << "Nhap don vi tinh moi: ";
        cin.getline(p->data.DVT, MAX_DVT);
        if (!KiemTraDVT(p->data.DVT)) {
            cout << "Don vi tinh khong hop le. Nhap lai.\n";
            continue;
        }
        break;
    } while (true);
}
 
	else {
        cout << "Nhap dung lua chon.\n";
        return;
    }

    cout << "Da cap nhat vat tu.\n";
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
void InDanhSachNhanVien(DSNHANVIEN ds) {
    if (ds.n == 0) {
        cout << "Danh sach nhan vien rong.\n";
        return;
    }

    cout << left
         << setw(12) << "Ma NV"
         << setw(25) << "Ho"
         << setw(15) << "Ten"
         << setw(10) << "Phai"
         << endl;

    cout << setfill('-') << setw(62) << "" << endl;
    cout << setfill(' ');

    for (int i = 0; i < ds.n; i++) {
        cout << left
             << setw(12) << ds.nv[i]->MANV
             << setw(25) << ds.nv[i]->HO
             << setw(15) << ds.nv[i]->TEN
             << setw(10) << ds.nv[i]->PHAI
             << endl;
    }

}
void InDanhSachVatTuTonKho(TREE root) {
    if (root == NULL) {
        cout << "Danh sach vat tu rong.\n";
        return;
    }
    VATTU temp[MAXTEMP];
    int n = 0;

  	ChepCayRaMang(root,temp, n);
   	SapXepTheoTen(temp, n);

    InTieuDe();
    for (int i = 0; i < n; i++) {
        cout << left
             << setw(10) << temp[i].MAVT
             << setw(25) << temp[i].TENVT
             << setw(20) << temp[i].DVT
             << setw(15) << temp[i].SLT
             << endl;
    }
}

int SoSanhNhanVien(NHANVIEN *a, NHANVIEN *b) {
    int kq = strcmp(a->TEN, b->TEN);
    if (kq != 0) return kq;

    kq = strcmp(a->HO, b->HO);
    if (kq != 0) return kq;

    return strcmp(a->MANV, b->MANV);
}

void ThemNhanVien(DSNHANVIEN &ds) {
    if (ds.n >= MAXNV) {
        cout << "Danh sach nhan vien da day.\n";
        return;
    }

    NHANVIEN *p = new NHANVIEN;

    // Nhap ma NV
    do {
        cout << "Nhap ma nhan vien: ";
        cin.getline(p->MANV, MAX_MANV);

        ChuanHoaKhoangTrang(p->MANV);
        UpperCase(p->MANV);

        KiemTraMaNV(p->MANV);

        if (!KiemTraTrungMANV(ds, p->MANV)) {
            cout << "Ma nhan vien da ton tai.\n";
            continue;
        }

        break;
    } while (true);

    // Nhap ho
    do {
        cout << "Nhap ho: ";
        cin.getline(p->HO, MAX_HO);
		KiemTraTenVatTu(p->HO);
        ChuanHoaHoTen(p->HO);

        if (strlen(p->HO) == 0) {
            cout << "Ho khong duoc rong.\n";
            continue;
        }

        break;
    } while (true);

    // Nhap ten
    do {
        cout << "Nhap ten: ";
        cin.getline(p->TEN, MAX_TEN);
		KiemTraTenVatTu(p->TEN);
        ChuanHoaHoTen(p->TEN);

        if (strlen(p->TEN) == 0) {
            cout << "Ten khong duoc rong.\n";
            continue;
        }

        break;
    } while (true);

    // Nhap phai
    do {
    	
        cout << left << setw(15) << "Nhap phai:" << "1. Nam\n";
		cout << left << setw(15) << ""           << "2. Nu\n";
		cout << "Nhap lua chon: ";
        cin.getline(p->PHAI, MAX_PHAI);
		if(strcmp(p->PHAI,"1") == 0 )
			strcpy(p->PHAI,"Nam");
		else if(strcmp(p->PHAI,"2") == 0)
			strcpy(p->PHAI,"Nu");
		else{
			
			cout<<"Chon dung lua chon (1/2):\n";
			continue;
		}
        ChuanHoaHoTen(p->PHAI);
        break;
    } while (true);

    p->dshd = NULL;

    // Tim vi tri chen
    int pos = ds.n;

    for (int i = 0; i < ds.n; i++) {
        if (SoSanhNhanVien(p, ds.nv[i]) < 0) {
            pos = i;	
            break;
        }
    }

    // Day mang sang phai
    for (int i = ds.n; i > pos; i--) {
        ds.nv[i] = ds.nv[i - 1];
    }

    ds.nv[pos] = p;
    ds.n++;

    cout << "Them nhan vien thanh cong.\n";
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
             cin.ignore(1000, '\n');
             cout << "Nhap sai. Vui long nhap lai (0-8): ";
             cin >> choice;
            }
        cin.ignore(1000, '\n');

        switch (choice) {
        case 1:{
        	ofstream f("vattu.txt");
            XoaManHinh();
            InDanhSachVatTuTonKho(root);
            cout << "\n+---Nhap thong tin vat tu: ---+\n";
            NhapThongTinVT(root,x);
            if (ThemVT(root, x))
                cout << "Them thanh cong\n";
            else
                cout << "Bi trung ma\n";
            SaveVatTuToFile(root, f);
            f.close();
            break;
}
        case 2:{        // SUA LAI CASE 2: moi khi tim thay vat tu, chi in ra dung vattu do o danh sach'
        	XoaManHinh();
        	cout << "DANH SACH VAT TU HIEN CO\n";   
        	InTieuDe();
			InDongVatTu(root);

            cout << "Nhap ma can tim: ";
            cin.getline(ma, MAX_MAVT);
			UpperCase(ma);
			
			TREE p =TimVT(root,ma)	;
            if (p != NULL){
                cout << "Tim thay\n";
                InTieuDe();
                  cout << left
                        << setw(10) << p->data.MAVT
                        << setw(25) << p->data.TENVT
                        << setw(20) << p->data.DVT
                        << setw(15) << p->data.SLT
                        << endl;
            }
            else{
			
                cout << "Khong tim thay\n";
            }
            break;
	}
        case 3: {           // SUA LAI CASE 3 : moi khi muon' sua thi` hien ra danh sach VT
            XoaManHinh();
            cout << "DANH SACH VAT TU HIEN CO\n";
            InTieuDe();
            InDongVatTu(root);
            cout << endl;

            HieuChinhVT(root, x);
            break;
	}
        case 4:         // SUA LAI CASE4: moi khi mun xoa theo mavt thi phai in hoa? -> tu dong in hoa dong vua nhap
            cout << "Nhap ma can xoa: ";
            cin.getline(ma, 50);
            XoaKhoangTrangDauCuoi(ma);
            UpperCase(ma);

            if (RemoveVT(root, ma))
                cout << "Xoa thanh cong\n";
            else
                cout << "Khong tim thay\n";
            break;
		case 5:
            XoaManHinh();
			InDanhSachVatTuTonKho(root);
			cout<<"bam nut bat ky de ra menu: \n";
	        cin.get();
            break;
        case 6:
	        XoaManHinh();
	        InDanhSachNhanVien(dsnv);
	        cout << "\n+---Nhap thong tin nhan vien: ---+\n";
	        ThemNhanVien(dsnv);
	        
	        SaveNhanVienToFile(dsnv);
	        break;

        case 7:
            XoaManHinh();
            InDanhSachNhanVien(dsnv);
            cout<<"bam nut bat ky de ra menu: \n";
	        cin.get();
            break;
        case 8:
        	LapHoaDon(root,dsnv);
        	int next_choice;				
        	cout<<"1. Them vat tu\n";						//12/4/2026 	16h
        	cout<<"2. Xoa vat tu\n";						//ngay lap hd, cin next_choice
        													//Them,sua,xoa VT(CTHD) chua oke
        	cout<<"3. Xem vat tu\n";	
        	while (cin.fail() || next_choice < 0 || next_choice > 8) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Nhap sai. Vui long nhap lai (0-8): ";
            cin >> next_choice;
            }
        	cin.ignore(1000, '\n');
        	
        	switch(next_choice){
			
        	case 1:
        		NhapMotCTHD(root,hd,hd.dscthd.n);
        		break;
        	case 0:
        		cout <<"thoat\n";
        		break;
			}
		case 0: {  
            cout << "Thoat\n";
            break;
}

        default:
            cout << "Lua chon khong hop le\n";
        }

    } while (choice != 0);

    return 0;
}



