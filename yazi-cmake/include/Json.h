#include "yazi.hpp"

#ifndef JSON
#define JSON
namespace yazi
{
	using std::list;
	using std::map;
	using std::string;

	namespace json
	{
		class Json
		{
		public:
			// friend std::ostream &operator<<(std::ostream &out, const Json &other);
			enum class Type;

		private:
			union Value
			{
				bool m_bool;
				int m_int;
				double m_double;
				string* m_string;
				list<Json>* m_array;
				map<string, Json>* m_object;
			};
			Type m_type;
			Value m_value;

			void copy(const Json& other);

		public:
			enum class Type
			{
				json_null = 0,
				json_bool,
				json_int,
				json_double,
				json_string,
				json_object,
				json_array
			};

			Json();
			Json(int value);
			Json(bool value);
			Json(double value);
			Json(const char* value);
			Json(const string& value);
			Json(Type type);
			Json(const Json& other);

			/// @brief copy constructor
			/// @param other
			/// @return *this
			Json& operator=(const Json& other);
			bool operator==(const Json& other);
			bool operator!=(const Json& other);

			operator int();
			operator double();
			operator std::string();
			operator bool();

			Json& operator[](int index);
			Json& operator[](size_t index);
			Json& operator[](const char* key);
			Json& operator[](const string& key);
			/// @brief 在数组的某位添加数据
			/// @param other
			void append(const Json& other);

			/// @brief 内容是否为空
			/// @param  nullptr
			/// @return bool
			bool empty();

			bool has(size_t index);
			bool has(const string& key);
			bool has(const char* key);

			void remove(size_t index);
			void remove(const char* key);
			void remove(const std::string& key);

			/// @brief
			/// @return 返回json的类型
			Type type() const;
			bool isNull() const;
			bool isBool() const;
			bool isInt() const;
			bool isDouble() const;
			bool isString() const;
			bool isArray() const;
			bool isObject() const;

			bool asBool() const;
			int asInt() const;
			double asDouble() const;
			string asString() const;

			typedef list<Json>::iterator iterator;
			iterator begin()
			{
				return (m_value.m_array)->begin();
			}
			iterator end()
			{
				return (m_value.m_array)->end();
			}

			size_t size() const;
			void clear();
			void parser(const std::string& data, bool isFile = false);
			string str() const;

			~Json();
		};
	}
}
#endif // json
