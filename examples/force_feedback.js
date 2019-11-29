const { vJoyDevice, vJoy } = require('../');

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

console.log("FFB supported:", device.ffbSupported);
console.log("Supported effects:");

let effects = device.ffbEffects;
for (let effect in effects) {
	console.log(`    ${effect}: ${effects[effect]}`);
}

// const vjoy_native = require('../build/Release/vjoy');
// vjoy_native.FfbRegisterGenCB((id, evt) => console.log(id, evt));

device.enableFFBEvents();

console.log("Captured events:");

device.on("ffb", evt => {
	console.log(`Event ${evt.type}`);

	if (evt.effect != null) {
		console.log("    Effect data:");
		for (let key in evt.effect) {
			console.log(`        ${key}: ${evt.effect[key]}`);
		}
	}

	if (evt.ebi != -1) {
		console.log(`    Effect Block Index: ${evt.ebi}`);
	}

	if (evt.gain != 0) {
		console.log(`    Gain: ${evt.gain}`);
	}

	if (evt.control != null) {
		console.log(`    Control: ${evt.control}`);
	}

	console.log();
});