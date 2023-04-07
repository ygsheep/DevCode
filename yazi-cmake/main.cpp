#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/timeb.h>
#include <vector>
using namespace std;

#include "include/Json.h"

using namespace yazi::json;

int main() {
  /*
  Json obj;
  obj["name"] = "tom";
  obj[5] = "tom";
  ��ʧ���� object -> array
  */
  /*
          Json arr;
          ���� x
          arr[0] = Josn("");
          ��ȷ ��
          Json _ = Josn("");
          arr[0] = _;
  */
  ifstream fin("assets/test.json");
  stringstream ss;
  ss << fin.rdbuf();
  const string &data = ss.str();
  cout << data << endl;
  Json json;

	json[0] = "jack";

  cout << json.str() << endl;

  // json.parser("\{\"name\":\"tom\"\}");

  // string line;

  // const int max = 10000;
  // for (size_t i = 0; i < max; i++)
  //{
  //	ifstream fin("test.json");
  //	while (std::getline(fin, line))
  //	{
  //		if (line.size() <= 1) {
  //			continue;
  //		}
  //		line = "{" + line;
  //		json.parser(line);
  //		//cout << json.str() << endl;
  //	}
  //	//cout << json.str() << endl;
  //	json.clear();
  // }

  // Json json;
  // Json j1 = 123;
  // Json j2 = 1.1;
  // Json j3 = "hello world";
  // Json j4 = true;

  // size_t size = j3.size();
  // json = j3;
  // Json arr(Json::Type::json_array);
  // arr[3] = json;
  // cout << arr.str() << endl;
  // arr[1] = j1;
  // arr[2] = j2;
  // arr[0] = j3;
  // arr[5] = json;
  // cout << arr.str() << endl;
  // cout << "Array is Size :" << arr.size() << endl;
  // Json j5("test01");
  // arr.append(Json());
  // arr.append(j5);
  // int a = arr[1];
  // double b = arr[2];
  // string c = arr[3];
  // cout << arr.str() << endl;
  // cout << "Array is Size :" << arr.size() << endl;

  // Json obj;

  // obj["name"] = arr;
  // obj["0"] = arr[0];

  // cout << obj.str() << endl;

  // json.parse(data);
  // std::cout << json.str() << std::endl;

  // const string & name = json["name"];
  // int type = json["age"];
  // const string & area = json["area"][0];
  // system("pause");
  return 0;
}
