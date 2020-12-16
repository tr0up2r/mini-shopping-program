#include <iostream>
using namespace std;

// Product 클래스
/*
	상품 이름과 가격, 재고량을 멤버 변수로 가집니다.
	등록되는 상품들의 재고량은 무조건 100으로 주도록 고정합니다.
	>> 연산자와 << 연산자를 재정의합니다.
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