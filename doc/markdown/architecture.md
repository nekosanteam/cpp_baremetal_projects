# アーキテクチャ説明

## Platform の構成

- HAL: Hardware Abstraction Layer
- FAL: Firmware Abstraction Layer
- MAL: Middleware Abstraction Layer
- PAL: Platforms Abstraction Layer

## ソースコードの構成

- Benchmarks - PAL(MAL,FAL,HAL)
- BootLoader(Tiny) - HAL
- CyclicTest - FAL
- ResultsLog - MAL, FAL
- SelfChecks - HAL
- StressTest - FAL, HAL

## スタートアップ環境 (00_Startup)
予定

- x86_64
  - Linux (nostdlib)
    - _start からの実行
    - .bss のクリア
    - main() の呼び出し
- aarch64
  - Linux (nostdlib)
  - BareMetal (qemu, rpi3/4)
    - _reset からの実行
    - vector の設定
    - スタックポインタ設定・環境変数
    - _start 以降の実行、またはOS起動(ジャンプ(go)、Linuxカーネル起動(boot)
- arm(hf)
  - Linux (nostdlib)
  - BareMetal (qemu, rpi3/4)

## 01_Drivers、02_HAL 環境
予定

- 機種共通
  - タイマ
  - UART、標準入出力
- H/W
  - 割り込みコントローラ
  - SPIコントローラ
  - キャッシュ制御、atomic

## 03_OS、04_FAL 環境
予定

- 機種共通
  - タスク・スレッド・プロセス、CPUコア管理、排他制御、並列処理
  - メモリ管理、H/W I/F
  - 入出力管理

## 05_Libraries、06_MAL 環境
予定

- 機種共通
  - 文字列・メモリ操作
  - ログ出力
  - ストレージ管理、ファイルシステム
  - ネットワークプロトコル・スタック
  - 圧縮・展開、暗号化、乱数

## 07_PAL 環境
HAL, FAL, MALの各機能の export。
