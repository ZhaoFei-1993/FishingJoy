
#ifndef ActionFactory_hpp
#define ActionFactory_hpp
#define ACT_FTY ActionFactory::getInstance()
#include"Header.h"

//�������� �ӵ����㡢�ȶ�����Դ
//plist����loading�м���
class ActionFactory
{
private:
	//С��-��
	Animate*fish_1_Move();
	Animate*fish_1_Die();
	//����-��
	Animate*fish_2_Move();
	Animate*fish_2_Die();
	//����-��
	Animate*fish_3_Move();
	Animate*fish_3_Die();
	//����-С
	Animate*fish_4_Move();
	Animate*fish_4_Die();

	//���T ��ɫ  ��
	Animate*fish_5_Move();
	Animate*fish_5_Die();

	//����-С
	Animate*fish_6_Move();
	Animate*fish_6_Die();

	//����-С
	Animate*fish_7_Move();
	Animate*fish_7_Die();

	//������-��
	Animate*fish_8_Move();
	Animate*fish_8_Die();

	//������-��
	Animate*fish_9_Move();
	Animate*fish_9_Die();

	//����-С-ͷ�ϴ�����
	Animate*fish_10_Move();
	Animate*fish_10_Die();

	//��С��
	Animate*fish_11_Move();
	Animate*fish_11_Die();

	//��С��-��ɫ
	Animate*fish_12_Move();
	Animate*fish_12_Die();

	//С��-��ɫ
	Animate*fish_13_Move();
	Animate*fish_13_Die();

	//С��-���ɫ
	Animate*fish_14_Move();
	Animate*fish_14_Die();

	//С��-��ɫ
	Animate*fish_15_Move();
	Animate*fish_15_Die();

	//С��-��ɫ
	Animate*fish_16_Move1();//С��
	Animate*fish_16_Move2();//����
	Animate*fish_16_Die();

	static ActionFactory*Instance;
public:
	static ActionFactory*getInstance();
	//ͨ����ĵ�ǰtag��ǩ��ȡ����,typeΪ1��ȡ����������Ĭ�ϻ�ȡ�ƶ��Ķ���
	Animate*GetFishAct_ByTag(int tag, int type = 0);
	//��̨���䶯��
	Animate*cannon_1_fire();
	Animate*cannon_2_fire();
	Animate*cannon_3_fire();
	Animate*cannon_4_fire();
	Animate*cannon_5_fire();
	Animate*cannon_6_fire();
	Animate*cannon_7_fire();
	Animate*cannon_jiguang_fire();
	Animate*cannon_jiguang_Boom();
	//�ӵ���ը
	Animate*BullectBoom1();
	Animate*BullectBoom2();
	//�ʺ�
	Animate*caiHong();
	//���
	Animate*Gold();
	//����ѡ�п�
	Animate*Select();
	
};

#endif /* ActionFactory_hpp */