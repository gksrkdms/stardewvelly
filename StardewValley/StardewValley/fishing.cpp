#include "stdafx.h"
#include "fishing.h"
#include "player.h"
#include "playerMenu.h"
#include "inven.h"
//0 60/  60 160  / 160 180

HRESULT fishing::init()
{
	// 가로바
	m_pIgaroBar = IMAGEMANAGER->findImage("i_GaroBar");
	// 맥스
	m_pImax = IMAGEMANAGER->findImage("i_Max");
	// 찌
	m_pIzzi = IMAGEMANAGER->findImage("i_Zzi");
	// 플레이어
	m_pIplayer = IMAGEMANAGER->findImage("i_Player");
	// 플레이어 낚시 모션
	m_pIplayerFishing = IMAGEMANAGER->findImage("i_PlayerFishing");
	// 느낌표
	m_pIFeel = IMAGEMANAGER->findImage("i_Feel");
	// 히트
	m_pIhit = IMAGEMANAGER->findImage("i_Hit");
	// 세로 바
	m_pIseroBar = IMAGEMANAGER->findImage("i_SeroBar");
	// 세로 바 뒤에 흰말풍선 배경 l,t
	m_pIwhiteUiLt = IMAGEMANAGER->findImage("i_WhitebarL");
	// 세로 바 뒤에 흰말풍선 배경 r,b
	m_pIwhiteUiRb = IMAGEMANAGER->findImage("i_WhitebarR");
	// 세로 초록색 렉트 바
	m_pIgreenBar = IMAGEMANAGER->findImage("i_GreenBar");
	// 세로 물고기 렉트 바
	m_pIfish = IMAGEMANAGER->findImage("i_moveFish");
	// 낚싯대 릴 감는 레버
	m_pIchoo = IMAGEMANAGER->findImage("i_moveChoo");
	// 낚인 물고기
	m_pIgogi = IMAGEMANAGER->findImage("i_GetFish");


	///플레이어 좌표
	m_fPlayerX = m_pPlayer->getX();
	m_fPlayerY = m_pPlayer->getY();

	m_iPlayerCount = 0;						// 플레이어 프레임 카운트
	m_iPlayerFrameX = 0;					// 플레이어 프레임


	///플레이어가 보는 방향
	//m_PlayerSee =
	//	//PLAYER_BACK; 
	//	//PLAYER_FRONT;
	//	PLAYER_LEFT;
	////PLAYER_RIGHT;


// 가로바 좌표
	m_fGaroBarX = m_fPlayerX - 55;
	m_fGaroBarY = m_fPlayerY - 70;


	// 가로바의 초록섹 렉트 바
	m_fRcX = m_pIgaroBar->getX() + 16 + m_fGaroBarX;
	m_fRcY = m_pIgaroBar->getY() + 12 + m_fGaroBarY;

	m_fRcMaxX = m_pIgaroBar->getWidth() - 20 + m_fGaroBarX;
	m_fRcMinX = m_pIgaroBar->getWidth() - m_pIgaroBar->getWidth();
	m_fRcCurrX = 0 - m_fPlayerX;

	m_rcGaroBar = RectMake(m_fRcX, m_fRcY, m_fRcMinX, m_pIgaroBar->getHeight() - 24);


	// 맥스 
	m_fMaxX = m_fGaroBarX + 50;
	m_fMaxY = m_fGaroBarY - 60;

	// 찌
	m_fZziX = m_fPlayerX - 15;
	m_fZziY = m_fPlayerY;
	m_iZziCount = 0;
	m_iFrameZziX = 0;

	// 느낌표
	m_fFeelX = m_fPlayerX + 27;
	m_fFeelY = m_fPlayerY - 45;
	m_iFeelAlpha = 255;

	// 히트
	m_fHitX = NULL;
	m_fHitY = NULL;
	m_fHitBig = 2; //스칼라



	if (m_pPlayer->getPlayerDir() == PLAYER_LEFT || m_pPlayer->getPlayerDir() == PLAYER_UP)
	{
		m_fSeroBarX = m_fPlayerX + 110;				// 세로 바(틀) 좌표 
		m_fSeroBarY = m_fPlayerY - 200;

		m_fWhiteUiX = m_fPlayerX + 80;				// 흰말풍선 좌표
		m_fWhiteUiY = m_fPlayerY - 230;
		m_fGreenBarX = m_fPlayerX + 180;			//세로 초록 렉트바 좌표
		if (m_pPlayer->getPlayerDir() == PLAYER_LEFT)
			m_iPlayerFrameY = 1;
		if (m_pPlayer->getPlayerDir() == PLAYER_UP)
			m_iPlayerFrameY = 3;
	}

	if (m_pPlayer->getPlayerDir() == PLAYER_RIGHT || m_pPlayer->getPlayerDir() == PLAYER_DOWN)
	{
		m_fSeroBarX = m_fPlayerX - 200;
		m_fSeroBarY = m_fPlayerY - 200;

		m_fWhiteUiX = m_fPlayerX - 210;
		m_fWhiteUiY = m_fPlayerY - 230;
		m_fGreenBarX = m_fPlayerX - 130;
		if (m_pPlayer->getPlayerDir() == PLAYER_DOWN)
			m_iPlayerFrameY = 0;
		if (m_pPlayer->getPlayerDir() == PLAYER_RIGHT)
			m_iPlayerFrameY = 2;
	}

	// 세로 초록 렉트 바
	m_fGreenBarY = m_fPlayerY + 203;				 // 초기값 이고 제일 아래 인 값  // 세로 초록 렉트바 좌표
	m_fGreenMinY = m_fPlayerY - 190;			// 최소값 제일 위 인 값
	m_fGreenCurrY = m_fGreenBarY - 30;			// 현재값
	m_fSpeedGreen = 0;							// 세로 초록 렉트 바 가속도 값

	m_rcGreenBar = RectMakeCenter(m_fGreenBarX, m_fGreenCurrY, 10, 77);    // 세로 초록색 렉트바

	//m_fSeroBarX = m_fPlayerX + 110;
	//m_fSeroBarY = m_fPlayerY - 200;
	//m_fWhiteUiX = m_fPlayerX + 80;
	//m_fWhiteUiY = m_fPlayerY - 230;



	// 오르락 내리락하는 물고기 렉트 바
	m_fFishX = m_fGreenBarX;
	m_fFishY = m_fGreenMinY + 5;
	m_rcFishBar = RectMakeCenter(m_fFishX, m_fFishY, 10, 37);

	//  떨어지면 낚시 끝, 올라가면 획득 하는 렉트 바 
	m_fSrcX = m_fGreenBarX + 65;
	m_fSrcY = m_fGreenBarY + 76;  //76

	m_fSrcWidth = 9;
	m_fSrcHeight = 3;
	m_fSrcCurrY = m_fSrcY;
	m_rcSeroBar = RectMake(m_fSrcX, m_fSrcY, m_fSrcWidth, m_fSrcHeight);

	m_rcSeroBar.top = m_fSrcCurrY - 250;  /// 물고기획득바 초기값  

	m_iLuck = 7;  /// 성공확률 + 해줌
	
	m_iChance = 150; /// 성공확률 1~100
	m_iRandomChance = 0; // 1~100 랜덤숫자 담기는 변수




	//낚싯대 레버
	m_fchooY = m_fGreenBarY;
	m_fchooX = m_fGreenBarX - 68;
	m_iChooFrame = 1;
	m_iChooCount = 0;


	//필렉트 색깔 rgb
	m_r = 255;
	m_g = 0;
	m_b = 0;




	m_BarState = PLUS; // 가로바의 초록렉트 처음상태
	m_BarResult = BAR_NULL1; // 가로바 결과
	m_FishResult = FISHGET_NULL; // 물고기와의 싸움 결과

	// 시간 
	m_fTime = 0;
	m_fTime2 = 0;
	m_fTime3 = 0;
	m_fTime4 = 0;
	m_fTime5 = 0;



	isMaxOn = NULL;	// 맥스이미지
	isOne = false;// 헤더파일 설명
	isTwo = false;
	isThree = false;
	isThrowing = false;
	isFeelClick = false;
	isHitOn = false;
	isGetFish = false;
	isMistake = true; // 함수 내에 스페이스바키를 따로넣어서 마지막에 문제생겨서 만든 불값
	isBring = false;


	return S_OK; //ok
}

void fishing::release()
{
}

void fishing::update()
{
	m_fPlayerX = m_pPlayer->getX();
	m_fPlayerY = m_pPlayer->getY();
	if (isFishing)
	{
		if (isMistake && KEYMANAGER->isStayKeyDown(VK_LBUTTON))  // 처음 시작 시 한번만 실행
		{
			isOne = true;
			isMistake = false;
		}

		fishingOne();
		ifMax();
		ifHit();

		fishingTwo();
		if (isThrowing)
			zziMove();

		fishingThree();
		fishMove();

		fishingFour();
	}
}

void fishing::render(HDC hdc)
{
	/*sprintf_s(m_szText, 128, "%d", (int)m_fGreenMinY);
	TextOut(hdc, 100, 40, m_szText, strlen(m_szText));
	sprintf_s(m_szText, 128, "%d", (int)m_fSrcCurrY);
	TextOut(hdc, 100, 60, m_szText, strlen(m_szText));

	sprintf_s(m_szText, 128, "%d", (int)m_fTime);
	TextOut(hdc, 100, 80, m_szText, strlen(m_szText));
	sprintf_s(m_szText, 128, "%d", (int)m_fTime2);
	TextOut(hdc, 100, 100, m_szText, strlen(m_szText));

	sprintf_s(m_szText, 128, "%d", (int)m_fTime3);
	TextOut(hdc, 100, 120, m_szText, strlen(m_szText));
	sprintf_s(m_szText, 128, "%d", (int)m_fTime4);
	TextOut(hdc, 100, 140, m_szText, strlen(m_szText));*/

	if (isFishing)
	{
		if (isOne == true)
		{
			HBRUSH brush = CreateSolidBrush(RGB(m_r, m_g, m_b)); //색깔브러쉬
			m_pIgaroBar->render(hdc, m_fGaroBarX, m_fGaroBarY); //가로바 
			FillRect(hdc, &m_rcGaroBar, brush);//렉트 색채워줌
			DeleteObject(brush);// 색깔브러쉬 사용후 삭제
		}
		if (isMaxOn == true)
			m_pImax->render(hdc, m_fMaxX, m_fMaxY); // max이미지

		if (isTwo || isThree || isHitOn)
		{
			m_pIzzi->frameRender(hdc, m_fZziX, m_fZziY, m_iFrameZziX, 1); //찌
		}
		if (isGetFish)
		{
			m_pIplayer->frameRender(hdc, m_fPlayerX, m_fPlayerY, m_iPlayerFrameX, m_iPlayerFrameY); //플레이어
		}
		else
		{
			m_pIplayerFishing->frameRender(hdc, m_fPlayerX - 55, m_fPlayerY - 30, m_iPlayerFrameX, m_iPlayerFrameY);
		}
		if (isHitOn == true)
			m_pIhit->render(hdc, m_fHitX, m_fHitY, m_fHitBig); //히트

		if (isFeelClick == true && m_iFeelAlpha > 0)
			m_pIFeel->alphaRender(hdc, m_fFeelX, m_fFeelY, m_iFeelAlpha); //느낌표


		if (isThree)
		{
			if (m_pPlayer->getPlayerDir() == PLAYER_LEFT || m_pPlayer->getPlayerDir() == PLAYER_UP)
			{
				m_pIwhiteUiLt->alphaRender(hdc, m_fWhiteUiX, m_fWhiteUiY, 170);
				m_pIseroBar->render(hdc, m_fSeroBarX, m_fSeroBarY);
			}
			if (m_pPlayer->getPlayerDir() == PLAYER_RIGHT || m_pPlayer->getPlayerDir() == PLAYER_DOWN)
			{
				m_pIwhiteUiRb->alphaRender(hdc, m_fWhiteUiX, m_fWhiteUiY, 170);
				m_pIseroBar->render(hdc, m_fSeroBarX, m_fSeroBarY);
			}
			m_pIgreenBar->render(hdc, m_fGreenBarX, m_fGreenCurrY);
			m_pIfish->render(hdc, m_fFishX, m_fFishY);
			m_pIchoo->frameRender(hdc, m_fchooX, m_fchooY, m_iChooFrame, 1);

			HBRUSH brush = CreateSolidBrush(RGB(m_r, m_g, m_b)); //색깔브러쉬
			FillRect(hdc, &m_rcSeroBar, brush);
			DeleteObject(brush);
			//Rectangle(hdc, m_fFishX + 1, m_fFishY, m_fFishX + 10, m_fFishY + 37);
			//Rectangle(hdc, m_fGreenBarX, m_fGreenCurrY, m_fGreenBarX + 10, m_fGreenCurrY + 77);		
		}

		if (m_FishResult == GET_FISH)
		{
			m_pIgogi->frameRender(hdc, m_fZziX, m_fZziY, 0, 0); //낚인고기
		}
		else if (m_FishResult == MISS_FISH)
			m_pIplayer->frameRender(hdc, m_fZziX + 50, m_fZziY + 100, 2, 0);
	}
}
// 가로 바
void fishing::fishingOne()
{
	if (isOne == true)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))  // space 클릭 을 마우스 클릭으로 바꿔야한다 >> 버튼 누르고 있으면 가로 게이지바 상승,하락
		{

			m_iPlayerCount++;
			if (m_iPlayerCount % 10 == 1)
				m_fPlayerY += 2;
			if (m_iPlayerCount % 5 == 0)
				m_fPlayerY -= 1;


			if (m_BarState == PLUS)
			{
				m_fRcCurrX = m_rcGaroBar.right += 3.f;
			}
			else if (m_BarState == MINUS)
			{
				m_fRcCurrX = m_rcGaroBar.right -= 2.8f;
			}

			if (m_rcGaroBar.right >= m_fRcMaxX - 1)
			{
				m_BarState = MINUS;
			}
			if (m_rcGaroBar.right < m_fGaroBarX + 16)
			{
				m_BarState = PLUS;
			}

		}

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{

			m_BarState = STOP;

		}

		if (m_BarState == STOP)
		{

			if (m_fRcCurrX - m_fGaroBarX >= 170)
			{
				m_BarResult = GREEN;
			}
			else if (m_fRcCurrX - m_fGaroBarX < 170 && m_fRcCurrX - m_fGaroBarX >= 60)
			{
				m_BarResult = YELLOW;
			}
			else if (m_fRcCurrX - m_fGaroBarX < 60)
			{
				m_BarResult = RED;
			}
		}

		if (m_BarState == STOP)
		{
			m_fTime2 += TIMEMANAGER->getElapsedTime();

			if (m_fTime2 > 0.5f)
			{
				if (m_fTime2 < 0.6f)
					m_iPlayerFrameX = 1;
				if (m_fTime2 < 0.8f)
					m_iPlayerFrameX = 2;
				if (m_fTime2 < 0.9f)
					m_iPlayerFrameX = 3;
				m_fTime2 = 0;
				isOne = false;
				isTwo = true;
			}
		}

		//게이지바 색깔
		if (m_fRcCurrX - m_fGaroBarX >= 160) // 움직이는 렉트의값이 140보다 크면 초록색으로표시
		{
			m_r = 0; m_g = 220; m_b = 0;
		}
		else if ((m_fRcCurrX - m_fGaroBarX) >= 130 && m_fRcCurrX - m_fGaroBarX < 160) //연두
		{
			m_r = 0; m_g = 255;	m_b = 0;
		}
		else if (m_fRcCurrX - m_fGaroBarX >= 80 && m_fRcCurrX - m_fGaroBarX < 130)  // 움직이는 렉트의값 70보다크고 140보다작으면 노랑
		{
			m_r = 255;	m_g = 255;	m_b = 0;
		}
		else if (m_fRcCurrX - m_fGaroBarX >= 60 && m_fRcCurrX - m_fGaroBarX < 80) //주
		{
			m_r = 255;	m_g = 128;	m_b = 0;
		}
		else if (m_fRcCurrX - m_fGaroBarX < 60) //빨
		{
			m_r = 255;	m_g = 0;	m_b = 0;
		}
	}
}

// 가로게이지바 오른쪾 끝에 맞추면 맥스 뜸
void fishing::ifMax()
{
	if (m_fRcCurrX - m_fGaroBarX >= 170 && m_BarState == STOP) // 맥스수치맞추면 맥스표시+맥스이미지 움직이고사라짐
	{
		isMaxOn = true;

		if (m_fTime <= 0.2f)
		{
			m_fMaxY -= 8.f;

		}
		if (m_fTime > 0.2f && m_fTime <= 0.4f)
		{
			m_fMaxY += 7.f;
		}
		if (m_fTime > 0.4f && m_fTime <= 0.6f)
		{
			m_fMaxY += 10.f;
		}
		if (m_fTime > 0.6f)
		{
			isMaxOn = false;
		}
	}
	if (isMaxOn)
	{
		m_fTime += TIMEMANAGER->getElapsedTime();
		if (m_fTime > 3.f)
		{
			m_fTime = 0;
			return;
		}
	}
}

// 느낌표 상태일떄 누르면 히트
void fishing::ifHit()
{
	if (isHitOn == true)
	{

		m_fTime3 += TIMEMANAGER->getElapsedTime();
		if (m_fTime3 < 0.1f)
		{
			m_fHitY -= 4;
			m_fHitBig = 3;
		}

		if (m_fTime3 > 0.2f && m_fTime3 < 0.3f)
		{
			m_fHitBig = 2;

		}
		if (m_fTime3 > 0.5f)
		{
			isThree = true;
			isHitOn = false;
		}


	}
}

// 물고기 물떄까지 기다리고 물면 누름
void fishing::fishingTwo()
{
	if (isOne == false && isTwo == true)
	{
		if (m_BarResult == RED)
		{
			
			isFishing = false;
			m_pPlayer->setPlayerState(PLAYER_PLAY);
			return;
		}

		if (m_BarResult == YELLOW || m_BarResult == GREEN)
		{
			if (isThrowing == false)
				zziThrow();

			m_fTime4 += TIMEMANAGER->getElapsedTime();

			if (m_fTime4 < 0.1f)
				m_iRandomChance = RANDOM->getFromIntTo(1, 100);

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (isFeelClick == true)
				{
					m_fHitX = m_fZziX + 30;
					m_fHitY = m_fZziY;
					isHitOn = true;

					m_iFeelAlpha = 0;
					m_fTime4 = 0;
					isTwo = false;
					
					return;
				}
				else
				{
					isFishing = false;
					m_pPlayer->setPlayerState(PLAYER_PLAY);
					return;
				}
			}

			if (m_iRandomChance - m_iLuck <= m_iChance && m_fTime4 >= 3.f)  // 물고기가 걸린경우
			{
				isFeelClick = true;

				if (isFeelClick == true && m_fTime4 <= 4.0f)
				{
					m_iFeelAlpha -= 3;
				}
				else if (m_fTime4 > 4.0f) // 못누른경우
				{

					m_fTime4 = 0;
					m_iRandomChance = 0;
					m_iFeelAlpha = 255;
					isFeelClick = false;
					return;
				}
			}
			else if (m_fTime4 >= 3.f && m_iRandomChance - m_iLuck > m_iChance)	// 걸리지 않은 경우
			{
				m_fTime4 = 0;
				m_iRandomChance = 0;
				return;
			}
		}
	}
}

//찌던짐
void fishing::zziThrow()
{
	m_iFrameZziX = 1;

	if (m_pPlayer->getPlayerDir() == PLAYER_DOWN)//앞을보고있을떄
	{
		m_fTime3 += TIMEMANAGER->getElapsedTime();
		if (m_fTime3 < 0.1f)
		{
			m_fZziX -= 5.f;
			m_fZziY += 10.f;
		}
		else if (m_fTime3 < 0.2f)
		{
			m_fZziY += 10.f;
		}
		else if (m_fTime3 < 0.3f)
		{
			m_fZziX += 8.f;
			m_fZziY += 15.f;
		}
		if (m_fTime3 > 0.4f && m_fTime3 < 0.6f)
		{
			m_fZziY += 0.7f;
		}
		else if (m_fTime3 > 0.7f && m_fTime3 < 1.2f)
		{
			m_fZziY -= 0.2f;
		}
	}
	else if (m_pPlayer->getPlayerDir() == PLAYER_UP)//뒤
	{

		m_fTime3 += TIMEMANAGER->getElapsedTime();
		if (m_fTime3 < 0.1f)
		{
			m_fZziX += 10.f;
			m_fZziY -= 10.f;
		}
		else if (m_fTime3 < 0.2f)
		{
			m_fZziY -= 10.f;
		}
		else if (m_fTime3 < 0.3f)
		{
			m_fZziX -= 5.f;
			m_fZziY -= 15.f;
		}
		if (m_fTime3 > 0.4f && m_fTime3 < 0.6f)
		{
			m_fZziY += 0.7f;
		}
		else if (m_fTime3 > 0.7f && m_fTime3 < 1.2f)
		{
			m_fZziY -= 0.2f;
		}
	}
	else if (m_pPlayer->getPlayerDir() == PLAYER_LEFT)//왼
	{
		m_fTime3 += TIMEMANAGER->getElapsedTime();
		if (m_fTime3 < 0.1f)
		{
			m_fZziX -= 5.f;
			m_fZziY -= 10.f;
		}
		else if (m_fTime3 < 0.2f)
		{
			m_fZziX -= 10.f;
			m_fZziY -= 10.f;
		}
		else if (m_fTime3 < 0.3f)
		{
			m_fZziX -= 20.f;
			m_fZziY += 35.f;
		}
		if (m_fTime3 > 0.4f && m_fTime3 < 0.6f)
		{
			m_fZziY += 0.7f;
		}
		else if (m_fTime3 > 0.7f && m_fTime3 < 1.2f)
		{
			m_fZziY -= 0.2f;
		}
	}
	else if (m_pPlayer->getPlayerDir() == PLAYER_RIGHT)//오
	{
		m_fTime3 += TIMEMANAGER->getElapsedTime();
		if (m_fTime3 < 0.1f)
		{
			m_fZziX += 5.f;
			m_fZziY -= 10.f;
		}
		else if (m_fTime3 < 0.2f)
		{
			m_fZziX += 10.f;
			m_fZziY -= 10.f;
		}
		else if (m_fTime3 < 0.3f)
		{
			m_fZziX += 23.f;
			m_fZziY += 35.f;
		}
		if (m_fTime3 > 0.4f && m_fTime3 < 0.6f)
		{
			m_fZziY += 0.7f;
		}
		else if (m_fTime3 > 0.7f && m_fTime3 < 1.2f)
		{
			m_fZziY -= 0.2f;
		}

	}
	if (m_fTime3 > 1.5f)
	{
		isThrowing = true;

		m_fTime3 = 0;
	}
}

// 찌 둥둥떠다니는움직임
void fishing::zziMove()
{
	m_iZziCount++;
	if (m_iZziCount % 100 == 1)
	{
		m_fZziY += 2.4f;
		m_iFrameZziX = 2;
	}
	if (m_iZziCount % 50 == 0)
	{
		m_fZziY -= 1.2f;
		m_iFrameZziX = 1;
	}
}

//세로 바
void fishing::fishingThree() // 물고기랑 싸움 시작
{
	if (isTwo == false && isThree == true)
	{
		if (m_fGreenCurrY >= m_fGreenMinY && m_fGreenCurrY <= m_fGreenBarY)
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))// 누르고있으면 증가해야하고
			{
				m_fGreenCurrY -= 12;
				m_fSpeedGreen -= 0.3;
				m_fGreenCurrY += m_fSpeedGreen;

				m_iChooCount++;
				if (m_iChooCount % 4 == 1)
				{
					m_iChooFrame++;
					if (m_iChooFrame > 3)
						m_iChooFrame = 0;
				}
			}
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			{
				m_iChooCount = 0;
				m_fSpeedGreen = 0;
			}
			else
				m_fGreenCurrY += 8; // 떼면 감소해야한다

		}
		if (m_fGreenCurrY >= m_fGreenBarY)
		{
			m_fGreenCurrY = m_fGreenBarY;
		}
		if (m_fGreenCurrY <= m_fGreenMinY)
		{
			m_fGreenCurrY = m_fGreenMinY;
		}
		////////
		m_rcFishBar = RectMake(m_fFishX, m_fFishY, 10, 37);
		m_rcGreenBar = RectMake(m_fGreenBarX, m_fGreenCurrY, 10, 77);
		if (m_fSrcCurrY <= m_fGreenBarY + 76 && m_fSrcCurrY >= m_fGreenMinY)
		{
			RECT rc;
			if (IntersectRect(&rc, &m_rcFishBar, &m_rcGreenBar))
			{
				m_fSrcCurrY = m_rcSeroBar.top -= 5;
			}

			m_fSrcCurrY = m_rcSeroBar.top += 2;

		}

		if (m_rcSeroBar.top >= m_fGreenBarY + 76)
		{
			m_fSrcCurrY = m_rcSeroBar.top = m_fGreenBarY + 76;
		}
		if (m_rcSeroBar.top <= m_fGreenMinY)
		{
			m_fSrcCurrY = m_rcSeroBar.top = m_fGreenMinY;
		}

		//게이지바 색깔
		if (m_fSrcCurrY - m_fGreenMinY >= 340) // 움직이는 렉트의값이 140보다 크면 빨
		{
			m_r = 255;	m_g = 0;	m_b = 0;
			if (m_fSrcCurrY - m_fGreenMinY >= 469)
				m_FishResult = MISS_FISH;
		}
		else if ((m_fSrcCurrY - m_fGreenMinY) >= 210 && m_fSrcCurrY - m_fGreenMinY < 340) //주
		{
			m_r = 255;	m_g = 128;	m_b = 0;
		}
		else if (m_fSrcCurrY - m_fGreenMinY >= 100 && m_fSrcCurrY - m_fGreenMinY < 210)  // 노
		{
			m_r = 255;	m_g = 255;	m_b = 0;
		}
		else if (m_fSrcCurrY - m_fGreenMinY >= 50 && m_fSrcCurrY - m_fGreenMinY < 100) //연
		{
			m_r = 0; m_g = 255;	m_b = 0;
		}
		else if (m_fSrcCurrY - m_fGreenMinY < 50) //파
		{
			m_r = 0; m_g = 220; m_b = 0;

			if (m_fSrcCurrY - m_fGreenMinY <= 0)
				m_FishResult = GET_FISH;
		}


		if (m_FishResult == GET_FISH)
		{
			isGetFish = true;

		}

		else if (m_FishResult == MISS_FISH)
		{

			//this->init();
			isFishing = false;
			m_pPlayer->setPlayerState(PLAYER_PLAY);
			return;
		}
	}

}

//물고기 랜덤움직임
void fishing::fishMove()
{
	if (isThree)
	{
		if (m_fFishY >= m_fGreenMinY + 5 && m_fFishY <= m_fGreenBarY + 31)
		{
			m_fTime2 += TIMEMANAGER->getElapsedTime();
			if (m_fTime2 < 0.1f)
			{
				m_iFishMove = RANDOM->getFromIntTo(1, 6);
			}

			if (m_fTime2 < 0.5f)
			{
				m_iPlayerCount++;
				if (m_iPlayerCount % 10 == 1)
					m_fPlayerY += 2;
				if (m_iPlayerCount % 5 == 0)
					m_fPlayerY -= 1;
				switch (m_iFishMove)
				{
				case 1:
					m_fFishY += 2;
					break;
				case 2:
					m_fFishY -= 2;
					break;
				case 3:
					m_fFishY += 10;
					break;
				case 4:
					m_fFishY -= 10;
					break;
				case 5:
					m_fFishY -= 4;
					break;
				case 6:
					m_fFishY += 4;
					break;
				default:
					break;
				}
			}
			else if (m_fTime2 > 0.5f)
			{
				m_fTime2 = 0;
			}

		}
		if (m_fFishY >= m_fGreenBarY + 31)
		{
			m_fFishY = m_fGreenBarY + 31;
		}
		if (m_fFishY <= m_fGreenMinY + 5)
		{
			m_fFishY = m_fGreenMinY + 5;
		}
	}
}

// 물고기를 잡은 경우
void fishing::fishingFour()
{
	if (isGetFish)
	{
		m_iPlayerFrameY = 0;
		m_iPlayerFrameX = 4;
		isOne = false;
		isTwo = false;
		isThree = false;
		m_fTime2 += TIMEMANAGER->getElapsedTime();

		if (!isBring)
			fishBring();
		if (m_fTime2 > 0.7f && m_fTime2 < 0.8f)
		{
			isBring = true;
			
		
		}
		
		if (m_fTime2 > 2.5f)
		{
			m_fTime2 = 0;
		
			m_pPlayer->getPlayerMenu()->getInven()->addItem(101);

			isFishing = false;
			m_pPlayer->setPlayerState(PLAYER_PLAY);
			return;
		}
	
	}

}

// 플레이어가 보는 방향에 따라 모션 정해주고 시간 받아서 낚인 물고기를 플레이어에게 이동하는 함수
void fishing::fishBring()
{

	m_fTime3 += TIMEMANAGER->getElapsedTime();
	if (m_pPlayer->getPlayerDir() == PLAYER_DOWN)//앞을보고있을떄
	{

		if (m_fTime3 < 0.1f)
		{
			m_fZziX += 5.f;
			m_fZziY -= 10.f;
		}
		else if (m_fTime3 < 0.2f)
		{
			m_fZziY -= 10.f;
		}
		else if (m_fTime3 < 0.3f)
		{
			m_fZziX -= 8.f;
			m_fZziY -= 15.f;
		}
		if (m_fTime3 > 0.4f && m_fTime3 < 0.4f)
		{
			m_fZziY -= 0.7f;
		}
		else if (m_fTime3 > 0.4f && m_fTime3 < 0.5f)
		{
			m_fZziY += 0.2f;
		}
	}
	else if (m_pPlayer->getPlayerDir() == PLAYER_UP)//뒤
	{

		if (m_fTime3 < 0.1f)
		{
			m_fZziX -= 10.f;
			m_fZziY += 10.f;
		}
		else if (m_fTime3 < 0.2f)
		{
			m_fZziY += 10.f;
		}
		else if (m_fTime3 < 0.3f)
		{
			m_fZziX += 5.f;
			m_fZziY += 15.f;
		}
		if (m_fTime3 > 0.4f && m_fTime3 < 0.4f)
		{
			m_fZziY -= 0.7f;
		}
		else if (m_fTime3 > 0.4f && m_fTime3 < 0.5f)
		{
			m_fZziY += 0.2f;
		}
	}
	else if (m_pPlayer->getPlayerDir() == PLAYER_LEFT)//왼
	{

		if (m_fTime3 < 0.1f)
		{
			m_fZziX += 5.f;
			m_fZziY += 10.f;
		}
		else if (m_fTime3 < 0.2f)
		{
			m_fZziX += 10.f;
			m_fZziY += 10.f;
		}
		else if (m_fTime3 < 0.3f)
		{
			m_fZziX += 20.f;
			m_fZziY -= 35.f;
		}
		if (m_fTime3 > 0.4f && m_fTime3 < 0.4f)
		{
			m_fZziY -= 0.7f;
		}
		else if (m_fTime3 > 0.4f && m_fTime3 < 0.5f)
		{
			m_fZziY += 0.2f;
		}

	}
	else if (m_pPlayer->getPlayerDir() == PLAYER_RIGHT)//오
	{

		if (m_fTime3 < 0.1f)
		{
			m_fZziX -= 5.f;
			m_fZziY += 10.f;
		}
		else if (m_fTime3 < 0.2f)
		{
			m_fZziX -= 10.f;
			m_fZziY += 10.f;
		}
		else if (m_fTime3 < 0.3f)
		{
			m_fZziX -= 23.f;
			m_fZziY -= 35.f;
		}
		if (m_fTime3 > 0.4f && m_fTime3 < 0.4f)
		{
			m_fZziY -= 0.7f;
		}
		else if (m_fTime3 > 0.4f && m_fTime3 < 0.5f)
		{
			m_fZziY += 0.2f;
		}

	}

	if (m_fTime3 > 0.6f)
	{
		m_fTime3 = 0;
	
	}


}



fishing::fishing()
{
}


fishing::~fishing()
{
}
