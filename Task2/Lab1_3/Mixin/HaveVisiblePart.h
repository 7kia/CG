#pragma once

#include <vector>

class IHaveVisiblePart
{
public:
	virtual ~IHaveVisiblePart() = default;

	virtual void						SetVisible(bool value) = 0;
	virtual void						SetVisible(size_t index, bool value) = 0;
	virtual bool						GetVisible(size_t index) const = 0;

	virtual void						CheckVisibleIndex(size_t index) const = 0;
};


class CHaveVisiblePart : public IHaveVisiblePart
{
public:
	CHaveVisiblePart(size_t size);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void						SetVisible(bool value) override;
	void						SetVisible(size_t index, bool value) override;
	bool						GetVisible(size_t index) const override;

protected:
	void						CheckVisibleIndex(size_t index) const override;
//////////////////////////////////////////////////////////////////////
// Data
protected:
	std::vector<bool>			m_visible;
};
