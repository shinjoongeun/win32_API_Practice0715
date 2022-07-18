#pragma once

class Vector
{
public:
	float x;
	float y;

public:
	Vector()
		: x(0.f)
		, y(0.f)
	{

	}

	Vector(float _x, float _y)
		: x(_x), y(_y)
	{

	}

	~Vector(){}
};

typedef Vector Vec;

struct tSelectPen
{
private:
	HDC m_hDC;
	HPEN m_hPrevPen;

public:
	tSelectPen(HDC _dc, HPEN _hPen)
		: m_hDC(_dc)
		, m_hPrevPen(_hPen)
	{
		// SelectObject �Լ��� GDI Object ���� �۾��� �����Ǹ� DC �� ������ ����ϰ� �ִ� GDI Object�� �ڵ� ����, �����ϸ� null ���� ��ȯ.
		m_hPrevPen = (HPEN)SelectObject(m_hDC, _hPen);
	}

	~tSelectPen()
	{
		SelectObject(m_hDC, m_hPrevPen);
	}
};

struct tSelectBrush
{
private:
	HDC m_hDC;
	HBRUSH m_hPrevBrush;

public:
	tSelectBrush(HDC _dc, HBRUSH _hBrush)
		: m_hDC(_dc)
		, m_hPrevBrush(_hBrush)
	{
		m_hPrevBrush = (HBRUSH)SelectObject(m_hDC, _hBrush);
	}

	~tSelectBrush()
	{
		SelectObject(m_hDC, m_hPrevBrush);
	}
};


