#include "MyPG.h"
#include "MyGameMain.h"
extern int savex;
extern int savey;
namespace NewGame 
{
	DG::Font::SP fontA;
	DG::Image::SP img;
	void  Initialize()
	{
		img = DG::Image::Create("./data/image/ControllerAI.png");
		fontA = DG::Font::Create("MS ゴシック", 8, 24);
		savex = 16;
		savey = 16;
	}
	TaskFlag  UpDate()
	{
		auto inp = ge->in1->GetState();
		TaskFlag rtv = TaskFlag::NewGame;
		if (true == inp.ST.down)
		{
			rtv = TaskFlag::Game;
		}
	
		return rtv;
	}
	void  Render()
	{
		ML::Box2D src = ML::Box2D(0, 0, 480, 270);
		ML::Box2D draw = ML::Box2D(0, 0, 480, 270);
		img->Draw(draw, src);
		ML::Box2D textBox(130, 50, 480, 100);
		string text = "　　　　矢印鍵　移動\nZ　主武器　　　 X　副武器　\nA　リスタート　　S　終了";
		fontA->Draw(textBox, text, ML::Color(0.8f, 0.5f, 0.9f, 1.0f));
	}
	void  Finalize()
	{
		fontA.reset();
	}

}