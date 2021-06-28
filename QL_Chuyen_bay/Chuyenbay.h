#include "Hanhkhach.h"

//==========================================================

struct VeMB
{
	string maVe;
	string CMND;
	// int maVe;
};

struct ChuyenBay
{
	string MaCB;
	Date NgayGioBay;
	string SanBayDen;
	int TrangThai;
	string SoHieuMB;
	VeMB *DSVe;
	int soVeDaBan;
};

struct node
{
	ChuyenBay info;
	node *pketiep;
};
typedef struct node NODECB;

struct listcb
{
	NODECB *phead;
	NODECB *ptail;
};
typedef struct listcb LISTCB;

void khoitaodanhsach(LISTCB &i)
{
	i.phead = NULL;
	i.ptail = NULL;
}


void Free_CB(LISTCB &i)
{
	NODECB *tam = i.phead;
	string soHieu;
	while (i.phead != NULL)
	{
		VeMB* a = i.phead->info.DSVe;
		soHieu = i.phead->info.SoHieuMB;
		tam = tam->pketiep;
		delete[] a; // giai phong vung nho cua DSVe
		delete i.phead; // giai phong vung nho cua cac chuyen bay
		i.phead = tam;
	}	
	khoitaodanhsach(i);
}

VeMB* khoitaoVe(VeMB *a, int day, int dong )
{
	int SoGhe = day*dong;
	a = new VeMB[SoGhe];
	char tempday;
	char tempdong;

	int dem = 0;

	//gán mã ghế tự regen ra
	for (int k = 1; k <= day; k++)  // day
	{
		for (int l = 1; l <= dong; l++) // dong
		{
			tempday = NumberToLetter(k);
			tempdong = l + 48;
			// gop vao tao thanh ma ve
			a[dem].maVe.push_back(tempday);
			a[dem].maVe.push_back(tempdong);
			//ghiFile("VeMayBay.txt", a[dem].maVe);
			dem++;
		}
	}
	return a;
}

NODECB* middle(NODECB* start, NODECB* last)
{
	if (start == NULL)
		return NULL;

	NODECB* slow = start;
	NODECB* fast = start->pketiep;

	while (fast != last)
	{
		fast = fast->pketiep;
		if (fast != last)
		{
			slow = slow->pketiep;
			fast = fast->pketiep;
		}
	}
	return slow;
}

NODECB* binarySearch(LISTCB i, string MaCB)
{
	NODECB* start = i.phead;
	NODECB* last = NULL;
	do
	{
		// Find middle 
		NODECB* mid = middle(start, last);

		// If middle is empty 
		if (mid == NULL)
		{
			gotoxy(95, wherey() + 1);
			CleanNBack("Khong tim thay chuyen bay");
			return NULL;
		}
		// If value is present at middle 
		if (mid->info.MaCB == MaCB)
			return mid;

		// If value is more than mid 
		else if (mid->info.MaCB < MaCB)
			start = mid->pketiep;

		// If the value is less than mid. 
		else
			last = mid;

	} while (last == NULL || last != start);

	
	// value not present 
	gotoxy(95, wherey() + 1);
	CleanNBack("Khong tim thay chuyen bay");
	return NULL;
}

bool KiemTraCB(LISTCB l, string x)
{
	NODECB* current = l.phead;
	while (current != NULL)
	{
		if (current->info.MaCB == x)
		{
			return true;
		}
		current = current->pketiep;
	}
	return false;
}

int DemVeTrong(ChuyenBay x, LISTCB listCB, ListMB listMB)
{
	string maCB = x.MaCB;
	NODECB *e;
	e = binarySearch(listCB, maCB);

	VeMB* ve = e->info.DSVe;
	int SoDay = listMB.DSMB[TimkiemMB(listMB, e->info.SoHieuMB)]->soDay;
	int SoDong = listMB.DSMB[TimkiemMB(listMB, e->info.SoHieuMB)]->soDong;
	int tongVe = SoDay*SoDong;

	e = binarySearch(listCB, maCB);
	int veTrong = tongVe - e->info.soVeDaBan;

	return veTrong;
}

void NhapTimeBay(Date &d)
{
	string date;

	cout << "Yyyy/Mm/Dd  hh:mm";
	gotoxy(wherex()-17, wherey());
	NhapDate(d.Nam, d.Thang, d.Ngay, d.Gio, d.Phut);
	
}

void NhapNgayBay_CauF(Date &d)
{
	string date;

	cout << "Yyyy/Mm/Dd";
	LuiVe(10);
	// Nam
NhapLaiNam:
	InputDate();
	cout << "Yyyy"; 	
	LuiVe(4);
	NhapSo(date, 4);
	chuyenso(date, d.Nam);
	if (d.Nam >= 2000 && d.Nam <= 2100)
	{
		LuiVe(4);
		Normal();
		cout << d.Nam << "/";
	}
	else
	{
		LuiVe(4);
		goto NhapLaiNam;
	}	
	// Thang
NhapLaiThang:
	InputDate();
	cout << "Mm"; 	
	LuiVe(2);
	NhapSo(date, 2);
	chuyenso(date, d.Thang);
	if (d.Thang > 0 && d.Thang < 13)
	{
		Normal();
		LuiVe(2);
		if (d.Thang < 10) cout << "0" << d.Thang << "/";
		else cout << d.Thang << "/";
	}
	else
	{
		LuiVe(2);
		goto NhapLaiThang;
	}
	// Ngay
NhapLaiNgay:
	InputDate();
	cout << "Dd"; 
	LuiVe(2);	
	NhapSo(date, 2);
	chuyenso(date, d.Ngay);
	if (d.Thang == 2 && d.Ngay >= 1 && d.Ngay <= 28)
	{
		Normal();
		LuiVe(2);
		if (d.Ngay < 10) cout << "0" << d.Ngay ;
		else cout << d.Ngay ;
	}
	else if (d.Thang == 4 || d.Thang == 6 || d.Thang == 9 || d.Thang == 11)
	{
		if (d.Ngay >= 1 && d.Ngay <= 30)
		{
			Normal();
			LuiVe(2);
			if (d.Ngay < 10) cout << "0" << d.Ngay;
			else cout << d.Ngay;
		}
	}
	else
	{
		if (d.Ngay >= 1 && d.Ngay <= 31)
		{
			Normal();
			LuiVe(2);
			if (d.Ngay < 10) cout << "0" << d.Ngay;
			else cout << d.Ngay;
		}
		else
		{
			LuiVe(2);
			goto NhapLaiThang;
		}
	}
	d.Gio = 0;
	d.Phut = 0;
}

void XuatCB_VeTrong(ChuyenBay x, LISTCB listCB, ListMB listMB)
{
	int VTx = wherex();
	int VTy = wherey();
	DataTable();
	gotoxy(VTx + 4, wherey());
	cout << x.MaCB;
	gotoxy(VTx + 17, wherey());
	cout << x.SanBayDen;
	gotoxy(VTx + 40, wherey());
	cout << x.SoHieuMB;
	gotoxy(VTx + 54, wherey());
	xuatFomatDate(x.NgayGioBay.Nam, x.NgayGioBay.Thang, x.NgayGioBay.Ngay, x.NgayGioBay.Gio, x.NgayGioBay.Phut);
	gotoxy(VTx + 82, wherey());
	int veTrong = DemVeTrong(x, listCB, listMB);
	cout << veTrong << endl;
	//cout << chuyenTrangThai(x.TrangThai) << endl;
}

void XuatCB(ChuyenBay &x)
{
	int VTx = wherex();
	int VTy = wherey();
	DataTable();
	gotoxy(VTx + 4, wherey());
	cout << x.MaCB;
	gotoxy(VTx + 17, wherey());
	cout << x.SanBayDen;
	gotoxy(VTx + 40, wherey());
	cout << x.SoHieuMB;
	gotoxy(VTx + 54, wherey());
	xuatFomatDate(x.NgayGioBay.Nam, x.NgayGioBay.Thang, x.NgayGioBay.Ngay, x.NgayGioBay.Gio, x.NgayGioBay.Phut);
	gotoxy(VTx + 81, wherey());

	cout << chuyenTrangThai(x.TrangThai) << endl;
}

void XuatDSCB(LISTCB &l)
{
	SetColor(11);
	cout << endl;
	gotoxy((wherex() + 1), wherey());
	cout << "Ma chuyen bay"
		<< "\t San bay den"
		<< "\t     Ma may bay"
		<< "\t\t Thoi gian"
		<< "\t\t Trang thai" << endl;
	for (NODECB *i = l.phead; i != NULL; i = i->pketiep)
	{
		gotoxy(wherex() + 1, wherey());
		XuatCB(i->info);
	}
}

void NhapCB(ChuyenBay &x, ListMB &l, LISTCB &cb, ListCBnMB &CBnMB)
{
	/*gotoxy(0, 1 + ITEMMENUMBAY);
	Normal();
	xuatDSMBay(l);*/
	
	int vitriX = 95;
	int vitriY = 7;
	khungNhapCB(vitriX, vitriY);
	bool kt;
	do
	{
		// chuyen mau va nhap
		InputHighLight();
		gotoxy(vitriX + 1, vitriY + 1);
		cout << " Ma chuyen bay:           ";
		LuiVe(10);
		NhapKiTuKSpace(x.MaCB, MaxIDCB);
		kt = KiemTraCB(cb, x.MaCB);
		if (kt == true)
		{
			gotoxy(vitriX + 1, vitriY + 2);
			Error("Ma chuyen bay trung !!!");
			Sleep(1000);
			gotoxy(vitriX + 1, vitriY + 2);
			Clean("Ma chuyen bay trung !!!", 7);
		}
		else
		{
			// tra ve mau cu
			gotoxy(vitriX + 1, wherey());
			Input();
			cout << " Ma chuyen bay: " << x.MaCB << endl;
		}
	} while (kt != false);

	// chuyen mau va nhap
	InputHighLight();
	gotoxy(vitriX + 1, wherey() + 1);
	cout << " Thoi gian bay: ";
	NhapTimeBay(x.NgayGioBay);
	// tra ve mau cu
	gotoxy(vitriX + 1, wherey());
	Input();
	cout << " Thoi gian bay:  ";	

	// fomat date
	
	xuatFomatDate(x.NgayGioBay.Nam, x.NgayGioBay.Thang, x.NgayGioBay.Ngay, x.NgayGioBay.Gio, x.NgayGioBay.Phut);
	cout << endl;

	// chuyen mau va nhap
	InputHighLight();
	gotoxy(vitriX + 1, wherey() + 1);
	cout << " San bay den: ";
	NhapChu(x.SanBayDen, MaxSanBayDen);
	xoakhoangtrang(x.SanBayDen);
	suakitu(x.SanBayDen);
	// tra ve mau cu
	gotoxy(vitriX + 1, wherey());
	Input();
	cout << " San bay den: " << x.SanBayDen << endl;
	int dongNhapSoHieu = wherey();
	x.TrangThai = 1;
	
	// in danh sach may bay
	xoaManhinhTrai();

	khungThemCB();
	gotoxy(0, 1 + ITEMMENUMBAY);
	Normal();
	xuatDSMBay(l);

	int Search;
	do
	{
		// chuyen mau va nhap
		InputHighLight();
		gotoxy(vitriX + 1, dongNhapSoHieu + 1);
		cout << " So hieu may bay: ";
		NhapKiTuKSpace(x.SoHieuMB, MAXSOHIEUMAYBAY);
		// tra ve mau cu
		gotoxy(vitriX + 1, wherey());
		Input();
		cout << " So hieu may bay: " << x.SoHieuMB;
		gotoxy(96, wherey() + 1);
		
		Search = binarySearch_CBnMB(CBnMB.MBnCB, CBnMB.index, x.SoHieuMB);;
		
		if (Search == -1)
		{
			int tempX = wherex(), tempY = wherey();
			gotoxy(tempX, tempY);
			Error("May Bay Khong Ton Tai !");
			Sleep(1000);
			gotoxy(tempX, tempY);
			Clean("May Bay Khong Ton Tai !",7);
			x.SoHieuMB.clear();
			gotoxy(vitriX + 1, wherey() - 1);
			InputHighLight();
			cout << " So hieu may bay:           ";
			gotoxy(0, wherey() - 1);
		}
		else if (Search == -2)
		{
			Error("Danh sach may bay rong, vui long cap nhat danh sach may bay");
			Sleep(1000);
			CleanRow("Danh sach may bay rong, vui long cap nhat danh sach may bay");

			x.SoHieuMB.clear();
			break;
		}
		else
		{
				bool KT = QuanHeMBVaCB(CBnMB, x.NgayGioBay, Search); // biến kiểm tra quan hệ máy bay và chuyến bay
				if (KT == false)
				{
					int tempX = wherex(), tempY = wherey();
					gotoxy(tempX, tempY);
					Error("May bay trung lich");
					Sleep(1000);
					gotoxy(tempX, tempY);
					Clean("May bay trung lich", 7);
					x.SoHieuMB.clear();
					gotoxy(vitriX + 1, wherey() - 1);
					InputHighLight();
					cout << " So hieu may bay:           ";
					gotoxy(0, wherey() - 1);
				}
				else
				{
					NodeDataCBnMB *p = new NodeDataCBnMB();
					p->data.NgayGioBay = x.NgayGioBay;
					p->data.MaCB = x.MaCB;
					p->pketiep = NULL;
					Insert_Order_CBnMB(CBnMB.MBnCB[Search].list, p);
					break;
				}
			
		}
	} while (true);
	x.soVeDaBan = TimkiemMB(l,x.SoHieuMB);// lấy vị trí máy bay trong danh sách
}

void NhapCB_KhongMaCB(ChuyenBay &x, ListMB l, ListCBnMB &CBnMB)
{
	/*gotoxy(0, 1 + ITEMMENUMBAY);
	Normal();
	xuatDSMBay(l);*/
	
	int vitriX = 95;
	int vitriY = 7;
	khungNhapCB(vitriX, vitriY);
	bool kt;

	// xuat ma CB co san
	gotoxy(vitriX + 1, vitriY + 1);
	Input();
	cout << " Ma chuyen bay: " << x.MaCB << endl;

	// chuyen mau va nhap
	InputHighLight();
	gotoxy(vitriX + 1, wherey() + 1);
	cout << " Thoi gian bay: ";
	NhapTimeBay(x.NgayGioBay);
	// tra ve mau cu
	gotoxy(vitriX + 1, wherey());
	Input();
	cout << " Thoi gian bay:  ";

	// fomat date

	xuatFomatDate(x.NgayGioBay.Nam, x.NgayGioBay.Thang, x.NgayGioBay.Ngay, x.NgayGioBay.Gio, x.NgayGioBay.Phut);
	cout << endl;

	// chuyen mau va nhap
	InputHighLight();
	gotoxy(vitriX + 1, wherey() + 1);
	cout << " San bay den: ";
	NhapChu(x.SanBayDen, MaxSanBayDen);
	xoakhoangtrang(x.SanBayDen);
	suakitu(x.SanBayDen);
	// tra ve mau cu
	gotoxy(vitriX + 1, wherey());
	Input();
	cout << " San bay den: " << x.SanBayDen << endl;
	int dongNhapSoHieu = wherey();
	x.TrangThai = 1;
	
	// in danh sach may bay
	xoaManhinhTrai();

	khungThemCB();
	gotoxy(0, 1 + ITEMMENUMBAY);
	Normal();
	xuatDSMBay(l);

	int Search;
	do
	{
		// chuyen mau va nhap
		InputHighLight();
		gotoxy(vitriX + 1, dongNhapSoHieu + 1);
		cout << " So hieu may bay: ";
		NhapKiTuKSpace(x.SoHieuMB, MAXSOHIEUMAYBAY);
		// tra ve mau cu
		gotoxy(vitriX + 1, wherey());
		Input();
		cout << " So hieu may bay: " << x.SoHieuMB;
		gotoxy(96, wherey() + 1);

		Search = binarySearch_CBnMB(CBnMB.MBnCB, CBnMB.index, x.SoHieuMB);
		
		if (Search == -1)
		{
			int tempX = wherex(), tempY = wherey();
			gotoxy(tempX, tempY);
			Error("May Bay Khong Ton Tai !");
			Sleep(1000);
			gotoxy(tempX, tempY);
			Clean("May Bay Khong Ton Tai !", 7);
			x.SoHieuMB.clear();
			gotoxy(vitriX + 1, wherey() - 1);
			InputHighLight();
			cout << " So hieu may bay:           ";
			gotoxy(0, wherey() - 1);
		}
		else if (Search == -2)
		{
			Error("Danh sach may bay rong, vui long cap nhat danh sach may bay");
			Sleep(1000);
			CleanRow("Danh sach may bay rong, vui long cap nhat danh sach may bay");

			x.SoHieuMB.clear();
			break;
		}
		else
		{
			bool KT = QuanHeMBVaCB(CBnMB, x.NgayGioBay, Search); // biến kiểm tra quan hệ máy bay và chuyến bay
				if (KT == false)
				{
					int tempX = wherex(), tempY = wherey();
					gotoxy(tempX, tempY);
					Error("May bay trung lich");
					Sleep(1000);
					gotoxy(tempX, tempY);
					Clean("May bay trung lich", 7);
					x.SoHieuMB.clear();
					gotoxy(vitriX + 1, wherey() - 1);
					InputHighLight();
					cout << " So hieu may bay:           ";
					gotoxy(0, wherey() - 1);
				}
				else
				{
					NodeDataCBnMB *p = new NodeDataCBnMB();
					p->data.NgayGioBay = x.NgayGioBay;
					p->data.MaCB = x.MaCB;
					p->pketiep = NULL;
					Insert_Order_CBnMB(CBnMB.MBnCB[Search].list, p);
					break;
				}
			}
	} while (true);
	// x.soVeDaBan = temp;// lấy vị trí máy bay trong danh sách
}

NODECB *khoitaoNODE(ChuyenBay x)
{
	NODECB *p = new NODECB;
	p->info.MaCB = x.MaCB;
	p->info.NgayGioBay = x.NgayGioBay;
	p->info.SanBayDen = x.SanBayDen;
	p->info.SoHieuMB = x.SoHieuMB;
	p->info.TrangThai = x.TrangThai;
	p->info.soVeDaBan = x.soVeDaBan;
	p->pketiep = NULL;
	return p;
}

void chencuoi(LISTCB &i, NODECB *p)
{
	if (i.phead == NULL)
	{
		i.phead = i.ptail = p;
	}
	else
	{
		i.ptail->pketiep = p;
		i.ptail = p;
	}
}

void Insert_Order(LISTCB &i, NODECB *p)
{
	LISTCB k;
	for (k.ptail = i.phead; k.ptail != NULL && k.ptail->info.MaCB < p->info.MaCB; k.ptail = k.ptail->pketiep)
	{
		k.phead = k.ptail;
	}
	if (k.ptail == i.phead)
	{
		p->pketiep = i.phead;
		i.phead = p;
	}
	else
	{
		p->pketiep = k.ptail;
		k.phead->pketiep = p;
	}
}

// chuyen nay chua co hanh khach nao dat ve
void HuyChuyen(LISTCB &l)
{
	// in danh sach CB
	gotoxy(0, 1 + ITEMMENUCBAY);
	Normal();
	XuatDSCB(l);

	if (l.phead == NULL)
	{
		cout << "\nDanh sach rong" << endl;
		return;
	}
	string MaCB;
	do
	{
		gotoxy(95, 7);
		cout << "Nhap ma chuyen bay muon huy: ";
		getline(cin, MaCB);
		string kq;
		NODECB * a = binarySearch(l, MaCB);
		if (a != NULL && (a->info.TrangThai == 1 || a->info.TrangThai == 2) && a->info.soVeDaBan == 0)
		{
			gotoxy(95, wherey());
			cout << "Ban co chac muon huy ?\n";
			select2(kq, 95 + 5, wherey(), "CO", "KHONG", 10);
			if (kq == "CO")
			{
				a->info.TrangThai = 0;
				
				break;
			}
			else if (kq == "KHONG")
			{
				break;
			}
		}
		else
		{
			gotoxy(95, wherey());
			CleanNBack("Chuyen Bay Khong The Huy");
			break;
		}
	} while (true);
}

void Xoa_CB(LISTCB &i, string a)
{
	// nếu danh sách rỗng thì không làm gì hết
	if (i.phead == NULL)
	{	
		CleanNBack("Khong co chuyen bay nao");
		return;
	}
	NODECB *g;
	if (i.phead->info.MaCB == a)
	{
		g = i.phead;
		i.phead = i.phead->pketiep;
		
		delete g;
	}
	//g = new NODECB; // node g là node trỏ đến node nằm trước node cần xóa: x
	// duyệt danh sách liên kết đơn để tìm
	for (NODECB *k = i.phead; k != NULL; k = k->pketiep)
	{
		// phát hiện phần tử cần xóa
		if (k->info.MaCB == a)
		{
			g->pketiep = k->pketiep; // cập nhật mối liên kết giữa node k với node sau node h
			delete k; // xóa node nằm sau node k	
			return;
		}
		g = k; // cho node g trỏ đến node k
	}
}

void Sua_CB(LISTCB &cb, ListMB &mb, ListCBnMB &CBnMB)
{
	if (cb.phead == NULL)
	{
		CleanNBack("Khong co chuyen bay nao");
		return;
	}
	string iD_CB;
	NhapKiTuKSpace(iD_CB, MaxIDCB);
	for (NODECB *k = cb.phead; k != NULL; k = k->pketiep)
	{
		if (k->info.MaCB == iD_CB && k->info.soVeDaBan == 0 && k->info.TrangThai == 1)
		{
			string luachon;
			int vtX = wherex();
			gotoxy(95, wherey() + 1);
			cout << "Ban con chac muon sua doi thong tin: ";
			select2(luachon, wherex(), wherey(), "YES", "NO", 10);
			if (luachon == "YES")
			{
				// in DS chuyen bay
				gotoxy(0, 1 + ITEMMENUCBAY);
				Normal();
				XuatDSCB(cb);
				int Search = binarySearch_CBnMB(CBnMB.MBnCB, CBnMB.index, k->info.SoHieuMB);
				Xoa_CBnMB(CBnMB.MBnCB[Search].list, k->info.MaCB);
				// them lai chuyen bay
				NhapCB_KhongMaCB(k->info, mb, CBnMB);

				break;
			}
		}
		else if(k->info.MaCB == iD_CB && (k->info.soVeDaBan != 0 || k->info.TrangThai != 1))
		{
			// in loi "Chuyen bay nay khong duoc phep sua"
			XuongDong();
			CleanNBack("Chuyen bay nay khong duoc phep sua");

		}
	}
}

void NhapVe(VeMB &x, TREE t)
{
	cout << "Nhap CMMD: ";
	NhapSo(x.CMND, SoCMND);
	NodeHK* hk = TimKiemHK(t, x.CMND);
	if (hk == NULL)
	{
		cout << "Hanh khach khong ton tai";
		ThemNode(t, hk->HanhKhach);
	}
	else
	{
		XuatHK(hk->HanhKhach);
	}
}

int TimViTriVe(VeMB *a, string ChoNgoi, int SoGhe)
{
	for (int i = 0; i < SoGhe; i++)
	{
		if (a[i].maVe == ChoNgoi && a[i].CMND.empty() == true)
		{
			return i;
		}
	}
	return -1;
}

bool TimCMNDTrongVe(VeMB *a, int SoGhe, string CMND)
{
	for (int i = 0; i < SoGhe; i++)
	{	

		if (SoSanhKiTu( CMND, a[i].CMND) == 0)
		{
			return false;
		}
	}
	return true;
}

void khungChonVe(VeMB* ve, int soDay, int soDong)
{
	int vtX = wherex();
	int vtY = wherey();
	int khoangcach = 4;
	khungVeMBAY(vtX, vtY, khoangcach, soDay, soDong);
	gotoxy(vtX + 1 + khoangcach, vtY);
	for (int i = 0; i < soDay*soDong; i++)
	{
		if ((i % soDong ) == 0)
		{
			if (ve[i].CMND != "")
			{
				VeMua();
				gotoxy(vtX + 1 + khoangcach, wherey() + 2);
				cout << ve[i].maVe << "    ";
			}
			else
			{
				VeTrong();
				gotoxy(vtX + 1 + khoangcach, wherey() + 2);
				cout << ve[i].maVe << "    ";
			}
		}
		else
		{ 
			if (ve[i].CMND != "")
			{
				VeMua();
				cout << ve[i].maVe << "    ";
			}
			else
			{
				VeTrong();
				cout << ve[i].maVe << "    ";
			}		
		}
			
	}
}

void XuatVe(VeMB x)
{
	cout << "CMND: " << x.CMND << endl;
	cout << "So ghe: " << x.maVe << endl;
}

// ================== Xu ly File
void ghiFileCB(ChuyenBay &x)
{
	ofstream fileout;
	fileout.open("ChuyenBay.txt", ios::out | ios::app);
	fileout << x.MaCB << ",";
	fileout << x.NgayGioBay.Phut << ",";
	fileout << x.NgayGioBay.Gio << ",";
	fileout << x.NgayGioBay.Ngay << ",";
	fileout << x.NgayGioBay.Thang << ",";
	fileout << x.NgayGioBay.Nam << ",";
	removeSpace(x.SanBayDen);
	fileout << x.SanBayDen << ",";
	fileout << x.TrangThai << ",";
	fileout << x.SoHieuMB << ",";
	fileout << x.soVeDaBan << endl;
	fileout.close();
}

void ghiDSCB(LISTCB &l)
{
	for (NODECB *i = l.phead; i != NULL; i = i->pketiep)
	{
		ghiFileCB(i->info);
	}
}

void nhapCBchoFile(ChuyenBay &x, string maCB, int phut, int gio
	, int ngay, int thang, int nam, string sanBay, int trangThai, string soHieu, int soVeDB)
{
	cout << "\nLoad chuyen bay" << endl;
	cout << maCB << endl;
	cout << phut << endl;
	cout << gio << endl;
	cout << ngay << endl;
	cout << thang << endl;
	cout << nam << endl;
	cout << sanBay << endl;
	cout << trangThai << endl;
	cout << soHieu << endl;
	cout << soVeDB << endl;
	//system("pause");
	x.MaCB = maCB;
	x.NgayGioBay.Phut = phut;
	x.NgayGioBay.Gio = gio;
	x.NgayGioBay.Ngay = ngay;
	x.NgayGioBay.Thang = thang;
	x.NgayGioBay.Nam = nam;
	addSpace(sanBay);
	x.SanBayDen = sanBay;
	x.TrangThai = trangThai;
	x.SoHieuMB = soHieu;
	x.soVeDaBan = soVeDB;
}

void nhapDSCBchoFile(LISTCB &l, ListMB mb, string maCB, int phut, int gio
	, int ngay, int thang, int nam, string sanBay, int trangThai, string soHieu, int soVeDB)
{
	//cout << "Nhap chuyen bay";
	if (maCB.empty() == true) return;

	//cout << "\nCo chuyen bay";
	ChuyenBay cb;
	nhapCBchoFile(cb, maCB, phut, gio, ngay, thang, nam, sanBay, trangThai, soHieu, soVeDB);
	NODECB *p = khoitaoNODE(cb);
	int Search = TimkiemMB(mb, p->info.SoHieuMB); // tim vi tri may bay
	if (Search != -1)
	{
		p->info.DSVe = khoitaoVe(p->info.DSVe, mb.DSMB[Search]->soDay, mb.DSMB[Search]->soDong);
		cout << "Khoi tao ve" << mb.DSMB[Search]->soDay << mb.DSMB[Search]->soDong << endl;
	}
	else
	{
		p->info.DSVe = NULL;
	}
	Insert_Order(l, p);

}

void docFileCB(ListMB &lmb, LISTCB &lcb)
{
	ifstream filein;
	filein.open("ChuyenBay.txt", ios::in );
	
	int temp; 
	while (!filein.eof())
	{
		string n, data;
		string maCB, sanBay, soHieu;
		int trangThai, gio, phut, ngay, thang, nam, soVeDB;
		char thongtin[40];

		filein >> thongtin; // dua thong tin vao bien
		cout << "Du lieu lay trong file: "<< thongtin << endl;
		if (thongtin == NULL) 
		{
			break;
		}
		int count = 1;
		// tach thong tin ra cac bien nho
		for (int i = 0; i < 40; i++) // do dai bien thongtin chua gom ca ','
		{

			if (thongtin[i] == NULL ) // neu chuoi rong thi break		
			{			
				if (count == 10) 
				{
					chuyenso(data, temp);
					soVeDB = temp;
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
				if (count == 1)	maCB = data;
				if (count == 2)
				{			
					chuyenso(data, temp);
					phut = temp;
				}
				if (count == 3)
				{
					chuyenso(data, temp);
					gio = temp;
				}				
				if (count == 4) {
					chuyenso(data, temp);
					ngay = temp;
				}			
				if (count == 5) {
					chuyenso(data, temp);
					thang = temp;
				}
				if (count == 6) {
					chuyenso(data, temp);
					nam = temp;
				}
				if (count == 7) sanBay = data;
				if (count == 8)
				{
					chuyenso(data, temp);
					trangThai = temp;
				}
				if (count == 9) soHieu = data;
				if (count == 10)
				{
					chuyenso(data, temp);
					soVeDB = temp;
					break;
				}			
				count++;
				//cout <<"data " << data <<endl;
				data.clear();
			} // end else
		} // end for

		getline(filein, n); // lay dau enter cuoi day ra									
		// luu vao danh sach chuyen bay
		nhapDSCBchoFile(lcb, lmb, maCB, phut, gio, ngay, thang, nam, sanBay, trangThai, soHieu, soVeDB);
	} // end while

	filein.close();
}

void ghiFileDatVe(ChuyenBay &x, VeMB ve)
{
	ofstream fileout;
	fileout.open("DatVe.txt", ios::out | ios::app);
	fileout << x.MaCB << ",";
	fileout << ve.CMND << ",";
	fileout << ve.maVe << endl;
	fileout.close();
}

void ghiDSDV(LISTCB &lcb, ListMB &mb)
{
	for (NODECB *i = lcb.phead; i != NULL; i = i->pketiep)
	{
		NODECB *e = binarySearch(lcb, i->info.MaCB);
		int SoGhe = GetSoGhe(mb, e->info.SoHieuMB);

		for (int k = 0; k < SoGhe; k++)
		{			
			if (i->info.DSVe[k].CMND != "")
			{
				ghiFileDatVe(i->info, i->info.DSVe[k]);
			}
		}
	}
}

// =================== Ket thuc xu ly File

int MenuCBAY(LISTCB &l, ListMB mb, ListCBnMB &CBnMB)
{
	ShowConsoleCursor(false);
	while (true) {
		system("cls");
		string tenMenu = "QUAN LY CHUYEN BAY";
		int luachon;
		//luachon = MenuDong(menuCBAY, ITEMMENUCBAY, tenMenu);
		khungCB();

		// in danh sach CB
		gotoxy(0, 1 + ITEMMENUCBAY);
		Normal();
		XuatDSCB(l);

		BatPhimChucNang(luachon);		
		xoaManhinhTrai();
		if (luachon == 1) // Ins
		{
			gotoxy(10, dong + ITEMMENUCBAY);
			Normal();
			ChuyenBay cb;
			NhapCB(cb, mb, l, CBnMB);
			NODECB *p = khoitaoNODE(cb); // so hieu MB luu tam vao soVeDaBan de tim vi tri
			p->info.DSVe = khoitaoVe(p->info.DSVe, mb.DSMB[p->info.soVeDaBan]->soDay, mb.DSMB[p->info.soVeDaBan]->soDong);
			p->info.soVeDaBan = 0;
			Insert_Order(l, p);
		}
		if (luachon == 2) // F1
		{
			gotoxy(0, 1 + ITEMMENUCBAY);
			Normal();
			XuatDSCB(l);
			system("pause");
		}
		if (luachon == 3) // Del
		{
			gotoxy(95, dong + ITEMMENUCBAY);
			NODECB *p;
			do
			{
				string a;
				cout << "Nhap id chuyen bay muon xoa:           ";
				LuiVe(10);
				NhapKiTuKSpace(a, MaxIDCB);
				p = binarySearch(l, a);
				if (p != NULL)
				{
					if (p->info.soVeDaBan == 0 && p->info.TrangThai == 1 )
					{
						int SearchCBnMB = binarySearch_CBnMB(CBnMB.MBnCB, CBnMB.index, p->info.SoHieuMB);
						Xoa_CBnMB(CBnMB.MBnCB[SearchCBnMB].list, p->info.MaCB);
						Xoa_CB(l, a);
						XuongDong();
						ChiThi("Xoa thanh cong");
						Sleep(1000);
					}
					else if (p->info.soVeDaBan != 0 || p->info.TrangThai != 1)
					{
						XuongDong();
						CleanNBack("Chuyen bay khong duoc phep xoa");
					}
				}
				else 
				{
					//XuongDong();
					//CleanNBack("Chuyen bay khong ton tai");
					gotoxy(95, wherey() - 1);
				}
			} while (p == NULL);
			Normal();
		}
		if (luachon == 4) // Home
		{
			gotoxy(95, dong + ITEMMENUCBAY);
			Normal();
			string a;
			cout << "Nhap id chuyen bay muon sua: ";
			Sua_CB(l, mb, CBnMB);

		}
		if (luachon == 8) // End
		{
			gotoxy(95, dong + ITEMMENUCBAY);
			Normal();
			HuyChuyen(l);

		}
		if (luachon == ITEMMENUCBAY) // Esc
		{
			Normal();
			cout << "\n";
			return 0;
		}
	}
}
