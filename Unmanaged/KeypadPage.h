#pragma once

#include "ChromaSDKImpl.h"

// CKeypadPage dialog

class CKeypadPage : public CPropertyPage
{
    DECLARE_DYNAMIC(CKeypadPage)

public:
    CKeypadPage();
    virtual ~CKeypadPage();

// Dialog Data
    enum { IDD = IDD_KEYPAD_PAGE };

private:
    CChromaSDKImpl m_ChromaSDKImpl;

private:
    void ShowButtons(UINT DeviceType);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonLoadingAnimation();
};
