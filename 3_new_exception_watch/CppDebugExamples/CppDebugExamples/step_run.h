#pragma once

#include <string>
#include <array>

class EventHandler
{
public:
	template <typename T>
	int OnEvent(T callback, char* data)
	{
		return callback(data);
	}
};

class NetworkEventHandler
{
	void ProcessData(void* p, const std::size_t length) {}
};

struct Dispatcher
{
	int operator()(const std::string& command) {
		std::string received = command;
		return 2 + 2;
	}
};

Dispatcher GetHandler(const std::wstring& type)
{
	return Dispatcher();
}

struct Packet
{
	std::wstring GetType() { return L"TypeAdded"; }
	std::array<char, 100> Buffer{ 'a', 'b', 'c', 'd' };
	char* GetPayload() { return &Buffer[0]; }
};