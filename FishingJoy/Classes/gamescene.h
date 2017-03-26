#ifndef gamescene_hpp
#define gamescene_hpp

#include"Header.h"
//Zֵ	��̨3 �ӵ�2 ��1
//tag	�ӵ�1-7	��101-
class gamescene :public Layer
{
private:
	//���������ӵ���ײ��ÿ0.2��ִ��һ��
	void collision(float dt);
	//���㹤��,1��ִ��һ��
	void FishFactory(float dt);

	//��̨�Ƕȵ�λ��Ļص����� �ӵ������﷢��
	void BulletFireCallback();
	//�ӵ�����Ŀ�����ߵ����ӵ����ʱ�Ļص�
	void BulletSuccedCallback(Node *Bullet);
	//ȫ������ִ����ɺ�Ļص���ɾ���ӵ�����ľ���
	void RemoveSpriteCallback(Node *node);
	//��̨�л�ʱ���ž���Ļص�
	void ScaleCallback();
	//�ڵ���ѹ�������ӵ������ڱ���
	Node*FishNode;//Z����Ϊ2
	Node*PauseNode;
	Node*rechargeNode;//��ֵ����
	enum fishFactory_Round {
		Round_one,
		Round_two,
		Round_three,
	}Now_Round;
	enum Arms {
		is_Pao,
		is_Jiguang,
	}now_Arms;
private:
	int last_PaoNum;//��һ����̨��� �����ж�
	int all_PaoNum;//��̨������
	int now_PaoNum;//��ǰ�����

	bool PaoChangeSucced;//�л���̨�Ƿ���ɣ�
	
	Sprite*pao[8];//��̨����
	Sprite*Now_pao;//��ǰ��ʾ��̨
	Sprite*JiguangPao;//������
	float angle;//��̨��ת�Ƕ�
	Vec2 m_TouchPoint;//����
	bool JiguangEnd;//�����Ƿ�����ϣ���Ϻ���ܷ���һ��

	Sprite*BackScene;

	TextAtlas*money;//�����ʾ���ı�
	int m_I_number;
	int m_I_bufferNumber;
	float GameTime;//��Ϸ����ʱ�䣬���ڿ�����ĳ��� 
public:
	static cocos2d::Scene* createScene();
	//��ť+
	void buttonJiaClickCallback(cocos2d::Ref* pSender);
	//��ť-
	void buttonJianClickCallback(cocos2d::Ref* pSender);
	//������ť
	void CameraButtonCallback(Ref *pSender);
	//�����������ְ�ť
	void ChangeBackMusicCallback(Ref *pSender);
	//��ͣ�ص�
	void PauseMenuCallback(Ref*pSender);
	//�����ص�
	void ContinueGameCallback(Ref*pSender);
	//�ص����˵�
	void sceneTomainCallback(Ref*pSender);
	//���򼤹���
	void jiguangPaoCallback(Ref*pSender);
	//�л� ����ͨ��
	void putongPaoCallback(Ref*pSender);
	virtual bool init();
	virtual void update(float dt);
	//�������
	bool onTouchBegan(Touch*touch, Event* event);
	//��������
	void onTouchMoved(Touch*touch, Event *event);
	//�뿪��Ļ
	void onTouchEnded(Touch*touch, Event *event);
	

	CREATE_FUNC(gamescene);


};

#endif /* gamescene_hpp */
