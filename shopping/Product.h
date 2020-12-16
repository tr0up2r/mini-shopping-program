#include <iostream>
using namespace std;

// Product Ŭ����
/*
	��ǰ �̸��� ����, ����� ��� ������ �����ϴ�.
	��ϵǴ� ��ǰ���� ����� ������ 100���� �ֵ��� �����մϴ�.
	>> �����ڿ� << �����ڸ� �������մϴ�.
*/
class Product
{
	string name;
	int price;
	int stock;
public:
	Product(string name = "", int price = 0, int stock = 100) : name(name), price(price), stock(stock) {}
	string getName() const { return name; }
	int getPrice() const { return price; }
	int getStock() const { return stock; }
	void setStock(int stock) { this->stock = stock; }
	friend istream& operator >> (istream& ins, Product& p);
	friend ostream& operator << (ostream& stream, const Product& p);
};