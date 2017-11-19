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
	//파일이 제대로 열렸는지 체크
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

	originSize = H.getFileSize(hufFilename);	//압축된 파일의 사이즈

	decodedFile = (string)strtok_s(hufFilename, ".", &context) + ".txt";

	H.decode(decodedFile, hufFile2);
	decodedSize = H.getFileSize(decodedFile);	//압축해제 후의 파일 사이즈

	finish = clock();

	cout << "\nExecution time: +/- " << ((double)(finish - start)) / CLOCKS_PER_SEC << "s\n";
	cout << "Before Compress : " << hufFilename << ".txt / " << originSize << "byte  "
		<< "&&  After Compress : " << decodedFile << " / " << decodedSize << "byte" << endl;
	cout << "\n압축해제완료!!!!" << endl;

	cin >> a;

}