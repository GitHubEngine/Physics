#pragma once
#include <cmath>
#include <vector>
using namespace std;
/*class Pend
{
public:
	const double PI = M_PI;
	virtual void Func() = 0;
	// ���������� ������ ��������� ������, ���������� ������
	virtual GetCoord() = 0;
	// �������� ������� ���������
	virtual vector <double> GetSpeed() = 0;
	// �������� ������� ��������
	virtual vector <double> GetA��el() = 0;
	// �������� ������� ���������
	virtual double GetEk() = 0;
	// �������� ������� ������������ �������
	virtual double GetEp() = 0;
	// �������� ������� ��������������� �������
	double GetE();
	// �������� ������� �������


};
*/
class MathPend
{
private:
	const double PI = asin(1.);
	const double convGtoR = PI / 180.;
	const double g = 9.817;
	const double pl = 1.;
	const double Cx = 0.3;
	double M, L, A, W, E, S, Ek, Ep, Dt;
	/*
	M - �����
	L - ������ �� ��������� �� ������ ����
	Cx - ����������� �������� �������������
	A - ������� ���������
	W - ������� ��������
	E - ������� ���������
	S - ������� �����
	Ek - ������� ������������
	Ep - ������� �������������
	Dt - ������� ����������
	*/
public:
	MathPend(double mass, double length, double radius, double start_axis,double start_speed, double dt);
	void Func();
	double GetCoord();
	double GetSpeed();
	double GetA��el();
	double GetEk();
	double GetEp();
	~MathPend();
};