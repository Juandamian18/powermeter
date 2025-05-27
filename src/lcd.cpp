/**
 * @file wificlient.h
 * @author Dirk Broßwick (dirk.brosswick@googlemail.com)
 * @brief 
 * @version 1.0
 * @date 2022-10-03
 * 
 * @copyright Copyright (c) 2022
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#include "lcd.h"
#include "measure.h"
#include <LiquidCrystal_I2C.h>

int lcdColumns = 16;
int lcdRows = 2;
int lcdAddress = 0x27;
static bool displayinit = false;
int virtualChannels = 6;
int currentChannel = 0;
int interval = 5;

LiquidCrystal_I2C lcd(lcdAddress, lcdColumns, lcdRows);

void lcd_init( void ) {
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Bienvenido");
    displayinit = true;
}

void lcd_loop( void ) {
    static uint64_t NextDisplayMillis = 0;
    /**
     * abort if display not init or active
     */
    if( !displayinit )
        return;
    /**
     * on first run, set next display update time
     */
    if( NextDisplayMillis == 0 )
        NextDisplayMillis = millis();
    /**
     * if display update time coming, update
     */
    if( NextDisplayMillis <= millis() ) {
        NextDisplayMillis = millis() + interval * 1000l;
        lcd.clear();

        int phase = currentChannel;
        int baseIndex = phase * 4;

        lcd.setCursor(0, 0);
        lcd.printf("Fase #%i", phase + 1);

        lcd.setCursor(8, 0);
        lcd.printf("%.1f%s", measure_get_channel_rms(baseIndex + 0), measure_get_channel_report_unit(baseIndex + 0)); // Corriente

        lcd.setCursor(0, 1);
        lcd.printf("%.1f%s", measure_get_channel_rms(baseIndex + 1), measure_get_channel_report_unit(baseIndex + 1)); // Voltaje

        lcd.setCursor(8, 1);
        lcd.printf("%.1f%s", measure_get_channel_rms(baseIndex + 2), measure_get_channel_report_unit(baseIndex + 2)); // Potencia

        currentChannel += 1;
        if(currentChannel >= 3){
            currentChannel = 0;
        }
    }
}
