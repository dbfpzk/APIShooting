#ifndef __Exploding_h__ //������ ����θ� ��
#define __Exploding_h__ //��������� ������ ����

#include "GObject.h"

class CExploding : public CGObject
{
public:
	CExploding();
	~CExploding();
	void Draw(LPDIRECTDRAWSURFACE7 lpSurface);
};


#endif
