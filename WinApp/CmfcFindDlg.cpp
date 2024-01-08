#include "pch.h"
#include "CmfcFindDlg.h"
#include "framework.h"
#include "mfcMemo.h"
#include "mfcMemoDlg.h"
#include "afxdialogex.h"

BEGIN_MESSAGE_MAP(CmfcFindDlg, CDialogEx)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

CmfcFindDlg::CmfcFindDlg() : CDialogEx(IDD_FIND_DIALOG)
{
}

void CmfcFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CmfcFindDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar)
	{
	case VK_RETURN:   //virtual key
		GetDlgItem(ID_EDIT_FIND)->GetWindowText(mStr);
		break;
	case VK_ESCAPE:
		mStr = "";
		break;
	default:
		break;
	}
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CmfcFindDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mStr = "";

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CmfcFindDlg::PreTranslateMessage(MSG* pMsg)   //pMsg는 구조체다 
{
	switch (pMsg->message)
	{
	case WM_KEYDOWN:	
		switch (pMsg->wParam)
		{
		case VK_RETURN:   //virtual key
			GetDlgItem(ID_EDIT_FIND)->GetWindowText(mStr);
			EndDialog(IDOK);  // 현재 Dialog의 return 값을 반환
			break;
		case VK_ESCAPE:
			mStr = "";
			EndDialog(IDCANCEL);
			break;
		default:
			break;
		}
	default:
		break;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
