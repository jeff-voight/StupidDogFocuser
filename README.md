# StupidDogFocuser

## Open-source electronic telescope focuser

The StupidDogFocuser is a work-in-progress prototype electronic focuser. It shall eventually comply with ASCOM and INDI and should operate on Linux, Windows, or Mac.

## Goals

The goal of this project is to develop an electronic focuser that is compact, free of airwires, capable of being mounted to a variety of telescope focusers controllable via a PCB-mounted knob, serial commands, and INDI and ASCOM software. It should be inexpensive, easy to build at home, and only use components that are easy to acquire.

Ultimately, I want somebody to be able to have a neat, compact focuser for under $100 and their time and solder.

## Size and Shape

The PCB is a shield for an Arduino UNO R3. I hope to be able to etch and solder the board at home, but it should also be designed in such a way that one could order a commercially manufactured board. The KiCad design files will be included. The initial builds will be geared toward a commercial board house.

The board is approximately the same shape as the UNO. It receives the 12V power directly from the Arduino. That means that you need to plug the Arduino into a 12V 1A power supply. These are available where you bought the Arduino. We could get more torque and speed if we went with a higher voltage, but we don't really need more torque or speed.

On one end is an optional temperature/humidity sensor. During assembly, the legs of the package need to be bent so that the sensor can be layed flat extended out in space beyond the board. This, hopefully, keeps the sensor far enough away from the driver that it isn't affected and it provides a way to extend the sensor out of an enclosure to give it access to the outdoor air.

The board features a mounted rotary encoder for handheld use. In fact, if one were so inclined, one wouldn't necessarily need to enclose this focuser. One could very easily just put the hat on the arduino, wire up the motor, plug it into 12V, and hold the thing bare and be up and running without an enclosure.

Heck, you could hot glue the whole thing right on your observatory wall or telescope mount and be fine. Maybe clean the spiders out from time to time. I mean, don't let it rain on it, but you weren't going to let it rain on your telescopes, right? 

The encoder has 30 detents, but something I didn't realize at first was that the encoder counts two steps per detent. At first I fretted about this, but at 5400 steps per rotation on a 27:1 geared stepper running at half-stepping (for torque and performance), two steps per detent seemed like an acceptable trade-off. If you're running a 200 step stepper, you *should* still be okay on a refractor or reflector. I can't say for an SCT.

## Enclosure
Included is a 3d-printable set of STL files that worked for me. It even has a knob.

I printed mine in glow-in-the-dark. It has never helped.

I hope to find a more professional enclosure, but I'm not actively looking.

Along with the enclosure, I haven't included the panel-mount electrical connector because I haven't found a 6 pin connector that I like.

I'm currently using a 4-pin aircraft something something. If you have a 6-pin (2 pins for the limit switch) connector that you love and you 
can find it on digikey, feel free to fork the code and submit a pull request.

## Assembly
The PCB is designed to use the same resistors and the same capacitors throughout. You can't go wrong. Just solder the resistors in wherever you see a resistor footprint and the same for the capacitors.

The DHT11 or DHT22 needs to be layed flat if you want it to stick out of an enclosure. This bend needs to be done before soldering.

The motor screw terminals should probably face in the same direction as the wires are going to go. There should be enough space to flip it around.

The Schmidtt Trigger footprint includes a dot and a little slanty line to indicate the dotted end of the chip. Make sure you get the orientation correct.

Likewise, the DRV8825 footprint includes a white rectangle on the same end that the chip of the DRV8825 daughterboard has. Make sure those line up, too.

The DRV8825 *ABSOLUTELY* needs the heatsink that comes with it. Make sure you put that thing on. It didn't take me but a few minutes to roast one of mine during development because I was being lazy.

The DRV8825 *ABSOLUTELY* needs to be adjusted before plugging in your first stepper. The steppers that I've been getting have been running best at about .8A per coil. But, the motor gets HOT.

### DIY disclaimer
I'm not opposed to through-hole parts, but I personally find drilling boards to be the most difficult part of home manufacture of PCB, I'd rather keep the drill-file to a minimum. Consider that you're going to be drilling all of the Arduino header pins and all of the component pins. It's probably safest to order the boards from a board house. However, if you only drill out the holes you need, you can save a whole bunch of the arduino pin holes. You technically only need one ground pin. Make sure you carry the 12V and 5V pins through.

The KiCad PCBs will be done for _my_ convenience for now. That means tiny traces and silkscreen that I wouldn't dare do at home and drill holes galor and if I feel like throwing in a via collection that carries signals and looks like a moose, that's my prerogative.

I mean, I probably won't, but just in case I do.

## Calibration and limit switches

Another goal is a limit switch and a reset routine. Upon hard reset (if there is such a thing), on power-up, it would store it's current position, rack the focuser IN until it touched the limit switch, reset everything such the limit switch is the low limit and the original position gets restored to it's whatever position it was before. I've included the pins for the limit switch, but I haven't yet worked out a homing routine. When it happens, you'll probably need to build a focuser for each telescope you want to drive because the results of the homing and length of focus will get stored in EEPROM.

One way or another, I feel like I need some type of security such that my cameras never fall to the floor or I end up stripping a gear on the focuser.

That said, it hasn't been a problem _yet_.

## Power-Off Conditions

For the time being, all is lost on reset/power-off. We start the focuser in the 20,000s. That should be enough to give a couple of inward turns of a knob.

A limit switch would solve this.

# As it is

As it is, we communicate at 115,200 baud. We depend on AccelStepper and a high performance encoder library, so I don't want to slow either of those down with slow serial performance. Our signal is only going a few feet, and unless you've got outrageous amounts of noise, 115,200 will be fine.

# Commands

Serial commands are as follows:

| Command | Description | Response        | Defaults | Comments |
| ---     | ---         | ---             | ---      | --- |
| \<HA>	  | Halt        | HA!             | N/A      | as quickly as possible |
| \<GE> 	  | Is enabled? | [T\|F]!          | True     | Motor Driver |
| \<GR>     | Is reversed?| [T\|F]!          | False    | Motor direction |
| \<GM>     | Microsteps  | [1-32]!         | _(1/)_1  | Denominator (not yet functional) | 
| \<GH>     | High limit  | MAXINT! | 108000    | Distance from initial |
| \<GL>     | Low limit   | [0! | 0  | 32 bit int |
| \<GS>     | Speed       | [0-255]!      | 255     | Stepper motor dependent |
| \<GT>     | Temperature | %f.2!             | N/A      | DHT11/22 precision  |
| \<GP>     | Position    | 0-MAXINT! | 0        | Previous focus position |
| \<IM>     | Moving?     | [T\|F]!          | F        | True during movement |
| \<AM%d>   | Absolute Move | %d! (target) | N/A      | Target position|
| \<RM%d>   | Relative Move | %d! (target) | N/A      | Target position |
| \<RD[T\|F]>     | Reverse Motor | [T\|F]!       | N/A      | Response is new is reversed |
| \<SY%d>   | Sync Motor | %d! (same as param) | N/A  | |
| \<EN>     | Enable motor | EN!          | N/A| ||
| \<DI>     | Disable motor| DI!          | N/A | |
| \<SM[1-32]> | Set Microstepping 1/1 - 1/32 | %u! | 1 | New microstep mode (not yet functional)|
| \<SP%u>   | Set Speed 200-4000 | %d! | New speed | 1000 | Measure your motor to determine |
| \<SH%d>   | Set high limit | %d! | 32767 | Response is new high |
| \<SL%d>   | Set low limit  | %d! | -32768 | Response is new low limit |

Any error will trigger ERROR(optional message)#

