#include<iostream>
#include<winsock.h>
#include <windows.h>
#include <tlhelp32.h> 
#pragma comment(lib,"ws2_32.lib")
using namespace std;
void initialization();
const char* ip;//�ͻ���Ҫ���ӵ�ip 
const char* ret()//ip���� 
{
	string ip1;
	cout << "������Ҫ���ӵĺ���ip:";
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
	//���峤�ȱ���
	system("title �������Ӷ�");
	int send_len = 0;
	int recv_len = 0;
	//���巢�ͻ������ͽ��ܻ�����
	char send_buf[100];
	char recv_buf[100];
	//���������׽��֣����������׽���
	SOCKET s_server;
	//����˵�ַ�ͻ��˵�ַ
	SOCKADDR_IN server_addr;
	initialization();
	//���������Ϣ
	server_addr.sin_family = AF_INET;
	ret();
	server_addr.sin_addr.S_un.S_addr = inet_addr(ip);
	server_addr.sin_port = htons(25);
	//�����׽���
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(s_server, (SOCKADDR *)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "��������ʧ�ܣ��Ƿ��˳�(yes,no)" << endl;
		string yesn;
		cin >> yesn;
		if(yesn == "yes")
		{
			WSACleanup();
			return 0;
		}
	}
	else {
		cout << "���ӳɹ�����ʼ����ɣ�" << endl;
	}
 
	//����,��������
	while (1) 
	{
		cout << "�����뷢����Ϣ:";
		cin >> send_buf;
		string en = send_buf;
		chuli(d2ecrypt(en),send_buf);
		send_len = send(s_server, send_buf, 100, 0);
		if (send_len < 0) 
		{
			cout << "����ʧ�ܣ�������socket���⣬�Ƿ����ߣ�(yes,no)" << endl;
			string ok;
			cin >> ok;
			if(ok == "yes") break; 
		}
		recv_len = recv(s_server, recv_buf, 100, 0);
		if (recv_len < 0) {
			cout << "����ʧ�ܣ��п�������ĺ��������ˡ��Ƿ��˳���(yes,no)" << endl;
			string yn;
			cin >> yn; 
			if(yn == "yes") break;
		}
		else {
			
			string ex = recv_buf;
			chuli(d2ecrypt(ex),recv_buf);
			MessageBeep(MB_ICONEXCLAMATION);
			cout << "������Ϣ:" << recv_buf << endl;
		}
	}
	//�ر��׽���
	closesocket(s_server);
	//�ͷ�DLL��Դ
	WSACleanup();
	return 0;
}
void initialization() {
	//��ʼ���׽��ֿ�
	WORD w_req = MAKEWORD(3, 2);//�汾��
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cout << "��ʼ��socket��ʧ�ܣ�" << endl;
	}
	else {
		cout << "��ʼ��socket��ɹ���" << endl;
	}
	//���汾��
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "socket��汾�Ų�����" << endl;
		WSACleanup();
	}
	else {
		cout << "socket��汾��ȷ��" << endl;
	}
	//������˵�ַ��Ϣ
 
}
