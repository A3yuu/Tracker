# A3Tracker

# これは何？
ポチって買える9軸センサー5個でフルトラするためのSteamVRドライバです。

どう動くかって？動画を見やがれです。
https://youtu.be/IdvmWnNRoRY

※あんまり精度よくない。やっぱ9軸だけに頼ると辛いね･･･

# 使い方

下の回路(1万円弱)を作って
ビルドしてバイナリ実行ください

# 回路作成方法
買って指すだけなのでハンダゴテはいらない
![回路写真のコピー](https://user-images.githubusercontent.com/21051958/89866230-28b4f700-dbea-11ea-96a0-29cf40be8483.jpg)

9DOFSensor × 5
https://www.seeedstudio.com/grove-imu-9dof-icm20600-ak0991-p-3157.html

M5 Atom Lite × 1
https://docs.m5stack.com/#/en/core/atom_lite

I2C Switching Hub
https://m5stack.com/collections/m5-unit/products/pahub-unit

1m Cable × 2

and some bands and battery
足につける用のマジックテープとかリストバンドとか
バッテリーも100均とかで買ってくる

#ビルド方法

■Tracker
マイコン用のプロジェクト
・ESP32環境
下記参考に導入
https://docs.m5stack.com/#/en/arduino/arduino_development
・Sensorライブラリ
公式のだと当時ESP32で使えなかったので修正&
いくつか気に入らないところ改造した下記を導入
https://github.com/A3yuu/Seeed_ICM20600_AK09918

ビルドしたら回路に書き込み

■Driver
OpenVR用のドライバ、Trackerが3つありますってSteamVRに言うやつ
VisualStudioでビルドできるはず

■HMDPose
UnityにHMDのポーズを教えるためのdll
Unityの機能で持ってくるとドライバ側と座標が違う･･･
VisualStudioでビルドできるはず

■TrackerServer2018
回路とBT接続して座標計算とか磁力キャリブレーションとかするやつ
HMDPoseをビルドしてできた「HMDPose.dll」と
OpenVRのdll「openvr_api.dll」を下記にコピー
TrackerServer2018\Assets\Plugins\x86_64
Unity2018でビルドできるはず

#使い方
・ドライバインストール
「Driver\install.bat」を実行
・サーバー起動
TrackerServer2018をビルドしてできた「TrackerServer2018.exe」を起動
・サーバー初回設定
起動後回路が接続されてるCOM番号設定
体の各種長さ設定
サーバー再起動
キャリブレーションを実行
暴れまわる(Sensorとコードや磁石が近づかないように)
キャリブレーション終了
・使用中
ポーズが崩れてきたら、真っすぐ立って、M5スタックのボタンを押す。
なんかBTのドライバが弱いのか再接続がうまく行かないので、切れたら
サーバー終了
M5のリセットボタン押す
サーバー起動