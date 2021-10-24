#include<bits/stdc++.h>

using namespace std;

vector<vector<bool>> control_mat(int m)
{
	const int n = floor(log2((double)m))+1;
	vector<vector<bool>> C(n,vector<bool>(m));
	for(int j=0; j<m; ++j)
		for(int i=n-1; i>=0; --i)
			C[i][j] = (j+1)&(1<<(n-1-i));
	return C;
}

void print_mat(vector<vector<bool>> A)
{
	for(int i=0; i<(int)A.size(); ++i)
	{
		for(int j=0; j<(int)A[0].size(); ++j) printf("%d ",(int)A[i][j]);
		printf("\n");
	}
}

void swap_col(vector<vector<bool>> &C, pair<int,int> p)
{
	const int n = C.size(), m = C[0].size();
	vector<int> temp;
	for(int i=n-1; i>=0; --i) temp.push_back(C[i][p.first]);
	for(int i=0; i<n; ++i)
	{
		C[i][p.first] = C[i][p.second];
		C[i][p.second] = temp[n-1-i];
	}
}

vector<vector<bool>> generator_mat(vector<vector<bool>> C)
{
	const int n = C.size(), m = C[0].size();
	vector<pair<int,int>> moves = {};
	pair<int,int> p;
	unordered_map<int,int> hash;
	int sum;
	for(int i=0; i<m; ++i) hash[i+1] = i;
	for(int j=1, cnt=1; j<=m; j<<=1, ++cnt)
	{
		sum=0;
		p = make_pair(hash[j],m-cnt);
		swap_col(C,p);
		for(int i=n-1; i>=0; --i) sum += (int)C[i][hash[j]]<<(n-1-i);
		swap(hash[sum],hash[j]);
		moves.push_back(p);
	}
	const int l = m-n;
	vector<vector<bool>> G(l,vector<bool>(m));

	for(int v=l-1, j=0; v>=0; --v, ++j)
		for(int i=l-1; i>=0; --i)
			G[i][j] = (1<<v)&(1<<(l-1-i));

	for(int j=l; j<m; ++j)
		for(int i=0; i<l; ++i)
			G[i][j] = C[j-l][i];

	while(!moves.empty())
	{
		swap_col(G,moves.back());
		moves.pop_back();
	}
	return G;
}

int main()
{	
	int n;
	scanf("%d",&n);
	vector<vector<bool>> t = control_mat(n);
	printf("H-Matrix\n");
	print_mat(t);
	printf("\nG-Matrix\n");
	print_mat(generator_mat(t));
	return 0;
}
