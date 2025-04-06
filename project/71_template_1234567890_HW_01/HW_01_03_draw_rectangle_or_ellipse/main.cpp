#include <iostream>                
using namespace std;

#include <opencv2/opencv.hpp>      
using namespace cv;              

// 전역 변수 선언
Mat    g_imgColor;               
bool   g_isMousePressed = false;  
int    g_mouseStartX = -1;        
int    g_mouseStartY = -1;      

// 📝코드 수정 부분
int    g_viewX = -1;          // 드래그 중 현재 마우스 X 좌표 (미리보기용)
int    g_viewY = -1;          // 드래그 중 현재 마우스 Y 좌표 (미리보기용)
Scalar g_viewColor;           // 드래그 중 현재 마우스 색상 (미리보기용)
bool   g_drawEllipse = false; // 타원 그리기 토글 boolean 변수

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
    if (event == EVENT_LBUTTONDOWN)
    {
        g_isMousePressed = true;
        
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

        //📝코드 수정 부분 - m토글 사각형/타원
        if(!g_drawEllipse)
        {
            rectangle(g_imgColor, Point(g_mouseStartX, g_mouseStartY), Point(x, y), g_viewColor, -1);
        }
        else
        {
            //타원을 그릴 때 사각형에 내접하기 위해서는 상하좌우 변수를 세팅해야한다.
            int left = min(g_mouseStartX, g_viewX);
            int right = max(g_mouseStartX, g_viewX);
            int top = min(g_mouseStartY, g_viewY);
            int bottom = max(g_mouseStartY, g_viewY);

            // 사각형의 너비와 높이를 계산    
            int width = right - left;
            int height = bottom - top;

            // 타원의 중심 좌표와 반지름을 계산
            Point center((left + right) / 2, (top + bottom) / 2);
            // 타원의 반지름을 계산
            Size axes(width / 2, height / 2);

            ellipse(g_imgColor, center, axes, 0, 0, 360, g_viewColor, -1); // 하하 여기서 타원 영어를 알아갑니다
        }


        // 랜덤 색상을 생성하여 저장
        Scalar color = randomColor(g_rng);

        // 시작점(g_mouseStartX, g_mouseStartY)부터 현재 마우스 위치(x, y)를 대각선 꼭지점으로 하는 사각형을 그림
        // 마지막 인자 -1은 사각형 내부를 채우라는 의미
    }
}

int main()
{
    const int rows = 480;
    const int cols = 640;
    g_imgColor = Mat::zeros(rows, cols, CV_8UC3);

    String strWindowName = "Mouse Events";
    namedWindow(strWindowName);

    // 생성한 창에 대해 마우스 이벤트 콜백 함수를 등록
    setMouseCallback(strWindowName, mouse_callback);

    //📝코드 수정 부분
    while (true)
    {
        if(g_isMousePressed)
        {
            Mat preview = g_imgColor.clone(); 

            if(!g_drawEllipse)
            {
            rectangle(preview, Point(g_mouseStartX, g_mouseStartY), Point(g_viewX, g_viewY), g_viewColor, -1);
            }
            else
            {
                int left = min(g_mouseStartX, g_viewX);
                int right = max(g_mouseStartX, g_viewX);
                int top = min(g_mouseStartY, g_viewY);
                int bottom = max(g_mouseStartY, g_viewY);
                int width = right - left;
                int height = bottom - top;
                Point center((left + right) / 2, (top + bottom) / 2);
                Size axes(width / 2, height / 2);
                ellipse(preview, center, axes, 0, 0, 360, g_viewColor, -1); 
            }

            // 드래그 중일 때는 미리보기 이미지를 사용
            imshow(strWindowName, preview);
        }
        else
        {
            // 드래그 중이 아닐 때는 g_imgColor를 그대로 사용
            imshow(strWindowName, g_imgColor);
        }

        // 1밀리초 동안 키 입력 대기 (실시간 업데이트를 위해 짧은 지연)
        char key = waitKey(1);

        // 📝코드 수정 부분 - 토글 key 
        if (key == 'm' || key == 'M')
        {
            // m 키를 누르면 사각형/타원 모드 전환
            g_drawEllipse = !g_drawEllipse;
        }

        // ESC 키를 누르면 루프 종료
        if (key == 27) break;
    }

    // 모든 생성된 창을 닫음
    destroyAllWindows();

    return 0;
}

// 회고 : 타원 그려지는 과정을 계산하는 것이 조금 생각하기 어려웠다.
// 회고 : 콜백함수와 메인 루프 함수에 중복되는 부분이 있는데 이를 리팩토링해서 따로 빼려고 했다. 하지만 엄연히 둘은 다른 역할을 하는 것이기 떄문에 다른 맥락에서 호출되는 것이 좋다고 생각했다.