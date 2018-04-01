// KeyboardPage.cpp : implementation file
//

#include "stdafx.h"
#include "RazerChromaSampleApplication.h"
#include "KeyboardPage.h"
#include "afxdialogex.h"
#include "TutorialDlg.h"
#include "HealthAmmoManaDlg.h"
#include "AlertDlg.h"
#include "CooldownTimerDlg.h"
#include "AmbientEffectDlg.h"


// CKeyboardPage dialog

IMPLEMENT_DYNAMIC(CKeyboardPage, CPropertyPage)

CKeyboardPage::CKeyboardPage()
    : CPropertyPage(CKeyboardPage::IDD)
{

}

CKeyboardPage::~CKeyboardPage()
{
}

void CKeyboardPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
}

BOOL CKeyboardPage::OnInitDialog()
{
    BOOL Result = CPropertyPage::OnInitDialog();

    return Result;
}

BEGIN_MESSAGE_MAP(CKeyboardPage, CPropertyPage)
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_BUTTON_LOADING_ANIMATION, &CKeyboardPage::OnBnClickedButtonLoadingAnimation)
END_MESSAGE_MAP()


// CKeyboardPage message handlers


void CKeyboardPage::OnBnClickedButtonLoadingAnimation()
{
    m_ChromaSDKImpl.PlayLoadingAnimation(1);
}


