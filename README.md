# StupidDogFocuser
As open-source electronic telescope focuser

The StupidDogFocuser is a prototype electronic focuser. It shall comply with ASCOM and INDI and can operate on Linux or Windows.

The goal of this project is to develop an electronic focuser that is compact, free of airwires, capable of being mounted to a variety of telescope focusers, software/hardware controllable, inexpensive, easy to build at home, and only use components that are easy to acquire.

The PCB should fit within a double-sided 100mm x 70mm copper clad board and should be possible to be etched and soldered at home, but it should also be designed in such a way that one could order a commercially manufactured board (that is to say that silkscreen layers should include all necessary information for the board to be run on a pick and place machine or ordred and soldered by a novice).

I'm not opposed to through-hole parts, but I personally find drilling boards to be the most difficult part of home manufacture of PCB, I'd rather keep the drill-file to a minimum if at all possible. That also means that VIAs should be kept to a minimum and *must* be large enough to be drilled at home (1.2mm/.8mm drill)

Traces should be a minimum width of .4mm (however, short stubs of .2mm to come off pads is acceptable)

There should be a calibration capability so that the user can set the inner and outer limits of their particular focuser. I don't believe that we need to worry about more than one focuser per board. If you have two or six telescopes to focus, maybe you should assemble two or six boards.

The calibration should survive a power-off. Additionally, the focus should survive a power-off. I understand that we can't be sure that the focuser wasn't manually moved during a power outage, but I think we can trust the user to understand that if they move the focuser by hand during a power outage, they're going to have to recalibrate.

I think that we could have a limit switch for some focusers (not all, though). It's because of the 'some' that I think we need to store the current focus position over a power off. The user shouldn't have to recalibrate the limits every time they power on the scope.

If somebody can figure out a way to detect the focus limits through power consumption, feel free to try to add it.

This should be a complete package. There should be an installer for every operating system. It shouldn't involve a lot of guesswork for the non-technical user who just wants to order the soldered board and get to work.

Ultimately, I want somebody to be able to have a neat, compact focuser for under $100 and their time and solder.
