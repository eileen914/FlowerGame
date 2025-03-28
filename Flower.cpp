#include "Flower.h"
#include <iostream>
#include <algorithm>
using namespace std;

// 생성자: 초기 상태 설정
Flower::Flower() : waterLevel(100.0f), sunLevel(100.0f), growthStage(0), isWilted(false), isGameComplete(false), decreaseRate(1.0f), remainingTime(10.0f) {}

// (성장단계) 초기화
void Flower::reset() {
    growthStage = 0;       // 성장 단계를 0으로 초기화
}

// 물 주기
void Flower::giveWater() {
    if (!isWilted && !isGameComplete) {
        waterLevel = min(100.0f, waterLevel + 5.0f);
        cout << "물을 주었습니다. 현재 물: " << waterLevel << endl;
    }
}

// 햇빛 받기
void Flower::giveSunlight() {
    if (!isWilted && !isGameComplete) {
        sunLevel = min(100.0f, sunLevel + 5.0f);
        cout << "햇빛을 받았습니다. 현재 햇빛: " << sunLevel << endl;
    }
}

// 시간이 지날 때 물과 햇빛이 줄어듦
void Flower::timePasses(float elapsed) {
    if (!isWilted && !isGameComplete) {
        waterLevel = max(0.0f, waterLevel - decreaseRate * elapsed);
        sunLevel = max(0.0f, sunLevel - decreaseRate * elapsed);
        remainingTime-=elapsed;

        if (remainingTime <= 0.0f) {
            checkStatus();
            resetTimer();  // 타이머를 다시 10초로 초기화
        }
    }
}

// 꽃의 상태 확인
void Flower::checkStatus() {
    if (waterLevel <= 0.0f || sunLevel <= 0.0f) {
        isWilted = true;
        cout << "꽃이 시들었습니다." << endl;
    } else {
        // 각 단계별 물과 햇빛의 필요조건이 다르므로 조건 설정을 해줌
        float requiredWaterMin = 0.0f, requiredWaterMax = 100.0f;
        float requiredSunMin = 0.0f, requiredSunMax = 100.0f;
        float nextDecreaseRate = decreaseRate;
        switch (growthStage) {
            case 0:
                requiredWaterMin = 80.0f;
                requiredSunMin = 80.0f;
                nextDecreaseRate = 2.0f;
                break;
            case 1:
                requiredWaterMin = 70.0f;
                requiredWaterMax = 90.0f;
                requiredSunMin = 70.0f;
                requiredSunMax = 90.0f;
                nextDecreaseRate = 3.5f;
                break;
            case 2:
                requiredWaterMin = 75.0f;
                requiredWaterMax = 85.0f;
                requiredSunMin = 75.0f;
                requiredSunMax = 85.0f;
                nextDecreaseRate = 5.0f;
                break;
            case 3:
                requiredWaterMin = 80.0f;
                requiredWaterMax = 90.0f;
                requiredSunMin = 70.0f;
                requiredSunMax = 80.0f;
                nextDecreaseRate = 7.0f;
                break;
            case 4:
                requiredWaterMin = 80.0f;
                requiredWaterMax = 85.0f;
                requiredSunMin = 80.0f;
                requiredSunMax = 85.0f;
                nextDecreaseRate = 4.5f;
                break;
            case 5:
                isGameComplete = true;  // 성장 단계가 최종 단계에 도달하면 게임 완료 상태로 설정
                cout << "꽃이 최종 단계에 도달했습니다! 게임이 완료되었습니다." << endl;
                return;
    }

    // 성장 단계 변화 조건
    if (waterLevel >= requiredWaterMin && waterLevel <= requiredWaterMax &&
        sunLevel >= requiredSunMin && sunLevel <= requiredSunMax) {
            growthStage++;
            decreaseRate = nextDecreaseRate;
            cout << "꽃이 성장했습니다! 현재 성장 단계: " << growthStage << endl;
        }
    }
}

void Flower::resetTimer() {
    remainingTime = 10.0f;
}

float Flower::getRemainingTime() const {
    return remainingTime;
}

// 꽃의 상태 출력
void Flower::showFlower() {
    cout << "물: " << waterLevel << ", 햇빛: " << sunLevel
         << ", 성장 단계: " << growthStage
         << ", 시듦 여부: " << (isWilted ? "예" : "아니오") << endl;
}

// Getter 메서드들 구현
float Flower::getWaterLevel() const { return waterLevel; }
float Flower::getSunLevel() const { return sunLevel; }
int Flower::getGrowthStage() const { return growthStage; }
bool Flower::getIsWilted() const { return isWilted; }
bool Flower::getIsGameComplete() const { return isGameComplete; }