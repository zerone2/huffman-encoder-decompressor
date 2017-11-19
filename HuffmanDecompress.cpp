#include "huffmanDecompress.h"

/*파일을 읽어와서 문자와 해당문자에 대한 key 값을 받아온다*/
void Huffman::getKeyFile(ifstream & key)
{
	char ch, temp;	//문자 읽어올 char변수
	string code = ""; // key값을 저장할 string변수
	for (;;)
	{
		key.get(ch);	//해당 문자
		key.get(temp);	//띄어쓰기
		if (temp == '*') return;		//띄어쓰기 자리에 *이 들어오면 함수 종료.
		while (temp != '\n') {			//ch2에 문자를 받아오다가 엔터가 들어오면 ch1에 문자 받아야하므로
			key.get(temp);
			if (temp != '\n') code += temp;	//엔터 들어오기전까지 받은 key값을 string 변수에 저장.
		}
		insert(ch, code);
		code = "";
	}
}

void Huffman::insert(char ch, string code)
{
	Huffman::pHuffNode p = myRoot; // 허프만 트리 포인터
	for (int i = 0; i < code.length(); i++)
	{
		switch (code[i])
		{
		case '0': //왼쪽 자식노드
			if (p->left == 0) // 노드만들기
				p->left = new Huffman::HuffTreeNode('*');
			p = p->left;
			break;
		case '1': //오른쪽 자식노드
			if (p->right == 0)
				p->right = new Huffman::HuffTreeNode('*');
			p = p->right;
			break;
		default:
			cerr << "*** can't read character in the key code ***" << endl;
			cout << "program will be terminated in 3sec" << endl;
			Sleep(3000);
			exit(1);
		}
	}
	p->data = ch;	//해당 문자 데이터에 저장.
}

/*압축해제 함수*/
void Huffman::decode(string fileName, ifstream & hufFile)
{
	char ch1, ch2, bit;		// 문자 읽어올 char 변수
	Huffman::pHuffNode p;	// 허프만 트리를 따라갈 포인터.
	std::ofstream output_file(fileName);
	bit = bit & 0x00;
	p = myRoot;

	/*인코딩체계를 걸러내기위한 for문*/
	for (;;)
	{
		hufFile.get(ch1);	//해당 문자
		hufFile.get(ch2);	//띄어쓰기
		if (ch2 == '*')		//띄어쓰기가 아닌 *이 있으면.
			break;
		while (ch2 != '\n') {	//ch2에 문자를 받아오다가 엔터가 들어오면 ch1에 문자 받아야하므로
			hufFile.get(ch2);
		}
	}

	/*binary 형태의 파일을 읽어와서 압축전 상태로 복구*/
	for (;;) {

		hufFile.get(bit);
		if (hufFile.eof()) return;
		for (int i = 0; i < 8; i++) {		//1byte=8bit, (압축할때 8비트씩 나눔)
			if (p->left == 0 && p->right == 0) {
				output_file << p->data;
				p = myRoot;
			}
			if ((bit & 0x80) == 0x80) {		//0x80 : 128 = 2^7
				p = p->right;
			}
			else {
				p = p->left;
			}
			bit <<= 1;	//비트를 한칸씩 왼쪽으로 이동.
		}
	}
}

/*파일 크기 구하는 함수*/
int Huffman::getFileSize(string fileName)
{
	ifstream file(fileName, ios_base::in | ios_base::binary);
	file.seekg(0, ios_base::end);
	long size = file.tellg();
	return size;
}

