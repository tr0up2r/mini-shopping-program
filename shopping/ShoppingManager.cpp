#pragma once
#include "ShoppingManager.h"
#include <fstream>
#include <string>

// ShoppingManager ������
/*
	�����ڿ��� �Ű������� filename�� �޽��ϴ�.
	�Ű������� ���� ���ϸ��� �̿��� product.txt�� ����, �̸� �Է��ص� ��ǰ���� ����մϴ�.
	�����ڿ��� productList�� �ٷ� �ʱ�ȭ�ϱ� ������ ���� ���� �޴��� ���� ���� �ʽ��ϴ�.
*/
ShoppingManager::ShoppingManager(const string filename)
{
	ifstream fin;
	fin.open(filename);

	if (!fin) // ������ ������ �ʾ��� ��� ���� �޼��� ���.
	{
		cout << "������ �� �� ����." << endl;
		return;
	}

	string line;
	while (getline(fin, line)) // ������ ������ ���� ������ �о�´�.
	{
		int length = line.size();

		int index = line.find(';', 0); // �ҷ��� ���ο��� ;�� ��ġ�� ���� �ε����� �����Ѵ�.
		string pName = line.substr(0, index); // ; ���� �տ� �ִ� �ܾ�� ��ǰ��(name)�� ����.
		string sPrice = line.substr(index + 1, length); // ; ���� �ڿ� �ִ� ���ڴ� ����(price)�� ����.
		int price = stoi(sPrice);

		Product p(pName, price);
		productList.push_back(p);
	}
}


// mainMenu()
/*
	���� �޴������� ���� ������ ���, �� ���, ����, �� ������ ������ �� �� �ֽ��ϴ�.
	���� �Է¿� ���� ���� ó���� �ϴ� ���� �ʾҽ��ϴ�.
*/
void ShoppingManager::mainMenu()
{
	int selection;

	while (true)
	{
		cout << "<< INU ���ο� ���� ���� ȯ���մϴ�! >>" << endl;
		cout << "[1] ���� ������ ���\n[2] �� ���\n[3] ����\n�Է� : ";
		cin >> selection;
		cin.ignore();

		switch (selection)
		{
		case 1: // [1] ���� ������ ��� ���� ��, managerMode() �Լ� ����.
			managerMode();
			break;
		case 2: // [2] �� ��� ���� ��, customerMode() �Լ� ����.
			customerMode();
			break;
		case 3: // [3] ���� ���� ��, ���α׷� ����.
			return;
		default:
			cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n" << endl;
		}
	}
}

// managerMode()
/*
	mainMenu()���� ���� ������ ��带 �����ϸ� ���� �� �ִ� ����Դϴ�.
	������ ���� Ư���� ��й�ȣ�� �Է��ؾ� �ϵ��� �����غý��ϴ�.
	��й�ȣ�� 1234�� �̸� �����Ͽ����ϴ�.

	��ǰ �߰�, ��ǰ ����, ��� ��ǰ ���, ���� �޴��� ���ư���, 4���� ����� �����մϴ�.
	��ǰ ������ �ڵ尡 �ʹ� ����� �� ���� �ϴ��� ���� �ʾҽ��ϴ�.
*/
void ShoppingManager::managerMode()
{
	int password;
	int selection;

	while (true)
	{
		cout << endl;
		cout << "������ ��й�ȣ�� �Է��ϼ���(���� ȭ������ ���ư����� -1 �Է�) : ";
		cin >> password;

		if (password == -1)
		{
			cout << endl;
			return;
		}
		else if (password == 1234)
			break;
		else
			cout << "��й�ȣ�� Ʋ���ϴ�!" << endl;
	}

	// ������ ��й�ȣ�� �ùٸ��� �Է��ϸ� ���� ������ ��尡 ǥ�õ˴ϴ�.
	while (true)
	{
		cout << "\n< ���� ������ ��� >" << endl;
		cout << "[1] ��ǰ �߰�\n[2] ��ǰ ����\n[3] ��� ��ǰ ���\n[4] ���ư���\n�Է� : ";
		cin >> selection;
		cin.ignore();

		switch (selection)
		{
		case 1: // [1] ��ǰ �߰� ���� ��
			addProduct();
			break;
		case 2: // [2] ��ǰ ���� ���� ��
			deleteProduct();
			break;
		case 3: // [3] ��� ��ǰ ��� ���� ��
			print(productList);
			break;
		case 4: // [4] ���ư��� ���� ��
			cout << endl;
			return;
		default:
			cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n" << endl;
		}
	}
}

// addProduct() - [1] ��ǰ �߰�
/*
	�����ڰ� ���ο� ��ǰ�� �߰��ϴ� ����Դϴ�.
*/
void ShoppingManager::addProduct()
{
	Product new_p;

	cout << "\n���ο� ��ǰ�� �߰��մϴ�. ��ǰ �̸� �Է� �� no�� �Է��ϸ� ���� �����ϴ�." << endl;

	while (true)
	{
		cout << endl;
		cin >> new_p; // �������� ������ >>�� �̿��� Product ��ü�� �Է�.

		if (new_p.getName() == "no") // ���Ḧ ���� ������ �켱������ �˻�. no�� �Է��ߴٸ� ��ǰ �߰� ����.
			return;

		int size = productList.size();
		for (int i = 0; i < size; i++) // �̸��� �̿��� �ߺ� �˻�
		{
			if (new_p.getName() == productList[i].getName())
			{
				cout << "�̹� �����ϴ� ��ǰ�Դϴ�." << endl;
				break;
			}
			else if (i + 1 == productList.size()) // �ߺ��Ǵ� ��ǰ�� ������ productList vector�� ��ǰ �߰�.
			{
				productList.push_back(new_p);
				cout << new_p.getName() << "��(��) ��Ͽ� ����߽��ϴ�." << endl;
				break;
			}
		}
	}
}

// deleteProduct() - ��ǰ ����
/*
	�����ڰ� productList�� �߰��ϴ� ����Դϴ�.
*/
void ShoppingManager::deleteProduct()
{
	if (productList.size() == 0) // ���Ͱ� ����ٸ�, ������ �Ұ������� �˸��� ���� �޼��� ���.
	{
		cout << "������ �� �ִ� ��ǰ�� �����ϴ�. ��ǰ�� ���� �߰����ּ���.\n\n";
		return;
	}

	vector<Product>::iterator it; // iterator�� �̿��� erase.
	string name;

	cout << "\n�����Ͻ� ��ǰ�� �̸��� �Է��ϼ��� : ";
	getline(cin, name);

	for (it = productList.begin(); it < productList.end(); it++)
	{
		if (it->getName() == name) // �Է��� ��ǰ�� ���Ϳ� �����Ѵٸ� ����.
		{
			cout << it->getName() << "��(��) �����մϴ�.\n\n";
			it = productList.erase(it);
			break;
		}
		else if (it == productList.end() - 1) // �������� �ʴ´ٸ� �������� ����.
		{
			cout << "�Է��Ͻ� ��ǰ�� ��Ͽ� �����ϴ�.\n\n";
			break;
		}
	}
}

// print() - �Ű������� ���� vector�� ���� ���
/*
	�Ű������� ���� Product�� vector�� ��� ���Ҹ� ������ݴϴ�.
	������ �Ű����� ���� print()�� �����ߴµ� �̷��� cart�� ����ϱⰡ �����,
	�Ű������� �ִ� �������� �ٲپ����ϴ�.
*/
void ShoppingManager::print(vector<Product> pList)
{
	int size = pList.size();
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << pList[i] << endl;
	}
	cout << "\n�� " << pList.size() << "������ ��ǰ\n" << endl;
}

// customerMode() - �� ���
/*
	�� ��忡���� ��ǰ ����, ��ǰ �˻�, ��ٱ��� ���, ���� �޴��� ���ư���, 4���� ����� �����մϴ�.
	��ǰ ����� print() �Լ��� �̿��ϴ� ������ �����̰�,
	��ǰ �˻��� ��ٱ��� ��带 �Ʒ����� ���� �����մϴ�.
*/
void ShoppingManager::customerMode()
{
	int selection;

	while (true)
	{
		cout << "\n< �� ��� >" << endl;
		cout << "[1] ��ǰ ����\n[2] ��ǰ �˻�\n[3] ��ٱ��� ���\n[4] ���ư���\n�Է� : ";
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
			cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n" << endl;
		}
	}

}

// search() - ��ǰ �˻�
/*
	�Է��� ��ǰ�� ����Ʈ�� �ִ��� �˻��ϴ� ������ ��ǰ ���������� ������ �����մϴ�.
	�� �κ��� ���� �Լ��� �� �� ������ �� ���� �� �����ϴ�...
*/
void ShoppingManager::search()
{
	string product;
	cout << "\n��ǰ���� �Է��ϼ��� : ";
	getline(cin, product);

	int size = productList.size();
	for (int i = 0; i < size; i++)
	{
		if (product == productList[i].getName()) // �Է��� ��ǰ�� ���Ϳ� �ִٸ� ���� ���.
		{
			cout << productList[i] << endl; // �������� ������ <<�� �̿��� Product ��ü�� ���.
			break;
		}
		else if (i + 1 == productList.size()) // �Է��� ��ǰ�� ���Ϳ� ���� ���.
		{
			cout << "�Է��Ͻ� ��ǰ�� ���� ��ϵǾ� ���� �ʽ��ϴ�.\n";
			break;
		}
	}
}

// cartMode() - ��ٱ��� ���
/*
	��ϵǾ� �ִ� ��ǰ���� �̿��� ��ٱ��� ��带 �����մϴ�.

	cart��� vector�� ��ٱ��� ��带 �̿��� ������ ������־�� �ϱ� ������
	��� ������ �ƴ�, cartMode() �Լ��� ���� ������ �����س��ҽ��ϴ�.

	��ǰ ��ü ����� ���⼭�� �� �� �ְ�,
	��µ� ��ǰ�� ����Ʈ�� ���� ��ٱ��Ͽ� ���� �� �ֽ��ϴ�.
	���� ���ݱ��� ��ٱ��Ͽ� ���� ��ǰ ����� ����غ� ���� �ֽ��ϴ�.

	��ٱ��Ͽ� ���� ��ǰ�� �����ϴ� ������ ���� �ʾҽ��ϴ�.
	productList�� ����� ���ҽ�Ű�� ���� �ٽ� �߰���Ű�� �ϴ� ������ �� ����� �� ���Ƽ���...
*/
void ShoppingManager::cartMode()
{
	int selection;
	vector<Product> cart;

	while (true)
	{
		cout << "\n< ��ٱ��� ��� >" << endl;
		cout << "[1] ��ǰ ����\n[2] ��ٱ��Ͽ� ���\n[3] ��ٱ��� ���\n[4] ����ϱ�\n�Է� : ";
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
			cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n" << endl;
		}
	}

}

// addToCart() - ��ٱ��Ͽ� ���
/*
	���⼭�� ���� �Է��� ��ǰ�� ��ٱ��Ͽ� �ִ��� �˻��ϴ� ������ �ʿ��ϳ׿�...
	Ȯ���� �� �κ��� �ٸ� �Լ��� ���� �ߺ� �ڵ带 ���� ���� �� ���� �� �����ϴ�.

	��ٱ��Ͽ� ���ϴ� ��ǰ�� ���, productList�� �ִ� �� ��ǰ�� ����� ���ҽ�ŵ�ϴ�.
*/
void ShoppingManager::addToCart(vector<Product>& cart)
{
	string product;
	while (true)
	{
		cout << "\n�����ϰ��� �ϴ� ��ǰ �̸� �Է�(��ٱ��� ��� ����� no �Է�) : ";
		getline(cin, product);

		if (product == "no")
			return;

		int pSize = productList.size();
		int quantity;
		for (int i = 0; i < pSize; i++)
		{
			if (product == productList[i].getName()) // �Է��� ��ǰ�� ���Ϳ� �ִٸ� ��ٱ��� ����.
			{
				Product p(productList[i].getName(), productList[i].getPrice(), 0);
				cout << "���� ���� �Է�(" << productList[i].getName() << "�� ���� ��� : "
					<< productList[i].getStock() << ") : ";
				cin >> quantity;
				cin.ignore();

				// ������� ���� ������ ��ǰ�� �������� �ϸ� ���� ó��.
				if (productList[i].getStock() < quantity)
				{
					cout << "��� �����մϴ�!" << endl;
					break;
				}
				else
				{
					cout << p.getName() << " " << quantity << "���� ��ٱ��Ͽ� ��ҽ��ϴ�." << endl;

					// ��ٱ��Ͽ� ���� ��ŭ �ش� ��ǰ�� ����� ���ҽ�Ŵ.
					productList[i].setStock(productList[i].getStock() - quantity);
					bool doesExist = false;

					int cSize = cart.size();
					// ������ ��ǰ�� ��ٱ��Ͽ� ���� ���� ���� ��Ƶ� ������ ���� �ʵ���.
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
			else if (i + 1 == pSize) // �Է��� ��ǰ�� ���Ϳ� ���� ���.
			{
				cout << "�Է��Ͻ� ��ǰ�� ���� ��ϵǾ� ���� �ʽ��ϴ�.\n";
				break;
			}
		}
	}

	return;

}

// calculate() - ����ϱ�
/*
	��ٱ��Ͽ� ���� ��ǰ���� �� �� ������� ��, �� �������� ������ְ� ��ٱ��� ��带 �����մϴ�.
	�ƹ��͵� ���� ���� ��쿡�� ��ٱ��� ��带 �����մϴ�.
*/
void ShoppingManager::calculate(const vector<Product> cart)
{
	int size = cart.size();

	if (size == 0)
	{
		cout << "\n��ٱ��Ͽ� �ƹ��͵� �����ϴ�." << endl;
		return;
	}

	int total = 0;
	print(cart);
	for (int i = 0; i < size; i++)
	{
		total += cart[i].getPrice() * cart[i].getStock();
	}

	cout << "�� " << total << "�� ���� �Ϸ�Ǿ����ϴ�." << endl;
	cout << "��ٱ��� ��带 �����մϴ�." << endl;
}