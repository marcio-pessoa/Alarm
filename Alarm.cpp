/* Alarm.cpp - Manage alarms
 * 
 */

#include "Arduino.h"
#include "Alarm.h"

/* Alarm::Alarm
 * 
 * Description
 *   Manage alarms.
 * 
 *   Alarm (int max_warning, int max_critical,
 *          int min_warning, int min_critical,
 *          bool inverse)
 * 
 * Parameters
 *   max_warning
 *   int max_critical
 *   min_warning
 *   min_critical
 *   inverse
 * 
 * Returns
 *   void
 */
Alarm::Alarm(int max_warning, int max_critical,
             int min_warning, int min_critical,
             bool inverse) {
  //
  _max_warning = max_warning;
  _max_critical = max_critical;
  // 
  _min_warning = min_warning;
  _min_critical = min_critical;
  //
  _inverse = inverse;
  //
  _name = "";
  _unit = "";
}

/* set
 * 
 * Description
 *   Set limits to alarm.
 * 
 *   alarm.set (int max_warning, int max_critical,
 *              int min_warning, int min_critical,
 *              bool inverse)
 * 
 * Parameters
 *   max_warning
 *   int max_critical
 *   min_warning
 *   min_critical
 *   inverse
 * 
 * Returns
 *   void
 */
void Alarm::set(int max_warning, int max_critical,
                int min_warning, int min_critical,
                bool inverse) {
  //
  _max_warning = max_warning;
  _max_critical = max_critical;
  // 
  _min_warning = min_warning;
  _min_critical = min_critical;
  //
  _inverse = inverse;
}

/* check
 * 
 * Description
 *   Check alarm.
 * 
 *   alarm.check()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   int: Status ID
 */
byte Alarm::check(float value) {
  // Maximum Critical
  _value = value;
  if (value >= _max_critical) {
    _status = CRITICAL;
  }
  // Maximum Warning
  else if (value >= _max_warning) {
    _status = WARNING;
  }
  // OK
  else {
    _status = OK;
  }
  if (_min_warning != _min_critical) {
    // Minimum Critical
    if (value <= _min_critical) {
      _status = CRITICAL;
    }
    // Minimum Warning
    else if (value <= _min_warning) {
      _status = WARNING;
    }
  }
  // Invert results if necessary
  if (_inverse) {
    switch (_status) {
      case OK: {
        _status = CRITICAL;
        break;
      }
      case CRITICAL: {
         _status = OK;
       break;
      }
    }
  }
  return _status;
}

/* force_check
 * 
 * Description
 *   Force check result.
 * 
 *   alarm.foce_check()
 * 
 * Parameters
 *   status: Alarm status
 * 
 * Returns
 *   bool: 
 */
bool Alarm::force_check(byte status) {
  if (status >= OK and status <= UNKNOWN) {
    _status = status;
    return false;
  }
  return true;
}

/* status
 * 
 * Description
 *   Return status ID.
 * 
 *   alarm.status()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   int: Status ID
 */
byte Alarm::status() {
  return _status;
}

/* status_name
 * 
 * Description
 *   Return fan name.
 * 
 *   alarm.status_name()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   int: Status name
 */
String Alarm::status_name() {
  switch (_status) {
    case OK: {
      return "OK";
    }
    case WARNING: {
      return "Warning";
    }
    case CRITICAL: {
       return "Critical";
    }
    case UNKNOWN:
    default: {
      return "Unknown";
    }
  }
}

/* max_warningRead
 * 
 * Description
 *   Get maximum warning threshold.
 * 
 *   alarm.max_warningRead()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   int: Maximum warning threshold 
 */
int Alarm::max_warningRead() {
  return _max_warning;
}

/* max_critical
 * 
 * Description
 *   Get maximum critical threshold.
 * 
 *   alarm.max_critical()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   int: Maximum critical threshold 
 */
int Alarm::max_criticalRead() {
  return _max_critical;
}

/* min_warningRead
 * 
 * Description
 *   Get minimum warning threshold.
 * 
 *   alarm.min_warningRead()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   int: Minimum warning threshold 
 */
int Alarm::min_warningRead() {
  return _min_warning;
}

/* min_criticalRead
 * 
 * Description
 *   Get minimum critical threshold.
 * 
 *   alarm.min_criticalRead()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   int: Minimum critical threshold 
 */
int Alarm::min_criticalRead() {
  return _min_critical;
}

/* min_criticalRead
 * 
 * Description
 *   Get minimum critical threshold.
 * 
 *   alarm.min_criticalRead()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   int: Minimum critical threshold 
 */
float Alarm::valueRead() {
  return _value;
}

/* nameWrite
 * 
 * Description
 *   Set alarm name.
 * 
 *   sensor.nameWrite()
 * 
 * Parameters
 *   String name
 * 
 * Returns
 *   true: if error
 *   false: if no error
 */
bool Alarm::nameWrite(char *name) {
  if (strlen(name) > 0) {
    _name = name;
    return false;
  }
  return true;
}

/* nameRead
 * 
 * Description
 *   Return alarm name.
 * 
 *   sensor.nameRead()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   String: Alarm name.
 */
String Alarm::nameRead() {
  return _name;
}

/* unitWrite
 * 
 * Description
 *   Set alarm unit.
 * 
 *   sensor.unitWrite()
 * 
 * Parameters
 *   String unit
 * 
 * Returns
 *   true: if error
 *   false: if no error
 */
bool Alarm::unitWrite(char *unit) {
  if (strlen(unit) > 0) {
    _unit = unit;
    return false;
  }
  return true;
}

/* unitRead
 * 
 * Description
 *   Return alarm unit.
 * 
 *   sensor.unitRead()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   String: Alarm unit.
 */
String Alarm::unitRead() {
  return _unit;
}
