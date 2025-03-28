#include "Flower.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;

int main() {
    // SFML 창 생성
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Flower Game");

    // 폰트와 텍스트 설정
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        cerr << "폰트를 로드할 수 없습니다! 기본 폰트를 사용합니다." << endl;
        font.loadFromFile("/System/Library/Fonts/Supplemental/Courier New.ttf");
    }


    sf::Text timerText;
    timerText.setFont(font);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(10, 10); // 창의 왼쪽 상단에 위치

    sf::Text flowerState;
    flowerState.setFont(font);
    flowerState.setCharacterSize(24);
    flowerState.setFillColor(sf::Color::White);
    flowerState.setPosition(10, 50); // timerText 아래에 위치

    // 게임 시작을 위한 시작 시간 기록
    auto startTime = chrono::steady_clock::now();

    // Opening 이미지 텍스처와 스프라이트 설정
    sf::Texture openingTexture;
    sf::Sprite openingSprite;
    if (!openingTexture.loadFromFile("/Users/junha/Desktop/컴퓨터프로그래밍/C++ PJ/Opening.png")) {
        cerr << "Error: Unable to load Opening image" << endl;
    } else {
        openingSprite.setTexture(openingTexture);
        
        // 창에 맞게 스케일 조정
        float windowWidth = window.getSize().x;
        float windowHeight = window.getSize().y;
        float scaleX = windowWidth / openingSprite.getLocalBounds().width;
        float scaleY = windowHeight / openingSprite.getLocalBounds().height;
        float scale = min(scaleX, scaleY) * 0.7f;  // 필요 시 축소
        openingSprite.setScale(scale, scale);
        
        // 스프라이트를 창 중앙에 배치
        openingSprite.setOrigin(openingSprite.getLocalBounds().width / 2, openingSprite.getLocalBounds().height / 2);
        openingSprite.setPosition(windowWidth / 2, windowHeight / 2);
    }

    // 꽃 이미지 텍스처와 스프라이트 설정
    sf::Texture flowerTexture;
    sf::Sprite flowerSprite;

    Flower myFlower;  // Flower 객체 생성
    
    auto lastUpdate = chrono::steady_clock::now();  // 마지막 업데이트 시간 저장

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (!myFlower.getIsGameComplete()) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::A) {
                        myFlower.giveWater();  // 물 주기
                    } else if (event.key.code == sf::Keyboard::G) {
                        myFlower.giveSunlight();  // 햇빛 주기
                    }
                }
            }
        }

        // 게임 시작 전 경과 시간 계산
        auto now = chrono::steady_clock::now();
        float elapsedOpeningTime = chrono::duration_cast<chrono::seconds>(now - startTime).count();

        if (elapsedOpeningTime < 10) {
            // 10초 동안 Opening 화면 표시
            window.clear();
            window.draw(openingSprite);
            window.display();
            continue;
        } else if (elapsedOpeningTime == 10) {
            myFlower.reset();  // Opening 후 Flower 객체 초기화
        }

        // 이후 게임 진행
        if (!myFlower.getIsGameComplete()) {
            auto now = chrono::steady_clock::now();
            float elapsed = chrono::duration_cast<chrono::milliseconds>(now - lastUpdate).count() / 1000.0f;
            if (elapsed >= 0.1f) {
                myFlower.timePasses(elapsed);
                lastUpdate = now;
            }
        }

        // 꽃의 상태에 따라 이미지 변경
        string imagePath;
        if (myFlower.getIsWilted()) {
            imagePath = "/Users/junha/Desktop/컴퓨터프로그래밍/C++ PJ/wilted.png";  // 시든 상태 이미지
        } else if (myFlower.getGrowthStage() == 0) {
            imagePath = "/Users/junha/Desktop/컴퓨터프로그래밍/C++ PJ/pot.png";  // 화분 이미지
        } else if (myFlower.getGrowthStage() == 1) {
            imagePath = "/Users/junha/Desktop/컴퓨터프로그래밍/C++ PJ/sprout.png";   // 새싹 이미지
        } else if (myFlower.getGrowthStage() == 2) {
            imagePath = "/Users/junha/Desktop/컴퓨터프로그래밍/C++ PJ/plant.png";  // 풀 이미지
        } else if (myFlower.getGrowthStage() == 3) {
            imagePath = "/Users/junha/Desktop/컴퓨터프로그래밍/C++ PJ/flower.png";  // 꽃 이미지
        } else if (myFlower.getGrowthStage() == 4) {
            imagePath = "/Users/junha/Desktop/컴퓨터프로그래밍/C++ PJ/bloomed_flower.png";  // 만개한 꽃 이미지
        } else if (myFlower.getGrowthStage() == 5) {
            imagePath = "/Users/junha/Desktop/컴퓨터프로그래밍/C++ PJ/full_bloom.png";  // 최종 단계 이미지
        }

        // 이미지 로드는 한번만 시도
        if (!flowerTexture.loadFromFile(imagePath)) {
            cerr << "Error: Unable to load image from " << imagePath <<endl;
        } else {
            flowerSprite.setTexture(flowerTexture);

            // 1. 텍스처를 스프라이트에 설정
            flowerSprite.setTexture(flowerTexture);

            // 32. 스프라이트 원점을 이미지 중앙으로 설정
            flowerSprite.setOrigin(flowerSprite.getLocalBounds().width / 2, flowerSprite.getLocalBounds().height / 2);
            // cout << "Sprite origin set to center: (" << flowerSprite.getOrigin().x << ", " << flowerSprite.getOrigin().y << ")" << endl;

            // 3. 창의 크기 가져오기
            float windowWidth = window.getSize().x;
            float windowHeight = window.getSize().y;
            // cout << "Window size: " << windowWidth << " x " << windowHeight << endl;

            // 4. sprite의 크기 가져오기
            float spriteWidth = flowerSprite.getLocalBounds().width;
            float spriteHeight = flowerSprite.getLocalBounds().height;

            // 창에 맞는 스케일 계산 (너비와 높이 비율 중 작은 값을 선택)
            float scaleX = windowWidth / spriteWidth;
            float scaleY = windowHeight / spriteHeight;
            float scale = min(scaleX, scaleY) * 0.7f;  // 창에 맞게 축소하고, 필요 시 0.5f로 추가 축소

            // 필요에 따라 sprite의 스케일 설정
            flowerSprite.setScale(scale, scale);  

            // 스프라이트를 창 중앙에 배치
            flowerSprite.setPosition(windowWidth / 2, windowHeight / 2);

        }

        // 남은 시간 텍스트 업데이트
        int remainingTime = myFlower.getRemainingTime();  // 남은 시간 가져오기
        timerText.setString("Time left: " + to_string(remainingTime) + "s");

        // 물과 햇빛의 양을 소수점 첫째 자리까지 표시하기 위해 ostringstream 사용
        ostringstream waterStream, sunlightStream;
        waterStream << fixed << setprecision(1) << myFlower.getWaterLevel();
        sunlightStream << fixed << setprecision(1) << myFlower.getSunLevel();
        
        // 꽃의 상태를 텍스트로 업데이트
        flowerState.setString("Water: " + waterStream.str() +
                              "\nSunlight: " + sunlightStream.str() +
                              "\nStage: " + to_string(myFlower.getGrowthStage()) +
                              "\nWilted: " + (myFlower.getIsWilted() ? "Yes" : "No"));

        // 화면 그리기
        window.clear();
        window.draw(flowerSprite);
        window.draw(timerText);
        window.draw(flowerState);
        window.display();
    }

    return 0;
}