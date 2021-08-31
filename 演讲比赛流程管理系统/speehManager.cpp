#include "speehManager.h"
#include<algorithm>
#include<deque>
#include<numeric>


SpeechManager::SpeechManager()
{
	//��ʼ������
	this->initSpeeh();
	//����ѡ��
	this->creatSpeaker();
}

void SpeechManager::show_menu()
{
	cout << "*******************************" << endl;
	cout << "*********��ӭ�μ��ݽ�����******"<<endl;
	cout << "*********1.��ʼ�ݽ�************" << endl;
	cout << "*********2.�鿴�����¼********" << endl;
	cout << "*********3.��ձ�����¼********" << endl;
	cout << "*********0.�˳�����ϵͳ********" << endl;
	cout << "*******************************" << endl;
	cout << endl;
}

void SpeechManager::exitScreen()
{
	cout << "��ӭ�´�ʹ�á�" << endl;
	system("pause");
	exit(0);

}

void SpeechManager::initSpeeh()
{
	//��֤����Ϊ��
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_speaker.clear();
	//��ʼ����������
	this->m_index = 1;
}

void SpeechManager::creatSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0;i < 12;i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];
		Speaker sp;
		sp.m_name = name;
		for (int i = 0;i < 2;i++)
		{
			sp.m_score[i] = 0;
		}
		//12��ѡ�ֱ��
		this->v1.push_back(10001 + i);
		//ѡ�ֱ���Լ���Ӧ��ѡ�ִ�ŵ�map������
		this->m_speaker.insert(make_pair(10001 + i, sp));
	}

}

void SpeechManager::startSpeech()
{
	//һ ����һ�ֱ���
	
	//1. ��ǩ
	speechDraw();
	//2. ����
	speechContest();
	//3. ��ʾ�������
	showScore();

	//�� ���ڶ��ֱ���
	//1. ��ǩ
	//2. ����
	//3. ��ʾ�������
	//�� ����ʾ���ս��
	//�� ���������

}

void SpeechManager::speechDraw()
{
	cout << "��" << this->m_index << "�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;
	if (this->m_index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin();it != v1.end();it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin();it != v2.end();it++)
		{
			cout << *it << endl;
		}
		cout << endl;
	}
	cout << "-------------------" << endl;
	system("pause");
	cout << endl;

}

void SpeechManager::speechContest()
{
	cout << "-----------��" << this->m_index << "�ֱ�����ʽ��ʼ��--------" << endl;
	//��ʱ���������������ѡ�ֱ��,�Ӵ�С������
	multimap<double, int, greater<int>>groupScore;

	//��¼��Ա��Ŀ6��Ϊһ��
	int num = 0;
	//������Ա������
	vector<int>vTemp;
	if (this->m_index == 1)
	{
		vTemp = v1;
	}
	else
	{
		vTemp = v2;
	}
	//�������в���ѡ�ֶ�����
	for (vector<int>::iterator it = vTemp.begin();it != vTemp.end();it++)
	{
		num++;
		deque<double>d;
		//��ί���
		for (int i = 0;i < 10;i++)
		{
			double score = (rand() % 401 + 600) / 10.0;// 600 ~ 1000 /10.0
			d.push_back(score);
		}
		//����
		sort(d.begin(), d.end(), greater<double>());
		//ȥ��һ����߷֣�ȥ��һ����ͷ�
		d.pop_front();
		d.pop_back();
		//����ƽ����
		double sum = accumulate(d.begin(), d.end(), 0.0);
		double avg = sum / (double)d.size();
		this->m_speaker[*it].m_score[this->m_index - 1] = avg;

		//6��һ�� ������ʱ��������
		groupScore.insert(make_pair(avg, *it));
		if ( num % 6 == 0)
		{
			cout << "��" << num / 6 << "С���������" << endl;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin();it != groupScore.end();it++)
			{
				cout << "���:" << it->second << " " << "������" << m_speaker[it->second].m_name << "�÷֣�" << m_speaker[it->second].m_score[this->m_index - 1] << endl;
			}
			int count = 0;
			//ȡǰ����
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin();it != groupScore.end() && count < 3;it++, count++)
			{
				if (this->m_index == 1)
				{
					v2.push_back(it->second);
				}
				else
				{
					vVictory.push_back(it->second);
				}
			}
			groupScore.clear();
			cout << endl;

		}
		


	}
	cout << "------------��" << this->m_index << "�ֱ������------------" << endl;
	system("pause");

}

void SpeechManager::showScore()
{
	cout << "��" << this->m_index << "�ֱ���������£�" << endl;
	vector<int>v;
	if (this->m_index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;

	}
	for (vector<int>::iterator it = v.begin();it != v.end();it++)
	{
		cout << "ѡ�ֱ�ţ�" << *it << " " << "ѡ��������" << this->m_speaker[*it].m_name << " ѡ�ֵ÷֣�" << this->m_speaker[*it].m_score[this->m_index-1] << endl;

	}
	cout << endl;
	system("pause");
	//system("cls");
	this->show_menu();
}



SpeechManager::~SpeechManager()
{
}
