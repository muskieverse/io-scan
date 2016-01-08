/********************************************************************
Copyright 2016 Joseph F. Muscarella

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
********************************************************************/

#ifndef __IO_SCAN_H
#define __IO_SCAN_H
#include "application.h"

class   DigitalInput
{
    public:
                DigitalInput();
                DigitalInput(int pin, PinMode mode, bool active_low=false);

        void    Scan();
        
        bool    RisingEdge();
        bool    FallingEdge();
        bool    State();
        
        // Properties        
        void    Pin(int pin);
        void    Mode(PinMode mode);
        void    ActiveLow(bool active_low);
        
    private:
    
        void    Initialize();
        
        int     pin_;
        PinMode mode_;
        bool    active_low_;
        
        bool    this_scan_;
        bool    last_scan_;
        bool    flag_active_;
        bool    rising_edge_;
        bool    falling_edge_;
};

class   DigitalOutput
{
    public:
    
                DigitalOutput();
                DigitalOutput(int pin, bool active_low=false);
                
        void    Off();
        void    On();
        void    State(bool state);
        void    Toggle();
        
        // Properties        
        void    Pin(int pin);
        void    ActiveLow(bool active_low);
        
    private:

        void    Initialize();

        int     pin_;
        bool    active_low_;
};

// Analog voltage input
class   AnalogInput
{
    public:
                AnalogInput();
                AnalogInput(int pin);
                AnalogInput(int pin, double range_lo, double range_hi);

        int     ReadRaw() const;
        double  ReadVoltage() const;
        double  ReadRange() const;

        // Properties        
        void    Pin(int pin);
        void    RangeLow(double lo);
        void    RangeHigh(double hi);
        
    private:
    
        void    Initialize();
        
        int     pin_;
        double  range_lo_;
        double  range_hi_;
};

// Analog voltage output (Photon only)
class   AnalogOutput
{
    public:
    
                AnalogOutput();
                AnalogOutput(int pin);
                
        void    OutputRaw(int binary);
        void    OutputVoltage(double voltage);

        // Properties        
        void    Pin(int pin);

    private:

        void    Initialize();

        int     pin_;
};

// PWM Analog Ouput
//   Core pins: A0, A1, A4, A5, A6, A7, D0 and D1
//   Photon pins: D0, D1, D2, D3, A4, A5, WKP, RX and TX  (see docs for caveat)
class   AnalogPWMOutput
{
    public:
    
                AnalogPWMOutput();
                AnalogPWMOutput(int pin);
                
        void    OutputRaw(uint8_t binary);              // binary = 0 to 255
        void    OutputDutyCycle(int percentage);        // percentage = 0 to 100

        // Properties        
        void    Pin(int pin);

    private:

        void    Initialize();

        int     pin_;
};

#endif  /* __IO_SCAN_H */

