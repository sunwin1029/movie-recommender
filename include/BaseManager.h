#pragma once
#include <string>

class BaseManager {
    public:
        // 각 Manager가 파일 입출력과 보유 데이터 수 조회를 같은 형태로 제공하도록 하는 공통 인터페이스
        virtual void loadFromFile(const std::string& filename) = 0;
        virtual void saveToFile(const std::string& filename) const = 0;
        virtual int size() const = 0;
        
        // BaseManager 포인터로 자식 Manager를 다룰 때도 올바른 소멸자가 호출되도록 virtual로 둔다.
        virtual ~BaseManager() {}
};
