#pragma once
/*
ʵ�����ӳع���ģ��
*/
#include<string>
# include<queue>
#include<mutex>
#include<atomic>
#include<iostream>
#include<thread>
#include<memory>
#include<functional>
#include"Connection.h"
#include<condition_variable>
using namespace std;
class ConnectionPool
{
public:
	//��ȡ���ӳض���ʵ��
	static ConnectionPool* getConnectionPool();
	//���ⲿ�ṩ�ӿڣ������ӳ��л�ȡһ�����õĿ�������
	 shared_ptr<Connection>getConnection();
private:
	//����#1 ���캯��˽�л�
	ConnectionPool();

	//�������ļ��м���������
	bool loadConfigFile();

	//�����ڶ������߳��У�ר�Ÿ�������������
	void produceConnectionTask();

	//ɨ�賬��maxIdleTimeʱ��Ŀ������ӣ����ж��ڶ�������ӵĻ���
	void scannerConnectionTask();

	string _ip; //msql��ip��ַ
	unsigned short _port;//mysql�Ķ˿ں� 3306
	string _username;//mysql��¼�û���
	string _password;//mysql��¼����
	string _dbname;//�������ݿ������
	int _initSize;//���ӳصĳ�ʼ������
	int _maxSize;//���ӳص����������
	int _maxIdleTime;//���ӳ�������ʱ��
	int _connectionTimeout;//���ӳػ�ȡ���ӵĳ�ʱʱ��



	queue<Connection*>_connectionQue;//�洢mysql���ӵĶ���
	mutex _queueMutex;//ά�����Ӷ��е��̰߳�ȫ������
	atomic_int _connectionCnt;//��¼������������connection���ӵ�������
	condition_variable cv;//���������������������������̺߳����������̵߳�ͨ��
};