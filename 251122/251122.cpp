// 251122.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//#include<cmath>
//#include<cstdio>
//#include<cstdlib>
//#include<string>
//#include<cstring>
//#include<iostream>
//#include<algorithm>
//using namespace std;
//
//char ans[20], str[20];
//int vis[20],flag;
//bool cmp(char a, char b) {
//    return a > b;
//}
//void dfs(int dep, int target, int len)
//{
//    if (dep == 5) {
//        int sum = 0;
//        for (int i = 1;i <= dep;++i) {
//            sum += (int)pow(ans[i - 1], i) * (int)pow(-1., i + 1);
//        }
//        if (sum == target) {
//            flag = 1;
//            printf("%s", ans);
//        }
//        return;
//    }
//    for (int i = 0;i < len;++i) {
//        if (!vis[i]) {
//            vis[i] = 1;
//            ans[dep] = str[i];
//            dfs(dep + 1, target, len);
//            if (flag)return;
//            vis[i] = 0;
//        }
//    }
//}
//int main()
//{
//    int target;
//    while (scanf_s("%d%s", &target, str,(unsigned)sizeof(str)) == 2 && strcmp(str, "END") != 0 && target != 0) {
//        flag = 0;
//        memset(vis, 0, sizeof(vis));
//        int len = strlen(str);
//        sort(str, str + len, cmp);
//        dfs(0, target, len);
//        if (!flag) {
//            printf("No Solution");
//        }
//        memset(str, 0, sizeof(str));
//    }
//}



#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n;
int ans[25] = { 0 };
int vis[25] = { 0 };

int IsPrime(int x) {
	if (x <= 1)return 0;
	int r = (int)sqrt((double)x);
	for (int i = 2;i <=r;i++) {
		if (x % i == 0) {
			return 0;
		}
	}
	return 1;
}

void dfs(int k, int now)
{
	if (k == n) {
		if (IsPrime(now + ans[0])) {
			for (int i = 0;i < n;++i) {
				printf("%d%c", ans[i], i == n - 1 ? '\n' : ' ');
			}
		}
		return;
	}
	for (int i = 2;i <= n;++i) {
		if (!vis[i] && IsPrime(now + i)) {
			vis[i] = 1;
			ans[k] = i;
			dfs(k + 1, i);
			vis[i] = 0;
		}
	}
}
int main()
{
	while (scanf_s("%d", &n) != EOF) {
		memset(vis, 0, sizeof(vis));
		vis[1] = 1;
		ans[0] = 1;
		dfs(1, 1);
		putchar('\n');
	}
	return 0;
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
