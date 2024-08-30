/**
 *****************************东莞理工学院ACE实验室 *****************************
 * @file Serial.c/h
 * @brief 串口，于蓝牙模块通信
 * @note 
 * @history 24/7/12   确定摇杆控制模式以及控制信号修正
 *          24/7/19   修改并决定整体小车控制信号
 *
 @verbatim 
 ==============================================================================
 使用数据包接收手机蓝牙的信号，控制小车移动
 串口： usart1: 小车蓝牙控制
        usart2: 视觉信号传输
 
 usart1：
 蓝牙模块：hc-05   波特率 38400
 数据形式：
     包头0xFF
     四位16进制数据信号
     包尾0xFE
     
     Serial_TxPacket[0] : 00底盘，01速度，02机械臂，03抓夹
     
     
 遥感控制：                         模式选择                   控制信号
                                      停止                   FF00000000FE
     左前进  前进  右前进             前进                   FF00000055FE
          \   |   /                   后退                   FF000000AAFE
           \  |  /                   左前进                  FF00010055FE
            \ | /                    右前进                  FF00020055FE
  左平移-----停止----- 右平移        左平移                  FF00000066FE
            / | \                    右平移                  FF00000099FE
           /  |  \                   左自旋                  FF00000096FE
          /   |   \                  右自旋                  FF00000069FE
    左自旋  后退  右自旋                                 
    
  usart2：
     视觉串口通信    波特率 115200
     
     一位数据接收       颜色识别
         0x00             蓝色
         0x01             红色
         0x02             黄色
 ==============================================================================
 @endverbatim
 *****************************东莞理工学院ACE实验室 *****************************
 */
 
#include "Serial.h"
//red 31   blue 32  yellow 33

uint8_t recvData1;   //usart1接收数据缓存
uint8_t FLAG = 0;

void OLED_COM(uint8_t a);

/*串口接收使能*/
void USART_IT_Enable(void)
{
    HAL_UART_Receive_IT(&huart1, &recvData1, 1);
}

/* 中断回调函数 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

if(huart == &huart1)
    {
        OLED_COM(recvData1);
        HAL_UART_Receive_IT(&huart1, (uint8_t *)&recvData1, 1);   //再开启接收中断
    }
}

void OLED_COM(uint8_t a)
{
    if(a == 0x31)
    {
        OLED_ShowCN_plus_pro(1,1,Red);  //接收视觉识别数据
        FLAG = 1;
    }
    else if(a == 0x32)
    {
        OLED_ShowCN_plus_pro(1,1,Blue);  //接收视觉识别数据
        FLAG = 1;
    }
    else if(a == 0x33)
    {
        OLED_ShowCN_plus_pro(1,1,Yellow);  //接收视觉识别数据
        FLAG = 1;
    }
}

