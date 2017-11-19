#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <Windows.h>

#include "huffmanDecompress.h"

using namespace std;

int main()
{
	char hufFilename[30];
	char *context;
	int originSize, decodedSize;
	int a;
	clock_t start, finish;
	Huffman H;
	string decodedFile;

	cout << "==Decompressor Ready==\n" << endl;
	cout << "name of the file to decompress : ";
	cin >> hufFilename;

	ifstream hufFile(hufFilename);
	hufFile.unsetf(ios_base::skipws);
	//������ ����� ���ȴ��� üũ
	if (!hufFile)
	{
		cout << "ifstream failed" << endl;
		cout << "check out that you typed write file, this program will be terminated after 3sec" << endl;
		Sleep(3000);
		return 0;
	}
	start = clock();
	H.getKeyFile(hufFile);

	ifstream hufFile2(hufFilename, ios::binary);
	hufFile.unsetf(ios_base::skipws);

	if (!hufFile2)
	{
		cout << "ifstream failed" << endl;
		cout << "check out that you typed write file, this program will be terminated after 3sec" << endl;
		Sleep(3000);
		return 0;
	}

	originSize = H.getFileSize(hufFilename);	//����� ������ ������

	decodedFile = (string)strtok_s(hufFilename, ".", &context) + ".txt";

	H.decode(decodedFile, hufFile2);
	decodedSize = H.getFileSize(decodedFile);	//�������� ���� ���� ������

	finish = clock();

	cout << "\nExecution time: +/- " << ((double)(finish - start)) / CLOCKS_PER_SEC << "s\n";
	cout << "Before Compress : " << hufFilename << ".txt / " << originSize << "byte  "
		<< "&&  After Compress : " << decodedFile << " / " << decodedSize << "byte" << endl;
	cout << "\n���������Ϸ�!!!!" << endl;

	cin >> a;

}