#pragma once
#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<map>
#include"speaker.h"


//�����ݽ�������
class SpeechManager
{
public:
	//���캯��
	SpeechManager();
	//չʾ�˵�
	void show_menu();
	//�˳�ϵͳ
	void exitScreen();

	//��ʼ������
	void initSpeeh();
	
	//�����ݽ���Ա
	void creatSpeaker();

	//��ʼ����  -�������̿���
	void startSpeech();

	//��ǩ
	void speechDraw();

	//����
	void speechContest();

	//��ʾ�������
	void showScore();


	//��������
	~SpeechManager();
	//��һ�ֲμ�ѡ�� 12��
	vector<int> v1;
	//�ڶ��ֲμ�ѡ�� 6��
	vector <int> v2;
	//���ջ�ʤ��ѡ�� 3��
	vector<int> vVictory;
	//��ű�ź;���ѡ��
	map<int, Speaker> m_speaker;
	int m_index;


};

