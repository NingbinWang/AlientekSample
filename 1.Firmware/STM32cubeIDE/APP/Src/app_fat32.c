#include "main.h"
#include "app_main.h"
#include "fatfs.h"
#include "stdio.h"
#include "sdio.h"

void SdioTest(void)
{
  printf("Micro SD Card Test...\r\n");
  /* 检测SD卡是否正常（处于数据传输模式的传输状态） */
  if(HAL_SD_GetCardState(&hsd) == HAL_SD_CARD_TRANSFER)
  {
      printf("Initialize SD card successfully!\r\n");
      // 打印SD卡基本信息
      printf(" SD card information! \r\n");
      printf(" CardCapacity  : %llu \r\n", (unsigned long long)hsd.SdCard.BlockSize * hsd.SdCard.BlockNbr);// 显示容量
     // printf(" CardBlockSize : %d \r\n", hsd.SdCard.BlockSize);   // 块大小
     // printf(" LogBlockNbr   : %d \r\n", hsd.SdCard.LogBlockNbr);	// 逻辑块数量
     // printf(" LogBlockSize  : %d \r\n", hsd.SdCard.LogBlockSize);// 逻辑块大小
     // printf(" RCA           : %d \r\n", hsd.SdCard.RelCardAdd);  // 卡相对地址
     // printf(" CardType      : %d \r\n", hsd.SdCard.CardType);    // 卡类型
      // 读取并打印SD卡的CID信息
      HAL_SD_CardCIDTypeDef sdcard_cid;
      HAL_SD_GetCardCID(&hsd,&sdcard_cid);
      printf(" ManufacturerID: %d \r\n",sdcard_cid.ManufacturerID);
  }
  else
  {
      printf("SD card init fail!\r\n" );
  }
}

void FatFsTest(void)
{
  FIL file;// 文件对象
  FRESULT f_res;// 文件操作结果
  UINT fnum;// 文件成功读写数量
  BYTE ReadBuffer[1024]={0};        /* 读缓冲区 */
  BYTE WriteBuffer[]= "test write data\n";
  //BYTE work[512];
    //在SD卡挂载文件系统，文件系统挂载时会对SD卡初始化
  f_res = f_mount(&SDFatFS,(TCHAR const*)SDPath,0);
  // 格式化测试
  // 如果没有文件系统就格式化创建创建文件系统
  if(f_res == FR_NO_FILESYSTEM)
  {
     printf("sd card have no file system  now start format sd card \r\n");
     // 格式化
     f_res=f_mkfs((TCHAR const*)SDPath,0,0);
     if(f_res == FR_OK)
      {
        printf("SD card have been formated\r\n");
        // 格式化后，先取消挂载
        f_res = f_mount(NULL,(TCHAR const*)SDPath,0);
        // 重新挂载
        f_res = f_mount(&SDFatFS,(TCHAR const*)SDPath,0);
      }
      else
      {
        printf("no file system format error %d\r\n",f_res);
        return;
      }
   }
   else if(f_res!=FR_OK)
   {
      printf("SDcard mount fat32 fail.f_res =  %d now format\r\n",f_res);
      f_res=f_mkfs((TCHAR const*)SDPath,0,0);
      if(f_res == FR_OK)
      {
          printf("SD card have been formated\r\n");
             // 格式化后，先取消挂载
          f_res = f_mount(NULL,(TCHAR const*)SDPath,0);
             // 重新挂载
          f_res = f_mount(&SDFatFS,(TCHAR const*)SDPath,0);
      }else{
	  printf("format error %d\r\n",f_res);
	  return;
      }
   }
   else
   {
      printf("mount filesystem ok now start test write and read test \r\n");
   }

    /*----------------------- 文件系统测试：写测试 -----------------------------*/
    /* 打开文件，如果文件不存在则创建它 */
    f_res = f_open(&file, "FatFstest.txt",FA_CREATE_ALWAYS | FA_WRITE );
    if ( f_res == FR_OK )
    {
      printf("open or crate fatfstest.txt error\r\n");
      /* 将指定存储区内容写入到文件内 */
      f_res=f_write(&file,WriteBuffer,sizeof(WriteBuffer),&fnum);
      if(f_res==FR_OK)
      {
        printf("write ok write byte=%d\r\n",fnum);
        printf("data:\n%s\n",WriteBuffer);
      }
      else
      {
        printf("write error(%d)\r\n",f_res);
      }
      /* 不再读写，关闭文件 */
      f_close(&file);
    }
    else
    {
      printf("open or creat error %d\r\n",f_res);
    }

    /*------------------- 文件系统测试：读测试 ------------------------------------*/
    f_res = f_open(&file, "FatFstest.txt", FA_OPEN_EXISTING | FA_READ);
    if(f_res == FR_OK)
    {
      printf("open file ok\r\n");
      f_res = f_read(&file, ReadBuffer, sizeof(ReadBuffer), &fnum);
      if(f_res==FR_OK)
      {
        printf("read ok byte=%d\r\n",fnum);
        printf("data:%s \r\n", ReadBuffer);
      }
      else
      {
        printf("read file error(%d)\r\n",f_res);
      }
    }
    else
    {
      printf("open file error %d。\r\n",f_res);
    }
    /* 不再读写，关闭文件 */
    f_close(&file);
    /* 不再使用，取消挂载 */
    f_res = f_mount(NULL,(TCHAR const*)SDPath,0);
  /* 注销一个FatFS设备：SD卡 */
  //FATFS_UnLinkDriver(SDPath);

}
