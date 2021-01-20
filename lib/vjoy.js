const vjoy_native = require('../build/Release/vjoy');

// display warning if driver version does not match
let check = vjoy_native.DriverMatch();

if (!check.matches && !("DISABLE_VJOY_VERSION_CHECK" in process.env)) {
	if (check.dll_version > check.drv_version) {
		console.warn(`WARNING: The installed version (${check.drv_version}) of vJoy is older than the SDK this library was built against (${check.dll_version}). If you run into problems, please update your vJoy installation.`);
	} else {
		console.warn(`WARNING: The installed version (${check.drv_version}) of vJoy is newer than the SDK this library was built against (${check.dll_version}). Please notify the author so he can update the library.`);
	}
}

const AXES = Object.freeze([ "X", "Y", "Z", "Rx", "Ry", "Rz", "Slider0", "Slider1", "Wheel", "POV" ]);

function registerRemovalCB(callback) {
	vjoy_native.RegisterRemovalCB(function(evt) {
		process.nextTick(() => {
			callback(evt);
		});
	});
}

module.exports = {
	isEnabled: vjoy_native.vJoyEnabled,
	version: vjoy_native.GetvJoyVersion,
	productString: vjoy_native.GetvJoyProductString,
	manufacturerString: vjoy_native.GetvJoyManufacturerString,
	serialString: vjoy_native.GetvJoySerialNumberString,
	driverMatch: vjoy_native.DriverMatch,
	maxDevices: vjoy_native.GetvJoyMaxDevices,
	existingDevices: vjoy_native.GetNumberExistingVJD,
	axes: AXES,
	registerRemovalCB,
};