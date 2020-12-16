#include <iostream>
#include <vector>
#include "Product.h"
using namespace std;

// ShoppingManager 클래스
/*
	쇼핑 사이트의 모든 상품 리스트인 productList vector를 멤버 변수로 가집니다.
	메뉴 형식에서 각 case에 해당하는 것들은 모두 함수로 세분화했습니다.
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