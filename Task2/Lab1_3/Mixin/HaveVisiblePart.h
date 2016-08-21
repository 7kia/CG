#pragma once

#include <vector>

class IHaveVisiblePart
{
public:
	virtual ~IHaveVisiblePart() = default;

	virtual void						SetVisible(bool value) = 0;
	virtual void						SetVisible(unsigned index, bool value) = 0;
	virtual bool						GetVisible(unsigned index) const = 0;

	virtual void						CheckVisibleIndex(unsigned index) const = 0;
};


class CHaveVisiblePart : public IHaveVisiblePart
{
public:
	CHaveVisiblePart(size_t size);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void						SetVisible(bool value) override;
	void						SetVisible(unsigned index, bool value) override;
	bool						GetVisible(unsigned index) const override;

protected:
	void						CheckVisibleIndex(unsigned index) const override;
//////////////////////////////////////////////////////////////////////
// Data
protected:
	std::vector<bool>			m_visible;
};
