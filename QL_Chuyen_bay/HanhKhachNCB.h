#pragma once
#include "Chuyenbay.h"

struct QL
{
	string CMND;
	Date NgayBay;
	string MaCB;
};

struct NodeQL
{
	QL info;
	NodeQL *pNext;
};

struct listql
{
	NodeQL *phead;
	NodeQL *ptail;
};
typedef struct listql ListQL;

void khoitaoDSQL(ListQL &ql)
{
	ql.phead = NULL;
	ql.ptail = NULL;
}

void Free_QL(ListQL &ql)
{
	NodeQL *tam = ql.phead;
	while (ql.phead != NULL)
	{
		tam = tam->pNext;
		delete ql.phead;
		ql.phead = tam;
	}
	khoitaoDSQL(ql);
}

void Insert_OrderQL(ListQL &i, NodeQL *p)
{
	ListQL k;
	for (k.ptail = i.phead; k.ptail != NULL && k.ptail->info.CMND < p->info.CMND; k.ptail = k.ptail->pNext)
	{
		k.phead = k.ptail;
	}
	if (k.ptail == i.phead)
	{
		p->pNext = i.phead;
		i.phead = p;
	}
	else
	{
		p->pNext = k.ptail;
		k.phead->pNext = p;
	}
}

void KhoiTaoListQL(ListQL &ql, LISTCB &cb, ListMB &mb)
{
	khoitaoDSQL(ql);
	if (cb.phead == NULL || mb.n == 0)
	{
		return;
	}
	int soGhe;
	for (NODECB *i = cb.phead; i != NULL; i = i->pketiep)
	{
		if (i->info.TrangThai == 1 || i->info.TrangThai == 2)
		{
			soGhe = GetSoGhe(mb, i->info.SoHieuMB);
			for (int j = 0; j < soGhe; j++)
			{
				cout << i->info.DSVe[j].maVe << endl;
			}
			for (int j = 0; j < soGhe; j++)
			{
				if (i->info.DSVe[j].CMND.empty() != true)
				{
					NodeQL *p = new NodeQL();
					p->info.CMND = i->info.DSVe[j].CMND;
					p->info.NgayBay = i->info.NgayGioBay;
					p->info.MaCB = i->info.MaCB;
					p->pNext = NULL;
					Insert_OrderQL(ql, p);
				}
			}
		}
	}
}

NodeQL* middle(NodeQL* start, NodeQL* last)
{
	if (start == NULL)
		return NULL;

	NodeQL* slow = start;
	NodeQL* fast = start->pNext;

	while (fast != last)
	{
		fast = fast->pNext;
		if (fast != last)
		{
			slow = slow->pNext;
			fast = fast->pNext;
		}
	}
	return slow;
}

NodeQL* binarySearchQL(ListQL i, string CMND)
{
	NodeQL* start = i.phead;
	NodeQL* last = NULL;

	do
	{
		// Find middle 
		NodeQL* mid = middle(start, last);

		// If middle is empty 
		if (mid == NULL)
			return NULL;

		// If value is present at middle 
		if (mid->info.CMND == CMND)
			return mid;

		// If value is more than mid 
		else if (mid->info.CMND < CMND)
			start = mid->pNext;

		// If the value is less than mid. 
		else
			last = mid;

	} while (last == NULL || last != start);

	// value not present 
	return NULL;
}

void Xoa_QL(ListQL &i, string a)
{
	// nếu danh sách rỗng thì không làm gì hết
	if (i.phead == NULL)
	{
		return;
	}
	NodeQL *g;
	/*if (i.phead->info.MaCB == a)
	{
		g = i.phead;
		i.phead = i.phead->pNext;
		delete g;
	}*/
	//g = new NODECB; // node g là node trỏ đến node nằm trước node cần xóa: x
	// duyệt danh sách liên kết đơn để tìm
	for (NodeQL *k = i.phead; k != NULL; k = k->pNext)
	{
		// phát hiện phần tử cần xóa
		if (k->info.MaCB == a)
		{
			g->pNext = k->pNext; // cập nhật mối liên kết giữa node k với node sau node h
			delete k; // xóa node nằm sau node k	
			return;
		}
		g = k; // cho node g trỏ đến node k
	}
}

void Xoa_QL_2(ListQL &i, string MCB, string CMND) //xoa theo huy ve
{
	// nếu danh sách rỗng thì không làm gì hết
	if (i.phead == NULL)
	{
		return;
	}
	NodeQL *g;
	if (i.phead->info.CMND == CMND && i.phead->info.MaCB == MCB)
	{
		g = i.phead;
		i.phead = i.phead->pNext;
		delete g;
	}
	//g = new NODECB; // node g là node trỏ đến node nằm trước node cần xóa: x
	// duyệt danh sách liên kết đơn để tìm
	for (NodeQL *k = i.phead; k != NULL; k = k->pNext)
	{
		// phát hiện phần tử cần xóa
		if (k->info.CMND == CMND && k->info.MaCB == MCB)
		{
			g->pNext = k->pNext; // cập nhật mối liên kết giữa node k với node sau node h
			delete k; // xóa node nằm sau node k	
			return;
		}
		g = k; // cho node g trỏ đến node k
	}
}
// ======================================================================


void KhoiTaoListCBnMB(ListCBnMB &listCbnMB, ListMB MB, LISTCB CB)
{
	if (MB.n == 0)
	{
		return;
	}
	listCbnMB.index = MB.n;
	for (int i = 0; i < MB.n; i++)
	{
		listCbnMB.MBnCB[i].sohieuMB = MB.DSMB[i]->sohieuMB;
		listCbnMB.MBnCB[i].list.phead = NULL;
		listCbnMB.MBnCB[i].list.ptail = NULL;
	}
	QuickSort_MBnCB(listCbnMB.MBnCB, 0, listCbnMB.index - 1);
	cout << "=============================";
	for (int i = 0; i < MB.n; i++)
	{
		cout << listCbnMB.MBnCB[i].sohieuMB << endl;
	}
	for (NODECB *i = CB.phead; i != NULL; i = i->pketiep)
	{
		int Search = binarySearch_CBnMB(listCbnMB.MBnCB, listCbnMB.index, i->info.SoHieuMB);
		if (Search != -1)
		{
			NodeDataCBnMB *p = new NodeDataCBnMB();
			p->data.NgayGioBay = i->info.NgayGioBay;
			p->data.MaCB = i->info.MaCB;
			p->pketiep = NULL;
			Insert_Order_CBnMB(listCbnMB.MBnCB[Search].list, p);
		}
	}
	system("pause");
}

