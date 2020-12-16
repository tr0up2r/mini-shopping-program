#include <iostream>
#include <vector>
#include "Product.h"
using namespace std;

// ShoppingManager Ŭ����
/*
	���� ����Ʈ�� ��� ��ǰ ����Ʈ�� productList vector�� ��� ������ �����ϴ�.
	�޴� ���Ŀ��� �� case�� �ش��ϴ� �͵��� ��� �Լ��� ����ȭ�߽��ϴ�.
*/
class ShoppingManager
{
	vector<Product> productList;
public:
	ShoppingManager(const string filename);

	// In mainMenu
	void mainMenu();
	void managerMode();
	void customerMode();

	// In managerMode()
	void addProduct();
	void deleteProduct();
	void print(vector<Product> pList);

	// In customerMode()
	void search();
	void cartMode();
	void addToCart(vector<Product>& cart);
	void calculate(const vector<Product> cart);
};