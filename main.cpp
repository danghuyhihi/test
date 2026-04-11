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
#define MAX_PHAI 4
#define MAX_SOHD 20
#define MAXCTHD 20
#define MAXNV 500
#define MAXTEMP 1001


struct huy{
    int age;
};
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
void ChuanHoaKhoangTrang(char s[])
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

TREE TaoNodeVT(VATTU x) {
    TREE p = new NodeVT;
    p->data = x;
    p->left = NULL;
    p->right = NULL;
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











int main() {
    TREE root;
    InitTree(root);
    LoadVatTuFromFile(root);

    int choice;
    VATTU x;
    char ma[MAX_MAVT];

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Them vat tu\n";
        cout << "2. Tim vat tu\n";
        cout << "3. Sua vat tu\n";
        cout << "4. Xoa vat tu\n";
        cout << "5. In danh sach vat tu ton kho\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> choice;
        cin.ignore(1000, '\n');

        switch (choice) {
        case 1:
            XoaManHinh();
            InDanhSachVatTuTonKho(root);
            cout << "\n+---Nhap thong tin vat tu: ---+\n";
            NhapThongTinVT(root,x);
            if (ThemVT(root, x))
                cout << "Them thanh cong\n";
            else
                cout << "Bi trung ma\n";
            break;

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
            break;
		case 0: {
            ofstream f("vattu.txt");
            SaveVatTuToFile(root, f);
            f.close();
            cout << "Thoat\n";
            break;
}

        default:
            cout << "Lua chon khong hop le\n";
        }

    } while (choice != 0);

    return 0;
}



