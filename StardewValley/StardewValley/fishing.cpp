#include "stdafx.h"
#include "fishing.h"
#include "player.h"
#include "playerMenu.h"
#include "inven.h"
//0 60/  60 160  / 160 180



HRESULT fishing::init()
{
	addImage();
	// ���ι�
	m_pIgaroBar = IMAGEMANAGER->findImage("i_GaroBar");
	// �ƽ�
	m_pImax = IMAGEMANAGER->findImage("i_Max");
	// ��
	m_pIzzi = IMAGEMANAGER->findImage("i_Zzi");
	// �÷��̾�
	m_pIplayer = IMAGEMANAGER->findImage("i_Player");
	// �÷��̾� ���� ���
	m_pIplayerFishing = IMAGEMANAGER->findImage("i_PlayerFishing");
	// ����ǥ
	m_pIFeel = IMAGEMANAGER->findImage("i_Feel");
	// ��Ʈ
	m_pIhit = IMAGEMANAGER->findImage("i_Hit");
	// ���� ��
	m_pIseroBar = IMAGEMANAGER->findImage("i_SeroBar");
	// ���� �� �ڿ� ��ǳ�� ��� l,t
	m_pIwhiteUiLt = IMAGEMANAGER->findImage("i_WhitebarL");
	// ���� �� �ڿ� ��ǳ�� ��� r,b
	m_pIwhiteUiRb = IMAGEMANAGER->findImage("i_WhitebarR");
	// ���� �ʷϻ� ��Ʈ ��
	m_pIgreenBar = IMAGEMANAGER->findImage("i_GreenBar");
	// ���� ����� ��Ʈ ��
	m_pIfish = IMAGEMANAGER->findImage("i_moveFish");
	// ���˴� �� ���� ����
	m_pIchoo = IMAGEMANAGER->findImage("i_moveChoo");
	// ���� �����
	m_pIgogi = IMAGEMANAGER->findImage("i_GetFish");
	// ��������� �˸���
	m_pIboard = IMAGEMANAGER->findImage("i_NoticeBoard");
	
	addSound();

	///�÷��̾� ��ǥ
	m_fPlayerX = m_pPlayer->getX() - CAMERA->getX();
	m_fPlayerY = m_pPlayer->getY() - CAMERA->getY();

	m_iPlayerCount = 0;						// �÷��̾� ������ ī��Ʈ
	m_iPlayerFrameX = 0;					// �÷��̾� ������


	///�÷��̾ ���� ����
	//m_PlayerSee =
	//	//PLAYER_BACK; 
	//	//PLAYER_FRONT;
	//	PLAYER_LEFT;
	////PLAYER_RIGHT;


// ���ι� ��ǥ
	m_fGaroBarX = m_fPlayerX - 55;
	m_fGaroBarY = m_fPlayerY - 70;


	// ���ι��� �ʷϼ� ��Ʈ ��
	m_fRcX = m_pIgaroBar->getX() + 16 + m_fGaroBarX;
	m_fRcY = m_pIgaroBar->getY() + 12 + m_fGaroBarY;

	m_fRcMaxX = m_pIgaroBar->getWidth() - 20 + m_fGaroBarX;
	m_fRcMinX = m_pIgaroBar->getWidth() - m_pIgaroBar->getWidth();
	m_fRcCurrX = 0 - m_fPlayerX;

	m_rcGaroBar = RectMake(m_fRcX, m_fRcY, m_fRcMinX, m_pIgaroBar->getHeight() - 24);


	// �ƽ� 
	m_fMaxX = m_fGaroBarX + 50;
	m_fMaxY = m_fGaroBarY - 60;

	// ��
	m_fZziX = m_fPlayerX - 15;
	m_fZziY = m_fPlayerY;
	m_iZziCount = 0;
	m_iFrameZziX = 0;
	m_fZziDistance = 100;
	// ����ǥ
	m_fFeelX = m_fPlayerX + 30;
	m_fFeelY = m_fPlayerY - 50;
	m_iFeelAlpha = 255;

	// ��Ʈ
	m_fHitX = NULL;
	m_fHitY = NULL;
	m_fHitBig = 2; //��Į��

	//����� ����
	m_fFishLong = 0;

	if (m_pPlayer->getPlayerDir() == PLAYER_LEFT || m_pPlayer->getPlayerDir() == PLAYER_UP)
	{
		m_fSeroBarX = m_fPlayerX + 110;				// ���� ��(Ʋ) ��ǥ 
		m_fSeroBarY = m_fPlayerY - 200;

		m_fWhiteUiX = m_fPlayerX + 80;				// ��ǳ�� ��ǥ
		m_fWhiteUiY = m_fPlayerY - 230;
		m_fGreenBarX = m_fPlayerX + 180;			//���� �ʷ� ��Ʈ�� ��ǥ
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

	// ���� �ʷ� ��Ʈ ��
	m_fGreenBarY = m_fPlayerY + 203;				 // �ʱⰪ �̰� ���� �Ʒ� �� ��  // ���� �ʷ� ��Ʈ�� ��ǥ
	m_fGreenMinY = m_fPlayerY - 190;			// �ּҰ� ���� �� �� ��
	m_fGreenCurrY = m_fGreenBarY - 30;			// ���簪
	m_fSpeedGreen = 0;							// ���� �ʷ� ��Ʈ �� ���ӵ� ��

	m_rcGreenBar = RectMakeCenter(m_fGreenBarX, m_fGreenCurrY, 10, 77);    // ���� �ʷϻ� ��Ʈ��

	//m_fSeroBarX = m_fPlayerX + 110;
	//m_fSeroBarY = m_fPlayerY - 200;
	//m_fWhiteUiX = m_fPlayerX + 80;
	//m_fWhiteUiY = m_fPlayerY - 230;



	// ������ �������ϴ� ����� ��Ʈ ��
	m_fFishX = m_fGreenBarX;
	m_fFishY = m_fGreenMinY + 5;
	m_rcFishBar = RectMakeCenter(m_fFishX, m_fFishY, 10, 37);

	//  �������� ���� ��, �ö󰡸� ȹ�� �ϴ� ��Ʈ �� 
	m_fSrcX = m_fGreenBarX + 65;
	m_fSrcY = m_fGreenBarY + 76;  //76

	m_fSrcWidth = 9;
	m_fSrcHeight = 3;
	m_fSrcCurrY = m_fSrcY;
	m_rcSeroBar = RectMake(m_fSrcX, m_fSrcY, m_fSrcWidth, m_fSrcHeight);

	m_rcSeroBar.top = m_fSrcCurrY - 250;  /// �����ȹ��� �ʱⰪ  

	m_iRandomFish = 0; //206~209 ��������� ���� ��
	m_iLuck = 7;  /// ����Ȯ�� + ����
	
	m_iChance = 100; /// ����Ȯ�� 1~100
	m_iRandomChance = 0; // 1~100 �������� ���� ����




	//���˴� ����
	m_fchooY = m_fGreenBarY;
	m_fchooX = m_fGreenBarX - 68;
	m_iChooFrame = 1;
	m_iChooCount = 0;


	//������� �˸���
	m_fBoardX = m_fPlayerX-100;
	m_fBoardY = m_fPlayerY-220;


	//�ʷ�Ʈ ���� rgb
	m_r = 255;
	m_g = 0;
	m_b = 0;




	m_BarState = PLUS; // ���ι��� �ʷϷ�Ʈ ó������
	m_BarResult = BAR_NULL1; // ���ι� ���
	m_FishResult = FISHGET_NULL; // �������� �ο� ���

	// �ð� 
	m_fTime = 0;
	m_fTime2 = 0;
	m_fTime3 = 0;
	m_fTime4 = 0;
	m_fTime5 = 0;



	isMaxOn = NULL;	// �ƽ��̹���
	isOne = false;// ������� ����
	isTwo = false;
	isThree = false;
	isThrowing = false;
	isFeelClick = false;
	isHitOn = false;
	isGetFish = false;
	isMistake = true; // �Լ� ���� �����̽���Ű�� ���γ־ �������� �������ܼ� ���� �Ұ�
	isBring = false;
	isSetFish = false;
	isSoundOn = false;
	isSoundOn2 = false;

	return S_OK; //ok
}

void fishing::release()
{
}

void fishing::update()
{

	m_fPlayerX = m_pPlayer->getX()- CAMERA->getX();
	m_fPlayerY = m_pPlayer->getY()- CAMERA->getY();
	if (isFishing)
	{
		if (isMistake && KEYMANAGER->isStayKeyDown(VK_LBUTTON))  // ó�� ���� �� �ѹ��� ����
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
			
			HBRUSH brush = CreateSolidBrush(RGB(m_r, m_g, m_b)); //����귯��
			m_pIgaroBar->render(hdc, m_fGaroBarX, m_fGaroBarY); //���ι� 
			FillRect(hdc, &m_rcGaroBar, brush);//��Ʈ ��ä����
			DeleteObject(brush);// ����귯�� ����� ����
		}
	
		if (isTwo || isThree || isHitOn)
		{
			m_pIzzi->frameRender(hdc, m_fZziX, m_fZziY, m_iFrameZziX, 1); //��
		}
		if (isGetFish)
		{
			m_pIplayer->frameRender(hdc, m_fPlayerX, m_fPlayerY, m_iPlayerFrameX, m_iPlayerFrameY); //�÷��̾�
		}
		else
		{
			m_pIplayerFishing->frameRender(hdc, m_fPlayerX - 55, m_fPlayerY - 30, m_iPlayerFrameX, m_iPlayerFrameY);
		}
		if (isHitOn == true)
			m_pIhit->render(hdc, m_fHitX, m_fHitY, m_fHitBig); //��Ʈ

	

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

			HBRUSH brush = CreateSolidBrush(RGB(m_r, m_g, m_b)); //����귯��
			FillRect(hdc, &m_rcSeroBar, brush);
			DeleteObject(brush);
			//Rectangle(hdc, m_fFishX + 1, m_fFishY, m_fFishX + 10, m_fFishY + 37);
			//Rectangle(hdc, m_fGreenBarX, m_fGreenCurrY, m_fGreenBarX + 10, m_fGreenCurrY + 77);		
		}

		if (m_FishResult == GET_FISH)
		{
			
			m_pIboard->render(hdc, m_fBoardX, m_fBoardY); // �˸���
			m_pIgogi->render(hdc, m_fZziX, m_fZziY, 4); //���ΰ��
			m_pIgogi->render(hdc, m_fBoardX+40, m_fBoardY+70, 4); //���ΰ��
			sprintf_s(m_szText, 128, "%s", getFishName(m_iRandomFish));
			TextOut(hdc, m_fBoardX + 150, m_fBoardY + 70, m_szText, strlen(m_szText));

			sprintf_s(m_szText, 128, " %.1f ��ġ! ", m_fFishLong);
			TextOut(hdc, m_fBoardX + 155, m_fBoardY + 100, m_szText, strlen(m_szText));
		}
		else if (m_FishResult == MISS_FISH)
			m_pIplayer->frameRender(hdc, m_fZziX + 50, m_fZziY + 100, 2, 0);

		if (isFeelClick == true && m_iFeelAlpha > 0)
			m_pIFeel->alphaRender(hdc, m_fFeelX, m_fFeelY, m_iFeelAlpha); //����ǥ
		if (isMaxOn == true)
			m_pImax->render(hdc, m_fMaxX, m_fMaxY); // max�̹���

	}
}
// ���� ��
void fishing::fishingOne()
{
	if (isOne == true)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))  // space Ŭ�� �� ���콺 Ŭ������ �ٲ���Ѵ� >> ��ư ������ ������ ���� �������� ���,�϶�
		{
			if (!isSoundOn)
			{
				SOUNDMANAGER->play("sound/effect/fishing/�����¼Ҹ�.wav", g_soundVolume.effect);
				isSoundOn = true;
			}
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
			if (isSoundOn)
			{
				SOUNDMANAGER->play("sound/effect/fishing/���ù�ư�Ҹ�.wav", g_soundVolume.effect);
				isSoundOn = false;
			}
				
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
				if (m_BarResult == YELLOW || m_BarResult == GREEN)
				{
					if (!isSoundOn)
					{
						SOUNDMANAGER->play("sound/effect/fishing/�����ٴ���.wav", g_soundVolume.effect);
						isSoundOn = true;
					}
				}
				m_fTime2 = 0;
			
				isOne = false;
				isTwo = true;
			}
		}

		//�������� ����
		if (m_fRcCurrX - m_fGaroBarX >= 160) // �����̴� ��Ʈ�ǰ��� 140���� ũ�� �ʷϻ�����ǥ��
		{
			m_r = 0; m_g = 220; m_b = 0;
		}
		else if ((m_fRcCurrX - m_fGaroBarX) >= 130 && m_fRcCurrX - m_fGaroBarX < 160) //����
		{
			m_r = 0; m_g = 255;	m_b = 0;
		}
		else if (m_fRcCurrX - m_fGaroBarX >= 80 && m_fRcCurrX - m_fGaroBarX < 130)  // �����̴� ��Ʈ�ǰ� 70����ũ�� 140���������� ���
		{
			m_r = 255;	m_g = 255;	m_b = 0;
		}
		else if (m_fRcCurrX - m_fGaroBarX >= 60 && m_fRcCurrX - m_fGaroBarX < 80) //��
		{
			m_r = 255;	m_g = 128;	m_b = 0;
		}
		else if (m_fRcCurrX - m_fGaroBarX < 60) //��
		{
			m_r = 255;	m_g = 0;	m_b = 0;
		}
	}
}

// ���ΰ������� �����U ���� ���߸� �ƽ� ��
void fishing::ifMax()
{
	if (m_fRcCurrX - m_fGaroBarX >= 170 && m_BarState == STOP) // �ƽ���ġ���߸� �ƽ�ǥ��+�ƽ��̹��� �����̰�����
	{
		isMaxOn = true;
		if (!isSoundOn2)
		{
			isSoundOn2 = true;
		}
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

// ����ǥ �����ϋ� ������ ��Ʈ
void fishing::ifHit()
{
	if (isHitOn == true)
	{
		if (!isSoundOn)
		{
			SOUNDMANAGER->play("sound/effect/fishing/������Ʈ.wav", g_soundVolume.effect);
			isSoundOn = true;
		}

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

// ����� �������� ��ٸ��� ���� ����
void fishing::fishingTwo()
{
	if (isOne == false && isTwo == true)
	{
		if (m_BarResult == RED)
		{
			SOUNDMANAGER->play("sound/effect/fishing/����ä�¼Ҹ�.wav", g_soundVolume.effect);
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
			{
				m_iRandomChance = RANDOM->getFromIntTo(1, 100);
				
			}
				
			
			

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
					SOUNDMANAGER->play("sound/effect/fishing/����ä�¼Ҹ�.wav", g_soundVolume.effect);
					isFishing = false;
					m_pPlayer->setPlayerState(PLAYER_PLAY);
					return;
				}
			}

			if (m_iRandomChance - m_iLuck <= m_iChance && m_fTime4 >= 4.f)  // ����Ⱑ �ɸ����
			{
				isFeelClick = true;
				if (isSoundOn)
				{
					SOUNDMANAGER->play("sound/effect/fishing/����ǥ�Ҹ�.wav", g_soundVolume.effect);
					isSoundOn = false;
				}
				
				if (isFeelClick == true && m_fTime4 <= 4.6f)
				{
					m_iFeelAlpha -= 3;
				}
				else if (m_fTime4 > 4.6f) // ���������
				{

					m_fTime4 = 0;
					m_iRandomChance = 0;
					m_iFeelAlpha = 255;
					isFeelClick = false;
					isSoundOn = true;
					return;
				}
			}
			else if (m_fTime4 >= 3.f && m_iRandomChance - m_iLuck > m_iChance)	// �ɸ��� ���� ���
			{
				m_fTime4 = 0;
				m_iRandomChance = 0;
				
				return;
			}
		}
	}
}

//�����
void fishing::zziThrow()
{
	m_iFrameZziX = 1;
	
	//float a= MY_UTIL::getDistance(m_fPlayerX, m_fPlayerY, m_fPlayerX - 100, m_fPlayerY - 100);

	//m_fZziX += cosf(MY_UTIL::getAngle(m_fZziX, m_fZziY, a, a)) * 10;
	//m_fZziY += -sinf(MY_UTIL::getAngle(m_fZziX, m_fZziY, a, a)) * 10;
	//


	if (m_pPlayer->getPlayerDir() == PLAYER_DOWN)//��������������
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
	else if (m_pPlayer->getPlayerDir() == PLAYER_UP)//��
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
	else if (m_pPlayer->getPlayerDir() == PLAYER_LEFT)//��
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
	else if (m_pPlayer->getPlayerDir() == PLAYER_RIGHT)//��
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

	if (m_fTime3 > 1.2f)
	{
		SOUNDMANAGER->play("sound/effect/fishing/÷���Ҹ�.wav", g_soundVolume.effect);
		isThrowing = true;
		m_fTime3 = 0;
	}
}

// �� �յն��ٴϴ¿�����
void fishing::zziMove()
{
	m_iZziCount++;
	if (m_iZziCount % 200 == 1)
	{
		SOUNDMANAGER->play("sound/effect/fishing/���Ҹ�.wav", g_soundVolume.effect);
	}
	
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

//���� ��
void fishing::fishingThree() // ������ �ο� ����
{
	if (isTwo == false && isThree == true)
	{
		if (m_fGreenCurrY >= m_fGreenMinY && m_fGreenCurrY <= m_fGreenBarY)
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))// ������������ �����ؾ��ϰ�
			{
				m_fGreenCurrY -= 12;
				m_fSpeedGreen -= 0.3;
				m_fGreenCurrY += m_fSpeedGreen;

				m_iChooCount++;
				if (m_iChooCount % 4 == 1)
				{
					m_iChooFrame++;
					if (m_iChooFrame > 3)
					{
						m_iChooFrame = 0;
						RECT rc;
						if (IntersectRect(&rc, &m_rcFishBar, &m_rcGreenBar))
						{
							SOUNDMANAGER->play("sound/effect/fishing/�����¼Ҹ�2.wav", g_soundVolume.effect);

						}
					}

				}
			}
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			{
				m_iChooCount = 0;
				m_fSpeedGreen = 0;
			
			}
			else
				m_fGreenCurrY += 8; // ���� �����ؾ��Ѵ�

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

		//�������� ����
		if (m_fSrcCurrY - m_fGreenMinY >= 340) // �����̴� ��Ʈ�ǰ��� 140���� ũ�� ��
		{
			m_r = 255;	m_g = 0;	m_b = 0;
			if (m_fSrcCurrY - m_fGreenMinY >= 469)
				m_FishResult = MISS_FISH;
		}
		else if ((m_fSrcCurrY - m_fGreenMinY) >= 210 && m_fSrcCurrY - m_fGreenMinY < 340) //��
		{
			m_r = 255;	m_g = 128;	m_b = 0;
		}
		else if (m_fSrcCurrY - m_fGreenMinY >= 100 && m_fSrcCurrY - m_fGreenMinY < 210)  // ��
		{
			m_r = 255;	m_g = 255;	m_b = 0;
		}
		else if (m_fSrcCurrY - m_fGreenMinY >= 50 && m_fSrcCurrY - m_fGreenMinY < 100) //��
		{
			m_r = 0; m_g = 255;	m_b = 0;
		}
		else if (m_fSrcCurrY - m_fGreenMinY < 50) //��
		{
			m_r = 0; m_g = 220; m_b = 0;

			if (m_fSrcCurrY - m_fGreenMinY <= 0)
			{
				m_FishResult = GET_FISH;
				if (isSetFish == false)
				{
					m_iRandomFish = RANDOM->getFromIntTo(206, 209);
					m_fFishLong = RANDOM->getFromFloatTo(0.f, 300.f);
					m_pIgogi = IMAGEMANAGER->findImage(getFishIcon(m_iRandomFish));
					isSetFish = true;
				}
			}
				
		}


		if (m_FishResult == GET_FISH)
		{
			SOUNDMANAGER->play("sound/effect/fishing/�����ٴ���.wav", g_soundVolume.effect);
			isGetFish = true;
			
		}

		else if (m_FishResult == MISS_FISH)
		{

			//this->init();
			SOUNDMANAGER->play("sound/effect/fishing/����ä�¼Ҹ�.wav", g_soundVolume.effect);
			isFishing = false;
			m_pPlayer->setPlayerState(PLAYER_PLAY);
			return;
		}
	}

}
const char * fishing::getFishIcon(int fishNum)
{
	switch (m_iRandomFish)
	{
	case 206://�ػ�
		return "item_206";
		break;
	case 207:
		return "item_207";
		break;
	case 208:
		return "item_208";
		break;
	case 209:
		return "item_209";
		break;
	default:
		break;
	}
	return NULL;
}
const char * fishing::getFishName(int fishNum)
{
	switch (m_iRandomFish)
	{
	case 206://�ػ�
		return " �ػ� !";
		break;
	case 207:
		return " �Ի���� ! ";
		break;
	case 208:
		return " �ݺؾ� ! ";
		break;
	case 209:
		return " �öѱ� ! ";
		break;
	default:
		break;
	}
	return NULL;
}
//����� ����������
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

// ����⸦ ���� ���
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
				
		if (m_fTime2 > 0.5f && m_fTime2 < 0.6f)
		{
			if (isSoundOn)
			{
				SOUNDMANAGER->play("sound/effect/fishing/��θ�.wav", g_soundVolume.effect);
				isSoundOn = false;
			}
			isBring = true;
					
		}	
		if (m_fTime2 > 3.5f)
		{		
			m_fTime2 = 0;
		
			m_pPlayer->getPlayerMenu()->getInven()->addItem(m_iRandomFish);
		
			isFishing = false;
			m_pPlayer->setPlayerState(PLAYER_PLAY);
			return;
		}
	
	}

}

// �÷��̾ ���� ���⿡ ���� ��� �����ְ� �ð� �޾Ƽ� ���� ����⸦ �÷��̾�� �̵��ϴ� �Լ�
void fishing::fishBring()
{
		if (m_pPlayer->getPlayerDir() == PLAYER_UP)//��
		{
			m_fZziX += cosf(MY_UTIL::getAngle(m_fZziX - 7, m_fZziY, m_fPlayerX, m_fPlayerY - 30)) * 10;
			m_fZziY += -sinf(MY_UTIL::getAngle(m_fZziX - 7, m_fZziY, m_fPlayerX, m_fPlayerY - 30)) * 10;
		}
		else
		{
			m_fZziX += cosf(MY_UTIL::getAngle(m_fZziX - 7, m_fZziY - 70, m_fPlayerX, m_fPlayerY)) * 10;
			m_fZziY += -sinf(MY_UTIL::getAngle(m_fZziX - 7, m_fZziY - 70, m_fPlayerX, m_fPlayerY)) * 10;
		}


	//if (m_pPlayer->getPlayerDir() == PLAYER_DOWN)//��������������
	//{

	//	if (m_fTime3 < 0.1f)
	//	{
	//		m_fZziX += 5.f;
	//		m_fZziY -= 10.f;
	//	}
	//	else if (m_fTime3 < 0.2f)
	//	{
	//		m_fZziY -= 10.f;
	//	}
	//	else if (m_fTime3 < 0.3f)
	//	{
	//		m_fZziX -= 8.f;
	//		m_fZziY -= 15.f;
	//	}
	//	if (m_fTime3 > 0.4f && m_fTime3 < 0.4f)
	//	{
	//		m_fZziY -= 0.7f;
	//	}
	//	else if (m_fTime3 > 0.4f && m_fTime3 < 0.5f)
	//	{
	//		m_fZziY += 0.2f;
	//	}
	//}
	//else if (m_pPlayer->getPlayerDir() == PLAYER_UP)//��
	//{

	//	if (m_fTime3 < 0.1f)
	//	{
	//		m_fZziX -= 10.f;
	//		m_fZziY += 10.f;
	//	}
	//	else if (m_fTime3 < 0.2f)
	//	{
	//		m_fZziY += 10.f;
	//	}
	//	else if (m_fTime3 < 0.3f)
	//	{
	//		m_fZziX += 5.f;
	//		m_fZziY += 15.f;
	//	}
	//	if (m_fTime3 > 0.4f && m_fTime3 < 0.4f)
	//	{
	//		m_fZziY -= 0.7f;
	//	}
	//	else if (m_fTime3 > 0.4f && m_fTime3 < 0.5f)
	//	{
	//		m_fZziY += 0.2f;
	//	}
	//}
	//else if (m_pPlayer->getPlayerDir() == PLAYER_LEFT)//��
	//{

	//	if (m_fTime3 < 0.1f)
	//	{
	//		m_fZziX += 5.f;
	//		m_fZziY += 10.f;
	//	}
	//	else if (m_fTime3 < 0.2f)
	//	{
	//		m_fZziX += 10.f;
	//		m_fZziY += 10.f;
	//	}
	//	else if (m_fTime3 < 0.3f)
	//	{
	//		m_fZziX += 20.f;
	//		m_fZziY -= 35.f;
	//	}
	//	if (m_fTime3 > 0.4f && m_fTime3 < 0.4f)
	//	{
	//		m_fZziY -= 0.7f;
	//	}
	//	else if (m_fTime3 > 0.4f && m_fTime3 < 0.5f)
	//	{
	//		m_fZziY += 0.2f;
	//	}

	//}
	//else if (m_pPlayer->getPlayerDir() == PLAYER_RIGHT)//��
	//{

	//	if (m_fTime3 < 0.1f)
	//	{
	//		m_fZziX -= 5.f;
	//		m_fZziY += 10.f;
	//	}
	//	else if (m_fTime3 < 0.2f)
	//	{
	//		m_fZziX -= 10.f;
	//		m_fZziY += 10.f;
	//	}
	//	else if (m_fTime3 < 0.3f)
	//	{
	//		m_fZziX -= 23.f;
	//		m_fZziY -= 35.f;
	//	}
	//	if (m_fTime3 > 0.4f && m_fTime3 < 0.4f)
	//	{
	//		m_fZziY -= 0.7f;
	//	}
	//	else if (m_fTime3 > 0.4f && m_fTime3 < 0.5f)
	//	{
	//		m_fZziY += 0.2f;
	//	}

	//}

	//if (m_fTime3 > 0.6f)
	//{
	//	
	//	m_fTime3 = 0;
	//	SOUNDMANAGER->play("sound/effect/fishing/�����ٴ���.wav");
	//
	//}


}

void fishing::addSound()
{
	////���û���
	SOUNDMANAGER->addSound("sound/effect/fishing/�����¼Ҹ�.wav", false, false);
	SOUNDMANAGER->addSound("sound/effect/fishing/���ù�ư�Ҹ�.wav", false, false);
	SOUNDMANAGER->addSound("sound/effect/fishing/�����ٴ���.wav", false, false);
	SOUNDMANAGER->addSound("sound/effect/fishing/����ǥ�Ҹ�.wav", false, false);
	SOUNDMANAGER->addSound("sound/effect/fishing/������Ʈ.wav", false, false);
	SOUNDMANAGER->addSound("sound/effect/fishing/÷���Ҹ�.wav", false, false);
	SOUNDMANAGER->addSound("sound/effect/fishing/���Ҹ�.wav", false, false);
	SOUNDMANAGER->addSound("sound/effect/fishing/�����¼Ҹ�2.wav", false, false);
	SOUNDMANAGER->addSound("sound/effect/fishing/��θ�.wav", false, false);
	SOUNDMANAGER->addSound("sound/effect/fishing/����ä�¼Ҹ�.wav", false, false);
}

void fishing::addImage()
{

	// ���ð��� �̹���
	IMAGEMANAGER->addImage("i_GaroBar", "image/Stardew Valley/fishing/���ι�.bmp", 200, 48, true, RGB(255, 0, 255));   // ���������� 50,12 
	IMAGEMANAGER->addImage("i_Max", "image/Stardew Valley/fishing/�ƽ�.bmp", 116, 48, true, RGB(255, 0, 255)); //�������� 58,24 
	IMAGEMANAGER->addImage("i_Zzi", "image/Stardew Valley/fishing/��.bmp", 120, 40, 3, 1, true, RGB(255, 0, 255)); //�������� 30,10 
	IMAGEMANAGER->addImage("i_Player", "image/Stardew Valley/fishing/player.bmp", 400, 640, 5, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("i_PlayerFishing", "image/Stardew Valley/fishing/�÷��̾��.bmp", 768, 768, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("i_Feel", "image/Stardew Valley/fishing/����ǥ.bmp", 30, 45, true, RGB(255, 0, 255)); //�������� 10,15 
	IMAGEMANAGER->addImage("i_Hit", "image/Stardew Valley/fishing/��Ʈ.bmp", 148, 64, true, RGB(255, 0, 255)); //�������� 74,32 
	IMAGEMANAGER->addImage("i_SeroBar", "image/Stardew Valley/fishing/���ι�.bmp", 160, 500, true, RGB(255, 0, 255)); //�������� 39,150  
	IMAGEMANAGER->addImage("i_WhitebarL", "image/Stardew Valley/fishing/��ǳ������.bmp", 210, 550, true, RGB(255, 0, 255)); //�������� 52,185 
	IMAGEMANAGER->addImage("i_WhitebarR", "image/Stardew Valley/fishing/��ǳ������.bmp", 210, 550, true, RGB(255, 0, 255)); //�������� 52,185  
	IMAGEMANAGER->addImage("i_GreenBar", "image/Stardew Valley/fishing/�ʷϹٸ����.bmp", 37, 77, true, RGB(255, 0, 255)); // 9,9 
	IMAGEMANAGER->addImage("i_moveFish", "image/Stardew Valley/fishing/�����.bmp", 37, 37, true, RGB(255, 0, 255)); // 19 19
	IMAGEMANAGER->addImage("i_moveChoo", "image/Stardew Valley/fishing/�߰���.bmp", 168, 55, 4, 1, true, RGB(255, 0, 255));// 72 21 
	IMAGEMANAGER->addImage("i_GetFish", "image/Stardew Valley/fishing/�ݺؾ�.bmp", 102, 51, 2, 1, true, RGB(255, 0, 255));// 34 17  
	IMAGEMANAGER->addImage("i_NoticeBoard", "image/Stardew Valley/fishing/���˸�.bmp", 292, 196, true, RGB(255, 0, 255)); // 73 49
}



fishing::fishing()
{
}


fishing::~fishing()
{
}
