# STM32Sample
在这个仓库中，主要是将我以前用过的开发板再拯救起来，做一些我以前没有开发过的一些事情

# 功能设计
就是接入OV7670的sensor,接入到图像，输出给TFT_LCD的屏幕,同时将接入MIC，进行录音,能够将视频与音频数据存储到SD卡中去。最后将设计子码流通过websock的方式直接传给云端做实时预览。同时还得支持MQTT协议用于将MPU6050的数据进行上传，并控制屏幕显示。使用lvgl的框架显示天气信息等。

# 修改历史
1.完成编译支持（20220427）
2.添加了STM32CUBEIDE的编译环境（20220428）

# 参考

[STM32-ILI9341-320x240-FSMC-Library](https://github.com/taburyak/STM32-ILI9341-320x240-FSMC-Library)