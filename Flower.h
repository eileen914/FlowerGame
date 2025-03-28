#ifndef FLOWER_H
#define FLOWER_H

class Flower {
    private:
        float waterLevel;      // 물의 양
        float sunLevel;        // 햇빛의 양
        int growthStage;     // 성장단계 (0:새싹, 1:(좀 더 자란)풀, 2:꽃)
        bool isWilted;       // 시들었는지 여부
        float decreaseRate;    // 성장 단계별 물/햇빛 감소 속도
        float remainingTime;   // 각 단계에서 남은 시간 (초 단위)
        bool isGameComplete;      // 게임 종료 상태 확인 변수

    public:
        Flower();
        void reset();         // 초기화
        void giveWater();     // (사용자) 물 주기
        void giveSunlight();  // (사용자) 햇빛 받기
        void timePasses(float elapsed);    // 시간이 지나면서 물/햇빛의 양이 줄어들도록 하는 메소드
        void checkStatus();   // 현재 상태 체크
        void resetTimer();       // 타이머 초기화
        float getRemainingTime() const;  // 남은 시간
        void showFlower();    // 꽃의 상태를 화면에 출력

        // Getter 메서드들
        float getWaterLevel() const;     // 물의 양
        float getSunLevel() const;       // 햇빛의 양
        int getGrowthStage() const;    // 성장 단계
        bool getIsWilted() const;      // 시들었는지 여부
        bool getIsGameComplete() const; // 게임 완료 여부
};

#endif
