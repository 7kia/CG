#pragma once

class CDynamicFeature
{
public:
	void				SetValue(int setValue);
	void				AddToValue(int summand);

	int					GetValue() const;

	void				SetMaxValue(int setValue);
	void				AddMaxToValue(int summand);

	int					GetMaxValue() const;
private:
	int					m_value;
	int					m_maxValue;
};
