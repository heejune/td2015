#pragma once

#include <string>
#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>


// http://www.codeproject.com/Articles/603810/Using-Casablanca-to-consume-a-REST-API

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace web::json;
using namespace concurrency::streams;       // Asynchronous streams


class TodoItem
{
public:
	TodoItem();
	~TodoItem();

	int Id;
	std::wstring Description;
	std::wstring Title;
	std::wstring Image;
	std::wstring Uri;
	bool Done;

	void Display()
	{
		std::wcout << L"Id: " << Id << L", "
			<< L"Title: " << Title << L", "
			<< L"Description: " << Description << L", "
			<< L"Image: " << Image << L", "
			<< L"Done: " << Done << std::endl;
	}
};

enum FieldValue { Id, Title, Description, Image, Done, Uri };

#include <map>

class TodoItemGenerator
{
	std::map<std::wstring, FieldValue> fieldMap;
	TodoItem item;

public:
	TodoItemGenerator()
	{
		fieldMap[L"id"] = FieldValue::Id;
		fieldMap[L"title"] = FieldValue::Title;
		fieldMap[L"description"] = FieldValue::Description;
		fieldMap[L"image"] = FieldValue::Image;
		fieldMap[L"done"] = FieldValue::Done;
		fieldMap[L"uri"] = FieldValue::Uri;
	}

	void SetField(std::wstring name, json::value value)
	{
		switch (fieldMap.at(name))
		{
		case FieldValue::Id:
			item.Id = value.as_integer();
			break;

		case FieldValue::Title:
			item.Title = value.as_string();
			break;

		case FieldValue::Description:
			item.Description = value.as_string();
			break;

		case FieldValue::Image:
			item.Image = value.as_string();
			break;

		case FieldValue::Done:
			item.Done = value.as_bool();
			break;

		case FieldValue::Uri:
			item.Uri = value.as_string();
			break;
		}
	}

	TodoItem GetMemberFromJson(json::value jsonValue)
	{
		//for (auto iterInner = jsonValue.cbegin(); iterInner != jsonValue.cend(); ++iterInner)
		//if (jsonValue.is_null())

		for (auto iter = jsonValue.as_object().cbegin(); iter != jsonValue.as_object().cend(); ++iter)
		{
			auto propertyName = iter->first;
			const json::value &propertyValue = iter->second;

			SetField(propertyName, propertyValue);
		}

		return item;
	}
};