#include "speehManager.h"
#include<algorithm>
#include<deque>
#include<numeric>


SpeechManager::SpeechManager()
{
	//初始化属性
	this->initSpeeh();
	//创建选手
	this->creatSpeaker();
}

void SpeechManager::show_menu()
{
	cout << "*******************************" << endl;
	cout << "*********欢迎参加演讲比赛******"<<endl;
	cout << "*********1.开始演讲************" << endl;
	cout << "*********2.查看往届记录********" << endl;
	cout << "*********3.清空比赛记录********" << endl;
	cout << "*********0.退出比赛系统********" << endl;
	cout << "*******************************" << endl;
	cout << endl;
}

void SpeechManager::exitScreen()
{
	cout << "欢迎下次使用。" << endl;
	system("pause");
	exit(0);

}

void SpeechManager::initSpeeh()
{
	//保证容器为空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_speaker.clear();
	//初始化比赛轮数
	this->m_index = 1;
}

void SpeechManager::creatSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0;i < 12;i++)
	{
		string name = "选手";
		name += nameSeed[i];
		Speaker sp;
		sp.m_name = name;
		for (int i = 0;i < 2;i++)
		{
			sp.m_score[i] = 0;
		}
		//12名选手编号
		this->v1.push_back(10001 + i);
		//选手编号以及对应的选手存放到map容器中
		this->m_speaker.insert(make_pair(10001 + i, sp));
	}

}

void SpeechManager::startSpeech()
{
	//一 。第一轮比赛
	
	//1. 抽签
	speechDraw();
	//2. 比赛
	speechContest();
	//3. 显示晋级结果
	showScore();

	//二 。第二轮比赛
	//1. 抽签
	//2. 比赛
	//3. 显示晋级结果
	//三 。显示最终结果
	//四 。保存分数

}

void SpeechManager::speechDraw()
{
	cout << "第" << this->m_index << "轮比赛选手正在抽签" << endl;
	cout << "------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
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
	cout << "-----------第" << this->m_index << "轮比赛正式开始：--------" << endl;
	//临时容器，保存分数，选手编号,从大到小排排列
	multimap<double, int, greater<int>>groupScore;

	//记录人员数目6个为一组
	int num = 0;
	//比赛人员的容器
	vector<int>vTemp;
	if (this->m_index == 1)
	{
		vTemp = v1;
	}
	else
	{
		vTemp = v2;
	}
	//遍历所有参赛选手对其打分
	for (vector<int>::iterator it = vTemp.begin();it != vTemp.end();it++)
	{
		num++;
		deque<double>d;
		//评委打分
		for (int i = 0;i < 10;i++)
		{
			double score = (rand() % 401 + 600) / 10.0;// 600 ~ 1000 /10.0
			d.push_back(score);
		}
		//排序
		sort(d.begin(), d.end(), greater<double>());
		//去掉一个最高分，去掉一个最低分
		d.pop_front();
		d.pop_back();
		//计算平均分
		double sum = accumulate(d.begin(), d.end(), 0.0);
		double avg = sum / (double)d.size();
		this->m_speaker[*it].m_score[this->m_index - 1] = avg;

		//6人一组 放在临时容器保存
		groupScore.insert(make_pair(avg, *it));
		if ( num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次" << endl;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin();it != groupScore.end();it++)
			{
				cout << "编号:" << it->second << " " << "姓名：" << m_speaker[it->second].m_name << "得分：" << m_speaker[it->second].m_score[this->m_index - 1] << endl;
			}
			int count = 0;
			//取前三名
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
	cout << "------------第" << this->m_index << "轮比赛完毕------------" << endl;
	system("pause");

}

void SpeechManager::showScore()
{
	cout << "第" << this->m_index << "轮比赛结果如下：" << endl;
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
		cout << "选手编号：" << *it << " " << "选手姓名：" << this->m_speaker[*it].m_name << " 选手得分：" << this->m_speaker[*it].m_score[this->m_index-1] << endl;

	}
	cout << endl;
	system("pause");
	//system("cls");
	this->show_menu();
}



SpeechManager::~SpeechManager()
{
}
