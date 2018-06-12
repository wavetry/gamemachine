﻿#ifndef __GMCONTROLTEXTEDIT_H__
#define __GMCONTROLTEXTEDIT_H__
#include <gmcommon.h>
#include <gmcontrols.h>
BEGIN_NS

class GMUniBuffer;

GM_PRIVATE_OBJECT(GMControlTextEdit)
{
	GMVec4 textColor = GMVec4(0, 0, 0, 1);
	GMVec4 selectionTextColor = GMVec4(0, 0, 0, 1);
	GMVec4 selectionBackColor = GMVec4(0, 0, 0, 1);
	GMVec4 caretColor = GMVec4(0, 0, 0, 1);
	GMint cp = 0;
	GMint firstVisibleCP = 0;
	GMint selectionStartCP = 0;
	GMUniBuffer* buffer = nullptr;
	GMRect rcText;
	GMStyle textStyle;
	GMControlBorder* borderControl = nullptr;
	GMint borderWidth = 5;
	GMfloat lastBlink = 0;
	GMfloat deltaBlink = .5f;
	bool caretOn = true;
	bool showCaret = true;
	bool insertMode = true;
};

class GMControlTextEdit : public GMControl
{
	GM_DECLARE_PRIVATE(GMControlTextEdit)

public:
	GM_DECLARE_SIGNAL(textChanged);

public:
	GMControlTextEdit(GMWidget* widget);
	~GMControlTextEdit();

public:
	virtual void render(GMfloat elapsed) override;
	virtual void setSize(GMint width, GMint height) override;
	virtual void setPosition(GMint x, GMint y) override;
	virtual bool onKeyDown(GMSystemKeyEvent* event) override;
	virtual bool onChar(GMSystemCharEvent* event) override;
	virtual bool canHaveFocus() override;
	virtual void setText(const GMString& text);

protected:
	virtual void renderCaret(GMint firstX, GMint caretX);

protected:
	void placeCaret(GMint cP);
	void moveCaret(bool next, bool newItem, bool select);
	void deleteSelectionText();
	void resetCaretBlink();
	void copyToClipboard();
	void pasteFromClipboard();

public:
	inline GMControlBorder* getBorder()
	{
		D(d);
		return d->borderControl;
	}

	inline void setBorderWidth(GMint width)
	{
		D(d);
		d->borderWidth = width;
	}

	inline void setShowCaret(bool showCaret)
	{
		D(d);
		d->showCaret = showCaret;
	}

	inline void setCaretBlinkSpeed(GMfloat blinkSpeedSecond)
	{
		D(d);
		d->deltaBlink = blinkSpeedSecond;
	}

protected:
	virtual void initStyles() override;
	virtual void updateRect() override;
};

END_NS
#endif