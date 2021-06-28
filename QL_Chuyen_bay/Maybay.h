#include "Dohoa.h"
#include "HamXuLy.h"

//===============================================
struct datamb
{
	string sohieuMB;
	string loaiMB; //Boeing 747, abc xyz ....
	int soDay; // A, B, C, D, E, F, G, H,.. max la 12 day
	int soDong; // 1-20
	int soLanbay;
};
typedef struct datamb DATAMB;

typedef struct listmb
{
	int n = 0;
	DATAMB *DSMB[MAXMAYBAY];
}ListMB;

//== Quan hệ Chuyến bay và Máy Bay

struct Date
{
	int Phut;
	int Gio;
	int Ngay;
	int Thang;
	int Nam;
};

struct DataCBnMB
{
	string MaCB;
	Date NgayGioBay;
};

struct NodeDataCBnMB
{
	DataCBnMB data;
	NodeDataCBnMB *pketiep;
};

struct ListNodeDataCBnMB
{
	NodeDataCBnMB *phead;
	NodeDataCBnMB *ptail;
};

struct CBnMB
{
	string sohieuMB;
	ListNodeDataCBnMB list;
};

struct ListCBnMB
{
	CBnMB *MBnCB = new CBnMB[MAXMAYBAY];
	int index = 0;
};

void Free_NodeCBnMB(ListNodeDataCBnMB &list)
{
	NodeDataCBnMB *tam = list.phead;
	while (list.phead != NULL)
	{
		tam = tam->pketiep;
		delete list.phead;
		list.phead = tam;
	}
	list.phead = NULL;
	list.ptail = NULL;
}

void Free_CBnMB(ListCBnMB &CBnMB)
{
	for (int i = 0; i < CBnMB.index; i++)
	{
		CBnMB.MBnCB[i].sohieuMB.erase();
		Free_NodeCBnMB(CBnMB.MBnCB[i].list);
	}
	delete[] CBnMB.MBnCB; // giai phong vung nho cua DS MBnCB
	CBnMB.index = 0;
}

// Hàm sắp xếp chính
void QuickSort_MBnCB(CBnMB *DSCBnMB, int left, int right)
{
	int i = left, j = right;
	//int pivot = DSMB[left + rand() % (right - left)]->soLanbay;
	string pivot = DSCBnMB[((left + right) / 2)].sohieuMB;
	// chia dãy thành 2 phần
	while (i <= j) {
		while (DSCBnMB[i].sohieuMB < pivot) ++i;
		while (DSCBnMB[j].sohieuMB > pivot) --j;

		if (i <= j) {
			string t = DSCBnMB[i].sohieuMB;
			DSCBnMB[i].sohieuMB = DSCBnMB[j].sohieuMB;
			DSCBnMB[j].sohieuMB = t;
			++i;
			--j;
		}
	}
	// Gọi đệ quy để sắp xếp các nửa
	if (left < j) QuickSort_MBnCB(DSCBnMB, left, j);
	if (i < right) QuickSort_MBnCB(DSCBnMB, i, right);
}

void dichChuoi_CBnMB(ListCBnMB &l, int vitri) // lùi chuỗi về trái 1 đơn vị từ vị trí cho sẵn
{
	for (; vitri < l.index; vitri++)
	{
		l.MBnCB[vitri] = l.MBnCB[vitri + 1];
	}
}

int binarySearch_CBnMB(CBnMB *MBnCB, int n, string x)
{
	if (n == 0)
	{
		return -2;
	}
	int r = n - 1; // chỉ số phần tử cuối
	int l = 0; // Chỉ số phần tử đầu tiên
	while (r >= l) {
		int mid = l + (r - l) / 2; // Tương đương (l+r)/2 nhưng ưu điểm tránh tràn số khi l,r lớn

								   // Nếu arr[mid] = x, trả về chỉ số và kết thúc.
		int KiemTra = SoSanhKiTu(MBnCB[mid].sohieuMB, x);
		if (KiemTra == 0)
		{
			return mid;
		}
		// Nếu arr[mid] > x, cập nhật lại right
		if (KiemTra == 1)
		{
			r = mid - 1;
		}
		// Nếu arr[mid] < x, cập nhật lại left
		if (KiemTra == -1)
		{
			l = mid + 1;
		}
	}
	/*for (int i = 0; i < n; i++)
	{
	if (MBnCB[i].sohieuMB == x)
	{
	return i;
	}
	}*/
	// Nếu không tìm thấy
	return -1;
}

bool SoSanhGioBay(Date NgayGio1, Date NgayGio2)
{
	if ((NgayGio1.Nam == NgayGio2.Nam) &&
		NgayGio1.Thang == NgayGio2.Thang &&
		NgayGio1.Ngay == NgayGio2.Ngay &&
		NgayGio1.Gio == NgayGio2.Gio)
	{
		return false;
	}
	return true;
}


bool QuanHeMBVaCB(ListCBnMB listCbnMB, Date NgayBay, int kt)
{
	if (kt == -1)
	{
		return true;
	}
	if (listCbnMB.MBnCB[kt].list.phead == NULL)
	{
		return true;
	}
	for (NodeDataCBnMB *k = listCbnMB.MBnCB[kt].list.phead; k != NULL; k = k->pketiep)
	{
		if (SoSanhGioBay(NgayBay, k->data.NgayGioBay) == true)
		{
			return true;
		}
	}
	return false;
}

void Insert_Order_CBnMB(ListNodeDataCBnMB &list, NodeDataCBnMB *p)
{
	ListNodeDataCBnMB k;
	for (k.ptail = list.phead; k.ptail != NULL && k.ptail->data.MaCB < p->data.MaCB; k.ptail = k.ptail->pketiep)
	{
		k.phead = k.ptail;
	}
	if (k.ptail == list.phead)
	{
		p->pketiep = list.phead;
		list.phead = p;
	}
	else
	{
		p->pketiep = k.ptail;
		k.phead->pketiep = p;
	}
}

void Xoa_CBnMB(ListNodeDataCBnMB &i, string a)
{
	// nếu danh sách rỗng thì không làm gì hết
	if (i.phead == NULL)
	{
		return;
	}
	NodeDataCBnMB *g;
	if (i.phead->data.MaCB == a)
	{
		g = i.phead;
		i.phead = i.phead->pketiep;
		delete g;
	}
	//g = new NODECB; // node g là node trỏ đến node nằm trước node cần xóa: x
	// duyệt danh sách liên kết đơn để tìm
	for (NodeDataCBnMB *k = i.phead; k != NULL; k = k->pketiep)
	{
		// phát hiện phần tử cần xóa
		if (k->data.MaCB == a)
		{
			g->pketiep = k->pketiep; // cập nhật mối liên kết giữa node k với node sau node h
			delete k; // xóa node nằm sau node k	
			return;
		}
		g = k; // cho node g trỏ đến node k
	}
}
//=============================


// tra ve vi tri may bay can tim
int TimkiemMB(ListMB x, string sohieuMB) 
{
	if (x.n == NULL)
	{
		return -2;//danh sach rong
	}
	for (int i = 0; i < x.n; i++)
	{
		if (SoSanhKiTu(x.DSMB[i]->sohieuMB, sohieuMB) == 0)
		{
			return i;
		}
	}
	return -1;
}

int GetSoGhe(ListMB x, string soHieuMB)
{
	if (x.n == NULL)
	{
		return -2;//danh sach rong
	}
	for (int i = 0; i < x.n; i++)
	{
		if (x.DSMB[i]->sohieuMB == soHieuMB)
		{
			return x.DSMB[i]->soDay * x.DSMB[i]->soDong;
		}
	}
	return -1;
}

void ghiFileMB(DATAMB *x)
{
	ofstream fileout;
	fileout.open("MayBay.txt", ios::out | ios::app);
	fileout << x->sohieuMB << ",";
	fileout << x->loaiMB << ",";
	fileout << x->soDay << ",";
	fileout << x->soDong << ",";
	fileout << x->soLanbay << endl;
	fileout.close();
}

void ghiDSMB(ListMB &l)
{
	int soMB = l.n;

	for (int i = 0; i < soMB; i++)
	{
		ghiFileMB(l.DSMB[i]);
	}
}

void Free_MB(ListMB &l)
{
	for (int i = 0; i < l.n; i++)
	{
		delete l.DSMB[i]; // giai phong vung nho may bay
	}
	l.n = 0;
}

void nhapMBaychoFile(DATAMB *x, string soHieu, string loai, int day, int dong, int soLanBay)
{
		x->sohieuMB = soHieu;
		x->loaiMB = loai;
		x->soDay = day;
		x->soDong = dong;
		x->soLanbay = soLanBay;
}
void nhapDSMBaychoFile(ListMB &i, string soHieu, string loai, int day, int dong, int soLanBay)
{
	int soMB = i.n;
	if (soHieu != "")
	{
		i.DSMB[soMB] = new DATAMB();
		nhapMBaychoFile(i.DSMB[soMB], soHieu, loai, day, dong, soLanBay);
		i.n++;
	}
	else return;
	
}

void docFileMB(ListMB &l)
{
	ifstream filein;
	filein.open("MayBay.txt", ios::in);
	//int dem = 0;
	while (!filein.eof())
	{
		string n, data;
		string soHieu, loai;
		int day, dong, soLanBay;
		char thongtin[40];
		
		filein >> thongtin; // dua thong tin vao bien
		if (thongtin[1] == NULL) // neu chuoi rong thi return
			break;
		int count = 1;
		// tach thong tin ra cac bien nho
		for (int i = 0; i < 40; i++)
		{		

			if (thongtin[i] == NULL) // neu chuoi rong thi return
			{
				if (count == 5)
				{
					int temp;
					chuyenso(data, temp);
					soLanBay = temp;
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
				if (count == 1)	soHieu = data;
				if (count == 2) loai = data;
				if (count == 3)
				{
					int temp;
					chuyenso(data, temp);
					day = temp;
				}
				if (count == 4)
				{
					int temp;
					chuyenso(data, temp);
					dong = temp;
				}
				if (count == 5)
				{
					int temp;
					chuyenso(data, temp);
					soLanBay = temp;
				}
				count ++;
				data.clear();
			
			} // end else
		} // end for
		getline(filein, n); // lay dau enter cuoi day ra	

		// luu vao danh sach may bay
		nhapDSMBaychoFile(l, soHieu, loai, day, dong, soLanBay);
		//dem++;	
	} // end while
	filein.close();
}


void nhapMBay(DATAMB *x, ListMB i, ListCBnMB &CBnMB)
{
	string soDay; //bien tam 
	string soDong;// bien tam
	int vitriX = 95;
	int vitriY = wherey() + 1;
	khungNhapMBAY(vitriX, vitriY);
	do
	{
		string soHieutemp;

		fflush(stdin);
		// chuyen mau va nhap
		InputHighLight();
		gotoxy(vitriX + 1, vitriY + 1);	
		cout << " So hieu may bay:           ";
		LuiVe(10);
		NhapKiTuKSpace(soHieutemp, MAXSOHIEUMAYBAY);
		// tra ve mau cu
		gotoxy(vitriX + 1, wherey());
		Input();
		cout << " So hieu may bay: " << soHieutemp << endl;

		int temp = TimkiemMB(i, soHieutemp);
		if (temp == -1 || temp == -2)
		{
			CBnMB.MBnCB[CBnMB.index].sohieuMB = soHieutemp;
			CBnMB.MBnCB[CBnMB.index].list.phead = NULL;
			CBnMB.MBnCB[CBnMB.index].list.ptail = NULL;
			CBnMB.index++;
			QuickSort_MBnCB(CBnMB.MBnCB, 0, CBnMB.index - 1);
			x->sohieuMB = soHieutemp;

		// chuyen mau va nhap
			InputHighLight();
			gotoxy(vitriX + 1, wherey() + 1);
			cout << " Loai may bay: ";
			NhapKiTuKSpace(x->loaiMB, MAXLOAIMAYBAY);
		// tra ve mau cu
			gotoxy(vitriX + 1, wherey() );
			Input();
			cout << " Loai may bay:  " << x->loaiMB << endl;

		// chuyen mau va nhap
			InputHighLight();
			gotoxy(vitriX + 1, wherey() + 1);
			cout << " So day: ";
			NhapDongDay(soDay, MAXSODAYDONG);
			chuyenso(soDay, x->soDay);
		// tra ve mau cu
			gotoxy(vitriX + 1, wherey());
			Input();
			cout << " So day:  "<< x->soDay << endl;

		// chuyen mau va nhap
			InputHighLight();
			gotoxy(vitriX + 1, wherey() + 1);
			cout << " So dong: ";
			NhapDongDay(soDong, MAXSODAYDONG);
			chuyenso(soDong, x->soDong);
		// tra ve mau cu
			gotoxy(vitriX + 1, wherey());
			Input();
			cout << " So dong:  " << x->soDong << endl;

			x->soLanbay = 0;
			break;
		}
		else 
		{
			gotoxy(vitriX + 1, wherey());
			Error("May bay da ton tai");
			Sleep(1000);
			gotoxy(vitriX + 1, wherey()-1);
			Input();
			cout << "                      ";
		}
	} while (true);
}

void nhapMBay_KhongSoHieu(DATAMB *x)
{
	string soDay; //bien tam 
	string soDong;// bien tam
	int vitriX = 95;
	int vitriY = wherey() + 1;
	khungNhapMBAY(vitriX, vitriY);
	do
	{

		// in ra so hieu ban dau
		gotoxy(vitriX + 1, vitriY + 1);
		Input();
		cout << " So hieu may bay: " << x->sohieuMB << endl;	

		// chuyen mau va nhap
		InputHighLight();
		gotoxy(vitriX + 1, wherey() + 1);
		cout << " Loai may bay: ";
		NhapKiTuKSpace(x->loaiMB, MAXLOAIMAYBAY);
		// tra ve mau cu
		gotoxy(vitriX + 1, wherey());
		Input();
		cout << " Loai may bay:  " << x->loaiMB << endl;

		// chuyen mau va nhap
		InputHighLight();
		gotoxy(vitriX + 1, wherey() + 1);
		cout << " So day: ";
		NhapDongDay(soDay, MAXSODAYDONG);
		chuyenso(soDay, x->soDay);
		// tra ve mau cu
		gotoxy(vitriX + 1, wherey());
		Input();
		cout << " So day:  " << x->soDay << endl;

		// chuyen mau va nhap
		InputHighLight();
		gotoxy(vitriX + 1, wherey() + 1);
		cout << " So dong: ";
		NhapDongDay(soDong, MAXSODAYDONG);
		chuyenso(soDong, x->soDong);
		// tra ve mau cu
		gotoxy(vitriX + 1, wherey());
		Input();
		cout << " So dong:  " << x->soDong << endl;

		x->soLanbay = 0;
		break;
	
		
	} while (true);
}

void nhapDSMBay(ListMB &i, ListCBnMB &CBnMB)
{
	int soMB = i.n;
	i.DSMB[soMB] = new DATAMB();
	gotoxy(wherex(), wherey());
	Output();
	cout << "< May bay thu " << soMB + 1 << " >"<< endl;
	nhapMBay(i.DSMB[soMB], i, CBnMB);
	i.n++;
}

void xuatMBay(DATAMB *x)
{
	int VTx = wherex();
	int VTy = wherey();
	dongXuatMBAY(VTx, VTy);
	gotoxy(4, wherey());
	cout << x->sohieuMB;
	gotoxy(20, wherey());
	cout << x->loaiMB;
	gotoxy(50, wherey());
	cout << x->soDong * x->soDay;
	gotoxy(68, wherey());
	cout << x->soLanbay << endl;	
}

void xuatDSMBay(ListMB &l)
{
	Output();
	cout << "\n\t~ DANH SACH MAY BAY ~" << endl;
	cout << "Co " << l.n << " may bay" << endl;

// ve man hinh xuat 
	int VTx, VTy;
	int trang = 1, sotrang;

	if ((l.n % 15) > 0) // tinh so trang
		sotrang = (l.n / 15) + 1; 
	else if ((l.n % 15 == 0))
		sotrang = l.n / 15; 
	Normal();
	veManhinhXuatMBAY(VTx,VTy); // VTx =0   VTy=13

	// in so trang
	gotoxy(VTx + 35, VTy + 15);
	cout << "<" << trang << "/" << sotrang << ">";
	gotoxy(VTx, VTy + 1); // dua con tro ve dau trang

	// load data vao
	if (l.n > 15) 
	{
		char kytu;
		int dem = 15;
		
		// load 15 may bay dau
		// 0 14
		for (int i = 0; i < dem; i++)
		{
			xuatMBay(l.DSMB[i]);
		}
		// luc nay dem = 15
		while (1)
		{	
			if (kbhit() == true)
			{
				kytu = _getch();
				if (kytu == -32)
				{
					kytu = _getch();

				}
				switch (kytu)
				{
				case Left:
					if (dem == 15)
					{

						// clear man hinh va dua con tro ve dau 
						tomaunen(75, 15, VTx + 1, VTy + 1);
						gotoxy(VTx + 1, VTy + 1);

						for (int i = 0; i < dem; i++)
						{
							xuatMBay(l.DSMB[i]);
						}
						// thay doi trang
						if (trang > 1) trang -= 1; // trang >=0
												   // 35 28
						gotoxy(VTx + 35, VTy + 15);
						cout << "<" << trang << "/" << sotrang << ">";
						//cout << "dem = 15";
						break;
					}

					if (dem > 15) // dem = 30/45/60
					{
					
						gotoxy(VTx + 35, VTy + 15);
						cout << "<" << trang << "/" << sotrang << ">";
						cout << "dem > 15 " ;

						// clear man hinh va dua con tro ve dau 
						tomaunen(75, 15, VTx + 1, VTy + 1);
						gotoxy(VTx + 1, VTy + 1);

						for (int i = dem - 15; i < dem; i++)
						{
							xuatMBay(l.DSMB[i]);
						}
						
						dem -= 15;

						// thay doi trang
						if (trang > 1) trang -= 1; // trang >=0
						// 35 28
						gotoxy(VTx + 35, VTy + 15);
						cout << "<" << trang << "/" << sotrang << ">";
						//cout << "dem > 15 " << dem;
						break;
					}

				case Right:
					
					if (dem + 15 > l.n && dem - 15 < l.n )
					{

						//if ((dem + phai) >= l.n) break; // ds k du 1 trang dau hoac da load het				
						// clear man hinh va dua con tro ve dau 
						tomaunen(75, 15, VTx + 1, VTy + 1);
						gotoxy(VTx + 1, VTy + 1);

						// dem = 15/30/45....	
						for (int i = dem; i < dem + 15; i++)  // data k du 1 trang thi break
						{
							if (i < l.n) 
								xuatMBay(l.DSMB[i]);
							else 
								break;
						}
						//khong tang dem

						//thay doi trang
						if (trang < sotrang) trang += 1;
						// 35 28
						gotoxy(VTx + 35, VTy + 15);
						cout << "<" << trang << "/" << sotrang << ">";
						//cout << "dem = " << dem;
						break;
					}
					else
					{
						// clear man hinh va dua con tro ve dau 
						tomaunen(75, 15, VTx + 1, VTy + 1);
						gotoxy(VTx + 1, VTy + 1);
						for (int i = dem; i < dem + 15; i++)
						{
							if (i >= l.n) break; // data k du 1 trang thi break
							xuatMBay(l.DSMB[i]);
						}
						dem += 15; // dem tang len

						//thay doi trang
						if (trang < sotrang) trang += 1;
						// 35 28
						gotoxy(VTx + 35, VTy + 15);
						cout << "<" << trang << "/" << sotrang << ">";
						//cout << "dem = " << dem;
						break;
					}

				case ESC:
					gotoxy(0, 30);
					Normal();
					break;
				}
				// end switch
				if (kytu == ESC) break;
			}
			// end kbhit()			
		}
		// end while		
	}
	else // load het 
	{
		for (int i = 0; i < l.n; i++)
		{
			xuatMBay(l.DSMB[i]);
		}
	}

	gotoxy(0, 30);
	Normal();
	
}

void dichChuoi(ListMB &l, int vitri) // lùi chuỗi về trái 1 đơn vị từ vị trí cho sẵn
{
	for (vitri; vitri < l.n; vitri++)
	{
		l.DSMB[vitri] = l.DSMB[vitri + 1];
	}
}

void xoaMBay(ListMB &l, ListCBnMB &CBnMB)
{
	if (l.n == 0)
	{
		Error("Danh sach rong, khong co phan tu de xoa");
		system("pause");
		return;
	}
	string sohieuMB;
	gotoxy(95, wherey() + 1);
	cout << "So hieu may bay can xoa: ";
	NhapKiTuKSpace(sohieuMB, MAXSOHIEUMAYBAY);


	int Search = binarySearch_CBnMB(CBnMB.MBnCB, CBnMB.index, sohieuMB);
	if (Search == -1)
	{
		gotoxy(95, wherey() + 1);
		CleanNBack("May bay khong ton tai");
	}
		
	else
	{
		
		if (CBnMB.MBnCB[Search].list.phead == NULL) // k co CB nao dang su dung may bay
		{
			//xoa man hinh trai
			xoaManhinhTrai();
			cout << "Co phai may bay nay ?" << endl;

			int tam = TimkiemMB(l, sohieuMB);

			// in header ra
			SetColor(11);
			cout << "\n So hieu      ";
			cout << "\t Loai may bay   ";
			cout << "\t\t So ghe";
			cout << "\t\t So lan bay" << endl;
			xuatMBay(l.DSMB[tam]);

			// lua chon left right
			gotoxy(95, wherey());
			ChiThi("Ban co chac chan xoa ?");
			string luachon;
			select2(luachon, 95 + 5, wherey(), "CO", "KHONG", 10);
			if (luachon == "CO")
			{
				CBnMB.MBnCB[Search].sohieuMB.erase();
				delete CBnMB.MBnCB[Search].list.phead;
				delete CBnMB.MBnCB[Search].list.ptail;
				dichChuoi_CBnMB(CBnMB, Search);
				CBnMB.index--;

				delete l.DSMB[tam];
				dichChuoi(l, tam);
				l.n--;
			}
			else
				return;
		}
		else
		{
			XuongDong();
			CleanNBack("May bay dang duoc su dung");
		}
	}
}
void suaMBay(ListMB &l, ListCBnMB &CBnMB)
{
	string sohieuMB;
	if (l.n == 0)
	{
		Error("Danh sach rong");
		system("pause");
		return;
	}

	gotoxy(95, wherey() + 1);
	cout << "So hieu may bay can sua: ";
	NhapKiTuKSpace(sohieuMB, MAXSOHIEUMAYBAY);
	cout << "\n";

	int Search = binarySearch_CBnMB(CBnMB.MBnCB, CBnMB.index, sohieuMB);
	int temp = TimkiemMB(l, sohieuMB);
	if (temp == -1)
	{
		Error("Khong tim thay may bay");
		Sleep(1000);
	}
	else
	{
		if (CBnMB.MBnCB[Search].list.phead == NULL) // k co CB nao dang dung MB
		{
			//xoa man hinh trai
			xoaManhinhTrai();

			cout << "Thong tin may bay can sua" << endl;
			// in header ra
			SetColor(11);
			cout << "\n So hieu      ";
			cout << "\t Loai may bay   ";
			cout << "\t\t So ghe";
			cout << "\t\t So lan bay" << endl;

			xuatMBay(l.DSMB[temp]); // xuat thong tin may bay
			gotoxy(95, wherey());
			ChiThi("Ban co chac muon sua doi thong tin ?");
			string luachon;
			select2(luachon, 95 + 5, wherey(), "CO", "KHONG", 10);
			if (luachon == "CO")
			{
				xoaManhinhPhai();
				nhapMBay_KhongSoHieu(l.DSMB[temp]);
			}
			else
			{

				return;
			}
		}
		else
		{
			XuongDong();
			CleanNBack("May bay dang duoc su dung");
		}
	}
}

int MenuMBAY(ListMB &l, ListCBnMB &CBnMB)
{
	ShowConsoleCursor(false);
	while (true) {
		system("cls");

		int luachon;
		//luachon = MenuDong(menuMBAY, ITEMMENUMBAY, tenMenu);
		//khungMainScreen();
		khungThemMB();
		gotoxy(0, 1 + ITEMMENUMBAY);
		Normal();
		xuatDSMBay(l);
		gotoxy(0, 5);
		phimGuide();
		
		BatPhimChucNang(luachon);

		if (luachon == 1)
		{
			gotoxy(0, 1 + ITEMMENUMBAY);
			Normal();
			gotoxy(100, wherey() + 1);
			nhapDSMBay(l, CBnMB);
		}
		if (luachon == 2)
		{
			gotoxy(0, 1 + ITEMMENUMBAY);
			Normal();
			xuatDSMBay(l);
		}
		if (luachon == 3)
		{
			gotoxy(0, 1 + ITEMMENUMBAY);
			Normal();
			xoaMBay(l,CBnMB);
		}
		if (luachon == 4)
		{
			gotoxy(0, 1 + ITEMMENUMBAY);
			Normal();
			suaMBay(l, CBnMB);
		}
		if (luachon == ITEMMENUMBAY)
		{
			Normal();
			
			cout << "\n";
			return 0;
		}
	}
}
