#include "Framework.h"
#include "String.h"

#include <iomanip>	// ����� ��Ʈ���� �����ڸ� �����ϴ� ���, ��Ʈ���� ��� ������ �����ϴ� �� ���
#include <sstream>	// ���ڿ� ��Ʈ���� ����, �޸� ���ۿ� �����͸� �а� ���µ� ���

// ���ڿ��� ������ �����ڷ� �����ϴ� ��� ���ڿ� �ڸ��� ��� (��κ� �����̳� ������ �̿� ���� �ı�)����
#pragma region SplitString
void String::SplitString(vector<string>* result, string origin, string tok)
{
	result->clear();
	int cutAt = 0; //�ڸ� ��ġ
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //�ڸ��� ��ġ�� 0���� ũ�ٸ�
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) //�ڸ��� �������� �ִٸ�
		result->push_back(origin.substr(0, cutAt));
}

void String::SplitString(vector<wstring>* result, wstring origin, wstring tok)
{
	result->clear();

	int cutAt = 0; //�ڸ� ��ġ
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //�ڸ��� ��ġ�� 0���� ũ�ٸ�
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) //�ڸ��� �������� �մٸ�
		result->push_back(origin.substr(0, cutAt));
}
#pragma endregion

// Ư���� ���ڷ� �����ϴ��� üũ
#pragma region StartWith
bool String::StartWith(string str, string comp)
{
	//npos no position �� ���ٴ� �Ҹ�
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && (int)index == 0)
		return true;

	return false;
}

bool String::StartWith(wstring str, wstring comp)
{
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && (int)index == 0)
		return true;
	return false;
}
#pragma endregion

// Ư���� ���ڸ� �����ϴ��� üũ 
//���ۺ��� �̰� �� ���� ��
#pragma region Contain
bool String::Contain(string str, string comp)
{
	size_t found = str.find(comp);

	return found != wstring::npos;
}

bool String::Contain(wstring str, wstring comp)
{
	size_t found = str.find(comp);

	return found != wstring::npos;
}
#pragma endregion

// Ư���� ���ڵ��� �ٸ� ���ڵ�� ��ü
// �Ŀ����� �Ƹ� ������ ���־����� �츮�� �׳� �������� ��� �̰� ȥ���ϴ� ���� �ȳ��� �ٱ��ִµ��� ��ɵ� �ʿ���
#pragma region Replace
void String::Replace(string* str, string comp, string rep)
{
	string temp = *str;

	size_t startPos = 0;
	while ((startPos = temp.find(comp, startPos)) != wstring::npos)
	{
		temp.replace(startPos, comp.length(), rep);
		startPos += rep.length();
	}

	*str = temp;
}

void String::Replace(wstring* str, wstring comp, wstring rep)
{
	wstring temp = *str;

	size_t startPos = 0;
	while ((startPos = temp.find(comp, startPos)) != wstring::npos)
	{
		temp.replace(startPos, comp.length(), rep);
		startPos += rep.length();
	}

	*str = temp;
}
#pragma endregion

// ���͸� ���ڿ��� �ٲ㼭 ���
#pragma region ToString
// setprecision : �ε� �Ҽ��� ������ ���е��� �����ϴ� ������

string String::ToString(D3DXVECTOR3 vec3, int precision)
{
	string temp;
	stringstream stream1, stream2, stream3;
	stream1 << fixed << setprecision(precision) << vec3.x;
	stream2 << fixed << setprecision(precision) << vec3.y;
	stream3 << fixed << setprecision(precision) << vec3.z;
	temp = "X : " + stream1.str() + " Y : " + stream2.str()
		 + " Z : " + stream3.str();
	return temp;
}

wstring String::ToWstring(D3DXVECTOR3 vec3, int precision)
{
	wstring temp;
	wstringstream stream1, stream2, stream3;
	stream1 << fixed << setprecision(precision) << vec3.x;
	stream2 << fixed << setprecision(precision) << vec3.y;
	stream3 << fixed << setprecision(precision) << vec3.z;
	temp = L"X : " + stream1.str() + L" Y : " + stream2.str()
		 + L" Z : " + stream3.str();
	return temp;
}
#pragma endregion

// string -> wstring
// ���ο��� �ٱ� �ǳ��༭ �ܺ� �Լ����� ����Ҷ� �� �ȵǴ°�쵵 ����
wstring String::ToWstring(string str)
{
	wstring temp = L"";
	temp.assign(str.begin(), str.end());
	return temp;
}

// wstring -> string
string String::ToString(wstring str)
{
	string temp = "";
	temp.assign(str.begin(), str.end());
	return temp;
}