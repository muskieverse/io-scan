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

#include "io-scan.h"
#include "application.h"

//
//  Digital Input
//

DigitalInput::DigitalInput()
    : pin_(0)
    , mode_(INPUT)
    , active_low_(false)
    , this_scan_(false)
    , last_scan_(false)
    , flag_active_(false)
    , rising_edge_(false)
    , falling_edge_(false)
{
}

DigitalInput::DigitalInput(int pin, PinMode mode, bool active_low)
    : pin_(pin)
    , mode_(mode)
    , active_low_(active_low)
    , this_scan_(false)
    , last_scan_(false)
    , flag_active_(false)
    , rising_edge_(false)
    , falling_edge_(false)
{
    Initialize();
}

void    DigitalInput::Initialize()
{
    pinMode(pin_, mode_);
    
    this_scan_      = State();
    last_scan_      = this_scan_;
    flag_active_    = false;
    rising_edge_    = false;
    falling_edge_   = false;
}

void    DigitalInput::ActiveLow(bool active_low)
{
    active_low_ = active_low;
    Initialize();
}

void    DigitalInput::Pin(int pin)
{
    pin_    = pin;
    Initialize();
}

void    DigitalInput::Mode(PinMode mode)
{
    mode_   = mode;
    Initialize();
}

bool    DigitalInput::State()
{
    if (active_low_ == true)
    {
        return (digitalRead(pin_) == LOW);
    }
    else
    {
        return (digitalRead(pin_) == HIGH);
    }
}

void    DigitalInput::Scan()
{
    this_scan_    = State();
    rising_edge_  = this_scan_ && last_scan_ && flag_active_;
    falling_edge_ = !this_scan_ && !last_scan_ && flag_active_;
    flag_active_  = ((this_scan_ && !last_scan_) || (last_scan_ && !this_scan_)) && !flag_active_;
    last_scan_    = this_scan_;
}

bool    DigitalInput::RisingEdge()
{
    return (rising_edge_);
}

bool    DigitalInput::FallingEdge()
{
    return (falling_edge_);
}

//
//  Digital Output
//

DigitalOutput::DigitalOutput()
    : pin_(0)
    , active_low_(false)
{
}

DigitalOutput::DigitalOutput(int pin, bool active_low)
    : pin_(pin)
    , active_low_(active_low)
{
    Initialize();
}

void    DigitalOutput::Initialize()
{
    pinMode(pin_, OUTPUT);
    Off();
}

void    DigitalOutput::ActiveLow(bool active_low)
{
    active_low_ = active_low;
    Initialize();
}

void    DigitalOutput::Pin(int pin)
{
    pin_    = pin;
    Initialize();
}

void    DigitalOutput::Off()
{
    if (active_low_ == true)
    {
        digitalWrite(pin_, HIGH);
    }
    else
    {
        digitalWrite(pin_, LOW);
    }
}

void    DigitalOutput::On()
{
    if (active_low_ == true)
    {
        digitalWrite(pin_, LOW);
    }
    else
    {
        digitalWrite(pin_, HIGH);
    }
}

void    DigitalOutput::State(bool state)
{
    if (state == true)
    {
        On();
    }
    else
    {
        Off();
    }
}

void    DigitalOutput::Toggle()
{
    digitalWrite(pin_, !digitalRead(pin_));
}




//
// AnalogInput
//
AnalogInput::AnalogInput()
    : pin_(0)
    , range_lo_(0.0)
    , range_hi_(0.0)
{
}

AnalogInput::AnalogInput(int pin)
    : pin_(pin)
    , range_lo_(0.0)
    , range_hi_(0.0)
{
    Initialize();
}

AnalogInput::AnalogInput(int pin, double range_lo, double range_hi)
    : pin_(pin)
    , range_lo_(range_lo)
    , range_hi_(range_hi)
{
    Initialize();
}

void    AnalogInput::Initialize()
{
    pinMode(pin_, INPUT);
}

void    AnalogInput::Pin(int pin)
{
    pin_    = pin;
    Initialize();
}

void    AnalogInput::RangeLow(double lo)
{
    range_lo_   = lo;
}

void    AnalogInput::RangeHigh(double hi)
{
    range_hi_   = hi;
}

int     AnalogInput::ReadRaw() const
{
    return (analogRead(pin_));
}

double     AnalogInput::ReadVoltage() const
{
    return (analogRead(pin_) * (3.3 / 4096));
}

// Helper - Double version of Particle map() function
double  dmap(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double     AnalogInput::ReadRange() const
{
    return (dmap(analogRead(pin_), 0, 4096, range_lo_, range_hi_));
}

//
// AnalogOutput
//
AnalogOutput::AnalogOutput()
    : pin_(0)
{
}

AnalogOutput::AnalogOutput(int pin)
    : pin_(pin)
{
    Initialize();
}

void    AnalogOutput::Initialize()
{
    pinMode(pin_, OUTPUT);
}

void    AnalogOutput::Pin(int pin)
{
    pin_    = pin;
    Initialize();
}

void    AnalogOutput::OutputRaw(int binary)
{
    pinMode(pin_, OUTPUT);
    analogWrite(pin_, binary);
}

void    AnalogOutput::OutputVoltage(double voltage)
{
    pinMode(pin_, OUTPUT);
    analogWrite(pin_, constrain((voltage / 3.3) * 4096, 0, 4095));
}

//
// AnalogPWMOutput
//
AnalogPWMOutput::AnalogPWMOutput()
    : pin_(0)
{
}

AnalogPWMOutput::AnalogPWMOutput(int pin)
    : pin_(pin)
{
    Initialize();
}

void    AnalogPWMOutput::Initialize()
{
    pinMode(pin_, OUTPUT);
}

void    AnalogPWMOutput::Pin(int pin)
{
    pin_    = pin;
    Initialize();
}

void    AnalogPWMOutput::OutputRaw(uint8_t binary)
{
    pinMode(pin_, OUTPUT);
    analogWrite(pin_, binary);
}

void    AnalogPWMOutput::OutputDutyCycle(int percentage)
{
    pinMode(pin_, OUTPUT);
    analogWrite(pin_, constrain((percentage * 255) / 100, 0, 255));
}



