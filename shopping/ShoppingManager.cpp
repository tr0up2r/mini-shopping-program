#pragma once
#include "ShoppingManager.h"
#include <fstream>
#include <string>

// ShoppingManager 생성자
/*
	생성자에서 매개변수로 filename을 받습니다.
	매개변수로 받은 파일명을 이용해 product.txt를 열어, 미리 입력해둔 상품들을 등록합니다.
	생성자에서 productList를 바로 초기화하기 때문에 파일 열기 메뉴는 따로 두지 않습니다.
*/
ShoppingManager::ShoppingManager(const string filename)
{
	ifstream fin;
	fin.open(filename);

	if (!fin) // 파일이 열리지 않았을 경우 오류 메세지 출력.
	{
		cout << "파일을 열 수 없다." << endl;
		return;
	}

	string line;
	while (getline(fin, line)) // 파일의 끝까지 라인 단위로 읽어온다.
	{
		int length = line.size();

		int index = line.find(';', 0); // 불러온 라인에서 ;이 위치한 곳의 인덱스를 추출한다.
		string pName = line.substr(0, index); // ; 보다 앞에 있는 단어는 상품명(name)에 저장.
		string sPrice = line.substr(index + 1, length); // ; 보다 뒤에 있는 숫자는 가격(price)에 저장.
		int price = stoi(sPrice);

		Product p(pName, price);
		productList.push_back(p);
	}
}


// mainMenu()
/*
	메인 메뉴에서는 쇼핑 관리자 모드, 고객 모드, 종료, 세 가지의 선택을 할 수 있습니다.
	문자 입력에 대한 예외 처리는 일단 하지 않았습니다.
*/
void ShoppingManager::mainMenu()
{
	int selection;

	while (true)
	{
		cout << "<< INU 쇼핑에 오신 것을 환영합니다! >>" << endl;
		cout << "[1] 쇼핑 관리자 모드\n[2] 고객 모드\n[3] 종료\n입력 : ";
		cin >> selection;
		cin.ignore();

		switch (selection)
		{
		case 1: // [1] 쇼핑 관리자 모드 선택 시, managerMode() 함수 실행.
			managerMode();
			break;
		case 2: // [2] 고객 모드 선택 시, customerMode() 함수 실행.
			customerMode();
			break;
		case 3: // [3] 종료 선택 시, 프로그램 종료.
			return;
		default:
			cout << "잘못된 입력입니다. 다시 입력해주세요.\n" << endl;
		}
	}
}

// managerMode()
/*
	mainMenu()에서 쇼핑 관리자 모드를 선택하면 들어올 수 있는 모드입니다.
	관리자 모드는 특별히 비밀번호를 입력해야 하도록 설정해봤습니다.
	비밀번호는 1234로 미리 지정하였습니다.

	상품 추가, 상품 삭제, 모든 상품 출력, 메인 메뉴로 돌아가기, 4가지 기능을 수행합니다.
	상품 수정은 코드가 너무 길어질 것 같아 일단은 넣지 않았습니다.
*/
void ShoppingManager::managerMode()
{
	int password;
	int selection;

	while (true)
	{
		cout << endl;
		cout << "관리자 비밀번호를 입력하세요(메인 화면으로 돌아가려면 -1 입력) : ";
		cin >> password;

		if (password == -1)
		{
			cout << endl;
			return;
		}
		else if (password == 1234)
			break;
		else
			cout << "비밀번호가 틀립니다!" << endl;
	}

	// 관리자 비밀번호를 올바르게 입력하면 쇼핑 관리자 모드가 표시됩니다.
	while (true)
	{
		cout << "\n< 쇼핑 관리자 모드 >" << endl;
		cout << "[1] 상품 추가\n[2] 상품 삭제\n[3] 모든 상품 출력\n[4] 돌아가기\n입력 : ";
		cin >> selection;
		cin.ignore();

		switch (selection)
		{
		case 1: // [1] 상품 추가 선택 시
			addProduct();
			break;
		case 2: // [2] 상품 삭제 선택 시
			deleteProduct();
			break;
		case 3: // [3] 모든 상품 출력 선택 시
			print(productList);
			break;
		case 4: // [4] 돌아가기 선택 시
			cout << endl;
			return;
		default:
			cout << "잘못된 입력입니다. 다시 입력해주세요.\n" << endl;
		}
	}
}

// addProduct() - [1] 상품 추가
/*
	관리자가 새로운 상품을 추가하는 모드입니다.
*/
void ShoppingManager::addProduct()
{
	Product new_p;

	cout << "\n새로운 상품을 추가합니다. 상품 이름 입력 시 no를 입력하면 빠져 나갑니다." << endl;

	while (true)
	{
		cout << endl;
		cin >> new_p; // 재정의한 연산자 >>를 이용한 Product 객체의 입력.

		if (new_p.getName() == "no") // 종료를 위한 조건을 우선적으로 검사. no를 입력했다면 상품 추가 종료.
			return;

		int size = productList.size();
		for (int i = 0; i < size; i++) // 이름을 이용한 중복 검사
		{
			if (new_p.getName() == productList[i].getName())
			{
				cout << "이미 존재하는 상품입니다." << endl;
				break;
			}
			else if (i + 1 == productList.size()) // 중복되는 상품이 없으면 productList vector에 상품 추가.
			{
				productList.push_back(new_p);
				cout << new_p.getName() << "를(을) 목록에 등록했습니다." << endl;
				break;
			}
		}
	}
}

// deleteProduct() - 상품 삭제
/*
	관리자가 productList을 추가하는 모드입니다.
*/
void ShoppingManager::deleteProduct()
{
	if (productList.size() == 0) // 벡터가 비었다면, 삭제가 불가능함을 알리는 오류 메세지 출력.
	{
		cout << "삭제할 수 있는 상품이 없습니다. 상품을 먼저 추가해주세요.\n\n";
		return;
	}

	vector<Product>::iterator it; // iterator를 이용한 erase.
	string name;

	cout << "\n삭제하실 상품의 이름을 입력하세요 : ";
	getline(cin, name);

	for (it = productList.begin(); it < productList.end(); it++)
	{
		if (it->getName() == name) // 입력한 상품이 벡터에 존재한다면 삭제.
		{
			cout << it->getName() << "를(을) 삭제합니다.\n\n";
			it = productList.erase(it);
			break;
		}
		else if (it == productList.end() - 1) // 존재하지 않는다면 삭제하지 않음.
		{
			cout << "입력하신 상품은 목록에 없습니다.\n\n";
			break;
		}
	}
}

// print() - 매개변수로 들어온 vector에 대한 출력
/*
	매개변수로 들어온 Product형 vector의 모든 원소를 출력해줍니다.
	원래는 매개변수 없는 print()로 선언했는데 이러면 cart를 출력하기가 어려워,
	매개변수가 있는 형식으로 바꾸었습니다.
*/
void ShoppingManager::print(vector<Product> pList)
{
	int size = pList.size();
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << pList[i] << endl;
	}
	cout << "\n총 " << pList.size() << "가지의 상품\n" << endl;
}

// customerMode() - 고객 모드
/*
	고객 모드에서는 상품 보기, 상품 검색, 장바구니 모드, 메인 메뉴로 돌아가기, 4가지 기능을 수행합니다.
	상품 보기는 print() 함수를 이용하는 간단한 형태이고,
	상품 검색과 장바구니 모드를 아래에서 새로 구현합니다.
*/
void ShoppingManager::customerMode()
{
	int selection;

	while (true)
	{
		cout << "\n< 고객 모드 >" << endl;
		cout << "[1] 상품 보기\n[2] 상품 검색\n[3] 장바구니 모드\n[4] 돌아가기\n입력 : ";
		cin >> selection;
		cin.ignore();
		switch (selection)
		{
		case 1:
			print(productList);
			break;
		case 2:
			search();
			break;
		case 3:
			cartMode();
			break;
		case 4:
			return;
		default:
			cout << "잘못된 입력입니다. 다시 입력해주세요.\n" << endl;
		}
	}

}

// search() - 상품 검색
/*
	입력한 상품이 리스트에 있는지 검사하는 과정이 상품 삭제에서와 굉장히 유사합니다.
	이 부분을 따로 함수로 뺄 수 있으면 더 좋을 것 같습니다...
*/
void ShoppingManager::search()
{
	string product;
	cout << "\n상품명을 입력하세요 : ";
	getline(cin, product);

	int size = productList.size();
	for (int i = 0; i < size; i++)
	{
		if (product == productList[i].getName()) // 입력한 상품이 벡터에 있다면 정보 출력.
		{
			cout << productList[i] << endl; // 재정의한 연산자 <<를 이용한 Product 객체의 출력.
			break;
		}
		else if (i + 1 == productList.size()) // 입력한 상품이 벡터에 없을 경우.
		{
			cout << "입력하신 상품은 현재 등록되어 있지 않습니다.\n";
			break;
		}
	}
}

// cartMode() - 장바구니 모드
/*
	등록되어 있는 상품들을 이용해 장바구니 모드를 진행합니다.

	cart라는 vector는 장바구니 모드를 이용할 때마다 비워져있어야 하기 때문에
	멤버 변수가 아닌, cartMode() 함수의 지역 변수로 선언해놓았습니다.

	상품 전체 출력을 여기서도 할 수 있고,
	출력된 상품의 리스트를 보고 장바구니에 담을 수 있습니다.
	또한 지금까지 장바구니에 담은 상품 목록을 출력해볼 수도 있습니다.

	장바구니에 담은 상품을 제거하는 과정은 넣지 않았습니다.
	productList의 재고량을 감소시키고 나서 다시 추가시키고 하는 과정이 좀 길어질 것 같아서요...
*/
void ShoppingManager::cartMode()
{
	int selection;
	vector<Product> cart;

	while (true)
	{
		cout << "\n< 장바구니 모드 >" << endl;
		cout << "[1] 상품 보기\n[2] 장바구니에 담기\n[3] 장바구니 출력\n[4] 계산하기\n입력 : ";
		cin >> selection;
		cin.ignore();

		switch (selection)
		{
		case 1:
			print(productList);
			break;
		case 2:
			addToCart(cart);
			break;
		case 3:
			print(cart);
			break;
		case 4:
			calculate(cart);
			return;
		default:
			cout << "잘못된 입력입니다. 다시 입력해주세요.\n" << endl;
		}
	}

}

// addToCart() - 장바구니에 담기
/*
	여기서도 역시 입력한 상품이 장바구니에 있는지 검사하는 과정이 필요하네요...
	확실히 이 부분을 다른 함수로 빼야 중복 코드를 많이 줄일 수 있을 것 같습니다.

	장바구니에 원하는 상품을 담고, productList에 있는 그 상품의 재고량을 감소시킵니다.
*/
void ShoppingManager::addToCart(vector<Product>& cart)
{
	string product;
	while (true)
	{
		cout << "\n구매하고자 하는 상품 이름 입력(장바구니 담기 종료는 no 입력) : ";
		getline(cin, product);

		if (product == "no")
			return;

		int pSize = productList.size();
		int quantity;
		for (int i = 0; i < pSize; i++)
		{
			if (product == productList[i].getName()) // 입력한 상품이 벡터에 있다면 장바구니 진행.
			{
				Product p(productList[i].getName(), productList[i].getPrice(), 0);
				cout << "담을 수량 입력(" << productList[i].getName() << "의 남은 재고 : "
					<< productList[i].getStock() << ") : ";
				cin >> quantity;
				cin.ignore();

				// 재고량보다 많은 수량의 상품을 담으려고 하면 오류 처리.
				if (productList[i].getStock() < quantity)
				{
					cout << "재고가 부족합니다!" << endl;
					break;
				}
				else
				{
					cout << p.getName() << " " << quantity << "개를 장바구니에 담았습니다." << endl;

					// 장바구니에 담은 만큼 해당 상품의 재고량을 감소시킴.
					productList[i].setStock(productList[i].getStock() - quantity);
					bool doesExist = false;

					int cSize = cart.size();
					// 동일한 상품을 장바구니에 여러 번에 거쳐 담아도 오류가 나지 않도록.
					for (int i = 0; i < cSize; i++)
					{
						if (p.getName() == cart[i].getName())
						{
							cart[i].setStock(cart[i].getStock() + quantity);
							doesExist = true;
							break;
						}
					}

					if (!doesExist)
					{
						p.setStock(quantity);
						cart.push_back(p);
						break;
					}
					break;
				}
			}
			else if (i + 1 == pSize) // 입력한 상품이 벡터에 없을 경우.
			{
				cout << "입력하신 상품은 현재 등록되어 있지 않습니다.\n";
				break;
			}
		}
	}

	return;

}

// calculate() - 계산하기
/*
	장바구니에 담은 상품들을 한 번 출력해준 후, 총 결제액을 출력해주고 장바구니 모드를 종료합니다.
	아무것도 넣지 않은 경우에도 장바구니 모드를 종료합니다.
*/
void ShoppingManager::calculate(const vector<Product> cart)
{
	int size = cart.size();

	if (size == 0)
	{
		cout << "\n장바구니에 아무것도 없습니다." << endl;
		return;
	}

	int total = 0;
	print(cart);
	for (int i = 0; i < size; i++)
	{
		total += cart[i].getPrice() * cart[i].getStock();
	}

	cout << "총 " << total << "원 결제 완료되었습니다." << endl;
	cout << "장바구니 모드를 종료합니다." << endl;
}