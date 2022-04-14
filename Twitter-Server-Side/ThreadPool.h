#pragma once
#include <thread> 
#include <queue> 
#include <mutex> 
#include <condition_variable> 
#include "Processor.h"
#include "../Network/TcpSocket.h"

class ThreadPool{
public:
	ThreadPool();
	~ThreadPool();
	void AddWork(int Client, std::shared_ptr<Processor>);

private:
	std::atomic_bool m_done;
	std::condition_variable_any m_workConditionVariable;
	std::vector<std::thread> m_threads;
	std::mutex m_workMutex;
	std::queue<std::pair<int, std::shared_ptr<Processor>>> m_clients;

private:
	void Worker_Thread();
	void HandleClient(int client, std::shared_ptr<Processor> r);
};

