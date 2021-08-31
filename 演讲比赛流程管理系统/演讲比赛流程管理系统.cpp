#include<iostream>
using namespace std;
#include"speehManager.h"
#include<string>
#include<ctime>

int main()
{
	srand((unsigned int)time(NULL));
	SpeechManager sm;
//	sm.show_menu();
	//测试选手
	//for (map<int, Speaker>::iterator it = sm.m_speaker.begin();it != sm.m_speaker.end();it++)
	//{
	//	cout << "参赛选手的编号：" << it->first << " " ;
	//	cout << "参赛选手的姓名：" << it->second.m_name << " ";
	//	cout << "参赛选手的的得分：" << it->second.m_score[0] << " ";
	//	cout << endl;
	//}

	//退出功能接口
	//存储用户选择
	int choice = -1;
	while (true)
	{
		sm.show_menu();
		
		cout << "请输入想要选择的功能：" << endl;
		cin >> choice;//用户选择

		switch (choice)
		{
			//开始演讲比赛
		case 1:sm.startSpeech();
			break;
			//查看往届记录
		case 2:
			sm.showRecod();
			break;
			//清空比赛记录
		case 3:
			sm.clearRecord();
			break;
			//退出系统
		case 0:
			sm.exitScreen();
			break;

		default:
			system("cls");//清屏
			break;
		}

	}
	system("pause");
	return 0;
}