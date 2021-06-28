#include "HanhKhachNCB.h"
	
void AutoCapNhatTrangThai(LISTCB &i, ListMB &mb, ListQL &ql, ListCBnMB &CBnMB)
{
	if (i.phead == NULL && mb.n == 0)
	{
		return;
	}
	for (NODECB *k = i.phead; k != NULL; k = k->pketiep)
	{
		int soghe = GetSoGhe(mb, k->info.SoHieuMB);
		if (SoSanhTimeNow(k->info.NgayGioBay.Ngay, k->info.NgayGioBay.Thang, k->info.NgayGioBay.Nam, k->info.NgayGioBay.Gio, k->info.NgayGioBay.Phut) == false
			&& (k->info.TrangThai == 1
				|| k->info.TrangThai == 2))
		{
			k->info.TrangThai = 3;
			int kt = TimkiemMB(mb, k->info.SoHieuMB);
			mb.DSMB[kt]->soLanbay++;
			Xoa_QL(ql, k->info.MaCB);
			int Search = binarySearch_CBnMB(CBnMB.MBnCB, CBnMB.index, k->info.SoHieuMB);
			if (Search != -1)
			{
				Xoa_CBnMB(CBnMB.MBnCB[Search].list, k->info.MaCB);
			}
		}
		else if (k->info.soVeDaBan == soghe)
		{
			k->info.TrangThai = 2;
		}
	}
}

void Free_CB_CauF(LISTCB &i)
{
	NODECB *tam = i.phead;
	string soHieu;
	while (i.phead != NULL)
	{
		VeMB* a = i.phead->info.DSVe;
		soHieu = i.phead->info.SoHieuMB;
		tam = tam->pketiep;
		//delete a; // giai phong vung nho cua DSVe
		delete i.phead; // giai phong vung nho cua cac chuyen bay
		i.phead = tam;
	}
	khoitaodanhsach(i);
}


// tra ve true neu bang nhau
bool SoSanhNgayBay_CauF(Date NgayGio1, Date NgayGio2)
{
	if ((NgayGio1.Nam == NgayGio2.Nam) &&
		NgayGio1.Thang == NgayGio2.Thang &&
		NgayGio1.Ngay == NgayGio2.Ngay)
	{
		return true;
	}
	return false;
}

// Tim kiem va in ra danh sach chuyen bay con ve theo san bay den
void TimKiemDSCB_SBD(LISTCB listCB, string SBD, LISTCB &dscb_sbd)
{

	for (NODECB *k = listCB.phead; k != NULL; k = k->pketiep)
	{
		if (k->info.SanBayDen == SBD && k->info.TrangThai == 1)
		{
			NODECB *p = khoitaoNODE(k->info);
			chencuoi(dscb_sbd, p);
			XuatCB(k->info);
		}
	}
}

// Tim kiem va in ra danh sach chuyen bay con ve
void TimKiemDSCB_ConVe(LISTCB listCB, LISTCB &dscb_sbd)
{
	for (NODECB *k = listCB.phead; k != NULL; k = k->pketiep)
	{
		if (k->info.TrangThai == 1)
		{
			NODECB *p = khoitaoNODE(k->info);
			chencuoi(dscb_sbd, p);
			XuatCB(k->info);
		}
	}
}

// Hàm sắp xếp chính
void QuickSort(DATAMB *DSMB[], int left, int right)
{
	int i = left, j = right;
	//int pivot = DSMB[left + rand() % (right - left)]->soLanbay;
	int pivot = DSMB[((left + right) / 2)]->soLanbay;
	// chia dãy thành 2 phần
	while (i <= j) {
		while (DSMB[i]->soLanbay > pivot) ++i;
		while (DSMB[j]->soLanbay < pivot) --j;

		if (i <= j) {
			DATAMB *t = DSMB[i];
			DSMB[i] = DSMB[j];
			DSMB[j] = t;
			++i;
			--j;
		}
	}
	// Gọi đệ quy để sắp xếp các nửa
	if (left < j) QuickSort(DSMB, left, j);
	if (i < right) QuickSort(DSMB, i, right);
}

//bool SoSanhGioBay(Date NgayGio1, Date NgayGio2)
//{
//	if ((NgayGio1.Nam == NgayGio2.Nam) &&
//		NgayGio1.Thang == NgayGio2.Thang &&
//		NgayGio1.Ngay == NgayGio2.Ngay &&
//		NgayGio1.Gio == NgayGio2.Gio &&
//		NgayGio1.Phut == NgayGio2.Phut)
//	{
//		return true;
//	}
//	return false;
//}

// kiểm tra logic một người chỉ đặt 1 chuyến bay cùng 1 thời điểm
bool KTNguoiNCB(ListQL ql, string CMND, Date NgayGioBay) // kiểm tra logic một người chỉ đặt 1 chuyến bay cùng 1 thời điểm
{
	for (NodeQL *i = ql.phead; i != NULL; i = i->pNext)
	{
		if (i->info.CMND == CMND)
		{
			if (i->info.NgayBay.Nam == NgayGioBay.Nam
				&& i->info.NgayBay.Thang == NgayGioBay.Thang
				&& i->info.NgayBay.Ngay == NgayGioBay.Ngay
				&& i->info.NgayBay.Gio == NgayGioBay.Gio
				/*&& i->info.NgayBay.Phut == NgayGioBay.Phut*/)
			{
				return false;
			}
		}
	}
	return true;
}

//Tim kiem chuyen bay theo ngay voi dieu kien sbd
void TimeKiemCB_Ngay(LISTCB dscb_sbd, Date NgayGioBay) 
{
	for (NODECB *k = dscb_sbd.phead; k != NULL; k = k->pketiep)
	{
		if (SoSanhGioBay(k->info.NgayGioBay, NgayGioBay) == true)
		{
			XuatCB(k->info);
		}
		else
		{
			//Error("\nKhong ton tai lua chon");
			Error("\nKhong co chuyen bay phu hop"); 
			Sleep(1200);
			CleanRow("Khong co chuyen bay phu hop");
		}
	}
}

//Tim kiem chuyen bay theo ngay voi dieu kien sbd & date
void TimeKiemCB_SBDnNgay(LISTCB dscb_sbd, Date NgayGioBay, ListMB listMB)
{
	int dem = 0;
	for (NODECB *k = dscb_sbd.phead; k != NULL; k = k->pketiep)
	{
		if (SoSanhNgayBay_CauF(k->info.NgayGioBay, NgayGioBay) == true)
		{
			XuatCB_VeTrong(k->info, dscb_sbd, listMB);
			dem++;
		}
	}
	if (dem == 0)
	{
		Error("\nKhong co chuyen bay phu hop");
		Sleep(1200);
		CleanRow("Khong co chuyen bay phu hop");
	}
}

void NhapDSVe(VeMB *a, int SoDay, int SoDong, int &SoVeDaBan, TREE &t, ListQL &listQL, Date NgayGioBay)
{
	int SoGhe = SoDay*SoDong;
	string temp, temp1;
	bool KTNguoi, KTVe;
	int dem = 0;
	int vtX = wherex();//95
	int vtY = wherey();//7
	do
	{
		gotoxy(vtX, vtY + 1);
		cout << "Nhap CMMD:           ";
		LuiVe(10);
		NhapSo(temp1, SoCMND);
		KTVe = TimCMNDTrongVe(a, SoGhe, temp1); // ktra xem ve dc dat chua
		KTNguoi = KTNguoiNCB(listQL, temp1, NgayGioBay); // ktra xem nguoi do da dat ve tren chuyen bay nay chua
		if (KTVe == false)
		{
			gotoxy(95, wherey() + 1);
			CleanNBack("Ban da mua ve roi");
		}
		else if (KTNguoi == false)
		{
			gotoxy(95, wherey() + 1);
			CleanNBack("Ban da trung lich bay");
		}
	
		NodeHK* hk = TimKiemHK(t, temp1);
		if (hk == NULL)
		{
			// khong co thong tin thi yeu cau nhap
			cout << endl;
			gotoxy(95, wherey());
			CleanNBack("Khong co thong tin khach hang");
			//ChiThi("Vui long cung cap thong tin\n");
			cout << "Ban co muon them thong tin ?\n";
			string lc;
			select2(lc, 95 + 5, wherey(), " YES ", " NO ", 10);
			if (lc == " YES ")
			{
				// nhap moi hanh khach
				DATAHK x;
				x.CMND = temp1;
				NhapHKkhongCMND(x);
				ThemNode(t, x);
				NodeQL *p = new NodeQL();
				p->info.CMND = temp1;
				p->info.NgayBay = NgayGioBay;
				Insert_OrderQL(listQL, p);
				break;
			}
			else
			{
				// nhap lai cmnd
				Normal();
				gotoxy(95, wherey());
				cout << "                                  ";
				gotoxy(95, wherey() - 1);
				cout << "                                  ";
			}
		}
		else
		{
			// co thong tin thi xuat ra man hinh
			xoaManhinhTrai();
			veManhinhXuatHK(0, 1 + ITEMMENUCBAY);
			XuatHK(hk->HanhKhach);
			break;
			system("pause");
		}
	} while (true);

	xoaManhinhTrai();
	gotoxy(15, vtY);
	khungChonVe(a, SoDay, SoDong);

	do
	{
		xoaManhinhPhai();
		gotoxy(vtX, vtY);

		cout << "Nhap cho ngoi: ";
		NhapChoNgoi(temp, MaxChoNgoi);
		UpperCase(temp);
		int ChoNgoi = TimViTriVe(a, temp, SoGhe);
		if (ChoNgoi == -1)
		{
			gotoxy(95, wherey() + 1);
			Error("Cho ngoi khong hop le");
			Sleep(1000);
			if (dem >= 3)
			{
				gotoxy(95, wherey() + 1);
				Error("Ban da nhap sai qua nhieu");
				Sleep(1000);
				return;
			}
			dem++;
		}
		else
		{
			string luachon;
			gotoxy(95, wherey());
			cout << "Ban chon cho ngoi nay ?\n";
			select2(luachon, 95 + 5, wherey(), " YES ", " NO ", 10);
			if (luachon == " YES ")
			{
				a[ChoNgoi].CMND = temp1;
				break;
			}
			
		}

	} while (true);
	Sleep(1000);
	//xoaManhinhTrai();
	gotoxy(15, vtY);
	khungChonVe(a, SoDay, SoDong);
	Sleep(1500);
	SoVeDaBan++;
}

void NhapDSVeChoFile(VeMB *a, int SoDay, int SoDong, int &SoVeDaBan
	, TREE &t, Date NgayGioBay, string cmnd, string maVe)
{
	int SoGhe = SoDay*SoDong;
	NodeQL *p = new NodeQL();
	p->info.CMND = cmnd;
	p->info.NgayBay = NgayGioBay;
	//Insert_OrderQL(listQL, p);
	int ChoNgoi = TimViTriVe(a, maVe, SoGhe);
	a[ChoNgoi].CMND = cmnd;
	SoVeDaBan++;
}

void DatVe(LISTCB &listCB, TREE &t, ListMB &listMB, ListQL &listQL)
{
	if (listCB.phead == NULL)
	{
		return;
	}
	xoaManhinhTrai();
	LISTCB dscb_conve;
	khoitaodanhsach(dscb_conve);

	// in header
	SetColor(11);
	gotoxy(0, 7);
	cout << " Ma chuyen bay"
		<< "\t San bay den"
		<< "\t     Ma may bay"
		<< "\t\t Thoi gian"
		<< "\t\t Trang thai" << endl;
	//XuatDSCB(listCB); 
	TimKiemDSCB_ConVe(listCB, dscb_conve);


	int dem = 0;
	LISTCB dscb_sbd;
	khoitaodanhsach(dscb_sbd); // mang phu dung de loc CB theo san bay den
	string SanBayDen;

	do
	{
		xoaManhinhPhai();
		gotoxy(95, 7);
		cout << "Nhap san bay den: ";
		NhapChu(SanBayDen, MaxSanBayDen); 
		xoakhoangtrang(SanBayDen);
		suakitu(SanBayDen);

		xoaManhinhTrai();
		cout << endl;
		TimKiemDSCB_SBD(listCB, SanBayDen, dscb_sbd);
		if (dscb_sbd.phead == NULL)
		{
			gotoxy(95, wherey());
			CleanNBack("Khong co chuyen bay hop le !");
			// in header
			SetColor(11);
			gotoxy(0, 7);
			cout << " Ma chuyen bay"
				<< "\t San bay den"
				<< "\t     Ma may bay"
				<< "\t\t Thoi gian"
				<< "\t\t Trang thai" << endl;; 
			TimKiemDSCB_ConVe(listCB, dscb_conve);
			if (dem >= 3)
			{
				gotoxy(95, 9);
				Error("Ban da nhap sai qua nhieu");
				Sleep(1000);
				return;
			}
			dem++;
		}
		else
		{
			// in header
			SetColor(11);
			gotoxy(0, 7);
			cout << " Ma chuyen bay"
				<< "\t San bay den"
				<< "\t     Ma may bay"
				<< "\t\t Thoi gian"
				<< "\t\t Trang thai" << endl;
			//TimKiemDSCB_SBD(listCB, SanBayDen, dscb_sbd);
			break;
		}
	} while (true);
	dem = 0; // reset dem
	NODECB *e;

	do
	{
		gotoxy(95, wherey());
		Normal();
		cout << "Nhap Ma Chuyen Bay Ban Muon:                     ";
		LuiVe(20);
		NhapKiTuKSpace(SanBayDen, MaxIDCB);
		e = binarySearch(dscb_sbd, SanBayDen);

		XuongDong();
		if (e == NULL)
		{
			gotoxy(wherex(), wherey() - 1);
			dem++;
		}
		/*else if (e->info.TrangThai == 3 || e->info.TrangThai == 0)
		{
			gotoxy(95, wherey() + 1);
			CleanNBack("Chuyen bay khong duoc truy cap");
			gotoxy(95, wherey() - 1);
			dem++;
		}*/

		if (dem >= 3)
		{
			gotoxy(95, wherey() + 1);
			Error("Ban da nhap sai qua nhieu");
			Sleep(1000);
			return;
		}

		gotoxy(wherex(), wherey() - 1);
	} while (e == NULL || e->info.TrangThai == 3 || e->info.TrangThai == 0);
	//int SoGhe = GetSoGhe(listMB, e->info.SoHieuMB);

	int SoDay = listMB.DSMB[TimkiemMB(listMB, e->info.SoHieuMB)]->soDay;
	int SoDong = listMB.DSMB[TimkiemMB(listMB, e->info.SoHieuMB)]->soDong;
	gotoxy(95, wherey()+1);
	e = binarySearch(listCB, SanBayDen); // tim CB trong ds chinh
	NhapDSVe(e->info.DSVe, SoDay, SoDong, e->info.soVeDaBan, t, listQL, e->info.NgayGioBay);

	// giai phong 2 ds phu
	Free_CB_CauF(dscb_conve);
	Free_CB_CauF(dscb_sbd);
}

void DatVechoFile(LISTCB &listCB, TREE &t, ListMB &listMB, string maCB, string cmnd, string maVe)
{
	if (maCB == "") return;

	cout << "Ma CB =" << maCB <<endl;
	cout << "CMND =" << cmnd << endl;
	cout << "Ma Ve =" << maVe << endl;

	NODECB *e = binarySearch(listCB, maCB);
	//int SoGhe = GetSoGhe(listMB, e->info.SoHieuMB);
	int SoDay = listMB.DSMB[TimkiemMB(listMB, e->info.SoHieuMB)]->soDay;
	int SoDong = listMB.DSMB[TimkiemMB(listMB, e->info.SoHieuMB)]->soDong;

	NhapDSVeChoFile(e->info.DSVe, SoDay, SoDong, e->info.soVeDaBan, t, e->info.NgayGioBay, cmnd, maVe);

}

int TimCMNDinVe(VeMB *a, string CMND, int SoGhe)
{
	for (int i = 0; i < SoGhe; i++)
	{
		if (a[i].CMND == CMND)
		{
			return i;
		}
	}
	return -1;
}

void HuyVe(LISTCB &listCB, TREE &t, ListMB &listMB, ListQL &listQL)
{	
	NODECB *e;
	string MCB;
	int SoGhe;
	int dem = 0;

	do
	{
		do
		{
			xoaManhinhTrai();
			gotoxy(0, 1 + ITEMMENUCBAY);
			Normal();
			XuatDSCB(listCB);

			xoaManhinhPhai();
			gotoxy(95, 7);
			cout << "Nhap ma chuyen bay can huy:                     ";
			LuiVe(20);
			NhapKiTuKSpace(MCB, MaxIDCB);
			e = binarySearch(listCB, MCB);

			XuongDong();
			if (e == NULL)
			{
				CleanNBack("Chuyen bay khong ton tai");				
				gotoxy(95, wherey() - 1);
				dem++;
			}
			else if (e->info.TrangThai == 3 || e->info.TrangThai == 0)
			{
				gotoxy(95, wherey() + 1);
				CleanNBack("Chuyen bay khong duoc truy cap");
				gotoxy(95, wherey() - 1);
				dem++;
			}
			if (dem >= 3)
			{
				XuongDong();
				Error("Ban da nhap sai qua nhieu");
				Sleep(1000);
				return;
			}
		} while (e == NULL || e->info.TrangThai == 3 || e->info.TrangThai == 0);

		SoGhe = GetSoGhe(listMB, e->info.SoHieuMB);
		
		xoaManhinhTrai();
		// in header 
		SetColor(11);
		gotoxy(0, 7);
		cout << "Ma chuyen bay"
			<< "\t San bay den"
			<< "\t     Ma may bay"
			<< "\t\t Thoi gian"
			<< "\t\t Trang thai" << endl;
		XuatCB(e->info);
		xoaManhinhPhai();
		string choice;
		
		gotoxy(95, 7);
		cout << "Co phai chuyen bay nay ?" << endl;

		select2(choice, 98, wherey(), " YES ", " NO ", 10);

		if (choice == " YES ")
		{
			if (e->info.soVeDaBan == 0)
			{
				XuongDong();
				CleanNBack("Danh sach ve rong");
			}
			else
			{
				break;
			}
				
		}
		else
			xoaManhinhPhai();

	} while (true);

	// in khung ve cua chuyen bay do ra
	int SoDay = listMB.DSMB[TimkiemMB(listMB, e->info.SoHieuMB)]->soDay;
	int SoDong = listMB.DSMB[TimkiemMB(listMB, e->info.SoHieuMB)]->soDong;

		// xuất khung vé 

	xoaManhinhTrai();
	gotoxy(15, 10);
	khungChonVe(e->info.DSVe, SoDay, SoDong);

	int vitri;
	dem = 0;

	do
	{
		xoaManhinhPhai();
		Normal();
		cout << "Nhap CMND: ";
		MCB.clear();
		NhapSo(MCB, SoCMND);

		

		vitri = TimCMNDinVe(e->info.DSVe, MCB, SoGhe);
		if (vitri == -1)
		{
			XuongDong();
			CleanNBack("Hanh khach khong co trong chuyen bay");
			if (dem >= 3)
			{
				XuongDong();
				Error("Ban da nhap sai qua nhieu");
				Sleep(1000);
				return;
			}
			dem++;
		}
		else
		{
			XuongDong();
			XuongDong();
			cout << "So ghe cua ban la: " << e->info.DSVe[vitri].maVe;
			NodeHK *tempHK = TimKiemHK(t, MCB);
			veManhinhXuatHK(0, 1 + ITEMMENUCBAY);		
			XuatHK(tempHK->HanhKhach);
		}
	} while (vitri == -1);

	XuongDong();
	cout << "Ban chac chan huy ?\n";
	string choice;
	select2(choice, 95 + 5, wherey(), " YES ", " NO ", 10);
	if (choice == " YES ")
	{
		Xoa_QL_2(listQL, e->info.MaCB, e->info.DSVe[vitri].CMND);
		e->info.DSVe[vitri].CMND.clear();
		e->info.soVeDaBan--;
		XuongDong();
		ChiThi("Da huy ve");
		Sleep(1000);
	}
	else
	{
		return;
	}
	
}

void docFileDV(LISTCB &listCB, TREE &t, ListMB &listMB)
{
	ifstream filein;
	filein.open("DatVe.txt", ios::in);

	int temp;
	while (!filein.eof())
	{
		string n, data;
		string maCB, cmnd, maVe;

		char thongtin[30];

		filein >> thongtin; // dua thong tin vao bien
		cout << "Du lieu lay trong file: " << thongtin << endl;
		if (thongtin == NULL)
		{
			break;
		}
		int count = 1;
		// tach thong tin ra cac bien nho
		for (int i = 0; i < 30; i++) // do dai bien thongtin chua gom ca ','
		{
			if (thongtin[i] == NULL) // neu = null thi break;		
			{
				if (count == 3)
				{
					maVe = data;
					cout << maVe;
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
				if (count == 2) cmnd = data;
				if (count == 3) maVe = data;

				count++;
				cout << "data " << data << endl;
				data.clear();
			} // end else
		} // end for

		getline(filein, n); // lay dau enter cuoi day ra	
		// luu vao danh sach chuyen bay
		DatVechoFile(listCB, t, listMB/*, listQL*/, maCB, cmnd, maVe);
	} // end while

	filein.close();
}

void DSHanhKhachTrenCB(ListMB listMB, TREE listHK, LISTCB listCB)
{
	string MaCB, SanBay;

	Normal();
	system("cls");
	XuatDSCB(listCB);
	system("pause");
	
	system("cls");
	cout << "Nhap ma chuyen bay: ";
	NhapKiTuKSpace(MaCB, MaxIDCB);
	NODECB *cb = binarySearch(listCB, MaCB);
	int SoGhe = GetSoGhe(listMB, cb->info.SoHieuMB);

	
	cout << "\n\t\t DANH SACH HANH KHACH THUOC CHUYEN BAY " << MaCB << endl;
	cout << "\nNgay gio khoi hanh: ";
	if (cb->info.NgayGioBay.Ngay < 10) cout << "0" << cb->info.NgayGioBay.Ngay << "/";
	else cout << cb->info.NgayGioBay.Ngay << "/";
	if (cb->info.NgayGioBay.Thang < 10) cout << "0" << cb->info.NgayGioBay.Thang << "/";
	else cout << cb->info.NgayGioBay.Thang << "/";
	cout << cb->info.NgayGioBay.Nam << " ";
	if (cb->info.NgayGioBay.Gio < 10) cout << "0" << cb->info.NgayGioBay.Gio << "/";
	else cout << cb->info.NgayGioBay.Gio << "/";
	if (cb->info.NgayGioBay.Phut < 10) cout << "0" << cb->info.NgayGioBay.Phut << endl;
	else cout << cb->info.NgayGioBay.Phut << endl;
	SanBay = cb->info.SanBayDen;
	cout << "\tNoi den: " << SanBay << endl;
	cout << "\n STT     SOVE     SO CMND       HO TEN               PHAI" << endl;
	int stt = 1;
	for (int i = 0; i < SoGhe; i++)
	{
		if (cb->info.DSVe[i].CMND.empty() == false)
		{
			gotoxy(2, wherey());
			cout <<stt;
			NodeHK *hk = TimKiemHK(listHK, cb->info.DSVe[i].CMND);
			gotoxy(10, wherey());
			cout << cb->info.DSVe[i].maVe;
			gotoxy(17, wherey());
			cout << hk->HanhKhach.CMND;
			gotoxy(30, wherey());
			cout << hk->HanhKhach.Ho << " ";
			cout << hk->HanhKhach.Ten ;
			gotoxy(53, wherey());
			if (hk->HanhKhach.Phai == true)
			{
				cout << "Nam" << endl;
			}
			else
			{
				cout << "Nu" << endl;
			}
			stt++;
		}
	}
	system("pause");
}

void DSCacCBKhoiHanh(LISTCB listCB, ListMB listMB)
{
	ShowConsoleCursor(false);
	if (listCB.phead == NULL)
	{
		return;
	}

	//int dem = 0;
	LISTCB dscb_sbd;
	khoitaodanhsach(dscb_sbd); // DS phu dung de luu chuyen bay du dieu kien
	string SanBayDen;
	Date NgayGioBay;

	khungDatHuyVe();
	gotoxy(0, 1 + ITEMMENUCBAY);
	Normal();
	XuatDSCB(listCB);

	do
	{
		xoaManhinhPhai();
		gotoxy(95, 7);
		cout << "Nhap san bay den: ";
		NhapChu(SanBayDen, MaxSanBayDen);
		xoakhoangtrang(SanBayDen);
		suakitu(SanBayDen);

		gotoxy(95, 8);
		cout << "Nhap thoi gian bay: ";

		NhapNgayBay_CauF(NgayGioBay);
		gotoxy(0, wherey());
		
		xoaManhinhTrai();
		cout << endl;

		TimKiemDSCB_SBD(listCB, SanBayDen, dscb_sbd);
		xoaManhinhTrai(); // moi dat dieu kien san bay nen k cho xuat ra
		if (dscb_sbd.phead == NULL)
		{
			gotoxy(95, wherey());
			CleanNBack("Khong co chuyen bay hop le !");
		}
		else
		{
			// in header
			SetColor(11);
			gotoxy(0, 7);
			cout << " Ma chuyen bay"
				<< "\t San bay den"
				<< "\t     Ma may bay"
				<< "\t\t Thoi gian"
				<< "\t\t So ve trong" << endl;
			TimeKiemCB_SBDnNgay(dscb_sbd, NgayGioBay, listMB);
			system("pause");
			break;
		}
	} while (true);
	Free_CB_CauF(dscb_sbd); // giai phong ds phu
}

void DSCacVeTrongTrenCB(LISTCB listCB, ListMB listMB)
{
	int vtX = wherex();
	int vtY = wherey();
	int khoangcach = 4;
	string maCB;
	NODECB *e;
	Normal();
	cout << "Nhap Ma Chuyen Bay Ban Muon:           ";
	LuiVe(10);
	NhapKiTuKSpace(maCB, MaxIDCB);
	e = binarySearch(listCB, maCB);

	VeMB* ve = e->info.DSVe;
	int SoDay = listMB.DSMB[TimkiemMB(listMB, e->info.SoHieuMB)]->soDay;
	int SoDong = listMB.DSMB[TimkiemMB(listMB, e->info.SoHieuMB)]->soDong;


	for (int i = 0; i < SoDay*SoDong; i++)
	{
		if ((i % SoDong) == 0)
		{
			if (ve[i].CMND != "")
			{
				VeMua();
				gotoxy(vtX + 1 + khoangcach, wherey() + 2);
				cout << "      ";
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
				cout /*<< ve[i].maVe*/ << "      ";
			}
			else
			{
				VeTrong();
				cout << ve[i].maVe << "    ";
			}
		}
		
	}
	cout << endl;
	Normal();
	system("pause");
}

void SoLuotThucHienChuyenBay(ListMB listMB)
{
	QuickSort(listMB.DSMB, 0, listMB.n - 1);

	cout << "\n So hieu may bay     Loai may bay              So luot thuc hien chuyen bay" << endl;
	for (int i = 0; i < listMB.n; i++)
	{
		gotoxy(3, wherey());
		cout << listMB.DSMB[i]->sohieuMB;
		gotoxy(21, wherey());
		cout << listMB.DSMB[i]->loaiMB;
		gotoxy(50, wherey());
		cout << listMB.DSMB[i]->soLanbay << endl;
	}
	system("pause");
}

int MenuDatHuyVe(LISTCB &listCB, TREE &t, ListMB &listMB, ListQL &listQL)
{
	ShowConsoleCursor(false);
	while (true)
	{
		int luachon;
		khungDatHuyVe();
		gotoxy(0, 1 + ITEMMENUCBAY);
		Normal();
		XuatDSCB(listCB);

		BatPhimChucNang(luachon);

		if (luachon == 1) // ins
		{
			DatVe(listCB, t, listMB, listQL);
		}
		if (luachon == 3) // del
		{
			HuyVe(listCB, t, listMB, listQL);
		}
		if (luachon == 5) // esc
		{
			Normal();

			cout << "\n";
			return 0;
		}
	}
}

int MenuTong()
{
	resizeConsole(800, 600);

	inLogo();
	iconPlane(5, 12, 70);
	inLogoRGB();
	system("pause");

	// init may bay
	ListMB listMB;
	docFileMB(listMB);
	//init hanh khach
	TREE t;
	KhoiTaoCay(t);
	docFileHK(t);

	//init chuyen bay
	LISTCB listCB;
	khoitaodanhsach(listCB);
	docFileCB(listMB, listCB);
	docFileDV(listCB, t, listMB);

	ListQL listQL;
	KhoiTaoListQL(listQL, listCB, listMB);
	
	ListCBnMB CBnMB;
	KhoiTaoListCBnMB(CBnMB, listMB, listCB);

	
	
	while (true) {
		system("cls");

		string tenMenu = "QUAN LY CHUYEN BAY NOI DIA";
		int luachon;
		/*AutoCapNhatTrangThai(listCB, listMB, listQL, CBnMB);*/
		luachon = MenuDong(menuTONG, ITEMMENUTONG, tenMenu);	
		if (luachon == 1)
		{
			resizeConsole(1100, 600);
			gotoxy(10, dong + 1 + 11);
			Normal();		
			MenuMBAY(listMB, CBnMB);
		}
		else if (luachon == 2)
		{
			resizeConsole(1100, 600);
			gotoxy(10, dong + 1 + 11);
			Normal();
			MenuHKHACH(t);
		}
		else if (luachon == 3)
		{
			resizeConsole(1100, 600);
			gotoxy(10, dong + 1 + 11);
			Normal();
			MenuCBAY(listCB, listMB, CBnMB);

		}
		else if (luachon == 4)
		{
			resizeConsole(1100, 600);
			gotoxy(10, dong + 1 + 11);
			Normal();
			MenuDatHuyVe(listCB, t, listMB, listQL);

		}
		else if (luachon == 5)
		{
			resizeConsole(1100, 600);
			gotoxy(10, dong + 1 + 11);
			Normal();
			DSHanhKhachTrenCB(listMB, t, listCB);

		}
		else if (luachon == 6)
		{
			resizeConsole(1100, 600);
			gotoxy(10, dong + 1 + 11);
			Normal();
			DSCacCBKhoiHanh(listCB, listMB);
		}
		else if (luachon == 7)
		{

			gotoxy(10, dong + 1 + 11);
			Normal();
			DSCacVeTrongTrenCB(listCB, listMB);

		}
		else if (luachon == 8)
		{
			gotoxy(10, dong + 1 + 11);
			Normal();
			SoLuotThucHienChuyenBay(listMB);
		}
		else if (luachon == ITEMMENUTONG )
		{
			Normal();
			deletaDataFile("MayBay.txt");
			ghiDSMB(listMB);
			deletaDataFile("HanhKhach.txt");
			ghiDSHK(t);
			deletaDataFile("ChuyenBay.txt");
			ghiDSCB(listCB);
			deletaDataFile("DatVe.txt");
			ghiDSDV(listCB, listMB);
			Free_CB(listCB);
			deleteTree(t);
			Free_MB(listMB);
			Free_QL(listQL);
			Free_CBnMB(CBnMB);

			cout << "\n";
			return 0;
		}

	}
}

int main()
{
	MenuTong();
	//checkmau();
	//kiemtraKBHIT();
	
	
	return 0;
}