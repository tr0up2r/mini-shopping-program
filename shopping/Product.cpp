#pragma once
#include <string>
#include <iomanip>
#include "Product.h"

// Product 클래스 객체에 대한 연산자 >> 재정의.
// 쇼핑 관리자 모드에서 새로운 상품을 추가할 때 사용됩니다.
istream& operator >> (istream& ins, Product& p)
{
	cout << "상품 이름 입력 : ";
	getline(ins, p.name);

	if (p.name == "no") // 만약 상품 이름이 no로 입력된다면, 상품 추가 종료.
	{
		cout << "새로운 상품 추가 종료.\n\n";
		return ins;
	}

	cout << "상품 가격 입력 : ";
	ins >> p.price;
	ins.ignore();

	return ins;
}

// Product 클래스 객체에 대한 연산자 << 재정의.
// 상품을 출력하는 print() 함수에서 사용됩니다.
ostream& operator << (ostream& stream, const Product& p) // 연산자 << 재정의.
{
	stream << std::left << "상품명 : " << setw(20) << p.name;
	stream << std::right << " 가격 : " << setw(8) << p.price << "원";
	stream << "  재고/수량 : " << p.stock << "개";
	return stream;
}