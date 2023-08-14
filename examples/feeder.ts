import { vJoyDevice, vJoy } from "../";

let deviceId = 1;

if (process.argv.length > 2) {
	deviceId = Number(process.argv[2]);
}

if (!vJoy.isEnabled()) {
	console.log("vJoy is not enabled.");
	process.exit();
}

let device = vJoyDevice.create(deviceId);

if (device == null) {
	console.log(`Could not initialize the device. Status: ${vJoyDevice.status(deviceId)}`);
	process.exit();
}

let axisVal = 0;
let activeButton = 0;

setInterval(() => {
	if (!device) return;

	axisVal = modClamp(axisVal + 200, 1, 0x8000);
	activeButton = modClamp(activeButton + 1, 1, 9);

	// set X, Y and Z axes
	if (device.axes.Z != null) {
		device.axes.Z.set(axisVal);
	}
	if (device.axes.X != null) {
		device.axes.X.set(modClamp(32000 - axisVal, 1, 0x8000));
	}
	if (device.axes.Y != null) {
		device.axes.Y.set(modClamp(Math.round(axisVal/2) + 7000, 1, 0x8000));
	}

	// set first 8 buttons
	device.resetButtons();

	if (device.buttons[activeButton] != undefined) {
		device.buttons[activeButton].set(true);
	}
}, 100);

function modClamp(value: number, lower: number, upper: number) {
	let diff = upper - lower;
	value -= lower;

	return lower + ((value % diff) + diff) % diff;
}