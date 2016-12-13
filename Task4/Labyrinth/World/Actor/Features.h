#pragma once

class CStaticFeature// TOOD : see need inheritance for CDynamicFeature
{
public:
	void				SetValue(int setValue);
	void				AddToValue(int summand);

	int					GetValue() const;

private:
	int					m_value;
};

class CDynamicFeature
{
public:
	void				SetValue(int setValue);
	void				AddToValue(int summand);

	int					GetValue() const;

	void				SetMaxValue(int setValue);
	void				AddToMaxValue(int summand);

	int					GetMaxValue() const;
private:
	int					m_value;
	int					m_maxValue;
};
