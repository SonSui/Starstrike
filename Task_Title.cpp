#include "MyPG.h"
#include "MyGameMain.h"

namespace Title
{
	int logoPosY;
	DG::Image::SP img;
	DG::Image::SP black;
	DG::Font::SP fontA;
	int to = 0;
	bool forward = false;
	bool isStart = false;
	void Initialize()
	{
		img = DG::Image::Create("./data/image/TitleAI3.png");
		black = DG::Image::Create("./data/image/Black.png");
		fontA = DG::Font::Create("HGS 明朝B", 12,20);
		logoPosY = -270;
		bgm::Stop("bgm1");
		bgm::Play("bgmTitle");
		forward = false;
		isStart = false;
	}
	void Finalize()
	{
		img.reset();
		black.reset();
		fontA.reset();
	}
	TaskFlag UpDate()
	{
		auto inp = ge->in1->GetState();
		logoPosY += 9;
		if (logoPosY > 0)
		{
			logoPosY = 0; 
			isStart = true;
		}
		//透明度コントローラー
		if (isStart && forward==false)
		{
			to+=2;
			if (to >= 100)
			{
				to = 100;
				forward = true;
			}
		}
		else if (isStart && forward==true)
		{
			to-=2;
			if(to<=1)
			{
				to = 1;
				forward = false;
			}
		}
		TaskFlag rtv = TaskFlag::Title;
		if (logoPosY >= 0) 
		{
			if (true == inp.ST.down)
			{
				rtv = TaskFlag::NewGame;
			}
		}
		return rtv;
	}
	void Render()
	{
		ML::Box2D draw(0, 0, 480, 270);
		draw.Offset(0, logoPosY);
		ML::Box2D src(0, 0, 480, 270);
		black->Draw(src, src);
		img->Draw(draw, src);
		ML::Box2D textBox = ML::Box2D(180, 200, 200, 50);
		string text = "S　START";
		float t = (float)to / 100.0f;
		fontA->Draw(textBox, text, ML::Color(t, 0.5f, 0.9f, 1.0f));
	}
}