#include "ThuVien.h"

void NhapSo(string &a, int dodai) // ham nhap chi so tu 0->9, enter khi du do dai
{
	a.clear();
	char c;
	bool kt = true;
	int dem = dodai;
	while (true)
	{
		c = _getch();
		if (int(c) == 8) // nếu ấn phím Backspace thì xóa 1 kí tự ở cuối
		{
			if (a.empty() != true) //Chuoi rong thi khong xoa tiep duoc
			{
				cout << "\b \b";
				a.erase(a.begin() + (a.length() - 1));
				dem++;
				kt = true;
			}
		}
		else if ((int)c == 13)
		{
			//nếu nhấn kí tự enter thì luu
			if (kt == true)// kiểm tra xem x có rỗng ko
			{
				continue;
			}
			else
			{
				break;
			}
		}
		else if (c >= 48 && c <= 57)
		{
			if (dem != 0) // chuoi du 9 ki tu khong nhap duoc nua
			{
				dem--;
				cout << c;
				a.push_back(c);
				kt = true;
				if (dem == 0)
				{
					kt = false;
				}
			}
		}
	}
}

void NhapDongDay(string &a, int dodai) // ham nhap chi so tu 0->9, enter khi du do dai
{
	a.clear();
	char c;
	bool kt = true;
	int dem = dodai;
	while (true)
	{
		c = _getch();
		if (int(c) == 8) // nếu ấn phím Backspace thì xóa 1 kí tự ở cuối
		{
			if (a.empty() != true) //Chuoi rong thi khong xoa tiep duoc
			{
				cout << "\b \b";
				a.erase(a.begin() + (a.length() - 1));
				dem++;
				kt = true;
			}
		}
		else if ((int)c == 13)
		{
			//nếu nhấn kí tự enter thì luu
			if (kt == true)// kiểm tra xem x có rỗng ko
			{
				continue;
			}
			else
			{
				break;
			}
		}
		else if (c >= 53 && c <= 57)
		{
			if (dem != 0) // chuoi du 9 ki tu khong nhap duoc nua
			{
				dem--;
				cout << c;
				a.push_back(c);
				kt = true;
				if (dem == 0)
				{
					kt = false;
				}
			}
		}
	}
}

void NhapKiTuKSpace(string &a, int dodai) // ham nhap chi so tu 0->9 & a->z & A->Z
{
	a.clear();
	int dem = dodai;
	char c;
	bool kt = true;
	while (true)
	{
		c = _getch();
		if (int(c) == 8) // nếu ấn phím Backspace thì xóa 1 kí tự ở cuối
		{
			if (a.empty() != true) //Chuoi rong thi khong xoa tiep duoc
			{
				cout << "\b \b";
				a.erase(a.begin() + (a.length() - 1));
				dem++;
			}
		}
		else if ((int)c == 13)
		{
			//nếu nhấn kí tự enter thì luu
			if (kt == true)// kiểm tra xem x có rỗng ko
			{
				continue;
			}
			else
			{
				break;
			}
		}
		else if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		{
			if (dem != 0) // chuoi du 9 ki tu khong nhap duoc nua
			{
				dem--;
				cout << c;
				a.push_back(c);
				kt = false;
			}
		}
	}
}
//hàm chuẩn hóa số
void chuyenso(string a, int &x)
{
	x = 0;
	int n = a.length();
	for (int i = 0; i < a.length(); i++)
	{
		x += (a[i] - 48)*pow(10, n - 1);
		n--;
	}
}
// hết hàm chuẩn hóa.

void NhapChu(string &a, int dodai) // ham nhap chu a->z, A->Z, " " 
{
	a.clear();
	char c;
	bool kt = true;
	int dem = dodai;
	while (true)
	{
		c = _getch();
		if (int(c) == 8) // nếu ấn phím Backspace thì xóa 1 kí tự ở cuối
		{
			if (a.empty() != true) //Chuoi rong thi khong xoa tiep duoc
			{
				cout << "\b \b";
				a.erase(a.begin() + (a.length() - 1));
				dem++;
			}
		}
		else if ((int)c == 13)
		{
			//nếu nhấn kí tự enter thì luu
			if (kt == true)// kiểm tra xem x có rỗng ko
			{
				continue;
			}
			else
			{
				break;
			}
		}
		else if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 32)
		{
			if (dem != 0) // chuoi du 9 ki tu khong nhap duoc nua
			{
				dem--;
				cout << c;
				a.push_back(c);
				kt = false;
			}
		}
	}
}
//hàm chuẩn hóa
void xoakhoangtrang(string &x) // Xoa khoang trang
{
	for (int i = 0; i < x.length(); i++)
	{
		if (x[i] == ' ')
		{
			x.erase(x.begin() + i);
			i--;
		}
		else
		{
			break;
		}
	}

	for (int i = x.length() - 1; i > 0; i--)
	{
		if (x[i] == ' ')
		{
			x.erase(x.begin() + i);
		}
		else
		{
			break;
		}
	}

	for (int i = 0; i < x.length(); i++)
	{
		if (x[i] == ' '&& x[i + 1] == ' ')
		{
			x.erase(x.begin() + i);
			i--;
		}
	}
}
void suakitu(string &x) //lam dep chuoi
{
	//chuyển sang chữ thường
	for (int i = 0; i < x.length(); i++)
	{
		if (x[i] >= 65 && x[i] <= 90)
		{
			x[i] = x[i] + 32;
		}
	}
	//chuyển sang chữ in hoa truoc dau cach
	for (int i = 1; i <= x.length(); i++)
	{
		if (x[i] == ' ')
		{
			x[i + 1] = x[i + 1] - 32;
		}
	}
	//chỉnh chữ hoa đầu câu
	if (x[0] != ' ' && x[0] >= 97 && x[0] <= 122)
	{
		x[0] = x[0] - 32;
	}
}     

void UpperCase(string &x)
{
	for (int i = 0; i < x.length(); i++)
	{
		if (x[i] >= 97 && x[i] <= 122)
		{
			x[i] = x[i] - 32;
		}
	}
}

tm* GetDate()
{
	time_t now = time(NULL);
	tm *ltm = localtime(&now);
	return ltm;
}

// so sanh voi thoi gian hien tai cua he thong, neu lon hon thi true, khong thi false
bool SoSanhTimeNow(int ngay, int thang, int nam, int gio, int phut)
{
	time_t now = time(NULL);
	/*char* dt = ctime(&now);
	string time = dt;
	return time;*/
	int ngayNow, thangNow, namNow;
	int gioNow, phutNow;
	tm *ltm = localtime(&now);

	gioNow = ltm->tm_hour;
	phutNow = ltm->tm_min;

	ngayNow = ltm->tm_mday;
	thangNow = 1 + ltm->tm_mon;
	namNow = 1900 + ltm->tm_year;


	if (nam > namNow) return true;
	else if (nam == namNow)
	{
		if (thang > thangNow)
		{
			return true;
		}
		else if (thang == thangNow)
		{
			if (ngay > ngayNow)
			{
				return true;
			}
			else if (ngay == ngayNow)
			{
				if (gio > gioNow)
				{
					return true;
				}
				else if (gio == gioNow)
				{
					if (phut > phutNow)
					{
						return true;
					}
					else return false;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else return false;
		
}

char NumberToLetter(int n)
{
	char a;
	if (n == 1) a = 'A';
	if (n == 2) a =	'B';
	if (n == 3) a = 'C';
	if (n == 4) a = 'D';
	if (n == 5) a = 'E';
	if (n == 6) a = 'F';
	if (n == 7) a = 'G';
	if (n == 8) a = 'H';
	if (n == 9) a = 'I';
	return a;
}

string chuyenTrangThai(int trangthai)
{
	if (trangthai == 1) return "Con ve";
	else if (trangthai == 0) return "Huy chuyen";
	else if (trangthai == 2) return "Het ve";
	else if (trangthai == 3) return "Hoan tat";
}

void ghiFile(string tenFile, string data)
{
	ofstream fout;
	fout.open(tenFile, ios::app | ios::app);
	//cout << "ghi file"<<endl;
	fout << data << endl;
	fout.close();
}

void docFile(string tenFile, string data)
{
	ifstream fin;
	fin.open(tenFile, ios::in);
	cout << "doc file"<<endl;
	int dem=0;
	do
	{
		string n;
		fin >> data;
		getline(fin, n);
		cout << data << " " << dem<<endl;
		fin.ignore();
		dem++;
	} while (!fin.eof());

	//cout << data;
	fin.close();
}

bool KiemTraThang(int x)
{
	if (x == 4 || x == 6 || x == 9 || x == 11)
	{
		return true;
	}
	return false;
}

void NhapDate(int &nam, int &thang, int &ngay, int &gio, int &phut)
{
	string a;
	a.clear();
	char c;
	bool kt = true;
	int dem = MaxYear;

	// to dam tra ve cho cu de nhap
	InputDate();
	int vitriNam = wherex();
	cout << "Yyyy";
	LuiVe(4);

	while (true) // nhap nam
	{
		c = _getch();
		if (int(c) == 8) // nếu ấn phím Backspace thì xóa 1 kí tự ở cuối
		{
			if (a.empty() != true) //Chuoi rong thi khong xoa tiep duoc
			{
				cout << "\b \b";
				a.erase(a.begin() + (a.length() - 1));
				dem++;
				kt = true;
			}
		}
		else if ((int)c == 13)
		{
			//nếu nhấn kí tự enter thì luu
			if (kt == true)// kiểm tra xem x có rỗng ko
			{
				continue;
			}
			else
			{
				tm *ltm = GetDate();
				chuyenso(a, nam);
				if ((1900 + ltm->tm_year) <= nam)
				{
					break;
				}
				else
				{
					gotoxy(96, wherey() + 1);
					CleanNBack("Nam khong hop le");
					Input();
					cout << "                ";
					gotoxy(vitriNam, wherey() -1); 
					InputDate();
					cout << "    "; LuiVe(4);
					nam = 0;
					a.clear();
					dem = MaxYear;
				}
			}
		}
		else if (c >= 48 && c <= 57)
		{
			if (dem != 0)
			{
				dem--;
				cout << c;
				a.push_back(c);
				if (dem == 0)
				{
					kt = false;
				}
			}
		}
	}

	//tra ve mau cu va in ra
	InputHighLight();
	LuiVe(4);
	cout << nam;

	cout << "/";
	a.clear();
	kt = true;
	dem = MaxDate;

	// to dam tra ve cho cu de nhap
	InputDate();
	int vitriThang = wherex();
	cout << "Mm";
	LuiVe(2);

	while (true) //nhap thang
	{
		c = _getch();
		if (int(c) == 8) // nếu ấn phím Backspace thì xóa 1 kí tự ở cuối
		{
			if (a.empty() != true) //Chuoi rong thi khong xoa tiep duoc
			{
				cout << "\b \b";
				a.erase(a.begin() + (a.length() - 1));
				dem++;
				kt = true;
			}
		}
		else if ((int)c == 13)
		{
			//nếu nhấn kí tự enter thì luu
			if (kt == true)// kiểm tra xem x có rỗng ko
			{
				continue;
			}
			else
			{
				tm *ltm = GetDate();
				chuyenso(a, thang);
				if (((1 + ltm->tm_mon) <= thang && nam == (1900 + ltm->tm_year)) || nam > (1900 + ltm->tm_year))
				{
					break;
				}
				else
				{
					gotoxy(96, wherey() + 1);
					CleanNBack("Thang khong hop le");
					Input();
					cout << "                  ";
					gotoxy(vitriThang, wherey() - 1);
					InputDate();
					cout << "  "; LuiVe(2);
					thang = 0;
					a.clear();
					dem = MaxDate;
				}
			}
		}
		else if (c >= 50 && c <= 57 && dem == 2)
		{
			if (dem != 0)
			{
				cout << "0";
				cout << c;
				a.push_back('0');
				a.push_back(c);
				kt = false;
				dem = 0;
			}
		}
		else if (c >= 48 && c <= 49)
		{
			if (dem != 0) // chuoi du 9 ki tu khong nhap duoc nua
			{
				dem--;
				cout << c;
				a.push_back(c);
				if (dem == 0)
				{
					kt = false;
				}
			}
		}
		else if (c >= 50 && c <= 57 && a[0] == '0')
		{
			if (dem != 0)
			{
				dem--;
				cout << c;
				a.push_back(c);
				if (dem == 0)
				{
					kt = false;
				}
			}
		}
		else if (c >= 48 && c <= 50 && a[0] == '1')
		{
			if (dem != 0)
			{
				dem--;
				cout << c;
				a.push_back(c);
				if (dem == 0)
				{
					kt = false;
				}
			}
		}
	}
	chuyenso(a, thang);

	//tra ve mau cu va in ra
	InputHighLight();
	LuiVe(2);
	if (thang < 10) cout << "0" << thang;
	else cout << thang;

	cout << "/";
	a.clear();
	kt = true;
	bool KT_thang = KiemTraThang(thang);
	dem = MaxDate;

	// to dam tra ve cho cu de nhap
	InputDate();
	int vitriNgay = wherex();
	cout << "Dd";
	LuiVe(2);

	while (true) //nhap ngay
	{
		c = _getch();
		if (int(c) == 8) // nếu ấn phím Backspace thì xóa 1 kí tự ở cuối
		{
			if (a.empty() != true) //Chuoi rong thi khong xoa tiep duoc
			{
				cout << "\b \b";
				a.erase(a.begin() + (a.length() - 1));
				dem++;
				kt = true;
			}
		}
		else if ((int)c == 13)
		{
			//nếu nhấn kí tự enter thì luu
			if (kt == true)// kiểm tra xem x có rỗng ko
			{
				continue;
			}
			else
			{
				tm *ltm = GetDate();
				chuyenso(a, ngay);
				if ( nam > (ltm->tm_year + 1900)
					|| thang > (ltm->tm_mon + 1)
					|| (thang == (ltm->tm_mon + 1) && ltm->tm_mday <= ngay) )
				{
					break;
				}
				else
				{
					gotoxy(96, wherey() + 1);
					CleanNBack("Ngay khong hop le");
					Input();
					cout << "                 ";
					gotoxy(vitriNgay, wherey() - 1);
					InputDate();
					cout << "  "; LuiVe(2);
					ngay = 0;
					a.clear();
					dem = MaxDate;
				}
			}
		}
		else if (c >= 52 && c <= 57 && dem == 2) // 4 -> 9
		{
			if (dem != 0)
			{
				cout << "0";
				cout << c;
				a.push_back('0');
				a.push_back(c);
				kt = false;
				dem = 0;
			}
		}
		else if (c >= 48 && c <= 51 && a.empty() == true && thang != 2) // 0.1.2.3
		{
			if (dem != 0)
			{
				dem--;
				cout << c;
				a.push_back(c);
				if (dem == 0)
				{
					kt = false;
				}
			}
		}
		else if (c >= 48 && c <= 50 && a.empty() == true && thang == 2) // 0.1.2
		{
			if (dem != 0)
			{
				dem--;
				cout << c;
				a.push_back(c);
				if (dem == 0)
				{
					kt = false;
				}
			}
		}
		else if (c >= 49 && c <= 57 && a[0] == 48) //0x
		{
			if (dem != 0)
			{
				dem--;
				cout << c;
				a.push_back(c);
				if (dem == 0)
				{
					kt = false;
				}
			}
		}
		else if (c >= 48 && c <= 57 && (a[0] == 49 || (a[0] == 50 && nam % 4 == 0))) // 1x , 2x nam nhuan
		{
			if (dem != 0)
			{
				dem--;
				cout << c;
				a.push_back(c);
				if (dem == 0)
				{
					kt = false;
				}
			}
		}
		else if (c >= 48 && c <= 56 && a[0] == 50 && nam % 4 != 0) //2x
		{
			if (dem != 0)
			{
				dem--;
				cout << c;
				a.push_back(c);
				if (dem == 0)
				{
					kt = false;
				}
			}
		}
		else if (c == 48 && a[0] == 51 && KT_thang == true) // 30
		{
			if (dem != 0)
			{
				dem--;
				cout << c;
				a.push_back(c);
				if (dem == 0)
				{
					kt = false;
				}
			}
		}
		else if (c >= 48 && c <= 49 && a[0] == 51 && KT_thang == false) // 31
		{
			if (dem != 0)
			{
				dem--;
				cout << c;
				a.push_back(c);
				if (dem == 0)
				{
					kt = false;
				}
			}
		}
	}
	chuyenso(a, ngay);

	//tra ve mau cu va in ra
	InputHighLight();
	LuiVe(2);
	if (ngay < 10) cout << "0" << ngay;
	else cout << ngay;

// =============================== NhapGio =============================

	a.clear();
	kt = true;
	dem = 2;


	gotoxy(wherex() + 2, wherey());

	// to dam tra ve cho cu de nhap
	InputDate();
	int vitriGio = wherex();
	cout << "Hh";
	LuiVe(2);

	while (true)
	{
		c = _getch();
		if (int(c) == 8) // nếu ấn phím Backspace thì xóa 1 kí tự ở cuối
		{
			if (a.empty() != true) //Chuoi rong thi khong xoa tiep duoc
			{
				cout << "\b \b";
				a.erase(a.begin() + (a.length() - 1));
				dem++;
				kt = true;
			}
		}
		else if ((int)c == 13)
		{
			//nếu nhấn kí tự enter thì luu
			if (kt == true)// kiểm tra xem x có rỗng ko
			{
				continue;
			}
			else
			{
				tm *ltm = GetDate();
				chuyenso(a, gio);
				if ( nam > ltm->tm_year + 1900
					|| thang > ltm->tm_mon + 1
					|| ngay > ltm->tm_mday
					|| (ngay == ltm->tm_mday && gio >= ltm->tm_hour) )
				{
					break;
					
				}
				else
				{
					gotoxy(96, wherey() + 1);
					CleanNBack("Gio khong hop le");
					Input();
					cout << "                ";
					gotoxy(vitriGio, wherey() - 1);
					InputDate();
					cout << "  "; LuiVe(2);
					gio = 0;
					a.clear();
					dem = MaxDate;
				}
			}
		}
		else if (c >= 51 && c <= 57 && dem == 2)
		{
			if (dem != 0)
			{
				cout << "0";
				cout << c;
				a.push_back('0');
				a.push_back(c);
				kt = false;
				dem = 0;
			}
		}
		else if (c >= 48 && c <= 50)
		{
			if (dem != 0) // chuoi du 9 ki tu khong nhap duoc nua
			{
				dem--;
				cout << c;
				a.push_back(c);
				if (dem == 0)
				{
					kt = false;
				}
			}
		}
		else if (c >= 51 && c <= 57 && (a[0] == '0' || a[0] == '1'))
		{
			if (dem != 0)
			{
				dem--;
				cout << c;
				a.push_back(c);
				if (dem == 0)
				{
					kt = false;
				}
			}
		}
		else if (c >= 48 && c <= 51 && a[0] == '2')
		{
			if (dem != 0)
			{
				dem--;
				cout << c;
				a.push_back(c);
				if (dem == 0)
				{
					kt = false;
				}
			}
		}
	}

	// tra ve mau cu va in ra
	InputHighLight();
	LuiVe(2);
	cout << a;

	//cout << "\nNhap gio: "; 
	
	//NhapGio(date); 
	gotoxy(wherex() + 1, wherey());
	cout << "   ";
	chuyenso(a, gio);

// ================================  NhapPhut =======================
	a.clear();
	kt = true;
	dem = 2;

	gotoxy(wherex() - 3, wherey());
	// to dam tra ve cho cu de nhap
	InputDate();
	int vitriphut = wherex();
	cout << "Mm";
	LuiVe(2);

	while (true)
	{
		c = _getch();
		if (int(c) == 8) // nếu ấn phím Backspace thì xóa 1 kí tự ở cuối
		{
			if (a.empty() != true) //Chuoi rong thi khong xoa tiep duoc
			{
				cout << "\b \b";
				a.erase(a.begin() + (a.length() - 1));
				dem++;
				kt = true;
			}
		}
		else if ((int)c == 13)
		{
			//nếu nhấn kí tự enter thì luu
			if (kt == true)// kiểm tra xem x có rỗng ko
			{
				continue;
			}
			else
			{
				tm *ltm = GetDate();
				chuyenso(a, phut);
				if (nam > ltm->tm_year + 1900
					|| thang > ltm->tm_mon + 1
					|| ngay > ltm->tm_mday
					|| gio > ltm->tm_hour
					|| (gio == ltm->tm_hour && phut >= ltm->tm_min) )
				{
					break;
				}
				else
				{
					gotoxy(96, wherey() + 1);
					CleanNBack("phut khong hop le");
					Input();
					cout << "                 ";
					gotoxy(vitriphut, wherey() - 1);
					InputDate();
					cout << "  "; LuiVe(2);

					phut = 0;
					a.clear();
					dem = MaxDate;
				}
			}
		}
		else if (c >= 54 && c <= 57 && dem == 2)
		{
			if (dem != 0)
			{
				cout << "0";
				cout << c;
				a.push_back('0');
				a.push_back(c);
				kt = false;
				dem = 0;
			}
		}
		else if (c >= 48 && c <= 53)
		{
			if (dem != 0) // chuoi du 9 ki tu khong nhap duoc nua
			{
				dem--;
				cout << c;
				a.push_back(c);
				if (dem == 0)
				{
					kt = false;
				}
			}
		}
		else if (c >= 54 && c <= 57 && (a[0] >= 48 & a[0] <= 53))
		{
			if (dem != 0)
			{
				dem--;
				cout << c;
				a.push_back(c);
				if (dem == 0)
				{
					kt = false;
				}
			}
		}
	}

	// tra ve mau cu va in ra
	InputHighLight();
	LuiVe(2);
	cout << a;
	chuyenso(a, phut);
	gotoxy(wherex() + 3, wherey());
}




	



void removeSpace(string &x)
{
	for (int i = 0; i < x.length(); i++)
	{
		if (x[i] == ' ')
		{
			x.erase(x.begin() + i);
			i--;
		}
	}
}
void addSpace(string &x)
{
	string temp;
	for (int i = 0; i < x.length(); i++)
	{
		if (i == 0)
		{
			temp += x[i];
			continue;
		}
		else if (x[i] >= 65 && x[i] <= 90)
		{
			temp += " ";
			temp += x[i];
		}
		else temp += x[i];
		cout << temp<<endl ;
	}
	x = temp;
}

void BatPhimChucNang(int &luachon)
{
	char kytu;
	bool press = false;
	while (true)
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
			case Ins:
				press = true;
				luachon = 1;
				break;
			case F1:
				press = true;
				luachon = 2;
				break;
			case Del:
				press = true;
				luachon = 3;
				break;
			case Home:
				press = true;
				luachon = 4;
				break;
			case ESC:
				press = true;
				luachon = 5;
				break;				
			case F3:
				press + true;
				luachon = 6;
				break;
			case F2:
				press = true;
				luachon = 7;
				break;
			case End:
				press = true;
				luachon = 8;
				break;
			} // end switch
		} // end if
		if (press == true) break;
	} // end while
}

void deletaDataFile(string name)
{
	// xoa du lieu cu trong file
	ofstream fileout;
	fileout.open(name, ios::trunc);
	fileout.close();
}

void NhapChoNgoi(string &a, int MaxCN) // ham nhap chi so tu 0->9, enter khi du do dai
{
	a.clear();
	char c;
	bool kt = true;
	int dem = MaxChoNgoi;
	while (true)
	{
		c = _getch();
		if (int(c) == 8) // nếu ấn phím Backspace thì xóa 1 kí tự ở cuối
		{
			if (a.empty() != true) //Chuoi rong thi khong xoa tiep duoc
			{
				cout << "\b \b";
				a.erase(a.begin() + (a.length() - 1));
				dem++;
				kt = true;
			}
		}
		else if ((int)c == 13)
		{
			//nếu nhấn kí tự enter thì luu
			if (kt == true)// kiểm tra xem x có rỗng ko
			{
				continue;
			}
			else
			{
				break;
			}
		}
		else if (c >= 97 && c <= 105 && dem == 2)
		{
			if (dem != 0) // chuoi du 9 ki tu khong nhap duoc nua
			{
				dem--;
				cout << c;
				a.push_back(c);
				kt = true;
				if (dem == 0)
				{
					kt = false;
				}
			}
		}
		else if (c >= 48 && c <= 57 && dem == 1)
		{
			if (dem != 0) // chuoi du 9 ki tu khong nhap duoc nua
			{
				dem--;
				cout << c;
				a.push_back(c);
				kt = true;
				if (dem == 0)
				{
					kt = false;
				}
			}
		}
	}
}

int SoSanhKiTu(string a, string b)
{
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] > b[i])
		{
			return 1;
		}
		else if (a[i] < b[i])
		{
			return -1;
		}

	}
	return 0;
}