
Z80Golf 環境


* make
	src ディレクトリで make をすると実行ファイル z80golf ができます。


* 実行

test ディレクトリの .z8b ファイルを食わせると実行されます。

	z80golf helloworld.z8b
	z80golf echo.z8b < echo.asm
	z80golf fizzbuzz.z8b


* z80golf のお約束

	- バイナリは０番地以降に転送される
	- HALT (76H) で停止させる
	- 8000H を呼び出すと標準出力にAレジスタの内容を１文字出力
	- 8003H を呼び出すと標準入力から文字入力、キャリーフラグが立ってたらEOF


* その他

fMSX の Z80 エミュレータを使ってる。 http://fms.komkon.org/fMSX/
ソースコード利用のライセンスはメールしてくれとのこと。

