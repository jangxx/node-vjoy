# vJoy Bindings for Node.js

**ATTENTION**: The module is built against the SDK shipped with a [fork of the original vJoy](https://github.com/njz3/vJoy). The newer SDK should be backwards compatible, but you will always see an error message if you're running the old official version 2.1.9.

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

**vJoyDevice.ffbSupported**(id)  
Checks if the device with the specified id supports Force Feedback.

**vJoyDevice.getFFBEffects**(id)  
Returns an object listing support for the various effect types.

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

*get* **ffbSupported**  
Contains the Force Feedback support status.

*get* **ffbEffects**  
Contains an object listing support for the various effect types.

**initialize**()  
Tries to acquire the device. Updates the internal initialized status and returns `true` if the device was acquired.

**updateInputs**()  
Query the driver for the number of buttons, pov switches and enabled axes and update the `buttons`, `discretePOV`, `continuousPOV` and `axes` properties.
This also resets all buttons and pov switches to an unpressed state.

**resetButtons**()  
Resets all buttons to an unpressed state.

**free**()  
Relinquishes the device. **THIS NEEDS TO BE CALLED WHEN YOU DON'T NEED THE DEVICE ANYMORE, OTHERWISE NO OTHER PROCESS CAN ACQUIRE IT**.

**enableFFBEvents**()  
Enables the emission of Force Feedback events.
Note: After this method has been called on any device, the Node process will not exit on its own anymore, since a event listener has been registered with the driver.

**disableFFBEvents**()  
Disabled the emission of Force Feedback events.
This will not unregister the event listener from the driver however (since that is impossible), so you still need to quit your program explicitly.

### Events

Event "**ffb**"  
This is event will only be emitted after `enableFFBEvents()` has been called on a device.
The emitted object has the format
```
{
	type: String
	type_n: Number,
	effect: Object,
	ebi: Number,
	gain: Number,
	control: String,
	control_n: Number
}
```
Each of the values can also be `null`, in case the respective value was not found in the effect packet sent by the driver.
Every field ending in `_n` is just the numerical representation of a string field with the same name.
A complete overview over the different effect types and the data contained within them is outside the scope of this README and can be found in the documentation of the vJoy SDK.

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