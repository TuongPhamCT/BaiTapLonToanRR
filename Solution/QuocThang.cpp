#include <iostream>
#include <fstream>
#define infi 9999

using namespace std;
int n, g[6][6], dem = 1, b[100], doi[6];
int S[6], P[6], Len[6];
int u, v;
int spanning[6][6];
bool d[6];
int hs[6][6] =
{
	{500, 3, 500, 500, 500, 5},
	{3, 500, 7, 500, 500, 1},
	{500, 7, 500, 5, 1, 8},
	{500, 500, 5, 500, 6, 2},
	{500, 500, 1, 6, 500, 7},
	{5, 1, 8, 2, 7, 500}
};

void duyetDoThiDFS(int i)
{
	for (int j = 1; j <= n; j++)
	{
		if (g[i][j] != 0 && d[j] == 0)
		{
			d[j] = 1;
			b[dem++] = j; 
			duyetDoThiDFS(j);
		}
	}
}

void inKQDuyet() {
	for (int i = 0; i < n; i++)
	{
		cout << "Da duyet dinh " << b[i] << endl;
	}
}


void BFS(int i) {

	int u, dauQ, cuoiQ;

	dauQ = 0; cuoiQ = 0; doi[cuoiQ] = i; d[i] = false;

	while (dauQ <= cuoiQ) {

		u = doi[dauQ];

		cout << "duyet qua dinh: " << u+1 << endl;

		dauQ = dauQ + 1;

		for (int j = 0; j < n; j++) {

			if (g[u][j] == 1 && d[j]) {

				cuoiQ = cuoiQ + 1;

				doi[cuoiQ] = j;

				d[j] = false;

			}

		}

	}

}



void TimBac()
{
	for (int i = 0; i < n; i++)
	{
		int d = 0;
		for (int j = 0; j < n; j++)
		{
			if (g[i][j] == 1)
				d++;
		}
		cout << "Bac cua dinh " << i + 1 << " la: " << d << endl;
	}
}

int prims()
{
	int cost[6][6];
	int u, v, min_distance, distance[6], from[6];
	int visited[6], no_of_edges, i, min_cost, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			if (g[i][j] == 0)
				cost[i][j] = infi;
			else
				cost[i][j] = hs[i][j];
			spanning[i][j] = 0;
		}
	distance[0] = 0;
	visited[0] = 1;
	for (i = 1; i < n; i++)
	{
		distance[i] = cost[0][i];
		from[i] = 0;
		visited[i] = 0;
	}
	min_cost = 0; //cost of spanning tree
	no_of_edges = n - 1; //no. of edges to be added
	while (no_of_edges > 0)
	{
		min_distance = infi;
		for (i = 1; i < n; i++)
			if (visited[i] == 0 && distance[i] < min_distance)
			{
				v = i;
				min_distance = distance[i];
			}
		u = from[v];
		spanning[u][v] = distance[v];
		spanning[v][u] = distance[v];
		no_of_edges--;
		visited[v] = 1;
		for (i = 1; i < n; i++)
			if (visited[i] == 0 && cost[i][v] < distance[i])
			{
				distance[i] = cost[i][v];
				from[i] = v;
			}
		min_cost = min_cost + cost[u][v];
	}
	return(min_cost);
}

int main()
{
	/*ofstream outfile;
	outfile.open("G9_input.txt");
	int arr[6][6] =
	{
		{0, 1, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 1},
		{0, 1, 0, 1, 1, 1},
		{0, 0, 1, 0, 1, 1},
		{0, 0, 1, 1, 0, 1},
		{1, 1, 1, 1, 1, 0}
	};
	cout << "1. Ghi file" << endl;
	outfile << 6 << endl;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			outfile << arr[i][j] << " ";
		}
		outfile << endl;
	}*/

	//Yeu cau 2. Doc file vao chuong trinh, luu vao n, va mang g
	ifstream infile;
	infile.open("G9_input.txt");
	infile >> n;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			infile >> g[i][j];
		}
	}

	//Yeu cau 3
	//i.Duyet do thi
	cout << "Duyet do thi theo DFS" << endl;
	b[0] = 1;
	d[1] = 1;
	duyetDoThiDFS(1);
	inKQDuyet();

	cout << endl;
	cout << "Duyet do thi theo BFS" << endl;
	for (int i = 0; i < n; i++)
	{
		d[i] = true;
	}
	for (int i = 0; i < n; i++)
		if (d[i])
			BFS(i);

	//ii. Tim bac cua cac dinh
	cout << endl;
	cout << "Tim bac cua cac dinh trong do thi: " << endl;
	TimBac();

	//iii. Tim duong di ngan nhat
	cout << endl;
	cout << "Tim duong di ngan nhat:" << endl;
	cout << "Nhap dinh u "; cin >> u;
	cout << "Nhap dinh v "; cin >> v;
	u--; v--;
	for (int i = 0; i < n; i++) {
		Len[i] = 500;
		S[i] = 0;                     
		P[i] = u;                     
	}
	Len[u] = 0;

	int i;
	while (S[v] == 0) 
	{
		for (i = 0; i < n; i++)          
			if (!S[i] && Len[i] < 500)
				break;
		if (i >= n) {
			break;
		}

		for (int j = 0; j < n; j++) 
		{
			if (!S[j] && Len[i] > Len[j]) {
				i = j;
			}
		}

		S[i] = 1;
		
		for (int j = 0; j < n; j++) 
		{
			if (!S[j] && Len[i] + hs[i][j] < Len[j]) {
				Len[j] = Len[i] + hs[i][j];
				P[j] = i;
			}
		}
	}


	if (Len[v] > 0 && Len[v] < 50) {
		cout << "Do dai duong di ngan nhat tu dinh " << u + 1 << " den dinh " << v + 1 << " la: " << Len[v] << endl;

		while (i != u) {
			cout << i + 1 << " <-- ";
			i = P[i];
		}

		cout << u + 1;
	}
	else {
		cout << "Khong tim thay duong di" << endl;
	}

	//iv. Tim cay khung nho nhat
	cout << endl;
	cout << "Cay khung theo thuat toan Prim:" << endl;
	cout << "So dinh: " << n << endl;
	for (i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << g[i][j] << " ";
		}
		cout << endl;
	}
	int tongGT = prims();
	cout << "Tong gia tri cua cay khung la: " << tongGT << endl;
	return 0;
}