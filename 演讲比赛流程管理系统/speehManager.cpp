#include "speehManager.h"
#include<algorithm>
#include<deque>
#include<numeric>
#include<fstream>
#include<string>


SpeechManager::SpeechManager()
{
	//��ʼ������
	this->initSpeeh();
	//����ѡ��
	this->creatSpeaker();
	//��ȡ�����¼
	this->loadRecord();
	
	//��ʼ����¼����
	this->m_record.clear();
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
	this->m_index++;
	//1. ��ǩ
	speechDraw();
	//2. ����
	speechContest();
	//3. ��ʾ�������
	showScore();
	//�� ����ʾ���ս��
	 
	//�� ���������
	saveRecord();

	//���ñ���
	//��ʼ������
	this->initSpeeh();

	//����ѡ��
	this->creatSpeaker();

	//��ȡ�����¼
	this->loadRecord();

	cout << "���������ϣ�" << endl;
	system("pause");
	system("cls");
	//this->show_menu();

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
	//this->show_menu();
}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speaker.csv", ios::out | ios::app);
	for (vector<int>::iterator it = vVictory.begin();it != vVictory.end();it++)
	{
		ofs << "ѡ�ֱ�ţ�" << "," << *it << "," << "ѡ��������" << "," << this->m_speaker[*it].m_name << "," << "ѡ�ַ�����" << "," << this->m_speaker[*it].m_score[1] << ",";
		ofs << endl;
	}
	ofs << endl;
	ofs.close();
	cout << "��¼�ɹ�����" << endl;
	this->fileIsEmpty = false;
}

void SpeechManager::loadRecord()
{
	ifstream ifs;
	ifs.open("speaker.csv", ios::in);
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "�ļ�������" << endl;
		ifs.close();
		return;

	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->fileIsEmpty = true;
		cout << "�ļ�Ϊ��" << endl;
		ifs.close();
		return;
	}
	//�ļ���Ϊ��
	this->fileIsEmpty = false;

	//��ȡ�ĵ����ַ��Ż�
	ifs.putback(ch);
	string data;
	int index = 0;
	int count = 0;
	vector<string>v;
	while (ifs >> data)
	{

		
		int pos = -1;
		int start = 0;
		
		pos = data.find("\n", start);
		string temp = data.substr(start, pos - start);
		v.push_back(temp);
	
		start = pos + 1;
		this->m_record.insert(make_pair(count, v));
		count++;
		
		/*for (int i = 0;i < this->m_record.size();i++)
		{
			cout << m_record[1][i]<<endl;
		}*/
		////getline(ifs, data);
		/*for (int i = 0; i < data.size();i++)
		{
			if (data.find(data.begin(),data.end(),"") == '\n')
			{
				cout << endl;
			}
		}*/
		
			
			//}
			//
			//vector<string>v;
			///*int pos = -1;
			//int start = 0;*/
			//int flag = 1;
			//while (true)
			//{
			///*	if (ifs.peek() == EOF)
			//	{
			//		flag = 0;
			//	}*/
			//	pos = data.find("\n", start);
			//	string temp = data.substr(start, pos - start);//�ҵ��ͷָ� ����1 ��ʼλ�� ������ �ָ��
			//	v.push_back(temp);
			//	
			//	start = pos + 1;
		

			//this->m_record.insert(make_pair(index, v));
			//index++;

		
		
	}
	ifs.close();
	
}

void SpeechManager::showRecod()
{
	if (this->fileIsEmpty)
	{
		cout << "�ļ������ڣ����¼Ϊ��!" << endl;
	}
	else
	{
		for (int i = 0; i < m_record.size();i++)
		{
			if (i % 3 == 0)
			{
				cout << "��" << i / 3 + 1 << "�������" << endl;

			}
			cout << this->m_record[i][i] << endl;

		}
	}
	
	/*for (map<int, vector<string>>::iterator it = this->m_record.begin();it != m_record.end();it++)
	{
		cout << "�ھ�" << it->first;
	}*/
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord()
{
	cout << "ȷ�������" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		//trunct
		ofstream ofs("speaker.csv", ios::trunc);
		ofs.close();
		//��ʼ������
		this->initSpeeh();
		//����ѡ��
		this->creatSpeaker();
		//��ȡ�����¼
		this->loadRecord();
		cout << "��ճɹ���" << endl;

	}
	system("pause");
	system("cls");
	
}



SpeechManager::~SpeechManager()
{
}
