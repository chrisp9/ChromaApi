#pragma once

#include "ChromaSDKImpl.h"


// CKeyboardPage dialog

class CKeyboardPage : public CPropertyPage
{
    DECLARE_DYNAMIC(CKeyboardPage)

public:
    CKeyboardPage();
    virtual ~CKeyboardPage();

// Dialog Data
    enum { IDD = IDD_KEYBOARD_PAGE };

private:
    CChromaSDKImpl m_ChromaSDKImpl;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonLoadingAnimation();
};
