#include "MyPG.h"
#include "MyGameMain.h"

extern int savex;
extern int savey;
namespace Game
{
	const int fps = 24;
	const int maxx = 480, maxy = 270;//screen size
	const int shotw = 32, shoth = 32;
	const int enemyw = 40, enemyh = 40;
	const int playerw = 64, playerh = 25;
	const int enemyshotw = 10, enemyshoth = 10;
	DG::Image::SP imgPlayer, imgShot;
	DG::Image::SP imgEnemy, imgEnemy2, imgEnemy3;
	DG::Image::SP imgBackground;
	DG::Image::SP imgBackground1, imgBackground2, imgBackground3 ;
	DG::Image::SP imgBomb;
	DG::Image::SP imgLife;

	DG::Image::SP bossBody;
	DG::Image::SP bossEngine;
	DG::Image::SP bossLazer;
	DG::Image::SP bossDestruct;

	XI::GamePad::SP in1;
	XI::GamePad::SP in2;

	DG::Font::SP fontA;
	DG::Image::SP fontBack;
	string text;
	enum class State { Normal, Hit, Non };
	struct Chara {
		State state;
		int typeNum;
		int x, y;
		float fx, fy;
		ML::Box2D hitBase;
		int moveCnt;
		int animCnt;
		int mode;
		int score;
		int damage;
		int life;
		int shiled, shiledMax;
		float angle;
		int speed;
		int targetType, targetIndex;
	};
	Chara player;
	Chara shiled;
	Chara shots[50];
	Chara bombs[60];
	Chara enemys[61];
	Chara backs[7];
	Chara enemyShots[60];
	Chara nullObj;
	Chara boss;
	Chara bossShot[30];
	Chara bossDes;

	//int speed;
	int timeCnt;
	int totalScore;
	int playerShotATimeCnt;
	int playerShotBTimeCnt;
	int exitCountDown;
	int lifeMax;
	bool isBossDestory;
	bool isBoss;
	int bossAct;
	int bossActCD;


	bool Hit(ML::Box2D a, ML::Box2D b);
	int FindNearestEnemy(Chara c_);

	void Back_Initialize(Chara& c_, int t);
	void Player_Initialize(Chara& c_, int x_, int y_);
	void PlayerShot_Initialize(Chara& c_, int type_);
	void PlayerShotA_Initialize(Chara& c_);
	void PlayerShotB_Initialize(Chara& c_);
	void Bomb_Initialize(Chara& c_, int x_, int y_);
	void Enemy_Initialize(Chara& c_, int tn_, int x_, int y_);
	void EnemyA_Initialize(Chara& c_, int x_, int y_);
	void EnemyB_Initialize(Chara& c_, int x_, int y_);
	void EnemyC_Initialize(Chara& c_, int x_, int y_);
	void EnemyShot_Initialize(Chara& c_, int type_);
	void EnemyShotA_Initialize(Chara& c_);
	void EnemyShotB_Initialize(Chara& c_);
	void EnemyShotC_Initialize(Chara& c_);
	void Boss_Initialize(Chara& c_);
	void BossShot_Initialize(Chara& c_, int type_);
	void BossShotA_Initialize(Chara& c_);
	void BossShotB_Initialize(Chara& c_);

	void Enemy_AppearTimer();
	void Enemy_Appear(int ID, int x_, int y_);
	void Shot_Appear(int x_, int y_, int tn_);
	void ShotA_Appear(int x_, int y_);
	void ShotB_Appear(int x_, int y_);
	void Shot_Move(Chara& c_);
	void ShotA_Move(Chara& c_);
	void ShotB_Move(Chara& c_);
	void Shot_Update(Chara& c_, int x_, int y_);
	void Enemy_Update(Chara& c_);
	void EnemyA_Update(Chara& c_);
	void EnemyB_Update(Chara& c_);
	void EnemyC_Update(Chara& c_);
	void EnemyShot_Update(Chara& c_, int type);
	void EnemyShotA_Update(Chara& c_);
	void EnemyShotB_Update(Chara& c_);
	void EnemyShotC_Update(Chara& c_);
	void EnemyShot_HitPlayer(Chara& c_);
	void Boss_Update(Chara& c_);
	void BossShot_Update(Chara& c_,int type);
	void BossShotA_Update(Chara& c_);
	void BossShotB_Update(Chara& c_);
	void BossActA_Update(Chara& c_,int cd);
	void BossActB_Update(Chara& c_,int cd);
	void BossActC_Update(Chara& c_,int cd);
	void Boss_Appear(Chara& c_,int x,int y);
	void Boss_Destruct(int x, int y);

	void Enemy_HitCheckPlayers_Std(Chara& c_);
	void Bomb_Update(Chara& c_);
	void Bomb_Appear(int x_, int y_);
	void Back_Update(Chara& c_,int t);
	TaskFlag GameManager();

	void Player_Draw(Chara& c_);
	void PlayerShot_Draw(Chara& c_, ML::Box2D s_, ML::Box2D p_,int type);
	void PlayerShotA_Draw(Chara& c_, ML::Box2D s_, ML::Box2D p_);
	void PlayerShotB_Draw(Chara& c_, ML::Box2D s_, ML::Box2D p_);
	void Enemy_Draw(Chara& c_);
	void EnemyA_Draw(Chara& c_);
	void EnemyB_Draw(Chara& c_);
	void EnemyC_Draw(Chara& c_);
	void EnemyShot_Draw(Chara& c_,int type);
	void EnemyShotA_Draw(Chara& c_);
	void EnemyShotB_Draw(Chara& c_);
	void EnemyShotC_Draw(Chara& c_);
	void Bomb_Draw(Chara& c_);
	void Back_Draw(Chara& c_,int t);
	void Score_Draw();
	void Life_Draw();
	void Boss_Draw(Chara& c_);
	void BossShot_Draw(Chara& c_,int type);
	void BossShotA_Draw(Chara& c_);
	void BossShotB_Draw(Chara& c_);
	void BossDestruct_Draw(Chara& c_);


	//---------------------MAIN--------------------------------
	void Initialize()
	{
		srand((unsigned int)time(NULL));
		imgBackground = DG::Image::Create("./data/image/parallax-space-backgound_480_270.png");//背景
		imgBackground1 = DG::Image::Create("./data/image/parallax-space-far-planets_480_270.png");//背景
		imgBackground2 = DG::Image::Create("./data/image/parallax-space-big-planet_150_148.png");//背景
		imgBackground3 = DG::Image::Create("./data/image/parallax-space-stars_270_480.png");//背景
		
		imgPlayer = DG::Image::Create("./data/image/player.png");//player
		imgShot = DG::Image::Create("./data/image/Shot.png");//弾
		imgEnemy = DG::Image::Create("./data/image/Enemy1.png");//敵
		imgEnemy2 = DG::Image::Create("./data/image/Enemy2.png");
		imgEnemy3 = DG::Image::Create("./data/image/Enemy3.png");
		imgBomb = DG::Image::Create("./data/image/bomb.png");//爆発エフェクト
		imgLife = DG::Image::Create("./data/image/06.png");

		//ボスに関する画像
		bossBody = DG::Image::Create("./data/image/DreadnoughtBody.png");
		bossEngine = DG::Image::Create("./data/image/DreadnoughtEngine.png");
		bossLazer = DG::Image::Create("./data/image/DreadnoughtLazer.png");
		bossDestruct = DG::Image::Create("./data/image/DreadnoughtDestruction.png");




		fontA = DG::Font::Create("HGS 明朝B", 20, 32);//点数表示する文字
		fontBack = DG::Image::Create("./data/image/shot5_exp3.png");//点数の背景



		//背景初期化
		for (int b = 0; b < 7; b++)
		{
			Back_Initialize(backs[b], b);
		}
		//プレイヤー初期化
		Player_Initialize(player, 50, maxy / 2);
		//プレイヤーの弾を初期化
		for (int s = 0; s < 25; s++)
		{
			//２種類の弾
			PlayerShot_Initialize(shots[s], 0);
			PlayerShot_Initialize(shots[25 + s], 1);
		}

		//爆発エフェクトの初期化
		for (int b = 0; b < 60; b++)
		{
			Bomb_Initialize(bombs[b], 0, 0);
		}
		bossDes.state = State::Non;
		bossDes.animCnt = 0;

		//敵を初期化
		for (int e = 0; e < 20; e++)
		{
			//３種類の敵
			Enemy_Initialize(enemys[e], 0, 480 + 32, 60);
			Enemy_Initialize(enemys[e + 20], 1, 480 + 32, 210);
			Enemy_Initialize(enemys[e + 40], 2, 480 + 32, 100);
			//検索値を記録
			enemys[e].targetIndex = e;
			enemys[e + 20].targetIndex = e + 20;
			enemys[e + 40].targetIndex = e + 40;
			//敵の弾もともに
			EnemyShot_Initialize(enemyShots[e], 0);
			EnemyShot_Initialize(enemyShots[e + 20], 1);
			EnemyShot_Initialize(enemyShots[e + 40], 2);
		}
		Boss_Initialize(enemys[60]);
		BossShot_Initialize(bossShot[0], 0);
		for (int s = 1; s < 30; s++)
		{
			BossShot_Initialize(bossShot[s], 1);
		}

		timeCnt = 0;//ゲームのフレーム時間
		totalScore = 0;//点数
		nullObj.state = State::Non;//NULLオブジェクト

		//プレヤーの弾の制限時間
		playerShotATimeCnt = 0;
		playerShotBTimeCnt = 0;
		exitCountDown = 1e9;//プレヤーが死んだら退出の時間
		lifeMax = 4;//プレイヤーのいのち
		isBoss = false;//ボスが出るか
		isBossDestory = false;
		
		//音楽
		bgm::Stop("bgmTitle");
		bgm::Play("bgm1");
	}

	void Finalize()
	{
		imgBackground.reset();
		imgBackground1.reset();
		imgBackground2.reset();
		imgBackground3.reset();
		imgPlayer.reset();
		imgShot.reset();
		imgEnemy.reset();
		imgEnemy2.reset();
		imgBomb.reset();
		imgLife.reset();
		in1.reset();
		in2.reset();
		fontA.reset();
		fontBack.reset();

		bossBody.reset();
		bossEngine.reset();
		bossLazer.reset();
		bossDestruct.reset();

	}

	TaskFlag UpDate()
	{
		auto inp = ge->in1->GetState();
		//プレイヤー
		if (player.state !=State::Non)
		{
			if (player.state == State::Hit) player.state = State::Normal;
			if (inp.LStick.BL.on) { player.x -= player.speed; }
			if (inp.LStick.BR.on) { player.x += player.speed; }
			if (inp.LStick.BU.on) { player.y -= player.speed; }
			if (inp.LStick.BD.on) { player.y += player.speed; }
			//プレイヤー移動範囲制限
			if (player.x < playerw / 2)player.x = playerw / 2;
			if (player.x > maxx - playerw / 2)player.x = maxx - playerw / 2;
			if (player.y < playerh / 2)player.y = playerh / 2;
			if (player.y > maxy - playerh / 2)player.y = maxy - playerh / 2;

			if (inp.B1.on&& playerShotATimeCnt==0) {
				//主武器発射
				Shot_Appear(player.x + 20, player.y, 0);
			}
			if (inp.B2.on&& playerShotBTimeCnt==0)
			{
				//副武器発射
				Shot_Appear(player.x + 20, player.y, 1);
			}
		}
		//弾の間隔
		if (playerShotATimeCnt != 0)playerShotATimeCnt++;
		if (playerShotBTimeCnt != 0)playerShotBTimeCnt++;
		if (playerShotATimeCnt > 12)playerShotATimeCnt = 0;//0.5秒ごと主弾発射
		if (playerShotBTimeCnt > 24 * 3)playerShotBTimeCnt = 0;//3秒ごと副弾発射

		//敵が現す時間管理
		Enemy_AppearTimer();
		timeCnt++;
		
		//敵の行為
		for (int e = 0; e < 60; e++)
		{
			Enemy_Update(enemys[e]);
			EnemyShot_Update(enemys[e], e / 20);
		}
		if (isBoss && !isBossDestory)
		{
			Boss_Update(enemys[60]);
		}
		if (isBoss && isBossDestory)
		{
			Boss_Destruct(enemys[60].x, enemys[60].y);
		}
		//背景
		for (int b = 0; b < 7; b++)
		{
			Back_Update(backs[b],b);
		}
		//爆発エフェクト
		for (int b = 0; b < 30; b++)
		{
			Bomb_Update(bombs[b]);
		}


		for (int s = 0; s < 50; s++)
		{	//player弾の移動
			Shot_Move(shots[s]);
			Shot_Move(shots[s]);
		}
		
		
		//シーン切り替え管理
		TaskFlag rtv = GameManager();
		if (true == inp.ST.down) {
			rtv = TaskFlag::Ending;
		}
		if (true == inp.SE.down)
		{
			rtv = TaskFlag::Title;
		}
		return rtv;
	}
	void Render()
	{
		ML::Box2D textBox(0, 0, 480, 270);
		ML::Box2D playerShot_pos(0, 96, 32, 32);
		ML::Box2D enemyShot_pos(3, 195, 10, 10);
		//背景描画
		for (int b = 0; b < 7; b++)
		{
			Back_Draw(backs[b],b);
		}
		//プレイヤー
		Player_Draw(player);
		//player弾
		for (int s = 0; s < 10; ++s)
		{
			PlayerShot_Draw(shots[s], ML::Box2D(-16, -16, 32, 32), playerShot_pos,0);
			PlayerShot_Draw(shots[s+25], ML::Box2D(-8, -8, 16, 16), ML::Box2D(0, 32, 16, 16),1);
		}
		//敵
		for (int e = 0; e < 60; e++)
		{
			Enemy_Draw(enemys[e]);
		}
		
		if (isBoss && !isBossDestory)
		{
			BossShotA_Draw(bossShot[0]);
			Boss_Draw(enemys[60]);
		}
		//敵の弾
		for (int es = 0; es < 60; es++)
		{
			EnemyShot_Draw(enemyShots[es], es / 20);
		}
		//爆発エフェクト
		for (int c = 0; c < 60; c++)
		{
			Bomb_Draw(bombs[c]);
		}
		if (isBossDestory)
		{
			BossDestruct_Draw(bossDes);
		}
		//点数
		Score_Draw();
		//プレイヤーのHP
		Life_Draw();
	}


	//---------------------機能-----------------------------------
	//当たり判定
	bool Hit(ML::Box2D a, ML::Box2D b)
	{
		if (a.x < b.x + b.w)
		{
			if (a.x + a.w > b.x)
			{
				if (a.y < b.y + b.h)
				{
					if (a.y + a.h > b.y)
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	//最寄の敵(の鍵)
	int FindNearestEnemy(Chara c_)
	{
		int  minDistance = 0x7FFFFFFF;
		int id = -1;
		int distance;
		int x = c_.x;
		int y = c_.y;
		for (int e = 0; e < 61; e++)
		{
			if (enemys[e].state == State::Normal)
			{
				distance = (x - enemys[e].x) * (x - enemys[e].x) + (y - enemys[e].y) * (y - enemys[e].y);
				if (distance < minDistance)
				{
					id = e;
					minDistance = distance;
				}
			}
		}
		//if (id == -1)return nullObj;
		return id;//enemys[id];
	}

	//---------------------INITIALIZE-----------------------------
	//背景初期化
	void Back_Initialize(Chara& c_, int t)
	{
		//四つの背景、ループで表示
		switch (t)
		{
		case 0:
			c_.state = State::Normal;
			c_.x = 0;
			c_.y = 0;
			c_.hitBase = ML::Box2D(0, 0, 480, 270);
			break;
		case 1:
			c_.state = State::Normal;
			c_.x = 0;
			c_.y = 0;
			c_.hitBase = ML::Box2D(0, 0, 480, 270);
			break;
		case 2:
			c_.state = State::Normal;
			c_.x = 480;
			c_.y = 0;
			c_.hitBase = ML::Box2D(480, 0, 480, 270);
			break;
		case 3:
			c_.state = State::Normal;
			c_.x = 0;
			c_.y = 0;
			c_.hitBase = ML::Box2D(0, 100, 150, 148);
			break;
		case 4:
			c_.state = State::Normal;
			c_.x = 480;
			c_.y = 0;
			c_.hitBase = ML::Box2D(480, 100, 150, 148);
			break;
		case 5:
			c_.state = State::Normal;
			c_.x = 0;
			c_.y = 0;
			c_.hitBase = ML::Box2D(0, 0, 480,270);
			c_.animCnt = 0;
			break;
		case 6:
			c_.state = State::Normal;
			c_.x = 480;
			c_.y = 0;
			c_.hitBase = ML::Box2D(480, 0, 480, 270);
			c_.animCnt = 0;
			break;
		}
		
	}
	//プレイヤー初期化
	void Player_Initialize(Chara& c_, int x_, int y_)
	{
		c_.state = State::Normal;
		c_.x = x_;
		c_.y = y_;
		c_.fx = x_;
		c_.fy = y_;
		c_.hitBase = ML::Box2D(-(playerw - 20) / 2, -(playerh - 16) / 2, playerw - 20, playerh - 16);
		c_.speed = 3;
		c_.moveCnt = 0;
		c_.animCnt = 0;
		c_.damage = 10;
		c_.life = 4;
		c_.shiledMax = 5;
		c_.shiled = c_.shiledMax;
		c_.angle = 0;
		c_.mode = 0;
	}
	//プレイヤーの弾初期化
	void PlayerShot_Initialize(Chara& c_, int type_)
	{

		switch (type_)
		{
		case 0:
			PlayerShotA_Initialize(c_);
			break;
		case 1:PlayerShotB_Initialize(c_);
			break;
		}
	}
	void PlayerShotA_Initialize(Chara& c_)
	{
		c_.typeNum = 0;
		c_.state = State::Non;
		c_.speed = 4;
		c_.hitBase = ML::Box2D(-4, -4, 8, 8);
		c_.moveCnt = 0;
		c_.animCnt = 0;
		c_.angle = 0;
		c_.mode = 0;
		c_.damage = 2;
		c_.targetType = 1;
	}
	void PlayerShotB_Initialize(Chara& c_)
	{
		c_.typeNum = 1;
		c_.state = State::Non;
		c_.speed = 2;
		c_.hitBase = ML::Box2D(-4, -4, 8, 8);
		c_.moveCnt = 0;
		c_.angle = 0;
		c_.mode = 0;
		c_.animCnt = 0;
		c_.damage = 1;
		c_.targetType = 1;
		c_.targetIndex = -1;
	}
	//爆発エフェクト初期化
	void Bomb_Initialize(Chara& c_, int x_, int y_)
	{
		c_.state = State::Non;
		c_.x = x_;
		c_.y = y_;
		c_.hitBase = ML::Box2D(-16, -16, 32, 32);
		c_.moveCnt = 0;
		c_.animCnt = 0;
	}
	//敵の初期化
	void Enemy_Initialize(Chara& c_, int tn_, int x_, int y_)
	{
		switch (tn_)
		{
		case 0:EnemyA_Initialize(c_, x_, y_); break;
		case 1:EnemyB_Initialize(c_, x_, y_); break;
		case 2:EnemyC_Initialize(c_, x_, y_); break;
		}
	}
	void EnemyA_Initialize(Chara& c_, int x_, int y_)
	{
		c_.state = State::Non;
		c_.x = x_;
		c_.y = y_;
		c_.moveCnt = 0;
		c_.animCnt = 0;
		c_.mode = 0;
		c_.hitBase = ML::Box2D(-20, -20, 40, 40);
		c_.typeNum = 0;
		c_.life = 1;
		c_.damage = 100;
		c_.score = 99;
		c_.targetType = 0;
	}
	void EnemyB_Initialize(Chara& c_, int x_, int y_)
	{
		c_.state = State::Non;
		c_.x = x_;
		c_.y = y_;
		c_.moveCnt = 0;
		c_.animCnt = 0;
		c_.mode = 0;
		c_.hitBase = ML::Box2D(-16, -16, 32, 32);
		c_.typeNum = 1;
		c_.life = 2;
		c_.damage = 100;
		c_.score = 122;
		c_.targetType = 0;
	}
	void EnemyC_Initialize(Chara& c_, int x_, int y_)
	{
		c_.state = State::Non;
		c_.x = x_;
		c_.y = y_;
		c_.moveCnt = 0;
		c_.animCnt = 0;
		c_.mode = 0;
		c_.hitBase = ML::Box2D(-20, -20, 40, 40);
		c_.typeNum = 2;
		c_.life = 3;
		c_.damage = 100;
		c_.score = 503;
		c_.targetType = 0;
	}
	void Boss_Initialize(Chara& c_)
	{
		c_.state = State::Non;
		c_.moveCnt = 0;
		c_.animCnt = 0;
		c_.mode = 0;
		c_.hitBase = ML::Box2D(-64, -32, 128, 64);
		c_.typeNum = 10;
		c_.life = 180;
		c_.damage = 100;
		c_.score = 15000;
		c_.targetType = 0;
	}
	//敵の弾の初期化
	void EnemyShot_Initialize(Chara& c_, int type_)
	{
		switch (type_)
		{
		case 0:EnemyShotA_Initialize(c_); break;
		case 1:EnemyShotB_Initialize(c_); break;
		case 2:EnemyShotC_Initialize(c_); break;
		}
	}
	void EnemyShotA_Initialize(Chara& c_)
	{
		c_.typeNum = 0;
		c_.state = State::Non;
		c_.x = 0;
		c_.y = 0;
		c_.fx = 0;
		c_.fy = 0;
		c_.hitBase = ML::Box2D(-4, -4, 8, 8);
		c_.damage = 1;
		c_.moveCnt = 0;
		c_.animCnt = 0;
		c_.angle = 0;
		c_.mode = 0;
		c_.speed = 2;
		c_.targetType = 0;
	}
	void EnemyShotB_Initialize(Chara& c_)
	{
		c_.typeNum = 1;
		c_.state = State::Non;
		c_.x = 0;
		c_.y = 0;
		c_.fx = 0;
		c_.fy = 0;
		c_.hitBase = ML::Box2D(-4, -4, 8, 8);
		c_.damage = 1;
		c_.moveCnt = 0;
		c_.animCnt = 0;
		c_.angle = 0;
		c_.mode = 0;
		c_.speed = 3;
		c_.targetType = 0;
	}
	void EnemyShotC_Initialize(Chara& c_)
	{
		c_.typeNum = 2;
		c_.state = State::Non;
		c_.x = 0;
		c_.y = 0;
		c_.fx = 0;
		c_.fy = 0;
		c_.hitBase = ML::Box2D(-4, -4, 8, 8);
		c_.damage = 2;
		c_.moveCnt = 0;
		c_.animCnt = 0;
		c_.angle = 0;
		c_.mode = 0;
		c_.speed = 3;
		c_.targetType = 0;
	}
	void BossShot_Initialize(Chara& c_, int type)
	{
		switch (type)
		{
		case 0:BossShotA_Initialize(c_); break;
		case 1:BossShotB_Initialize(c_); break;
		}
	}
	void BossShotA_Initialize(Chara& c_)
	{
		c_.typeNum = 0;
		c_.state = State::Non;
		c_.x = 0;
		c_.y = 0;
		c_.fx = 0;
		c_.fy = 0;
		c_.hitBase = ML::Box2D(-500, -15, 500, 30);
		c_.damage = 1;
		c_.moveCnt = 0;
		c_.animCnt = 0;
		c_.angle = 0;
		c_.mode = 0;
		c_.speed = 0;
		c_.targetType = 0;
	}
	void BossShotB_Initialize(Chara& c_)
	{
		c_.typeNum = 1;
		c_.state = State::Non;
		c_.x = 0;
		c_.y = 0;
		c_.fx = 0;
		c_.fy = 0;
		c_.hitBase = ML::Box2D(-4, -4, 8, 8);
		c_.damage = 2;
		c_.moveCnt = 0;
		c_.animCnt = 0;
		c_.angle = 0;
		c_.mode = 0;
		c_.speed = 3;
		c_.targetType = 0;
	}

	//---------------------UPDATE--------------------------------
	//敵が表す時間表
	void Enemy_AppearTimer()
	{
		struct sAppearData {
			int appTime;
			int ID;
			int x, y;
		};
		sAppearData ad[] = {
			{50,10,500,60},
			{50,30,500,210},
			{50,50,500,110},
			{50,51,500,160},

			{100,0,500,60},
			{120,1,500,60},
			{140,2,500,60},
			{160,3,500,60},
			{180,4,500,60},

			{300,20,500,210},
			{320,21,500,210},
			{340,22,500,210},
			{360,23,500,210},
			{380,24,500,210},

			{600,40,500,60},
			{600,41,500,210},
			{620,42,500,60},
			{620,43,500,210},
			{640,44,500,60},
			{640,45,500,210},
			{660,46,500,60},
			{660,47,500,210},
			{680,48,500,60},
			{680,49,500,210},
		};
		for (int i = 0; i < _countof(ad); i++)
		{
			if (timeCnt == ad[i].appTime) {
				Enemy_Appear(ad[i].ID, ad[i].x, ad[i].y);
			}
		}
		if (timeCnt > 700 && ((timeCnt - 700) % 20 == 0 )&& timeCnt < 2400)//700フレームからランダム
		{
			int rangeY = 200;
			int rID = rand() % 60;
			if (rID < 40)rangeY = 150;
			int rY = rand() % rangeY+(270-rangeY)/2;
			Enemy_Appear(rID, 500, rY);
		}
		if (timeCnt > 2500 && isBoss == false)
		{
			isBoss = true;
			Boss_Appear(enemys[60],500,135);
		}


	}
	void Enemy_Appear(int ID, int x_, int y_)
	{
		if (enemys[ID].state == State::Non)
		{
			Enemy_Initialize(enemys[ID], ID / 20, x_, y_);
			enemys[ID].state = State::Normal;
			enemys[ID].x = x_;
			enemys[ID].y = y_;
			enemys[ID].fx = x_;
			enemys[ID].fy = y_;
		}

	}
	//プレイヤーの弾を発射
	void Shot_Appear(int x_, int y_, int tn_)
	{
		switch (tn_)
		{
		case 0:ShotA_Appear(x_, y_); break;
		case 1:ShotB_Appear(x_, y_); break;
		}
	}
	void ShotA_Appear(int x_, int y_)
	{
		//player shotA appear
		for (int s = 0; s < 25; s++)
		{
			if (shots[s].state == State::Non)
			{
				shots[s].state = State::Normal;
				shots[s].x = x_;
				shots[s].y = y_;
				shots[s].hitBase = ML::Box2D(-6, -6, 12, 12);
				shots[s].animCnt = 0;
				playerShotATimeCnt++;
				se::Play("PlayerShot1");
				break;
			}
		}
	}
	void ShotB_Appear(int x_, int y_)
	{
		//player shot appear
		for (int s = 25; s < 50; s++)
		{
			if (shots[s].state == State::Non)
			{
				shots[s].state = State::Normal;
				shots[s].x = x_;
				shots[s].y = y_;
				shots[s].fx = x_;
				shots[s].fy = y_;
				shots[s].mode = 0;
				shots[s].hitBase = ML::Box2D(-4, -4, 8, 8);
				shots[s].targetIndex = -1;
				shots[s].animCnt = 0;
				playerShotBTimeCnt++;
				break;
			}
		}
	}
	//プレイヤーの弾の移動
	void Shot_Move(Chara& c_)
	{
		switch (c_.typeNum)
		{
		case 0:ShotA_Move(c_); break;
		case 1:ShotB_Move(c_); break;
		}
	}
	//横移動の弾
	void ShotA_Move(Chara& c_)
	{
		if (c_.state == State::Normal)
		{
			Shot_Update(c_, c_.x + c_.speed, c_.y);
			if (c_.state == State::Normal)
			{
				ML::Box2D me = c_.hitBase.OffsetCopy(c_.x, c_.y);
				for (int e = 0; e < 61; e++)
				{
					if (enemys[e].state == State::Normal)
					{
						ML::Box2D you = enemys[e].hitBase.OffsetCopy(enemys[e].x, enemys[e].y);
						if (Hit(me, you))
						{
							enemys[e].life -= c_.damage;
							if (enemys[e].life <= 0)
							{
								enemys[e].state = State::Non;
								totalScore += enemys[e].score;
								Bomb_Appear(enemys[e].x, enemys[e].y);
								if (e == 60 && isBoss)
								{
									isBossDestory = true;
								}
							}
							else enemys[e].state = State::Hit;
							c_.state = State::Non;
							break;
						}
					}
				}

			}
		}
	}
	//追跡する弾
	void ShotB_Move(Chara& c_)
	{
		if (c_.state == State::Normal)
		{
			switch (c_.mode)
			{
			case 0:
				//最初は追跡しない
				c_.angle = 45;
				c_.fx += cos(c_.angle) * c_.speed;
				c_.fy += sin(c_.angle) * c_.speed;
				//小数のデータをよく保存
				c_.x = (int)c_.fx;
				c_.y = (int)c_.fy;
				Shot_Update(c_, c_.x, c_.y);
				c_.moveCnt++;
				if (c_.moveCnt > 20) {
					c_.mode = 1;
					c_.moveCnt = 0;
				}
				break;
			case 1:
				if(c_.targetIndex !=-1&&enemys[c_.targetIndex].state==State::Normal)
				{
					//追跡目標を確認
					Chara *target = &enemys[c_.targetIndex];
					float mx = target->x - c_.x;
					float my = target->y - c_.y;
					float tempAngle = atan2(my, mx);
					c_.angle = tempAngle;
				}
				else
				{
					int id = FindNearestEnemy(c_);
					c_.targetIndex = id;
				}
				c_.fx += cos(c_.angle) * c_.speed;
				c_.fy += sin(c_.angle) * c_.speed;
				c_.x = (int)c_.fx;
				c_.y = (int)c_.fy;
				Shot_Update(c_, c_.x, c_.y);
				c_.moveCnt++;
			}

			if (c_.state == State::Normal)
			{
				ML::Box2D me = c_.hitBase.OffsetCopy(c_.x, c_.y);
				for (int e = 0; e < 61; e++)
				{
					if (enemys[e].state == State::Normal)
					{
						ML::Box2D you = enemys[e].hitBase.OffsetCopy(enemys[e].x, enemys[e].y);
						if (Hit(me, you))
						{
							enemys[e].life -= c_.damage;
							if (enemys[e].life <= 0)
							{
								enemys[e].state = State::Non;
								totalScore += enemys[e].score;
								Bomb_Appear(enemys[e].x, enemys[e].y);
								if (e == 60 && isBoss)
								{
									isBossDestory = true;
								}
							}
							else enemys[e].state = State::Hit;
							c_.state = State::Non;
							c_.moveCnt = 0;
							c_.mode = 0;
							break;
						}
					}
				}

			}
		}
	}
	void Shot_Update(Chara& c_, int x_, int y_)
	{
		//スクリーンから出る判定
		if (c_.state == State::Normal)
		{
			c_.animCnt++;
			if (x_ > maxx + shotw / 2 || x_ < -enemyshotw / 2)
			{
				c_.state = State::Non;
				
				return;
			}
			else if (y_ > maxy + shoth / 2 || y_ < -shoth / 2)
			{
				c_.state = State::Non;
			
				return;
			}
			c_.x = x_;
			c_.y = y_;
		}
	}
	//敵の行動
	void Enemy_Update(Chara& c_)
	{
		switch (c_.typeNum) {
		case 0:EnemyA_Update(c_); break;
		case 1:EnemyB_Update(c_); break;
		case 2:EnemyC_Update(c_); break;
		}
	}
	void EnemyA_Update(Chara& c_)
	{
		if (c_.state != State::Non) {
			if (c_.state == State::Hit)c_.state = State::Normal;
			switch (c_.mode) {
			case 0:
				c_.x -= 2;
				c_.moveCnt++;
				if (c_.moveCnt > 100) {
					c_.mode = 1;
					c_.moveCnt = 0;
				}
				break;
			case 1:
				c_.x += 1;
				c_.y += 1;
				c_.moveCnt++;
				if (c_.moveCnt > 50)
				{
					c_.mode = 2;
					c_.moveCnt = 0;
				}
				break;
			case 2:
				c_.x -= 2;
				c_.moveCnt++;
				break;
			}
			if (c_.x + 32 < 0)
			{
				c_.state = State::Non;
			}
			c_.animCnt++;
			Enemy_HitCheckPlayers_Std(c_);

		}
	}
	void EnemyB_Update(Chara& c_)
	{
		if (c_.state != State::Non) {
			if (c_.state == State::Hit)c_.state = State::Normal;
			switch (c_.mode) {
			case 0:
				c_.x -= 2;
				c_.moveCnt++;
				if (c_.moveCnt > 100) {
					c_.mode = 1;
					c_.moveCnt = 0;
				}
				break;
			case 1:
				c_.x += 1;
				c_.y -= 1;
				c_.moveCnt++;
				if (c_.moveCnt > 50)
				{
					c_.mode = 2;
					c_.moveCnt = 0;
				}
				break;
			case 2:
				c_.x -= 2;
				c_.moveCnt++;
				break;
			}
			if (c_.x + 32 < 0)
			{
				c_.state = State::Non;
			}
			c_.animCnt++;
			Enemy_HitCheckPlayers_Std(c_);

		}
	}
	void EnemyC_Update(Chara& c_)
	{
		if (c_.state != State::Non) {
			if (c_.state == State::Hit)c_.state = State::Normal;
			c_.x -= 2;
			if (c_.x + 32 < 0)
			{
				c_.state = State::Non;
			}
			c_.animCnt++;
			Enemy_HitCheckPlayers_Std(c_);

		}
	}
	void Enemy_HitCheckPlayers_Std(Chara& c_)
	{
		if (c_.state == State::Normal)
		{
			ML::Box2D me = c_.hitBase.OffsetCopy(c_.x, c_.y);
			if (State::Normal == player.state)
			{
				ML::Box2D you = player.hitBase.OffsetCopy(player.x, player.y);
				if (true == you.Hit(me)) {
					if (c_.life - player.damage <= 0)
					{
						c_.state = State::Non;
						Bomb_Appear(c_.x, c_.y);
						totalScore += c_.score;
					}
					else {
						c_.state = State::Hit;
					}
					player.state = State::Non;
					player.life = 0;
					Bomb_Appear(player.x, player.y);
				}
			}
		}
	}
	void Boss_Appear(Chara& c_,int x_,int y_)
	{
		if (c_.state == State::Non)
		{
			Boss_Initialize(c_);
			c_.state = State::Normal;
			c_.x = x_;
			c_.y = y_;
			c_.fx = x_;
			c_.fy = y_;
			bossActCD = 50;
		}
	}
	void Boss_Update(Chara& c_)
	{
		if (c_.life <= 0)
			isBossDestory = true;
		if (c_.state != State::Non) {
			if (c_.state == State::Hit)c_.state = State::Normal;
			if (timeCnt > 4000)c_.mode = 4;
			switch (c_.mode) {
			case 0:
				c_.x -= 2;
				c_.moveCnt++;
				bossActCD = 50;
				bossAct = 5;
				if (c_.moveCnt > 50) {
					c_.mode = 1;
					c_.moveCnt = 0;
					bossActCD = 0;
				}
				break;
			case 1:
				c_.y += 1;
				c_.moveCnt++;
				if (c_.moveCnt > 50)
				{
					c_.mode = 2;
					c_.moveCnt = 0;
				}
				break;
			case 2:
				c_.y -= 1;
				c_.moveCnt++;
				if (c_.moveCnt > 100)
				{
					c_.mode = 3;
					c_.moveCnt = 0;
				}
				break;
			case 3:
				c_.y += 1;
				c_.moveCnt++;
				if (c_.moveCnt > 100)
				{
					c_.mode = 2;
					c_.moveCnt = 0;
				}
				break;
			case 4:
				c_.x -= 2;
				c_.moveCnt++;
				break;
			}
			if (c_.x + 64 < 0)
			{
				c_.state = State::Non;
			}
			c_.animCnt++;
			Enemy_HitCheckPlayers_Std(c_);
			if (bossActCD <= 0) {
				bossAct++;
				bossAct = bossAct % 3;
				bossActCD = 200;
			}
			else
			{
				bossActCD--;
			}
			switch (bossAct)
			{
			case 0:
				BossActA_Update(bossShot[0], bossActCD);
				break;
			case 1:
				//BossActB_Update(c_, bossActCD);
				break;
			case 2:
				//BossActC_Update(c_, bossActCD);
				break;
			default:
				break;
			}
		}
	}
	void BossActA_Update(Chara& c_,int cd)
	{
		if (isBossDestory)
		{
			c_.state = State::Non;
			return;
		}
		if (cd >= 200)
		{
			BossShotA_Initialize(c_);
			c_.state = State::Normal;
			c_.hitBase = ML::Box2D(600, 0, 600, 1);
			c_.x = enemys[60].x-40;
			c_.y = enemys[60].y;
			c_.mode = 0;
			c_.animCnt = 0;
		}
		else if (cd > 150)
		{
			c_.x = enemys[60].x - 40;
			c_.y = enemys[60].y;
			c_.mode = 0;
			Shot_Update(c_, c_.x, c_.y);
		}
		else if (cd > 25)
		{
			c_.hitBase = ML::Box2D(-500, -5, 500, 10);
			c_.x = enemys[60].x - 40;
			c_.y = enemys[60].y;
			c_.mode = 1;
			Shot_Update(c_, c_.x, c_.y);
			EnemyShot_HitPlayer(c_);
		}
		else if (cd > 10)
		{
			c_.hitBase = ML::Box2D(600, 0, 600, 1);
			c_.x = enemys[60].x - 40;
			c_.y = enemys[60].y;
			c_.mode = 0;
			Shot_Update(c_, c_.x, c_.y);
		}
		else if (cd >= 0)
		{
			c_.state = State::Non;
		}
	}
	void BossActB_Update(Chara& c_,int cd)
	{
		
	}
	void BossActC_Update(Chara& c_,int cd)
	{
		
	}
	void Boss_Destruct(int x, int y)
	{
		bossDes.state = State::Normal;
		bossDes.x = x;
		bossDes.y = y;
		bossDes.animCnt++;
		if(bossDes.animCnt%20==0)se::Play("Explosion");
	}

	//敵の弾
	void EnemyShot_Update(Chara& c_, int type)
	{
		switch (type)
		{
		case 0:EnemyShotA_Update(c_); break;
		case 1:EnemyShotB_Update(c_); break;
		case 2:EnemyShotC_Update(c_); break;
		}
	}
	void EnemyShotA_Update(Chara& c_)
	{
		//プレイヤーの位置を狙う弾
		int e = c_.targetIndex;
		if (c_.state != State::Non)
		{
			
			if (enemyShots[e].state == State::Non && c_.moveCnt > 99) //敵Aは生まれた99フレイムと移動完了した99フレイムに弾を発射
			{
				EnemyShot_Initialize(enemyShots[e], 0);
				enemyShots[e].state = State::Normal;
				enemyShots[e].x = c_.x;
				enemyShots[e].y = c_.y;
				enemyShots[e].fx = (float)c_.x;
				enemyShots[e].fy = (float)c_.y;
				enemyShots[e].hitBase = ML::Box2D(-4, -4, 8, 8);
				enemyShots[e].animCnt = 0;
				int mx = player.x - c_.x;
				int my = player.y - c_.y;
				enemyShots[e].angle = atan2(my, mx);//方向を固定する弾
			}
		}
		if (enemyShots[e].state == State::Normal) //既に発射したら、移動
		{
			enemyShots[e].fx += enemyShots[e].speed * cos(enemyShots[e].angle);
			enemyShots[e].fy += enemyShots[e].speed * sin(enemyShots[e].angle);
			enemyShots[e].x = (int)enemyShots[e].fx;
			enemyShots[e].y = (int)enemyShots[e].fy;
			Shot_Update(enemyShots[e], enemyShots[e].x, enemyShots[e].y);
			if (enemyShots[e].state == State::Normal)
			{
				EnemyShot_HitPlayer(enemyShots[e]);
			}
		}
	}
	void EnemyShotB_Update(Chara& c_)
	{
		//横移動の弾
		int e = c_.targetIndex;
		if (c_.state != State::Non)
		{

			if (enemyShots[e].state == State::Non && c_.moveCnt > 99) //敵Aは生まれた99フレイムと移動完了した99フレイムに弾を発射
			{
				EnemyShot_Initialize(enemyShots[e], 1);
				enemyShots[e].x = c_.x;
				enemyShots[e].y = c_.y;
				enemyShots[e].state = State::Normal;
				enemyShots[e].hitBase = ML::Box2D(-6, -6, 12, 12);
				enemyShots[e].animCnt = 0;
			}
		}
		if (enemyShots[e].state == State::Normal) //既に発射したら、移動
		{
			enemyShots[e].x += -enemyShots[e].speed;
			Shot_Update(enemyShots[e], enemyShots[e].x, enemyShots[e].y);
			if (enemyShots[e].state == State::Normal)
			{
				EnemyShot_HitPlayer(enemyShots[e]);
			}
		}
	
	}
	void EnemyShotC_Update(Chara& c_)
	{
		//横移動の弾
		int e = c_.targetIndex;
		if (c_.state != State::Non)
		{

			if (enemyShots[e].state == State::Non) //生きている敵は1/300の確率で攻撃
			{
				int r = rand() % 300;
				if (r == 1) 
				{
					EnemyShot_Initialize(enemyShots[e], 2);
					enemyShots[e].x = c_.x;
					enemyShots[e].y = c_.y;
					enemyShots[e].state = State::Normal;
					enemyShots[e].hitBase = ML::Box2D(-6, -6, 12, 12);
					enemyShots[e].animCnt = 0;
				}
			}
		}
		if (enemyShots[e].state == State::Normal) //既に発射したら、移動
		{
			enemyShots[e].x += -enemyShots[e].speed;
			Shot_Update(enemyShots[e], enemyShots[e].x, enemyShots[e].y);
			if (enemyShots[e].state == State::Normal)
			{
				EnemyShot_HitPlayer(enemyShots[e]);
			}
		}
	}
	void EnemyShot_HitPlayer(Chara& c_)
	{
		ML::Box2D me = c_.hitBase.OffsetCopy(c_.x, c_.y);
		ML::Box2D you = player.hitBase.OffsetCopy(player.x, player.y);
		if (player.state == State::Normal)
		{
			if (Hit(me, you))
			{
				player.life -= c_.damage;//HP計算
				if (player.life <= 0)
				{
					player.state = State::Non;
					Bomb_Appear(player.x, player.y);
				}
				else player.state = State::Hit;
				c_.state = State::Non;
				c_.moveCnt = 0;
				c_.mode = 0;
			}
		}
	}
	//爆発エフェクトの更新
	void Bomb_Update(Chara& c_)
	{
		if (c_.state == State::Normal)
		{
			c_.animCnt++;
			if (c_.animCnt >= 40)
			{
				c_.animCnt = 0;
				c_.state = State::Non;
			}
		}
	}
	//爆発エフェクトを表示
	void Bomb_Appear(int x_, int y_)
	{
		for (int c = 0; c < 60; c++)
		{
			if (bombs[c].state == State::Non)
			{
				bombs[c].state = State::Normal;
				bombs[c].x = x_;
				bombs[c].y = y_;
				se::Play("Explosion");
				break;
			}
		}
	}
	//背景の移動
	void Back_Update(Chara& c_,int t)
	{
		//距離感を作るために背景移動速度を別々に
		int tem = 0;
		switch (t)
		{
		case 0:
			break;
		case 1:
			tem = 1;
			break;
		case 2:
			tem = 1;
			break;
		case 3:
			tem = 2;
			break;
		case 4:
			tem = 2;
			break;
		case 5:
			//臨場感を作るために星が光る
			c_.animCnt++;
			if (c_.animCnt == 100)
			{
				c_.animCnt = 0;
				c_.state = State::Hit;
			}
			else c_.state = State::Normal;
			tem = 3;
			break;
		case 6:
			c_.animCnt++;
			if (c_.animCnt == 70)
			{
				c_.animCnt = 0;
				c_.state = State::Hit;
			}
			else c_.state = State::Normal;
			tem = 3;
			break;
		}
		int wide = 480;
		if (tem == 2)wide = 520;
		if (c_.x <= -wide)c_.x = wide;
		c_.x -= tem;
	}
	//ゲーム管理
	TaskFlag GameManager()
	{
		savex = totalScore;
		TaskFlag rtv = TaskFlag::Game;
		if (player.state == State::Non && exitCountDown > 100)//プレイヤーが死んだら、少し待つ
		{
			exitCountDown = 100;
		}
		if (isBossDestory && exitCountDown > 100)
		{
			exitCountDown = 100;
		}

		exitCountDown--;
		int minute = 3;//3分後ゲーム終了
		if (timeCnt > 24 * 60 * minute || exitCountDown < 0)
		{
			rtv = TaskFlag::Ending;
		}
		
		return rtv;
	}





	//---------------------RENDER--------------------------------
	//Hitに関するコードは基本的に撃たれた効果を表示、背景は光る効果
	void Player_Draw(Chara& c_)
	{
		if (c_.state != State::Non)
		{
			ML::Color color(1.0f, 1, 1, 1);
			if (c_.state == State::Hit)color = ML::Color(1.0f, 255, 255, 255);
			ML::Box2D draw(-32, -12, playerw, playerh);
			draw.Offset(player.x, player.y);
			ML::Box2D src(0, 0, 64, 25);
			imgPlayer->Draw(draw, src,color);
		}
	}
	void PlayerShot_Draw(Chara& c_, ML::Box2D s_, ML::Box2D p_,int type)
	{
		switch (type)
		{
		case 0:PlayerShotA_Draw(c_, s_, p_);
			break;
		case 1:PlayerShotB_Draw(c_, s_, p_);
			break;
		}
	}
	void PlayerShotA_Draw(Chara& c_, ML::Box2D s_, ML::Box2D p_)
	{
		if (c_.state == State::Normal)
		{
			ML::Box2D draw = s_;
			ML::Box2D src = p_;
			int animTable[] = { 0,1,2,3,2,1 };
			src.x += animTable[(c_.animCnt / 5) % 6] * 32;
			draw.Offset(c_.x, c_.y);
			imgShot->Draw(draw, src);
		}
	}
	void PlayerShotB_Draw(Chara& c_, ML::Box2D s_, ML::Box2D p_)
	{
		if (c_.state == State::Normal)
		{
			ML::Box2D draw = s_;
			ML::Box2D src = p_;
			int animTable[] = { 0,1,2,3,2,1 };
			src.x += animTable[(c_.animCnt / 5) % 6] * 16;
			draw.Offset(c_.x, c_.y);
			imgShot->Draw(draw, src);
		}
	}

	
	void Enemy_Draw(Chara& c_)
	{
		if (c_.state != State::Non)
		{
			switch (c_.typeNum) {
			case 0:EnemyA_Draw(c_); break;
			case 1:EnemyB_Draw(c_); break;
			case 2:EnemyC_Draw(c_); break;
			}
		}
	}
	void EnemyA_Draw(Chara& c_)
	{
		ML::Color color(1.0f, 1, 1, 1);
		if(c_.state== State::Hit)color = ML::Color(1.0f, 255, 255, 255);
		ML::Box2D draw(-20, -20, 40, 40);
		int animTable[] = { 0,1,2,3,2,1 };
		draw.Offset(c_.x, c_.y);
		ML::Box2D src(animTable[(c_.animCnt / 5) % 6] * 40, 0, 40, 40);
		imgEnemy->Draw(draw, src,color);
	}
	void EnemyB_Draw(Chara& c_)
	{
		ML::Color color(1.0f, 1, 1, 1);
		if (c_.state == State::Hit)color = ML::Color(1.0f, 255, 255, 255);
		ML::Box2D draw(-16, -16, 32, 32);
		int animTable[] = { 0,1,2,3,2,1 };
		draw.Offset(c_.x, c_.y);
		ML::Box2D src(animTable[(c_.animCnt / 5) % 6] * 32, 0, 32, 32);
		imgEnemy2->Draw(draw, src, color);
	}
	void EnemyC_Draw(Chara& c_)
	{
		ML::Color color(1.0f, 1, 1, 1);
		if (c_.state == State::Hit)color = ML::Color(1.0f, 255, 255, 255);
		ML::Box2D draw(-20, -20, 40, 40);
		int animTable[] = { 0 };
		draw.Offset(c_.x, c_.y);
		ML::Box2D src(0, 0, 40, 40);
		imgEnemy3->Draw(draw, src, color);
	}
	void Boss_Draw(Chara& c_)
	{
		ML::Color color(1.0f, 1, 1, 1);
		if (c_.state == State::Hit)color = ML::Color(1.0f, 255, 255, 255);
		ML::Box2D draw(-64, -64, 128, 128);
		int animTable[] = { 0,1,2,3,4,5,6,5,4,3,2,1 };
		draw.Offset(c_.x, c_.y);
		ML::Box2D src(0,animTable[0, (c_.animCnt / 5) % 12] * 128, 128, 128);
		bossEngine->Draw(draw, src, color);
		bossBody->Draw(draw, src, color);
		
	}
	void BossShotA_Draw(Chara& c_)
	{
		if (c_.state == State::Non)
			return;
		ML::Box2D draw;
		switch (c_.mode)
		{
		case 0:
			draw = ML::Box2D(-600, -3, 600, 6); break;
		case 1:
			draw = ML::Box2D(-600, -15, 600, 30); break;
		}
		draw.Offset(c_.x, c_.y);
		int animTable[] = { 0,1,2,1};
		ML::Box2D src(0, animTable[0, (c_.animCnt / 5) % 4] * 30, 64, 30);
		
		bossLazer->Draw(draw, src);
	}
	void BossDestruct_Draw(Chara& c_)
	{
		if (c_.state == State::Normal)
		{
			ML::Box2D draw(-64, -64, 128, 128);
			int animTable[] = { 17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0 };
			draw.Offset(c_.x, c_.y);
			ML::Box2D src(0, animTable[0, (c_.animCnt / 6) % 18] * 128, 128, 128);
			
			bossDestruct->Draw(draw, src);
			
		}
		
	}
	void EnemyShot_Draw(Chara& c_,int type)
	{
		if (c_.state == State::Normal)
		{
			switch (type)
			{
			case 0:EnemyShotA_Draw(c_); break;
			case 1:EnemyShotB_Draw(c_); break;
			case 2:EnemyShotC_Draw(c_); break;
			}
		}
	}
	void EnemyShotA_Draw(Chara& c_)
	{
		ML::Box2D draw(-8, -8, 16, 16);
		ML::Box2D src(0, 192, 16, 16);
		int animTable[] = { 0,1,2,1 };
		src.x += animTable[(c_.animCnt / 5) % 4] * 16;
		draw.Offset(c_.x,c_.y);
		imgShot->Draw(draw, src);

	}
	void EnemyShotB_Draw(Chara& c_)
	{
		ML::Box2D draw(-8, -8, 16, 16);
		ML::Box2D src(0, 126, 32, 32);
		int animTable[] = { 0,1,2,1 };
		src.x += animTable[(c_.animCnt / 5) % 4] * 32;
		draw.Offset(c_.x, c_.y);
		imgShot->Draw(draw, src);
	}
	void EnemyShotC_Draw(Chara& c_)
	{
		ML::Box2D draw(-8, -8, 16, 16);
		ML::Box2D src(0, 224, 32, 32);
		int animTable[] = { 0,3,2,1 };
		src.x = animTable[(c_.animCnt / 5) % 4] * 32;
		draw.Offset(c_.x, c_.y);
		imgShot->Draw(draw, src);
	}
	void Bomb_Draw(Chara& c_)
	{
		if (c_.state == State::Normal)
		{
			ML::Box2D draw(-16, -16, 32, 32);
			int animTable[] = { 0,1,2,3,4,5,6,7 };
			draw.Offset(c_.x, c_.y);
			ML::Box2D src(animTable[(c_.animCnt / 5) % 8] * 32, 0, 32, 32);
			ML::Color color(0.95f, 1, 1, 1);
			imgBomb->Draw(draw, src, color);
		}
	}
	void Back_Draw(Chara& c_,int t_)
	{
		ML::Box2D draw =ML::Box2D(0, 0, 480, 270);
		ML::Box2D src = ML::Box2D(0, 0, 480, 270);
		ML::Color color = ML::Color(1.0f, 1, 1, 1);
		switch (t_)
		{
		case 0:
			imgBackground->Draw(draw, src);
			break;
		case 1:
			draw.Offset(c_.x, c_.y);
			imgBackground1->Draw(draw, src);
			break;
		case 2:
			draw.Offset(c_.x, c_.y);
			imgBackground1->Draw(draw, src);
			break;
		case 3:
			draw = ML::Box2D(0, 100, 150, 148);
			src= ML::Box2D(0, 0, 150, 148);
			draw.Offset(c_.x, c_.y);
			imgBackground2->Draw(draw, src);
			break;
		case 4:
			draw = ML::Box2D(0, 100, 150, 148);
			src = ML::Box2D(0, 0, 150, 148);
			draw.Offset(c_.x, c_.y);
			imgBackground2->Draw(draw, src);
			break;
		case 5:
			if(c_.state==State::Hit)color=ML::Color(1.0f, 255, 255, 255);
			draw.Offset(c_.x, c_.y);
			imgBackground3->Draw(draw, src,color);
			break;
		case 6:
			draw.Offset(c_.x, c_.y);
			imgBackground3->Draw(draw, src, color);
			if (c_.state == State::Hit)color = ML::Color(1.0f, 255, 255, 255);
			
			break;
		}
	}
	void Score_Draw()
	{
		ML::Box2D src = ML::Box2D(32, 36, 104, 84);
		ML::Box2D draw = ML::Box2D(360, 0,180, 64);
		fontBack->Draw(draw, src);
		std::string st= to_string(totalScore);
		st.insert(st.begin(), 5 - st.length(), '0');//5桁不足なら、0を挿入
		string scoreNow = st;
		ML::Box2D textBox = ML::Box2D(360, 0, 120, 32);
		fontA->Draw(textBox, scoreNow, ML::Color(1.0f, 1.0f, 1.0f, 1.0f));
		
	}
	void Life_Draw()
	{
		int lx = (4 - player.life)*48;
		ML::Box2D draw(0, 0, 96, 32);
		ML::Box2D src(lx, 16, 48, 16);
		imgLife->Draw(draw, src);
	}
	
}
	