volatile u8 isCharging = 0;      // 충전 중 플래그 (1: 충전 중일 때만 애니메이션)
static u8 chargingY = 41;
static s8 chargingDir = 1;
static u8 prevY = 41;
static u32 lastUpdateTick = 0;   // ms 단위 tick (사용자가 구현한 시스템 tick 필요)

// 빈 이미지 정의 (13x18 크기, 전부 0)
const u8 Blank13x18[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
};

HumanImagesDef IMG_Blank13x18 = {13, 18, Blank13x18};

void lfDisplay_Charging_Animate(void)
{
    if (!isCharging) return;

    // 딜레이 조건 체크 (GIF 속도: 약 200~250ms)
    if ((GetSysTick() - lastUpdateTick) < 250) return;
    lastUpdateTick = GetSysTick();

    // 이전 위치 지우기
    SSD1312_Images(ldIMG_BatteryCharing_X, prevY, IMG_Blank13x18);

    // 현재 위치 출력
    SSD1312_Images(ldIMG_BatteryCharing_X, chargingY, IMG_BatteryCharing);
    prevY = chargingY;

    // 다음 위치 계산
    chargingY += chargingDir;

    // 방향 전환
    if (chargingY >= 43) chargingDir = -1;
    else if (chargingY <= 41) chargingDir = 1;
}
