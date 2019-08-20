const vjoy_native = require('../build/Release/vjoy');
const vJoy = require('./vjoy');

const vJoyButton = require('./vjoy_button');
const vJoyAxis = require('./vjoy_axis');
const vJoyDiscretePOV = require('./vjoy_disc_pov');
const vJoyContinuousPOV = require('./vjoy_cont_pov');

class vJoyDevice {
	constructor(id) {
		this._id = id;

		this._initialized = false;

		this._axes = {};
		this._buttons = {};
		this._discretePOV = {};
		this._continuousPOV = {};

		for (let axisId of vJoy.axes) {
			this._axes[axisId] = null;
		}
	}

	/**
	 * Convenience method to create and initialize a new vJoyDevice
	 * @param {Number} id 
	 * @return {vJoyDevice}
	 */
	static create(id) {
		if (!vJoyDevice.exists(id)) {
			return null;
		}

		let device = new vJoyDevice(id);

		let result = device.initialize();

		if (result) {
			device.updateInputs();

			return device;
		} else {
			return null;
		}
	}

	/**
	 * Check if a vJoy device id exists
	 * @param {Number} id 
	 * @returns {Boolean}
	 */
	static exists(id) {
		return vjoy_native.isVJDExists(id);
	}

	/**
	 * Check the status of a vJoy device
	 * @param {Number} id 
	 * @returns {String}
	 */
	static status(id) {
		let status = vjoy_native.GetVJDStatus(id);

		switch(status) {
			case "VJD_STAT_BUSY": 
				return "busy";
			case "VJD_STAT_MISS":
				return "missing";
			case "VJD_STAT_FREE":
				return "free";
			case "VJD_STAT_OWN":
				return "acquired";
			case "VJD_STAT_UNKN":
			default:
				return "unknown";
		}
	}

	get id() {
		return this._id;
	}

	get initialized() {
		return this._initialized;
	}

	get buttons() {
		return Object.freeze(this._buttons);
	}

	get discretePOV() {
		return Object.freeze(this._discretePOV);
	}

	get continuousPOV() {
		return Object.freeze(this._continuousPOV);
	}

	get axes() {
		return Object.freeze(this._axes);
	}

	get status() {
		return vJoyDevice.status(this.id);
	}

	/**
	 * Initializes the device by checking its status and acquriring it if possible.
	 * Returns true if the initialization was successful.
	 * @returns {Boolean}
	 */
	initialize() {
		let status = this.status;

		if (status == "busy" || status == "missing" || status == "unknown") {
			return false;
		}

		if (status == "free") {
			let result = vjoy_native.AcquireVJD(this.id);

			this._initialized = result;
			return result;
		} else if (status == "acquired") {
			this._initialized = true;
			return true;
		}
	}

	/**
	 * Query the driver for configured axes, buttons and POV switches.
	 * This also resets all button and POV values
	 */
	updateInputs() {
		if (!this.initialized) throw new Error("Device is not initialized");

		vjoy_native.ResetVJD(this.id);

		let buttonCount = vjoy_native.GetVJDButtonNumber(this.id);
		let discPovCount = vjoy_native.GetVJDDiscPovNumber(this.id);
		let contPovCount = vjoy_native.GetVJDContPovNumber(this.id);

		let buttonCountBefore = Object.keys(this._buttons).length;
		let discPovCountBefore = Object.keys(this._discretePOV).length;
		let contPovCountBefore = Object.keys(this._continuousPOV).length;

		// delete additional buttons
		if (buttonCountBefore > buttonCount) {
			for(let buttonId = buttonCount + 1; buttonId <= buttonCountBefore; buttonId++) {
				delete this._buttons[buttonId];
			}
		}

		// create new buttons
		for(let buttonId = 1; buttonId <= buttonCount; buttonId++) {
			if (this._buttons[buttonId] == undefined) {
				this._buttons[buttonId] = new vJoyButton(this, buttonId);
			} else {
				this._buttons[buttonId]._reset();
			}
		}

		// delete additional discrete POV switches
		if (discPovCountBefore > discPovCount) {
			for(let i = discPovCount + 1; i <= discPovCountBefore; i++) {
				delete this._discretePOV[i];
			}
		}

		// create new discrete POV switches
		for(let povId = 1; povId <= discPovCount; povId++) {
			if (this._discretePOV[povId] == undefined) {
				this._discretePOV[povId] = new vJoyDiscretePOV(this, povId);
			} else {
				this._discretePOV[povId]._reset();
			}
		}

		// delete additional continuous POV switches
		if (contPovCountBefore > contPovCount) {
			for(let i = contPovCount + 1; i <= contPovCountBefore; i++) {
				delete this._continuousPOV[i];
			}
		}

		// create new continuous POV switches
		for(let povId = 1; povId <= contPovCount; povId++) {
			if (this._continuousPOV[povId] == undefined) {
				this._continuousPOV[povId] = new vJoyContinuousPOV(this, povId);
			} else {
				this._continuousPOV[povId]._reset();
			}
		}

		// check which axes exist and update the corresponding object
		for(let axisId of vJoy.axes) {
			let exists = vjoy_native.GetVJDAxisExists(this.id, axisId);

			if (exists && this._axes[axisId] == null) {
				this._axes[axisId] = new vJoyAxis(this, axisId);
			} else if (!exists && this._axes[axisId] != null) {
				delete this._axes[axisId];
			}
		}
	}

	/**
	 * Sets all buttons to not pressed
	 * @returns {Boolean}
	 */
	resetButtons() {
		let result = vjoy_native.ResetButtons(this.id);

		if (result) {
			for(let buttonId in this.buttons) {
				this.buttons[buttonId]._reset();
			}
		}

		return result;
	}

	/**
	 * Relinquishes the device. Do not forget to relinquish a device if you want other feeders to access it.
	 */
	free() {
		this._initialized = false;
		return vjoy_native.RelinquishVJD(this.id);
	}
}

module.exports = vJoyDevice;