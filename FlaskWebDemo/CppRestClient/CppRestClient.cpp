// CppRestClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include "TodoItem.h"
#include <ostream>
#include <sstream>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

// sample ref: http://www.codeproject.com/Articles/603810/Using-Casablanca-to-consume-a-REST-API

pplx::task<void> Refresh()
{
	return pplx::create_task([]
	{
		http_client client(U("http://localhost:5555/"));

		uri_builder builder(U("/todo/api/v1.0/tasks"));

		return client.request(methods::GET, builder.to_string());

	}).then([](http_response response)
	{
		if (response.status_code() == status_codes::OK)
		{
			return response.extract_json();
		}

		return pplx::create_task([] { return json::value(); });

	}).then([](json::value jsonValue)
	{
		if (jsonValue.is_null())
			return;

		auto json_array = jsonValue[U("tasks")].as_array();

		TodoItemGenerator generator;
		for (auto iter = json_array.cbegin(); iter != json_array.cend(); ++iter)
		{
			auto item = generator.GetMemberFromJson(*iter);
			item.Display();
		}
	});
}

pplx::task<std::wstring> Post()
{
	return pplx::create_task([]
	{
		json::value jsonToPost;
		jsonToPost[L"title"] = json::value::string(L"Studying the cpprestsdk");
		jsonToPost[L"description"] = json::value::string(L"Build a sample with the cpprestsdk");
		jsonToPost[L"image"] = json::value::string(L"/static/images/demo.png");

		http_client client(L"http://localhost:5555/todo/api/v1.0/tasks");

		uri_builder builder(U("/todo/api/v1.0/tasks"));

		return client.request(methods::POST, builder.to_string(), jsonToPost.serialize(), L"application/json");

	}).then([](http_response response)
	{
		if (response.status_code() == status_codes::OK)
		{
			auto body = response.extract_string();
			std::wcout << L"result: " << body.get().c_str() << std::endl;

			//return std::stoi(body.get().c_str());
			return body.get();
		}

		return utility::string_t(L"Add Failed");
	});
}

int main()
{
	// Open stream to output file.
	pplx::task<void> requestTask = Refresh();

	// Wait for all the outstanding I/O to complete and handle any exceptions
	try
	{
		Post().wait();
		//requestTask.wait();
		//Refresh().then([] {
		//	Post().then([](utility::string_t result) {
		//	});
		//});
	}
	catch (const std::exception &e)
	{
		// Print error.
		std::wostringstream ss;
		ss << e.what() << std::endl;
		std::wcout << ss.str();
	}

	return 0;
}

