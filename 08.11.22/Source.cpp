#include <windows.h>
#include <tchar.h>
#include "resource.h"
#pragma comment(lib, "comctl32")
#include <CommCtrl.h>

int score = 0;
HWND hButton1, hButton2, hButton3, hButton4, hButton5, hButton6, hButton7, hButton8, hButton9, hButton10, hButton11, hButton12;
HWND hEdit1, hEdit2, hEdit3, hEdit4;
HWND hProg, hResult;
HWND hSpin1, hSpin2, hAnw1, hAnw2;
HANDLE Th1;

UDACCEL pAcceleration[3] = { {1,1}, {3,10}, {5,50} };

TCHAR edit1[20], edit2[20], edit3[20], edit4[20];

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return  DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

DWORD WINAPI Thread1(LPVOID lp)
{
	DWORD prior_thread = GetPriorityClass(GetCurrentThread());
	DWORD prior_proc = GetPriorityClass(GetCurrentProcess());
	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
	int time = 10;
	while (true)
	{
		static _TCHAR str[100];
		wsprintf(str, TEXT("Осталось времени: %d секунд"), time);
		SetWindowText((HWND)lp, str);
		time--;
		Sleep(1000);
		str[lstrlen(str)] = '\0';
		if (time == 0)
			break;
	}
	SetWindowText((HWND)lp, TEXT("Осталось времени: 0 секунд"));
	SetPriorityClass(GetCurrentProcess(), prior_proc);
	SetThreadPriority(GetCurrentThread(), prior_thread);
	MessageBox((HWND)lp, TEXT("Время вышло"), TEXT("Тест"), MB_OK);
	EndDialog((HWND)lp, 0);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	switch (message)
	{
	case WM_INITDIALOG:
		Th1 = CreateThread(NULL, 0, Thread1, hWnd, 0, NULL);
		hButton1 = GetDlgItem(hWnd, IDC_RADIO2);
		hButton2 = GetDlgItem(hWnd, IDC_RADIO5);
		hButton3 = GetDlgItem(hWnd, IDC_RADIO9);
		hButton4 = GetDlgItem(hWnd, IDC_RADIO14);
		hButton5 = GetDlgItem(hWnd, IDC_RADIO17);
		hButton6 = GetDlgItem(hWnd, IDC_RADIO18);
		hButton7 = GetDlgItem(hWnd, IDC_RADIO22);
		hButton8 = GetDlgItem(hWnd, IDC_RADIO23);
		hButton9 = GetDlgItem(hWnd, IDC_CHECK1);
		hButton10 = GetDlgItem(hWnd, IDC_CHECK3);
		hButton11 = GetDlgItem(hWnd, IDC_CHECK4);
		hButton12 = GetDlgItem(hWnd, IDC_CHECK7);
		hEdit1 = GetDlgItem(hWnd, IDC_EDIT1);
		hEdit2 = GetDlgItem(hWnd, IDC_EDIT2);
		hEdit3 = GetDlgItem(hWnd, IDC_EDIT3);
		hEdit4 = GetDlgItem(hWnd, IDC_EDIT4);
		hProg = GetDlgItem(hWnd, IDC_PROGRESS1);
		hResult = GetDlgItem(hWnd, IDC_RESULT);
		hSpin1 = GetDlgItem(hWnd, IDC_SPIN1);
		hSpin2 = GetDlgItem(hWnd, IDC_SPIN2);
		hAnw1 = GetDlgItem(hWnd, IDC_ANSWER1);
		hAnw2 = GetDlgItem(hWnd, IDC_ANSWER2);
		hProg = GetDlgItem(hWnd, IDC_PROGRESS1);
		SendMessage(hProg, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
		SendMessage(hProg, PBM_SETPOS, 0, 0);
		SendMessage(hProg, PBM_SETBKCOLOR, 0, LPARAM(RGB(255, 0, 0)));
		SendMessage(hProg, PBM_SETBARCOLOR, 0, LPARAM(RGB(0, 255, 0)));
		SendMessage(hSpin1, UDM_SETRANGE32, 0, 10000);
		SendMessage(hSpin2, UDM_SETRANGE32, 0, 10000);
		SendMessage(hSpin1, UDM_SETACCEL, 3, LPARAM(pAcceleration));
		SendMessage(hSpin2, UDM_SETACCEL, 3, LPARAM(pAcceleration));
		SendMessage(hSpin1, UDM_SETBUDDY, WPARAM(hAnw1), 0);
		SendMessage(hSpin2, UDM_SETBUDDY, WPARAM(hAnw2), 0);
		SetWindowText(hAnw1, TEXT("0"));
		SetWindowText(hAnw2, TEXT("0"));
		ShowWindow(hProg, SW_HIDE);
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wp) == IDC_BUTTON1)
		{
			TerminateThread(Th1, 0);
			int anw1 = SendMessage(hSpin1, UDM_GETPOS32, 0, 0);
			int anw2 = SendMessage(hSpin2, UDM_GETPOS32, 0, 0);
			LRESULT lResult1 = SendMessage(hButton1, BM_GETCHECK, 0, 0);
			LRESULT lResult2 = SendMessage(hButton2, BM_GETCHECK, 0, 0);
			LRESULT lResult3 = SendMessage(hButton3, BM_GETCHECK, 0, 0);
			LRESULT lResult4 = SendMessage(hButton4, BM_GETCHECK, 0, 0);
			LRESULT lResult5 = SendMessage(hButton5, BM_GETCHECK, 0, 0);
			LRESULT lResult6 = SendMessage(hButton6, BM_GETCHECK, 0, 0);
			LRESULT lResult7 = SendMessage(hButton7, BM_GETCHECK, 0, 0);
			LRESULT lResult8 = SendMessage(hButton8, BM_GETCHECK, 0, 0);
			LRESULT lResult9 = SendMessage(hButton9, BM_GETCHECK, 0, 0);
			LRESULT lResult10 = SendMessage(hButton10, BM_GETCHECK, 0, 0);
			LRESULT lResult11 = SendMessage(hButton11, BM_GETCHECK, 0, 0);
			LRESULT lResult12 = SendMessage(hButton12, BM_GETCHECK, 0, 0);
			GetWindowText(hEdit1, edit1, 20);
			GetWindowText(hEdit2, edit2, 20);
			GetWindowText(hEdit3, edit3, 20);
			GetWindowText(hEdit4, edit4, 20);
			if (lResult1 == BST_CHECKED)
				score += 1;
			if (lResult2 == BST_CHECKED)
				score += 1;
			if (lResult3 == BST_CHECKED)
				score += 1;
			if (lResult4 == BST_CHECKED)
				score += 1;
			if (lResult5 == BST_CHECKED)
				score += 1;
			if (lResult6 == BST_CHECKED)
				score += 1;
			if (lResult7 == BST_CHECKED)
				score += 1;
			if (lResult8 == BST_CHECKED)
				score += 1;
			if (lResult9 == BST_CHECKED && lResult10 == BST_CHECKED)
			{
				LRESULT check1 = SendDlgItemMessage(hWnd, IDC_CHECK2, BM_GETCHECK, 0, 0);
				if (check1 != BST_CHECKED)
					score += 1;
			}
			if (lResult11 == BST_CHECKED && lResult12 == BST_CHECKED)
			{
				LRESULT check1 = SendDlgItemMessage(hWnd, IDC_CHECK5, BM_GETCHECK, 0, 0);
				LRESULT check2 = SendDlgItemMessage(hWnd, IDC_CHECK6, BM_GETCHECK, 0, 0);
				if (check1 != BST_CHECKED && check2 != BST_CHECKED)
					score += 1;
			}
			if (!lstrcmp(edit1,TEXT("Hello world")))
				score += 1;
			if (!lstrcmp(edit2,TEXT("2022")))
				score += 1;
			if (!lstrcmp(edit3,TEXT("Барсик")))
				score += 1;
			if (!lstrcmp(edit4,TEXT("993")))
				score += 1;
			if(anw1 == 5)
				score += 1;
			if(anw2 == 1953)
				score += 1;
			TCHAR buf[50];
			int proc = score * 100 / 16;
			wsprintf(buf, TEXT("Ваша оценка: %d балов"), proc);
			SetWindowText(hResult, buf);
			SendMessage(hProg, PBM_SETPOS, WPARAM(proc), 0);
			ShowWindow(hProg, SW_SHOW);
			score = 0;
		}
		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}