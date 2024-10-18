2D Shooting Game Developed by C++

Demo Video Link: https://youtu.be/lYJO9mmRk0M

 

  

Game scene source code ゲームシーンのソースコード: Task_Game.cpp

Title scene source code タイトルシーンのソースコード: Task_Title.cpp

Controls Instructions scene source code チュートリアルシーンのソースコード: Task_NewGame.cpp

Ending scene source code エンディングシーンのソースコード: Task_Ending.cpp

Scene controls source code シーン管理のソースコード: MyGameMain.cpp

Game ゲーム本体: ./x64/Debug/GPG_2020.exe


ゲームプログラミングの期末課題では、自分が以前作成した課題を改造するという内容でした。改造前の課題は非常にシンプルな横スクロールシューティングゲームで、背景も簡単なものでした。敵は攻撃してこず、ボスもいなく、ゲームは自動で終了しない仕様でした。プレイヤーの攻撃手段は横方向のメインウェポンと斜め方向のサブウェポンのみで、対応するキーを押した瞬間にしか発射されませんでした。

今回の改造では、各敵キャラに異なる攻撃パターンを追加し、4層にわたる移動速度の異なる背景を導入して、奥行き感を出しました。また、ボスを追加し、プレイヤーの生存状態やボスの生存状態、ゲームの進行時間に基づいて自動的にゲームが終了するようにしました。スコアシステムを追加し、終了画面でスコアを一つずつ表示するようにしました。加えて、スタート画面とチュートリアル画面でのヒントを表示するようにし、弾のダメージシステムと敵の体力システムも導入しました。プレイヤーの攻撃が一撃で敵を倒せなかった場合、敵は一瞬点滅してダメージを受けたことが分かるようにしました。さらに、背景音や効果音も追加しました。プレイヤーのサブウェポンは追尾弾に改造され、対応するキーを押し続けると一定の間隔で自動的に発射されるようにしました。


For the final project in game programming, we were tasked with modifying a previous project we had worked on. My original project was a very simple side-scrolling shooter game, with only basic backgrounds. The enemies did not attack, there was no boss, and the game wouldn’t end automatically. The player could only attack using a main weapon that fired horizontally and a sub-weapon that fired diagonally, and they would only shoot when the corresponding keys were pressed.

For the modification, I added different attack patterns to each enemy and implemented a four-layer background with varying movement speeds to create a sense of depth. I also introduced a boss, and the game now automatically ends based on the player's survival status, the boss's survival status, and the elapsed game time. A scoring system was added, with scores displayed one by one on the end screen. I also added hints on the start and tutorial screens, implemented a bullet damage system and a health system for the enemies. If the player's attack doesn't defeat the enemy in one shot, the enemy flashes briefly to indicate they’ve taken damage. In addition, I added background music and sound effects. The player's sub-weapon was upgraded to homing bullets, and now, by holding down the corresponding key, the bullets fire at regular intervals automatically.
