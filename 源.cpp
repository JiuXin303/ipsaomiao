#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#define ipMax 255
std::fstream outfile("result.txt", std::ios_base::out | std::ios_base::trunc);
void myPing(short ip1, short ip2, short ip3, short ip4) {
	FILE* cmdResult;
	std::string ip = "";
	std::string result = "";
	ip += std::string("ping ") += std::to_string(ip1) += std::string(".") +=
		std::to_string(ip2) += std::string(".") += std::to_string(ip3) +=
		std::string(".") += std::to_string(ip4);
	std::cout << "正在ping......,请耐心等待" << std::endl;
	if ((cmdResult = _popen(ip.c_str(), "r")) != NULL) {
		while (!feof(cmdResult)) {
			result += fgetc(cmdResult);
		}
		std::cout << "ping完成，打印信息" << std::endl;
		if (strstr(result.c_str(), ("请求超时")) == NULL) {
			outfile << ip << std::endl;
		}
		std::cout << result;
	}
	_pclose(cmdResult);
	ip.clear();
	result.clear();
}
int main(int argc, char* argv[]) {
	short ip1[2], ip2[2], ip3[2], ip4[2];
	short select;
	short loop = 1;
	std::string ip;
	while (loop)
	{
		std::cout << "请输入选择，1为网址，2为地址段,3退出：";
		scanf("%hd", &select);
		switch (select)
		{
		case 1:
			std::cout << "请输入网址：";
			std::cin >> ip;
			ip.insert(0, "ping ");
			system(ip.c_str());
			break;
		case 2:
			while (1) {
				std::cout << "输入开始ip:";
				scanf("%hd.%hd.%hd.%hd", &ip1[0], &ip2[0], &ip3[0], &ip4[0]);
				std::cout << "输入结束ip:";
				scanf("%hd.%hd.%hd.%hd", &ip1[1], &ip2[1], &ip3[1], &ip4[1]);
				if (ip1[0] <= ipMax || ip1[1] <= ipMax || ip2[0] <= ipMax || ip2[1] <= ipMax ||
					ip3[0] <= ipMax || ip3[1] <= ipMax || ip4[0] <= ipMax || ip4[1] <= ipMax)
				{
					break;
				}
				else {
					std::cout << "输入错误,请重新输入" << std::endl;
				}
			}
			for (; ip1[0] <= ip1[1]; ip1[0]++) {
				for (; ip1[0] != ip1[1] || ip2[0] <= ipMax; ip2[0]++)
				{
					if (ip1[0] == ip1[1] && ip2[0] == ip2[1])
					{
						ip2[0] = ip2[1];
					}
					for (; ip1[0] != ip1[1] || ip2[0] != ip2[1] || ip3[0] <= ipMax; ip3[0]++)
					{
						if (ip1[0] == ip1[1] && ip2[0] == ip2[1] && ip3[0] == ip3[1])
						{
							ip3[0] = ip3[1];
						}
						for (; ip1[0] != ip1[1] || ip2[0] != ip2[1] || ip3[0] != ip3[1] || ip4[0] <= ipMax; ip4[0]++)
						{
							if (ip1[0] == ip1[1] && ip2[0] == ip2[1] && ip3[0] == ip3[1] && ip4[0] == ip4[1])
							{
								ip4[0] = ip4[1];
								myPing(ip1[0], ip2[0], ip3[0], ip4[0]);
								goto end;
							}
							myPing(ip1[0], ip2[0], ip3[0], ip4[0]);
							if (ip4[0] == ipMax)
							{
								ip4[0] = 0;
								break;
							}
						}
						if (ip3[0] == ipMax)
						{
							ip3[0] = 0;
							break;
						}
					}
					if (ip2[0] == ipMax) {
						ip2[0] = 0;
						break;
					}
				}
			}
		end:
			std::cout << "成功ping的ip地址已写入outfile文件中" << std::endl;
			outfile.close();
			break;
		case 3:
			loop = 0;
			break;
		default:
			break;
		}
	}
	system("pause");
	return 0;
}
