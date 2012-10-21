/*
 * =====================================================================================
 *
 *       Filename:  lcdc_s6d_backlight.c
 *
 *    Description:  LCD Backlight control Function
 *
 *        Version:  1.0
 *        Created:  2010??11??25??15??21ë¶?38ì´?
 *       Revision:  1.0
 *       Compiler:  arm-linux-gcc
 *
 *         Author:  File (System S/W Group Kernel Part), 
 *        Company:  Samsung Electronics
 *
 * =====================================================================================
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License version 2 and only version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * END
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <linux/delay.h>
#include <mach/gpio.h>
#include "lcdc_s6d_backlight.h"
#include "msm_fb.h"

static int lcd_brightness = -1;
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIOATT)
struct brt_value brt_table_ktd[] = {
	  { 0,  5 }, // Off
	  { 20, 7 }, // Dimming pulse 26(33-7) by HW
	  { MIN_BRIGHTNESS_VALUE,  6 }, // Min pulse 27(33-6) by HW
	  { 41,  7 }, 
	  { 53,  8 },  
	  { 64,  9 }, 
	  { 76,  10 }, 
	  { 87,  11 }, 
	  { 99,  12 }, 
	  { 110,  13 },
	  { 122,  14 },
	  { 133,  15 },
	  { 145,  16 }, // default pulse 17(33-16) by HW
	  { 156,  17 },
	  { 167,  18 },
	  { 178,  19 }, 
	  { 189,  20 }, 
	  { 200,  21 }, 
	  { 211,  22 }, 
	  { 222,  23 }, 
	  { 233,  24  },
	  { 244,  25  },
	  { MAX_BRIGHTNESS_VALUE,  26 }, // Max pulse 7(33-26) by HW
};
#elif defined(CONFIG_MACH_BENI)
struct brt_value brt_table_ktd[] = {
		{ 0, 	1	}, // Off
		{ 20, 	3	}, // Dimming
		{ MIN_BRIGHTNESS_VALUE, 	5	}, // Min
		{ 47, 	6	}, 
		{ 64, 	7	}, 
		{ 81, 	8	}, 	
		{ 97, 	9	}, 
		{ 113, 	10	}, 
		{ 129, 	11	}, 
		{ 145, 	12	}, // default
		{ 155, 	13	}, 
		{ 165, 	14	}, 
		{ 175, 	15	}, 
		{ 185, 	16	}, 
		{ 195, 	17	},	
		{ 205, 	18	}, 
		{ 215, 	19	}, 
		{ 225, 	20	}, 
		{ 235,  21  },
		{ 245,  22  },
		{ MAX_BRIGHTNESS_VALUE, 	23	}, // Max
};
#elif defined(CONFIG_MACH_LUCAS)
struct brt_value brt_table_ktd[] = {
		{ 0, 	1	}, // Off
		{ 15, 	2	}, // Test value 1.
		{ 20, 	3	}, // Dimming
		{ 25,	4 	}, // Test value 2.
		{ MIN_BRIGHTNESS_VALUE, 	5	}, // Min
		{ 49, 	6	}, 
		{ 65, 	7	}, 
		{ 81, 	8	}, 	
		{ 97, 	9	}, 
		{ 113, 	10	}, 
		{ 129, 	11	}, 
		{ 145, 	12	}, // default
		{ 156, 	13	}, 
		{ 167, 	14	}, 
		{ 178, 	15	}, 
		{ 189, 	16	}, 
		{ 200, 	17	},	
		{ 211, 	18	}, 
		{ 222, 	19	}, 
		{ 233, 	20	}, 
		{ 244,  21  },
		{ MAX_BRIGHTNESS_VALUE,  22  }, // Max
//		{ MAX_BRIGHTNESS_VALUE, 	23	}, // Max
};

#elif defined(CONFIG_MACH_TASS)
struct brt_value brt_table_ktd[] = {
		{ 0, 	1	}, // Off
		{ 20, 	1	}, // Dimming
		{ MIN_BRIGHTNESS_VALUE, 	1	}, // Min
		{ 38, 	2	}, 
		{ 40, 	3	}, 
		{ 48, 	4	}, 
		{ 58, 	5	}, 
		{ 68, 	6	}, 
		{ 78, 	7	}, 
		{ 90, 	8	}, 	
		{ 104, 	9	}, 
		{ 114, 	10	}, 
		{ 126, 	11	}, 
		{ 136, 	12	}, 
		{ 145, 	13	}, // default
		{ 154, 	14	}, 
		{ 162, 	15	}, 
		{ 171, 	16	}, 
		{ 179, 	17	},	
		{ 187, 	18	}, 
		{ 196, 	19	}, 
		{ 204, 	20	}, 
		{ 213,  21  },
		{ 222,  22  },
		{ 231,  23  }, 
		{ 240, 	24	}, 
		{ MAX_BRIGHTNESS_VALUE, 	25	}, // Max

};
#elif defined(CONFIG_MACH_TASSTMO) || defined(CONFIG_MACH_TASSMCT) || defined(CONFIG_MACH_TASSVTR) 
struct brt_value brt_table_ktd[] = {
		{ 0, 	1 	}, // Off
		{ 20, 	1 	}, // Dimming
		{ MIN_BRIGHTNESS_VALUE,		1 	}, // Min
		{ 38, 	2 	}, 
		{ 40, 	4	}, 
		{ 48, 	5 	}, 
		{ 58, 	7 	}, 
		{ 68, 	8 	}, 
		{ 78, 	9 	}, 
		{ 90, 	11 	},  
		{ 104,  12 	}, 
		{ 114,  14 	}, 
		{ 126,  15 	}, 
		{ 136,  16 	}, 
		{ 145,  18 	}, // default
		{ 154,  19 	}, 
		{ 162,  20 	}, 
		{ 171,  21 	}, 
		{ 179,  22 	}, 
		{ 187,  23 	}, 
		{ 196,  24 	}, 
		{ 204,  25	}, 
		{ 213,  26	},
		{ 222,  27  	},
		{ 231,  28  	}, 
		{ 240,  29 	}, 
		{ MAX_BRIGHTNESS_VALUE, 	30	}, // Max

};

#elif defined (CONFIG_MACH_GT2)
struct brt_value brt_table_ktd[] = {
	{ 0,	0	}, // Off
		{ 20, 2 }, // Dimming
		{ MIN_BRIGHTNESS_VALUE,  2 }, // Min
		{ 39, 5 }, 
		{ 56, 9 }, 
		{ 72, 12 }, 
		{ 88, 15 }, 
		{ 104, 19 }, 
		{ 120, 22 }, 
		{ 136, 26 }, 
		{ 145, 28 }, // default
		{ 154, 31 }, 
		{ 162, 33 }, 
		{ 171, 35 }, 
		{ 179, 37 }, 
		{ 187, 39 }, 
		{ 196, 41 }, 
		{ 204, 43 }, 
		{ 213, 45 },
		{ 222, 46 },
		{ 231, 48 }, 
		{ 240, 49 }, 
		{ MAX_BRIGHTNESS_VALUE,  51 }, // Max
};
#elif defined (CONFIG_MACH_FLIPBOOK)	//ADD_FB LCD
struct brt_value brt_table_ktd[] = {
		{ 0,	0	}, // Off
 		{ 20,	11	}, // Dimming
		{ MIN_BRIGHTNESS_VALUE,		11	}, // Min
		{ 39,	13	}, 
		{ 56,	15	}, 
		{ 72,	17	}, 
		{ 88,	19	}, 
		{ 104,	21	}, 
		{ 120,	23	}, 
		{ 136,	25	}, 
		{ 145,	27	}, // default
		{ 154,	28	}, 
		{ 162,	30	}, 
		{ 171,	32	}, 
		{ 179,	33	}, 
		{ 187,	35	}, 
		{ 196,	37	}, 
		{ 204,	38	}, 
		{ 213,	40	},
		{ 222,	42	},
		{ 231,	43	}, 
		{ 240,	45	}, 
		{ MAX_BRIGHTNESS_VALUE,		47	}, // Max

};
#else // Default value is based on TASS Setting
struct brt_value brt_table_ktd[] = {
		{ 0, 	1	}, // Off
		{ 20, 	3	}, // Dimming
		{ MIN_BRIGHTNESS_VALUE, 	5	}, // Min
		{ 39, 	6	}, 
		{ 56, 	7	}, 
		{ 72, 	8	}, 	
		{ 88, 	9	}, 
		{ 104, 	10	}, 
		{ 120, 	11	}, 
		{ 136, 	12	}, 
		{ 145, 	13	}, // default
		{ 154, 	14	}, 
		{ 162, 	15	}, 
		{ 171, 	16	}, 
		{ 179, 	17	},	
		{ 187, 	18	}, 
		{ 196, 	19	}, 
		{ 204, 	20	}, 
		{ 213,  21  },
		{ 222,  22  },
		{ 231,  23  }, 
		{ 240, 	24	}, 
		{ MAX_BRIGHTNESS_VALUE, 	25	}, // Max

};

#endif

#if defined(CONFIG_MACH_LUCAS)
struct brt_value brt_table_aat[] = {
		{ 255, 	9	}, // Max
		{ 244, 	10	}, 
		{ 233, 	11	}, 
		{ 222, 	12	}, 
		{ 211, 	13	}, 
		{ 200, 	14	}, 	
		{ 189, 	15	}, 
		{ 178, 	16	}, 
		{ 166, 	17	}, 
		{ 154, 	18	}, 
		{ 141, 	19	}, // Bennet Default	
		{ 127, 	20	}, 
		{ 113, 	21	}, 
		{ 99, 	22	}, 
		{ 85, 	23	},	
		{ 71, 	24	}, 
		{ 57, 	25	}, 
		{ 43, 	26	},  
		{ 30,   27  }, // Min
		{ 20, 	29	}, // Dimming
		{ 0, 	30	}, // Off
};
#else
struct brt_value brt_table_aat[] = {
		{ 255, 	9	}, // Max
		{ 240, 	10	}, 
		{ 230, 	11	}, 
		{ 220, 	12	}, 
		{ 210, 	13	}, 
		{ 200, 	14	}, 	
		{ 190, 	15	}, 
		{ 180, 	16	}, 
		{ 170, 	17	}, 
		{ 160, 	18	}, 
		{ 150, 	19	},	
		{ 141, 	20	}, // default
		{ 125, 	21	}, 
		{ 110, 	22	}, 
		{ 95, 	23	},	
		{ 80, 	24	}, 
		{ 65, 	25	}, 
		{ 50, 	26	},  
		{ 30,   27  }, // Min
		{ 20, 	29	}, // Dimming
		{ 0, 	30	}, // Off
};

#endif

#define MAX_BRT_STAGE_KTD (int)(sizeof(brt_table_ktd)/sizeof(struct brt_value))
#define MAX_BRT_STAGE_AAT (int)(sizeof(brt_table_aat)/sizeof(struct brt_value))

static DEFINE_SPINLOCK(bl_ctrl_lock);

void lcdc_s6d_set_brightness_by_aat1401(int level)
{
	int tune_level = 0;
	int i;

	spin_lock(&bl_ctrl_lock);
	if(level > 0) {
		if(level < MIN_BRIGHTNESS_VALUE) {
			tune_level = AAT_DIMMING_VALUE; //DIMMING
			} else {
				for(i = 0; i < MAX_BRT_STAGE_AAT; i++) {
					if(level <= brt_table_aat[i].level && level > brt_table_aat[i+1].level) {
						tune_level = brt_table_aat[i].tune_level;
						break;
					}
				}
			}
		} /*  BACKLIGHT is KTD model */

	if(!tune_level) {
			gpio_set_value(GPIO_BL_CTRL, 0);
			mdelay(3);
	} else {
		for(;tune_level>0;tune_level--) 
		{
			gpio_set_value(GPIO_BL_CTRL, 0);
			udelay(3);
			gpio_set_value(GPIO_BL_CTRL, 1);
			udelay(3);
		}
	}

	spin_unlock(&bl_ctrl_lock);

}

void lcdc_s6d_set_brightness_by_ktd259(int level)
{
		int pulse;
		int tune_level = 0;
		int i;
#if defined(CONFIG_MACH_GT2)
		unsigned long flags;

		spin_lock_irqsave(&bl_ctrl_lock,flags);
#else
		spin_lock(&bl_ctrl_lock);
#endif
		if(level > 0) {
			if(level < MIN_BRIGHTNESS_VALUE) {
				tune_level = KTD_DIMMING_VALUE; //DIMMING
			} else if (level == MAX_BRIGHTNESS_VALUE) {
				tune_level = brt_table_ktd[MAX_BRT_STAGE_KTD-1].tune_level;
			} else {
				for(i = 0; i < MAX_BRT_STAGE_KTD; i++) {
					if(level <= brt_table_ktd[i].level ) {
						tune_level = brt_table_ktd[i].tune_level;
						break;
					}
				}
			}
		}
		printk("Platform V:%d, Find V:%d\n",level, tune_level);

		if(tune_level <= 0) {
				gpio_set_value(GPIO_BL_CTRL, 0);
				mdelay(3);
				lcd_brightness = tune_level;
		} else {
				if(unlikely(lcd_brightness < 0)) {
						// first time
						int val = gpio_get_value(GPIO_BL_CTRL);
						if(val)
						{
								lcd_brightness = 0;
								gpio_set_value(GPIO_BL_CTRL, 0);
								mdelay(3); // guaranteed for shutdown
						}
				} 
				if(!lcd_brightness)
				{
						gpio_set_value(GPIO_BL_CTRL, 1);
						udelay(3);
						lcd_brightness = MAX_BRIGHTNESS_IN_BLU;
				}
#if (defined CONFIG_MACH_GT2) &&  (CONFIG_BOARD_REVISION >= 1)
				pulse = (MAX_BRIGHTNESS_IN_BLU- tune_level) % MAX_BRIGHTNESS_IN_BLU;
#else
				pulse = (lcd_brightness - tune_level + MAX_BRIGHTNESS_IN_BLU) % MAX_BRIGHTNESS_IN_BLU;
#endif
				
				for(;pulse>0;pulse--) 
				{
						gpio_set_value(GPIO_BL_CTRL, 0);
						udelay(3);
						gpio_set_value(GPIO_BL_CTRL, 1);
						udelay(3);
				}
		}
		lcd_brightness = tune_level;
#if defined(CONFIG_MACH_GT2)
		spin_unlock_irqrestore(&bl_ctrl_lock, flags);

#else
		spin_unlock(&bl_ctrl_lock);
#endif
}

#if defined (CONFIG_MACH_FLIPBOOK)
void lcdc_s6d_set_brightness_by_RT8565_with_BLIC_num(int level, int num_blic_en)
{
		int pulse;
		int tune_level = 0;
		int i;

		spin_lock(&bl_ctrl_lock);
		if(level > 0) {
			if(level < MIN_BRIGHTNESS_VALUE) {
				tune_level = KTD_DIMMING_VALUE; //DIMMING
			} else if (level == MAX_BRIGHTNESS_VALUE) {
				tune_level = brt_table_ktd[MAX_BRT_STAGE_KTD-1].tune_level;
			} else {
				for(i = 0; i < MAX_BRT_STAGE_KTD; i++) {
					if(level <= brt_table_ktd[i].level ) {
						tune_level = brt_table_ktd[i].tune_level;
						break;
					}
				}
			}
		}
		printk("Platform V:%d, Find V:%d\n",level, tune_level);

		if(tune_level <= 0) {
			gpio_set_value(num_blic_en, 0);
			mdelay(3);
			lcd_brightness = tune_level;
		} else {
			if(unlikely(lcd_brightness < 0)) {
				// first time
				int val = gpio_get_value(num_blic_en);
				
				if(val)
				{
					lcd_brightness = 0;
					gpio_set_value(num_blic_en, 0);
					mdelay(3); // guaranteed for shutdown
				}
			} 
			if(!lcd_brightness)
			{
				gpio_set_value(num_blic_en, 1);
				udelay(3);
				lcd_brightness = MAX_BRIGHTNESS_IN_BLU;
			}
			pulse = (lcd_brightness - tune_level + MAX_BRIGHTNESS_IN_BLU) % MAX_BRIGHTNESS_IN_BLU;

			for(;pulse>0;pulse--) 
			{
				gpio_set_value(num_blic_en, 0);
				udelay(3);
				gpio_set_value(num_blic_en, 1);
				udelay(3);
			}
		}
		lcd_brightness = tune_level;

		spin_unlock(&bl_ctrl_lock);
}
#endif
