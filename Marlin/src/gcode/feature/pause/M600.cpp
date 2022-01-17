/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "../../../inc/MarlinConfig.h"

#if ENABLED(ADVANCED_PAUSE_FEATURE)

#include "../../gcode.h"
#include "../../../feature/pause.h"
#include "../../../module/motion.h"
#include "../../../module/printcounter.h"

#if HAS_MULTI_EXTRUDER
  #include "../../../module/tool_change.h"
#endif

#if HAS_LCD_MENU
  #include "../../../lcd/marlinui.h"
#endif

#if ENABLED(MMU2_MENUS)
  #include "../../../lcd/menu/menu_mmu2.h"
#endif

#if ENABLED(MIXING_EXTRUDER)
  #include "../../../feature/mixing.h"
#endif

#if HAS_FILAMENT_SENSOR
  #include "../../../feature/runout.h"
#endif

/**
 * M600: Pause for filament change
 *
 *  E[distance] - Retract the filament this far
 *  Z[distance] - Move the Z axis by this distance
 *  X[position] - Move to this X position, with Y
 *  Y[position] - Move to this Y position, with X
 *  U[distance] - Retract distance for removal (manual reload)
 *  L[distance] - Extrude distance for insertion (manual reload)
 *  B[count]    - Number of times to beep, -1 for indefinite (if equipped with a buzzer)
 *  T[toolhead] - Select extruder for filament change
 *  R[temp]     - Resume temperature (in current units)
 *
 *  Default values are used for omitted arguments.
 */
void GcodeSuite::M600() {
  #if ENABLED(HOME_BEFORE_FILAMENT_CHANGE)
    home_all_axes();
  #endif
  // Move the head up so you can easily grab the extruded filament out without burning your self.
  do_blocking_move_to_z(70);

  change_filament();
}

#endif // ADVANCED_PAUSE_FEATURE
