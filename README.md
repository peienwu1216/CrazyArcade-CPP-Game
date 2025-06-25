# 瘋狂炸彈人 (Crazy Arcade) 🎮
## 🚀 專案演進與後續計畫：從 C++ 到 Python 的重構與升級
> 本專案 (`CrazyArcade-CPP-Game`) 是我在大一上學期「計算機概論」課程中，對C++與遊戲邏輯的應用的探索，它為我奠定了重要的基礎。
>
> 在完成此專案後，我將從中學到的經驗與反思，在大一下的物件導向程式設計課程中，投入到一個**技術更深入、工程實踐更完善**的後續專案 **`Pycade Bomber`** 中。該專案在原有的基礎上進行了全面升級：
>
> * **技術棧升級**: 從純 C++ 控制台，升級為使用 **Python** 與 **Pygame** 函式庫，實現了更豐富的圖形化介面。
> * **AI 演算法強化**: AI 的路徑規劃演算法從 BFS 升級為 **A***，並設計了四種不同行為模式的 **Finite State Machine (FSM)**。
> * **導入現代軟體工程實踐**: 建立了完整的 **CI/CD (持續整合/持續部署)** 流程，透過 **GitHub Actions** 進行自動化測試 (Pytest) 與部署。
> * **線上遊玩**: 專案會自動部署到 **GitHub Pages**，您可以**直接在線上體驗最新版本**的遊戲。
>
> **因此，強烈建議優先瀏覽我更成熟的 `Pycade Bomber` 專案，以更全面地了解我的技術成長與工程能力。**
>
> * 🔗 [**前往更完善的 `Pycade Bomber` 專案 (Python/Pygame)**](https://github.com/peienwu1216/oop-2025-proj-pycade)
> * 📝 [**閱讀我為此專案撰寫的詳細開發歷程與技術剖析文章**](https://peienwu-blog-next.vercel.app/pycade-bomber-ai-and-cicd)

---
歡迎來到《瘋狂炸彈人》！這是一款基於經典炸彈人玩法的 C++ 遊戲專案。玩家可以在精心設計的地圖中與 AI 控制的對手或另一位玩家展開刺激的炸彈對決，收集強力道具，爭取最終的勝利。本專案為國立陽明交通大學計算機概論與程式設計的期末專題。

## 專案特色 ✨

* **多樣的遊戲模式**：
    * 單人模式：與 AI 電腦對戰 (提供簡易/困難兩種難度)。
    * 雙人模式：支援兩位玩家在同一台電腦上進行本地對戰。
* **動態地圖系統**：
    * 多種預設地圖可供選擇 (雙人模式)。
    * 隨機生成地圖，增加遊戲的重玩性與挑戰性。
* **豐富的道具系統**：收集各種道具來增強角色能力，如提升炸彈威力、增加炸彈數量、提高移動速度或增加生命值。
* **智慧型 AI 對手**：AI 採用有限狀態機 (Finite State Machine, FSM) 設計，並結合廣度優先搜尋 (Breadth-First Search, BFS) 演算法進行路徑規劃與決策，能夠執行躲避危險、追擊敵人、拾取道具等行為。
* **排行榜功能**：記錄玩家的輝煌戰績，挑戰高分。
* **物件導向設計**：專案採用物件導向程式設計 (OOP) 原則，提高程式碼的可維護性與擴展性。

## 目錄 📖

- [瘋狂炸彈人 (Crazy Arcade) 🎮](#瘋狂炸彈人-crazy-arcade-)
  - [專案特色 ✨](#專案特色-)
  - [目錄 📖](#目錄-)
  - [系統需求 (System Requirements) 💻](#系統需求-system-requirements-)
  - [檔案結構 (File Structure) 📂](#檔案結構-file-structure-)
  - [編譯與執行 (Compilation and Execution) 🚀](#編譯與執行-compilation-and-execution-)
  - [遊戲操作 (Controls) 🕹️](#遊戲操作-controls-️)
  - [遊戲機制與道具 (Game Mechanics \& Items) 💣💥](#遊戲機制與道具-game-mechanics--items-)
    - [選單選項 (Menu Options)](#選單選項-menu-options)
    - [道具說明 (Item Descriptions)](#道具說明-item-descriptions)
    - [計分與勝利條件 (Scoring and Victory)](#計分與勝利條件-scoring-and-victory)
  - [AI 行為詳解 (AI Behavior) 🧠](#ai-行為詳解-ai-behavior-)
  - [開發團隊 (Developers) 🧑‍💻](#開發團隊-developers-)
  - [開發歷程與致謝 (Development Process \& Acknowledgements) 🙏](#開發歷程與致謝-development-process--acknowledgements-)
  - [未來展望 (Future Work) 🚀](#未來展望-future-work-)
  - [授權條款 (License) 📄](#授權條款-license-)

## 系統需求 (System Requirements) 💻

* **作業系統：** Windows / macOS / Linux (已在這些平台上測試)
* **編譯器：** 建議使用 g++ 或 clang++ (需支援 C++14 或更高版本)
* **必要函式庫：** 標準 C++ 庫 (Standard C++ Library)

## 檔案結構 (File Structure) 📂

以下為本專案的目錄結構：

```text
CrazyArcade/
├── .git/                   # Git 版本控制系統目錄 (自動生成)
├── .gitignore              # 指定 Git 忽略追蹤的檔案與目錄
├── src/                    # 存放所有 C++ 原始碼檔案 (.cpp) 與標頭檔 (.h)
│   ├── AIController.cpp
│   ├── AIController.h
│   ├── GameCrazyArcade.cpp
│   ├── GameCrazyArcade.h
│   ├── GameObject.cpp
│   ├── GameObject.h
│   ├── Globals.cpp
│   ├── Globals.h
│   ├── main.cpp
│   ├── Menu.cpp
│   └── Menu.h
├── assets/                 # 存放遊戲所需的資源檔案
│   ├── animation.txt       # ASCII 動畫效果文字檔
│   └── leaderboard.txt     # 排行榜資料存檔 (初始可能為空或範例)
├── docs/                   # 存放專案相關文件
│   └── CrazyArcade_Final_Report.pdf # 詳細的期末專題報告
├── README.md               # 即本檔案，專案的主要說明文件
└── LICENSE                 # 專案的開源許可證文件
```

詳細的專案設計與實作細節，請參閱 [`docs/CrazyArcade_Final_Report.pdf`](./docs/CrazyArcade_Final_Report.pdf)。

## 編譯與執行 (Compilation and Execution) 🚀

請依照以下步驟編譯並執行本遊戲：

1.  **取得專案：**
    * 若您尚未取得專案，請先 Clone 本倉庫：
        ```bash
        git clone https://github.com/peienwu1216/CrazyArcade.git
        ```
    * 進入專案根目錄：
        ```bash
        cd CrazyArcade
        ```

2.  **編譯原始碼：**
    本專案提供了 Makefile 以簡化編譯流程。請在專案的**根目錄**下執行以下指令：
    ```bash
    make
    ```
    或者，若要包含所有編譯警告：
    ```bash
    make all
    ```
    這將使用 `g++` 和 C++14 標準進行編譯，並在根目錄生成名為 `CrazyArcade` 的執行檔。

3.  **執行遊戲：**
    編譯成功後，可使用以下指令執行遊戲：
    ```bash
    make run
    ```
    或者直接執行：
    * 在 Linux / macOS 上執行：
        ```bash
        ./CrazyArcade
        ```
    * 在 Windows 上執行 (可能為 `CrazyArcade.exe`)：
        ```bash
        CrazyArcade.exe
        ```
    遊戲啟動後，您將看到主選單。

若需要清理編譯產生的檔案，可以執行：
```bash
make clean
```

## 遊戲操作 (Controls) 🕹️

**遊戲目標：**
* 利用炸彈消滅所有對手。
* 策略性地收集道具以強化自身能力。
* 成功炸到對手可獲得 +100 分。

**基本操作：**

* **玩家 1 (Player 1):**
    * 移動 (Move): `W` (上), `A` (左), `S` (下), `D` (右)
    * 放置炸彈 (Place Bomb): `F`

* **玩家 2 (Player 2) (雙人模式時):**
    * 移動 (Move): `O` (上), `K` (左), `L` (下), `;` (右) (或根據你的實際設定調整)
    * 放置炸彈 (Place Bomb): `J` (或根據你的實際設定調整)

**選單操作 (Menu Navigation):**
* 通常使用 `W` (上) 和 `S` (下) 選擇選項。
* 使用 `Enter` (或特定按鍵，請依遊戲內提示) 確認選項。

## 遊戲機制與道具 (Game Mechanics & Items) 💣💥

### 選單選項 (Menu Options)
啟動遊戲後，您將進入主選單頁面，包含以下選項：
1.  **Start Single-Player Game (Easy):** 與 AI 電腦對戰，簡單模式。
2.  **Start Single-Player Game (Hard):** 與 AI 電腦對戰，困難模式。
3.  **Start Two-Player Game:** 雙人對戰模式，地圖為隨機選擇。
4.  **Select Map:** (雙人模式) 點按後可選擇三種不同難度的預設地圖。
5.  **View Leaderboard:** 查看排行榜。
6.  **Exit:** 結束遊戲並退出程式。

*(單人及雙人遊戲模式中的地圖均包含隨機生成的障礙物與道具)*

### 道具說明 (Item Descriptions)
在地圖中破壞可摧毀的障礙物後，有機會出現以下道具：
* **綠色星星 ★:** 增加玩家分數 +50 分。
* **紅色愛心 ♥:** 增加玩家生命值 +1 條命，以及獲得分數 +20分。
* **黑桃 ♠:** 玩家可同時放置的炸彈數量上限 +1，以及獲得分數 +20 分。
* **黑色齒輪符號 ❁:** 炸彈爆炸範圍 +1 格，以及獲得分數 +20分。

### 計分與勝利條件 (Scoring and Victory)
* **擊敗對手:** +100 分。
* **收集道具:** 如上所述，不同道具提供不同分數。
* **勝利條件:** 在指定時間內（若有設定時限）或生命值耗盡前，最後存活的玩家獲勝。
* **排行榜登記:** 遊戲結束後，若分數夠高，勝利方可輸入名字記錄於排行榜。

## AI 行為詳解 (AI Behavior) 🧠

本遊戲中的 AI 採用有限狀態機 (FSM) 來控制其行為，並透過廣度優先搜尋 (BFS) 演算法來規劃移動路徑。AI 的主要決策狀態包括：

* **`ESCAPE` (逃離危險):**
    * **觸發條件:** 偵測到自身處於即將爆炸的炸彈範圍內。
    * **行為:** 迅速計算並移動至最近的安全區域。
* **`WAIT_EXPLOSION` (等待爆炸):**
    * **觸發條件:** AI 剛放置了一顆炸彈。
    * **行為:** 移動到預計的安全位置，等待自己放置的炸彈爆炸。
* **`Fetch_ITEMS` (拾取道具):**
    * **觸發條件:** 地圖上存在可拾取的道具，且自身未處於直接危險中，也沒有明確的攻擊目標。
    * **行為:** 計算前往最近或最有價值道具的路徑並移動拾取。
* **`ATTACK_PLAYER` (攻擊玩家):**
    * **觸發條件:** 偵測到敵方玩家進入其攻擊範圍或策略考量。
    * **行為:** 追蹤敵方玩家，並在適當時機與位置放置炸彈。
* **`IDLE` (閒置/巡邏):**
    * **觸發條件:** 當前沒有立即的危險、無道具可拾取、且無明確攻擊目標。
    * **行為:** 在地圖上隨機移動或有策略地巡邏，尋找新的機會或等待其他狀態觸發。

AI 的狀態會根據遊戲環境的即時變化（如玩家位置、炸彈狀態、道具出現等）動態切換，以模擬出更具挑戰性的對手。

## 開發團隊 (Developers) 🧑‍💻

* **主要開發者 (Lead Developer):** 113511103 吳沛恩
* **協同開發者 (Co-Developer/Contributor):** 113511216 洪崧祐

聯絡方式: `peien.wu1216@gmail.com`

## 開發歷程與致謝 (Development Process & Acknowledgements) 🙏

本專案是我們在計算機與程式設計概論的課程中，投入大量時間與心血完成的作品。在整個開發過程中，我們深入學習並實踐了物件導向程式設計 (OOP) 的核心概念，包括類別的封裝、繼承與多型。同時，為了實現智慧型 AI，我們研究並應用了廣度優先搜尋 (BFS) 演算法以及有限狀態機 (FSM) 的設計模式。

UI/UX 設計方面，我們也嘗試加入了開場動畫、勝利動畫等視覺元素，力求提升玩家的遊戲體驗。地圖隨機生成與道具系統的設計，旨在增加遊戲的趣味性與耐玩度。但由於教授規定不能使用其他函式庫，因此我們只有使用C++函式庫做 UI/UX 的優化。

**特別感謝：**
* 教授以及助教在我們開發過程中給予實用的建議與指導
* 在專案的構思、演算法設計、程式碼撰寫與除錯，以及文件整理的過程中，我們也積極運用了AI 輔助工具ChatGPT 進行協作，它在提供解決方案建議、解釋複雜概念及優化程式碼方面給予了我們莫大的幫助，顯著提升了開發效率與專案品質。

## 未來展望 (Future Work) 🚀 

雖然目前專案已達到一個完整可玩的階段，但仍有一些可以進一步探索與完善的方向：
* **更豐富的遊戲內容：** 設計更多種類的地圖、道具與角色特殊能力。
* **網路對戰功能：** 引入多人連線對戰，讓玩家可以與遠方的朋友一較高下。
* **AI 深度強化：** 探索更進階的 AI 演算法，如 Minimax、蒙地卡羅樹搜尋 (MCTS) 或機器學習模型，讓 AI 行為更加複雜與擬人化。
* **圖形化介面升級：** 使用如 SDL, SFML 等圖形函式庫，將目前的文字介面升級為更精美的 2D 圖形介面。

## 授權條款 (License) 📄

本專案採用 [MIT 許可證 (MIT License)](./LICENSE) 進行授權。歡迎自由使用、修改與散佈，但請務必保留原始的版權聲明。

---

希望這份《瘋狂炸彈人》能帶給您愉快的遊戲時光！如果您有任何建議或發現任何問題，歡迎隨時與我們聯繫。
