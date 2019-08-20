const vjoy_native = require('../build/Release/vjoy');

class vJoyAxis {
	constructor(parent, axisId) {
		this._parent = parent;

		this._id = axisId;
		this._value = 0x4000;
	}

	get id() {
		return this._id;
	}

	get value() {
		return this._value;
	}

	/**
	 * Reset the internal value of the POV abstraction
	 */
	_reset() {
		this._value = 0x4000;
	}

	/**
	 * Set the value of the axis between 1 and 32769 (0x8000)
	 * @param {Number} value 
	 * @returns {Boolean}
	 */
	set(value) {
		if (!this._parent.initialized) throw new Error("Device is not initialized");

		if (value < 1 || value > 0x8000) {
			throw new Error("Invalid value");
		}

		let result = vjoy_native.SetAxis(this._parent.id, this.id, value);

		if (result) {
			this._value = value;
		}

		return result;
	}
}

module.exports = vJoyAxis;