#include <iostream>
#include <queue>
using namespace std;
#define MAX 1001

// ���� ����
int n, m, v;
int map[MAX][MAX];
bool visited[MAX];
queue<int> q;

int main()
{
	// �Է� �� �ޱ�
	cin >> n, m, v;

	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		map[a][b] = 1;
		map[b][a] = 1;
	}

	reset();
	dfs(v);

	cout << '\n';

	reset();
	bfs(v);

	return 0;
}