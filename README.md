# objc_utils

## yas_objc_macros

* ARC設定の違いを吸収するマクロ集
* MacとiOSのクラス名の違いを吸収するマクロ集

## YASUnownedObject

オブジェクトのオーナーシップを持たずに保持するクラス。  
ARCなら`weak`、Non-ARCなら`assign`で保持する。
