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
	//����ѡ��
	//for (map<int, Speaker>::iterator it = sm.m_speaker.begin();it != sm.m_speaker.end();it++)
	//{
	//	cout << "����ѡ�ֵı�ţ�" << it->first << " " ;
	//	cout << "����ѡ�ֵ�������" << it->second.m_name << " ";
	//	cout << "����ѡ�ֵĵĵ÷֣�" << it->second.m_score[0] << " ";
	//	cout << endl;
	//}

	//�˳����ܽӿ�
	//�洢�û�ѡ��
	int choice = -1;
	while (true)
	{
		sm.show_menu();
		
		cout << "��������Ҫѡ��Ĺ��ܣ�" << endl;
		cin >> choice;//�û�ѡ��

		switch (choice)
		{
			//��ʼ�ݽ�����
		case 1:sm.startSpeech();
			break;
			//�鿴�����¼
		case 2:
			sm.showRecod();
			break;
			//��ձ�����¼
		case 3:
			sm.clearRecord();
			break;
			//�˳�ϵͳ
		case 0:
			sm.exitScreen();
			break;

		default:
			system("cls");//����
			break;
		}

	}
	system("pause");
	return 0;
}