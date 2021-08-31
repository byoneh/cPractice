#pragma once
#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<map>
#include"speaker.h"


//创建演讲管理类
class SpeechManager
{
public:
	//构造函数
	SpeechManager();
	//展示菜单
	void show_menu();
	//退出系统
	void exitScreen();

	//初始化属性
	void initSpeeh();
	
	//创建演讲人员
	void creatSpeaker();

	//开始比赛  -比赛流程控制
	void startSpeech();

	//抽签
	void speechDraw();

	//比赛
	void speechContest();

	//显示晋级结果
	void showScore();

	//保存比赛结果
	void saveRecord();

	//查看往届记录
	void loadRecord();

	//显示往届记录
	void showRecod();

	//清空记录
	void clearRecord();


	//析构函数
	~SpeechManager();
	//第一轮参加选手 12名
	vector<int> v1;
	//第二轮参加选手 6名
	vector <int> v2;
	//最终获胜的选手 3名
	vector<int> vVictory;
	//存放编号和具体选手
	map<int, Speaker> m_speaker;
	//比赛轮数
	int m_index;
	//文件为空的标志
	bool fileIsEmpty;

	//往届记录
	map<int, vector<string>> m_record;

};

