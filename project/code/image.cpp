#include "image.h"

#define white 255 
using namespace std;


/*************************************************************** 
* 函数名称：GetOSTU,大津法
* 函数输入：摄像头传感器图像数组
* 函数输出：阈值大小 （Threshold）
* 功能说明：求阈值大小 
***************************************************************/
short GetOSTU (unsigned char tmImage[UVC_HEIGHT][UVC_WIDTH])
{
    signed short i, j;
    unsigned long Amount = 0;
    unsigned long PixelBack = 0;
    unsigned long PixelshortegralBack = 0;
    unsigned long Pixelshortegral = 0;
    signed long PixelshortegralFore = 0;
    signed long PixelFore = 0;
    float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // 类间方差;
    signed short MinValue, MaxValue;
    signed short Threshold = 0;
    unsigned char HistoGram[256];              //

    for (j = 0; j < 256; j++)
        HistoGram[j] = 0; //初始化灰度直方图

    for (j = 0; j < UVC_HEIGHT; j++)
    {
        for (i = 0; i < UVC_WIDTH; i++)
        {
            HistoGram[tmImage[j][i]]++; //统计灰度级中每个像素在整幅图像中的个数
        }
    }

    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++);        //获取最小灰度的值
    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--); //获取最大灰度的值

    if (MaxValue == MinValue)
        return MaxValue;         // 图像中只有一个颜色
    if (MinValue + 1 == MaxValue)
        return MinValue;        // 图像中只有二个颜色

    for (j = MinValue; j <= MaxValue; j++)
        Amount += HistoGram[j];        //  像素总数

    Pixelshortegral = 0;
    for (j = MinValue; j <= MaxValue; j++)
    {
        Pixelshortegral += HistoGram[j] * j;        //灰度值总数
    }
    SigmaB = -1;
    for (j = MinValue; j < MaxValue; j++)
    {
        PixelBack = PixelBack + HistoGram[j];     //前景像素点数
        PixelFore = Amount - PixelBack;           //背景像素点数
        OmegaBack = (float) PixelBack / Amount;   //前景像素百分比
        OmegaFore = (float) PixelFore / Amount;   //背景像素百分比
        PixelshortegralBack += HistoGram[j] * j;  //前景灰度值
        PixelshortegralFore = Pixelshortegral - PixelshortegralBack;  //背景灰度值
        MicroBack = (float) PixelshortegralBack / PixelBack;   //前景灰度百分比
        MicroFore = (float) PixelshortegralFore / PixelFore;   //背景灰度百分比
        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);   //计算类间方差
        if (Sigma > SigmaB)                    //遍历最大的类间方差g //找出最大类间方差以及对应的阈值
        {
            SigmaB = Sigma;
            Threshold = j;
        }
    }
    return Threshold;                        //返回最佳阈值;
}

/*---------------------------------------------------------------
 【函    数】Bin_Image_Filter
 【功    能】过滤噪点
 【参    数】无
 【返 回 值】无
 【注意事项】
 ----------------------------------------------------------------*/
void Bin_Image_Filter(unsigned char Bin_Image[UVC_HEIGHT][UVC_WIDTH]) {
    int16_t nr; //行
    int16_t nc; //列

    for (nr = 1; nr < UVC_HEIGHT - 1; nr++) {
        for (nc = 1; nc < UVC_WIDTH - 1; nc++) {
            if ((Bin_Image[nr][nc] == 0) &&
                (Bin_Image[nr - 1][nc] + Bin_Image[nr + 1][nc] + Bin_Image[nr][nc + 1] + Bin_Image[nr][nc - 1] > 2)) {
                Bin_Image[nr][nc] = 1;
            } else if ((Bin_Image[nr][nc] == 1) &&
                       (Bin_Image[nr - 1][nc] + Bin_Image[nr + 1][nc] + Bin_Image[nr][nc + 1] + Bin_Image[nr][nc - 1] < 2)) {
                Bin_Image[nr][nc] = 0;
            }
        }
    }
}
/************************************************************
【函数名称】Horizontal_line
【功    能】横向巡线函数
【参    数】无
【返 回 值】无
【实    例】Horizontal_line();
【注意事项】无
***********************************************************/
void Horizontal_line(unsigned char Pixle[UVC_HEIGHT][UVC_WIDTH], int Row, int Col, int midline[], int leftline[], int rightline[])
{
  uint8_t i, j;
  // 初始化中间线
  if(Pixle[Row-1][Col/2] == 0)
  {
    if(Pixle[Row-1][5] == white)
      midline[Row] = 5;
    else if(Pixle[Row-1][Col-5] == white)
      midline[Row] = Col-5;
    else
      midline[Row] = Col/2;
  }
  else
  {
    midline[Row] = Col/2;
  }
  
  // 从底部向上遍历行
  for(i = Row-1; i > 0; i--)
  {
    // 寻找左侧线
    for(j = midline[i+1]; j >= 0; j--)
    {
      if(Pixle[i][j] == 0 || j == 0)
      {
        leftline[i] = j;
        break;
      }
    }
    // 寻找右侧线
    for(j = midline[i+1]; j <= Col-1; j++)
    {
      if(Pixle[i][j] == 0 || j == Col-1)
      {
        rightline[i] = j;
        break;
      }
    }
    // 计算中间线
    midline[i] = (leftline[i] + rightline[i]) / 2;
    // 如果上一行的中间线是黑色，则向上传播当前中间线
    if(Pixle[i-1][midline[i]] == 0 || i == 0)
    {
      for(j = i; j > 0; j--)
      {
        midline[j] = midline[i];
        leftline[j] = midline[i];
        rightline[j] = midline[i];
      }
      break;
    }
  }
}
void binary_ipsdrawline() {
    cv::Mat frame, grayFrame, binaryFrame;


    // 声明舵机控制器
    ServoController my_servo;


    ips200_init("/dev/fb0");

    servo_init(&my_servo);  // 初始化舵机
        // 初始化电机系统
    MotorController::initialize();

    // 使用 OpenCV 的 VideoCapture 打开摄像头
    cv::VideoCapture cap("/dev/video0");
    if (!cap.isOpened()) {
        printf("Error: Could not open camera!\n");
        return;
    }

    // 设置摄像头分辨率（可选）
    cap.set(cv::CAP_PROP_FRAME_WIDTH, UVC_WIDTH);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, UVC_HEIGHT);

    // 定义中线、左线和右线数组
    int midline[UVC_HEIGHT] = {0};
    int leftline[UVC_HEIGHT] = {0};
    int rightline[UVC_HEIGHT] = {0};
    uint8_t binaryArray[UVC_HEIGHT][UVC_WIDTH] = {0};


    while (1) {
        // 从摄像头读取一帧
        if (!cap.read(frame)) {
            printf("Error: Could not read frame!\n");
            continue;  // 跳过本次循环
        }

        // 检查图像是否有效
        if (frame.empty()) {
            printf("Warning: Empty frame!\n");
            continue;
        }

        // 转换为灰度图
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

        // 二值化处理
        cv::threshold(grayFrame, binaryFrame, 128, 255, cv::THRESH_BINARY);

        // 将二值化图像复制到数组
        for (int i = 0; i < UVC_HEIGHT; i++) {
            for (int j = 0; j < UVC_WIDTH; j++) {
                binaryArray[i][j] = binaryFrame.at<uint8_t>(i, j);
            }
        }

        // 显示图像
        Horizontal_line(binaryArray, UVC_HEIGHT, UVC_WIDTH, midline, leftline, rightline);


        // 计算偏差并控制舵机
        int error = midline[UVC_HEIGHT - 1] - (UVC_WIDTH / 2);
        servo_control_by_error(&my_servo, error, UVC_WIDTH / 2);
            // 设置最大速度为50%
        MotorController::setMaxSpeed(20);
        MotorController::setMotors(12, 12);    // 两电机40%速度前进

        ips200_show_binary_image(0, 0, binaryFrame.data, binaryFrame.cols, binaryFrame.rows, midline);
    }

    cap.release();  // 释放摄像头
}
