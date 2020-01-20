#include <string>
#include <ostream>
#include <iostream>
#include <bitset>
#include <vector>
#include <fstream>		//	�t�@�C���̓��o�͗p

using namespace std;

int main()
{
	ifstream ifs("test.test", ios::binary);

	if (!ifs) cout << "�ǂݎ��Ȃ�����" << endl;

	char temp;

	int count = 7;

	int colorTableCount = pow(2, (count + 1));

	vector<bitset<8>> hexVec(colorTableCount);

	cout << colorTableCount << endl;

	string str = "";

	for (int i = 0; i < 6; i++)
	{
		ifs.get(temp);

		bitset<8> bi(temp);

		hexVec[i] = bi;

		bitset<8> bis;
		for (int i = 0; i < 8; i++)
		{
			bis.set(i, bi[7 - i]);
		}

		unsigned long result = bi.to_ulong();
		unsigned long reversResult = bis.to_ulong();

		str += bis.to_string();

		cout << hexVec[i] << endl;
		cout << bis << endl;

		cout << "10�i��" << result << endl;
		cout << "10�i��" << reversResult << endl;
	}

	cout << str << endl;

	int countt = 9;

	int start = 0;
	int end = countt;

	for (int i = 0; i < str.length() / countt; i++)
	{
		cout << "�J�n�����ʒu : " << start << "�I�������ʒu : " << end << endl;

		if (end > str.length()) { break; }

		std::string substr = str.substr(start, 9);

		cout << "���o:" << substr << endl;

		std::string stra = substr;

		std::reverse(stra.begin(), stra.end());

		cout << "���]" << stra << endl;

		bitset<9> resu(stra);
		unsigned long tt = resu.to_ulong();

		cout << tt << endl;

		start = end;
		end = end + 9;
	}
}