#include "MyPG.h"
#include "MyGameMain.h"
extern int savex;
namespace Ending {
	DG::Image::SP imgBG;
	DG::Image::SP black;
	int logoPosY;
	DG::Font::SP fontA;
	void Score_Draw();
	void Score_Update();
	int scoreNow;
	int scoreDigit;
	int time;

	void  Initialize()
	{
		fontA = DG::Font::Create("HGS 明朝B", 25, 32);//点数表示する文字
		imgBG = DG::Image::Create("./data/image/ResultAIRe.png");
		black = DG::Image::Create("./data/image/Black.png");
		logoPosY = -270;
		scoreNow = 0;
		scoreDigit = 0;
		time = 0;
	}
	void  Finalize()
	{
		imgBG.reset();
		fontA.reset();
		black.reset();
	}
	TaskFlag  UpDate()
	{
		auto inp = ge->in1->GetState();
		time++;
		if (scoreDigit < 5 && time % 3 == 0)Score_Update();


		logoPosY += 9;
		if (logoPosY > 0) { logoPosY = 0; }
		//logoPosY = min(logoPosY+9,0);
		TaskFlag rtv = TaskFlag::Ending;
		if (logoPosY >= 0)
		{
			if (true == inp.ST.down)
			{
				rtv = TaskFlag::Title;
			}
		}
		return rtv;
	}
	void  Render()
	{
		ML::Box2D draw(0, 0, 480, 270);
		draw.Offset(0, logoPosY);
		ML::Box2D src(0, 0, 480, 270);
		black->Draw(src, src);
		imgBG->Draw(draw, src);
		Score_Draw();
	}
	void Score_Update()//桁ごと表示
	{
		int tempScore=savex;
		int tempScore2 = scoreNow;
		int digit = 1;
		bool isZero=false;
		for (int i = 0; i < scoreDigit; i++)//今表示する桁を切り取る
		{
			tempScore /= 10;
			tempScore2 /= 10;
			digit *= 10;//桁数を記録
		}
		tempScore %= 10;
		if (tempScore2 < 10)tempScore2++;//まず1~9を表示
		if(tempScore2==10)//それから本当の数字を表示、次の桁へ進む
		{
			tempScore2 = tempScore;
			scoreDigit++;
		}
		scoreNow = (scoreNow % digit) + (tempScore2 % 10) * digit;
		se::Play("ScoreUp");//スコアアップ音声
	}
	void Score_Draw()
	{
		std::string st = to_string(scoreNow);
		st.insert(st.begin(), 5 - st.length(), '0');//まだ表示していない点数は0にする
		ML::Box2D textBox = ML::Box2D(165, 160, 150, 32);
		fontA->Draw(textBox, st, ML::Color(1.0f, 1.0f, 1.0f, 1.0f));

	}
	
}