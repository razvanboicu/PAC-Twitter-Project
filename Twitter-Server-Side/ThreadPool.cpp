#include "ThreadPool.h"
#include <iostream>
#include <array>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "../Logger/Logger.h"

#pragma comment(lib, "Ws2_32.lib")	//  links to Ws2_32.lib
#include "Users.h"
#include "Processor.h"

ThreadPool::ThreadPool():
	m_done(false)
{
	auto NumberOfThreads = std::thread::hardware_concurrency();
	for (unsigned int i = 0; i < NumberOfThreads; i++)
		m_threads.push_back(std::thread(&ThreadPool::Worker_Thread,this));

}

ThreadPool::~ThreadPool()
{
	m_done = true;

	m_workConditionVariable.notify_all();
	for (auto& thread : m_threads)
		if (thread.joinable())
			thread.join();

}

void ThreadPool::AddWork(int Client, std::shared_ptr<Processor> p)
{
	std::lock_guard<std::mutex> lck(m_workMutex); //will unlock after end of scope
	m_clients.push(std::pair(Client,p));
	m_workConditionVariable.notify_one();
}

void ThreadPool::Worker_Thread()
{
	int client;
	std::shared_ptr<Processor> resource;
	while (!m_done)
	{
		{
			std::unique_lock<std::mutex> lck(m_workMutex);
			m_workConditionVariable.wait(lck, [this] { return !m_clients.empty() || m_done; });
			if (m_clients.empty())
				return;
			client = m_clients.front().first;
			resource = m_clients.front().second;
			m_clients.pop();
		}
		HandleClient(client, resource);
	}
}

void ThreadPool::HandleClient(int client,std::shared_ptr<Processor> r)
{
	std::ofstream out("logs.txt", std::ios::app);
	Logger logger(out);

	std::string request, response;
	std::ostringstream buffer;
	std::stringstream stream;
	std::array<char, 512> receiveBuffer;
	int revieved;
	while (true)
	{
		TcpSocket::RecieveUsingHandle(client, receiveBuffer.data(), receiveBuffer.size(), revieved);

		logger.Log(Logger::Level::Info, "Received:");
		std::cout << "Received:";

		for (int i = 0; i < revieved; i++)
			buffer << receiveBuffer[i];
		request = buffer.str();
		buffer.str(std::string());
		logger.Log(Logger::Level::Info, request);
		std::cout << request;
		logger.Log(Logger::Level::Info, "\n");
		std::cout << std::endl;
		response=r->ProcessRequest(request);

		logger.Log(Logger::Level::Info, "Sent: ", response, "\n");
		std::cout << "Sent:" << response << '\n';
		TcpSocket::SendUsingHandle(client, response.c_str(), response.size());
		request = "STANDBY", response = "STANDBY";
	}
}
