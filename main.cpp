#include "aes128.h"
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

//AES算法基本功能（ECB模式，128bit）测试函数
void test_ecb_aes128(){
	byte_t plainText[4][4] = {0x00, 0x44, 0x88, 0xcc,
							  0x11, 0x55, 0x99, 0xdd,
							  0x22, 0x66, 0xaa, 0xee,
							  0x33, 0x77, 0xbb, 0xff};

	byte_t key[4][4] = {0x00, 0x04, 0x08, 0x0c,
						0x01, 0x05, 0x09, 0x0d,
						0x02, 0x06, 0x0a, 0x0e,
						0x03, 0x07, 0x0b, 0x0f};

	cout << "|------ AES-128 ECB MODE ------|" << endl
		 << endl;
	cout << "PLAINTEXT:\t\t";					//显示初始信息（明文、密钥）
	printBlock(plainText);						//
	cout << "KEY:\t\t\t";						//
	printBlock(key);							//
	cout << endl;								//

	aes_128(plainText, key, true, true);		//加密并输出过程数据
	cout << endl;
	aes_128(plainText, key, false, true);		//解密并输出过程数据
}

//AES算法OFB模式（128bit）测试函数
void test_ofb_aes128(){
	byte_t key[4][4] = {0x00, 0x04, 0x08, 0x0c,
						0x01, 0x05, 0x09, 0x0d,
						0x02, 0x06, 0x0a, 0x0e,
						0x03, 0x07, 0x0b, 0x0f};

	byte_t IV[4][4] = {0x08, 0x04, 0x00, 0xcc,
					   0x07, 0x03, 0x99, 0xdd,
					   0x06, 0x02, 0xaa, 0xee,
					   0x05, 0x01, 0xbb, 0xff};

	string str_plainText = "AES became effective as a federal government standard after approval by the Secretary of Commerce. It is the first publicly accessible cipher approved by the National Security Agency for top secret information.";
	vector<byte_t> vec_cipherText;

	//填充0
	while (str_plainText.size() % 16 != 0)
		str_plainText.push_back(char(0));

	//逐块计算密文
	byte_t block[4][4];
	int blockCnt = str_plainText.size() / 16;
	for (int i = 0; i < blockCnt;i++){
		//IV与密钥进行加密运算，结果保存至IV
		aes_128(IV, key, true, false);	

		//从明文中读取16字节
		for (int j = 0; j < 16;j++){
			block[j % 4][j / 4] = str_plainText[i * 16 + j];
		}

		//调用轮密钥加函数计算异或值，结果保存至block
		add_round_key(block, IV);

		//将异或后的密文保存到容器中
		for (int j = 0; j < 16;j++){
			vec_cipherText.push_back(block[j % 4][j / 4]);
		}
	}

	//输出结果
	cout << "|------ AES-128 OFB MODE ------|" << endl
		 << endl;
	cout << "PLAINTEXT:" << endl;
	cout << str_plainText << endl
		 << endl;
	cout << "CIPHERTEXT:" << endl;
	for (int i = 0; i < vec_cipherText.size(); i++){
		cout << setfill('0') << setw(2) << hex << (int)vec_cipherText[i];
	}
	cout << endl;
}

int main(int argc, char *argv[])
{
	if(argc > 1){
		if (string(argv[1]) == "ofb") //若指定调用OFB模式
			test_ofb_aes128();		  //则调用OFB模式测试函数
	}
	else
		test_ecb_aes128();				//默认调用ECB模式测试函数

	return 0;
}
