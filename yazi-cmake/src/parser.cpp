#include "parser.h"

using namespace yazi::json;
using std::string;
using std::logic_error;

Parser::Parser() :m_idx(0)
{
}
Parser::Parser(const string& data)
{
	load(data);
}

Parser::~Parser()
{
}

void Parser::load(const string& data)
{
	m_data = data;
	m_idx = 0;
}

Json yazi::json::Parser::parser()
{
	char _ = get_next_token();
	switch (_)
	{
	case 'n':
		return parser_null();
	case 't':
	case 'f':
		return parser_bool();
	case '-':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return parser_number();
	case '\"':
		return Json(parser_string());
	case '[':
		return parser_array();
	case '{':
		return parser_object();
	case ',':
	case ':':
		return parser();
	default:
		break;
	}
	throw new logic_error("unexpected char");
}

Json yazi::json::Parser::parser_of()
{
	Json *arr = new Json(Json::Type::json_array);
	size_t pos;
	while (true)
	{
		pos = m_idx;
		int _ch = m_data.find_first_of(":", pos);
		m_idx = _ch + 1;
		char ch = get_next_token();
		if (_ch <= 0) {
			break;
		}
		string s;
		switch (ch)
		{
		case '[':
			s = "]";
			break;
		case '{':
			s = "}";
			break;
		default:
			s = ",";
			break;
		}
		_ch = m_data.find_first_of(s, m_idx);
		if (!_ch) {
			break;
		}
		m_idx = _ch + 1;
		string ss = m_data.substr(pos, m_idx - pos + 1);
		ss = ss[0] == '{' ? ss : '{' + ss;
		string temp = m_data;
		load(ss);
		arr->append(parser());
		load(temp);
		m_idx = _ch + 1;
	}

	return arr;
}

Json Parser::parser_null() {
	m_idx--;
	if (m_data.compare(m_idx, 4, "null") == 0) {
		m_idx += 4;
		return Json();
	}
	throw new std::logic_error("parser null error");
}
Json Parser::parser_bool()
{
	m_idx--;
	if (!m_data.compare(m_idx, 4, "true")) {
		m_idx += 4;
		return Json(true);
	}
	else if (!m_data.compare(m_idx, 5, "false"))
	{
		m_idx += 5;
		return Json(false);
	}
	throw new std::logic_error("parser bool error");
}
Json Parser::parser_number() {
	int pos = --m_idx;
	if (m_data[m_idx] == '-') {
		m_idx++;
	}
	if (m_data[m_idx] >= '0' && m_data[m_idx] <= '9') {
		while (m_data[m_idx] >= '0' && m_data[m_idx] <= '9')
		{
			m_idx++;
		}
	}
	else {
		throw new logic_error("parser number error");
	}

	if (m_data[m_idx] != '.') {
		string _s = m_data.substr(pos, m_idx - pos);
		int _ = std::atoi(_s.c_str());
		return Json(_);
	}
	m_idx++;
	if (m_data[m_idx] < '0' || m_data[m_idx] > '9') {
		throw new logic_error("parser number error");
	}
	while (m_data[m_idx] >= '0' && m_data[m_idx] <= '9')
	{
		m_idx++;
	}
	string _s = m_data.substr(pos, m_idx - pos);
	double _ = std::atof(_s.c_str());
	return Json(_);
}
string Parser::parser_string() {
	skip_white_space();
	size_t pos_lenght = m_data.find_first_of('\"', m_idx) - m_idx;
	string key = m_data.substr(m_idx, pos_lenght);
	m_idx += pos_lenght + 1;
	return key;
}
Json Parser::parser_array() {
	m_idx--;
	Json arr(Json::Type::json_array);
	while (m_data[m_idx++] != ']')
	{
		arr.append(parser());
	}

	return arr;
}
Json Parser::parser_object() {
	Json object(Json::Type::json_object);
	char _ = get_next_token();
	if (_ != '\"') {
		throw new logic_error("parser object error");
	}
	string key = parser_string();
	Json value = parser();

	object[key] = value;

	return object;
}

void Parser::skip_white_space() {
	/// @brief 去除 空白 换行 回车 制表符
	while (m_data[m_idx] == ' ' || m_data[m_idx] == '\t' || m_data[m_idx] == '\n' || m_data[m_idx] == '\r')
	{
		m_idx++;
	}
}
char Parser::get_next_token() {
	skip_white_space();
	return m_data[m_idx++];
}