
## simple-cmap

`simple-cmap` 是一個使用紅黑樹實作的 C 語言鍵值對封裝模組，支援高效插入、查詢、刪除與遍歷操作，具備良好記憶體管理與錯誤防呆機制，適合系統工具、嵌入式應用或個人開發使用。

## 功能特色

* 提供通用 API：`map_insert`, `map_get`, `map_remove`, `map_foreach`, `map_keys` 等。
* 採用紅黑樹，操作效率為 O(log n)，適合大量資料。
* 支援自定比較與清除函式，使用者可自由決定 key/value 的管理方式。
* 所有資源皆有完整釋放邏輯，防止記憶體洩漏。
* 具備 NULL 檢查與錯誤回傳機制，可安全應對不合法輸入。

## 安裝與編譯

1. 安裝 GCC 或 Clang 編譯器。
2. 使用範例 Makefile 編譯：

   ```
   make
   ```
3. 可透過 Dr. Memory 或 Valgrind 執行記憶體錯誤檢查。

## 📦 專案結構

```
.
├── c-map.h            # 公開 API 宣告
├── c-map.c            # 主體邏輯實作
├── map_internal.h     # 紅黑樹內部結構與函式
├── map_xxx.c          # 插入、刪除、搜尋等模組化實作檔案
├── demo.c             # 單元測試與使用範例
└── README.md          # 本說明文件
```

## 📖 使用範例

```
#include "c-map.h"

intcompare(void* a, void* b){
    returnstrcmp((char*)a, (char*)b);
}

voidcleanup(void* key, void* val){
    free(key);
    free(val);
}

intmain(){
    map_t* map= map_create(compare, cleanup);
    map_insert(map, strdup("apple"), strdup("fruit"));
    printf("%s\n", (char*)map_get(map, "apple"));  // output: fruit
    map_free(map);
    return0;
}
```

## 🧪 測試方式

編譯並執行 `demo.c` 單元測試：

```
gcc -std=c99 -g demo.c c-map.c map_*.c -o demo
./demo
```

若使用 Dr. Memory（Windows）：

```
"C:\Program Files (x86)\Dr. Memory\bin\drmemory.exe"-- demo.exe
```

## 💡 設計理念

此模組設計以  **安全性** 、**靈活性** 與 **效率** 為主軸，透過紅黑樹確保操作平衡，並加入錯誤防呆與自定義函式介面，提升可應用性。
