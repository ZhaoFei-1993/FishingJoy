#ifndef loadscene_hpp
#define loadscene_hpp
#include"Header.h"
#include "SceneManagement.h"

class loadscene :public Layer
{
private:
	int m_nNumberOfResource; //������Դ����
	int m_nNumberOfLoadedResource; //���������Դ��
	Text*m_pLabelPercent;//�ٷֱȱ�ǩ
	LoadingBar *LoadingBar1;//������һ
	LoadingBar *LoadingBar2;//��������
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(loadscene);
	void onLoadingCallback(Texture2D* texture);
	virtual void onEnterTransitionDidFinish();
};

#endif /* loadscene_hpp */
