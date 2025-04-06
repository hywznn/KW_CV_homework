#include <iostream>                
using namespace std;

#include <opencv2/opencv.hpp>      
using namespace cv;              

// 전역 변수 선언
Mat    g_imgColor;               
bool   g_isMousePressed = false;  
int    g_mouseStartX = -1;        
int    g_mouseStartY = -1;      


int    g_viewX = -1;          // 드래그 중 현재 마우스 X 좌표 (미리보기용)
int    g_viewY = -1;          // 드래그 중 현재 마우스 Y 좌표 (미리보기용)
Scalar g_viewColor;           // 드래그 중 현재 마우스 색상 (미리보기용)

// 📝코드 수정 부분
int g_mode = 0; // 모드 전환을 위한 변수 (0: 사각형, 1: 타원, 2: 브러시)

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
        g_viewX = x;
        g_viewY = y;
        // 클릭 시 랜덤 색상을 생성하여 저장 (최종 도형과 원 브러시에 사용)
        g_viewColor = randomColor(g_rng);
        
        // 원 브러시 모드일 경우, 마우스 다운 시 최초 원 찍기
        if(g_mode == 2)
        {
            circle(g_imgColor, Point(x, y), 5, g_viewColor, -1);
        }
    }
    else if (event == EVENT_MOUSEMOVE && g_isMousePressed)
    {
        if(g_mode == 2)
        {
            // 📝코드 추가 부분 : 원 브러시 모드: 보간 없이 현재 마우스 위치에서 바로 원을 찍음
            circle(g_imgColor, Point(x, y), 5, g_viewColor, -1);
        }
        else
        {
            // 사각형, 타원 모드: 미리보기용 좌표 업데이트
            g_viewX = x;
            g_viewY = y;
        }
    }
    else if (event == EVENT_LBUTTONUP)
    {
        g_isMousePressed = false;
         // 📝코드 추가 부분 : 모드 구분을 잘 해줘야함 특히 도형 같은 경우는 출발점과 도착점 정의를 잘 해줘야함
        if(g_mode == 0)
        {
            // 사각형 모드: 최종 사각형 그리기
            rectangle(g_imgColor, Point(g_mouseStartX, g_mouseStartY), Point(x, y), g_viewColor, -1);
        }
        else if(g_mode == 1)
        {
            // 타원 모드: 출발점과 도착점을 포함하는 사각형 내에 내접하는 타원 그리기
            int left   = min(g_mouseStartX, x);
            int right  = max(g_mouseStartX, x);
            int top    = min(g_mouseStartY, y);
            int bottom = max(g_mouseStartY, y);
            int width  = right - left;
            int height = bottom - top;
            Point center((left + right) / 2, (top + bottom) / 2);
            Size axes(width / 2, height / 2);
            ellipse(g_imgColor, center, axes, 0, 0, 360, g_viewColor, -1);
        }
        // 원 브러시 모드에서는 마우스 이동 시 바로 그림이 찍히므로 별도 처리하지 않음
    }
}

int main()
{
    const int rows = 480;
    const int cols = 640;
    g_imgColor = Mat::zeros(rows, cols, CV_8UC3);

    String strWindowName = "Mouse Events";
    namedWindow(strWindowName);

    // 마우스 이벤트 콜백 등록
    setMouseCallback(strWindowName, mouse_callback);

    while (true)
    {
        if(g_isMousePressed && (g_mode == 0 || g_mode == 1))
        {
            // 사각형 또는 타원 모드의 경우, 미리보기로 현재 도형 상태를 보여줌
            Mat preview = g_imgColor.clone();
            if(g_mode == 0)
            {
                rectangle(preview, Point(g_mouseStartX, g_mouseStartY), Point(g_viewX, g_viewY), g_viewColor, -1);
            }
            else if(g_mode == 1)
            {
                int left   = min(g_mouseStartX, g_viewX);
                int right  = max(g_mouseStartX, g_viewX);
                int top    = min(g_mouseStartY, g_viewY);
                int bottom = max(g_mouseStartY, g_viewY);
                int width  = right - left;
                int height = bottom - top;
                Point center((left + right) / 2, (top + bottom) / 2);
                Size axes(width / 2, height / 2);
                ellipse(preview, center, axes, 0, 0, 360, g_viewColor, -1);
            }
            imshow(strWindowName, preview);
        }
        else
        {
            // 원 브러시 모드 또는 마우스 누르지 않은 경우, g_imgColor를 그대로 표시
            imshow(strWindowName, g_imgColor);
        }

        char key = waitKey(1);
        if(key == 27) // ESC 키 종료
            break;
        else if(key == 'm' || key == 'M')
        {
            // 'm' 키 토글: 모드를 순환 (0: 사각형, 1: 타원, 2: 원 브러시)
            g_mode = (g_mode + 1) % 3;
        }
    }

    destroyAllWindows();
    return 0;
}

// 회고 : mode 로 1,2,3 으로 조절하여 진행했다 , 원브러시 부분은 추가적으로 종료했을 때 카피할 부분이 따로 없어서 편했다.