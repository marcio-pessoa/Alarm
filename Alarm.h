/* Alarm.h - Manage alarms
 * 
 * Author: Márcio Pessoa <marcio.pessoa@sciemon.com>
 * Contributors: none
 * 
 * Examples
 * 
 *   Speed monitoring
 *     Code:
 *       Alarm speed(40, 60);
 *       speed.nameWrite("Speed");
 *       speed.unitWrite(" k/h");
 *     Results:
 *       Speed: 30 k/h (OK)
 *       Speed: 39 k/h (OK)
 *       Speed: 40 k/h (Warning)
 *       Speed: 59 k/h (Warning)
 *       Speed: 60 k/h (Critical)
 *       Speed: 70 k/h (Critical)
 * 
 *   Temperature monitoring
 *     Code:
 *       Alarm temperature(40, 50, 20, 10);
 *       temperature.nameWrite("Temperature");
 *       temperature.unitWrite(" celcius");
 *     Results:
 *       Temperature: 0 celcius (Critical)
 *       Temperature: 10 celcius (Critical)
 *       Temperature: 11 celcius (Warning)
 *       Temperature: 20 celcius (Warning)
 *       Temperature: 21 celcius (OK)
 *       Temperature: 39 celcius (OK)
 *       Temperature: 40 celcius (Warning)
 *       Temperature: 49 celcius (Warning)
 *       Temperature: 50 celcius (Critical)
 *       Temperature: 60 celcius (Critical)
 * 
 *   Lenght monitoring
 *     Code:
 *       Alarm lenght(40, 50, 20, 10, true);
 *       lenght.nameWrite("Lenght");
 *       lenght.unitWrite(" meters");
 *     Results:
 *       Lenght: 0 meters (OK)
 *       Lenght: 10 meters (OK)
 *       Lenght: 11 meters (Warning)
 *       Lenght: 20 meters (Warning)
 *       Lenght: 21 meters (Critical)
 *       Lenght: 39 meters (Critical)
 *       Lenght: 40 meters (Warning)
 *       Lenght: 49 meters (Warning)
 *       Lenght: 50 meters (OK)
 *       Lenght: 60 meters (OK)
 * 
 * Change log
 * 2016-03-01
 *         * status_name
 *         Code optimization, removed some break statements after return.
 * 
 * 2015-06-20
 *         * min_warningRead
 *         Fix to return corret variable.
 *         * min_criticalRead
 *         Fix to return corret variable.
 * 
 * 2015-05-31
 *         * unitRead
 *         Added unitRead method.
 *         * unitWrite
 *         Added unitWrite method.
 * 
 * 2014-12-11
 *         * check
 *         Fixed minimum alarm thresholds.
 * 
 * 2014-11-20
 *         Experimental version.
 */

#ifndef Alarm_h
#define Alarm_h

#include "Arduino.h"

// Status ID
#define OK 0
#define WARNING 1
#define	CRITICAL 2
#define UNKNOWN 3

class Alarm
{
  public:
    Alarm(int max_warning, int max_critical,
          int min_warning = 0, int min_critical = 0,
          bool inverse = false);
    void set(int max_warning, int max_critical,
             int min_warning = 0, int min_critical = 0,
             bool inverse = false);
    byte check(float value);
    bool force_check(byte status);
    byte status();
    String status_name();
    int max_warningRead();
    int max_criticalRead();
    int min_warningRead();
    int min_criticalRead();
    float valueRead();
    bool nameWrite(char *name);
    String nameRead();
    bool unitWrite(char *name);
    String unitRead();
  private:
    void reset_status_timer();
    float _value = 0;
    bool _inverse;
    // thresholds
    int _max_warning;
    int _max_critical;
    int _min_warning;
    int _min_critical;
    // service status
    byte _status = UNKNOWN;
    // Identification
    char *_name;
    char *_unit;
};

#endif
