#pragma once
#include <string>
#include <iomanip>
#include "Product.h"

// Product Ŭ���� ��ü�� ���� ������ >> ������.
// ���� ������ ��忡�� ���ο� ��ǰ�� �߰��� �� ���˴ϴ�.
istream& operator >> (istream& ins, Product& p)
{
	cout << "��ǰ �̸� �Է� : ";
	getline(ins, p.name);

	if (p.name == "no") // ���� ��ǰ �̸��� no�� �Էµȴٸ�, ��ǰ �߰� ����.
	{
		cout << "���ο� ��ǰ �߰� ����.\n\n";
		return ins;
	}

	cout << "��ǰ ���� �Է� : ";
	ins >> p.price;
	ins.ignore();

	return ins;
}

// Product Ŭ���� ��ü�� ���� ������ << ������.
// ��ǰ�� ����ϴ� print() �Լ����� ���˴ϴ�.
ostream& operator << (ostream& stream, const Product& p) // ������ << ������.
{
	stream << std::left << "��ǰ�� : " << setw(20) << p.name;
	stream << std::right << " ���� : " << setw(8) << p.price << "��";
	stream << "  ���/���� : " << p.stock << "��";
	return stream;
}