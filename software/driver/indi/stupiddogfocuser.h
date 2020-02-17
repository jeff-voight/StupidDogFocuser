/*
    Stupid Dog Focuser
    Stupid Dog Observatory
    Copyright 2020 Jeff Voight (jeff.voight@gmail.com)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

 */

#pragma once

#include "indifocuser.h"

class StupidDogFocuser : public INDI::Focuser {
public:
    StupidDogFocuser();
    virtual ~StupidDogFocuser() override = default;

    virtual bool ISNewNumber(const char *dev, const char *name, double values[], char *names[], int n) override;
    virtual bool ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[], int n) override;

protected:
    virtual bool Handshake() override;
    const char *getDefaultName() override;
    virtual bool initProperties() override;
    virtual bool updateProperties() override;
    virtual IPState MoveAbsFocuser(uint32_t targetTicks) override;
    virtual IPState MoveRelFocuser(FocusDirection dir, uint32_t ticks) override;
    virtual bool AbortFocuser() override;
    virtual void TimerHit() override;
    virtual bool saveConfigItems(FILE *fp) override;
    virtual bool SyncFocuser(uint32_t ticks) override;

private:
    unsigned char CheckSum(char *_focuser_cmd);
    unsigned char CalculateSum(const char *_focuser_cmd);
    int SendCommand(char *_focuser_cmd);
    int ReadResponse(char *_focuser_cmd);
    void GetFocusParams();

    int updateFocuserPosition(double *value);
    int updateFocuserTemperature(double *value);
    int updateFocuserBacklash(double *value);
    int updateFocuserFirmware(char *_focuser_cmd);
    int updateFocuserMotorSettings(double *duty, double *delay, double *ticks);
    int updateFocuserPositionRelativeInward(double value);
    int updateFocuserPositionRelativeOutward(double value);
    int updateFocuserPositionAbsolute(double value);
    int updateFocuserPowerSwitches(int s, int new_sn, int *cur_s1LL, int *cur_s2LR, int *cur_s3RL, int *cur_s4RR);
    int updateFocuserMaxPosition(double *value);
    int updateFocuserSetPosition(const double *value);

    int ReadUntilComplete(char *buf, int timeout);

    int timerID{ -1};
    double targetPos{ 0};
    double simulatedTemperature{ 0};
    double simulatedPosition{ 0};

    INumber TemperatureN[1];
    INumberVectorProperty TemperatureNP;

    INumber SettingsN[3];
    INumberVectorProperty SettingsNP;

    ISwitch PowerSwitchesS[4];
    ISwitchVectorProperty PowerSwitchesSP;

    INumber MinMaxPositionN[2];
    INumberVectorProperty MinMaxPositionNP;

    INumber MaxTravelN[1];
    INumberVectorProperty MaxTravelNP;

    INumber SetRegisterPositionN[1];
    INumberVectorProperty SetRegisterPositionNP;

    INumber RelMovementN[1];
    INumberVectorProperty RelMovementNP;

    INumber AbsMovementN[1];
    INumberVectorProperty AbsMovementNP;

    
};