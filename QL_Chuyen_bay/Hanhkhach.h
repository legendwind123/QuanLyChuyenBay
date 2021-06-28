#include "MayBay.h"

#pragma disable(warning:4996)

// ============== Khởi tạo cấu trúc cây nhị phân hành khách ==============

struct data
{
	string CMND;
	string Ho;
	string Ten;
	bool Phai; // vi co 2 phai "nam" va "nu". True = nam & False = nu.
};
typedef struct data DATAHK;
// khai báo cấu trúc 1 node hanh khach
struct nodeHanhKhach
{
	DATAHK HanhKhach;
	nodeHanhKhach *pLeft;
	nodeHanhKhach *pRight;
};
typedef struct nodeHanhKhach NodeHK;
typedef NodeHK* TREE;

// hàm khởi tạo cây nhị phân tìm kiếm
void KhoiTaoCay(TREE &t)
{
	t = NULL;
}

// hàm thêm 1 cái NODE vào cây
void ThemNode(TREE &t, DATAHK x)
{
	// cây đang rỗng
	if (t == NULL)
	{
		NodeHK *p = new NodeHK;
		if (p == NULL)
		{
			cout << "\nKhong du bo nho de cap phat";
			return;
		}
		//cout << "kiem tra";
		p->pLeft = NULL;
		p->pRight = NULL;
		p->HanhKhach = x;
		t = p;
	}
	else
	{
		if (t->HanhKhach.CMND > x.CMND)
		{
			ThemNode(t->pLeft, x);
		}
		else if (t->HanhKhach.CMND < x.CMND)
		{
			ThemNode(t->pRight, x);
		}
	}
}

// nếu node có tồn tại trong cây thì trả về cái node đó - còn không tồn tại thì trả về NULL
NodeHK* TimKiemHK(TREE t, string x)
{
	// nếu cây rỗng
	if (t == NULL)
	{
		return NULL;
	}
	else
	{
		// nếu phần tử cần tìm kiếm mà nhỏ hơn node gốc thì duyệt(đệ quy) sang bên trái để tìm
		if (x < t->HanhKhach.CMND)
		{
			return TimKiemHK(t->pLeft, x);
		}
		else if (x > t->HanhKhach.CMND) // duyệt sang bên phải
		{
			return TimKiemHK(t->pRight, x);
		}
		else if (x == t->HanhKhach.CMND)// <=> t->data == x
		{
			return t; // trả về node cần tìm kiếm
		}
		else
		{
			return NULL;
		}
	}

}

// hết hàm chuẩn hóa.
void NhapHoTen(DATAHK &x)
{
	int kt;

	int tempX = wherex();
	int tempY = wherey();
	do
	{
		gotoxy(tempX, tempY);
		InputHighLight();
		cout << " Ho va Ten:                               ";
		LuiVe(30);
		NhapChu(x.Ho, SoHT);
		xoakhoangtrang(x.Ho);
		suakitu(x.Ho);
		kt = x.Ho.find(32); // kiem tra ten dung theo yeu cau khong
		if (kt == -1)
		{
			gotoxy(96, wherey() + 1);
			Error("Vui long nhap ho ten day du");
			Sleep(1000);
			gotoxy(96, wherey() - 1);
			Clean("Vui long nhap ho ten day du", 7);

		}
	} while (kt == -1);

	
	int i, dl;
	for (i = x.Ho.length() - 1; i >= 0; i--)// tim vi tri ten
	{
		if (x.Ho[i] == ' ')
		{
			dl = i;
			i = i + 1;
			break;
		}
	}
	for (; i < x.Ho.length(); i++)//dua ten wa tag Ten
	{
		x.Ten.push_back(x.Ho[i]);
	}
	x.Ho.erase(x.Ho.begin() + dl, x.Ho.begin() + x.Ho.length()); //xoa
	
}
void NhapHKkhongCMND(DATAHK &x)
{
	int vitriX = 95;
	int vitriY = wherey();
	string luachon;

	fflush(stdin);

	khungNhapHK(vitriX, vitriY);
	// chuyen mau va nhap
	//InputHighLight();
	gotoxy(vitriX + 1, vitriY + 1);
	/*cout << " So CMND: ";
	NhapSo(x.CMND, SoCMND);*/
	// tra ve mau cu
	gotoxy(vitriX + 1, wherey());
	Input();
	cout << " So CMND: " << x.CMND << endl;

	// chuyen mau va nhap
	InputHighLight();
	gotoxy(vitriX + 1, wherey() + 1);
	//cout << " Ho va Ten: ";
	NhapHoTen(x);
	// tra ve mau cu
	gotoxy(vitriX + 1, wherey());
	Input();
	cout << " Ho va Ten:  " << x.Ho << " " << x.Ten << endl;

	// chuyen mau va nhap
	InputHighLight();
	gotoxy(vitriX + 1, wherey() + 1);
	cout << " Gioi tinh: ";
	SetColor(14);
	select2(luachon, wherex() + 1, wherey(), " NAM ", " NU ", 10);
	if (luachon == " NAM ")
	{
		x.Phai = true;
	}
	else
	{
		x.Phai = false;
	}
}

void NhapHK(DATAHK &x)
{
	int vitriX = 95;
	int vitriY = wherey();
	string luachon;

	fflush(stdin);

	khungNhapHK(vitriX, vitriY);
	// chuyen mau va nhap
	InputHighLight();
	gotoxy(vitriX + 1, vitriY + 1);
	cout << " So CMND: ";
	NhapSo(x.CMND, SoCMND);
	// tra ve mau cu
	gotoxy(vitriX + 1, wherey());
	Input();
	cout << " So CMND: " << x.CMND << endl;

	// chuyen mau va nhap
	InputHighLight();
	gotoxy(vitriX + 1, wherey() + 1);
	//cout << " Ho va Ten: ";
	NhapHoTen(x);
	// tra ve mau cu
	gotoxy(vitriX + 1, wherey());
	Input();
	cout << " Ho va Ten:  " << x.Ho << " " << x.Ten << endl;

	// chuyen mau va nhap
	InputHighLight();
	gotoxy(vitriX + 1, wherey() + 1);
	cout << " Gioi tinh: ";
	SetColor(14);
	select2(luachon, wherex() + 1, wherey(), " NAM ", " NU ", 10);
	if (luachon == " NAM ")
	{
		x.Phai = true;
	}
	else
	{
		x.Phai = false;
	}
}


//----Kết Thúc Nhập

//----Xuất Danh sách
void XuatHK(DATAHK &x)
{
	int vtX = wherex();
	int vtY = wherey();

	SetColor(31);
	gotoxy(1, vtY);
	cout << x.CMND;
	gotoxy(17, wherey());
	cout << x.Ho;
	gotoxy(49, wherey());
	cout<< x.Ten;
	gotoxy(65, wherey());
	if (x.Phai == true)
	{
		cout << "Nam" << endl;
	}
	else
	{
		cout << "Nu" << endl;
	}
}
// hàm duyệt cây theo NRL
void NRL(TREE t)
{
	
	// nếu cây rỗng
	if (t == NULL)
	{
		return;
	}
	else
	{
		XuatHK(t->HanhKhach);
		NRL(t->pRight);
		NRL(t->pLeft);
	}
}
//----Kết thúc Danh Sách

// xóa 1 node là lá 
void TimNodeTheMang(TREE t, TREE x) //timphantuthemangphainhatcaycontrai
{
	if (x->pRight != NULL)
	{
		TimNodeTheMang(t, x->pRight);
	}
	else
	{
		t->HanhKhach = x->HanhKhach;
		t = x;
		x = x->pLeft;
	}
}

void xoanode(TREE &t, string x)
{
	if (t == NULL)
	{
		return;
	}
	else
	{
		if (t->HanhKhach.CMND > x)
		{
			xoanode(t->pLeft, x);
		}
		else if (t->HanhKhach.CMND < x)
		{
			xoanode(t->pRight, x);
		}
		else
		{
			NodeHK *p = t;
			if (t->pLeft == NULL)
			{
				t = t->pRight;
			}
			else if (t->pRight == NULL)
			{
				t = t->pLeft;
			}
			else
			{
				// cách 1 tìm phần tử trái nhất cây con phải 
				//timphantuthemangtrainhatcayconphai(p, t->pright);
				//cách 2 tìm pahn62 tử thế mạng phải nhất cây con trái
				TimNodeTheMang(p, t->pLeft);
			}
			delete p;
		}
	}
}

void suanode(TREE &t, DATAHK x)
{
	string temp;
	if (t == NULL) //danh sach rong thi return
	{
		return;
	}
	else
	{
		xoanode(t, x.CMND);
		ThemNode(t, x);
		//t->HanhKhach = x;
	}
}

void deleteTree(TREE &t)
{
	if (t == NULL) return;

	/* first delete both subtrees */
	deleteTree(t->pLeft);
	deleteTree(t->pRight);

	/* then delete the node */
	cout << "\n Deleting node: " << endl;
	XuatHK(t->HanhKhach);
	delete t;
}
// ========================= Xu ly file

void ghiFileHK(DATAHK &x)
{
	ofstream fileout;
	fileout.open("HanhKhach.txt", ios::out | ios::app);
	fileout << x.CMND << ",";
	removeSpace(x.Ho);
	fileout << x.Ho << ",";
	fileout << x.Ten << ",";
	fileout << x.Phai << endl;
	fileout.close();
}

void ghiDSHK(TREE &t)
{
	// nếu cây rỗng
	if (t == NULL)
	{
		return;
	}
	else
	{
		ghiFileHK(t->HanhKhach);
		ghiDSHK(t->pRight);
		ghiDSHK(t->pLeft);
	}
}

void nhapHKchoFile(DATAHK &x, string cmnd, string ho, string ten, int phai)
{
	x.CMND = cmnd;
	addSpace(ho);
	x.Ho = ho;
	x.Ten = ten;
	if(phai == 1) x.Phai = true;
	else if(phai == 0) x.Phai = false;
	
}

void nhapDSHKchoFile(TREE &t, string cmnd, string ho, string ten, int phai)
{
	//cout << "Nhap hanh khach";
	if (cmnd == "") return;
	DATAHK x;
	nhapHKchoFile(x, cmnd, ho, ten, phai);
	ThemNode(t, x);
		
}

void docFileHK(TREE &t)
{
	//TREE t1;
	//DATAHK x;
	ifstream filein;
	filein.open("Hanhkhach.txt", ios::in);

	int temp;
	while (!filein.eof())
	{
		string n, data;
		string ho, ten, cmnd;
		int phai;
		char thongtin[50];

		filein >> thongtin; // dua thong tin vao bien
		cout << "Du lieu lay trong file: " << thongtin << endl;
		if (thongtin == NULL) break;
		int count = 1;
		// tach thong tin ra cac bien nho
		for (int i = 0; i < 50; i++)
		{

			if (thongtin[i] == NULL) // neu chuoi rong thi break
			{
				if (count == 4)
				{			
					chuyenso(data, temp);
					phai = temp;
					break;
				}
				else 
					break;
			}

			if (thongtin[i] != ',')
			{
				data.push_back(thongtin[i]);
			}
			else
			{
				if (count == 1) cmnd = data;
				if (count == 2) ho = data;
				if (count == 3) ten = data;
				if (count == 4)
				{
					chuyenso(data, temp);
					phai = temp;
					cout << phai;
				}
				count++;
				cout << "data " << data << endl;
				data.clear();
			} // end else
		} // end for
		
		getline(filein, n); // lay dau enter cuoi day ra		
		// luu vao danh sach hanh khach
		nhapDSHKchoFile(t, cmnd, ho, ten, phai);
	} // end while
	filein.close();
}

// ======================= End xu ly file

int MenuHKHACH(TREE &t)
{
	ShowConsoleCursor(false);
	while (true)
	{
		system("cls");

		string tenMenu = "QUAN LY HANH KHACH";
		int luachon;
		//luachon = MenuDong(menuHKHACH, ITEMMENUHKHACH, tenMenu);
		khungMainScreen();

		veManhinhXuatHK(0, 1 + ITEMMENUCBAY);
		NRL(t);

		BatPhimChucNang(luachon);

		if (luachon == 1)
		{
			gotoxy(0, 1 + ITEMMENUHKHACH);
			Normal();
			DATAHK x;
			NhapHK(x);
			ThemNode(t, x);
			
			Sleep(1000);
		}
		if (luachon == 2)
		{
			gotoxy(0, 1 + ITEMMENUHKHACH);
			Normal();
			NRL(t);
			system("pause");
		}
		if (luachon == 7)
		{
			gotoxy(95, 1 + ITEMMENUHKHACH);
			Normal();
			if (t == NULL)
			{
				cout << "Rong";
			}
			else
			{
				string x;
				cout << "Nhap CMND can tim: ";
				NhapSo(x, SoCMND);
				NodeHK *temp = TimKiemHK(t, x);
				if (temp == NULL)
				{
					cout << "Thong tin khong ton tai!!";
				}
				else
				{
					XuatHK(temp->HanhKhach);
				}
				cout << "Xong";
			}
			system("pause");
		}
		if (luachon == 4)
		{
			gotoxy(95, 1 + ITEMMENUHKHACH);
			Normal();
			if (t == NULL)
			{
				cout << "Rong";
			}
			else
			{
				string temp;
				DATAHK x;
				cout << "Nhap CMND can sua: ";
				NhapSo(temp, SoCMND);
				x.CMND = temp;
				NhapHKkhongCMND(x);
				suanode(t, x);
			}
			system("pause");
		}
		if (luachon == 3)
		{
			gotoxy(95, 1 + ITEMMENUHKHACH);
			Normal();
			string x;
			cout << "Nhap CMND can xoa: ";
			NhapSo(x, SoCMND);
			xoanode(t, x);
		}
		if (luachon == 6)
		{
			gotoxy(0, 1 + ITEMMENUHKHACH);
			Normal();
			deleteTree(t);
			t = NULL;
			//system("pause");
		}
		if (luachon == 5) {
			Normal();
			cout << "\n";
			return 0;
		}
	}
}