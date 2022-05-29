#include<iostream>
#include<winsock.h>
#include <windows.h>
#include <tlhelp32.h> 
#pragma comment(lib,"ws2_32.lib")
using namespace std;
void initialization();
const char* ip;//客户端要连接的ip 
const char* ret()//ip处理 
{
	string ip1;
	cout << "请输入要连接的好友ip:";
	cin >> ip1;
	ip = ip1.c_str();
}
const char* pswd = "YGHW7DJEoH3p/7DIgV4+wXPu6dD+8eECqwm1hLACOxkfZnOFZ1VGxeMCgYEA8UYHnIJL0gmo4T/zDaMr8vsn7Ck+wLjXUsYt1/EulLtVnuH76FU0PkjJqBdre5Gjf23/Enllm1yVtelKTwzeIPNikVgErpRQAo6PZOmrOPMBAnb5j8RAh9OUR48m/ZTJEpoS";
string d2ecrypt(string s)
{
	for(int i = 0;i <= s.size() - 1;i++)
	{
		s[i] ^= pswd[i % strlen(pswd)];
	}
	return s;
}
char chuli(string s,char x[100])
{
	for(int i = 0;i <= s.size() - 1;i++)
	{
		x[i] = s[i];
	}
}
int main() {
	//定义长度变量
	system("title 主动连接端");
	int send_len = 0;
	int recv_len = 0;
	//定义发送缓冲区和接受缓冲区
	char send_buf[100];
	char recv_buf[100];
	//定义服务端套接字，接受请求套接字
	SOCKET s_server;
	//服务端地址客户端地址
	SOCKADDR_IN server_addr;
	initialization();
	//填充服务端信息
	server_addr.sin_family = AF_INET;
	ret();
	server_addr.sin_addr.S_un.S_addr = inet_addr(ip);
	server_addr.sin_port = htons(25);
	//创建套接字
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(s_server, (SOCKADDR *)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "好友连接失败！是否退出(yes,no)" << endl;
		string yesn;
		cin >> yesn;
		if(yesn == "yes")
		{
			WSACleanup();
			return 0;
		}
	}
	else {
		cout << "连接成功！开始聊天吧！" << endl;
	}
 
	//发送,接收数据
	while (1) 
	{
		cout << "请输入发送信息:";
		cin >> send_buf;
		string en = send_buf;
		chuli(d2ecrypt(en),send_buf);
		send_len = send(s_server, send_buf, 100, 0);
		if (send_len < 0) 
		{
			cout << "发送失败！可能是socket问题，是否下线？(yes,no)" << endl;
			string ok;
			cin >> ok;
			if(ok == "yes") break; 
		}
		recv_len = recv(s_server, recv_buf, 100, 0);
		if (recv_len < 0) {
			cout << "接受失败！有可能是你的好友下线了。是否退出？(yes,no)" << endl;
			string yn;
			cin >> yn; 
			if(yn == "yes") break;
		}
		else {
			
			string ex = recv_buf;
			chuli(d2ecrypt(ex),recv_buf);
			MessageBeep(MB_ICONEXCLAMATION);
			cout << "好友信息:" << recv_buf << endl;
		}
	}
	//关闭套接字
	closesocket(s_server);
	//释放DLL资源
	WSACleanup();
	return 0;
}
void initialization() {
	//初始化套接字库
	WORD w_req = MAKEWORD(3, 2);//版本号
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cout << "初始化socket库失败！" << endl;
	}
	else {
		cout << "初始化socket库成功！" << endl;
	}
	//检测版本号
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "socket库版本号不符！" << endl;
		WSACleanup();
	}
	else {
		cout << "socket库版本正确！" << endl;
	}
	//填充服务端地址信息
 
}
