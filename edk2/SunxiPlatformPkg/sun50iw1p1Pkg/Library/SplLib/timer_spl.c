/** @file
*
*  Copyright (c) 2007-2014, Allwinner Technology Co., Ltd. All rights reserved.
*  http://www.allwinnertech.com
*
*  tangmanliang <tangmanliang@allwinnertech.com>
*  
*  This program and the accompanying materials                          
*  are licensed and made available under the terms and conditions of the BSD License         
*  which accompanies this distribution.  The full text of the license may be found at        
*  http://opensource.org/licenses/bsd-license.php                                            
*
*  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
*  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             
*
**/


#include <boot0_include/boot0_helper.h>
#include <Sun50iW1P1/timer.h>
#include <Sun50iW1P1/ccmu.h>

int timer_init(void)
{
  struct sunxi_timer_reg *timer_reg = (struct sunxi_timer_reg *)SUNXI_TIMER_BASE;

  writel(readl(CCMU_AVS_CLK_REG) | (1U << 31), CCMU_AVS_CLK_REG);

  timer_reg->tirqen  = 0;
  timer_reg->tirqsta |= 0x03f;
  /* start avs as counter */
  //ccm_reg->avs_clk_cfg |= (1 << 31);
  timer_reg->avs.ctl  = 3; //enable avs cnt0 and cnt1,source is 24M
  /* div cnt0 12000 to 2000hz, high 32 bit means 1000hz.*/
  /* div cnt 1 12 to 2000000hz ,high 32 bit means 1000000hz */
  timer_reg->avs.div   = 0xc2ee0;
  timer_reg->avs.cnt0  = 0;
  timer_reg->avs.cnt1  = 0;

  return 0;
}
/*
************************************************************************************************************
*
*                                             function
*
*    函数名称：
*
*    参数列表：
*
*    返回值  ：
*
*    说明    ：
*
*
************************************************************************************************************
*/
void __msdelay(unsigned long ms)
{
  u32 t1, t2;
  struct sunxi_timer_reg *timer_reg = (struct sunxi_timer_reg *)SUNXI_TIMER_BASE;

  t1 = timer_reg->avs.cnt0;
  t2 = t1 + ms;
  do
  {
    t1 = timer_reg->avs.cnt0;
  }
  while(t2 >= t1);

  return ;
}
/*
************************************************************************************************************
*
*                                             function
*
*    函数名称：
*
*    参数列表：
*
*    返回值  ：
*
*    说明    ：
*
*
************************************************************************************************************
*/
void __usdelay(unsigned long us)
{
  u32 t1, t2;
  struct sunxi_timer_reg *timer_reg = (struct sunxi_timer_reg *)SUNXI_TIMER_BASE;

  t1 = timer_reg->avs.cnt1;
  t2 = t1 + us;
  do
  {
    t1 = timer_reg->avs.cnt1;
  }
  while(t2 >= t1);

  return ;
}
/*
************************************************************************************************************
*
*                                             function
*
*    函数名称：
*
*    参数列表：
*
*    返回值  ：
*
*    说明    ：
*
*
************************************************************************************************************
*/
void timer_exit(void)
{
  ;
}

