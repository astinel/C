#pragma once
class object
{
public:
	object();
	~object();
	char x, y;			//장애물 좌표
	char speed;		//낙하 속도
	char pri[3] = "■";		//장애물 형태
};

