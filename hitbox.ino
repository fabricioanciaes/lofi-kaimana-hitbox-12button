//  example.ino
//
//  Copyright 2013 Paradise Arcade Shop, ParadiseArcadeShop.com  
//  All rights reserved.  Use is subject to license terms.
//
//  Code is provided for entertainment purposes and use with the Kaimana controller.
//  Code may be copied, modified, resused with this Copyright notice.
//  No commercial use without written permission from Paradise Arcade Shop.
//
//  Paradise Arcade Shop Kaimana LED Driver Board
//  Initial Release October 15, 2013
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//
//  Kaimana example based on original source released by ParadiseArcadeShop.com October 15, 2013
//
//  Created:  October 24, 2013    zonbipanda // gmail.com  -- Arduino 1.0.5 Support
//  Revised:  October 29, 2013    zonbipanda // gmail.com
//  Revised:  April   11, 2015    zonbipanda // gmail.com  -- Arduino 1.6.3 Support
//


#define __PROG_TYPES_COMPAT__
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "kaimana.h"
#include "kaimana_custom.h"
#include "animations.h"
#include "settings.h"


// local function declarations
int  pollSwitches(void);
void showStartup(void);
void setLEDRandomColor(int index);
int tourneypollSwitches(void);
int holdTimeout = 0;
boolean tournamentMode = false;
// ParadiseArcadeShop.com Kaimana features initialzied when Kaimana class instantiated
Kaimana kaimana;


// the setup routine runs first and once each time power is applied to the Kaimana board
void setup() 
{                
  // light up all leds at boot to demonstrate everything is functional
	showStartup();
}



// the loop routine repeats indefinitely and executes immediately following the setup() function
void loop() 
{
  unsigned long  ulTimeout;
  
    
  // initialize timeout value to now + some seconds
  ulTimeout = millis() + ( (unsigned long)IDLE_TIMEOUT_SECONDS * 1000 );
  

  // infinite loop of read switches, update LEDs and idle animation when necessary
while(true)
  {
      if (tournamentMode != true)
      {
        // active -- poll switches and update leds
        if( pollSwitches() != 0 )
        {
          // some switches were active so reset idle timeout to now + some seconds
          ulTimeout = millis() + ( (unsigned long)IDLE_TIMEOUT_SECONDS * 1000 );
        }
      }
      else
      {
        if( tourneypollSwitches() != 0 )
        {
          // some switches were active so reset idle timeout to now + some seconds
          ulTimeout = millis() + ( (unsigned long)IDLE_TIMEOUT_SECONDS * 1000 );
        }
      }    
  } 
}


// ==============================================================
//
//  local functions start here
//
// ==============================================================


// light up all leds at boot to demonstrate everything is functional
//
void showStartup(void)
{
  kaimana.setALL( BLACK );
  delay( BOOT_COLOR_DELAY );
  kaimana.setALL( PURPLE );
  delay( BOOT_COLOR_DELAY );
  kaimana.setALL( BLACK );
  delay( BOOT_COLOR_DELAY );
  kaimana.setALL( PURPLE );
  delay( BOOT_COLOR_DELAY );
  kaimana.setALL( BLACK );
  delay( BOOT_COLOR_DELAY );
  kaimana.setALL( PURPLE );
  delay( BOOT_COLOR_DELAY );

  kaimana.setALL( BLACK );
  delay( BOOT_COMPLETE_DELAY );
}

void tourneyModeActivate(void)
{
	
	kaimana.setALL(RED);
	kaimana.updateALL();
	delay( T_DELAY );
	
	kaimana.setLED(LED_K4, BLACK);
	kaimana.setLED(LED_P4, BLACK);
	kaimana.updateALL();
	delay( T_DELAY );	
	
	kaimana.setLED(LED_K3, BLACK);
	kaimana.setLED(LED_P3, BLACK);
	kaimana.setLED(LED_START, BLACK);
	kaimana.updateALL();
	delay( T_DELAY );
	
	kaimana.setLED(LED_K2, BLACK);
	kaimana.setLED(LED_P2, BLACK);
	kaimana.setLED(LED_HOME, BLACK);
	kaimana.updateALL();
	delay( T_DELAY );
	
	kaimana.setLED(LED_K1, BLACK);
	kaimana.setLED(LED_P1, BLACK);
	kaimana.setLED(LED_SELECT, BLACK);
	kaimana.updateALL();
	delay( T_DELAY );

  kaimana.setLED(LED_UP, BLACK);
	kaimana.setLED(LED_UP, BLACK);
	kaimana.updateALL();
	delay( T_DELAY );	

  kaimana.setLED(LED_RIGHT, BLACK);
	kaimana.setLED(LED_RIGHT, BLACK);
	kaimana.updateALL();
	delay( T_DELAY );	

  kaimana.setLED(LED_DOWN, BLACK);
	kaimana.setLED(LED_DOWN, BLACK);
	kaimana.updateALL();
	delay( T_DELAY );	

  kaimana.setLED(LED_LEFT, BLACK);
	kaimana.setLED(LED_LEFT, BLACK);
	kaimana.updateALL();
	delay( T_DELAY );
 
  kaimana.setALL(BLACK);
  kaimana.updateALL();
  delay( T_DELAY );
}

void tourneyModeDeactivate(void)
{
	kaimana.setALL(BLACK);
	kaimana.updateALL();
	delay( T_DELAY );
	
  kaimana.setLED(LED_LEFT, RED );
	kaimana.updateALL();
	delay( T_DELAY );	

  kaimana.setLED(LED_DOWN, RED );
	kaimana.updateALL();
	delay( T_DELAY );	

  kaimana.setLED(LED_RIGHT, RED );
	kaimana.updateALL();
	delay( T_DELAY );	

  kaimana.setLED(LED_UP, RED );
	kaimana.updateALL();
	delay( T_DELAY );	

	kaimana.setLED(LED_K1, RED);
	kaimana.setLED(LED_P1, RED);
	kaimana.setLED(LED_SELECT, RED);
	kaimana.updateALL();
	delay( T_DELAY );
		
	kaimana.setLED(LED_K2, RED);
	kaimana.setLED(LED_P2, RED);
	kaimana.setLED(LED_HOME, RED);
	kaimana.updateALL();
	delay( T_DELAY );
	
	kaimana.setLED(LED_K3, RED);
	kaimana.setLED(LED_P3, RED);
	kaimana.setLED(LED_START, RED);
	kaimana.updateALL();
	delay( T_DELAY );
	
	kaimana.setLED(LED_K4, RED );
	kaimana.setLED(LED_P4, RED);
	kaimana.updateALL();
	delay( T_DELAY );	

	kaimana.setALL(BLACK);
	kaimana.updateALL();
	delay( T_DELAY );
	
	kaimana.setALL(RED);
	kaimana.updateALL();
	delay( T_DELAY );
	
	kaimana.setALL(BLACK);
	kaimana.updateALL();
	delay( T_DELAY );

  kaimana.setALL(BLACK);
  kaimana.updateALL();
  delay( T_DELAY );
}

int pollSwitches(void)
{
  static int  iLED[LED_COUNT];
  static int  iActiveSwitchCount;
  static int  i;  
  static int  j;  
  static int  firsttime;
  static uint16_t  joystickDirection;
  static uint16_t  switchActivity;

  // reset LED status
  if (firsttime == 1)
  {
    for(i=0;i<LED_COUNT;++i)
    {
      iLED[i] = false;
      firsttime = 0;
    }
  }

  // read arduino pins and save results in the mapped LED if button is pressed (pin grounded)

  // complex special case for joystick but it's worth the effort
  // clear results for switch activity
  switchActivity = ATTACK_NONE;

  // SOCD LEFT+RIGHT
  
  if(!digitalRead(PIN_LEFT) && !digitalRead(PIN_RIGHT))
  {
      switchActivity |= ATTACK_RIGHT + ATTACK_LEFT;
      if(iLED[LED_RIGHT] && iLED[LED_LEFT] == true)
      {
        iLED[LED_RIGHT] = false;
        iLED[LED_LEFT] = false;
      } else {
        kaimana.setLED( LED_RIGHT, _ON_SOCD_PRESS_COLOR );
        kaimana.setLED( LED_LEFT, _ON_SOCD_PRESS_COLOR );
        iLED[LED_RIGHT] = true;
        iLED[LED_LEFT] = true;
      }
  }
  else
  {
   if(!digitalRead(PIN_RIGHT))
  {
    switchActivity |= ATTACK_RIGHT;
      // switch is active
      if(iLED[LED_RIGHT] == true)
      {
        kaimana.setLED( LED_RIGHT, _ON_PRESS_BTN_COLOR );
        iLED[LED_RIGHT] = true;
      }
      else
      {
        // select new color when switch is first activated
        kaimana.setLED( LED_RIGHT, _ON_PRESS_BTN_COLOR );
        iLED[LED_RIGHT] = true;
      }
    }
    else
    {
        // switch is inactive
        kaimana.setLED(LED_RIGHT, BLACK);    
        iLED[LED_RIGHT] = false;
    }
  if(!digitalRead(PIN_LEFT))
  {
    switchActivity |= ATTACK_LEFT;
    // switch is active
    if(iLED[LED_LEFT] == true)
    {
      kaimana.setLED( LED_LEFT, _ON_PRESS_BTN_COLOR );
      iLED[LED_LEFT] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED( LED_LEFT, _ON_PRESS_BTN_COLOR );
      iLED[LED_LEFT] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_LEFT, BLACK);    
      iLED[LED_LEFT] = false;
  } 
  }

  //SOCD DOWN+UP
  
  if(!digitalRead(PIN_UP) && !digitalRead(PIN_DOWN))
  {
      switchActivity |= ATTACK_DOWN + ATTACK_UP;
      if(iLED[LED_DOWN] && iLED[LED_UP] == true)
      {
        iLED[LED_DOWN] = false;
        iLED[LED_UP] = false;
      } else {
        kaimana.setLED( LED_DOWN, _ON_SOCD_PRESS_COLOR );
        kaimana.setLED( LED_UP, _ON_SOCD_PRESS_COLOR );
        iLED[LED_DOWN] = true;
        iLED[LED_UP] = true;
      }
  }
  else
  {
   if(!digitalRead(PIN_DOWN))
  {
    switchActivity |= ATTACK_DOWN;
      // switch is active
      if(iLED[LED_DOWN] == true)
      {
        kaimana.setLED( LED_DOWN, _ON_PRESS_BTN_COLOR );
        iLED[LED_DOWN] = true;
      }
      else
      {
        // select new color when switch is first activated
        kaimana.setLED( LED_DOWN, _ON_PRESS_BTN_COLOR );
        iLED[LED_DOWN] = true;
      }
    }
    else
    {
        // switch is inactive
        kaimana.setLED(LED_DOWN, BLACK);    
        iLED[LED_DOWN] = false;
    }
  if(!digitalRead(PIN_UP))
  {
    switchActivity |= ATTACK_UP;
    // switch is active
    if(iLED[LED_UP] == true)
    {
      kaimana.setLED( LED_UP, _ON_PRESS_BTN_COLOR );
      iLED[LED_UP] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED( LED_UP, _ON_PRESS_BTN_COLOR );
      iLED[LED_UP] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_UP, BLACK);    
      iLED[LED_UP] = false;
  } 
  }


  
  // test switch and set LED based on result       // HOME = GUIDE
   if(!digitalRead(PIN_HOME))
  {
    // switch is active
    if(iLED[LED_HOME] == true)
    {
      //maintain color while switch is active
      iLED[LED_HOME] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED( LED_HOME, _ON_PRESS_BTN_COLOR );
      iLED[LED_HOME] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_HOME, BLACK);    
      iLED[LED_HOME] = false;
  }


  // test switch and set LED based on result    // SELECT = BACK 
  if(!digitalRead(PIN_SELECT))
  {
    // switch is active
    if(iLED[LED_SELECT] == true)
    {
      //maintain color while switch is active
      iLED[LED_SELECT] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED( LED_SELECT, _ON_PRESS_BTN_COLOR );
      iLED[LED_SELECT] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_SELECT, BLACK);    
      iLED[LED_SELECT] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_START))
  {
    // switch is active
    if(iLED[LED_START] == true)
    {
      //maintain color while switch is active
      iLED[LED_START] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED( LED_START, _ON_PRESS_BTN_COLOR );
      iLED[LED_START] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_START, BLACK);    
      iLED[LED_START] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_P1))
  {
    switchActivity |= ATTACK_P1;
    
    // switch is active
    if(iLED[LED_P1] == true)
    {
      //maintain color while switch is active
      iLED[LED_P1] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED( LED_P1, _ON_PRESS_BTN_COLOR );
      iLED[LED_P1] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_P1, BLACK);    
      iLED[LED_P1] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_P2))
  {
    switchActivity |= ATTACK_P2;
    
    // switch is active
    if(iLED[LED_P2] == true)
    {
      //maintain color while switch is active
      iLED[LED_P2] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED( LED_P2, _ON_PRESS_BTN_COLOR );
      iLED[LED_P2] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_P2, BLACK);    
      iLED[LED_P2] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_P3))
  {
    switchActivity |= ATTACK_P3;
    
    // switch is active
    if(iLED[LED_P3] == true)
    {
      //maintain color while switch is active
      iLED[LED_P3] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED( LED_P3, _ON_PRESS_BTN_COLOR );
      iLED[LED_P3] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_P3, BLACK);    
      iLED[LED_P3] = false;
  }
  

  // test switch and set LED based on result
  if(!digitalRead(PIN_P4))
  {
    switchActivity |= ATTACK_P4;
    
    // switch is active
    if(iLED[LED_P4] == true)
    {
      //maintain color while switch is active
      iLED[LED_P4] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED( LED_P4, _ON_PRESS_BTN_COLOR );
      iLED[LED_P4] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_P4, BLACK);    
      iLED[LED_P4] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K1))
  {
    switchActivity |= ATTACK_K1;
    
    // switch is active
    if(iLED[LED_K1] == true)
    {
      //maintain color while switch is active
      iLED[LED_K1] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED( LED_K1, _ON_PRESS_BTN_COLOR );
      iLED[LED_K1] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_K1, BLACK);    
      iLED[LED_K1] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K2))
  {
    switchActivity |= ATTACK_K2;
    
    // switch is active
    if(iLED[LED_K2] == true)
    {
      //maintain color while switch is active
      iLED[LED_K2] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED( LED_K2, _ON_PRESS_BTN_COLOR );
      iLED[LED_K2] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_K2, BLACK);    
      iLED[LED_K2] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K3))
  {
    switchActivity |= ATTACK_K3;
    
    // switch is active
    if(iLED[LED_K3] == true)
    {
      //maintain color while switch is active
      iLED[LED_K3] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED( LED_K3, _ON_PRESS_BTN_COLOR );
      iLED[LED_K3] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_K3, BLACK);    
      iLED[LED_K3] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K4))
  {
    switchActivity |= ATTACK_K4;
    
    // switch is active
    if(iLED[LED_K4] == true)
    {
      //maintain color while switch is active
      iLED[LED_K4] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED( LED_K4, _ON_PRESS_BTN_COLOR );
      iLED[LED_K4] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_K4, BLACK);    
      iLED[LED_K4] = false;
  }
  if(!digitalRead(PIN_LEFT) && !digitalRead(PIN_RIGHT) && !digitalRead(PIN_DOWN)&& !digitalRead(PIN_UP) && !digitalRead(PIN_P1) && !digitalRead(PIN_P2) && !digitalRead(PIN_P3)) {
    //Button hold to start tourneymode
    holdTimeout += 1;
    if(holdTimeout == 2000)
    {
    tournamentMode = true;
    tourneyModeActivate();
    } 
  } else {
    holdTimeout = 0;
  }


  // zero active switch counter (note: 4 way joystick counts as 1)
  iActiveSwitchCount = 0;
  
  // set LED color based on switch
  for(i=0;i<LED_COUNT;++i)
  {
    if(iLED[i] == true)
      ++iActiveSwitchCount;
  }  

  // update the leds with new/current colors in the array
  kaimana.updateALL();
  
  // return number of active switches
  return(iActiveSwitchCount);
}  

int tourneypollSwitches(void)
{
  static int  iLED[LED_COUNT];
  static int  iActiveSwitchCount = 0;
  static int  i;
  static int  j;
  static int  firsttime;
  static uint16_t  joystickDirection;
  static uint16_t  switchActivity;

  if(!digitalRead(PIN_LEFT) && !digitalRead(PIN_RIGHT) && !digitalRead(PIN_DOWN) && !digitalRead(PIN_UP) && !digitalRead(PIN_P1) && !digitalRead(PIN_P2) && !digitalRead(PIN_P3))
  {
    //Button hold to change idle animation
    holdTimeout += 1;
    //Button hold to start tourneymode    
    if(holdTimeout == 200)
    {
    tournamentMode = false;
    tourneyModeDeactivate();
    }
      ++iActiveSwitchCount;
  delay(10);    
  }
  else
  {    
  holdTimeout=0;
  }
    return(iActiveSwitchCount);
}


 
