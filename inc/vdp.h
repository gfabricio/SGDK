/**
 *  \file vdp.h
 *  \brief VDP main
 *  \author Stephane Dallongeville
 *  \date 08/2011
 *
 * This unit provides general VDP methods :<br/>
 * - initialisation<br/>
 * - get / set register<br/>
 * - get / set resolution<br/>
 * - enable / disable VDP features<br/>
 */

#ifndef _VDP_H_
#define _VDP_H_


#include "font.h"


/**
 *  \brief
 *      VDP Data port address.
 */
#define GFX_DATA_PORT           0xC00000
/**
 *  \brief
 *      VDP Control port address.
 */
#define GFX_CTRL_PORT           0xC00004
/**
 *  \brief
 *      VDP HV counter port address.
 */
#define GFX_HVCOUNTER_PORT      0xC00008

/**
 *  \brief
 *      VDP FIFO empty flag.
 */
#define VDP_FIFOEMPTY_FLAG      (1 << 9)
/**
 *  \brief
 *      VDP FIFO full flag.
 */
#define VDP_FIFOFULL_FLAG       (1 << 8)
/**
 *  \brief
 *      VDP Vertical interrupt pending flag.
 */
#define VDP_VINTPENDING_FLAG    (1 << 7)
/**
 *  \brief
 *      VDP sprite overflow flag.
 */
#define VDP_SPROVERFLOW_FLAG    (1 << 6)
/**
 *  \brief
 *      VDP sprite collision flag.
 */
#define VDP_SPRCOLLISION_FLAG   (1 << 5)
/**
 *  \brief
 *      VDP odd frame flag.
 */
#define VDP_ODDFRAME_FLAG       (1 << 4)
/**
 *  \brief
 *      VDP Vertical blanking flag.
 */
#define VDP_VBLANK_FLAG         (1 << 3)
/**
 *  \brief
 *      VDP Horizontal blanking flag.
 */
#define VDP_HBLANK_FLAG         (1 << 2)
/**
 *  \brief
 *      VDP DMA busy flag.
 */
#define VDP_DMABUSY_FLAG        (1 << 1)
/**
 *  \brief
 *      VDP PAL mode flag.
 */
#define VDP_PALMODE_FLAG        (1 << 0)

/**
 *  \brief
 *      VDP window tilemap address in VRAM.<br/>
 *      Short version of #VDP_WINDOW definition.
 */
#define WINDOW                  window_adr
/**
 *  \deprecated
 *      Use #WINDOW instead.
 */
#define WPLAN                   WINDOW
/**
 *  \brief
 *      VDP horizontal scroll table address in VRAM.<br/>
 *      Short version of #VDP_SCROLL_H definition.
 */
#define HSCRL                   hscrl_adr
/**
 *  \brief
 *      VDP sprite list table address in VRAM.<br/>
 *      Short version of #VDP_SPRITE_LIST definition.
 */
#define SLIST                   slist_adr
/**
 *  \brief
 *      VDP background A tilemap address in VRAM.<br/>
 *      Short version of #VDP_PLAN_A definition.
 */
#define APLAN                   aplan_adr
/**
 *  \brief
 *      VDP background B tilemap address in VRAM.<br/>
 *      Short version of #VDP_PLAN_B definition.
 */
#define BPLAN                   bplan_adr

/**
 *  \brief
 *      VDP window tilemap address in VRAM.
 */
#define VDP_WINDOW              WINDOW
/**
 *  \deprecated
 *      Use #VDP_WINDOW instead.
 */
#define VDP_PLAN_WINDOW         VDP_WINDOW
/**
 *  \brief
 *      VDP horizontal scroll table address in VRAM.
 */
#define VDP_SCROLL_H            HSCRL
/**
 *  \brief
 *      VDP sprite list table address in VRAM.
 */
#define VDP_SPRITE_LIST         SLIST
/**
 *  \brief
 *      VDP background A tilemap address in VRAM.
 */
#define VDP_PLAN_A              APLAN
/**
 *  \brief
 *      VDP background B tilemap address in VRAM.
 */
#define VDP_PLAN_B              BPLAN

/**
 *  \brief
 *      Definition to set horizontal scroll to mode plan.
 */
#define HSCROLL_PLANE           0
/**
 *  \brief
 *      Definition to set horizontal scroll to mode tile.
 */
#define HSCROLL_TILE            2
/**
 *  \brief
 *      Definition to set horizontal scroll to mode line.
 */
#define HSCROLL_LINE            3

/**
 *  \brief
 *      Definition to set vertical scroll to mode plan.
 */
#define VSCROLL_PLANE           0
/**
 *  \brief
 *      Definition to set vertical scroll to mode 2 tile.
 */
#define VSCROLL_2TILE           1

/**
 *  \brief
 *      Interlaced scanning mode disabled.<br/>
 *      That is the default mode for the VDP.
 */
#define INTERLACED_NONE         0
/**
 *  \brief
 *      Interlaced Scanning Mode 1 - 8x8 dots per cell (normal vertical resolution)<br/>
 *      In Interlaced Mode 1, the same pattern will be displayed on the adjacent lines of even and odd numbered fields.
 */
#define INTERLACED_MODE1        1
/**
 *  \brief
 *      Interlaced Scanning Mode 2 - 8x16 dots per cell (double vertical resolution)<br/>
 *      In Interlaced Mode 2, different patterns can be displayed on the adjacent lines of even and odd numbered fields.
 */
#define INTERLACED_MODE2        2

/**
 *  \brief
 *      Size of a single tile in byte.
 */
#define TILE_SIZE               32
#define TILE_INDEX_MASK         (0xFFFF / TILE_SIZE)

/**
 *  \brief
 *      Space in byte for tile in VRAM (tile space ends where window tilemap starts)
 */
#define TILE_SPACE              WINDOW

/**
 *  \brief
 *      Maximum number of tile in VRAM (related to TILE_SPACE).
 */
#define TILE_MAXNUM             (TILE_SPACE / TILE_SIZE)
/**
 *  \brief
 *      Maximum tile index in VRAM (related to TILE_MAXNUM).
 */
#define TILE_MAXINDEX           (TILE_MAXNUM - 1)
/**
 *  \brief
 *      System base tile index in VRAM.
 */
#define TILE_SYSTEMINDEX        0x0000
/**
 *  \brief
 *      Number of system tile.
 */
#define TILE_SYSTEMLENGTH       0x10
/**
 *  \deprecated Use TILE_SYSTEMLENGTH instead.
 */
#define TILE_SYSTEMLENGHT       TILE_SYSTEMLENGTH
/**
 *  \brief
 *      User base tile index.
 */
#define TILE_USERINDEX          (TILE_SYSTEMINDEX + TILE_SYSTEMLENGTH)
/**
 *  \brief
 *      Font base tile index.
 */
#define TILE_FONTINDEX          (TILE_MAXNUM - FONT_LEN)
/**
 *  \brief
 *      Number of available user tile.
 */
#define TILE_USERLENGTH         (TILE_FONTINDEX - TILE_USERINDEX)
/**
 *  \deprecated Use TILE_USERLENGTH instead.
 */
#define TILE_USERLENGHT         TILE_USERLENGTH
/**
 *  \brief
 *      Maximum tile index in VRAM for user.
 */
#define TILE_USERMAXINDEX       (TILE_USERINDEX + TILE_USERLENGTH - 1)
/**
 *  \brief
 *      System tile address in VRAM.
 */
#define TILE_SYSTEM             (TILE_SYSTEMINDEX * TILE_SIZE)
/**
 *  \brief
 *      User tile address in VRAM.
 */
#define TILE_USER               (TILE_USERINDEX * TILE_SIZE)
/**
 *  \brief
 *      Font tile address in VRAM.
 */
#define TILE_FONT               (TILE_FONTINDEX * TILE_SIZE)

/**
 *  \brief
 *      Palette 0
 */
#define PAL0                    0
/**
 *  \brief
 *      Palette 1
 */
#define PAL1                    1
/**
 *  \brief
 *      Palette 2
 */
#define PAL2                    2
/**
 *  \brief
 *      Palette 3
 */
#define PAL3                    3

/**
 *  \brief
 *      Set VDP command to read specified VRAM address.
 */
#define GFX_READ_VRAM_ADDR(adr)     ((0x0000 + ((adr) & 0x3FFF)) << 16) + (((adr) >> 14) | 0x00)
/**
 *  \brief
 *      Set VDP command to read specified CRAM address.
 */
#define GFX_READ_CRAM_ADDR(adr)     ((0x0000 + ((adr) & 0x3FFF)) << 16) + (((adr) >> 14) | 0x20)
/**
 *  \brief
 *      Set VDP command to read specified VSRAM address.
 */
#define GFX_READ_VSRAM_ADDR(adr)    ((0x0000 + ((adr) & 0x3FFF)) << 16) + (((adr) >> 14) | 0x10)

/**
 *  \brief
 *      Set VDP command to write at specified VRAM address.
 */
#define GFX_WRITE_VRAM_ADDR(adr)    ((0x4000 + ((adr) & 0x3FFF)) << 16) + (((adr) >> 14) | 0x00)
/**
 *  \brief
 *      Set VDP command to write at specified CRAM address.
 */
#define GFX_WRITE_CRAM_ADDR(adr)    ((0xC000 + ((adr) & 0x3FFF)) << 16) + (((adr) >> 14) | 0x00)
/**
 *  \brief
 *      Set VDP command to write at specified VSRAM address.
 */
#define GFX_WRITE_VSRAM_ADDR(adr)   ((0x4000 + ((adr) & 0x3FFF)) << 16) + (((adr) >> 14) | 0x10)

/**
 *  \brief
 *      Set VDP command to issue a DMA transfert to specified VRAM address.
 */
#define GFX_DMA_VRAM_ADDR(adr)      ((0x4000 + ((adr) & 0x3FFF)) << 16) + (((adr) >> 14) | 0x80)
/**
 *  \brief
 *      Set VDP command to issue a DMA transfert to specified CRAM address.
 */
#define GFX_DMA_CRAM_ADDR(adr)      ((0xC000 + ((adr) & 0x3FFF)) << 16) + (((adr) >> 14) | 0x80)
/**
 *  \brief
 *      Set VDP command to issue a DMA transfert to specified VSRAM address.
 */
#define GFX_DMA_VSRAM_ADDR(adr)     ((0x4000 + ((adr) & 0x3FFF)) << 16) + (((adr) >> 14) | 0x90)

/**
 *  \brief
 *      Set VDP command to issue a DMA VRAM copy to specified VRAM address.
 */
#define GFX_DMA_VRAMCOPY_ADDR(adr)  ((0x4000 + ((adr) & 0x3FFF)) << 16) + (((adr) >> 14) | 0xC0)

/**
 *  \brief
 *      Helper to write in vertical scroll table (same as GFX_WRITE_VSRAM_ADDR).
 */
#define GFX_VERT_SCROLL(adr)        GFX_WRITE_VSRAM_ADDR(adr)
/**
 *  \brief
 *      Helper to write in horizontal scroll table (same as GFX_WRITE_VRAM_ADDR(VDP_SCROLL_H + adr)).
 */
#define GFX_HORZ_SCROLL(adr)        GFX_WRITE_VRAM_ADDR(VDP_SCROLL_H + (adr))

/**
 *  \brief
 *      Tests VDP status against specified flag (see VDP_XXX_FLAG).
 */
#define GET_VDPSTATUS(flag)         ((*(vu16*)(GFX_CTRL_PORT)) & (flag))
/**
 *  \brief
 *      Tests if current system is a PAL system (50 Hz).
 */
#define IS_PALSYSTEM                GET_VDPSTATUS(VDP_PALMODE_FLAG)

/**
 *  \brief
 *      Returns HV counter.
 */
#define GET_HVCOUNTER               (*(vu16*)(GFX_HVCOUNTER_PORT))
/**
 *  \brief
 *      Returns Horizontal counter.
 */
#define GET_HCOUNTER                (GET_HVCOUNTER & 0xFF)
/**
 *  \brief
 *      Returns Vertical counter.
 */
#define GET_VCOUNTER                (GET_HVCOUNTER >> 8)


/**
 *  \brief
 *      Type used to define on which plan to work (only used in some methods).<br/>
 *      You should use the #PLAN_A and #PLAN_B constants.
 *
 *   \see PLAN_A
 *   \see PLAN_B
 */
typedef struct
{
    u16 v;
} VDPPlan;

/**
 *  \brief
 *      Constant to define VDP plan A
 */
extern const VDPPlan PLAN_B;
/**
 *  \brief
 *      Constant to define VDP plan A
 */
extern const VDPPlan PLAN_A;


// used by define
extern u16 window_adr;
extern u16 aplan_adr;
extern u16 bplan_adr;
extern u16 hscrl_adr;
extern u16 slist_adr;

/**
 *  \brief
 *      Current screen width (horizontale resolution)
 */
extern u16 screenWidth;
/**
 *  \brief
 *      Current screen height (verticale resolution)
 */
extern u16 screenHeight;


/**
 *  \brief
 *      Initialize the VDP sub system.
 *
 * Reset VDP registers, clear VRAM, set defaults grey, red, green & blue palette.
 */
void VDP_init();

/**
 *  \brief
 *      Get VDP register value.
 *
 *  \param reg
 *      Register number we want to retrieve value.
 *  \return specified register value.
 */
u8   VDP_getReg(u16 reg);
/**
 *  \brief
 *      Set VDP register value.
 *
 *  \param reg
 *      Register number we want to set value.
 *  \param value
 *      value to set.
 */
void VDP_setReg(u16 reg, u8 value);

/**
 *  \brief
 *      Returns VDP enable state.
 */
u8   VDP_getEnable();
/**
 *  \brief
 *      Set VDP enable state.
 *
 *  You can temporary disable VDP to speed up VDP memory transfert.
 */
void VDP_setEnable(u8 value);

/**
 *  \brief
 *      Returns number of total scanline.
 *
 *  312 for PAL system and 262 for NTSC system.
 */
u16  VDP_getScanlineNumber();
/**
 *  \brief
 *      Returns vertical screen resolution.
 *
 *  Always returns 224 on NTSC system as they only support this mode.<br>
 *  PAL system supports 240 pixels mode.
 */
u16  VDP_getScreenHeight();
/**
 *  \brief
 *      Set vertical resolution to 224 pixels.
 *
 *  This is the only accepted mode for NTSC system.
 */
void VDP_setScreenHeight224();
/**
 *  \brief
 *      Set vertical resolution to 240 pixels.
 *
 *  Only work on PAL system.
 */
void VDP_setScreenHeight240();
/**
 *  \brief
 *      Returns horizontal screen resolution.
 *
 *  Returns 320 or 256 depending current horizontal resolution mode.
 */
u16  VDP_getScreenWidth();
/**
 *  \brief
 *      Set horizontal resolution to 256 pixels.
 */
void VDP_setScreenWidth256();
/**
 *  \brief
 *      Set horizontal resolution to 320 pixels.
 */
void VDP_setScreenWidth320();

/**
 *  \brief
 *      Returns background plan width (in tile).
 *
 *  Possible values are: 32, 64, 128
 */
u16  VDP_getPlanWidth();
/**
 *  \brief
 *      Returns background plan height (in tile).
 *
 *  Possible values are: 32, 64, 128
 */
u16  VDP_getPlanHeight();
/**
 *  \brief
 *      Set background plan size (in tile).
 *
 *  \param w
 *      width in tile.<br/>
 *      Possible values are 32, 64 or 128.
 *  \param h
 *      height in tile.<br/>
 *      Possible values are 32, 64 or 128.
 */
void VDP_setPlanSize(u16 w, u16 h);

/**
 *  \brief
 *      Returns plan horizontal scrolling mode.
 *
 *  Possible values are: HSCROLL_PLANE, HSCROLL_TILE, HSCROLL_LINE
 *
 *  \see VDP_setScrollingMode for more informations about scrolling mode.
 */
u8 VDP_getHorizontalScrollingMode();
/**
 *  \brief
 *      Returns plan vertical scrolling mode.
 *
 *  Possible values are: VSCROLL_PLANE, VSCROLL_2TILE
 *
 *  \see VDP_setScrollingMode for more informations about scrolling mode.
 */
u8 VDP_getVerticalScrollingMode();
/**
 *  \brief
 *      Set plan scrolling mode.
 *
 *  \param hscroll
 *      Horizontal scrolling mode :<br>
 *      <b>HSCROLL_PLANE</b> = Scroll offset is applied to the whole plan.<br/>
 *      <b>HSCROLL_TILE</b> = Scroll offset is applied on a tile basis granularity (8 pixels bloc).<br/>
 *      <b>HSCROLL_LINE</b> = Scroll offset is applied on a line basis granularity (1 pixel).<br/>
 *  \param vscroll
 *      Vertical scrolling mode :<br>
 *      <b>VSCROLL_PLANE</b> = Scroll offset is applied to the whole plan.<br/>
 *      <b>VSCROLL_2TILE</b> = Scroll offset is applied on 2 tiles basis granularity (16 pixels bloc).<br/>
 *
 *  \see VDP_setHorizontalScroll() to set horizontal scroll offset in mode plane.<br/>
 *  \see VDP_setHorizontalScrollTile() to set horizontal scroll offset(s) in mode tile.<br/>
 *  \see VDP_setHorizontalScrollLine() to set horizontal scroll offset(s) in mode line.<br/>
 *  \see VDP_setVerticalScroll() to set vertical scroll offset in mode plane.<br/>
 *  \see VDP_setVerticalScrollTile() to set vertical scroll offset(s) in mode 2-tile.<br/>
 */
void VDP_setScrollingMode(u16 hscroll, u16 vscroll);


/**
 *  \brief
 *      Returns the background color index.
 */
u8 VDP_getBackgroundColor();
/**
 *  \brief
 *      Set the background color index.
 */
void VDP_setBackgroundColor(u8 value);

/**
 *  \brief
 *      Returns auto increment register value.
 */
u8   VDP_getAutoInc();
/**
 *  \brief
 *      Set auto increment register value.
 */
void VDP_setAutoInc(u8 value);

/**
 *  \brief
 *      Enable or Disable Horizontal interrupt.
 *
 *  \see VDP_setHIntCounter()
 */
void VDP_setHInterrupt(u8 value);
/**
 *  \brief
 *      Enable or Disable Hilight / Shadow effect.
 */
void VDP_setHilightShadow(u8 value);

/**
 *  \brief
 *      Get Horizontal interrupt counter value.
 */
u8   VDP_getHIntCounter();
/**
 *  \brief
 *      Set Horizontal interrupt counter value.
 *
 *  When Horizontal interrupt is enabled, setting 5 here means that H int will occurs each (5+1) scanline.<br/>
 *  Set value 0 to get H int at each scanline.
 */
void VDP_setHIntCounter(u8 value);

/**
 *  \brief
 *      Get VRAM address (location) of Plan A tilemap.
 */
u16 VDP_getAPlanAddress();
/**
 *  \brief
 *      Get VRAM address (location) of Plan B tilemap.
 */
u16 VDP_getBPlanAddress();
/**
 *  \brief
 *      Get VRAM address (location) of Window tilemap.
 */
u16 VDP_getWindowAddress();
/**
 *  \deprecated
 *      Use #VDP_getWindowAddress(..) instead.
 */
u16 VDP_getWindowPlanAddress();
/**
 *  \brief
 *      Get VRAM address (location) of Sprite list.
 */
u16 VDP_getSpriteListAddress();
/**
 *  \brief
 *      Get VRAM address (location) of H SCroll table.
 */
u16 VDP_getHScrollTableAddress();

/**
 *  \brief
 *      Set VRAM address (location) of Plan A tilemap.
 *      <br/>
 *      WARNING: the window tilemap should always be the first object attribute in VRAM:<br/>
 *      | system tiles<br/>
 *      | user tiles<br/>
 *      | window plan<br/>
 *      v others (plan a, plan b, ...)<br/>
 *      <br/>
 *      The window tilemap address is used internally to calculated how much space is available for tiles.
 *
 *  EX:<br/>
 *      VDP_setAPlanAddress(0xC000)<br/>
 *      Will set the Plan A to at address 0xC000 in VRAM.
 */
void VDP_setAPlanAddress(u16 value);
/**
 *  \brief
 *      Set VRAM address (location) of Window tilemap.<br/>
 *      <br/>
 *      WARNING: the window tilemap should always be the first object attribute in VRAM:<br/>
 *      | system tiles<br/>
 *      | user tiles<br/>
 *      | window plan<br/>
 *      v others (plan a, plan b, ...)<br/>
 *      <br/>
 *      The window tilemap address is used internally to calculated how much space is available for tiles.
 *
 *  EX:<br/>
 *      VDP_setWindowAddress(0xA000)<br/>
 *      Will set the Window tilemap to at address 0xA000 in VRAM.
 */
void VDP_setWindowAddress(u16 value);
/**
 *  \deprecated
 *      Use #VDP_setWindowAddress(..) instead.
 */
void VDP_setWindowPlanAddress(u16 value);
/**
 *  \brief
 *      Set VRAM address (location) of Plan B tilemap.<br/>
 *      <br/>
 *      WARNING: the window tilemap should always be the first object attribute in VRAM:<br/>
 *      | system tiles<br/>
 *      | user tiles<br/>
 *      | window plan<br/>
 *      v others (plan a, plan b, ...)<br/>
 *      <br/>
 *      The window tilemap address is used internally to calculated how much space is available for tiles.
 *
 *  EX:<br/>
 *      VDP_setBPlanAddress(0xE000)<br/>
 *      Will set the Plan B to at address 0xE000 in VRAM.
 */
void VDP_setBPlanAddress(u16 value);
/**
 *  \brief
 *      Set VRAM address (location) of Sprite list.<br/>
 *      <br/>
 *      WARNING: the window tilemap should always be the first object attribute in VRAM:<br/>
 *      | system tiles<br/>
 *      | user tiles<br/>
 *      | window plan<br/>
 *      v others (plan a, plan b, ...)<br/>
 *      <br/>
 *      The window tilemap address is used internally to calculated how much space is available for tiles.
 *
 *  EX:<br/>
 *      VDP_setSpriteListAddress(0xB800)<br/>
 *      Will set the Sprite list to at address 0xB800 in VRAM.
 */
void VDP_setSpriteListAddress(u16 value);
/**
 *  \brief
 *      Set VRAM address (location) of H Scroll table.<br/>
 *      <br/>
 *      WARNING: the window tilemap should always be the first object attribute in VRAM:<br/>
 *      | system tiles<br/>
 *      | user tiles<br/>
 *      | window plan<br/>
 *      v others (plan a, plan b, ...)<br/>
 *      <br/>
 *      The the window tilemap address is used internally to calculated how much space is available for tiles.
 *
 *  EX:<br/>
 *      VDP_setHScrollTableAddress(0xB400)<br/>
 *      Will set the HScroll table to at address 0xB400 in VRAM.
 */
void VDP_setHScrollTableAddress(u16 value);

/**
 *  \brief
 *      Sets the scan mode of the display.
 *
 *  \param mode
 *      Accepted values : #INTERLACED_NONE, #INTERLACED_MODE1, #INTERLACED_MODE2
 *
 * This function changes the scanning mode on the next display blanking period.<br/>
 * In Interlaced Mode 1, the same pattern will be displayed on the adjacent lines of even and odd numbered fields.<br/>
 * In Interlaced Mode 2, different patterns can be displayed on the adjacent lines of even and odd numbered fields.<br/>
 * The number of cells on the screen stays the same regardless of which scanning mode is active.
 */
void VDP_setScanMode(u16 mode);

/**
 *  \brief
 *      Wait for DMA operation to complete.
 */
void VDP_waitDMACompletion();
/**
 *  \brief
 *      Wait for VDP FIFO to be empty.
 */
void VDP_waitFIFOEmpty();

/**
 *  \brief
 *      Wait for Vertical Synchro.
 *
 *  The method actually wait for the next start of Vertical blanking.
 */
void VDP_waitVSync();

/**
 *  \brief
 *      Reset background plan and palette.
 *
 *  Clear background plans and reset palette to grey / red / green / blue.
 */
void VDP_resetScreen();


/**
 *  \brief
 *      Display number of Frame Per Second.
 *
 *  \param float_display
 *      Display as float number.
 *
 * This function actually display the number of time it was called in the last second.<br>
 * i.e: for benchmarking you should call this method only once per frame update.
 */
void VDP_showFPS(u16 float_display);


#endif // _VDP_H_
