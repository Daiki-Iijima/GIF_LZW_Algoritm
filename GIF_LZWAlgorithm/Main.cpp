#include <string>
#include <ostream>
#include <iostream>
#include <bitset>
#include <vector>
#include <fstream>		//	ファイルの入出力用

using namespace std;

int GetColorTable(int count)
{
	return pow(2, (count + 1));
}

string LoadDataConvertToString(ifstream& _ifs, int _dataSize)
{
	string loadBitStr = "";					//	読み込んで反転させたビットを文字列として一つなぎで保存するための変数
	char tmp;							//	読み取り用の一時変数

	for (int i = 0; i < _dataSize; i++)
	{
		_ifs.get(tmp);					//	文字列を読み込む

		bitset<8> loadbitset(tmp);		//	8bitの型に変換

		bitset<8> reversbitset;
		for (int i = 0; i < 8; i++)		//	反転
		{
			reversbitset.set(i, loadbitset[7 - i]);
		}

		loadBitStr += reversbitset.to_string();
	}

	cout << "\n=== 読み取りビット === \n" << loadBitStr << "\n" << endl;

	return loadBitStr;
}

vector<unsigned long> ConvetDataToVecLong(string _str, int _firstBitSize)
{
	int firstBitSize = _firstBitSize;				//	最小LZW辞書サイズ

	int startPos = 0;								//	読み取り開始位置
	int endPos = firstBitSize;						//	読み取り文字列の最終位置

	int strLength = _str.length();					//	文字列の長さ
	int dataCount = strLength / firstBitSize;		//	変換後のデータ数

	vector<unsigned long> convertData(dataCount);	//	変換したデータ

	for (int i = 0; i < dataCount; i++)
	{
		cout << "開始文字位置 : " << startPos << "終了文字位置 : " << endPos << endl;

		if (endPos > strLength) { break; }

		std::string subStr = _str.substr(startPos, firstBitSize);	//	辞書サイズで文字抽出

		cout << "抽出:" << subStr << endl;

		std::reverse(subStr.begin(), subStr.end());					//	反転

		cout << "反転" << subStr << endl;

		bitset<256> resu(subStr);									//	ビットに変換

		convertData[i] = resu.to_ulong();

		startPos = endPos;
		endPos = endPos + firstBitSize;
	}

	return convertData;
}

int main()
{
	ifstream ifs("test.test", ios::binary);
	if (!ifs) cout << "読み取れないぞい" << endl;

	int tableCount = 7;
	cout << "使用する色数" << GetColorTable(tableCount) << endl;

	string str = LoadDataConvertToString(ifs, 6);					//	データ部分を読み取って、ビット変換->1文字ずつビットを並べ替え->文字列として結合

	vector<unsigned long> dataVec = ConvetDataToVecLong(str, 9);	//	01の文字列になっているデータを抽出->反転->ビット変換->数値変換

	for (const auto& data : dataVec) {
		cout << data << endl;
	}
}