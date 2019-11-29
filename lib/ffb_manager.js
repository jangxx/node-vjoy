const vjoy_native = require('../build/Release/vjoy');

class FFBManager {
	constructor() {
		this._registeredCallbacks = {};
		this._driverRegistered = false;
	}

	_handleEvent(deviceId, evt) {
		if (deviceId in this._registeredCallbacks) {
			this._registeredCallbacks[deviceId].call(null, evt);
		}
	}

	register(deviceId, callback) {
		// only register with the driver after a device wants to get FFB events
		if (!this._driverRegistered) {
			vjoy_native.FfbRegisterGenCB((id, evt) => {
				// run code in the main thread to be able to handle errors 
				process.nextTick(() => {
					this._handleEvent(id, evt);
				});
			});
			this._driverRegistered = true;
		}

		this._registeredCallbacks[deviceId] = callback;
	}

	unregister(deviceId) {
		if (deviceId in this._registeredCallbacks) {
			delete this._registeredCallbacks[deviceId];
		}
	}
}

module.exports = new FFBManager();