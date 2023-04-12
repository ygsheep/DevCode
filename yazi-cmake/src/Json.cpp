#include "yazi.hpp"

using namespace yazi::json;
using std::list;
using std::map;
using std::string;

Json::Json(/* args */) : m_type(Type::json_null)
{
	m_value.m_int = 0;
}
Json::Json(int value) : m_type(Type::json_int)
{
	m_value.m_int = value;
}
Json::Json(double value) : m_type(Type::json_double)
{
	m_value.m_double = value;
}
Json::Json(bool value) : m_type(Type::json_bool)
{
	m_value.m_bool = value;
}
Json::Json(const char* value) : m_type(Type::json_string)
{
	m_value.m_string = new string(value);
}
Json::Json(const string& value) : m_type(Type::json_string)
{
	m_value.m_string = new string(value);
}
Json::Json(const Json& other)
{
	copy(other);
}
Json::Json::~Json()
{
	//clear();
	//std::cout << "析构函数触发" << std::endl;
}

Json::Json(Type type) : m_type(type)
{
	switch (m_type)
	{
	case Type::json_null:
		break;
	case Type::json_bool:
		m_value.m_bool = false;
		break;
	case Type::json_int:
		m_value.m_int = 0;
		break;
	case Type::json_double:
		m_value.m_double = 0;
		break;
	case Type::json_string:
		m_value.m_string = new std::string("");
		break;
	case Type::json_object:
		m_value.m_object = new map<string, Json>();
		break;
	case Type::json_array:
	{
		m_value.m_array = new list<Json>();
		break;
	}
	}
}
Json& Json::operator=(const Json& other)
{
	copy(other);
	return *this;
}
bool Json::operator==(const Json& other)
{
	if (m_type == other.type())
	{
		switch (m_type)
		{
		case Type::json_null:
			return true;
		case Type::json_bool:
			return m_value.m_bool == other.m_value.m_bool;
		case Type::json_int:
			return m_value.m_int == other.m_value.m_int;
		case Type::json_double:
			return m_value.m_double == other.m_value.m_double;
		case Type::json_string:
			return *(m_value.m_string) == *(other.m_value.m_string);
		case Type::json_object:
			return m_value.m_object == other.m_value.m_object;
		case Type::json_array:
			return m_value.m_array == other.m_value.m_array;
		default:
			break;
		}
	}
	return false;
}
bool Json::operator!=(const Json& other)
{
	return !operator==(other);
}
// std::ostream &operator<<(std::ostream &out, const Json &other)
// {
//   out << other.str();
//   return out;
// }

Json::operator int()
{
	if (m_type != Type::json_int)
	{
		throw new std::logic_error("Type error: not int value");
	}
	return m_value.m_int;
}
Json::operator double()
{
	if (m_type != Type::json_double)
	{
		throw new std::logic_error("Type error: not double value");
	}
	return m_value.m_double;
}
Json::operator std::string()
{
	if (m_type != Type::json_string)
	{
		throw new std::logic_error("Type error: not string value");
	}
	return *(m_value.m_string);
}
Json::operator bool()
{
	if (m_type != Type::json_bool)
	{
		throw new std::logic_error("Type error: not bool value");
	}
	return m_value.m_bool;
}

Json& Json::operator[](int index)
{
	return (*(this))[(size_t)index];
}
Json& Json::operator[](size_t index)
{
	if (index < 0)
	{
		throw std::logic_error("function Json::operator [int] index less than 0");
	}
	// if (m_type != Type::json_array)
	// {
	//   clear();
	//   m_type = Type::json_array;
	//   m_value.m_array = new std::list<Json>();
	// }
	// int size = (m_value.m_array)->size();
	// if (index >= 0 && index < size)
	// {
	//   auto it = (m_value.m_array)->begin();
	//   for (int i = 0; i < index; i++)
	//   {
	//     it++;
	//   }
	//   return *it;
	// }
	// if (index >= size)
	// {
	//   for (int i = size; i <= index; i++)
	//   {
	//     (m_value.m_array)->push_back(Json());
	//   }
	// }
	// return (m_value.m_array)->back();
	if (m_type != Type::json_array)
	{
		clear();
		// 丢失原始数据
		m_type = Type::json_array;
		m_value.m_array = new list<Json>();
	}
	size_t size = m_value.m_array->size();
	// std::cout << "the size of Array (old):" << size << std::endl;
	if (index >= 0 && index <= size)
	{
		auto it = m_value.m_array->begin();
		for (size_t i = 0; i < index; i++)
		{
			it++;
		}
		return *it;
	}
	if (index >= size)
	{
		(m_value.m_array)->resize(index + 1, Json());
	}
	return (m_value.m_array)->back();
}
Json& Json::operator[](const char* key)
{
	string name(key);
	return (*(this))[name];
}
Json& Json::operator[](const string& key)
{
	if (m_type != Type::json_object)
	{
		m_type = Type::json_object;
		m_value.m_object = new map<string, Json>();
	}

	return (*(m_value.m_object))[key];
}

bool Json::empty()
{
	switch (m_type)
	{
	case yazi::json::Json::Type::json_null:
		return true;
	case yazi::json::Json::Type::json_object:
		return (m_value.m_object)->empty();
	case yazi::json::Json::Type::json_array:
		return (m_value.m_array)->empty();
	default:
		break;
	}
	return false;
}

bool Json::has(size_t index)
{
	if (isArray())
	{
		size_t size = (m_value.m_array)->size();
		return (index >= 0) && (index < size);
	}
	return false;
}
bool Json::has(const string& key)
{
	if (isArray())
	{
		return (m_value.m_object)->find(key) != (m_value.m_object)->end();
	}
	return false;
}
bool Json::has(const char* key)
{
	string name(key);
	return has(name);
}

void Json::remove(size_t index)
{
	size_t pos = (m_value.m_array)->size();
	if (isArray() && index < pos && index >= 0)
	{
		auto it = (m_value.m_array)->begin();
		for (size_t i = 0; i < index; i++)
		{
			it++;
		}
		it->clear();
		m_value.m_array->erase(it);
	}
	return;
}
void Json::remove(const char* key)
{
	string name(key);
	remove(name);
}
void Json::remove(const std::string& key)
{
	if (isObject())
	{
		auto it = (m_value.m_object)->find(key);
		if (it != m_value.m_object->end())
		{
			it->second.clear();
			(m_value.m_object)->erase(it);
		}
	}
	return;
}

string Json::str() const
{
	std::stringstream ss;

	switch (m_type)
	{
	case Type::json_null:
		ss << "null";
		break;
	case Type::json_bool:
	{
		string _ = m_value.m_bool ? "true" : "false";
		ss << _;
		break;
	}
	case Type::json_int:
		ss << std::to_string(m_value.m_int);
		break;
	case Type::json_double:
		ss << std::to_string(m_value.m_double);
		break;
	case Type::json_string:
		ss << '\"' << *(m_value.m_string) << '\"';
		break;
	case Type::json_object:
	{
		ss << '{';
		for (auto it = (m_value.m_object)->begin(); it != (m_value.m_object)->end(); it++)
		{
			if (it != (m_value.m_object)->begin())
			{
				ss << ',';
			}
			ss << '\"' << it->first << '\"' << ':' << it->second.str();
		}
		ss << '}';
		break;
	}
	case Type::json_array:
	{
		ss << '[';
		for (auto& it : *(m_value.m_array))
		{
			ss << it.str();
			ss << ",";
		}

		ss << ']';
		break;
	}
	default:
		break;
	}

	return ss.str();
}

void Json::append(const Json& other)
{
	if (m_type != Type::json_array)
	{
		m_type = Type::json_array;
		m_value.m_array = new list<Json>();
	}
	(m_value.m_array)->push_back(other);
}

Json::Type Json::type() const
{
	return m_type;
}

bool Json::isNull() const
{
	return m_type == Type::json_null;
}
bool Json::isBool() const
{
	return m_type == Type::json_bool;
}
bool Json::isInt() const
{
	return m_type == Type::json_int;
}
bool Json::isDouble() const
{
	return m_type == Type::json_double;
}
bool Json::isString() const
{
	return m_type == Type::json_string;
}
bool Json::isArray() const
{
	return m_type == Type::json_array;
}
bool Json::isObject() const
{
	return m_type == Type::json_object;
}

bool Json::asBool() const
{
	if (isBool())
	{
		return m_value.m_bool;
	}
	throw std::logic_error("function Json::asBool value type error");
}
int Json::asInt() const
{
	if (isInt())
	{
		return m_value.m_int;
	}
	throw std::logic_error("function Json::asInt value type error");
}
double Json::asDouble() const
{
	if (isDouble())
	{
		return m_value.m_double;
	}
	throw std::logic_error("function Json::asDouble value type error");
}
string Json::asString() const
{
	if (isString())
	{
		return *(m_value.m_string);
	}
	throw std::logic_error("function Json::asString value type error");
}

size_t Json::size() const
{
	switch (m_type)
	{
	case Type::json_object:
		return m_value.m_object->size();
	case Type::json_array:
		return m_value.m_array->size();
	default:
		break;
	}
	throw std::logic_error("function size() value type error");
}

void Json::parser(const std::string& data, bool isFile)
{
	Parser par;
	par.load(data);
	if (isFile)
	{
		*this = par.parser_of();
	}
	else
	{
		*this = par.parser();
	}
}

void Json::copy(const Json& other)
{
	clear();
	if (other.m_type == Json::Type::json_array) {
		for (auto& it : *(other.m_value.m_array))
		{
			append(it);
		}
		return;
	}
	this->m_type = other.m_type;
	this->m_value = other.m_value;
}
void Json::clear()
{
	switch (m_type)
	{
	case Type::json_null:
	case Type::json_bool:
	case Type::json_int:
	case Type::json_double:
		break;
	case Type::json_string:
	{
		delete m_value.m_string;
		break;
	}
	case Type::json_object:
	{
		for (auto& it : *(m_value.m_object))
		{
			it.second.clear();
		}
		delete m_value.m_object;
		break;
	}
	case Type::json_array:
	{
		// for (auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); it++)
		// {
		//   it->clear();
		// }
		for (auto& it : *(m_value.m_array))
		{
			it.clear();
		}
		delete m_value.m_array;
		break;
	}
	}
	m_type = Type::json_null;
}
