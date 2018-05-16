#include "DxLib.h"
#include <string>
#include "main.h"
#include "player.h"
#include "enemy.h"
#include "gameStateStage.h"
#include "bullet.h"
#include "effect.h"
#include "stage.h"
#include "drawString.h"
using namespace std;

void BulletSelect();
void BulletGage();
void LifeGage();
void Tutorial();

void GameStateStage(int stageNum, int playerType)
{
	static bool initFlag = false;
	static int backY = 0;
	static Graphic backGround(stage[stageNum].backImageFilePath);
	static int frame = 0;
	static vector<unsigned short> enemySetFrame;

	//初期化です
	if (initFlag == false)
	{
		int speed[3] = { 10, 8, 12 };
		int life[3] = { 125, 100, 75 };
		char tempString[256];

		player.Set(SCREEN_X / 2, SCREEN_Y - 100);

		player.type = playerType;
		player.speed = speed[playerType];
		player.life = life[playerType];
		player.lifeMax = life[playerType];

		LoadBulletData();
		LoadEnemyData();

		for (int i = 0; i < BULLET_TYPE_MAX; i++)
		{
			player.bulletAmmo[i] = bulletData[i].ammoMax;
			DrawLoad();
		}

		for (int i = 0; i < 256; i++)
		{
			char tempString[256] = { 0 };
			LoadCSV(tempString, "data/parameter/stage2.csv", i + 1, 1, 4, 256);
			enemySetFrame.push_back(atoi(tempString));
		}

		initFlag = true;
	}

	//背景を描画します
	DrawExtendGraph(0, backY % SCREEN_Y - SCREEN_Y, SCREEN_X, backY % SCREEN_Y, backGround.handle(), true);
	DrawExtendGraph(0, backY % SCREEN_Y, SCREEN_X, backY % SCREEN_Y + SCREEN_Y, backGround.handle(), true);

	if (stageNum == 0)
	{
		Tutorial();
	}
	else
	{
		//Shiftが押されていない場合は
		//通常の処理をします
		if (key.GetKey(KEY_INPUT_LSHIFT) == false &&
			key.GetKey(KEY_INPUT_RSHIFT) == false)
		{
			backY += stage[stageNum].backGroundScrollSpeed;

			//エフェクトを更新、描画しています
			//iは警告が出ないよう、unsignedを使って
			//エフェクトを消したら範囲外アクセスが起きないよう
			//continueしています
			for (unsigned int i = 0; i < effect.size(); i++)
			{
				effect[i].Move();
				if (effect[i].Delete(i))continue;
			}

			//1/10の確率で敵を出しています
			if (frame < stage[stageNum].bossSetFrame)
			{
				if (GetRand(9) == 0){ SetEnemy((EnemyType)GetRand(ENEMY_TYPE_MAX - 1), GetRand(SCREEN_X), -100); }
			}

			//ボスセットフレームになったら
			//ボスをセットします
			if (frame == stage[stageNum].bossSetFrame)
			{
				SetEnemyBoss(stage[stageNum].bossType);
			}

			//敵を更新、描画しています
			//iは警告が出ないよう、unsignedを使って
			//敵を消したら範囲外アクセスが起きないよう
			//continueしています
			for (unsigned int i = 0; i < enemy.size(); i++)
			{
				DrawFormatString(0, i * 16, GetColor(255, 255, 255), "%d,%d,%d", i, enemy[i].pos.x(), enemy[i].pos.y());
				enemy[i].Move(i);
				enemy[i].CheckHit();
				if (enemy[i].Delete(i) == true)
				{
					if (frame > stage[stageNum].bossSetFrame &&
						i == 0)
					{
						gameState.Change(GAME_STATE_CLEAR);
					}
					continue;
				}
			}

			//弾を更新、描画しています
			//iは警告が出ないよう、unsignedを使って
			//弾を消したら範囲外アクセスが起きないよう
			//continueしています
			for (unsigned int i = 0; i < bullet.size(); i++)
			{
				bullet[i].Move();
				bullet[i].CheckHit();
				if (bullet[i].Delete(i))continue;
			}

			//プレイヤーを更新して描画しています
			player.Move();
			player.Shoot();

			//フレームを進めときます
			frame++;
		}

		//エフェクトを描画しています
		for (unsigned int i = 0; i < effect.size(); i++)effect[i].Draw();
		//敵を描画しています
		for (unsigned int i = 0; i < enemy.size(); i++)enemy[i].Draw();
		//弾を描画しています
		for (unsigned int i = 0; i < bullet.size(); i++)bullet[i].Draw();
		
		//プレイヤーの処理
		//プレイヤーが死んだらゲームオーバー画面に遷移する
		if (player.life <= 0)
		{
			gameState.Change(GameStateType::GAME_STATE_GAME_OVER);
		}
		//プレイヤーを描画しています
		player.Draw();

		//Shiftを押している間は武器セレクトを表示します
		if (key.GetKey(KEY_INPUT_LSHIFT) ||
			key.GetKey(KEY_INPUT_RSHIFT))
		{
			BulletSelect();
		}
		//Shiftが押されていない場合は
		//通常のGUIを表示します
		else
		{
			LifeGage();
			BulletGage();
		}
	}
}

void BulletSelect()
{
	static Graphic bulletSelect("data/img/gui/bulletSelect.png");
	static Graphic bulletSelectCursor("data/img/gui/bulletSelectCursor.png");
	static Graphic bulletIcon[8] = {
		"data/img/gui/bulletIcon/shotgun.png",
		"data/img/gui/bulletIcon/rifle.png",
		"data/img/gui/bulletIcon/gatoring.png",
		"data/img/gui/bulletIcon/bazzoca.png",
		"data/img/gui/bulletIcon/sarvel.png",
		"data/img/gui/bulletIcon/baria.png",
		"data/img/gui/bulletIcon/micile.png",
		"data/img/gui/bulletIcon/cyclon.png",
	};
	static int selectCursorX = SCREEN_X / 4;
	static int selectCursorY = SCREEN_Y / 2;
	int inputX = 0;
	int inputY = 0;

	if (key.GetKey(KEY_INPUT_UP))inputY = -1;
	if (key.GetKey(KEY_INPUT_DOWN))inputY = 1;
	if (key.GetKey(KEY_INPUT_LEFT))inputX = -1;
	if (key.GetKey(KEY_INPUT_RIGHT))inputX = 1;

	if (inputX == 0 && inputY == -1)player.holdWeapon = BULLET_TYPE_SHOT;
	else if (inputX == 1 && inputY == -1)player.holdWeapon = BULLET_TYPE_LASER;
	else if (inputX == 1 && inputY == 0)player.holdWeapon = BULLET_TYPE_GATLING;
	else if (inputX == 1 && inputY == 1)player.holdWeapon = BULLET_TYPE_BAZOOKA;
	else if (inputX == 0 && inputY == 1)player.holdWeapon = BULLET_TYPE_SABER;
	else if (inputX == -1 && inputY == 1)player.holdWeapon = BULLET_TYPE_BARRIER;
	else if (inputX == -1 && inputY == 0)player.holdWeapon = BULLET_TYPE_MISSILE;
	else if (inputX == -1 && inputY == -1)player.holdWeapon = BULLET_TYPE_TYPHOON;

	//武器セレクトの背景画像を描画しています
	DrawRotaGraph(SCREEN_X / 4, SCREEN_Y / 2, 1.5, 0, bulletSelect.handle(), true);

	//武器のアイコンを描画しています
	DrawRotaGraph(SCREEN_X / 4, SCREEN_Y / 2 - 240, 1, GetRadian(45), bulletIcon[0].handle(), true);
	DrawRotaGraph(SCREEN_X / 4 + 170, SCREEN_Y / 2 - 170, 1, 0, bulletIcon[1].handle(), true);
	DrawRotaGraph(SCREEN_X / 4 + 240, SCREEN_Y / 2, 1, GetRadian(45), bulletIcon[2].handle(), true);
	DrawRotaGraph(SCREEN_X / 4 + 170, SCREEN_Y / 2 + 170, 1, 0, bulletIcon[3].handle(), true);
	DrawRotaGraph(SCREEN_X / 4, SCREEN_Y / 2 + 240, 1, GetRadian(45), bulletIcon[4].handle(), true);
	DrawRotaGraph(SCREEN_X / 4 - 170, SCREEN_Y / 2 + 170, 1, 0, bulletIcon[5].handle(), true);
	DrawRotaGraph(SCREEN_X / 4 - 240, SCREEN_Y / 2, 1, GetRadian(45), bulletIcon[6].handle(), true);
	DrawRotaGraph(SCREEN_X / 4 - 170, SCREEN_Y / 2 - 170, 1, 0, bulletIcon[7].handle(), true);

	//武器セレクトのカーソルを描画しています
	//DrawRotaGraph(SCREEN_X / 4, SCREEN_Y / 2, 1.5, 0, bulletSelectCursor.handle(), true);

	int l = player.bulletLevel[player.holdWeapon];	//レベル
	string tempName;
	if (0 <= l && 1000 > l) tempName = "おとなしい";
	if (1000 <= l && 2000 > l) tempName = "荒ぶる";
	if (2000 <= l && 3000 > l) tempName = "激高した";
	if (3000 <= l && 4000 > l) tempName = "凶暴な";
	if (4000 <= l) tempName = "鬼の如き";
	tempName += bulletData[player.holdWeapon].name.c_str();
	CenterDrawStringToHandle(SCREEN_X / 4, SCREEN_Y / 2 - 150, 0.5, 0.5, tempName.c_str(), GetColor(127, 255, 255), fontHandle[FS_32], GetColor(0, 63, 127));
	DrawLineStringToHandle(SCREEN_X / 4 - 200, SCREEN_Y / 2 - 100, bulletData[player.holdWeapon].caption.c_str(), GetColor(127, 255, 255), fontHandle[FS_24], GetColor(0, 63, 127));

	DrawCircle(selectCursorX + inputX * 100, selectCursorY + inputY * 100, 10, GetColor(255, 255, 255), true);
}

void BulletGage()
{
	static Graphic bulletGageBackGround("data/img/gui/bulletGageBackGround.png");
	static Graphic bulletGage("data/img/gui/bulletGage.png");
	static Graphic bulletGageMax("data/img/gui/bulletGageMax.png");
	static Graphic bulletWaitGage("data/img/gui/bulletWaitGage.png");
	static Graphic thunder("data/img/effect/thunder.png");

	if (player.pos.x() > -10 &&
		player.pos.x() < 430 + 10 &&
		player.pos.y() > SCREEN_Y - 230 &&
		player.pos.y() < SCREEN_Y + 10)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 63);
	}

	//武器ゲージの背景を描画します
	DrawRotaGraph(192, SCREEN_Y, 1.5, 0, bulletGageBackGround.handle(), true);

	//武器の発射待ち時間を円グラフのような形で描画します
	DrawCircleGauge(50, SCREEN_Y - 96, (double)player.bulletWait[player.holdWeapon] / (bulletData[player.holdWeapon].resetWait / (double)(player.bulletLevel[player.holdWeapon] / 1000 + 1)) * 100.0, bulletWaitGage.handle());

	if (player.bulletLevel[player.holdWeapon] < 4000)
	{
		DrawRotaGraph(-165 + 357 * (player.bulletLevel[player.holdWeapon] % 1000 / 1000.0), SCREEN_Y, 1.5, 0, bulletGage.handle(), true);
	}
	else
	{
		DrawRotaGraph(192, SCREEN_Y, 1.5, 0, bulletGageMax.handle(), true);
		DrawRotaGraph(GetRand(343), SCREEN_Y - GetRand(100), 1 + GetRand(10) / 10.0, GetRadian(GetRand(360)), thunder.handle(), true);
		DrawRotaGraph(GetRand(343), SCREEN_Y - GetRand(100), 1 + GetRand(10) / 10.0, GetRadian(GetRand(360)), thunder.handle(), true);
	}

	int l = player.bulletLevel[player.holdWeapon];	//レベル
	string tempName;
	if (0 <= l && 1000 > l) tempName = "おとなしい";
	if (1000 <= l && 2000 > l) tempName = "荒ぶる";
	if (2000 <= l && 3000 > l) tempName = "激高した";
	if (3000 <= l && 4000 > l) tempName = "凶暴な";
	if (4000 <= l) tempName = "鬼の如き";
	tempName += bulletData[player.holdWeapon].name.c_str();

	DrawFormatStringToHandle(150, SCREEN_Y - 90, GetColor(127, 255, 255), fontHandle[FS_48], "%d", player.bulletAmmo[player.holdWeapon]);
	DrawFormatStringToHandle(280, SCREEN_Y - 75, GetColor(127, 255, 255), fontHandle[FS_24], "/%d", bulletData[player.holdWeapon].ammoMax);

	DrawStringToHandle(10, SCREEN_Y - 30, tempName.c_str(), GetColor(127, 255, 255), fontHandle[FS_24], GetColor(0, 63, 127));

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void LifeGage()
{
	static Graphic lifeGageBackGround("data/img/gui/lifeGageBackGround.png");
	static Graphic lifeGage("data/img/gui/lifeGage.png");

	if (player.pos.x() > SCREEN_X - 150 &&
		player.pos.x() < SCREEN_X + 10 &&
		player.pos.y() > SCREEN_Y - 230 &&
		player.pos.y() < SCREEN_Y + 10)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 63);
	}

	//武器ゲージの背景を描画します
	DrawRotaGraph(SCREEN_X - 145, SCREEN_Y, 1.5, 0, lifeGageBackGround.handle(), true);

	float playerLifeMax[3] = { 125, 100, 75 };

	DrawRotaGraph(SCREEN_X + 205 - 350 * (player.life / playerLifeMax[player.type]), SCREEN_Y, 1.5, 0, lifeGage.handle(), true);

	DrawFormatStringToHandle(SCREEN_X - 230, SCREEN_Y - 60, GetColor(127, 255, 255), fontHandle[FS_48], "%d", player.life);
	DrawFormatStringToHandle(SCREEN_X - 100, SCREEN_Y - 45, GetColor(127, 255, 255), fontHandle[FS_24], "/%d", player.lifeMax);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void Tutorial()
{
	static int tutorialProgress = 1;//チュートリアルの進行度
	static bool drawStringEnd = false;	//文章がすべて表示し終わったらtrueになる
	static bool stringInit = false;
	static char tutorialString[27][256];
	static int tutorialStringSpeed[28];
	static Graphic messageWindow("data/img/gui/messageWindow.png");
	static Graphic kuroto("data/img/char/kuroto.png");

	//Shiftが押されていない場合は
	//通常の処理をします
	if ((key.GetKey(KEY_INPUT_LSHIFT) == false &&
		key.GetKey(KEY_INPUT_RSHIFT) == false &&
		tutorialProgress == 13) ||
		tutorialProgress != 13)
	{
		//エフェクトを更新、描画しています
		//iは警告が出ないよう、unsignedを使って
		//エフェクトを消したら範囲外アクセスが起きないよう
		//continueしています
		for (unsigned int i = 0; i < effect.size(); i++)
		{
			effect[i].Move();
			if (effect[i].Delete(i))continue;
			effect[i].Draw();
		}

		//敵を更新、描画しています
		//iは警告が出ないよう、unsignedを使って
		//敵を消したら範囲外アクセスが起きないよう
		//continueしています
		for (unsigned int i = 0; i < enemy.size(); i++)
		{
			if (tutorialProgress == 15 || tutorialProgress == 14 || tutorialProgress == 22)
			{
				enemy[i].Move(i);
				enemy[i].CheckHit();
			}
			if (enemy[i].Delete(i))continue;
			enemy[i].Draw();
		}

		//弾を更新、描画しています
		//iは警告が出ないよう、unsignedを使って
		//弾を消したら範囲外アクセスが起きないよう
		//continueしています
		for (unsigned int i = 0; i < bullet.size(); i++)
		{
			bullet[i].Move();
			bullet[i].CheckHit();
			if (bullet[i].Delete(i))continue;
			bullet[i].Draw();
		}

		//プレイヤーを移動する
		if (tutorialProgress == 9 || tutorialProgress == 11 || tutorialProgress == 13 || tutorialProgress == 15 || tutorialProgress == 22){ player.Move(); }
		if (tutorialProgress == 11 || tutorialProgress == 13 || tutorialProgress == 22){ player.Shoot(); }
		if (tutorialProgress == 15 || tutorialProgress == 22)
		{
			//player.Eat();
		}
		//プレイヤーを表示する
		player.Draw();

		//メッセージウィンドウを描画する
		if (tutorialProgress != 22)DrawRotaGraph(SCREEN_X / 2, SCREEN_Y / 2, 1.5, 0, messageWindow.handle(), true);

		//クロトを描画する
		if (tutorialProgress != 22)DrawRotaGraph(SCREEN_X / 2 - 243, SCREEN_Y / 2, 1.2, 0, kuroto.handle(), true);

		if (stringInit == false)
		{
			for (int i = 1; i < 27; i++)
			{
				char tempString[256] = { 0 };
				LoadCSV(tempString, "data/parameter/tutorial.csv", i, 0, 22, 3);
				sprintf(tutorialString[i], "%s", tempString);
				LoadCSV(tempString, "data/parameter/tutorial.csv", i, 1, 22, 3);
				sprintf(tutorialString[i], "%s\n%s", tutorialString[i], tempString);
				LoadCSV(tempString, "data/parameter/tutorial.csv", i, 2, 22, 3);
				tutorialStringSpeed[i] = atoi(tempString);
				DrawLoad();
			}
			for (int i = 0; i < ENEMY_TYPE_MAX; i++)
			{
				//player.stageKillEnemyNum[i] = 0;
			}
			stringInit = true;
		}

		if (key.GetKeyDown(KEY_INPUT_Z) && drawStringEnd == true && tutorialProgress != 9 && tutorialProgress != 11 && tutorialProgress != 13 && tutorialProgress != 15 && tutorialProgress != 19 && tutorialProgress != 22)
		{
			tutorialProgress++;
			DrawSlowStringToHandle(0, 0, "", 0, 0, fontHandle[FS_32], 0, true);
		}

		if (tutorialProgress == 9 || tutorialProgress == 11 || tutorialProgress == 13 || tutorialProgress == 15)
		{
			static int nextTutorialFrame = 500;
			char tempString[256] = { 0 };
			float nextTutorialFrameLength = tutorialProgress == 13 ? 1000 : 500;
			float nextTutorialFrameRate = nextTutorialFrame / nextTutorialFrameLength;
			sprintf(tempString, "%d", nextTutorialFrame);
			CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y / 2 + 70, 0.5, 0.5, tempString, GetColor(127, 255, 255), fontHandle[FS_24], GetColor(0, 63, 127));
			//残り時間バーを表示するために
			//残り時間バーを表示する
			DrawLine(SCREEN_X / 2 - 158, SCREEN_Y / 2 + 42, SCREEN_X / 2 - 158 + (450 * nextTutorialFrameRate), SCREEN_Y / 2 + 42, GetColor(63, 191, 255), 5);

			nextTutorialFrame--;
			if (nextTutorialFrame < 0)
			{
				if (tutorialProgress == 11)nextTutorialFrame = 1000;
				else nextTutorialFrame = 500;
				tutorialProgress++;
				DrawSlowStringToHandle(0, 0, "", 0, 0, fontHandle[FS_32], 0, true);
			}
		}

		if (tutorialProgress < 27)
		{
			drawStringEnd = DrawSlowStringToHandle(SCREEN_X / 2 - 150, SCREEN_Y / 2 - 40, tutorialString[tutorialProgress], tutorialStringSpeed[tutorialProgress], GetColor(127, 255, 255), fontHandle[FS_32], GetColor(0, 63, 127));
		}
		else
		{
			gameState.Change(GAME_STATE_CLEAR);
		}

		static bool enemySetFlag = false;
		if (tutorialProgress == 14 && enemySetFlag == false)
		{
			enemySetFlag = true;
			SetEnemy(ENEMY_TYPE_PATROL, SCREEN_X / 2, 0);
			SetEnemy(ENEMY_TYPE_PATROL, SCREEN_X / 4 * 3, 0);
			SetEnemy(ENEMY_TYPE_PATROL, SCREEN_X / 4, 0);
		}
		static bool bossSetFlag = false;
		if (tutorialProgress == 17)
		{
			if (bossSetFlag == false)
			{
				SetEnemyBoss(ENEMY_TYPE_BOSS_SPEED);
				bossSetFlag = true;
			}
			enemy[0].angle = GetRadian(90);
			if (enemy[0].pos.y() < 100)
			{
				enemy[0].pos.y(enemy[0].pos.y() + 1);
			}
		}
		if (bossSetFlag == true && tutorialProgress == 19)
		{
			static int bossMoveState = 0;
			DrawFormatString(0, 64, GetColor(255, 255, 255), "ボスステート=%d", bossMoveState);

			//ココから下はボスを出現時に動かしてます
			if (bossMoveState == 0)
			{
				enemy[0].angle = atan2((double)player.pos.y() - enemy[0].pos.y(), player.pos.x() - enemy[0].pos.x());
				enemy[0].pos.x(enemy[0].pos.x() + cos(enemy[0].angle) * 10);
				enemy[0].pos.y(enemy[0].pos.y() + sin(enemy[0].angle) * 10);
				if (CheckDistance(enemy[0].pos.x(), enemy[0].pos.y(), player.pos.x(), player.pos.y()) < 24)
				{
					bossMoveState = 1;
				}
			}
			if (bossMoveState == 1)
			{
				enemy[0].angle = GetRadian(-90);
				enemy[0].pos.x(enemy[0].pos.x() + cos(enemy[0].angle) * 10);
				enemy[0].pos.y(enemy[0].pos.y() + sin(enemy[0].angle) * 10);
				if (CheckDistance(enemy[0].pos.x(), enemy[0].pos.y(), player.pos.x(), player.pos.y()) > 100)
				{
					enemy[0].angle = GetRadian(-90);
					bossMoveState = 2;
				}
			}
			if (bossMoveState == 2)
			{
				enemy[0].angle += GetRadian(10);
				enemy[0].pos.x(player.pos.x() + cos(enemy[0].angle) * 100);
				enemy[0].pos.y(player.pos.y() + sin(enemy[0].angle) * 100);
				if ((int)(enemy[0].angle * 180 / DX_PI) > 270)
				{
					bossMoveState = 3;
				}
			}
			if (bossMoveState == 3)
			{
				enemy[0].angle = atan2((double)-100 - enemy[0].pos.y(), SCREEN_X / 2 - enemy[0].pos.x());
				enemy[0].pos.x(enemy[0].pos.x() + cos(enemy[0].angle) * 10);
				enemy[0].pos.y(enemy[0].pos.y() + sin(enemy[0].angle) * 10);
				if (CheckDistance(enemy[0].pos.x(), enemy[0].pos.y(), SCREEN_X / 2, -100) < 24)
				{
					bossMoveState = 4;
				}
			}
			if (bossMoveState == 4)
			{
				enemy[0].angle = atan2((double)100 - enemy[0].pos.y(), SCREEN_X / 2 - enemy[0].pos.x());
				enemy[0].pos.x(enemy[0].pos.x() + cos(enemy[0].angle) * 10);
				enemy[0].pos.y(enemy[0].pos.y() + sin(enemy[0].angle) * 10);
				if (CheckDistance(enemy[0].pos.x(), enemy[0].pos.y(), SCREEN_X / 2, 100) < 24)
				{
					enemy[0].pos.x(SCREEN_X / 2);
					enemy[0].pos.y(100);
					enemy[0].angle = GetRadian(90);
					bossMoveState = 5;
				}
			}
			if (bossMoveState == 5)
			{
				static int count = 0;
				count++;
				if (count > 30)
				{
					if (count % 4 == 0)enemy[0].pos.y(100);
					else enemy[0].pos.y(105);
					DrawOval(SCREEN_X / 2 + 230, 120, 200, 50, GetColor(0, 63, 127), true);
					CenterDrawStringToHandle(SCREEN_X / 2 + 230, 120, 0.5, 1.25, "ババッババババッ!!", GetColor(127, 255, 255), fontHandle[FS_24], GetColor(0, 63, 127));
					CenterDrawStringToHandle(SCREEN_X / 2 + 230, 120, 0.5, -0.25, "訳)武器とってやったぜ!!", GetColor(127, 255, 255), fontHandle[FS_24], GetColor(0, 63, 127));
				}
				if (count > 180)
				{
					enemy[0].pos.y(100);
					bossMoveState = 0;
					tutorialProgress++;
					DrawSlowStringToHandle(0, 0, "", 0, 0, fontHandle[FS_32], 0, true);
				}
			}
		}
		if (bossSetFlag == true && enemy.size() == 0 && tutorialProgress == 22)
		{
			tutorialProgress++;
			DrawSlowStringToHandle(0, 0, "", 0, 0, fontHandle[FS_32], 0, true);
		}
	}

	//チュートリアルプロセスを表示する
	DrawFormatString(0, 48, GetColor(255, 255, 255), "チュートリアル進行度=%d", tutorialProgress);

	//Shiftを押している間は武器セレクトを表示します
	if ((key.GetKey(KEY_INPUT_LSHIFT) ||
		key.GetKey(KEY_INPUT_RSHIFT)) &&
		tutorialProgress == 13)
	{
		BulletSelect();
	}
	//Shiftが押されていない場合は
	//通常のGUIを表示します
	else
	{
		LifeGage();
		BulletGage();
	}
}
