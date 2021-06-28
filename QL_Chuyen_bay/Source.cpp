//void xuatDSMBay(ListMB &l)
//{
//	cout << "\t~ DANH SACH MAY BAY ~" << endl;
//	cout << "Co " << l.n << " may bay" << endl;
//
//	// ve man hinh xuat 
//	int VTx, VTy;
//	int trang = 1, sotrang;
//
//	if ((l.n % 15) > 0) // tinh so trang
//		sotrang = (l.n / 15) + 1;
//	else if ((l.n % 15 == 0))
//		sotrang = l.n / 15;
//
//	veManhinhXuatMBAY(VTx, VTy); // VTx =0   VTy=13
//
//								 // in so trang
//	gotoxy(VTx + 35, VTy + 15);
//	cout << "<" << trang << "/" << sotrang << ">";
//	gotoxy(VTx, VTy + 1); // dua con tro ve dau trang
//
//						  // load data vao
//	if (l.n > 15)
//	{
//		char kytu;
//		int dem = 0, phai = 0;
//
//		// load 15 may bay dau
//		// 0 14
//		for (int i = 0; i < 15; i++)
//		{
//			xuatMBay(l.DSMB[i]);
//			dem += 1;
//		}
//		// luc nay dem = 15
//		while (1)
//		{
//			if (kbhit() == true)
//			{
//				kytu = _getch();
//				if (kytu == -32)
//				{
//					kytu = _getch();
//
//				}
//				switch (kytu)
//				{
//				case Left:
//					if (dem == 0) break; // neu ben trai khong con gi thi break
//					phai = 0; // reset phai
//					if (dem > 15)
//					{
//						// clear man hinh va dua con tro ve dau 
//						tomaunen(75, 15, VTx + 1, VTy + 1);
//						gotoxy(0, 14);
//
//						for (int i = dem - 15; i < dem; i++)
//						{
//							xuatMBay(l.DSMB[i]);
//						}
//						dem -= 15;
//					}
//					else
//					{
//						// clear man hinh va dua con tro ve dau 
//						tomaunen(75, 15, VTx + 1, VTy + 1);
//						gotoxy(0, 14);
//
//						for (int i = 0; i < dem; i++)
//						{
//							xuatMBay(l.DSMB[i]);
//						}
//					}
//					// dem = 15, trai = 15
//
//					// thay doi trang
//					if (trang > 1) trang -= 1; // trang >=0
//											   // 35 28
//					gotoxy(VTx + 35, VTy + 15);
//					cout << "<" << trang << "/" << sotrang << ">";
//					break;
//
//				case Right:
//
//					if (dem + 15 > l.n)
//					{
//						//if ((dem + phai) >= l.n) break; // ds k du 1 trang dau hoac da load het				
//						// clear man hinh va dua con tro ve dau 
//						tomaunen(75, 15, VTx + 1, VTy + 1);
//						gotoxy(0, 14);
//
//						// dem = 15/30/45....  phai = 0		
//						for (int i = dem; i < dem + 15; i++)
//						{
//							if (i < l.n)
//								xuatMBay(l.DSMB[i]);
//							else
//								break; // data k du 1 trang thi break
//						}
//						//dem van bang = 15 
//					}
//					else
//					{
//						// clear man hinh va dua con tro ve dau 
//						tomaunen(75, 15, VTx + 1, VTy + 1);
//						gotoxy(0, 14);
//						for (int i = dem; i < dem + 15; i++)
//						{
//							if (i >= l.n) break; // data k du 1 trang thi break
//							xuatMBay(l.DSMB[i]);
//						}
//						dem += 15; // dem tang len
//					}
//					//if (phai == 0) // sang phai lan dau hoac sau khi moi tang dem
//					//{
//					//	// dem = 15/30/45....  phai = 0		
//					//	for (int i = dem; i < dem + 15; i++)
//					//	{
//					//		if (i >= l.n) break; // data k du 1 trang thi break
//					//			xuatMBay(l.DSMB[i]);
//					//			phai += 1;				
//					//	}
//					//	//dem van bang = 15 , phai = 15
//					//}
//					//else 
//					//{				
//					//	// clear man hinh va dua con tro ve dau 
//					//	tomaunen(75, 15, VTx + 1, VTy + 1);
//					//	gotoxy(0, 14);
//					//	dem += 15; // dem tang len
//					//	
//					//	// bat dau dem lai phai
//					//	for (int i = dem ; i < dem + 15; i++)
//					//	{
//					//		if (i >= l.n) break; // data k du 1 trang thi break
//					//		xuatMBay(l.DSMB[i]);
//					//	}
//					//	phai = 0; //reset phai
//					//}
//
//					//thay doi trang
//					if (trang < sotrang) trang += 1;
//					// 35 28
//					gotoxy(VTx + 35, VTy + 15);
//					cout << "<" << trang << "/" << sotrang << ">";
//					break;
//
//				case 13:
//					gotoxy(0, 30);
//					Normal();
//					break;
//				}
//				// end switch
//				if (kytu == 13) break;
//			}
//			// end kbhit()			
//		}
//		// end while		
//	}
//	else // load het 
//	{
//		for (int i = 0; i < l.n; i++)
//		{
//			xuatMBay(l.DSMB[i]);
//		}
//	}
//
//	gotoxy(0, 30);
//	Normal();
//	system("pause");
//}