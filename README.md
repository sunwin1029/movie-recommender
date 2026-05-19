

# Movie-recommender

> 20211423 서해승 
> C++ 프로그래밍 및 실습 마일스톤 과정을 위한 레포지토리입니다.

## 현재 파일별 용도

1. `Movie`, `User`, `Rating`
- 영화, 사용자, 평점 데이터를 표현하는 기본 클래스입니다.

2. `MovieManager`, `UserManager`, `RatingManager`
- 각 데이터 목록을 `vector`로 관리합니다.
- 추가, 검색, 목록 출력, CSV `loadFromFile` / `saveToFile` 기능을 담당합니다.
- `BaseManager`를 상속하여 공통 인터페이스를 맞춥니다.

3. `Manager`
- 세부 Manager들을 조율하는 상위 클래스입니다.
- 중복 ID, 존재하지 않는 사용자/영화, 평점 범위, 추천 가능 여부 같은 도메인 검증을 담당합니다.
- 프로그램 시작 시 CSV를 로드하고 종료 시 저장합니다.

4. `UserInterface`
- 메뉴 출력과 사용자 입력을 담당합니다.
- 정수/실수 입력 형식 검증을 수행하고, 실제 작업은 `Manager`에 요청합니다.

5. `SimilarityCalculator`
- 두 사용자의 평점 목록을 비교하여 유사도 점수를 계산합니다.
- 공통 영화 수와 평점 차이를 기반으로 계산합니다.

6. `Recommender`
- 대상 사용자와 유사한 사용자를 찾고, 대상 사용자가 아직 보지 않은 영화를 추천합니다.
- 추천 결과는 movieId 목록으로 반환합니다


## 실행방법

```zsh
# 컴파일
make

# 프로그램 실행
make run 
```
