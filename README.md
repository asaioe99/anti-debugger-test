# anti-debugger-test
使用の際は適切にパックしてください。そのままではwindows defenderに検知されます。
https://github.com/upx/upx/releases/tag/v3.96 により、

upx -9 test.exe

でパックした場合、検知されませんでした。

参考文献
・「アナライジング・マルウェア ―フリーツールを使った感染事案対処 (Art Of Reversing)」
https://www.amazon.co.jp/%E3%82%A2%E3%83%8A%E3%83%A9%E3%82%A4%E3%82%B8%E3%83%B3%E3%82%B0%E3%83%BB%E3%83%9E%E3%83%AB%E3%82%A6%E3%82%A7%E3%82%A2-%E2%80%95%E3%83%95%E3%83%AA%E3%83%BC%E3%83%84%E3%83%BC%E3%83%AB%E3%82%92%E4%BD%BF%E3%81%A3%E3%81%9F%E6%84%9F%E6%9F%93%E4%BA%8B%E6%A1%88%E5%AF%BE%E5%87%A6-Art-Reversing-%E6%96%B0%E4%BA%95/dp/4873114551/ref=sr_1_1?__mk_ja_JP=%E3%82%AB%E3%82%BF%E3%82%AB%E3%83%8A&dchild=1&keywords=%E3%82%A2%E3%83%8A%E3%83%A9%E3%82%A4%E3%82%B8%E3%83%B3%E3%82%B0%E3%83%9E%E3%83%AB%E3%82%A6%E3%82%A7%E3%82%A2&qid=1626739052&sr=8-1
->検体の大半はここで紹介される手法を利用している。

・「サイバーセキュリティプログラミング ―Pythonで学ぶハッカーの思考」
https://www.amazon.co.jp/s?k=%E3%82%B5%E3%82%A4%E3%83%90%E3%83%BC%E3%82%BB%E3%82%AD%E3%83%A5%E3%83%AA%E3%83%86%E3%82%A3%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0&__mk_ja_JP=%E3%82%AB%E3%82%BF%E3%82%AB%E3%83%8A&linkCode=qs&sourceid=Mozilla-search&tag=mozillajapan-fx-22
->act10及び11で参考にした。特にAPIの先頭アドレス+2Byteから実行するスライディングコールの原理については、他に解説を見つけることはできなかったため有用である。
