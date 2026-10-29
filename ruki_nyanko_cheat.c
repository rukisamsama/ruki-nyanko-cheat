// ============================================================
// にゃんこ大戦争 チート dylib
// 2026.10.27 developer @ruki1919
// 修正版H5GGで手動ロードする想定
// Lua版の内容をネイティブに移植
// ============================================================

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// ===================== オフセット（必ず埋める） =====================
static uint64_t OFF_CATFOOD          = 0x0;  // 猫缶
static uint64_t OFF_XP               = 0x0;  // XP
static uint64_t OFF_NP               = 0x0;  // NP
static uint64_t OFF_CATFOOD_MAX      = 0x0;  // 猫缶最大値
static uint64_t OFF_MONEY            = 0x0;  // 所持金
static uint64_t OFF_CASTLE_HP        = 0x0;  // にゃんこ城HP
static uint64_t OFF_CASTLE_LEVEL     = 0x0;  // にゃんこ城レベル
static uint64_t OFF_MATATABI_RED     = 0x0;  // 赤マタタビ
static uint64_t OFF_MATATABI_BLUE    = 0x0;  // 青マタタビ
static uint64_t OFF_MATATABI_PURPLE  = 0x0;  // 紫マタタビ
static uint64_t OFF_MATATABI_YELLOW  = 0x0;  // 黄マタタビ
static uint64_t OFF_MATATABI_RAINBOW = 0x0;  // 虹マタタビ
static uint64_t OFF_SPEED            = 0x0;  // ゲーム速度

// ===================== 状態 =====================
static bool autoclick_enabled = false;
static float autoclick_interval = 0.08f;

// ===================== メモリ操作 =====================
static bool write_u32(uint64_t addr, uint32_t value) {
    if (addr == 0) return false;
    *(volatile uint32_t *)addr = value;
    return true;
}

static bool write_float(uint64_t addr, float value) {
    if (addr == 0) return false;
    *(volatile float *)addr = value;
    return true;
}

static uint32_t read_u32(uint64_t addr) {
    if (addr == 0) return 0;
    return *(volatile uint32_t *)addr;
}

// ===================== メイン機能 =====================
void cheat_set_catfood(uint32_t value) {
    write_u32(OFF_CATFOOD, value);
}

void cheat_set_xp(uint32_t value) {
    write_u32(OFF_XP, value);
}

void cheat_set_np(uint32_t value) {
    write_u32(OFF_NP, value);
}

void cheat_set_catfood_max(uint32_t value) {
    write_u32(OFF_CATFOOD_MAX, value);
}

void cheat_unlock_all_characters(void) {
    // 全キャラ解放
    // 実際はキャラデータの配列をまとめて書き換える必要がある
    // オフセットが揃ってから実装
}

void cheat_unlock_character_by_id(uint32_t id) {
    // 指定キャラ解放（ID指定）
    // オフセット + id の計算が必要
}

void cheat_unlock_all_evolve(void) {
    // 全進化解放
}

void cheat_unlock_all_talents(void) {
    // 本能全解放
}

void cheat_max_all_levels(void) {
    // 全キャラレベルMAX
}

// ===================== 素材系 =====================
void cheat_set_matatabi_red(uint32_t value) {
    write_u32(OFF_MATATABI_RED, value);
}

void cheat_set_matatabi_blue(uint32_t value) {
    write_u32(OFF_MATATABI_BLUE, value);
}

void cheat_set_matatabi_purple(uint32_t value) {
    write_u32(OFF_MATATABI_PURPLE, value);
}

void cheat_set_matatabi_yellow(uint32_t value) {
    write_u32(OFF_MATATABI_YELLOW, value);
}

void cheat_set_matatabi_rainbow(uint32_t value) {
    write_u32(OFF_MATATABI_RAINBOW, value);
}

void cheat_set_all_matatabi(uint32_t value) {
    cheat_set_matatabi_red(value);
    cheat_set_matatabi_blue(value);
    cheat_set_matatabi_purple(value);
    cheat_set_matatabi_yellow(value);
    cheat_set_matatabi_rainbow(value);
}

void cheat_set_castle_level(uint32_t value) {
    write_u32(OFF_CASTLE_LEVEL, value);
}

void cheat_max_castle_materials(void) {
    // 城強化素材一括MAX
    // 複数オフセットが必要
}

// ===================== 詳細設定 =====================
void cheat_set_castle_hp(uint32_t value) {
    write_u32(OFF_CASTLE_HP, value);
}

void cheat_set_money(uint32_t value) {
    write_u32(OFF_MONEY, value);
}

void cheat_remove_ads(void) {
    // 広告削除
    // 実装は環境依存
}

void cheat_set_game_speed(float multiplier) {
    // 100 = 等倍 → 1.0f
    write_float(OFF_SPEED, multiplier);
}

void cheat_autoclick_enable(bool enable) {
    autoclick_enabled = enable;
}

void cheat_autoclick_set_interval(float seconds) {
    if (seconds > 0.0f) {
        autoclick_interval = seconds;
    }
}

// ===================== ロード時処理 =====================
__attribute__((constructor))
static void on_dylib_load(void) {
    // H5GGでこのdylibを選んでロードした瞬間に実行される
    // ここに「起動時に自動でやりたいこと」を書ける

    // 例:
    // cheat_set_catfood(999999);
    // cheat_set_xp(99999999);
    // cheat_set_all_matatabi(9999);
}

// 外部から呼び出せるエントリ（必要なら）
void ruki_cheat_init(void) {
    // 修正版H5GGが特定の関数を呼ぶ場合に備えて残す
}
