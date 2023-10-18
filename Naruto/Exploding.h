#ifndef __Exploding_h__ //무조건 헤더로만 씀
#define __Exploding_h__ //백업파일을 만들지 않음

#include "GObject.h"

class CExploding : public CGObject
{
public:
	CExploding();
	~CExploding();
	void Draw(LPDIRECTDRAWSURFACE7 lpSurface);
};


#endif
