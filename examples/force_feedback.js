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

device.enableFFBEvents();

console.log("Captured events:");
console.log("----------------");

device.on("ffb", evt => {
	console.log(`Event ${evt.type}`);

	if (evt.effect != null) {
		console.log("    Effect data:");
		for (let key in evt.effect) {
			console.log(`        ${key}: ${evt.effect[key]}`);
		}
	}

	if (evt.ebi != null) {
		console.log(`    Effect Block Index: ${evt.ebi}`);
	}

	if (evt.gain != null) {
		console.log(`    Gain: ${evt.gain}`);
	}

	if (evt.control != null) {
		console.log(`    Control: ${evt.control}`);
	}

	console.log();
});