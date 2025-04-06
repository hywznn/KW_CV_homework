#include <iostream>                // 표준 입출력 라이브러리 포함, 이하 생략.
using namespace std;

#include <opencv2/opencv.hpp>      // OpenCV 라이브러리 포함, 이하 생략.
using namespace cv;                // OpenCV 네임스페이스 사용, 이하 생략.

// 전역 변수 선언
Mat    g_imgColor;                // 그릴 이미지를 저장하는 변수 (컬러 이미지)
bool   g_isMousePressed = false;  // 마우스 버튼이 눌렸는지 여부를 저장하는 변수
int    g_mouseStartX = -1;        // 마우스 클릭 시 시작점의 X 좌표
int    g_mouseStartY = -1;        // 마우스 클릭 시 시작점의 Y 좌표

// 📝코드 수정 부분
int    g_viewX = -1;          // 드래그 중 현재 마우스 X 좌표 (미리보기용)
int    g_viewY = -1;          // 드래그 중 현재 마우스 Y 좌표 (미리보기용)
Scalar g_viewColor;           // 드래그 중 현재 마우스 색상 (미리보기용)

// OpenCV의 RNG 초기화 (현재 틱 카운트를 이용)
RNG g_rng(getTickCount());

// 랜덤 색상을 생성하는 함수
Scalar randomColor(RNG &g_rng)
{
    // RNG 객체를 통해 정수 난수를 생성하고, 이를 각 색상 채널에 할당
    int icolor = (unsigned) g_rng;
    // 각 채널은 8비트(0~255)로 표현: 비트마스킹과 시프트 연산을 통해 R, G, B 값을 추출   
    return Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}

// 마우스 이벤트 콜백 함수 정의
void mouse_callback(int event, int x, int y, int flags, void *param)
{
    // 마우스 왼쪽 버튼이 눌렸을 때의 처리
    if (event == EVENT_LBUTTONDOWN)
    {
        // 마우스 버튼이 눌렸음을 기록
        g_isMousePressed = true;
        
        // 현재 마우스의 위치를 시작점으로 저장
        g_mouseStartX = x;
        g_mouseStartY = y;

        //📝코드 수정 부분
        // 미리보기용 현재 좌표도 초기화
        g_viewX = x;
        g_viewY = y;
        //미리보기 색상도 deep copy로 했기 때문에 변수에 저장
        g_viewColor = randomColor(g_rng);
    }
    //📝코드 수정 부분
    else if (event == EVENT_MOUSEMOVE && g_isMousePressed)
    {
        // 드래그 중 : 현재 마우스 좌표에 따라 viewX,viewY 업데이트
        g_viewX = x;
        g_viewY = y;
        // 미리보기는 메인 루프에서 처리
        // 이유: 드래그 중에 실시간으로 사각형을 그리기 위해서는 매 프레임마다 이미지를 업데이트해야 함
        // 스레드 안전성 문제를 피하기 위해 메인 루프에서 처리
    }

    // 마우스 왼쪽 버튼에서 손을 뗄 때의 처리
    else if (event == EVENT_LBUTTONUP)
    {
        // 마우스 버튼이 눌리지 않은 상태로 변경
        g_isMousePressed = false;

        // 랜덤 색상을 생성하여 저장
        Scalar color = randomColor(g_rng);

        // 시작점(g_mouseStartX, g_mouseStartY)부터 현재 마우스 위치(x, y)를 대각선 꼭지점으로 하는 사각형을 그림
        // 마지막 인자 -1은 사각형 내부를 채우라는 의미
        rectangle(g_imgColor, Point(g_mouseStartX, g_mouseStartY), Point(x, y), g_viewColor, -1);
    }
}

int main()
{
    // 480x640 크기의 검은색(0으로 초기화된) 컬러 이미지 생성
    const int rows = 480;
    const int cols = 640;
    g_imgColor = Mat::zeros(rows, cols, CV_8UC3);

    // "Mouse Events"라는 이름의 창을 생성
    String strWindowName = "Mouse Events";
    namedWindow(strWindowName);

    // 생성한 창에 대해 마우스 이벤트 콜백 함수를 등록
    setMouseCallback(strWindowName, mouse_callback);

    // 무한 루프: 사용자가 ESC 키(ASCII 코드 27)를 누를 때까지 반복
    //📝코드 수정 부분
    while (true)
    {
        if(g_isMousePressed)
        {
            Mat preview = g_imgColor; // shallow copy가 #1-1, deep copy가 #1-2 의도인 것 같음 , #1-2에서는 .clone(); 로 현재 이미지를 복사하여 미리보기용 이미지 생성, 깊은 복사 deep copy
            // 이유1 : 드래그 중에 실시간으로 사각형을 그리기 위해서는 매 프레임마다 이미지를 업데이트해야 함
            // 이유2 : g_imgColor를 직접 수정하면 이미 그려진 사각형이 지워질 수 있음

            rectangle(preview, Point(g_mouseStartX, g_mouseStartY), Point(g_viewX, g_viewY), g_viewColor, -1);
            imshow(strWindowName, preview);
        }
        else
        {
            // 드래그 중이 아닐 때는 g_imgColor를 그대로 사용
            imshow(strWindowName, g_imgColor);
        }

        // 1밀리초 동안 키 입력 대기 (실시간 업데이트를 위해 짧은 지연)
        char key = waitKey(1);

        // ESC 키를 누르면 루프 종료
        if (key == 27) break;
    }

    // 모든 생성된 창을 닫음
    destroyAllWindows();

    return 0;
}

// 회고 : 전역변수를 사용하는 것에 익숙해져야함