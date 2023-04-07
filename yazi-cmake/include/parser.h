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
			/// @brief ���ݳ�ʼ��
			/// @param data
			void load(const string& data);

			Json parser();
			Json parser_of();

			/// @brief �����ַ��Ŀո�
			void skip_white_space();
			/// @brief  ��ȡ��һ���ַ�
			/// @return ��Ϊ�յ��ַ�
			char get_next_token();

		private:
			//�ַ���
			string m_data;
			//��ǰ�±�
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
