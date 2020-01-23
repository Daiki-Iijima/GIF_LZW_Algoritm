#include <string>
#include <ostream>
#include <iostream>
#include <bitset>
#include <vector>
#include <fstream>		//	�t�@�C���̓��o�͗p

using namespace std;

int GetColorTable(int count)
{
	return pow(2, (count + 1));
}

string LoadDataConvertToString(ifstream& _ifs, int _dataSize)
{
	string loadBitStr = "";					//	�ǂݍ���Ŕ��]�������r�b�g�𕶎���Ƃ��Ĉ�Ȃ��ŕۑ����邽�߂̕ϐ�
	char tmp;							//	�ǂݎ��p�̈ꎞ�ϐ�

	for (int i = 0; i < _dataSize; i++)
	{
		_ifs.get(tmp);					//	�������ǂݍ���

		bitset<8> loadbitset(tmp);		//	8bit�̌^�ɕϊ�

		bitset<8> reversbitset;
		for (int i = 0; i < 8; i++)		//	���]
		{
			reversbitset.set(i, loadbitset[7 - i]);
		}

		loadBitStr += reversbitset.to_string();
	}

	cout << "\n=== �ǂݎ��r�b�g === \n" << loadBitStr << "\n" << endl;

	return loadBitStr;
}

vector<unsigned long> ConvetDataToVecLong(string _str, int _firstBitSize)
{
	int firstBitSize = _firstBitSize;				//	�ŏ�LZW�����T�C�Y

	int startPos = 0;								//	�ǂݎ��J�n�ʒu
	int endPos = firstBitSize;						//	�ǂݎ�蕶����̍ŏI�ʒu

	int strLength = _str.length();					//	������̒���
	int dataCount = strLength / firstBitSize;		//	�ϊ���̃f�[�^��

	vector<unsigned long> convertData(dataCount);	//	�ϊ������f�[�^

	for (int i = 0; i < dataCount; i++)
	{
		cout << "�J�n�����ʒu : " << startPos << "�I�������ʒu : " << endPos << endl;

		if (endPos > strLength) { break; }

		std::string subStr = _str.substr(startPos, firstBitSize);	//	�����T�C�Y�ŕ������o

		cout << "���o:" << subStr << endl;

		std::reverse(subStr.begin(), subStr.end());					//	���]

		cout << "���]" << subStr << endl;

		bitset<256> resu(subStr);									//	�r�b�g�ɕϊ�

		convertData[i] = resu.to_ulong();

		startPos = endPos;
		endPos = endPos + firstBitSize;
	}

	return convertData;
}

int main()
{
	ifstream ifs("test.test", ios::binary);
	if (!ifs) cout << "�ǂݎ��Ȃ�����" << endl;

	int tableCount = 7;
	cout << "�g�p����F��" << GetColorTable(tableCount) << endl;

	string str = LoadDataConvertToString(ifs, 6);					//	�f�[�^������ǂݎ���āA�r�b�g�ϊ�->1�������r�b�g����בւ�->������Ƃ��Č���

	vector<unsigned long> dataVec = ConvetDataToVecLong(str, 9);	//	01�̕�����ɂȂ��Ă���f�[�^�𒊏o->���]->�r�b�g�ϊ�->���l�ϊ�

	for (const auto& data : dataVec) {
		cout << data << endl;
	}
}