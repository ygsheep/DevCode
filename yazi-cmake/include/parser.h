#pragma once

#include "yazi.hpp"
namespace yazi {
	namespace json {
		class Parser
		{
		public:
			Parser();
			Parser(const string& data);
			~Parser();
			/// @brief 数据初始化
			/// @param data
			void load(const string& data);

			Json parser();
			Json parser_of();

			/// @brief 跳过字符的空格
			void skip_white_space();
			/// @brief  获取下一个字符
			/// @return 不为空的字符
			char get_next_token();

		private:
			//字符串
			string m_data;
			//当前下标
			size_t m_idx;

			Json parser_null();
			Json parser_bool();
			Json parser_number();
			string parser_string();
			Json parser_array();
			Json parser_object();
		};
	}
}
