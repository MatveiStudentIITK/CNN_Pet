#include<iostream>
using namespace std;
struct A abstract
{
	virtual void Func() = 0;
};
struct B : A
{
	void Func() override { cout << "class B" << endl; }
};
struct C : A
{
	void Func() override { cout << "class C" << endl; }
};
int main(const int& Argc, const char* const* const& Args)
{
	A& a = *(new C());
	a.Func();
}