# Nippo

シンプルな日報アプリ
設定したフォルダ下にcsvベースで年ごとの稼働時間を記録できます
アプリを開くと今日の稼働時間を設定できますが、それ以外の日付のものを変更するときはcsvを直接編集してください

# 使い方

最初にフォルダを設定します

（設定を変えたいときはスペースキーで再度フォルダ設定ダイアログが出ます）

ジョブを追加するときは、Addボタンを押します

ジョブの時間を記入するには、上下矢印を押すと0.5時間ずつ変えられます

時間はドラッグすると0.1時間刻みで変更できます。

ジョブ名をクリックすると今日のメモが記入できます。メモはcsv上で毎日別のセルになるので翌日はアプリ上では消えます

# Required Addons

https://github.com/paulvollmer/ofxCsv

https://github.com/tettou771/ofxFpsAutoReducer

https://github.com/tettou771/ofxComponent

https://github.com/tettou771/ofxComponentUI

# 

# Build

openFrameworks 0.11.2 + Mac OS
