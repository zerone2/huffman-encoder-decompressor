#include "huffmanDecompress.h"

/*������ �о�ͼ� ���ڿ� �ش繮�ڿ� ���� key ���� �޾ƿ´�*/
void Huffman::getKeyFile(ifstream & key)
{
	char ch, temp;	//���� �о�� char����
	string code = ""; // key���� ������ string����
	for (;;)
	{
		key.get(ch);	//�ش� ����
		key.get(temp);	//����
		if (temp == '*') return;		//���� �ڸ��� *�� ������ �Լ� ����.
		while (temp != '\n') {			//ch2�� ���ڸ� �޾ƿ��ٰ� ���Ͱ� ������ ch1�� ���� �޾ƾ��ϹǷ�
			key.get(temp);
			if (temp != '\n') code += temp;	//���� ������������ ���� key���� string ������ ����.
		}
		insert(ch, code);
		code = "";
	}
}

void Huffman::insert(char ch, string code)
{
	Huffman::pHuffNode p = myRoot; // ������ Ʈ�� ������
	for (int i = 0; i < code.length(); i++)
	{
		switch (code[i])
		{
		case '0': //���� �ڽĳ��
			if (p->left == 0) // ��常���
				p->left = new Huffman::HuffTreeNode('*');
			p = p->left;
			break;
		case '1': //������ �ڽĳ��
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
	p->data = ch;	//�ش� ���� �����Ϳ� ����.
}

/*�������� �Լ�*/
void Huffman::decode(string fileName, ifstream & hufFile)
{
	char ch1, ch2, bit;		// ���� �о�� char ����
	Huffman::pHuffNode p;	// ������ Ʈ���� ���� ������.
	std::ofstream output_file(fileName);
	bit = bit & 0x00;
	p = myRoot;

	/*���ڵ�ü�踦 �ɷ��������� for��*/
	for (;;)
	{
		hufFile.get(ch1);	//�ش� ����
		hufFile.get(ch2);	//����
		if (ch2 == '*')		//���Ⱑ �ƴ� *�� ������.
			break;
		while (ch2 != '\n') {	//ch2�� ���ڸ� �޾ƿ��ٰ� ���Ͱ� ������ ch1�� ���� �޾ƾ��ϹǷ�
			hufFile.get(ch2);
		}
	}

	/*binary ������ ������ �о�ͼ� ������ ���·� ����*/
	for (;;) {

		hufFile.get(bit);
		if (hufFile.eof()) return;
		for (int i = 0; i < 8; i++) {		//1byte=8bit, (�����Ҷ� 8��Ʈ�� ����)
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
			bit <<= 1;	//��Ʈ�� ��ĭ�� �������� �̵�.
		}
	}
}

/*���� ũ�� ���ϴ� �Լ�*/
int Huffman::getFileSize(string fileName)
{
	ifstream file(fileName, ios_base::in | ios_base::binary);
	file.seekg(0, ios_base::end);
	long size = file.tellg();
	return size;
}

