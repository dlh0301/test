// 251117.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//#include<stdio.h>
//#include <iostream>
//using namespace std;
//int n, m, t;
//int sx, sy;
//int dx, dy;
//bool flag = false;
//char a[10][10] = {0};
//int dir[4][2] = { 0,1,1,0,-1,0,0,-1 };
//
//void DFS(int x, int y, int time) {
//    if (x<0 || x>n || y<0 || y>m)return;
//    if (x == dx && y == dy) {
//        flag = true;
//        return;
//    }
//    if (flag)return;
//    int temp = t - time - (abs(x - dx) + abs(y - dy));
//    if (temp &1 || temp < 0) {
//        return;
//    }
//    for (int i = 0;i < 4;i++) {
//        int xx = x + dir[i][0];
//        int yy = y + dir[i][1];
//        if (a[xx][yy] != 'X') {
//            a[xx][yy] = 'X';
//            DFS(xx, yy, time + 1);
//            a[xx][yy] = '.';
//            if (flag)return;
//        }
//    }
//}
//
//int main()
//{
//    while (cin >> n >> m >> t) {
//        if (n == 0||m==0)break;
//        for (int i = 0;i < n;i++) {
//            for (int j = 0;j < m;j++) {
//                cin >> a[i][j];
//                if (a[i][j] == 'S') {
//                    sx = i;sy = j;
//                }
//                else if (a[i][j] == 'D') {
//                    dx = i;dy = j;
//                }
//            }
//        }
//        a[sx][sy] = 'X';
//        DFS(sx, sy, 0);
//        if (flag) {
//            cout << "YES" << endl;
//        }
//        else {
//            cout << "NO" << endl;
//        }
//    }
//    return 0;
//}
// 
// 










//#include<stdio.h>
//#include <iostream>
//#include<vector>
//#include<string.h>
//#include<math.h>
//using namespace std;
//int dp[101][101] ;
//vector<int>path[101];
//int roomNumber, trooperNumber;
//int cost[101];
//bool visited[101];
//int max(int x, int y) {
//	return x > y ? x : y;
//}
//
//void solve(int deep)
//{
//	visited[deep] = true;
//	for (int i = 0;i < path[deep].size();i++) {
//		int value = path[deep][i];
//		if (visited[value])continue;
//		solve(value);
//
//		for (int j = trooperNumber - 1;j >= cost[deep];j--) {
//			for (int index = 1;j + index <= trooperNumber;index++) {
//				if (dp[value][index]) {
//					dp[deep][j + index] = max(dp[deep][index + j], dp[deep][index] + dp[value][j]);
//				}
//			}
//		}
//	}
//
//}
//
//int main() 
//{
//	while (cin >> roomNumber >> trooperNumber) {
//		if (roomNumber == -1 && trooperNumber == -1)break;
//		for (int i = 0;i <= roomNumber;i++) {
//			path[i].clear();
//		}
//		memset(dp, 0, sizeof(dp));
//		memset(visited, 0, sizeof(visited));
//		int tempA;
//		for (int i = 1;i <= roomNumber;i++) {
//			cin >> cost[i] >> tempA;
//			cost[i] = (cost[i] + 19) / 20;
//			for (int j = cost[i];j <=trooperNumber;j ++ ) {
//				dp[i][j] = tempA;
//			}
//		}
//		int tempB;
//		for (int i = 1;i <= roomNumber - 1;i++) {
//			cin >> tempB >> tempA;
//			path[tempA].push_back(tempB);
//			path[tempB].push_back(tempA);
//		}
//		if (trooperNumber == 0) {
//			printf("0\n");
//		}
//		else {
//			solve(1);
//			printf("%d\n", dp[1][trooperNumber]);
//		}
//	}
//	return 0;
//}







//#include<stdio.h>
//#include <iostream>
//#include<vector>
//#include<string.h>
//#include<math.h>
//using namespace std;
//
//
//int f(int n)
//{
//	if (n >= 1) {
//		return n * f(n - 1);
//	}
//	else {
//		return 1;
//	}
//}
//int main()
//{
//	printf("n e\n");
//	printf("- -----------\n");
//	double sum = 0;
//	for (int i = 0;i < 10;i++) {
//		sum += (double)1 / f(i);
//		if (i == 0) {
//			printf("%d %.0f\n",i, sum);
//		}
//		else if (i == 1) {
//			printf("%d %.0f\n",i, sum);
//		}
//		else if (i == 2) {
//			printf("%d %.1f\n",i, sum);
//		}
//		else if(i==3){
//			printf("%d %.9f\n",i, sum);
//		}
//		else if (i == 4) {
//			printf("%d %.9f\n",i, sum);
//		}
//	}
//}

//#include<stdio.h>
//#include <iostream>
//#include<vector>
//#include<string.h>
//#include<math.h>
//using namespace std;
//
//int main()
//{
//	unsigned int MOD, STEP;
//	while (cin >> STEP >> MOD) {
//		int seed = 0;
//		int count = 0;
//		do {
//			seed = (seed + STEP) % MOD;
//			count++;
//		} while (seed != 0);
//		if (count == MOD) {
//			printf("GOOD CHOICE\n");
//		}
//		else printf("BAD CHOICE\n");
//	}
//}

#include<stdio.h>
#include <iostream>
#include<vector>
#include<string.h>
#include<math.h>
using namespace std;

int main()
{

}











// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
