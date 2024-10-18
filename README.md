2D Shooting Game Developed by C++

Demo Video Link: https://youtu.be/lYJO9mmRk0M

 

  

Game scene source code ゲームシーンのソースコード: Task_Game.cpp

Title scene source code タイトルシーンのソースコード: Task_Title.cpp

Controls Instructions scene source code チュートリアルシーンのソースコード: Task_NewGame.cpp

Ending scene source code エンディングシーンのソースコード: Task_Ending.cpp

Scene controls source code シーン管理のソースコード: MyGameMain.cpp

Game ゲーム本体: ./x64/Debug/GPG_2020.exe


ゲームプログラミングの期末課題は、以前自分が作成した課題を改造するというものでした。改造前の課題は非常にシンプルな横スクロールシューティングゲームで、背景も簡単なもの、敵は攻撃せず、ボスも登場せずに自動で終了する内容でした。プレイヤーの攻撃手段は横方向のメイン武器と斜め方向のサブ武器だけで、対応するボタンを押した瞬間にのみ発射される仕様でした。

今回の改造では、すべての敵に異なる攻撃パターンを追加し、4層にわたる異なる移動速度の背景を追加することで、奥行きを表現しました。また、ボスを追加し、ゲームはプレイヤーの生存状態、ボスの生存状態、プレイ時間に応じて自動的に終了するようにしました。スコアシステムを導入し、終了画面ではスコアを順番に表示させるようにしました。さらに、スタート画面とチュートリアル画面にヒントを追加しました。

弾のダメージシステムと敵の体力システムも追加し、プレイヤーの攻撃が一撃で敵を倒せなかった場合、敵は一瞬だけ点滅して被弾を表現するようにしました。加えて、背景音や効果音も導入しました。さらに、プレイヤーのサブ武器を追尾弾に変更し、対応するボタンを押し続けるだけで弾が一定の間隔で自動的に発射されるようにしました。

The final assignment for the game programming course was to modify a previous project I had created. The original project was a very simple side-scrolling shooter game, with a basic background, enemies that didn’t attack, no boss, and the game would end automatically. The player's attack options were limited to a horizontally-firing main weapon and a diagonally-firing sub-weapon, and the weapons would only fire at the moment the corresponding button was pressed.

In the modified version, I added different attack patterns to each enemy, and implemented a four-layer background with different scrolling speeds to create a sense of depth. I also added a boss, and the game now ends automatically depending on the player’s survival status, the boss’s survival status, and the playtime. A scoring system was added, and the scores are displayed one by one on the game-over screen. I also included hints in the start screen and tutorial screen.

Additionally, I introduced a damage system for the bullets and a health system for the enemies. If the player's attack doesn’t defeat the enemy in one hit, the enemy will briefly flash to indicate it's been hit. I also added background music and sound effects. Lastly, I modified the player’s sub-weapon to be a homing missile, so now holding down the corresponding button fires the bullets at fixed intervals automatically.
