#include "gamescene.h"
#include"SceneManagement.h"
#include "ActionFactory.h"

Scene*gamescene::createScene() {
	auto scene = Scene::create();
	auto layer = gamescene::create();
	scene->addChild(layer);
	return scene;
}
void gamescene::buttonJiaClickCallback(cocos2d::Ref * pSender)
{
	//��ǰ�������ڲŸ���,������Ե�
	if (now_Arms == is_Pao) {
		PaoChangeSucced = false;
		now_PaoNum++;
		if (now_PaoNum > all_PaoNum)
		{
			now_PaoNum = 0;
		}
		Now_pao->runAction(CCSequence::create(
			CCScaleTo::create(0.5f, 0.3f),
			CCCallFunc::create(this, callfunc_selector(gamescene::ScaleCallback)),
			NULL));
		int sundID = SimpleAudioEngine::sharedEngine()->playEffect("music/bgm_change_cannon.mp3");
	}
	

}
void gamescene::buttonJianClickCallback(cocos2d::Ref * pSender)
{
	if (now_Arms == is_Pao) {
		PaoChangeSucced = false;

		now_PaoNum--;
		if (now_PaoNum < 0)
		{
			now_PaoNum = 6;
		}
		Now_pao->runAction(CCSequence::create(
			CCScaleTo::create(0.5f, 0.3f),
			CCCallFunc::create(this, callfunc_selector(gamescene::ScaleCallback)),
			NULL));
		int sundID = SimpleAudioEngine::sharedEngine()->playEffect("music/bgm_change_cannon.mp3");
	}
	
}
void gamescene::CameraButtonCallback(Ref * pSender)
{
	int m_soundID = SimpleAudioEngine::sharedEngine()->playEffect("music/bgm_camera.mp3");
}
void gamescene::ChangeBackMusicCallback(Ref * pSender)
{
	static int MusicID = 0;
	switch (MusicID)
	{
	case 0:SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/music_1.mp3", true);break;
	case 1:SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/music_2.mp3", true);break;
	case 2:SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/music_3.mp3", true);break;
	case 3:SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/music_4.mp3", true);break;
	case 4:SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/music_5.mp3", true);break;
	case 5:SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/music_6.mp3", true);break;
	default:
		break;
	}
	if (++MusicID > 5)
		MusicID = 0;

}
void gamescene::PauseMenuCallback(Ref * pSender)
{
	auto s = Director::getInstance()->getWinSize();
	//PauseNode->setVisible(true);
	PauseNode->setZOrder(5);
	PauseNode->runAction(CCSequence::create(
		MoveTo::create(0.5f, Vec2(s.width / 2, s.height / 2)),
		JumpTo::create(0.5,Vec2(s.width/2,s.height/2),20,1),
		NULL));
	unscheduleAllSelectors();
}
void gamescene::ContinueGameCallback(Ref * pSender)
{
	auto s = Director::getInstance()->getWinSize();
	PauseNode->setZOrder(5);
	PauseNode->runAction(CCSequence::create(
		JumpTo::create(0.5, Vec2(s.width / 2, s.height / 2), 20, 1), 
		MoveTo::create(0.5f, Vec2(s.width / 2, 1500)),
		NULL));
	schedule(schedule_selector(gamescene::FishFactory), 1.f);//���㹤��
	schedule(schedule_selector(gamescene::collision), 0.1f);//���ڴ����ӵ�������ײ���߼�
	schedule(schedule_selector(gamescene::update));//������Ҫʵʱ���µ��߼�
}
void gamescene::sceneTomainCallback(Ref * pSender)
{
	scenemanagement::getInstance()->sceneToMain();
}
void gamescene::jiguangPaoCallback(Ref * pSender)
{
	if (now_Arms != is_Jiguang) {
		now_Arms = is_Jiguang;
		auto button = (Button*)pSender;
		getChildByName("Select")->setPosition(button->getPosition());
		//���ﻹ��Ҫд�л������ڵ��߼�
		Now_pao->runAction(CCSequence::create(
			CCScaleTo::create(0.5f, 0.3f),
			CCCallFunc::create(this, callfunc_selector(gamescene::ScaleCallback)),
			NULL));
		int sundID = SimpleAudioEngine::sharedEngine()->playEffect("music/bgm_change_cannon.mp3");
	}
	
}
void gamescene::putongPaoCallback(Ref * pSender)
{
	if (now_Arms != is_Pao) {
		now_Arms = is_Pao;
		auto button = (Button*)pSender;
		getChildByName("Select")->setPosition(button->getPosition());
		//���ﻹ��Ҫд�л����߼�
		Now_pao->runAction(CCSequence::create(
			CCScaleTo::create(0.5f, 0.3f),
			CCCallFunc::create(this, callfunc_selector(gamescene::ScaleCallback)),
			NULL));
		int sundID = SimpleAudioEngine::sharedEngine()->playEffect("music/bgm_change_cannon.mp3");
	}
	
}
bool gamescene::init() {
	if (!Layer::init()) {
		return false;
	}
	
	auto s = Director::getInstance()->getWinSize();
	{	//���� ��������
		//���������¼�
		setTouchEnabled(true);
		//����Ϊ���㴥��  
		setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

		GameTime = 0.f;
		PaoChangeSucced = true;
		JiguangEnd = true;
		FishNode = Node::create();
		addChild(FishNode, 2);
		Now_Round = Round_one;//������
		now_Arms = is_Pao;//��ǰʹ�õ�����

		auto Select = Sprite::create();
		Select->setPosition(810, 30);
		Select->setScale(1.3f);
		addChild(Select,10,"Select");
		Select->runAction(RepeatForever::create(ACT_FTY->Select()));

		//���ű�������
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/music_2.mp3", true);
	}
	{	//csb��Դ


		auto m_csbNode = CSLoader::createNode("res/GameScene.csb");
		addChild(m_csbNode);
		//������
		BackScene = static_cast<Sprite*>(m_csbNode->getChildByName("backScene"));
		BackScene->setZOrder(-1);//��ײ�
		
		//���Ͻ���ת�ľ���
		auto angle_img = static_cast<Sprite*>(m_csbNode->getChildByName("Angle_sprite"));
		angle_img->runAction(RepeatForever::create(CCRotateBy::create(1.f, 50)));

		//������Ť
		auto  CameraButton= static_cast<Button*>(m_csbNode->getChildByName("Camera"));
		CameraButton->addClickEventListener(CC_CALLBACK_1(gamescene::CameraButtonCallback, this));
		
		//���ָ�����ť
		auto  MusicButton = static_cast<Button*>(m_csbNode->getChildByName("Music"));
		MusicButton->addClickEventListener(CC_CALLBACK_1(gamescene::ChangeBackMusicCallback, this));
		
		//��ʼ�����
		money = static_cast<TextAtlas*>(m_csbNode->getChildByName("MoneyText"));
		m_I_bufferNumber = m_I_number = 999999;
		std::string s_Money = StringUtils::format("%07d", m_I_number);
		money->setString(s_Money);

		//��̨�Ӻ�
		auto button_jia = static_cast<Button*>(m_csbNode->getChildByName("Button_3"));
		button_jia->addClickEventListener(CC_CALLBACK_1(gamescene::buttonJiaClickCallback, this));
		//��̨����
		auto button_jian = static_cast<Button*>(m_csbNode->getChildByName("Button_4"));
		button_jian->addClickEventListener(CC_CALLBACK_1(gamescene::buttonJianClickCallback, this));
		//�����ڰ�ť
		auto jiguang = static_cast<Button*>(m_csbNode->getChildByName("Button_6"));
		jiguang->addClickEventListener(CC_CALLBACK_1(gamescene::jiguangPaoCallback, this));
		//��ͨ �ڰ�ť
		auto PutongPao = static_cast<Button*>(m_csbNode->getChildByName("Button_5"));
		PutongPao->addClickEventListener(CC_CALLBACK_1(gamescene::putongPaoCallback, this));
		//��ͣ�ڵ�-��Ϸ����
		auto button_Pause = static_cast<Button*>(m_csbNode->getChildByName("Button_13"));
		button_Pause->addClickEventListener(CC_CALLBACK_1(gamescene::PauseMenuCallback, this));
		PauseNode= static_cast<Node*>(m_csbNode->getChildByName("Node_1"));
		PauseNode->setPosition(s.width / 2, 1500);
		PauseNode->setZOrder(999);
		auto continueGame = (Button*)PauseNode->getChildByName("Button_10");
		continueGame->addClickEventListener(CC_CALLBACK_1(gamescene::ContinueGameCallback, this));
		auto sceneTomain = (Button*)PauseNode->getChildByName("Button_12");
		//sceneTomain->addClickEventListener(CC_CALLBACK_1(gamescene::sceneTomainCallback, this));
		
		//��ҳ�ֵ�ڵ�
		rechargeNode = static_cast<Node*>(m_csbNode->getChildByName("Node_2"));
		rechargeNode->setPosition(s.width / 2, 1500);


	}


	{	//��̨����
		last_PaoNum = now_PaoNum = 0;
		all_PaoNum = 6;
		angle = 0.f;
		//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cannon/cannon.plist");
		for (int paoNum = 1;paoNum <= 7;paoNum++)
		{
			std::string temp = StringUtils::format("actor_cannon1_%d1.png", paoNum);
			pao[paoNum - 1] = Sprite::createWithSpriteFrame(
				SpriteFrameCache::getInstance()->getSpriteFrameByName(temp));
			pao[paoNum - 1]->setPosition(s.width / 2, 50);
			pao[paoNum - 1]->setAnchorPoint(Vec2(0.5f, 0.5f));
			pao[paoNum - 1]->setVisible(false);
			//pao[paoNum - 1]->setRotation(angle);
			addChild(pao[paoNum - 1], 3);
		}
		
		Now_pao = pao[now_PaoNum];
		angle = Now_pao->getRotation();
		pao[now_PaoNum]->setVisible(true);
		
		JiguangPao= Sprite::createWithSpriteFrame(
			SpriteFrameCache::getInstance()->getSpriteFrameByName("actor_cannon_jiguang_01.png"));
		JiguangPao->setPosition(s.width / 2, 50);
		JiguangPao->setVisible(false);
		addChild(JiguangPao);
	}


	schedule(schedule_selector(gamescene::FishFactory), 1.f);//���㹤��
	schedule(schedule_selector(gamescene::collision), 0.1f);//���ڴ����ӵ�������ײ���߼�
	
	schedule(schedule_selector(gamescene::update));//������Ҫʵʱ���µ��߼�

	return true;
}

void gamescene::update(float dt)
{

	if (m_I_number > 0)
	{
		if (m_I_bufferNumber != m_I_number)//�����ֵ �뻺����ֵ��ͬʱ����
		{
			//������ӵ����
			if (m_I_bufferNumber > m_I_number) {
				m_I_number++;
			}
			//��Ҽ��ٵ����
			else if (m_I_bufferNumber < m_I_number) {
				m_I_number--;
			}
			std::string s_Money = StringUtils::format("%07d", m_I_number);
			money->setString(s_Money);
		}

	}
	else {
		//û�����
	}
}

bool gamescene::onTouchBegan(Touch * touch, Event * event)
{

	if (!PaoChangeSucced || !JiguangEnd&&now_Arms == is_Jiguang)
		return false;//��̨δ�л�������ﲻ��ִ�� ��һ������δ���Ҳ����ִ������
	if(now_Arms==is_Jiguang)
		JiguangEnd = false;

	Vec2 touchPoint = touch->getLocation();
	Vec2 paoPoint = Now_pao->getPosition();

	m_TouchPoint = touchPoint;//��¼���λ��

	{	//�����ʱ����֮��ĽǶ�
		double cb_1 = abs(touchPoint.y - paoPoint.y);
		double ab_1 = abs(touchPoint.x - paoPoint.x);
		double ac_1 = sqrtf(cb_1*cb_1 + ab_1*ab_1);
		double acb_1 = (ac_1*ac_1 + ab_1*ab_1 - cb_1*cb_1) / (2 * ab_1*ac_1);
		angle = CC_RADIANS_TO_DEGREES(acb_1);//acb / 3.141592653f * 180;
		//57.2748413
		if (angle >= 45.f) {
			double bc_2 = abs(touchPoint.x - paoPoint.x);
			double ba_2 = abs(touchPoint.y - paoPoint.y);
			double ac_2 = sqrtf(bc_2*bc_2 + ba_2*ba_2);
			double acb_2 = (ba_2*ba_2 + ac_2*ac_2 - bc_2*bc_2) / (2 * ba_2*ac_2);
			angle = 90-CC_RADIANS_TO_DEGREES(acb_2);//acb / 3.141592653f * 180;
		}
		if (touchPoint.x < paoPoint.x) {
			angle = -angle;
		}
		float angleTime = abs(angle - Now_pao->getRotation()) / 300;//90-0/100,��ֵԽ�߽Ƕ�Խ����
		
		
		
		//������̨��ת��������Ƕȣ��󴥷�fire�ص�
		Now_pao->runAction(CCSequence::create(
			CCRotateTo::create(angleTime, angle),
			CCCallFunc::create(this, callfunc_selector(gamescene::BulletFireCallback)),
			NULL));

	
	}
	return true;
}
void gamescene::onTouchMoved(Touch * touch, Event * event)
{
}

void gamescene::onTouchEnded(Touch * touch, Event * event)
{
}


void gamescene::collision(float dt)
{
	Vector<cocos2d::Node*>Children = FishNode->getChildren();//��ȡ��ǰ�ڵ����ж�������
	Vector<cocos2d::Node*>::iterator fish, bullet;
	for (bullet = Children.begin(); bullet != Children.end();bullet++)
	{
		//8-30���Ǽ�����
		//1-7�ӵ���������������Ļ�е��� �ӵ���tagΪ1��7 ���tagΪ101-116
		int BulletTag = (*bullet)->getTag();
		//��ͨ�ӵ���ײ�ж�
		if (BulletTag >= 1 && BulletTag <= 7)
		{
			//������
			for (fish = Children.begin(); fish != Children.end();fish++)
			{
				if ((*fish)->getTag() > 100)
				{
					int FishTag = (*fish)->getTag();
					auto fishRect = (*fish)->getBoundingBox();
					auto fishSize = (*fish)->getContentSize();
					//Vec2 LeftTop, RightTop, LeftDown, RightDown;
					
					if (fishRect.getMaxY() - fishRect.getMinY() > 90) {
						fishSize.height /= 2;//��� �Ǵ��㣬��ײ�����������м�
					}
					Vec2 LeftTop = Vec2(fishRect.getMinX(), fishRect.getMaxY());
					Vec2 RightTop = Vec2(fishRect.getMaxX(), fishRect.getMaxY());
					Vec2 LeftDown = Vec2(fishRect.getMinX(), fishRect.getMinY());
					Vec2 RightDown = Vec2(fishRect.getMaxX(), fishRect.getMinY());

					//�ж��ӵ������ֱ�߾��룬�ж��ӵ��Ƿ� ���Χ
					if (ccpDistance((*bullet)->getPosition(), (*fish)->getPosition()) <= fishSize.height
						/*|| ccpDistance((*bullet)->getPosition(), RightTop) <= 40
						|| ccpDistance((*bullet)->getPosition(), LeftDown) <= 40
						|| ccpDistance((*bullet)->getPosition(), RightDown) <= 40*/
						
						|| (*bullet)->getPosition().x>fishRect.getMinX()&& (*bullet)->getPosition().x<fishRect.getMaxX()
						&& (*bullet)->getPosition().y>fishRect.getMinY()+ fishSize.height
						&& (*bullet)->getPosition().y<fishRect.getMaxY())
					{
						int sundID1 = SimpleAudioEngine::sharedEngine()->playEffect("music/Bombette.mp3");
						//��ײ����㴦��
						(*fish)->stopAllActions();
						auto fishPos = (*fish)->getPosition();
						auto fishAngle = (*fish)->getRotation();
						FishNode->removeChild((*fish));
						
						auto FishDeath = Sprite::create();
						FishDeath->setPosition(fishPos);
						FishDeath->setRotation(fishAngle);
						FishDeath->runAction(CCSequence::create(
							ACT_FTY->GetFishAct_ByTag(FishTag,1),
							CCCallFuncN::create(this, callfuncN_selector(gamescene::RemoveSpriteCallback)),
							NULL));

						//���
						int sundID2 = SimpleAudioEngine::sharedEngine()->playEffect("music/bgm_coin_01.mp3");
						auto gold = Sprite::create();
						gold->setPosition(fishPos);
						gold->setTag(200 + (FishTag - 100) * 2);
						addChild(gold,2);
						gold->runAction(RepeatForever::create(ACT_FTY->Gold()));
						gold->runAction(CCSequence::create(
							MoveTo::create(2,Vec2(400,20)),
							CCCallFuncN::create(this, callfuncN_selector(gamescene::RemoveSpriteCallback)),
							NULL));

						addChild(FishDeath);

						//��ײ����ӵ�����
						(*bullet)->stopAllActions();
						auto bulletPos = (*bullet)->getPosition();
						auto bulletAngle = (*bullet)->getRotation();
						FishNode->removeChild((*bullet));
						
						auto BulletBoom = Sprite::create();
						BulletBoom->setPosition(bulletPos);
						BulletBoom->setRotation(bulletAngle);
						if (BulletTag < 5){
							BulletBoom->runAction(CCSequence::create(
								ACT_FTY->BullectBoom1(),
								CCCallFuncN::create(this, callfuncN_selector(gamescene::RemoveSpriteCallback)),
								NULL));
						}
						else {
							BulletBoom->runAction(CCSequence::create(
								ACT_FTY->BullectBoom2(),
								CCCallFuncN::create(this, callfuncN_selector(gamescene::RemoveSpriteCallback)),
								NULL));
						}
						addChild(BulletBoom);
						break;//һ���ӵ�ֻ�ж�һ����
					}
					
				}
				else
					continue;
			}

		}
		//��������ײ�ж�
		else if (BulletTag > 8 && BulletTag <= 30) {
			//here is jiGuangPao de collision;
			(*bullet)->setTag(--BulletTag);
			if (BulletTag >= 12 && BulletTag <= 21){
				for (fish = Children.begin(); fish != Children.end();fish++) {
					int FishTag = (*fish)->getTag();
					//	A   *****************	C
					//		*			  *	
					//		*		    *	
					//		*		  *		
					//		*		*		
					//		*	  *			
					//		*	*			
					//		* *				
					//	B	*
					float ac = abs((*fish)->getPosition().x - (*bullet)->getPosition().x);
					float ab = abs((*fish)->getPosition().y - (*bullet)->getPosition().y);
					float bc = sqrtf(ac*ac + ab*ab);
					float angle_abc = CC_RADIANS_TO_DEGREES((ac*ac + bc*bc - ab*ab) / (2 * ac*bc));
					if (angle_abc > 45) {
						angle_abc = 90 - CC_RADIANS_TO_DEGREES((ab*ab + bc*bc - ac*ac) / (2 * ab*bc));
					}
					float angle_pao = (*bullet)->getRotation();
					if ((*fish)->getPosition().x < (*bullet)->getPosition().x) {
						angle_abc = -angle_abc;
					}	//collision angle
					if (abs(angle_abc - angle_pao) <= 3) {
						(*fish)->stopAllActions();
						auto fishPos = (*fish)->getPosition();
						auto fishAngle = (*fish)->getRotation();
						FishNode->removeChild((*fish));

						auto FishDeath = Sprite::create();
						FishDeath->setPosition(fishPos);
						FishDeath->setRotation(fishAngle);
						FishDeath->runAction(CCSequence::create(
							ACT_FTY->GetFishAct_ByTag(FishTag, 1),
							CCCallFuncN::create(this, callfuncN_selector(gamescene::RemoveSpriteCallback)),
							NULL));
						//coin
						int sundID2 = SimpleAudioEngine::sharedEngine()->playEffect("music/bgm_coin_01.mp3");
						auto gold = Sprite::create();
						gold->setPosition(fishPos);
						gold->setTag(200 + (FishTag - 100) * 2);
						addChild(gold, 2);
						gold->runAction(RepeatForever::create(ACT_FTY->Gold()));
						gold->runAction(CCSequence::create(
							MoveTo::create(2, Vec2(400, 20)),
							CCCallFuncN::create(this, callfuncN_selector(gamescene::RemoveSpriteCallback)),
							NULL));

						addChild(FishDeath);
					}
				}

			}
			else
				continue;
		}
		else
			continue;
	}

}

void gamescene::FishFactory(float dt)
{
	static float FishTime = 0.f;//��һ���� 0-60s С��

	GameTime += dt;FishTime += dt;

	if (GameTime >= 0 && GameTime <= 60)
		Now_Round = Round_one;
	/*else if (GameTime > 60 && GameTime <= 120)
		Now_Round = Round_two;
	else if (GameTime > 120 && GameTime < 180)
		Now_Round = Round_three;*/

	auto s = Director::getInstance()->getWinSize();
	
	
	int fish_tag = 100;
	bool Fish_Succed = false;
	float MoveTime = 0.f;
	{	//��ʼ ����  ͨ��ʱ�����
		{	//��һ��
			switch (Now_Round)
			{
			case Round_one: {
				if (FishTime > 10)
					FishTime = 0.f;
				if (abs(FishTime - 1.f) <= 0.2f)
				{
					fish_tag = 101;Fish_Succed = true;
					MoveTime = CCRANDOM_0_1()*(15 - 10 + 1) + 10;
				}
				else if (abs(FishTime - 2.f) <= 0.2f)
				{
					fish_tag = 106;Fish_Succed = true;
					MoveTime = CCRANDOM_0_1()*(15 - 10 + 1) + 10;
				}
				else if (abs(FishTime - 3.f) <= 0.2f)
				{
					fish_tag = 107;Fish_Succed = true;
					MoveTime = CCRANDOM_0_1()*(15 - 10 + 1) + 10;
				}
				else if (abs(FishTime - 4.f) <= 0.2f)
				{
					fish_tag = 111;Fish_Succed = true;
					MoveTime = CCRANDOM_0_1()*(15 - 10 + 1) + 10;
				}
				else if (abs(FishTime - 5.f) <= 0.2f)
				{
					fish_tag = 104;Fish_Succed = true;
					MoveTime = CCRANDOM_0_1()*(15 - 10 + 1) + 10;
				}
				else if (abs(FishTime - 6.f) <= 0.2f)
				{
					fish_tag = 112;Fish_Succed = true;
					MoveTime = CCRANDOM_0_1()*(15 - 10 + 1) + 10;
				}
				else if (abs(FishTime - 7.f) <= 0.2f)
				{
					fish_tag = 113;Fish_Succed = true;
					MoveTime = CCRANDOM_0_1()*(15 - 10 + 1) + 10;
				}
				else if (abs(FishTime - 8.f) <= 0.2f)
				{
					fish_tag = 114;Fish_Succed = true;
					MoveTime = CCRANDOM_0_1()*(15 - 10 + 1) + 10;
				}
				else if (abs(FishTime - 9.f) <= 0.2f)
				{
					fish_tag = 115;Fish_Succed = true;
					MoveTime = CCRANDOM_0_1()*(15 - 10 + 1) + 10;
				}
			}break;
			case Round_two:break;
			case Round_three:break;
			default:
				break;
			}
			
		}
		

		
	}
	


	//��һ������
	if (Now_Round == Round_one) {
		if (Fish_Succed) {
			auto fish = Sprite::create();
			fish->setTag(fish_tag);
			fish->setPosition(s.width + fish->getContentSize().width, CCRANDOM_0_1()*(650 - 100 + 1) + 100);
			fish->runAction(RepeatForever::create(ACT_FTY->GetFishAct_ByTag(fish_tag)));//ͨ��tag��ǩ��ȡ��Ӧ��Ķ���
			fish->runAction(CCSequence::create(
				MoveTo::create(MoveTime, Vec2(-fish->getContentSize().width - 200, CCRANDOM_0_1()*(650 - 100 + 1) + 100)),
				CCCallFuncN::create(this, callfuncN_selector(gamescene::RemoveSpriteCallback)),
				NULL));
			//fish->autorelease();//�����Զ��ͷ�
			FishNode->addChild(fish, 1);
		}
	}
	
	
	
	
}

void gamescene::BulletFireCallback()
{
	Sprite* Bullet;//�ӵ�����
	int Length;//�ӵ��������
	float BoomTime;//����ʱ��
	std::string BulletName;//�ӵ�����
	int m_tag;//�ӵ���ţ�1-4�ӵ����1��5-7��� 2
	if (now_Arms == is_Pao) {
		switch (now_PaoNum)
		{
		case 0:
		{
			m_I_bufferNumber -= 1;
			Now_pao->runAction(ACT_FTY->cannon_1_fire());
			BulletName = "weapon_bullet_001.png";
			Length = 300;m_tag = 1;
			break;
		}
		case 1:
		{
			m_I_bufferNumber -= 2;
			Now_pao->runAction(ACT_FTY->cannon_2_fire());
			BulletName = "weapon_bullet_002.png";
			Length = 350;m_tag = 2;
			break;
		}
		case 2:
		{
			m_I_bufferNumber -= 3;
			Now_pao->runAction(ACT_FTY->cannon_3_fire());
			BulletName = "weapon_bullet_003.png";
			Length = 400;m_tag = 3;
			break;
		}
		case 3:
		{
			m_I_bufferNumber -= 4;
			Now_pao->runAction(ACT_FTY->cannon_4_fire());
			BulletName = "weapon_bullet_004.png";
			Length = 450;m_tag = 4;
			break;
		}
		case 4:
		{
			m_I_bufferNumber -= 5;
			Now_pao->runAction(ACT_FTY->cannon_5_fire());
			BulletName = "weapon_bullet_005.png";
			Length = 500;m_tag = 5;
			break;
		}
		case 5:
		{
			m_I_bufferNumber -= 6;
			Now_pao->runAction(ACT_FTY->cannon_6_fire());
			BulletName = "weapon_bullet_006.png";
			Length = 550;m_tag = 6;
			break;
		}
		case 6:
		{
			m_I_bufferNumber -= 7;
			Now_pao->runAction(ACT_FTY->cannon_7_fire());
			BulletName = "weapon_bullet_007.png";
			Length = 600;m_tag = 7;
			break;
		}
		default:break;
		}
		int sundID = SimpleAudioEngine::sharedEngine()->playEffect("music/bgm_fire.mp3");
		//��λ����
		Vec2 oneNormalize = ccpNormalize(m_TouchPoint - Now_pao->getPosition());
		//ʱ�䣬�����ӵ��ٶ�һ��
		BoomTime = ccpDistance(Now_pao->getPosition() + oneNormalize*Length, Now_pao->getPosition()) / 600;

		Bullet = Sprite::createWithSpriteFrame(
			SpriteFrameCache::getInstance()->getSpriteFrameByName(BulletName));
		Bullet->setTag(m_tag);
		Bullet->setZOrder(2);
		Bullet->setPosition(Now_pao->getPosition());//��������̨�������
		Bullet->setRotation(Now_pao->getRotation());//�Ƕ�����̨�Ƕ����
		Bullet->runAction(CCSequence::create(
			CCMoveTo::create(BoomTime, Now_pao->getPosition() + oneNormalize*Length),
			CCCallFuncN::create(this, callfuncN_selector(gamescene::BulletSuccedCallback)),
			NULL));
		FishNode->addChild(Bullet);
	}
	else {
		int sundID = SimpleAudioEngine::sharedEngine()->playEffect("music/bgm_ach.mp3");
		m_I_bufferNumber -= 50;//һ����ʮ
		Now_pao->runAction(ACT_FTY->cannon_jiguang_fire());
		Bullet = Sprite::create();
		Bullet->setTag(30);//����15-20���������� tagΪ8
		Bullet->setName("woshijiguang");
		Bullet->setZOrder(2);
		Bullet->setAnchorPoint(Vec2(0.5, 0));
		Bullet->setPosition(Now_pao->getPosition());//��������̨�������
		Bullet->setRotation(Now_pao->getRotation());//�Ƕ�����̨�Ƕ����
		Bullet->runAction(CCSequence::create(
			ACT_FTY->cannon_jiguang_Boom(),
			CCCallFuncN::create(this, callfuncN_selector(gamescene::RemoveSpriteCallback)),
			NULL));
		FishNode->addChild(Bullet);
	}
	
}

void gamescene::BulletSuccedCallback(Node * Bullet)
{
	//�ӵ��ﵽ�յ��

	Bullet->removeFromParentAndCleanup(true);
	addChild(Bullet);

	switch (Bullet->getTag())
	{
		//1������Ч��
	case 1:Bullet->runAction(CCSequence::create(ACT_FTY->BullectBoom1(),
		CCCallFuncN::create(this, callfuncN_selector(gamescene::RemoveSpriteCallback)),
		NULL));break;
	case 2:Bullet->runAction(CCSequence::create(ACT_FTY->BullectBoom1(),
		CCCallFuncN::create(this, callfuncN_selector(gamescene::RemoveSpriteCallback)),
		NULL));break;
	case 3:Bullet->runAction(CCSequence::create(ACT_FTY->BullectBoom1(),
		CCCallFuncN::create(this, callfuncN_selector(gamescene::RemoveSpriteCallback)),
		NULL));break;
	case 4:Bullet->runAction(CCSequence::create(ACT_FTY->BullectBoom1(),
		CCCallFuncN::create(this, callfuncN_selector(gamescene::RemoveSpriteCallback)),
		NULL));break;

		//2������Ч��
	case 5:Bullet->runAction(CCSequence::create(ACT_FTY->BullectBoom2(),
		CCCallFuncN::create(this, callfuncN_selector(gamescene::RemoveSpriteCallback)),
		NULL));break;
	case 6:Bullet->runAction(CCSequence::create(ACT_FTY->BullectBoom2(),
		CCCallFuncN::create(this, callfuncN_selector(gamescene::RemoveSpriteCallback)),
		NULL));break;
	case 7:Bullet->runAction(CCSequence::create(ACT_FTY->BullectBoom2(),
		CCCallFuncN::create(this, callfuncN_selector(gamescene::RemoveSpriteCallback)),
		NULL));break;
	default:
		break;
	}

	int sundID = SimpleAudioEngine::sharedEngine()->playEffect("music/Bombette.mp3");
}

void gamescene::RemoveSpriteCallback(Node * node)
{
	//��� �ǽ�Ҿ���Ļ�
	if (node->getTag() >= 200) {
		m_I_bufferNumber += node->getTag() - 200;
	}
	//����Ǽ����ڵĻ�
	if (node->getName()== StringUtils::format("woshijiguang")) {
		JiguangEnd = true;
	}
	//��������뾫���ϵ����ж���
	node->removeFromParentAndCleanup(true);
}

void gamescene::ScaleCallback()
{
	if (now_Arms == is_Pao) {
		JiguangPao->setVisible(false);
		if (Now_pao == JiguangPao) 
			angle = JiguangPao->getRotation();
		else
			angle = pao[last_PaoNum]->getRotation();

		pao[last_PaoNum]->setVisible(false);
		pao[now_PaoNum]->setVisible(true);
		pao[now_PaoNum]->setScale(pao[last_PaoNum]->getScale());
		pao[now_PaoNum]->setRotation(angle);
		last_PaoNum = now_PaoNum;
		Now_pao = pao[now_PaoNum];
		Now_pao->runAction(CCScaleTo::create(0.5f, 1.f));
		PaoChangeSucced = true;;
	}
	else if(now_Arms == is_Jiguang){
		angle = Now_pao->getRotation();
		JiguangPao->setScale(Now_pao->getScale());
		JiguangPao->setRotation(angle);
		Now_pao->setVisible(false);
		Now_pao = JiguangPao;
		Now_pao->setVisible(true);
		Now_pao->runAction(CCScaleTo::create(0.5f, 1.f));
		PaoChangeSucced = true;
	}
	
}
