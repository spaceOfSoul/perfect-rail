# Perfect Rail
SFML을 활용하여 제작한 건반형 리듬게임.

### setting for debian(linux)
- sfml 설치
    ```
    sudo apt-get update
    sudo apt-get upgrade

    sudo apt-get install libsfml-dev
    ```
- 기타 종속성
    ```
    sudo apt-get install libopenal-dev libflac-dev libvorbis-dev
    sudo apt-get install libenet-dev
    sudo apt-get install libfreetype6-dev libjpeg-dev libxrandr-dev libglew-dev
    ```


### CMAKE build
`Project31`에 `build` 디렉토리 만든 후 그 안에서 아래 명령으로 빌드.
- 디버그
  ```
  cmake -DCMAKE_BUILD_TYPE=Debug ..
  ```
- 릴리즈
    ```
    cmake -DCMAKE_BUILD_TYPE=Release ..
    ```

### g++ 빌드
위 빌드가 잘 먹히지 않는 경우, 아래와 같은 구문을 사용하여 g++ 수동 빌드를 진행할 수 있다.
- 디버그
  ```
  g++ -std=c++17 -g -O0 -o PerfectRail *.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
    ```