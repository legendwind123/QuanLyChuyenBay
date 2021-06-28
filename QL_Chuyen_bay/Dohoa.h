#include<iostream>
#include<string>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include"mylib.h"
#include"ThuVien.h"
using namespace std;

#define ITEMMENUTONG 9
#define ITEMMENUHKHACH 7
#define ITEMMENUMBAY 5
#define ITEMMENUCBAY 5

const int dong = 3; // dong bat dau in ra menu
const int cot = 0; // cot bat dau in ra menu
const int Up = 72;
const int Down = 80;
const int Right = 77;
const int Left = 75;
const int Del = 83;
const int Ins = 82;
const int Home = 71;
const int End = 79;
const int ESC = 27;
const int F1 = 59;
const int F2 = 60;
const int F3 = 61;

string menuTONG[ITEMMENUTONG] = { 
"\n Cap nhat danh sach cac may bay",
"\n Cap nhat danh sach hanh khach",
"\n Cap nhat danh sach chuyen bay",
"\n Quan Ly ve",
"\n Xem danh sach khach hang tren chuyen bay",
"\n Xem danh sach cac chuyen bay khoi hanh",
"\n Danh sach ve trong tren 1 chuyen bay",
"\n Thong ke so lan bay cua mot chuyen bay",
"\n Thoat" };

// danh sach menu may bay
string menuMBAY[ITEMMENUMBAY] = {
"\n1 . Them may bay",
"\n2 . Hien thi danh sach may bay",
"\n3 . Xoa may bay",
"\n4 . Sua may bay",
"\n5 . Tro ve" };


// danh sach menu hanh khach
string menuHKHACH[ITEMMENUHKHACH] = {
"\n1 . Nhap phan tu cho cay nhi phan tim kiem",
"\n2 . Xuat cay NLR",
"\n3 . Tim kiem phan tu",
"\n4 . Sua thong tin",
"\n5 . Xoa thong tin",
"\n6 . Giai phong cay",
"\n7 . Tro ve" };

// danh sach menu chuyen bay
string menuCBAY[ITEMMENUCBAY] = {
"\n1 . Them chuyen bay",
"\n2 . Hien thi danh sach chuyen bay",
"\n3 . Huy chuyen bay",
"\n4 . Sua chuyen bay",
"\n5 . Tro ve" };

void Normal() // mau chu binh thuong
{
	SetColor(15);
	SetBGColor(0);
}

void VeMua()
{
	SetColor(12);
	SetBGColor(0);
}

void VeTrong() 
{
	SetColor(9);
	SetBGColor(0);
}

void Input() // chu xanh, nen bac
{
	SetColor(9);
	SetBGColor(7);
}

void InputHighLight() // chu den, nen bac
{
	SetColor(16);
	SetBGColor(7);
}

void InputDate() // chu trang, nen xanh
{
	SetColor(15);
	SetBGColor(1);
}

void Output()
{
	SetColor(14);
	SetBGColor(9);
}
void DataTable()
{
	SetColor(31);
	SetBGColor(0);
}

void HighLight() // chu vang, nen xanh la
{
	SetColor(62);
	SetBGColor(2);
}
void ChiThi(string a) // chu trang, nen xanh duong
{
	SetColor(31);
	SetBGColor(1);
	cout  << a << endl;
	Normal();
}

void Error(string a) // chu trang, nen xanh
{
	SetColor(46);
	SetBGColor(4);
	cout << a << endl;
	Normal();
}

void Clean(int dodai)
{
	SetBGColor(7);
	Normal();
	for (int i = 0; i < dodai; i++)
	{
		cout << " ";
	}
	gotoxy(wherex() - dodai, wherey());
}

void Clean(string a, int BGcolor)
{
	int dodai = a.length();
	SetBGColor(BGcolor);
	for (int i = 0; i < dodai; i++)
	{
		cout << " ";
	}
	gotoxy(wherex() - dodai, wherey());
}

void CleanRow(string a)
{
	int dodai = a.length();
	int vitriX = wherex() - dodai;
	if (vitriX < 0) vitriX = 0;
	gotoxy(vitriX, wherey()-1);
	Clean(dodai);
}

void CleanNBack(string a)
{
	int tempX = wherex(), tempY = wherey();
	Error(a);
	Sleep(1000);
	gotoxy(tempX, tempY);
	Clean(a, 0);
}

void LuiVe(int i)
{
	gotoxy(wherex() - i, wherey());
}

void XuongDong()
{
	gotoxy(95, wherey() + 1);
}

// x = rong  y= cao   Ox,Oy = vi tri bat dau
void kekhung(int X, int Y, int Ox, int Oy)
{
	for (int k = 0; k<Y; k++)
	{
		if (k == 0)
		{
			gotoxy(Ox, Oy);
			for (int i = 0; i<X; i++)
				printf("%c", 219);
			printf("\n");
		}
		if (k == Y - 1)
		{
			gotoxy(Ox, wherey());
			for (int i = 0; i<X; i++)
				printf("%c", 219);
			printf("\n");
		}
		else {
			gotoxy(Ox, wherey());
			printf("%c", 219);
			gotoxy(Ox + X - 1, wherey());
			printf("%c", 219);
			printf("\n");
		}
	}
}

void tomaunen(int rong, int cao, int vitriX, int vitriY)
{
	gotoxy(vitriX, vitriY);
	for (int i = 0; i < cao; i++)
	{
		gotoxy(vitriX, vitriY);
		for (int k = 0; k < rong; k++)
		{
			cout << " ";
		}
		vitriY += 1;
	}
}

void khungNhapMBAY(int vitriX, int vitriY)
{
	Input();
	int rong = 52;
	kekhung(rong, 9, vitriX, vitriY);
	gotoxy(vitriX + 1, vitriY);
	
	for (int i = 1; i < 9; i++)
	{
		gotoxy(vitriX + 1, vitriY + i);
		for (int k = 1; k < rong -1; k++) // ngang 60
		{
			cout << " ";
		}
		cout << endl;
	}
	
	Input();
	gotoxy(vitriX + 1, vitriY + 1);
	cout << " So hieu may bay: " << endl;
	gotoxy(vitriX + 1, vitriY + 3);
	cout << " Loai may bay: " << endl;
	gotoxy(vitriX + 1, vitriY + 5);
	cout << " So day: " << endl;
	gotoxy(vitriX + 1, vitriY + 7);
	cout << " So dong: " << endl;
	gotoxy(vitriX, vitriY);
}

void khungXuatMBAY(int vitriX, int vitriY)
{
	Output();
	kekhung(77,16,vitriX, vitriY);
	tomaunen(75,15,vitriX + 1, vitriY+1);
	//// phan trang
	//gotoxy(vitriX + 35, vitriY + 15);

	gotoxy(vitriX, vitriY + 1); // dua con tro ve dau trang
}

void dongXuatMBAY(int vitriX, int vitriY)
{
	SetColor(31);
}

void veManhinhXuatMBAY(int &VTx, int &VTy)
{
	// ve man hinh xuat 
	SetColor(11);
	cout << "\n So hieu      ";
	cout << "\t Loai may bay   ";
	cout << "\t\t So ghe";
	cout << "\t\t So lan bay" << endl;
	VTx = wherex();
	VTy = wherey();
	khungXuatMBAY(VTx, VTy);
}

void veManhinhXuatHK(int VTx, int VTy)
{
	gotoxy(VTx, VTy);
	Normal();
	// ve man hinh xuat 
	SetColor(11);
	cout << "\n Cmnd      ";
	cout << "\t Ho   ";
	cout << "\t\t\t\t Ten";
	cout << "\t\t Phai" << endl;
}

void khungNhapHK(int vitriX, int vitriY)
{
	int cao = 7, rong = 53;

	Input();
	kekhung(rong, cao, vitriX, vitriY);
	gotoxy(vitriX + 1, vitriY);

	for (int i = 1; i < cao; i++)
	{
		gotoxy(vitriX + 1, vitriY + i);
		for (int k = 1; k < rong - 1; k++) // ngang 60
		{
			cout << " ";
		}
		cout << endl;
	}

	Input();
	gotoxy(vitriX + 1, vitriY + 1);
	cout << " So CMND: " << endl;
	gotoxy(vitriX + 1, vitriY + 3);
	cout << " Ho va Ten: " << endl;
	gotoxy(vitriX + 1, vitriY + 5);
	cout << " Gioi tinh: " << endl;
	gotoxy(vitriX, vitriY);
}

void khungNhapCB(int vitriX, int vitriY)
{
	int cao = 9, rong = 52;
	Input();
	kekhung(rong, cao, vitriX, vitriY);
	gotoxy(vitriX + 1, vitriY);

	for (int i = 1; i < cao; i++)
	{
		gotoxy(vitriX + 1, vitriY + i);
		for (int k = 1; k < rong - 1; k++)
		{
			cout << " ";
		}
		cout << endl;
	}

	Input();
	gotoxy(vitriX + 1, vitriY + 1);
	cout << " Ma chuyen bay: " << endl;
	gotoxy(vitriX + 1, vitriY + 3);
	cout << " Thoi gian bay: " << endl;
	gotoxy(vitriX + 1, vitriY + 5);
	cout << " San bay den: " << endl;
	gotoxy(vitriX + 1, vitriY + 7);
	cout << " So hieu may bay: " << endl;

	gotoxy(vitriX, vitriY);
}


void kiemtraKBHIT()
{
	int kytu;
	while (true)
	{
		if (kbhit() == true)
		{
			kytu = _getch();
			cout << kytu<< endl;
			if (kytu == -32)
			{
				kytu = _getch();
				int temp = kytu;
				cout << temp<<endl;
			}
		}
	}
}

void timeGadget(int vitrix, int vitriy) // in ra ngay/thang/nam
{
	time_t now = time(0);
	//cout << "Number of sec since January 1,1970:" << now << endl;
	tm *ltm = localtime(&now);
	// print various components of tm structure.
	gotoxy(vitrix, vitriy);
	cout << " .===============. ";
	gotoxy(vitrix, vitriy + 1);
	cout << "|  " << ltm->tm_mday << " - " << 1 + ltm->tm_mon << " - " << 1900 + ltm->tm_year 
		<< "  |" << ltm->tm_hour << "/"<<ltm->tm_min;
	gotoxy(vitrix, vitriy + 2);
	cout << " '===============' ";
	gotoxy(vitrix, vitriy + 3);
	gotoxy(0, 0);
}

int MenuDong(string td[], int SL, string ten) {
	Normal();
	system("cls");
	int chon = 0;
	int i;

	timeGadget(38,1);

	cout << "\t\t================== " << ten << " ==================" << endl;

	for (i = 0; i< SL; i++)
	{
		gotoxy(cot, dong + i);
		cout << td[i];
	}
	HighLight();
	gotoxy(cot, dong + chon);
	cout << td[chon];
	char kytu;
	do {
		kytu = _getch();
		if (kytu == -32) kytu = _getch();
		switch (kytu) {
		case Up:if (chon >0)
		{
			Normal();
			gotoxy(cot, dong + chon); cout << td[chon];
			chon--;
			HighLight();
			gotoxy(cot, dong + chon); 	cout << td[chon];
		}
				break;
		case Down:if (chon + 1 <SL)
		{
			Normal();
			gotoxy(cot, dong + chon);	cout << td[chon];
			chon++;
			HighLight();
			gotoxy(cot, dong + chon); 	cout << td[chon];

		}
				  break;
		case 13: return chon + 1;
		}  // end switch
	} while (1);
}

int Menu(char td[ITEMMENUHKHACH][50]) {

	system("cls");
	int chon = 0;
	int i;
	for (i = 0; i< ITEMMENUHKHACH; i++)
	{
		gotoxy(cot, dong + i);
		cout << td[i];
	}
Nhaplai:
	gotoxy(cot, dong + ITEMMENUHKHACH);
	cout << "Ban chon 1 so (1..10) :    ";
	gotoxy(wherex() - 4, wherey());
	cin >> chon;
	if (chon <1 || chon >ITEMMENUHKHACH) goto Nhaplai;
	return chon;

}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void inLogo()
{
	cout << " \n.----------------.  .----------------.  .----------------.  .-----------------. .-----------------. " << endl;
	cout << "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |" << endl;
	cout << "| |   ______     | || |   _____      | || |      __      | || | ____  _____  | || |  _________   | |" << endl;
	cout << "| |  |_   __ " << "\\" << "   | || |  |_   _|     | || |     /  " << "\\" << "     | || ||_   " << "\\" << "|_   _| | || | |_   ___  |  | |" << endl;
	cout << "| |    | |__) |  | || |    | |       | || |    / /" << "\\" << " " << "\\" << "    | || |  |   " << "\\" << " | |   | || |   | |_  " << "\\" << "_|  | |" << endl;
	cout << "| |    |  ___/   | || |    | |   _   | || |   / ____ " << "\\" << "   | || |  | |" << "\\" << " " << "\\" << "| |   | || |   |  _|  _   | |" << endl;
	cout << "| |   _| |_      | || |   _| |__/ |  | || | _/ /    " << "\\" << " " << "\\" << "_ | || | _| |_" << "\\" << "   |_  | || |  _| |___/ |  | |" << endl;
	cout << "| |  |_____|     | || |  |________|  | || ||____|  |____|| || ||_____|" << "\\" << "____| | || | |_________|  | |" << endl;
	cout << "| |              | || |              | || |              | || |              | || |              | |" << endl;
	cout << "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |" << endl;
	cout << " '----------------'  '----------------'  '----------------'  '----------------'  '----------------' " << endl;
}

void inLogoRGB() // doi mau chu lien tuc
{
	int i = 0;
	ShowConsoleCursor(false);
	while(true)
	{
		if (i > 80) i = 0;
		SetColor(i);
		gotoxy(0, 0);
		cout << " \n.----------------.  .----------------.  .----------------.  .-----------------. .-----------------. " << endl;
		cout << "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |" << endl;
		cout << "| |   ______     | || |   _____      | || |      __      | || | ____  _____  | || |  _________   | |" << endl;
		cout << "| |  |_   __ " << "\\" << "   | || |  |_   _|     | || |     /  " << "\\" << "     | || ||_   " << "\\" << "|_   _| | || | |_   ___  |  | |" << endl;
		cout << "| |    | |__) |  | || |    | |       | || |    / /" << "\\" << " " << "\\" << "    | || |  |   " << "\\" << " | |   | || |   | |_  " << "\\" << "_|  | |" << endl;
		cout << "| |    |  ___/   | || |    | |   _   | || |   / ____ " << "\\" << "   | || |  | |" << "\\" << " " << "\\" << "| |   | || |   |  _|  _   | |" << endl;
		cout << "| |   _| |_      | || |   _| |__/ |  | || | _/ /    " << "\\" << " " << "\\" << "_ | || | _| |_" << "\\" << "   |_  | || |  _| |___/ |  | |" << endl;
		cout << "| |  |_____|     | || |  |________|  | || ||____|  |____|| || ||_____|" << "\\" << "____| | || | |_________|  | |" << endl;
		cout << "| |              | || |              | || |              | || |              | || |              | |" << endl;
		cout << "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |" << endl;
		cout << " '----------------'  '----------------'  '----------------'  '----------------'  '----------------' " << endl;
		i++;
		Sleep(100);
		if (kbhit() == true) break;
	}
	
}

void iconPlane(int x, int y,int dodai)
{
	for (int i = 0; i < dodai; i++)
	{
		gotoxy(x + i, y);		cout << "	. " << endl;
		gotoxy(x + i, y + 1);	cout << "----	=|= " << endl;
		gotoxy(x + i, y + 2);	cout << "-	=| \\ " << endl;
		gotoxy(x + i, y + 3);	cout << " |\\............." << endl;
		gotoxy(x + i, y + 4);	cout << " | |= AIR LINE =|)" << endl;
		gotoxy(x + i, y + 5);	cout << " |/'''''''''''''" << endl;
		gotoxy(x + i, y + 6);	cout << "-	=| / " << endl;
		gotoxy(x + i, y + 7);	cout << "----	=|= "  << endl;
		gotoxy(x + i, y + 8);	cout << "	' " << endl;
		Sleep(2);
	}

}

void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

// bien luu ket qua, vi tri bat dau x , y , lua chon trai , phai , khoang cach giua 2 nut
void select2(string &ketqua, int x ,int y, string trai, string phai, int khoangcach)
{
	char kytu;
	int black = 0,
		green = 2,
		blue = 1,
		grey = 8;
	const int vitriX = x;
	const int vitriY = y;
	string ktra = "";

	gotoxy(vitriX, vitriY);
	SetBGColor(grey);
	cout << trai;

	gotoxy(vitriX + khoangcach, vitriY);
	SetBGColor(grey);
	cout << phai;

	gotoxy(0,0);
	while (true)
	{
		// kiem tra xem ben nao dang chon        1 = Right, 2 = Left
		if (kbhit() == true)
		{
			kytu = _getch();
			if (kytu == -32)
			{
				kytu = _getch();
				
			}
			switch (kytu)
			{
			case Left: // nut da chon thi k di chuyen nua
				// di chuyen
				ketqua = trai;
				// bo mau ben phai
				gotoxy(vitriX + khoangcach, vitriY);
				SetBGColor(grey);
				cout << phai << "";

				// to mau ben trai
				gotoxy(vitriX, vitriY);
				SetBGColor(blue);
				cout << trai;
				ktra = 1;
				break;

			case Right: // nut da chon thi k di chuyen nua				
				// di chuyen
				ketqua = phai;
				//bo mau ben trai
				gotoxy(vitriX, vitriY);
				SetBGColor(grey);
				cout << trai <<"";
				// to mau ben phai
				gotoxy(vitriX+khoangcach, vitriY);
				SetBGColor(blue);
				cout << phai;
				ktra = 2;
				break;

			case 13:
				SetBGColor(grey);
				break;
			}
			if (kytu == 13) break;
		}
	}
	Normal();
}

void checkmau()
{
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int k = 0; k <= 255; k++) {
		SetConsoleTextAttribute(hConsoleColor, k);
		cout << k << " - Change color!  ";
		if (k % 3 == 0) cout << endl;
	}
}

void khungVeMBAY(int vitriX, int vitriY, int khoangcach, int soDay, int soDong)
{
	gotoxy(vitriX, vitriY + 1);
	Input();
	kekhung((soDong * 2) + ((soDong + 1) * khoangcach) + 2 , soDay + (soDay + 1) + 1, vitriX, vitriY);
	//tomaunen(soDay * 15 -2, (soDong * 2) - 2, vitriX + 1, vitriY + 1);
}

// cac phim them/ xoa/ sua/ esc/ f1
void phimGuide()
{
	InputHighLight();
	cout << "   INS = Them       DEL = Xoa       HOME = Sua";
	cout << "     F1 = Danh sach chuyen bay     ESC = Thoat   " << endl;
}

// cac phim dat ve/ huy ve
void phimGuide2()
{
	InputHighLight();
	cout << "   INS = Dat ve       DEL = Huy ve             ";
	cout << "             ESC = Thoat                        " << endl;
}
void phimGuide3()
{
	InputHighLight();
	cout << "             Bam ESC de tiep tuc                  ";
	cout << "                                             " << endl;
}

void phimGuideCB()
{
	InputHighLight();
	cout << "   INS = Them       DEL = Xoa       HOME = Sua       END = Huy chuyen";
	cout << "     F1 = Danh sach chuyen bay     ESC = Thoat   " << endl;
}

void khungScreen()
{
	SetBGColor(1);
	cout << "                                     "
		<< "                                     "
		<< "                                     "
		<< "                                     ";
	for (int i = 0; i < 27; i++)
	{
		gotoxy(94, wherey());
		cout << " " << endl;
	}
	Normal();
}

void khungMainScreen()
{
	Normal();
	system("cls");	
	timeGadget(38, 1);
	gotoxy(0, 5);
	phimGuide();
	khungScreen();
	
}

void khungDatHuyVe()
{
	Normal();
	system("cls");
	timeGadget(38, 1);
	gotoxy(0, 5);
	phimGuide2();
	khungScreen();
}

void khungThemCB()
{
	timeGadget(38, 1);
	gotoxy(0, 5);
	phimGuide3();
	khungScreen();
}

void khungThemMB()
{
	Normal();
	system("cls");
	timeGadget(38, 1);
	gotoxy(0, 5);
	phimGuide3();
	khungScreen();
}

void khungCB()
{
	Normal();
	system("cls");
	timeGadget(38, 1);
	gotoxy(0, 5);
	phimGuideCB();
	khungScreen();

}

void xoaManhinhTrai()
{
	int cao = 25, rong = 94;
	gotoxy(0, 7);
	Normal();
	for (int i = 0; i < cao; i++)
	{
		for (int k = 0; k < rong; k++)
		{
			cout << " ";
		}
		cout << endl;
	}
	gotoxy(0, 7);
}

void xoaManhinhPhai()
{
	int cao = 25, rong = 53;
	gotoxy(95, 7);
	Normal();
	for (int i = 0; i < cao; i++)
	{
		for (int k = 0; k < rong; k++)
		{
			cout << " ";
		}
		gotoxy(95, wherey() + 1);
	}
	gotoxy(95, 7);
}

void xuatFomatDate(int nam, int thang, int ngay, int gio, int phut)
{
	cout << nam << "/";
	if (thang < 10) cout << "0" << thang;
	else cout << thang;
	cout << "/";
	if (ngay < 10) cout << "0" << ngay;
	else cout << ngay;
	cout << "  ";

	if (gio < 10) cout << "0" << gio;
	else cout << gio;
	cout << ":";
	if (phut < 10) cout << "0" << phut;
	else cout << phut;
}