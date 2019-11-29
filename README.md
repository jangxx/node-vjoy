# vJoy Bindings for Node.js

**ATTENTION**: The module will always check if the SDK and installed driver versions match and issue a warning if they don't. Unfortunately, the SDK has not been updated to the latest version at the time of this writing, so you will always see a warning.

# Installation

```bash
npm install vjoy
```

Since the vJoy driver only works on Windows, this module can also only be installed on Windows.
If you have problems building the native code parts, try installing the Windows Build Tools by running

```bash
npm install -g windows-build-tools
```

# Usage

A minimal example of a feeder application looks like this:

```javascript
const { vJoy, vJoyDevice } = require('vjoy');

if (!vJoy.isEnabled()) {
	console.log("vJoy is not enabled.");
	process.exit();
}

let device = vJoyDevice.create(1);

device.buttons[1].set(true); // press the first button

device.axes.X.set(10000); // set the X axis to some value

device.discretePOV[1].set(0); // set the first POV switch to point upwards
```

More examples can be found in the _examples/_ directory.

# Methods

## vJoy

This object is a collection of several functions, which are more or less exported 1:1 from the SDK.

**vJoy.isEnabled**()  
Returns a boolean indicating, whether or not the vJoy driver is enabled.

**vJoy.version**()  
Returns the numerical version of the vJoy driver.

**vJoy.productString**()  
Returns a string describing the vJoy driver.

**vJoy.manufacturerString**()  
Returns a string describing the manufacturer of the vJoy driver.

**vJoy.serialString**()  
Returns the version number as a String.

**vJoy.driverMatch**()
Returns an object of the form `{ matches: true, dll_version: 536, drv_version: 536 }`, which contains information about the versions of the SDK and the installed driver.

**vJoy.maxDevices**()  
Returns the maximum number of devices.

**vJoy.existingDevices**()  
Returns the current number of enabled devices.

**vJoy.registerRemovalCB**(callback)  
Registers a function to be called every time a virtual controller is added or removed. 
Will be called with `{ removed: bool, first: bool }`.
The meaning of the parameters is explained in the SDK README:
- When the removal process begins, `removed = true` and `first = true`
- When the removal process is finished, `removed = true` and `first = false`
- When the arrival process begins, `removed = false` and `first = true`
- When the arrival process is finished, `removed = false` and `first = false`

Note: You can only register a single callback. Subsequent calls overwrite the previously set callbacks.

**vJoy.axes**  
A static array of the names of the axes. Contains: `[ "X", "Y", "Z", "Rx", "Ry", "Rz", "Slider0", "Slider1", "Wheel", "POV" ]`

## vJoyDevice

This is the class abstracting the vJoy SDK into an easy-to-use library.
It is recommended to not instantiate this class directly and use `vJoyDevice.create(deviceId)`, which takes care of all the initialization, instead.

**vJoyDevice.create**(id)  
Creates and initializes a new `vJoyDevice`. Returns the new device if the initialization was successful and `null` otherwise.

**vJoyDevice.exists**(id)  
Checks if the device with the specified id exists.

**vJoyDevice.status**(id)  
Queries the driver for the status of the device. Returns one of the following values:
```
"busy": The device is owned by another feeder and can not be acquired at this time.
"missing": The vJoy device is missing.
"free": The device is free and can be aquired by running initialize().
"acquired": The device is already acquired by the current feeder.
"unknown": Something went wrong.
```

**constructor**(id)  
Creates a new device instance with the supplied id.

*get* **id**

*get* **initialized**

*get* **status**  
Contains the status of the device.

*get* **buttons**  
An object mapping button ids to `vJoyButton` objects. Contains all the currently known buttons of the device.

*get* **discretePOV**  
An object mapping POV ids to `vJoyDiscretePOV` objects. Contains all the currently known discrete POV switches of the device.

*get* **continuousPOV**  
An object mapping POV ids to `vJoyContinuousPOV` objects. Contains all the currently known continuous POV switches of the device.

*get* **axes**  
An object mapping axis ids (from `vJoy.axes`) to `vJoyAxis` objects, or `null` if the axis is not configured.

**initialize**()  
Tries to acquire the device. Updates the internal initialized status and returns `true` if the device was acquired.

**updateInputs**()  
Query the driver for the number of buttons, pov switches and enabled axes and update the `buttons`, `discretePOV`, `continuousPOV` and `axes` properties.
This also resets all buttons and pov switches to an unpressed state.

**resetButtons**()  
Resets all buttons to an unpressed state.

**free**()  
Relinquishes the device. **THIS NEEDS TO BE CALLED WHEN YOU DON'T NEED THE DEVICE ANYMORE, OTHERWISE NO OTHER PROCESS CAN ACQUIRE IT**.

## vJoyButton, vJoyDiscretePOV, vJoyContinuousPOV, vJoyAxis

These are the classes abstracting the different types of input on a device and they are all very similar.
You can not instantiate these youself, instead you get them from the `buttons`, `discretePOV`, `continuousPOV` and `axes` properties on a `vJoyDevice`.

*get* **id**

*get* **value**  
Contains the current value of the input.

**set**(value)  
Sets the input to the specified value and returns a boolean indicating if the operation was successful.
The values and their meanings differ for all the input types.

- vJoyButton: The value is a boolean indicating if the button is pressed.
- vJoyDiscretePOV: The value is an integer between -1 and 3 with the following meaning: _-1 = neutral, 0 = up, 1 = left, 2 = down, 3 = right_
- vJoyContinuousPOV: The value is an integer between -1 and 35999, where _-1 = neutral, 0-35999 = 1/100 degree steps with 0 = up_
- vJoyAxis: The value is an integer between 1 and 32769.

# Attribution

The vJoy SDK is licensed under the MIT license.

```
MIT License

Copyright (c) 2017 Shaul Eizikovich

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```